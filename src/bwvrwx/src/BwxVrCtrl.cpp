#include "stdafx.h"

#include "wx/module.h"
#include "wx/msw/private.h"
#include "wx/msw/palette.h"

#include "BwxVrCtrl.h"

#include <bwstd/BwException.h>

#include <bwvr/config/ogre.h>

// ----------------------------------------------------------------------------
static const wxChar *BwxVrCtrlClassName = wxT("BwxVrCtrlClass");
static const wxChar *BwxVrCtrlClassNameNoRedraw = wxT("BwxVrCtrlClassNR");

LRESULT WXDLLEXPORT APIENTRY _EXPORT wxWndProc(HWND hWnd, UINT message,
                                   WPARAM wParam, LPARAM lParam);

class bwxOgreModule : public wxModule
{
public:
	bool OnInit() { return true; }
	void OnExit() { UnregisterClasses(); }

	// register the classes if not done yet, return true if ok, false if
	// registration failed
	static bool RegisterClasses();

	// unregister the classes, done automatically on program termination
	static void UnregisterClasses();

private:
    // BwxVrCtrl is only used from the main thread so this is MT-ok
    static bool ms_registeredOgreClasses;

    DECLARE_DYNAMIC_CLASS(bwxOgreModule)
};

IMPLEMENT_DYNAMIC_CLASS(bwxOgreModule, wxModule)

bool bwxOgreModule::ms_registeredOgreClasses = false;

/* static */
bool bwxOgreModule::RegisterClasses()
{
    if (ms_registeredOgreClasses)
        return true;

    WNDCLASSEX wndclass;
    wndclass.cbSize			= sizeof(WNDCLASSEX);
    wndclass.style			= CS_HREDRAW|CS_VREDRAW|CS_OWNDC|CS_DBLCLKS; // Redraw all when resized, OWNER DC for speed
    wndclass.lpfnWndProc	= (WNDPROC)wxWndProc; // what is this DWORD used for?
    wndclass.cbClsExtra		= 0;
    wndclass.cbWndExtra		= sizeof( DWORD );
    wndclass.hInstance		= wxhInstance;
    wndclass.hIcon			= NULL;
    wndclass.hIconSm		= NULL;
	wndclass.hCursor		= ::LoadCursor(NULL,IDC_ARROW);
    wndclass.hbrBackground	= NULL;
    wndclass.lpszMenuName	= NULL;
    wndclass.lpszClassName	= BwxVrCtrlClassName;

    if ( !::RegisterClassEx(&wndclass) )
    {
        wxLogLastError(wxT("RegisterClassEx(BwxVrCtrlClass)"));
        return false;
    }

	wndclass.style			&= ~ (CS_HREDRAW|CS_VREDRAW);
    wndclass.lpszClassName	= BwxVrCtrlClassNameNoRedraw;
    if ( !::RegisterClassEx(&wndclass) )
    {
		::UnregisterClass(BwxVrCtrlClassName, wxhInstance);
        wxLogLastError(wxT("RegisterClassEx(BwxVrCtrlClassNR)"));
        return false;
    }

    ms_registeredOgreClasses = true;

    return true;
}

/* static */
void bwxOgreModule::UnregisterClasses()
{
    // we need to unregister the classes in case we're in a DLL which is
    // unloaded and then loaded again because if we don't, the registration is
    // going to fail in BwxVrCtrl::Create() the next time we're loaded
    if ( ms_registeredOgreClasses )
    {
        ::UnregisterClass(BwxVrCtrlClassName, wxhInstance);
        ::UnregisterClass(BwxVrCtrlClassNameNoRedraw, wxhInstance);

        ms_registeredOgreClasses = false;
    }
}
// ----------------------------------------------------------------------------
const long ID_RENDERTIMER = wxNewId();

IMPLEMENT_CLASS(BwxVrCtrl, wxControl)

BEGIN_EVENT_TABLE(BwxVrCtrl, wxControl)
	EVT_SIZE(BwxVrCtrl::OnSize)
	//EVT_PAINT(BwxVrCtrl::OnPaint) // don't try this :(
	EVT_ERASE_BACKGROUND( BwxVrCtrl::OnEraseBackground )
	EVT_TIMER( ID_RENDERTIMER, BwxVrCtrl::OnRenderTimer )
END_EVENT_TABLE()

BwxVrCtrl::BwxVrCtrl(		wxWindow* parent,
							BwxVrCtrlInfo& info,
							wxWindowID id /* = wxID_ANY */, 
							const wxPoint& pos /* = wxDefaultPosition */, 
							const wxSize& size /* = wxDefaultSize */, 
							long style /* = 0  */ ) :
	wxControl(),
	p_applet(NULL),
	mRoot( 0 ),
	//mD3DRenderSystem( 0 ),
	mD3DRenderWindow( 0 ),
	mSceneMgr( 0 ),
	mCamera( 0 ),
	mViewport( 0 ),
	mReady( false ),
	m_hwnd( 0 ),
	mTimer(this, ID_RENDERTIMER)
{
	bool ret = Create(parent, info, id, pos, size, style);
}
BwxVrCtrl::~BwxVrCtrl()
{
	cleanupOgre();
	m_hwnd = 0;
}
bool BwxVrCtrl::Create( wxWindow *parent, BwxVrCtrlInfo& info, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
{
    wxCHECK_MSG( parent, false, wxT("can't create wxWindow without parent") );

	style |= wxFULL_REPAINT_ON_RESIZE;

	if ( !bwxOgreModule::RegisterClasses() )
    {
        wxLogError(_("Failed to register BwxVrCtrl window class."));
        return false;
    }

    if ( !CreateBase(parent, id, pos, size, style, wxDefaultValidator, "OgreControl") )
        return false;

    parent->AddChild(this);

    DWORD msflags = WS_CHILD | WS_VISIBLE;
    WXDWORD exStyle = 0;

    bool ret = MSWCreate(BwxVrCtrlClassName, NULL, pos, size, msflags, exStyle);
	wxCHECK_MSG( ret, false, wxT("Could not create window. MSWCreate() failed") );
	if (!ret)
		return false;

	m_hwnd = HWND( GetHWND() );

	using namespace Ogre;

	try {
		p_applet = info.produceApplet(this) ;
		p_applet->createEmbedded(m_hwnd, bwSize2(size.GetWidth(), size.GetHeight())) ;
		mD3DRenderWindow = p_applet->getRenderWindow() ;
	}
	catch(BwException &e) {
		return false ;
	}
	//f6:fixme:more elegant way?  Wasn't necessary in wxWidgets 2.6
	//causes infinite message loop.
	m_oldWndProc = NULL ;
	//
	return true;
}
void BwxVrCtrl::startRendering( const preferredTimeStep /* = 100  */)
{
	if (mTimer.IsRunning())
		mTimer.Stop();
	mTimer.Start(preferredTimeStep);
}
//f6:fixme:isn't this redundant?
void BwxVrCtrl::cleanupOgre()
{
	using namespace Ogre;

	try {
		if (mReady)
		{
			//clear scene @todo: move to clearScene()
			MeshManager::getSingletonPtr()->removeAll();
			SkeletonManager::getSingletonPtr()->removeAll();
			MaterialManager::getSingletonPtr()->removeAll();
			TextureManager::getSingletonPtr()->removeAll();
			GpuProgramManager::getSingletonPtr()->removeAll();
			mSceneMgr->destroyAllEntities();

			SceneNode *root = mSceneMgr->getRootSceneNode();
			if (root)
			{
				if (root->numChildren())
					root->removeAllChildren();
			}
		}
		// destroy / close OGRE
		delete mRoot;
		mRoot = 0;
	}
	catch (Ogre::Exception& e)
	{
		wxMessageBox(e.getFullDescription().c_str(), "OGRE Exception" );
		cleanupOgre();
	}
}
void BwxVrCtrl::OnSize(wxSizeEvent& event)
{
	try {
		if (mD3DRenderWindow)
			mD3DRenderWindow->windowMovedOrResized();
	}
	catch (Ogre::Exception& e)
	{
		wxMessageBox(e.getFullDescription().c_str(), "OGRE Exception" );
		cleanupOgre();
	}
	//mSigResize( event.GetSize().GetWidth(), event.GetSize().GetHeight() );
	Refresh();
}
void BwxVrCtrl::OnRenderTimer(wxTimerEvent& event)
{
	p_applet->doStep() ;
	p_applet->doPostStep() ;
	/*try {
		if (mRoot) 
		{
			if (!mRoot->renderOneFrame())
			{
				//@todo do something useful here...
			}
		}
	}
	catch (Ogre::Exception& e)
	{
		wxMessageBox(e.getFullDescription().c_str(), "OGRE Exception" );
		cleanupOgre();
	}*/
}
void BwxVrCtrl::OnPaint(wxPaintEvent& event)
{
#if 0 // DON'T use this. It doesn't work. Really. Strange effects.
	try {
		if (mRoot)
			mRoot->renderOneFrame();
	}
	catch (Ogre::Exception& e)
	{
		wxMessageBox(e.getFullDescription().c_str(), "OGRE Exception" );
		cleanupOgre();
	}
#endif
}
void BwxVrCtrl::OnEraseBackground(wxEraseEvent&)
{
}
Ogre::RenderWindow* BwxVrCtrl::_getRenderWindow() const
{ 
	return mD3DRenderWindow; 
}
unsigned short BwxVrCtrl::getRenderWindowWidth() const
{
	if (mD3DRenderWindow)
		return mD3DRenderWindow->getWidth();
	else
		return 0;
}
unsigned short BwxVrCtrl::getRenderWindowHeight() const
{
	if (mD3DRenderWindow)
		return mD3DRenderWindow->getHeight();
	else
		return 0;
}

#ifndef _BwxVrCtrl_H
#define _BwxVrCtrl_H

#include <bwvr/VrApplet.h>

namespace Ogre {
	class Root;
	class RenderWindow;
	class D3D9RenderSystem;
	class D3D9RenderWindow;
	class SceneManager;
	class Camera;
	class Viewport; 
}

class BwxVrCtrl ;

class BwxVrCtrlInfo {
public:
	virtual VrApplet* produceApplet(BwxVrCtrl* pCtrl) {
		_ASSERT(0) ;
		return NULL ;
	}
} ;

class BwxVrCtrl : public wxControl
{
	DECLARE_CLASS(BwxVrCtrl)
public:
	BwxVrCtrl(	wxWindow* parent,
				BwxVrCtrlInfo& info = BwxVrCtrlInfo(),
				wxWindowID id = wxID_ANY,
				const wxPoint& pos = wxDefaultPosition,
				const wxSize& size = wxDefaultSize, 
				long style = 0 );
	~BwxVrCtrl();

    // Replaces wxWindow::Create functionality, since
    // we need to use a different window class
	bool Create(	wxWindow *parent,
					BwxVrCtrlInfo& info,
					wxWindowID id,
					const wxPoint& pos, 
					const wxSize& size,
					long style);
	void startRendering( const preferredTimeStep = 100 ); // in milliseconds

	Ogre::RenderWindow* _getRenderWindow() const;

	//ED_SIGNAL( Resize, void(const unsigned short, const unsigned short), public );

	unsigned short getRenderWindowWidth() const;
	unsigned short getRenderWindowHeight() const;
protected:
	DECLARE_EVENT_TABLE()

	void OnSize(wxSizeEvent& event);
	void OnPaint(wxPaintEvent& event);
	void OnEraseBackground( wxEraseEvent& );
	void OnRenderTimer(wxTimerEvent& event);
	//
public:
	VrApplet* getApplet() { return p_applet ; }
private:
	VrApplet *p_applet ;
	wxTimer					mTimer;

	// win32 stuff
	HWND					m_hwnd;

	// Ogre Stuff
	void cleanupOgre();

	Ogre::Root*				mRoot;
	Ogre::RenderWindow*		mD3DRenderWindow;
	Ogre::SceneManager*		mSceneMgr;
	Ogre::Camera*			mCamera;
	Ogre::Viewport*			mViewport; 

	bool					mReady;
};

#endif

#include "stdafx.h"
#include <bwbotworx/BwxMindTreeCtrl.h>
#include <bwbotworx/BwxEvent.h>
//
#include <bwmessaging/BwMailSlot.h>

#include <bwagency/BwAgent.h>
#include <bwagency/BwAgentSession.h>
#include <bwagency/BwAgentClient.h>
#include <bwagency/_BwAgent.h>
using namespace _BwAgent ;
//
#include <bwmessaging/BwCmd.h>
#include <bwapplet/BwAppletSession.h>
#include <bwbotworx/_BwxAgentApplet.h>
using namespace _BwxAgentApplet ;
//
#include <wx/image.h>
#include <wx/toolbar.h>

#include <bwwx/resource/icon/xpm/icon1.xpm>
#include <bwwx/resource/icon/xpm/icon2.xpm>
#include <bwwx/resource/icon/xpm/icon3.xpm>
#include <bwwx/resource/icon/xpm/icon4.xpm>
#include <bwwx/resource/icon/xpm/icon5.xpm>

class BwxMindTreeCtrl ;

namespace _BwxMindTreeCtrl {
class MyClient : public BwAgentClient {
public:
	MyClient(BwxMindTreeCtrl *pOwner) : p_ctrl(pOwner) {}
	virtual bwString getClassName() { return "MyClient" ; }
	virtual void onEvent(const BwMessage& msg) ;
	//
	BwxMindTreeCtrl *p_ctrl ;
};
void MyClient::onEvent(const BwMessage& msg) {
	switch(msg.what()) {
		case EVENT_STATE_ADDED :
		case EVENT_FRAME_ADDED :
		{
			bwString path ;
			bwHandle handle ;
			bwHandle parentHandle ;
			bwString arc ;
			msg()->findString("PATH", path) ;
			msg()->findHandle("HANDLE", handle) ;
			msg()->findHandle("PARENT", parentHandle) ;
			p_ctrl->CreateItem(path, handle, parentHandle, "duh") ;
		}
		break ;
	}
	BwAgentClient::onEvent(msg) ;
}
} ; //namespace BwxMindTreeCtrl
///////////////
using namespace _BwxMindTreeCtrl ;

class BwxApp ;

// BwxMindTreeCtrl implementation
//IMPLEMENT_DYNAMIC_CLASS(BwxMindTreeCtrl, wxTreeCtrl)
IMPLEMENT_DYNAMIC_CLASS(BwxMindTreeCtrl, BwxTreeCtrl)

BwxMindTreeCtrl::BwxMindTreeCtrl(wxWindow *parent, const BwxContext& context)
	//: BwxTreeCtrl(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE), m_context(context)
	: BwxTreeCtrl(parent, ID_BwxMindTreeCtrl, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE), m_context(context)
{
	p_client = new MyClient(this) ;
	p_client->create() ;
	p_client->connect(context.getAgentSession()) ;

    m_reverseSort = false;
    CreateImageList();

	int image = wxGetApp().ShowImages() ? BwxMindTreeCtrl::TreeCtrlIcon_Folder : -1;

	wxTreeItemId rootId = AddRoot(wxT("/"), image, image, new BwxTreeItemData(wxT("Root item")));
	m_itemMap["/"] = rootId ;
    if ( image != -1 )
    {
        SetItemImage(rootId, TreeCtrlIcon_FolderOpened, wxTreeItemIcon_Expanded);
    }
}
void BwxMindTreeCtrl::CreateItem(const bwPath &path, bwHandle handle, bwHandle parentHandle, const bwString& arc) {
	int image, imageSel;
	//image = depth == 1 ? TreeCtrlIcon_File : TreeCtrlIcon_Folder;
	image = TreeCtrlIcon_Folder;
	imageSel = image + 1 ;

	wxTreeItemId idParent ;

	if(path.string() == "/") //f6:fixme:create root node here!!!
		return ;
	if(path.has_branch_path())
		idParent = m_itemMap[path.branch_path().string()] ;
	else
		idParent = GetRootItem() ;

	//wxString str = path.leaf().c_str() ;
	//
	BwxTreeItemData* pData = new BwxMindTreeItemData(path, handle, parentHandle, arc) ;
	wxTreeItemId id = AppendItem(idParent, pData->m_desc, image, imageSel, pData );
	m_itemMap[path.string()] = id ;
}
void BwxMindTreeCtrl::OnItemActivated(wxTreeEvent& event) {
    wxTreeItemId itemId = event.GetItem();
    BwxMindTreeItemData *item = (BwxMindTreeItemData *)GetItemData(itemId);
	m_context.getAppletSession()->getApplet()->getEventSlot().send(BwxStateSelectedEvent(item->m_handle)) ;
	const size_t bufferSize = 16;
	char buffer[bufferSize] ;
	//_itoa(item->m_handle, buffer, 10) ;
	//snprintf(buffer, bufferSize, "%d", item->m_handle);
	bwItoa(item->m_handle, buffer, bufferSize, 10);
	BwCmd cmd("selectMind");
	p_client->doCommand(cmd << bwString(buffer) << end) ;

}
///////
BEGIN_EVENT_TABLE(BwxMindTreeCtrl, BwxTreeCtrl)
    EVT_TREE_BEGIN_DRAG(ID_BwxMindTreeCtrl, BwxTreeCtrl::OnBeginDrag)
    EVT_TREE_BEGIN_RDRAG(ID_BwxMindTreeCtrl, BwxTreeCtrl::OnBeginRDrag)
    EVT_TREE_END_DRAG(ID_BwxMindTreeCtrl, BwxTreeCtrl::OnEndDrag)
    EVT_TREE_BEGIN_LABEL_EDIT(ID_BwxMindTreeCtrl, BwxTreeCtrl::OnBeginLabelEdit)
    EVT_TREE_END_LABEL_EDIT(ID_BwxMindTreeCtrl, BwxTreeCtrl::OnEndLabelEdit)
    EVT_TREE_DELETE_ITEM(ID_BwxMindTreeCtrl, BwxTreeCtrl::OnDeleteItem)
#if 0       // there are so many of those that logging them causes flicker
    EVT_TREE_GET_INFO(ID_BwxMindTreeCtrl, BwxTreeCtrl::OnGetInfo)
#endif
    EVT_TREE_SET_INFO(ID_BwxMindTreeCtrl, BwxTreeCtrl::OnSetInfo)
    EVT_TREE_ITEM_EXPANDED(ID_BwxMindTreeCtrl, BwxTreeCtrl::OnItemExpanded)
    EVT_TREE_ITEM_EXPANDING(ID_BwxMindTreeCtrl, BwxTreeCtrl::OnItemExpanding)
    EVT_TREE_ITEM_COLLAPSED(ID_BwxMindTreeCtrl, BwxTreeCtrl::OnItemCollapsed)
    EVT_TREE_ITEM_COLLAPSING(ID_BwxMindTreeCtrl, BwxTreeCtrl::OnItemCollapsing)

    EVT_TREE_SEL_CHANGED(ID_BwxMindTreeCtrl, BwxTreeCtrl::OnSelChanged)
    EVT_TREE_SEL_CHANGING(ID_BwxMindTreeCtrl, BwxTreeCtrl::OnSelChanging)
    EVT_TREE_KEY_DOWN(ID_BwxMindTreeCtrl, BwxTreeCtrl::OnTreeKeyDown)
    EVT_TREE_ITEM_ACTIVATED(ID_BwxMindTreeCtrl, BwxMindTreeCtrl::OnItemActivated)

    // so many differents ways to handle right mouse button clicks...
    EVT_CONTEXT_MENU(BwxTreeCtrl::OnContextMenu)
    // EVT_TREE_ITEM_MENU is the preferred event for creating context menus
    // on a tree control, because it includes the point of the click or item,
    // meaning that no additional placement calculations are required.
    EVT_TREE_ITEM_MENU(ID_BwxMindTreeCtrl, BwxTreeCtrl::OnItemMenu)
    EVT_TREE_ITEM_RIGHT_CLICK(ID_BwxMindTreeCtrl, BwxTreeCtrl::OnItemRClick)

    EVT_RIGHT_DOWN(BwxTreeCtrl::OnRMouseDown)
    EVT_RIGHT_UP(BwxTreeCtrl::OnRMouseUp)
    EVT_RIGHT_DCLICK(BwxTreeCtrl::OnRMouseDClick)
END_EVENT_TABLE()

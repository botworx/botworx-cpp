#include "stdafx.h"

#include <bwbotworx/BwxTreeCtrl.h>
#include <bwbotworx/BwxEvent.h>
//
#include <bwmessaging/BwMailSlot.h>

#include <wx/image.h>
#include <wx/imaglist.h>

#include <bwwx/resource/icon/xpm/icon1.xpm>
#include <bwwx/resource/icon/xpm/icon2.xpm>
#include <bwwx/resource/icon/xpm/icon3.xpm>
#include <bwwx/resource/icon/xpm/icon4.xpm>
#include <bwwx/resource/icon/xpm/icon5.xpm>

// BwxTreeCtrl implementation
IMPLEMENT_DYNAMIC_CLASS(BwxTreeCtrl, wxTreeCtrl)

BwxTreeCtrl::BwxTreeCtrl(wxWindow *parent, const wxWindowID id,
                       const wxPoint& pos, const wxSize& size,
                       long style)
          : wxTreeCtrl(parent, id, pos, size, style)
{
}
void BwxTreeCtrl::CreateItem(const bwPath &path) {
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

	wxString str = path.leaf().c_str() ;
	wxTreeItemId id = AppendItem(idParent, str, image, imageSel,
                                         new BwxTreeItemData(str));
	m_itemMap[path.string()] = id ;
}
void BwxTreeCtrl::CreateImageList(int size) {
    if ( size == -1 ) {
        SetImageList(NULL);
        return;
    }
    if ( size == 0 )
        size = m_imageSize;
    else
        m_imageSize = size;

    // Make an image list containing small icons
    wxImageList *images = new wxImageList(size, size, true);

    // should correspond to TreeCtrlIcon_xxx enum
    wxBusyCursor wait;
    wxIcon icons[5];
    icons[0] = wxIcon(icon1_xpm);
    icons[1] = wxIcon(icon2_xpm);
    icons[2] = wxIcon(icon3_xpm);
    icons[3] = wxIcon(icon4_xpm);
    icons[4] = wxIcon(icon5_xpm);

    int sizeOrig = icons[0].GetWidth();
    for ( size_t i = 0; i < WXSIZEOF(icons); i++ ) {
        if ( size == sizeOrig ) {
            images->Add(icons[i]);
        }
        else {
            images->Add(wxBitmap(wxBitmap(icons[i]).ConvertToImage().Rescale(size, size)));
        }
    }

    AssignImageList(images);
}

#if USE_GENERIC_TREECTRL || !defined(__WXMSW__)
void BwxTreeCtrl::CreateButtonsImageList(int size) {
    if ( size == -1 ) {
        SetButtonsImageList(NULL);
        return;
    }

    // Make an image list containing small icons
    wxImageList *images = new wxImageList(size, size, true);

    // should correspond to TreeCtrlIcon_xxx enum
    wxBusyCursor wait;
    wxIcon icons[4];
    icons[0] = wxIcon(icon3_xpm);   // closed
    icons[1] = wxIcon(icon3_xpm);   // closed, selected
    icons[2] = wxIcon(icon5_xpm);   // open
    icons[3] = wxIcon(icon5_xpm);   // open, selected

    for ( size_t i = 0; i < WXSIZEOF(icons); i++ ) {
        int sizeOrig = icons[i].GetWidth();
        if ( size == sizeOrig ) {
            images->Add(icons[i]);
        }
        else {
            images->Add(wxBitmap(wxBitmap(icons[i]).ConvertToImage().Rescale(size, size)));
        }
    }

    AssignButtonsImageList(images);
#else
void BwxTreeCtrl::CreateButtonsImageList(int WXUNUSED(size)) {
#endif
}

int BwxTreeCtrl::OnCompareItems(const wxTreeItemId& item1, const wxTreeItemId& item2) {
    if ( m_reverseSort ) {
        // just exchange 1st and 2nd items
        return wxTreeCtrl::OnCompareItems(item2, item1);
    }
    else {
        return wxTreeCtrl::OnCompareItems(item1, item2);
    }
}
void BwxTreeCtrl::AddItemsRecursively(const wxTreeItemId& idParent,
                                     size_t numChildren,
                                     size_t depth,
                                     size_t folder)
{
    if ( depth > 0 ) {
        bool hasChildren = depth > 1;

        wxString str;
        for ( size_t n = 0; n < numChildren; n++ ) {
            // at depth 1 elements won't have any more children
            if ( hasChildren )
                str.Printf(wxT("%s child %d"), wxT("Folder"), n + 1);
            else
                str.Printf(wxT("%s child %d.%d"), wxT("File"), folder, n + 1);

            // here we pass to AppendItem() normal and selected item images (we
            // suppose that selected image follows the normal one in the enum)
            int image, imageSel;
            if ( wxGetApp().ShowImages() ) {
                image = depth == 1 ? TreeCtrlIcon_File : TreeCtrlIcon_Folder;
                imageSel = image + 1;
            }
            else {
                image = imageSel = -1;
            }
            wxTreeItemId id = AppendItem(idParent, str, image, imageSel,
                                         new BwxTreeItemData(str));

            // and now we also set the expanded one (only for the folders)
            if ( hasChildren && wxGetApp().ShowImages() ) {
                SetItemImage(id, TreeCtrlIcon_FolderOpened,
                             wxTreeItemIcon_Expanded);
            }
            // remember the last child for OnEnsureVisible()
            if ( !hasChildren && n == numChildren - 1 ) {
                m_lastItem = id;
            }

            AddItemsRecursively(id, numChildren, depth - 1, n + 1);
        }
    }
    //else: done!
}

void BwxTreeCtrl::AddTestItemsToTree(size_t numChildren, size_t depth) {
    int image = wxGetApp().ShowImages() ? BwxTreeCtrl::TreeCtrlIcon_Folder : -1;
    wxTreeItemId rootId = AddRoot(wxT("Root"),
                                  image, image,
                                  new BwxTreeItemData(wxT("Root item")));
    if ( image != -1 ) {
        SetItemImage(rootId, TreeCtrlIcon_FolderOpened, wxTreeItemIcon_Expanded);
    }

    AddItemsRecursively(rootId, numChildren, depth, 0);

    // set some colours/fonts for testing
    //SetItemFont(rootId, *wxITALIC_FONT);

    wxTreeItemIdValue cookie;
    wxTreeItemId id = GetFirstChild(rootId, cookie);
    //SetItemTextColour(id, *wxBLUE);

    id = GetNextChild(rootId, cookie);
    id = GetNextChild(rootId, cookie);
    //SetItemTextColour(id, *wxRED);
    //SetItemBackgroundColour(id, *wxLIGHT_GREY);
}
void BwxTreeCtrl::GetItemsRecursively(const wxTreeItemId& idParent, wxTreeItemIdValue cookie) {
    wxTreeItemId id;

    if ( !cookie )
        id = GetFirstChild(idParent, cookie);
    else
        id = GetNextChild(idParent, cookie);

    if ( !id.IsOk() )
        return;

    wxString text = GetItemText(id);
    //wxLogMessage(text);

    if (ItemHasChildren(id))
        GetItemsRecursively(id);

    GetItemsRecursively(idParent, cookie);
}

void BwxTreeCtrl::DoToggleIcon(const wxTreeItemId& item) {
    int image = GetItemImage(item) == TreeCtrlIcon_Folder ? TreeCtrlIcon_File
                                                          : TreeCtrlIcon_Folder;

    SetItemImage(item, image);
}

void BwxTreeCtrl::OnBeginRDrag(wxTreeEvent& event){ SetLastItem(wxTreeItemId()); event.Skip(); }
void BwxTreeCtrl::OnDeleteItem(wxTreeEvent& event){ SetLastItem(wxTreeItemId()); event.Skip(); }
void BwxTreeCtrl::OnGetInfo(wxTreeEvent& event){ SetLastItem(wxTreeItemId()); event.Skip(); }
void BwxTreeCtrl::OnSetInfo(wxTreeEvent& event){ SetLastItem(wxTreeItemId()); event.Skip(); }
void BwxTreeCtrl::OnItemExpanded(wxTreeEvent& event){ SetLastItem(wxTreeItemId()); event.Skip(); }
void BwxTreeCtrl::OnItemExpanding(wxTreeEvent& event){ SetLastItem(wxTreeItemId()); event.Skip(); }
void BwxTreeCtrl::OnItemCollapsed(wxTreeEvent& event){ SetLastItem(wxTreeItemId()); event.Skip(); }
void BwxTreeCtrl::OnSelChanged(wxTreeEvent& event){ SetLastItem(wxTreeItemId()); event.Skip(); }
void BwxTreeCtrl::OnSelChanging(wxTreeEvent& event){ SetLastItem(wxTreeItemId()); event.Skip(); }

void BwxTreeCtrl::LogKeyEvent(const wxChar *name, const wxKeyEvent& event) {
    wxString key;
    long keycode = event.GetKeyCode();
    {
        switch ( keycode )
        {
            case WXK_BACK: key = wxT("BACK"); break;
            case WXK_TAB: key = wxT("TAB"); break;
            case WXK_RETURN: key = wxT("RETURN"); break;
            case WXK_ESCAPE: key = wxT("ESCAPE"); break;
            case WXK_SPACE: key = wxT("SPACE"); break;
            case WXK_DELETE: key = wxT("DELETE"); break;
            case WXK_START: key = wxT("START"); break;
            case WXK_LBUTTON: key = wxT("LBUTTON"); break;
            case WXK_RBUTTON: key = wxT("RBUTTON"); break;
            case WXK_CANCEL: key = wxT("CANCEL"); break;
            case WXK_MBUTTON: key = wxT("MBUTTON"); break;
            case WXK_CLEAR: key = wxT("CLEAR"); break;
            case WXK_SHIFT: key = wxT("SHIFT"); break;
            case WXK_ALT: key = wxT("ALT"); break;
            case WXK_CONTROL: key = wxT("CONTROL"); break;
            case WXK_MENU: key = wxT("MENU"); break;
            case WXK_PAUSE: key = wxT("PAUSE"); break;
            case WXK_CAPITAL: key = wxT("CAPITAL"); break;
            case WXK_END: key = wxT("END"); break;
            case WXK_HOME: key = wxT("HOME"); break;
            case WXK_LEFT: key = wxT("LEFT"); break;
            case WXK_UP: key = wxT("UP"); break;
            case WXK_RIGHT: key = wxT("RIGHT"); break;
            case WXK_DOWN: key = wxT("DOWN"); break;
            case WXK_SELECT: key = wxT("SELECT"); break;
            case WXK_PRINT: key = wxT("PRINT"); break;
            case WXK_EXECUTE: key = wxT("EXECUTE"); break;
            case WXK_SNAPSHOT: key = wxT("SNAPSHOT"); break;
            case WXK_INSERT: key = wxT("INSERT"); break;
            case WXK_HELP: key = wxT("HELP"); break;
            case WXK_NUMPAD0: key = wxT("NUMPAD0"); break;
            case WXK_NUMPAD1: key = wxT("NUMPAD1"); break;
            case WXK_NUMPAD2: key = wxT("NUMPAD2"); break;
            case WXK_NUMPAD3: key = wxT("NUMPAD3"); break;
            case WXK_NUMPAD4: key = wxT("NUMPAD4"); break;
            case WXK_NUMPAD5: key = wxT("NUMPAD5"); break;
            case WXK_NUMPAD6: key = wxT("NUMPAD6"); break;
            case WXK_NUMPAD7: key = wxT("NUMPAD7"); break;
            case WXK_NUMPAD8: key = wxT("NUMPAD8"); break;
            case WXK_NUMPAD9: key = wxT("NUMPAD9"); break;
            case WXK_MULTIPLY: key = wxT("MULTIPLY"); break;
            case WXK_ADD: key = wxT("ADD"); break;
            case WXK_SEPARATOR: key = wxT("SEPARATOR"); break;
            case WXK_SUBTRACT: key = wxT("SUBTRACT"); break;
            case WXK_DECIMAL: key = wxT("DECIMAL"); break;
            case WXK_DIVIDE: key = wxT("DIVIDE"); break;
            case WXK_F1: key = wxT("F1"); break;
            case WXK_F2: key = wxT("F2"); break;
            case WXK_F3: key = wxT("F3"); break;
            case WXK_F4: key = wxT("F4"); break;
            case WXK_F5: key = wxT("F5"); break;
            case WXK_F6: key = wxT("F6"); break;
            case WXK_F7: key = wxT("F7"); break;
            case WXK_F8: key = wxT("F8"); break;
            case WXK_F9: key = wxT("F9"); break;
            case WXK_F10: key = wxT("F10"); break;
            case WXK_F11: key = wxT("F11"); break;
            case WXK_F12: key = wxT("F12"); break;
            case WXK_F13: key = wxT("F13"); break;
            case WXK_F14: key = wxT("F14"); break;
            case WXK_F15: key = wxT("F15"); break;
            case WXK_F16: key = wxT("F16"); break;
            case WXK_F17: key = wxT("F17"); break;
            case WXK_F18: key = wxT("F18"); break;
            case WXK_F19: key = wxT("F19"); break;
            case WXK_F20: key = wxT("F20"); break;
            case WXK_F21: key = wxT("F21"); break;
            case WXK_F22: key = wxT("F22"); break;
            case WXK_F23: key = wxT("F23"); break;
            case WXK_F24: key = wxT("F24"); break;
            case WXK_NUMLOCK: key = wxT("NUMLOCK"); break;
            case WXK_SCROLL: key = wxT("SCROLL"); break;
            case WXK_PAGEUP: key = wxT("PAGEUP"); break;
            case WXK_PAGEDOWN: key = wxT("PAGEDOWN"); break;
            case WXK_NUMPAD_SPACE: key = wxT("NUMPAD_SPACE"); break;
            case WXK_NUMPAD_TAB: key = wxT("NUMPAD_TAB"); break;
            case WXK_NUMPAD_ENTER: key = wxT("NUMPAD_ENTER"); break;
            case WXK_NUMPAD_F1: key = wxT("NUMPAD_F1"); break;
            case WXK_NUMPAD_F2: key = wxT("NUMPAD_F2"); break;
            case WXK_NUMPAD_F3: key = wxT("NUMPAD_F3"); break;
            case WXK_NUMPAD_F4: key = wxT("NUMPAD_F4"); break;
            case WXK_NUMPAD_HOME: key = wxT("NUMPAD_HOME"); break;
            case WXK_NUMPAD_LEFT: key = wxT("NUMPAD_LEFT"); break;
            case WXK_NUMPAD_UP: key = wxT("NUMPAD_UP"); break;
            case WXK_NUMPAD_RIGHT: key = wxT("NUMPAD_RIGHT"); break;
            case WXK_NUMPAD_DOWN: key = wxT("NUMPAD_DOWN"); break;
            case WXK_NUMPAD_PAGEUP: key = wxT("NUMPAD_PAGEUP"); break;
            case WXK_NUMPAD_PAGEDOWN: key = wxT("NUMPAD_PAGEDOWN"); break;
            case WXK_NUMPAD_END: key = wxT("NUMPAD_END"); break;
            case WXK_NUMPAD_BEGIN: key = wxT("NUMPAD_BEGIN"); break;
            case WXK_NUMPAD_INSERT: key = wxT("NUMPAD_INSERT"); break;
            case WXK_NUMPAD_DELETE: key = wxT("NUMPAD_DELETE"); break;
            case WXK_NUMPAD_EQUAL: key = wxT("NUMPAD_EQUAL"); break;
            case WXK_NUMPAD_MULTIPLY: key = wxT("NUMPAD_MULTIPLY"); break;
            case WXK_NUMPAD_ADD: key = wxT("NUMPAD_ADD"); break;
            case WXK_NUMPAD_SEPARATOR: key = wxT("NUMPAD_SEPARATOR"); break;
            case WXK_NUMPAD_SUBTRACT: key = wxT("NUMPAD_SUBTRACT"); break;
            case WXK_NUMPAD_DECIMAL: key = wxT("NUMPAD_DECIMAL"); break;

            default:
            {
               if ( keycode < 128 && wxIsprint((int)keycode) )
                   key.Printf(wxT("'%c'"), (char)keycode);
               else if ( keycode > 0 && keycode < 27 )
                   key.Printf(_("Ctrl-%c"), wxT('A') + keycode - 1);
               else
                   key.Printf(wxT("unknown (%ld)"), keycode);
            }
        }
    }

    /*wxLogMessage( wxT("%s event: %s (flags = %c%c%c%c)"),
                  name,
                  key.c_str(),
                  event.ControlDown() ? wxT('C') : wxT('-'),
                  event.AltDown() ? wxT('A') : wxT('-'),
                  event.ShiftDown() ? wxT('S') : wxT('-'),
                  event.MetaDown() ? wxT('M') : wxT('-'));*/
}

void BwxTreeCtrl::OnTreeKeyDown(wxTreeEvent& event)
{
    LogKeyEvent(wxT("Tree key down "), event.GetKeyEvent());

    event.Skip();
}

void BwxTreeCtrl::OnBeginDrag(wxTreeEvent& event)
{
    // need to explicitly allow drag
    if ( event.GetItem() != GetRootItem() )
    {
        m_draggedItem = event.GetItem();

        /*wxLogMessage(wxT("OnBeginDrag: started dragging %s"),
                     GetItemText(m_draggedItem).c_str());*/

        event.Allow();
    }
    else
    {
        //wxLogMessage(wxT("OnBeginDrag: this item can't be dragged."));
    }
}

void BwxTreeCtrl::OnEndDrag(wxTreeEvent& event)
{
    wxTreeItemId itemSrc = m_draggedItem,
                 itemDst = event.GetItem();
    m_draggedItem = (wxTreeItemId)0l;

    // where to copy the item?
    if ( itemDst.IsOk() && !ItemHasChildren(itemDst) )
    {
        // copy to the parent then
        itemDst = GetItemParent(itemDst);
    }

    if ( !itemDst.IsOk() )
    {
        //wxLogMessage(wxT("OnEndDrag: can't drop here."));

        return;
    }

    wxString text = GetItemText(itemSrc);
    /*wxLogMessage(wxT("OnEndDrag: '%s' copied to '%s'."),
                 text.c_str(), GetItemText(itemDst).c_str());*/

    // just do append here - we could also insert it just before/after the item
    // on which it was dropped, but this requires slightly more work... we also
    // completely ignore the client data and icon of the old item but could
    // copy them as well.
    //
    // Finally, we only copy one item here but we might copy the entire tree if
    // we were dragging a folder.
    int image = wxGetApp().ShowImages() ? TreeCtrlIcon_File : -1;
    AppendItem(itemDst, text, image);
}

void BwxTreeCtrl::OnBeginLabelEdit(wxTreeEvent& event)
{
    //wxLogMessage(wxT("OnBeginLabelEdit"));

    // for testing, prevent this item's label editing
    wxTreeItemId itemId = event.GetItem();
    if ( IsTestItem(itemId) )
    {
        wxMessageBox(wxT("You can't edit this item."));

        event.Veto();
    }
    else if ( itemId == GetRootItem() )
    {
        // test that it is possible to change the text of the item being edited
        SetItemText(itemId, _T("Editing root item"));
    }
}

void BwxTreeCtrl::OnEndLabelEdit(wxTreeEvent& event)
{
    //wxLogMessage(wxT("OnEndLabelEdit"));

    // don't allow anything except letters in the labels
    if ( !event.GetLabel().IsWord() )
    {
        wxMessageBox(wxT("The new label should be a single word."));

        event.Veto();
    }
}

void BwxTreeCtrl::OnItemCollapsing(wxTreeEvent& event)
{
    //wxLogMessage(wxT("OnItemCollapsing"));

    // for testing, prevent the user from collapsing the first child folder
    wxTreeItemId itemId = event.GetItem();
    if ( IsTestItem(itemId) )
    {
        wxMessageBox(wxT("You can't collapse this item."));

        event.Veto();
    }
}

void BwxTreeCtrl::OnItemActivated(wxTreeEvent& event)
{
    // show some info about this item
    wxTreeItemId itemId = event.GetItem();
    BwxTreeItemData *item = (BwxTreeItemData *)GetItemData(itemId);

    if ( item )
    {
        item->ShowInfo(this);
    }

    //wxLogMessage(wxT("OnItemActivated"));
}

void BwxTreeCtrl::OnItemMenu(wxTreeEvent& event)
{
    wxTreeItemId itemId = event.GetItem();
    BwxTreeItemData *item = itemId.IsOk() ? (BwxTreeItemData *)GetItemData(itemId)
                                         : NULL;

    /*wxLogMessage(wxT("OnItemMenu for item \"%s\""), item ? item->GetDesc()
                                                         : _T(""));*/

    event.Skip();
}

void BwxTreeCtrl::OnContextMenu(wxContextMenuEvent& event)
{
    wxPoint pt = event.GetPosition();
    wxTreeItemId item;
    if ( !HasFlag(wxTR_MULTIPLE) )
        item = GetSelection();
    //wxLogMessage(wxT("OnContextMenu at screen coords (%i, %i)"), pt.x, pt.y);

    // check if event was generated by keyboard (MSW-specific?)
    if ( pt.x == -1 && pt.y == -1 ) //(this is how MSW indicates it)
    {
        // attempt to guess where to show the menu
        if ( item.IsOk() )
        {
            // if an item was clicked, show menu to the right of it
            wxRect rect;
            GetBoundingRect(item, rect, true /* only the label */);
            pt = wxPoint(rect.GetRight(), rect.GetTop());
        }
        else
        {
            pt = wxPoint(0, 0);
        }
    }
    else // event was generated by mouse, use supplied coords
    {
        pt = ScreenToClient(pt);
    }

    ShowMenu(item, pt);
}

void BwxTreeCtrl::ShowMenu(wxTreeItemId id, const wxPoint& pt)
{
    wxString title;
    if ( id.IsOk() )
    {
        title << wxT("Menu for ") << GetItemText(id);
    }
    else
    {
        title = wxT("Menu for no particular item");
    }
    wxMenu menu(title);
    menu.Append(ID_BwxTreeCtrl_About, wxT("&About..."));
    menu.Append(ID_BwxTreeCtrl_Dump, wxT("&Dump"));

    PopupMenu(&menu, pt);
}

void BwxTreeCtrl::OnItemRClick(wxTreeEvent& event)
{
    wxTreeItemId itemId = event.GetItem();
    BwxTreeItemData *item = itemId.IsOk() ? (BwxTreeItemData *)GetItemData(itemId)
                                         : NULL;

	//Edit(itemId) ;
    /*wxLogMessage(wxT("Item \"%s\" right clicked"), item ? item->GetDesc()
                                                        : _T(""));*/

    event.Skip();
}

void BwxTreeCtrl::OnRMouseDown(wxMouseEvent& event)
{
    //wxLogMessage(wxT("Right mouse button down"));

    event.Skip();
}

void BwxTreeCtrl::OnRMouseUp(wxMouseEvent& event)
{
    //wxLogMessage(wxT("Right mouse button up"));

    event.Skip();
}

void BwxTreeCtrl::OnRMouseDClick(wxMouseEvent& event)
{
    wxTreeItemId id = HitTest(event.GetPosition());
    if ( !id )
        wxLogMessage(wxT("No item under mouse"));
    else
    {
        BwxTreeItemData *item = (BwxTreeItemData *)GetItemData(id);
        /*if ( item )
            wxLogMessage(wxT("Item '%s' under mouse"), item->GetDesc());*/
    }

    event.Skip();
}

static inline const wxChar *Bool2String(bool b)
{
    return b ? wxT("") : wxT("not ");
}

void BwxTreeItemData::ShowInfo(wxTreeCtrl *tree)
{
    /*wxLogMessage(wxT("Item '%s': %sselected, %sexpanded, %sbold,\n")
                 wxT("%u children (%u immediately under this item)."),
                 m_desc.c_str(),
                 Bool2String(tree->IsSelected(GetId())),
                 Bool2String(tree->IsExpanded(GetId())),
                 Bool2String(tree->IsBold(GetId())),
                 tree->GetChildrenCount(GetId()),
                 tree->GetChildrenCount(GetId(), false));*/
}
///////////////
BEGIN_EVENT_TABLE(BwxTreeCtrl, wxTreeCtrl)
    EVT_TREE_BEGIN_DRAG(ID_BwxTreeCtrl, BwxTreeCtrl::OnBeginDrag)
    EVT_TREE_BEGIN_RDRAG(ID_BwxTreeCtrl, BwxTreeCtrl::OnBeginRDrag)
    EVT_TREE_END_DRAG(ID_BwxTreeCtrl, BwxTreeCtrl::OnEndDrag)
    EVT_TREE_BEGIN_LABEL_EDIT(ID_BwxTreeCtrl, BwxTreeCtrl::OnBeginLabelEdit)
    EVT_TREE_END_LABEL_EDIT(ID_BwxTreeCtrl, BwxTreeCtrl::OnEndLabelEdit)
    EVT_TREE_DELETE_ITEM(ID_BwxTreeCtrl, BwxTreeCtrl::OnDeleteItem)
#if 0       // there are so many of those that logging them causes flicker
    EVT_TREE_GET_INFO(ID_BwxTreeCtrl, BwxTreeCtrl::OnGetInfo)
#endif
    EVT_TREE_SET_INFO(ID_BwxTreeCtrl, BwxTreeCtrl::OnSetInfo)
    EVT_TREE_ITEM_EXPANDED(ID_BwxTreeCtrl, BwxTreeCtrl::OnItemExpanded)
    EVT_TREE_ITEM_EXPANDING(ID_BwxTreeCtrl, BwxTreeCtrl::OnItemExpanding)
    EVT_TREE_ITEM_COLLAPSED(ID_BwxTreeCtrl, BwxTreeCtrl::OnItemCollapsed)
    EVT_TREE_ITEM_COLLAPSING(ID_BwxTreeCtrl, BwxTreeCtrl::OnItemCollapsing)

    EVT_TREE_SEL_CHANGED(ID_BwxTreeCtrl, BwxTreeCtrl::OnSelChanged)
    EVT_TREE_SEL_CHANGING(ID_BwxTreeCtrl, BwxTreeCtrl::OnSelChanging)
    EVT_TREE_KEY_DOWN(ID_BwxTreeCtrl, BwxTreeCtrl::OnTreeKeyDown)
    EVT_TREE_ITEM_ACTIVATED(ID_BwxTreeCtrl, BwxTreeCtrl::OnItemActivated)

    // so many differents ways to handle right mouse button clicks...
    EVT_CONTEXT_MENU(BwxTreeCtrl::OnContextMenu)
    // EVT_TREE_ITEM_MENU is the preferred event for creating context menus
    // on a tree control, because it includes the point of the click or item,
    // meaning that no additional placement calculations are required.
    EVT_TREE_ITEM_MENU(ID_BwxTreeCtrl, BwxTreeCtrl::OnItemMenu)
    EVT_TREE_ITEM_RIGHT_CLICK(ID_BwxTreeCtrl, BwxTreeCtrl::OnItemRClick)

    EVT_RIGHT_DOWN(BwxTreeCtrl::OnRMouseDown)
    EVT_RIGHT_UP(BwxTreeCtrl::OnRMouseUp)
    EVT_RIGHT_DCLICK(BwxTreeCtrl::OnRMouseDClick)
END_EVENT_TABLE()

//////////////////////////////////////////////////////////////////////////
// This program is free software: you can redistribute it and/or modify //
// it under the terms of the GNU General Public License as published by //
// the Free Software Foundation, either version 3 of the License, or    //
// (at your option) any later version.                                  //
//                                                                      //
// This program is distributed in the hope that it will be useful,      //
// but WITHOUT ANY WARRANTY; without even the implied warranty of       //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        //
// GNU General Public License for more details.                         //
//////////////////////////////////////////////////////////////////////////

#include "Precompiled.h"

#include <wx/wx.h>

#include "FileTree.h"



enum FileTreeIds
{
	ID_ON_BEGIN_LABEL_EDIT = 6000,
	ID_ON_END_LABEL_EDIT,
	ID_ON_ITEM_ACTIVATED,
	ID_ON_ITEM_MENU
};


IMPLEMENT_DYNAMIC_CLASS(FileTree, wxTreeCtrl)


BEGIN_EVENT_TABLE(FileTree, wxTreeCtrl)
	EVT_MENU(ID_REMOVE_ITEM, FileTree::OnRemoveItem)
	EVT_MENU(ID_DELETE_ITEM, FileTree::OnDeleteItem)
	EVT_MENU(ID_RENAME_ITEM, FileTree::OnRename)


	EVT_TREE_BEGIN_DRAG(FileTree::StaticId, FileTree::OnBeginDrag)
	EVT_TREE_END_DRAG(FileTree::StaticId, FileTree::OnEndDrag)
	EVT_TREE_BEGIN_LABEL_EDIT(FileTree::StaticId, FileTree::OnBeginLabelEdit)
	EVT_TREE_END_LABEL_EDIT(FileTree::StaticId, FileTree::OnEndLabelEdit)
	//EVT_TREE_DELETE_ITEM(FileTree::StaticId, FileTree::OnDeleteItem)

	//EVT_TREE_SET_INFO(FileTree::StaticId, FileTree::OnSetInfo)
	//EVT_TREE_ITEM_EXPANDED(FileTree::StaticId, FileTree::OnItemExpanded)
	//EVT_TREE_ITEM_EXPANDING(FileTree::StaticId, FileTree::OnItemExpanding)
	//EVT_TREE_ITEM_COLLAPSED(FileTree::StaticId, FileTree::OnItemCollapsed)
	//EVT_TREE_ITEM_COLLAPSING(FileTree::StaticId, FileTree::OnItemCollapsing)

	EVT_TREE_SEL_CHANGED(FileTree::StaticId, FileTree::OnSelectionChanged)
	EVT_TREE_SEL_CHANGING(FileTree::StaticId, FileTree::OnSelectionChanging)
	//EVT_TREE_KEY_DOWN(FileTree::StaticId, FileTree::OnTreeKeyDown)
	EVT_TREE_ITEM_ACTIVATED(FileTree::StaticId, FileTree::OnItemActivated)

	EVT_TREE_ITEM_MENU(FileTree::StaticId, FileTree::OnItemMenu)
	//EVT_TREE_ITEM_RIGHT_CLICK(FileTree::StaticId, FileTree::OnItemRClick)

	//EVT_LEFT_DOWN(FileTree::OnLeftMouseDown)
	//EVT_RIGHT_UP(FileTree::OnRMouseUp)
	//EVT_RIGHT_DCLICK(FileTree::OnRMouseDClick)
END_EVENT_TABLE()




FileTree::FileTree(wxWindow *parent, const wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxTreeCtrl(parent, id, pos, size, style)
{

	wxTreeItemId root = AddRoot( _T("Root") );

	wxTreeItemId mapsRoot = AddNewChildItem( root, new TreeItemData( TreeItemData::TypeVirtualFolder, _T("Maps"), wxEmptyString, false, false ) );
	wxTreeItemId imagesRoot = AddNewChildItem( root, new TreeItemData( TreeItemData::TypeVirtualFolder, _T("Images"), wxEmptyString, false, false ) );
	wxTreeItemId tilesetRoot = AddNewChildItem( root, new TreeItemData( TreeItemData::TypeVirtualFolder, _T("Tilesets"), wxEmptyString, false, false ) );

	//test items
	AddNewChildItem( mapsRoot, new TreeItemData( TreeItemData::TypeMap, _T("item 1") ) );
	AddNewChildItem( mapsRoot, new TreeItemData( TreeItemData::TypeMap, _T("item 2") ) );

	AddNewChildItem( imagesRoot, new TreeItemData( TreeItemData::TypeImage, _T("item 1") ) );
	AddNewChildItem( imagesRoot, new TreeItemData( TreeItemData::TypeImage, _T("item 2") ) );

	AddNewChildItem( tilesetRoot, new TreeItemData( TreeItemData::TypeTileset, _T("item 1") ) );
	AddNewChildItem( tilesetRoot, new TreeItemData( TreeItemData::TypeTileset, _T("item 2") ) );

}


FileTree::~FileTree()
{
}


wxTreeItemId FileTree::AddNewChildItem( const wxTreeItemId &parent, TreeItemData* data, int image, int selImage )
{
	return AppendItem( parent, data->GetDisplayName(), image, selImage, data );
}


void FileTree::OnRename(wxCommandEvent& WXUNUSED(event))
{
	wxTreeItemId item = GetSelection();
	if( item.IsOk() )
	{
		EditLabel(item);
	}
}


void FileTree::OnRemoveItem(wxCommandEvent& WXUNUSED(event))
{
	wxTreeItemId item = GetSelection();
	if( item.IsOk() )
	{
		TreeItemData* data = (TreeItemData*)GetItemData(item);
		Delete(item);
	}
}


void FileTree::OnDeleteItem(wxCommandEvent& WXUNUSED(event))
{
	wxTreeItemId item = GetSelection();
	if( item.IsOk() )
	{
		TreeItemData* data = (TreeItemData*)GetItemData(item);
		Delete(item);
	}
}


void FileTree::OnItemMenu(wxTreeEvent& event)
{
	wxLogMessage(wxT("OnItemMenu"));
	wxTreeItemId item = event.GetItem();
	if( item.IsOk() )
	{
		TreeItemData* data = (TreeItemData*)GetItemData(item);
		wxPoint clientpt = event.GetPoint();
		wxPoint screenpt = ClientToScreen(clientpt);

		ShowMenu(item, clientpt);
	}

	event.Skip();
}


void FileTree::OnBeginLabelEdit(wxTreeEvent& event)
{
	wxLogMessage(wxT("OnBeginLabelEdit"));
	wxTreeItemId item = event.GetItem();
	TreeItemData* data = (TreeItemData*)GetItemData(item);

	if( !data->IsRenamable() || item == GetRootItem() )
	{
		//wxMessageBox(_T("This item cannot be renamed."));
		//event.Veto();
	}
}


void FileTree::OnEndLabelEdit(wxTreeEvent& event)
{
	wxLogMessage(wxT("OnEndLabelEdit"));
	if( !event.GetLabel().IsWord() )
	{
		event.Veto();
	}
	else
	{
		RenameFile( event.GetItem(), event.GetLabel() );
	}
}


void FileTree::OnItemActivated(wxTreeEvent& event)
{
	wxLogMessage(wxT("OnItemActivated"));
	wxTreeItemId item = event.GetItem();
	if( !item.IsOk() )
		return;

    TreeItemData* data = (TreeItemData*)GetItemData(item);
    if(!data)
		return;

	if( data->GetType() == TreeItemData::TypeVirtualFolder )
    {
		if( IsExpanded(item) )
		{
			Collapse(item);
		}
		else
		{
			Expand(item);
		}
    }
	else
	{
		OpenFile(item);
	}
}


void FileTree::OnSelectionChanging(wxTreeEvent& event)
{
	event.Skip();
}


void FileTree::OnSelectionChanged(wxTreeEvent& event)
{
	event.Skip();
}


void FileTree::OnBeginDrag(wxTreeEvent& event)
{
	wxLogMessage(wxT("OnBeginDrag"));
	event.Skip();
}


void FileTree::OnEndDrag(wxTreeEvent& event)
{
	wxLogMessage(wxT("OnEndDrag"));
	event.Skip();
}


void FileTree::ShowMenu( wxTreeItemId item, const wxPoint& pos )
{
	if( !item.IsOk() )
		return;

	TreeItemData* data = (TreeItemData*)GetItemData(item);
	if(!data)
		return;

	wxMenu menu; // data->GetDisplayName() );
	wxMenu* addMenu = new wxMenu();// _T("&Add") );

	TreeItemData::TreeItemDataType type = data->GetType();
	if( type == TreeItemData::TypeVirtualFolder )
	{
		addMenu->Append(ID_ADD_ITEM_NEW, _T("&New Item..."));
		addMenu->Append(ID_ADD_ITEM_EXISTING, _T("&Existing Item..."));
		addMenu->Append(ID_ADD_ITEM_FILTER, _T("&New Filter"));
		menu.AppendSubMenu(addMenu, _T("&Add"));
		menu.AppendSeparator();
	}
	if( data->IsRemovable() )
	{
		menu.Append(ID_REMOVE_ITEM, _T("&Remove"));
		menu.Append(ID_DELETE_ITEM, _T("&Delete"));
	}
	if( data->IsRenamable() )
	{
		menu.Append(ID_RENAME_ITEM, _T("&Rename"));
	}

	PopupMenu(&menu, pos);
}


void FileTree::RenameFile( const wxTreeItemId &item, const wxString &newName )
{
	TreeItemData* data = (TreeItemData*)this->GetItemData(item);
	data->SetDisplayName(newName);
	this->SetItemText(item, newName);
}


void FileTree::OpenFile( const wxTreeItemId &item )
{
	TreeItemData* data = (TreeItemData*)this->GetItemData(item);
	//TODO: load it or open it...
}


void FileTree::ToggleIcon( const wxTreeItemId& item )
{
	/*
    int image = (GetItemImage(item) == TreeCtrlIcon_Folder)
                    ? TreeCtrlIcon_File
                    : TreeCtrlIcon_Folder;
    SetItemImage(item, image, wxTreeItemIcon_Normal);

    image = (GetItemImage(item) == TreeCtrlIcon_FolderSelected)
                    ? TreeCtrlIcon_FileSelected
                    : TreeCtrlIcon_FolderSelected;
    SetItemImage(item, image, wxTreeItemIcon_Selected);
	*/
}








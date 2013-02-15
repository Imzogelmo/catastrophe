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

#pragma once

#include <wx/treectrl.h>



class TreeItemData : public wxTreeItemData
{
public:
	enum TreeItemDataType
	{
		TypeUnknown, //should always be known
		TypeVirtualFolder,
		TypeImage,
		TypeMap,
		TypeTileset
	};

	TreeItemData() : wxTreeItemData(), type(TypeUnknown), displayname(), fullpath() {}
	TreeItemData( TreeItemDataType itemType,
		const wxString &displayName,
		const wxString &fullPath = wxEmptyString,
		bool canRemove = true,
		bool isRenamable = true )
		:
		wxTreeItemData(),
		type(itemType),
		displayname(displayName), 
		fullpath(fullPath), 
		canremove(canRemove), 
		canrename(isRenamable)
	{}


	const wxString&		GetDisplayName() const { return displayname; }
	const wxString&		GetFullPath() const { return fullpath; }
	TreeItemDataType	GetType() const { return type; }
	bool				IsRemovable() const { return canremove; }
	bool				IsRenamable() const { return canrename; }

	void SetDisplayName( const wxString &displayName ) { displayname = displayName; }
	void SetFullPath( const wxString &file ) { fullpath = file; }
	void SetType( TreeItemDataType itemType ) { type = itemType; }

	bool DebugIsValidItem() const
	{
		return(
			type != TypeUnknown && !displayname.empty() &&
			( !fullpath.empty() || type == TypeVirtualFolder )
		);
	}

protected:
	TreeItemDataType	type;
	wxString			displayname;
	wxString			fullpath; //path + filename
	bool				canremove;
	bool				canrename;
};



class FileTree : public wxTreeCtrl
{
public:
	static const int StaticId = 1000; //todo: unique id

	FileTree() {}
	FileTree(wxWindow *parent, 
		const wxWindowID id = StaticId,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxTR_DEFAULT_STYLE | wxTR_HIDE_ROOT | wxTR_EDIT_LABELS | wxSUNKEN_BORDER
		);

	~FileTree();

protected:
	enum PopupMenuIds
	{
		ID_ADD_ITEM = 3000,
			ID_ADD_ITEM_NEW,
			ID_ADD_ITEM_EXISTING,
			ID_ADD_ITEM_FILTER,
		ID_OPEN_ITEM,
		ID_REMOVE_ITEM,
		ID_DELETE_ITEM,
		ID_RENAME_ITEM
	};

	//Menu events
	void OnRename(wxCommandEvent& event);
	void OnRemoveItem(wxCommandEvent& event);
	void OnDeleteItem(wxCommandEvent& event);


	//Tree events
	void OnItemMenu(wxTreeEvent& event);
	void OnBeginLabelEdit(wxTreeEvent& event);
	void OnEndLabelEdit(wxTreeEvent& event);
	void OnItemActivated(wxTreeEvent& event);
	void OnSelectionChanging(wxTreeEvent& event);
	void OnSelectionChanged(wxTreeEvent& event);
	void OnBeginDrag(wxTreeEvent& event);
	void OnEndDrag(wxTreeEvent& event);

	//Mouse events
	//void OnLeftMouseDown(wxMouseEvent& event);


	wxTreeItemId AddNewChildItem( const wxTreeItemId &parent, TreeItemData* data, int image = -1, int selImage = -1 );
	void ShowMenu( wxTreeItemId item, const wxPoint& pt );
	void RenameFile( const wxTreeItemId &item, const wxString &newName );
	void OpenFile( const wxTreeItemId &item );
	void ToggleIcon( const wxTreeItemId &item );


protected:
	wxTreeItemId		m_draggedItem;


	DECLARE_DYNAMIC_CLASS(FileTree);
	DECLARE_EVENT_TABLE();
};




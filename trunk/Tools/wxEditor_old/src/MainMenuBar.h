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

#include <wx/wx.h>


namespace MainMenu
{
	enum MenuIDs //TODO: Redo these properly once the menu stuff actually does something...
	{
		ID_FILE_NEW_PROJECT = 100,
		ID_FILE_OPEN_PROJECT,
		ID_FILE_SAVE_PROJECT,
		ID_FILE_SAVE_PROJECT_AS,
		ID_FILE_SAVE_ITEM,
		ID_FILE_SAVE_ALL,
		ID_FILE_PROPERTIES,
		ID_FILE_QUIT = wxID_EXIT,

		ID_EDIT_UNDO = 200,
		ID_EDIT_REDO,
		ID_EDIT_CUT,
		ID_EDIT_COPY,
		ID_EDIT_PASTE,

		ID_VIEW_FILES = 300,
		ID_VIEW_MAPS,
		ID_VIEW_TILESETS,
		ID_VIEW_LAYERS,
		ID_VIEW_SPRITES,
		ID_VIEW_MINIMAP,

		ID_MAP_NEW = 400,
		ID_MAP_RESIZE,
		ID_MAP_DELETE,
		ID_MAP_SAVE,
		ID_MAP_GENERATE_FROM_IMAGE,


		ID_AUDIO_LOAD = 500,

		ID_MAX
	};

} //namespace MainMenu





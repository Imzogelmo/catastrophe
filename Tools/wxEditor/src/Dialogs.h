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
#include <wx/dialog.h>
#include <wx/progdlg.h>

//#include "ResizeMapDialog.h"
//#include "NewMapDialog.h"
//#include "NewMapDialog.h"


class Dialog
{
public:
	static void ErrorDialog(const wxString &message, wxWindow* parent = 0);

	static bool LoadImageDialog(wxImage* image, wxString &outFilename, wxWindow* parent = 0);
	static bool SaveImageDialog(wxImage* image, wxString &outFilename, wxWindow* parent = 0);

	static bool LoadAudioDialog(wxString &outFilename, wxWindow* parent = 0);

};



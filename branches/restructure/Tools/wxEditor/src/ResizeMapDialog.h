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
#include <wx/spinctrl.h>

#include "Editor.h"


class ResizeMapDialog : public wxDialog 
{
public:
	ResizeMapDialog( wxWindow* parent,
			wxWindowID id = ID_NEW_MAP, 
			const wxString& title = wxT("Create New Map"), 
			const wxPoint& pos = wxDefaultPosition, 
			const wxSize& size = wxSize( 320, 320 ), 
			long style = wxDEFAULT_DIALOG_STYLE
			);

	virtual ~ResizeMapDialog();

protected:
	virtual void OnAccept( wxCommandEvent& event );
	virtual void OnCancel( wxCommandEvent& event );

	enum __DialogId
	{
		ID_NEW_MAP = 10000,
		ID_CANCEL,
		ID_ACCEPT
	};


	wxSpinCtrl* m_spinMapWidth;
	wxSpinCtrl* m_spinMapHeight;

	wxButton* m_buttonAccept;
	wxButton* m_buttonCancel;

};



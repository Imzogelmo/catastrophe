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

#include "ResizeMapDialog.h"
#include "MainEditorFrame.h"



ResizeMapDialog::ResizeMapDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style )
	: wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxString mapNameStr = Editor->GetActiveMap()->GetName().c_str();
	wxStaticText *mapName = new wxStaticText( this, wxID_ANY, mapNameStr, wxPoint(20,20), wxDefaultSize, 0 );


	wxStaticText *mapWidth = new wxStaticText( this, wxID_ANY, wxT("Map Width"), wxDefaultPosition, wxDefaultSize, 0 );
	mapWidth->Wrap( -1 );
	mapWidth->SetPosition( wxPoint(20, 80) );
	m_spinMapWidth = new wxSpinCtrl( this, wxID_ANY, wxT("32"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 2, 1024, 64 );
	m_spinMapWidth->SetPosition( wxPoint(80, 80) );


	wxStaticText *mapHeight = new wxStaticText( this, wxID_ANY, wxT("Map Height"), wxDefaultPosition, wxDefaultSize, 0 );
	mapHeight->Wrap( -1 );
	mapHeight->SetPosition( wxPoint(20, 100) );
	m_spinMapHeight = new wxSpinCtrl( this, wxID_ANY, wxT("32"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 2, 1024, 64 );
	m_spinMapHeight->SetPosition( wxPoint(80, 100) );


	m_buttonCancel = new wxButton( this, ID_CANCEL, wxT("Cancel"), wxPoint(20, 160), wxDefaultSize, 0 );
	m_buttonAccept = new wxButton( this, ID_ACCEPT, wxT("Resize"), wxPoint(120, 160), wxDefaultSize, 0 );
	m_buttonAccept->SetDefault(); 


	this->Centre( wxBOTH );
	this->SetSize( 0, 0, 240, 240 );
	

	m_buttonAccept->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ResizeMapDialog::OnAccept ), 0, this );
	m_buttonCancel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ResizeMapDialog::OnCancel ), 0, this );
}


ResizeMapDialog::~ResizeMapDialog()
{
	m_buttonAccept->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ResizeMapDialog::OnAccept ), 0, this );
	m_buttonCancel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ResizeMapDialog::OnCancel ), 0, this );
}



void ResizeMapDialog::OnAccept( wxCommandEvent& event )
{
	uint w = (uint)m_spinMapWidth->GetValue();
	uint h = (uint)m_spinMapHeight->GetValue();
	Editor->ResizeMap(w, h);

	this->Destroy();
}


void ResizeMapDialog::OnCancel( wxCommandEvent& event )
{
	this->Destroy();
}

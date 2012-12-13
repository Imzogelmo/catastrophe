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

#include "NewMapDialog.h"
#include "MainEditorFrame.h"



NewMapDialog::NewMapDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style )
	: wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	
	wxStaticText *mapName = new wxStaticText( this, wxID_ANY, wxT("Map Name"), wxPoint(20,20), wxDefaultSize, 0 );
	mapName->Wrap( -1 );
	mapName->SetPosition( wxPoint(20, 20) );
	m_textMapName = new wxTextCtrl( this, wxID_ANY, wxT("Untitled Map"), wxDefaultPosition, wxDefaultSize, 0 );
	m_textMapName->SetMaxLength( 32 ); 
	m_textMapName->SetPosition( wxPoint(80, 20) );


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
	m_buttonAccept = new wxButton( this, ID_ACCEPT, wxT("Create"), wxPoint(120, 160), wxDefaultSize, 0 );
	m_buttonAccept->SetDefault(); 


	this->Centre( wxBOTH );
	this->SetSize( 0, 0, 240, 240 );
	

	m_buttonAccept->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( NewMapDialog::OnAccept ), 0, this );
	m_buttonCancel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( NewMapDialog::OnCancel ), 0, this );
}


NewMapDialog::~NewMapDialog()
{
	m_buttonAccept->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( NewMapDialog::OnAccept ), 0, this );
	m_buttonCancel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( NewMapDialog::OnCancel ), 0, this );
}



void NewMapDialog::OnAccept( wxCommandEvent& event )
{
	wxString name = m_textMapName->GetValue();
	uint w = (uint)m_spinMapWidth->GetValue();
	uint h = (uint)m_spinMapHeight->GetValue();

	Editor->GetMainEditorFrame()->CreateNewMap( wxString(name.c_str()), w, h );

	this->Destroy();
}


void NewMapDialog::OnCancel( wxCommandEvent& event )
{
	this->Destroy();
}

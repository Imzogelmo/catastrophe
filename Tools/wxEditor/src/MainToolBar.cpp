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

#include "MainToolBar.h"
#include "MainEditorFrame.h"

#include "Icons.h"

#include <wx/sysopt.h>


void MainEditorFrame::InitializeToolBars()
{
	//For bitmap icons with more than 16 colors.
	wxSystemOptions::SetOption(wxT("msw.remap"), 0);

	m_toolBar = new wxToolBar(this, wxID_ANY, 
		wxDefaultPosition, wxDefaultSize, wxTB_FLAT | wxNO_BORDER | wxTB_NODIVIDER);//wxTB_NODIVIDER); //this->CreateToolBar();
	m_toolBar->SetMargins(5, 5);

	m_toolBar->AddTool(wxID_NEW, Icon::New, _T("New file")); 
	m_toolBar->AddTool(wxID_OPEN, Icon::Open, _T("Open file"));
	m_toolBar->AddTool(wxID_SAVE, Icon::Save, _T("Save file"));
	m_toolBar->AddSeparator();
	m_toolBar->AddTool(wxID_COPY, Icon::Copy, _T("Copy"));
	m_toolBar->AddTool(wxID_CUT, Icon::Cut, _T("Cut"));
//	m_toolBar->AddTool(wxID_PASTE, Icon::Paste), _T("Paste"));
	m_toolBar->AddSeparator();
	m_toolBar->AddTool(wxID_PRINT, Icon::Print, _T("Print"));
	m_toolBar->AddSeparator();
	m_toolBar->AddTool(wxID_HELP, Icon::Help, _T("Help"));

	m_toolBar->Realize();
	m_toolBar->EnableTool( wxID_PRINT, false );
	m_toolBar->EnableTool( wxID_HELP, false );


	m_auiManager.AddPane(m_toolBar,
		wxAuiPaneInfo().
		Name(_T("Pauff")).
		Caption(_T(" Stuff")).
		Show(true).
		ToolbarPane().
		Top().
		LeftDockable(false).
		RightDockable(false)
	);


	m_paintTools = new wxToolBar(this, wxID_ANY, 
		wxDefaultPosition, wxDefaultSize, wxTB_FLAT | wxNO_BORDER | wxTB_NODIVIDER);//, wxTB_FLAT);// | wxTB_NODIVIDER);
	//m_paintTools->SetMargins(5,5);
	//m_paintTools->SetMargins(1,1);

	m_paintTools->SetToolBitmapSize( wxSize(16, 16) );
	m_paintTools->AddTool( 567, wxString("Paint"), Icon::Pen, wxString(), wxITEM_RADIO );
	m_paintTools->AddTool( wxID_ANY, _T("Paint2"), Icon::Eraser, wxString(), wxITEM_RADIO );
	m_paintTools->AddTool( wxID_ANY, _T("Paint3"), Icon::Floodfill, wxString(), wxITEM_RADIO );
	m_paintTools->AddTool( wxID_ANY, _T("Paint4"), Icon::RectSelection, wxString(), wxITEM_RADIO );
	m_paintTools->AddTool( wxID_ANY, _T("Paint5"), Icon::ColorPicker, wxString(), wxITEM_RADIO );
	m_paintTools->AddTool( wxID_ANY, _T("Paint6"), Icon::Play, wxString(), wxITEM_RADIO );
	m_paintTools->Realize();

/*
	m_paintTools->AddTool( 567, wxString("Paint"), Icon::Pen, wxString(), wxITEM_RADIO );
	m_paintTools->AddTool( 587, _T("Paint2"), Icon::Eraser, wxString(), wxITEM_RADIO );
	m_paintTools->AddTool( 588, _T("Paint3"), Icon::Floodfill, wxString(), wxITEM_RADIO );
	m_paintTools->AddTool( 589, _T("Paint4"), Icon::RectSelection, wxString(), wxITEM_RADIO );
	m_paintTools->Realize();
*/

	m_paintTools->ToggleTool(567, true);

	m_auiManager.AddPane(m_paintTools,
		wxAuiPaneInfo().
		Name(_T("Paint Stuff")).
		Caption(_T("Paint Stuff")).
		Show(true).
		ToolbarPane().
		Top().
		LeftDockable(false).
		RightDockable(false)
		);


}



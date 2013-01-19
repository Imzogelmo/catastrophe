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

#include <cstdio>
#include <wx/wx.h>
#include <wx/log.h>
#include <wx/filefn.h>

#include "Application.h"
#include "MainEditorFrame.h"
#include "Editor.h"
#include "Directory.h"

IMPLEMENT_APP(Application);



bool Application::OnInit()
{
	if ( !wxApp::OnInit() )
		return false;

	InitLogging();
	InitImageHandlers();

	const wxString frameTitle = wxString("Map Editor");
	const wxPoint framePosition = wxDefaultPosition;
	const wxSize frameSize = wxSize(800, 600);

	m_frame = new MainEditorFrame(frameTitle, framePosition, frameSize);
	m_frame->Show(true);

	return true;
}


int Application::OnExit()
{
    return 0;
}


void Application::InitImageHandlers()
{
	wxImageHandler *jpegHandler = new wxJPEGHandler();
	wxImageHandler *pngHandler = new wxPNGHandler();
	wxImageHandler *pcxHandler = new wxPCXHandler();
	wxImageHandler *tgaHandler = new wxTGAHandler();
	wxImageHandler *gifHandler = new wxGIFHandler(); //load only

	wxImage::AddHandler(jpegHandler);
	wxImage::AddHandler(pngHandler);
	wxImage::AddHandler(pcxHandler);
	wxImage::AddHandler(tgaHandler);
	wxImage::AddHandler(gifHandler);
}


void Application::InitLogging()
{
	wxLog::SetLogLevel(wxLOG_Max);
	wxLog::SetVerbose(true);
	wxLog::SetRepetitionCounting(false); 

	wxLog* logStdOut = new wxLogStderr(stdout);
	wxLog::SetActiveTarget(logStdOut);

	FILE* f = fopen("editor.log", "w");
	if(f)
	{
		wxLogStderr* log = new wxLogStderr(f);
		wxLogChain* chain = new wxLogChain(log);
	}

	wxLogStatus(wxT("Logging Initialized"));
}


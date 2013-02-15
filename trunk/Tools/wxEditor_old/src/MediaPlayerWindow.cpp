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

#include "Icons.h"
#include "MediaPlayerWindow.h"
#include "Sound/FmodPlayer.h"


MediaPlayerWindow::MediaPlayerWindow( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : 
	wxPanel( parent, id, pos, size, style )
{
	const wxColour silver(200,200,200);
	const wxColour gold(10, 25, 105);
	const wxColour darkGray(78, 78, 78);

	this->SetBackgroundColour( silver );
	this->SetMinSize( wxSize( 240,88 ) );

	wxBoxSizer* paneSizer = new wxBoxSizer( wxVERTICAL );
	wxBoxSizer* textSizer = new wxBoxSizer( wxHORIZONTAL );
	
	m_songNameText = new wxStaticText( this, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, 0 );
	m_songNameText->Wrap( -1 );
	m_songNameText->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 90, false, wxEmptyString ) );
	m_songNameText->SetForegroundColour( gold );
	//m_songNameText->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BTNTEXT ) );

	textSizer->Add( m_songNameText, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxRIGHT|wxLEFT, 5 );
	textSizer->Add( 0, 0, 1, wxALIGN_CENTER_VERTICAL, 5 );

	m_songTimeText = new wxStaticText( this, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, 0 );
	m_songTimeText->Wrap( -1 );
	m_songTimeText->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 90, false, wxEmptyString ) );
	m_songTimeText->SetForegroundColour( gold );
	//m_songTimeText->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BTNTEXT ) );

	textSizer->Add( m_songTimeText, 0, wxRIGHT|wxLEFT|wxALIGN_CENTER_VERTICAL, 5 );
	paneSizer->Add( textSizer, 0, wxEXPAND|wxTOP|wxRIGHT|wxLEFT, 5 );

	wxBoxSizer* mediaButtonSizer;
	mediaButtonSizer = new wxBoxSizer( wxHORIZONTAL );

	m_seekBackButton = new wxBitmapButton( this, wxID_ANY, Icon::SkipBackward, wxDefaultPosition, wxSize( -1,16 ), wxBU_AUTODRAW );	
	m_seekBackButton->SetBackgroundColour( darkGray );
	mediaButtonSizer->Add( m_seekBackButton, 1, wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	m_skipBackButton = new wxBitmapButton( this, wxID_ANY, Icon::SeekBackward, wxDefaultPosition, wxSize( -1,16 ), wxBU_AUTODRAW );
	m_skipBackButton->SetBackgroundColour( darkGray );
	mediaButtonSizer->Add( m_skipBackButton, 1, wxTOP|wxBOTTOM, 5 );
	
	m_playButton = new wxBitmapButton( this, wxID_ANY, Icon::Play, wxDefaultPosition, wxSize( -1,16 ), wxBU_AUTODRAW );
	m_playButton->SetBackgroundColour( darkGray );
	mediaButtonSizer->Add( m_playButton, 1, wxTOP|wxBOTTOM, 5 );

	m_pauseButton = new wxBitmapButton( this, wxID_ANY, Icon::Pause, wxDefaultPosition, wxSize( -1,16 ), wxBU_AUTODRAW );
	m_pauseButton->SetBackgroundColour( darkGray );
	mediaButtonSizer->Add( m_pauseButton, 1, wxTOP|wxBOTTOM, 5 );

	m_stopButton = new wxBitmapButton( this, wxID_ANY, Icon::Stop, wxDefaultPosition, wxSize( -1,16 ), wxBU_AUTODRAW );
	m_stopButton->SetBackgroundColour( darkGray );
	mediaButtonSizer->Add( m_stopButton, 1, wxTOP|wxBOTTOM, 5 );

	m_skipForwardButton = new wxBitmapButton( this, wxID_ANY, Icon::SeekForward, wxDefaultPosition, wxSize( -1,16 ), wxBU_AUTODRAW );
	m_skipForwardButton->SetBackgroundColour( darkGray );
	mediaButtonSizer->Add( m_skipForwardButton, 1, wxTOP|wxBOTTOM, 5 );

	m_seekForwardButton = new wxBitmapButton( this, wxID_ANY, Icon::SkipForward, wxDefaultPosition, wxSize( -1,16 ), wxBU_AUTODRAW );
	m_seekForwardButton->SetBackgroundColour( darkGray );
	mediaButtonSizer->Add( m_seekForwardButton, 1, wxTOP|wxBOTTOM|wxRIGHT, 5 );

	paneSizer->Add( mediaButtonSizer, 1, wxALIGN_CENTER_HORIZONTAL|wxEXPAND|wxALL, 5 );

	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxHORIZONTAL );

	m_volumeSlider = new wxSlider( this, wxID_ANY, 50, 0, 100, wxDefaultPosition, wxSize( 80,-1 ), wxSL_HORIZONTAL );
	m_volumeSlider->SetMaxSize( wxSize( 80,-1 ) );
	//m_volumeSlider->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BTNTEXT ) );
	bSizer4->Add( m_volumeSlider, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );

	m_songTimeSlider = new wxSlider( this, wxID_ANY, 0, 0, 1024, wxDefaultPosition, wxSize( -1,-1 ), wxSL_HORIZONTAL );
	//m_songTimeSlider->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BTNTEXT ) );
	bSizer4->Add( m_songTimeSlider, 1, wxALIGN_CENTER_HORIZONTAL|wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );

	paneSizer->Add( bSizer4, 1, wxEXPAND, 5 );

	this->SetSizer( paneSizer );
	this->Layout();

	// Connect Events
	m_seekBackButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MediaPlayerWindow::OnSeekBackward ), NULL, this );
	m_skipBackButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MediaPlayerWindow::OnSkipBackward ), NULL, this );
	m_playButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MediaPlayerWindow::OnPlay ), NULL, this );
	m_pauseButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MediaPlayerWindow::OnPause ), NULL, this );
	m_stopButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MediaPlayerWindow::OnStop ), NULL, this );
	m_skipForwardButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MediaPlayerWindow::OnSkipForward ), NULL, this );
	m_seekForwardButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MediaPlayerWindow::OnSeekForward ), NULL, this );
	m_volumeSlider->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( MediaPlayerWindow::OnEndVolumeAdjust ), NULL, this );
	m_volumeSlider->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( MediaPlayerWindow::OnBeginVolumeAdjust ), NULL, this );
	m_songTimeSlider->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( MediaPlayerWindow::OnEndSeek ), NULL, this );
	m_songTimeSlider->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( MediaPlayerWindow::OnBeginSeek ), NULL, this );



	m_lastTimerUpdate = 0;
	m_volumeSliderDragged = false;
	m_songTimeSliderDragged = false;

	m_audioPlayer = new FmodPlayer();
	m_timer = new MediaPlayerTimer(this);
	m_timer->Start(500);
}


MediaPlayerWindow::~MediaPlayerWindow()
{
	delete m_audioPlayer;
	delete m_timer;

	// Disconnect Events
	m_seekBackButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MediaPlayerWindow::OnSeekBackward ), NULL, this );
	m_skipBackButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MediaPlayerWindow::OnSkipBackward ), NULL, this );
	m_playButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MediaPlayerWindow::OnPlay ), NULL, this );
	m_pauseButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MediaPlayerWindow::OnPause ), NULL, this );
	m_stopButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MediaPlayerWindow::OnStop ), NULL, this );
	m_skipForwardButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MediaPlayerWindow::OnSkipForward ), NULL, this );
	m_seekForwardButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MediaPlayerWindow::OnSeekForward ), NULL, this );
	m_volumeSlider->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( MediaPlayerWindow::OnEndVolumeAdjust ), NULL, this );
	m_volumeSlider->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( MediaPlayerWindow::OnBeginVolumeAdjust ), NULL, this );
	m_songTimeSlider->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( MediaPlayerWindow::OnEndSeek ), NULL, this );
	m_songTimeSlider->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( MediaPlayerWindow::OnBeginSeek ), NULL, this );
}


#define SEEK_MS 5000
void MediaPlayerWindow::Seek( int milliseconds )
{
	m_audioPlayer->SetPosition( m_audioPlayer->GetPosition() + milliseconds );
}


void MediaPlayerWindow::OnSeekBackward( wxCommandEvent& event )
{
	Seek( -SEEK_MS * 6 );
}


void MediaPlayerWindow::OnSkipBackward( wxCommandEvent& event )
{
	Seek( -SEEK_MS );
}


void MediaPlayerWindow::OnPlay( wxCommandEvent& event )
{
	if( !m_audioPlayer->IsPlaying() )
		m_audioPlayer->Play();

	else if( m_audioPlayer->IsPaused() )
		m_audioPlayer->Pause(false);

}


void MediaPlayerWindow::OnPause( wxCommandEvent& event )
{
	m_audioPlayer->Pause( !m_audioPlayer->IsPaused() );
}


void MediaPlayerWindow::OnStop( wxCommandEvent& event )
{
	m_songTimeSlider->SetValue(0);
	m_audioPlayer->Stop();
}


void MediaPlayerWindow::OnSkipForward( wxCommandEvent& event )
{
	Seek( SEEK_MS );
}


void MediaPlayerWindow::OnSeekForward( wxCommandEvent& event )
{
	Seek( SEEK_MS * 6 );
}


void MediaPlayerWindow::OnBeginVolumeAdjust( wxScrollEvent& event )
{
	m_volumeSliderDragged = true;
	NotifyTimerUpdate();
}


void MediaPlayerWindow::OnEndVolumeAdjust( wxScrollEvent& event )
{
	m_volumeSliderDragged = false;
	NotifyTimerUpdate();
}


void MediaPlayerWindow::OnBeginSeek( wxScrollEvent& event )
{
	m_songTimeSliderDragged = true;
	NotifyTimerUpdate();
}


void MediaPlayerWindow::OnEndSeek( wxScrollEvent& event )
{
	m_songTimeSliderDragged = false;
	NotifyTimerUpdate();
}


void MediaPlayerWindow::Load( const wxString& file )
{
	m_audioPlayer->Load( file.c_str() );

	wxFileName fn(file);
	m_songNameText->SetLabel( fn.GetName() );
}


void MediaPlayerWindow::NotifyTimerUpdate()
{
	UpdateMediaPlayer();

	wxString str;
	int length = m_audioPlayer->GetLength();
	int pos = m_audioPlayer->GetPosition();

	str.Printf( _T("%2i:%02i / %2i:%02i"), 
		pos / 60000, (pos % 60000) / 1000,
		length / 60000, (length % 60000) / 1000 
		);

	m_songTimeText->SetLabel(str);


	if( m_songTimeSliderDragged )
	{
		int sliderPos = (int)(((float)m_songTimeSlider->GetValue() / 1024.0f) * (float)length);
		m_audioPlayer->SetPosition( sliderPos );
	}
	else
	{
		int sliderPos = (int)(((float)pos / (float)length) * 1024.0f);
		m_songTimeSlider->SetValue( length > 0 ?
			(sliderPos > 1024 ? 1024 : sliderPos) :
			0 
		);
	}

	if( m_volumeSliderDragged )
	{
		m_audioPlayer->SetVolume( (float)m_volumeSlider->GetValue() / 100.f );
	}
}


void MediaPlayerWindow::UpdateMediaPlayer()
{
	/*
	if( m_timer->IsRunning() )
	{
		m_lastTimerUpdate += m_timer->GetInterval();
		if( m_lastTimerUpdate > 16 )
		{
			m_audioPlayer->Update();
			m_lastTimerUpdate = 0;
		}
	}
*/
	m_audioPlayer->Update();
}


void MediaPlayerTimer::Notify()
{
	m_parent->NotifyTimerUpdate();
}




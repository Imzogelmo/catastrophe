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


class AudioPlayer;
class MediaPlayerTimer;

class MediaPlayerWindow :  public wxPanel 
{
public:
	MediaPlayerWindow( wxWindow* parent, 
		wxWindowID id = wxID_ANY, 
		const wxPoint& pos = wxDefaultPosition, 
		const wxSize& size = wxSize( 256,92 ), 
		long style = wxCLIP_CHILDREN|wxFULL_REPAINT_ON_RESIZE|wxNO_BORDER 
		);
	~MediaPlayerWindow();

	void Load( const wxString& file );

protected:
	void OnSeekBackward( wxCommandEvent& event );
	void OnSkipBackward( wxCommandEvent& event );
	void OnPlay( wxCommandEvent& event );
	void OnPause( wxCommandEvent& event );
	void OnStop( wxCommandEvent& event );
	void OnSkipForward( wxCommandEvent& event );
	void OnSeekForward( wxCommandEvent& event );
	void OnEndVolumeAdjust( wxScrollEvent& event );
	void OnBeginVolumeAdjust( wxScrollEvent& event );
	void OnEndSeek( wxScrollEvent& event );
	void OnBeginSeek( wxScrollEvent& event );

	void Seek( int milliseconds );
	void NotifyTimerUpdate();
	void UpdateMediaPlayer();


protected:
	wxStaticText* m_songNameText;
	wxStaticText* m_songTimeText;
	wxBitmapButton* m_seekBackButton;
	wxBitmapButton* m_skipBackButton;
	wxBitmapButton* m_playButton;
	wxBitmapButton* m_pauseButton;
	wxBitmapButton* m_stopButton;
	wxBitmapButton* m_skipForwardButton;
	wxBitmapButton* m_seekForwardButton;
	wxSlider* m_volumeSlider;
	wxSlider* m_songTimeSlider;


	AudioPlayer*		m_audioPlayer;
	MediaPlayerTimer*	m_timer;

	int	m_lastTimerUpdate;
	bool m_volumeSliderDragged;
	bool m_songTimeSliderDragged;

	friend class MediaPlayerTimer;
};



class MediaPlayerTimer : public wxTimer
{
public:
	MediaPlayerTimer(MediaPlayerWindow* parent) { m_parent = parent; }

protected:
	void Notify();

	MediaPlayerWindow* m_parent;
};


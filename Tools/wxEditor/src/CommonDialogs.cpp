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


#include "Dialogs.h"




void Dialog::ErrorDialog(const wxString &message, wxWindow* parent)
	{
		wxMessageDialog errorMessage( parent, 
				message,
				_T("Error"),
				wxOK
			);

			errorMessage.ShowModal();
	}


bool Dialog::LoadImageDialog(wxImage* image, wxString &outFilename, wxWindow* parent)
	{
		bool retSuccess = true;

		wxString filename = wxFileSelector(wxT("Select image to load"),
			wxT(""),
			wxT(""),
			wxT(""),
			wxT("Image Files(*.bmp;*.png;*.tga;*.pcx;*.jpeg;*.gif)|*.bmp;*.png;*.tga;*.pcx;*.jpeg;*.gif|All files (*.*)|*.*"),
			wxFD_OPEN,
			parent
		);

		outFilename = filename;
		if( filename.IsEmpty() )
			return false;

		if(!image)
			throw("Null image error");

		image->LoadFile(filename);

		if( !image->Ok() )
		{
			wxMessageDialog errorMessage( parent, 
				_T("Error loading " + filename),
				_T("Zuul"),
				wxOK
			);

			errorMessage.ShowModal();
			retSuccess = false;
		}


		return retSuccess;
	}


bool Dialog::SaveImageDialog(wxImage* image, wxString &outFilename, wxWindow* parent)
	{
		bool retSuccess = true;

		wxString filename = wxFileSelector( wxT("Save Image"),
				wxEmptyString,
				wxEmptyString,
				(const wxChar *)NULL,
				wxT("png files (*.png)|*.png|")
				wxT("bmp files (*.bmp)|*.bmp|")
				wxT("jpeg files (*.jpg)|*.jpg|")
				wxT("pcx files (*.pcx)|*.pcx"),
				wxFD_SAVE,
				parent
			);

		outFilename = filename;
		if( filename.empty() )
			return false;

		if( !image->SaveFile(filename) )
		{
			wxMessageDialog errorMessage( parent, 
					_T("Error saving " + filename),
					_T("Gozer"),
					wxOK
				);

			errorMessage.ShowModal();
			retSuccess = false;
		}

		return retSuccess;
	}




bool Dialog::LoadAudioDialog(wxString &outFilename, wxWindow* parent)
{
	bool retSuccess = true;

	wxString filename = wxFileSelector(wxT("Select Audio File"),
		wxT(""),
		wxT(""),
		wxT(""),
		wxT("Audio Files(*.aiff;*.asf;*.asx;*.dls;*.flac;*.fsb;*.it;*.m3u;*.mid;*.midi;*.mod;*.mp2;*.mp3;*.ogg;*.pls;*.raw;*.s3m;*.vag;*.wav;*.wax;*.wma;*.xm)|" \
			"*.aiff;*.asf;*.asx;*.dls;*.flac;*.fsb;*.it;*.m3u;*.mid;*.midi;*.mod;*.mp2;*.mp3;*.ogg;*.pls;*.raw;*.s3m;*.vag;*.wav;*.wax;*.wma;*.xm|All files (*.*)|*.*"),
		wxFD_OPEN,
		parent
	);

	outFilename = filename;
	if( filename.IsEmpty() )
		return false;

	return retSuccess;
}




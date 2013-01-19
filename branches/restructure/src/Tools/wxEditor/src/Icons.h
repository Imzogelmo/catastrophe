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

#include <wx/bitmap.h>


namespace Icon
{
#define ICON(decl) \
	extern wxBitmap decl

	//general
	ICON( New );
	ICON( Open );
	ICON( Save );
	ICON( Copy );
	ICON( Cut );
	ICON( Print );
	ICON( Preview );
	ICON( Help );
	ICON( Cancel );

	ICON( Quake3 );

	//paint
	ICON( Pen );
	ICON( Floodfill );
	ICON( Eraser );
	ICON( ColorPicker );
	ICON( RectSelection );

	//media
	ICON( Play );
	ICON( Pause );
	ICON( Stop );
	ICON( SkipForward );
	ICON( SeekForward );
	ICON( SkipBackward );
	ICON( SeekBackward );

#undef ICON
};



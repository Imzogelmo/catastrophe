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


//general use
#include "../icons/new.xpm"
#include "../icons/open.xpm"
#include "../icons/save.xpm"
#include "../icons/copy.xpm"
#include "../icons/cut.xpm"
#include "../icons/print.xpm"
#include "../icons/preview.xpm"
#include "../icons/help.xpm"
#include "../icons/cancel.xpm"


#include "../icons/layers_new.xpm"
#include "../icons/layers_up.xpm"
#include "../icons/layers_down.xpm"
#include "../icons/layers_delete.xpm"
#include "../icons/layers_eye.xpm"


//paint tools
#include "../icons/quake_3.xpm"
#include "../icons/pen.xpm"
#include "../icons/floodfill.xpm"
#include "../icons/eraser.xpm"
#include "../icons/colorpicker.xpm"
#include "../icons/rectselection.xpm"


//audio tools
#include "../icons/play.xpm"
#include "../icons/pause.xpm"
#include "../icons/stop.xpm"
#include "../icons/skipforward.xpm"
#include "../icons/seekforward.xpm"
#include "../icons/skipbackward.xpm"
#include "../icons/seekbackward.xpm"


namespace Icon
{

#define CREATE_ICON(decl,xpm) \
	wxBitmap decl(xpm)

	//general
	CREATE_ICON( New, new_xpm );
	CREATE_ICON( Open, open_xpm );
	CREATE_ICON( Save, save_xpm );
	CREATE_ICON( Copy, copy_xpm );
	CREATE_ICON( Cut, cut_xpm );
	CREATE_ICON( Print, print_xpm );
	CREATE_ICON( Preview, preview_xpm );
	CREATE_ICON( Help, help_xpm );
	CREATE_ICON( Cancel, cancel_xpm );

	CREATE_ICON( Quake3, quake_3_xpm );

	//paint
	CREATE_ICON( Pen, pen_xpm );
	CREATE_ICON( Floodfill, floodfill_xpm );
	CREATE_ICON( Eraser, eraser_xpm );
	CREATE_ICON( ColorPicker, colorpicker_xpm );
	CREATE_ICON( RectSelection, rectselection_xpm );

	//media
	CREATE_ICON( Play, play_xpm );
	CREATE_ICON( Pause, pause_xpm );
	CREATE_ICON( Stop, stop_xpm );
	CREATE_ICON( SkipForward, skipforward_xpm );
	CREATE_ICON( SeekForward, seekforward_xpm );
	CREATE_ICON( SkipBackward, skipbackward_xpm );
	CREATE_ICON( SeekBackward, seekbackward_xpm );

#undef CREATE_ICON

};


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

#include <wx/gdicmn.h>
#include "Forward.h"


class Mouse
{
public:
	wxPoint pos;		// current mouse position
	wxPoint previous;	// last mouse position
	wxPoint clicked;	// mouse position when left click button was pressed

	bool left;	//probably should fix these booleans. hmm...
	bool right;
	bool middle;
	bool inWindow;		// whether or not the cursor is inside the target window


	Mouse() : pos(), previous(), clicked(), left(0), right(0), middle(0), inWindow(false)
	{}


	wxRect GetHighlightedRect() const;
	Vector2 GetPositionVector() const
	{
		return Vector2( float(pos.x), float(pos.y) );
	}

	Vector2 GetDirectionVector() const
	{
		wxPoint dir = pos - previous;

		return Vector2( float(dir.x), float(dir.y) );
	}

};




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



#include "Mouse.h"



wxRect Mouse::GetHighlightedRect() const
	{
		wxRect rect(pos, wxSize());
		//if(left)
		{
			wxPoint s = pos - clicked;
			wxPoint a(clicked);
			wxSize b(s.x, s.y);

			//if( b.x < a.x ) std::swap( a.x, b.x );
			//if( b.y < a.y ) std::swap( a.y, b.y );

			rect = wxRect(a, b);
		}

		return rect;
	}



// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.


#include "Math/PackedPoint.h"
#include "Math/PackedRect.h"
#include "Math/Point.h"
#include "Math/Rect.h"
#include "Math/Vector2.h"
#include "Math/Rectf.h"

CE_NAMESPACE_BEGIN


PackedPoint	PackedPoint::Zero	= PackedPoint(0, 0);
Point		Point::Zero			= Point(0, 0);

PackedRect	PackedRect::Zero	= PackedRect(0, 0, 0, 0);
Rect		Rect::Zero			= Rect(0, 0, 0, 0);


Point::Point( const Vector2& v ) :
	x((int)v.x), y((int)v.y)
{
}


Rect::Rect( const Rectf& r )
{
	pos.x = (int)r.min.x;
	pos.y = (int)r.min.y;
	size.x = (int)(r.Width());
	size.y = (int)(r.Height());
}


void Rect::Merge( const Rect& r )
{
	if(r.pos.x < pos.x) pos.x = r.pos.x;
	if(r.pos.y < pos.y) pos.y = r.pos.y;

	int xoff = r.Right() - Right();
	int yoff = r.Bottom() - Bottom();
	if( xoff > 0 ) size.x += xoff;
	if( yoff > 0 ) size.y += xoff;

}


Rectf Rect::ToRectf() const
{
	return Rectf( (float)pos.x, (float)pos.y, (float)(pos.x + size.x), (float)(pos.y + size.y) );
}



CE_NAMESPACE_END


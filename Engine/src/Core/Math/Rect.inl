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


#include "Catastrophe/Core/Math/Packed/PackedPoint.h"
#include "Catastrophe/Core/Math/Packed/PackedRect.h"
#include "Catastrophe/Core/Math/Point.h"
#include "Catastrophe/Core/Math/Rect.h"
#include "Catastrophe/Core/Math/Vector2.h"
#include "Catastrophe/Core/Math/Rectf.h"

CE_NAMESPACE_BEGIN

Point Point::Zero = Point(0, 0);
Rect Rect::Zero = Rect(0, 0, 0, 0);
Rect Rect::One = Rect(0, 0, 1, 1);


Point::Point( const Vector2& v ) :
	x((int)v.x), y((int)v.y)
{
}


Rect::Rect( const PackedRect& r )
{
	position.x = (int)r.position.x;
	position.y = (int)r.position.y;
	size.x = (int)r.Width();
	size.y = (int)r.Height();
}


Rect::Rect( const Rectf& r )
{
	position.x = Math::Round(r.min.x);
	position.y = Math::Round(r.min.y);
	size.x = Math::Round(r.Width());
	size.y = Math::Round(r.Height());
}


void Rect::Merge( const Rect& r )
{
	if(r.position.x < position.x) position.x = r.position.x;
	if(r.position.y < position.y) position.y = r.position.y;

	int xoff = r.Right() - Right();
	int yoff = r.Bottom() - Bottom();
	if( xoff > 0 ) size.x += xoff;
	if( yoff > 0 ) size.y += xoff;

}


Rectf Rect::ToRectf() const
{
	return Rectf( (float)position.x, (float)position.y, (float)(position.x + size.x), (float)(position.y + size.y) );
}



CE_NAMESPACE_END


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

Rect Rect::Zero = Rect(0, 0, 0, 0);
Rect Rect::One = Rect(0, 0, 1, 1);


Rect::Rect( const PackedRect& value )
{
	position.x = (int)value.position.x;
	position.y = (int)value.position.y;
	size.x = (int)value.Width();
	size.y = (int)value.Height();
}


Rect::Rect( const Rectf& value )
{
	position.x = Math::Round(value.min.x);
	position.y = Math::Round(value.min.y);
	size.x = Math::Round(value.Width());
	size.y = Math::Round(value.Height());
}


void Rect::Merge( const Rect& rect )
{
	if(rect.position.x < position.x) position.x = rect.position.x;
	if(rect.position.y < position.y) position.y = rect.position.y;

	int xoff = rect.Right() - Right();
	int yoff = rect.Bottom() - Bottom();
	if( xoff > 0 ) size.x += xoff;
	if( yoff > 0 ) size.y += xoff;

}



CE_NAMESPACE_END


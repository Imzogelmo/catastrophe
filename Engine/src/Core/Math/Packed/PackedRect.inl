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

#include "Catastrophe/Core/Math/Packed/PackedRect.h"
#include "Catastrophe/Core/Math/Rect.h"


CE_NAMESPACE_BEGIN

PackedRect PackedRect::Zero = PackedRect(0, 0, 0, 0);
PackedRect PackedRect::One = PackedRect(0, 0, 1, 1);


PackedRect::PackedRect( const Rect& rect )
{
	x = (s16)rect.x;
	y = (s16)rect.y;
	width = (s16)rect.width;
	height = (s16)rect.height;
}


PackedRect::PackedRect( const Rectf& value )
{
	x = (s16)Math::Round(value.min.x);
	y = (s16)Math::Round(value.min.y);
	width = (s16)Math::Round(value.Width());
	height = (s16)Math::Round(value.Height());
}


PackedRect& PackedRect::operator =( const Rect &rect )
{
	*this = PackedRect(rect);
	return *this;
}


PackedRect& PackedRect::operator =( const Rectf &rectf )
{
	*this = PackedRect(rectf);
	return *this;
}




CE_NAMESPACE_END


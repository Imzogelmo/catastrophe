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

#include "Math/Rectf.h"


CE_NAMESPACE_BEGIN

Rectf Rectf::Zero = Rectf(0.f, 0.f, 0.f, 0.f);
Rectf Rectf::One = Rectf(0.f, 0.f, 1.f, 1.f);


bool Rectf::IntersectsCircle( const Vector2& point, float radius )
{
	const float rx = Width() * 0.5f;
	const float ry = Height() * 0.5f;
	const float dx = fabsf(point.x - ((min.x + max.x) * 0.5f) + rx);
	const float dy = fabsf(point.y - ((min.x + max.x) * 0.5f) + ry);

	if( dx > (rx + radius) || dy > (ry + radius) )
		return false;

	if( dx <= rx || dy <= ry )
		return true;

	//special case for collision against corner
	const float ox = dx - rx;
	const float oy = dy - ry;
	const float distanceSquared = ox * ox + oy * oy;

	return (distanceSquared <= radius * radius);
}




CE_NAMESPACE_END


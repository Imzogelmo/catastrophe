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

#include "Math/BoundingBox.h"
#include "Math/Frustum.h"


CE_NAMESPACE_BEGIN

BoundingBox BoundingBox::Zero = BoundingBox(0.f, 0.f, 0.f, 0.f, 0.f, 0.f);
BoundingBox BoundingBox::One = BoundingBox(0.f, 0.f, 0.f, 1.f, 1.f, 1.f);



Vector3 BoundingBox::Center() const
{
	return Vector3( 
		(min.x + max.x) * 0.5f,
		(min.y + max.y) * 0.5f,
		(min.z + max.z) * 0.5f
		);
}


void BoundingBox::Merge( const BoundingBox& r )
{
	if(r.min.x < min.x) min.x = r.min.x;
	if(r.max.x > max.x) max.x = r.max.x;
	if(r.min.y < min.y) min.y = r.min.y;
	if(r.max.y > max.y) max.y = r.max.y;
	if(r.min.z < min.z) min.z = r.min.z;
	if(r.max.z > max.z) max.z = r.max.z;
}


void BoundingBox::Merge( const Vector3& p )
{
	if(p.x < min.x) min.x = p.x;
	if(p.x > max.x) max.x = p.x;
	if(p.y < min.y) min.y = p.y;
	if(p.y > max.y) max.y = p.y;
	if(p.z < min.z) min.z = p.z;
	if(p.z > max.z) max.z = p.z;
}


BoundingBox BoundingBox::CreateFromFrustum( const Frustum& f )
{
	return f.GetBoundingBox();
}


CE_NAMESPACE_END


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

#include "Math/Vector3.h"
#include "Math/Matrix.h"
#include "Math/Plane.h"
#include "Math/BoundingBox.h"
#include "Math/Frustum.h"

CE_NAMESPACE_BEGIN


Frustum::Frustum( const Matrix& view )
{
	Define(view);
}


bool Frustum::Equals( const Frustum &f, float epsilon ) const
{
	for( int i(0); i < MAX_PLANES; ++i )
		if( !planes[i].Equals(f.planes[i], epsilon) )
			return false;
	return true;
}


float Frustum::Distance( const Vector3& point ) const
{
	float distance = 0.f;
	for( int i(0); i < MAX_PLANES; ++i)
		distance = Math::Min(planes[i].Distance(point), distance);

	return distance;
}


bool Frustum::Intersects( const BoundingBox& box ) const
{
	const Vector3 center = box.Center();
	const Vector3 extent = box.Extents();

	for( int i(0); i < MAX_PLANES; ++i )
	{
		if( planes[i].normal.Dot(center) - planes[i].d < -planes[i].AbsNormal().Dot(extent) )
			return false;
	}

	return true;
}


bool Frustum::Intersects(const Sphere& sphere) const
{
	for( int i(0); i < MAX_PLANES; ++i )
	{
		if( planes[i].Distance(sphere.pos) < -sphere.radius)
			return false;
	}
	
	return true;
}


void Frustum::NormalizePlanes()
{
	for( int i(0); i < MAX_PLANES; ++i )
		planes[i].Normalize();
}


void Frustum::Define( const Matrix& view )
{
	//fixme:...
	const float* m = &view.m[0];

	planes[PLANE_RIGHT].normal.x = m[ 3] - m[ 0];
	planes[PLANE_RIGHT].normal.y = m[ 7] - m[ 4];
	planes[PLANE_RIGHT].normal.z = m[11] - m[ 8];
	planes[PLANE_RIGHT].d = m[15] - m[12];

	planes[PLANE_LEFT].normal.x = m[ 3] + m[ 0];
	planes[PLANE_LEFT].normal.y = m[ 7] + m[ 4];
	planes[PLANE_LEFT].normal.z = m[11] + m[ 8];
	planes[PLANE_LEFT].d = m[15] + m[12]; 		

	planes[PLANE_TOP].normal.x = m[ 3] - m[ 1];
	planes[PLANE_TOP].normal.y = m[ 7] - m[ 5];
	planes[PLANE_TOP].normal.z = m[11] - m[ 9];
	planes[PLANE_TOP].d = m[15] - m[13];

	planes[PLANE_BOTTOM].normal.x = m[ 3] + m[ 1];
	planes[PLANE_BOTTOM].normal.y = m[ 7] + m[ 5];
	planes[PLANE_BOTTOM].normal.z = m[11] + m[ 9];
	planes[PLANE_BOTTOM].d = m[15] + m[13]; 

	planes[PLANE_FAR].normal.x = m[ 3] - m[ 2];
	planes[PLANE_FAR].normal.y = m[ 7] - m[ 6];
	planes[PLANE_FAR].normal.z = m[11] - m[10];
	planes[PLANE_FAR].d	= m[15] - m[14];

	planes[PLANE_NEAR].normal.x = m[ 3] + m[ 2];
	planes[PLANE_NEAR].normal.y = m[ 7] + m[ 6];
	planes[PLANE_NEAR].normal.z = m[11] + m[10];
	planes[PLANE_NEAR].d = m[15] + m[14]; 

	NormalizePlanes();
}



CE_NAMESPACE_END


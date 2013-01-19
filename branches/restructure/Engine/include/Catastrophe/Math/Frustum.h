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

#pragma once

#include "Common.h"
#include "Vector3.h"
#include "BoundingBox.h"
#include "Sphere.h"
#include "Plane.h"
#include "Ray.h"
#include "Rectf.h"
#include "Matrix.h"

#ifdef _MSC_VER
	#pragma warning ( push )
	#pragma warning ( disable : 4201 ) //nameless struct/union
#endif

CE_NAMESPACE_BEGIN


class CE_API Frustum
{
public:
	enum FrustumPlane
	{
		PLANE_LEFT,
		PLANE_RIGHT,
		PLANE_TOP,
		PLANE_BOTTOM,
		PLANE_NEAR,
		PLANE_FAR,
		MAX_PLANES
	};

	union {
		struct {
			Plane left;
			Plane right;
			Plane top;
			Plane bottom;
			Plane front;
			Plane back;
		};
		struct { Plane planes[MAX_PLANES]; };
	};

	Frustum() {}
	Frustum( const Matrix& view );

	bool Equals( const Frustum &f, float epsilon = Math::Epsilon ) const;

	float Distance( const Vector3& point ) const;
	bool Intersects( const BoundingBox& box ) const;
	bool Intersects(const Sphere& sphere) const;

	void NormalizePlanes();
	void Define( const Matrix& view );

	BoundingBox GetBoundingBox() const
	{
		BoundingBox box = BoundingBox::Zero; //todo
		return box;
	}

};


CE_NAMESPACE_END

#ifdef _MSC_VER
	#pragma warning ( pop )
#endif


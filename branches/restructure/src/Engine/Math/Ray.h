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

CE_NAMESPACE_BEGIN


class CE_API Ray
{
public:
	Vector3 pos;
	Vector3 dir;

	Ray() {}
	Ray( const Vector3& pos, const Vector3& dir ) : pos(pos), dir(dir) {}

	bool operator == ( const Ray &r ) const { return pos == r.pos && dir == r.dir; }
	bool operator != ( const Ray &r ) const { return !(*this == r); }
	bool Equals( const Ray &r, float epsilon = Math::Epsilon ) const
	{
		return (pos.Equals(r.pos, epsilon) && dir.Equals(r.dir, epsilon));
	}


};


CE_NAMESPACE_END


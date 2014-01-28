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

#include <fc/type_traits.h>

#include "../Common.h"
#include "../Math/Vector2.h"
#include "../Math/Vector3.h"
#include "../Math/Color.h"
#include "../Math/Math.h"

CE_NAMESPACE_BEGIN


struct VertexColor
{
	VertexColor() {}
	VertexColor( const Vector2 &pos, const Color &color)
		: pos(pos), color(color) {}

	Vector2 pos;
	Color color;

	static VertexColor Lerp( const VertexColor &a, const VertexColor &b, float t )
	{
		return VertexColor(
			Math::Lerp(a.pos, a.pos, t),
			Color::Lerp(a.color, b.color, t)
		);
	}
};


struct VertexColorTexture
{
	VertexColorTexture() {}
	VertexColorTexture( const Vector2 &pos, const Vector2 &uv, const Color &color)	
		: pos(pos), uv(uv), color(color) {}

	Vector2 pos, uv;
	Color color;

	static VertexColorTexture Lerp( const VertexColorTexture &a, const VertexColorTexture &b, float t )
	{
		return VertexColorTexture(
			Math::Lerp(a.pos, a.pos, t),
			Math::Lerp(a.uv, b.uv, t),
			Color::Lerp(a.color, b.color, t)
		);
	}
};


struct Vertex3D
{
	Vector3 pos;
	Vector3 normal;
	Vector2 uv;
	Color color;

	Vertex3D() {}
	Vertex3D( const Vector3 &pos, const Vector3 &normal, const Vector2 &uv, const Color &color)
		: pos(pos), normal(normal), uv(uv), color(color) {}

	static Vertex3D Lerp( const Vertex3D &a, const Vertex3D &b, float t )
	{
		return Vertex3D(
			Math::Lerp(a.pos, a.pos, t),
			Math::Lerp(a.normal, b.normal, t),
			Math::Lerp(a.uv, b.uv, t),
			Color::Lerp(a.color, b.color, t)
		);
	}
};


CE_NAMESPACE_END



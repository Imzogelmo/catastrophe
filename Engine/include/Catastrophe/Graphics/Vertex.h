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

#include "Catastrophe/Core/Common.h"
#include "Catastrophe/Core/Math/Vector2.h"
#include "Catastrophe/Core/Math/Vector3.h"
#include "Catastrophe/Core/Math/Color.h"
#include "Catastrophe/Core/PlatformMath.h"

#include "Catastrophe/Graphics/Common.h"

CE_NAMESPACE_BEGIN


enum VertexType
{
	VertexFormat_Byte = 1520,
	VertexFormat_UnsignedByte = 1521,
	VertexFormat_Short = 1522,
	VertexFormat_UnsignedShort = 1523,
	VertexFormat_Int = 1524,
	VertexFormat_UnsignedInt = 1525,
	VertexFormat_Float = 1526
};


enum VertexUsage
{
	VertexUsage_Position,
	VertexUsage_Color,
	VertexUsage_TextureCoordinate,
	VertexUsage_Normal
};


struct VertexElement
{
	int offset;
	int count;
	int type;
	int usage;

	VertexElement() : offset(0), count(0), type(0), usage(0) {}

	VertexElement( int offset, int count, int type, int usage )
		: offset(offset), count(count), type(type), usage(usage)
	{
	}
};


struct VertexFormat
{
	static const int MaxElements = 4;

	int stride;
	int numElements;
	VertexElement elements[MaxElements];

	VertexFormat()
	{
		numElements = 0;
	}

	VertexFormat( const VertexElement* vertexElements, int numElements, int stride )
	{
		this->stride = stride;
		this->numElements = numElements;
		for( int i(0); i < numElements; ++i )
			elements[i] = vertexElements[i];
	}
};


struct Vertex2D
{
	Vector2 position;

	Vertex2D() {}
	Vertex2D( const Vector2 &position ) : position(position) {}
};


struct VertexColor2D
{
	Vector2 position;
	Color color;

	VertexColor2D() {}
	VertexColor2D( const Vector2 &position, const Color &color ) : position(position), color(color) {}
};


struct VertexColorTexture2D
{
	Vector2 position;
	Vector2 uv;
	Color color;

	VertexColorTexture2D() {}
	VertexColorTexture2D( const Vector2 &position, const Vector2 &uv, const Color &color )
		: position(position), uv(uv), color(color) {}
};


struct Vertex3D
{
	Vector3 position;

	Vertex3D() {}
	Vertex3D( const Vector2 &position ) : position(position) {}
};


struct VertexColor3D
{
	Vector3 position;
	Color color;

	VertexColor3D() {}
	VertexColor3D( const Vector3 &position, const Color &color )
		: position(position), color(color) {}

};


struct VertexColorTexture3D
{
	Vector3 position;
	Vector2 uv;
	Color color;

	VertexColorTexture3D() {}
	VertexColorTexture3D( const Vector3 &position, const Vector2 &uv, const Color &color )
		: position(position), uv(uv), color(color) {}

};


struct VertexNormalTexture3D
{
	Vector3 position;
	Vector3 normal;
	Vector2 uv;

	VertexNormalTexture3D() {}
	VertexNormalTexture3D( const Vector3 &position, const Vector3 &normal, const Vector2 &uv )
		: position(position), normal(normal), uv(uv) {}

};


struct VertexColorNormalTexture3D
{
	Vector3 position;
	Vector3 normal;
	Vector2 uv;
	Color color;

	VertexColorNormalTexture3D() {}
	VertexColorNormalTexture3D( const Vector3 &position, const Vector3 &normal, const Vector2 &uv, const Color &color )
		: position(position), normal(normal), uv(uv), color(color) {}

};


// Make POD types
MAKE_TRAIT(VertexElement, is_pod);
MAKE_TRAIT(VertexFormat, is_pod);
MAKE_TRAIT(Vertex2D, is_pod);
MAKE_TRAIT(VertexTexture2D, is_pod);
MAKE_TRAIT(VertexColor2D, is_pod);
MAKE_TRAIT(VertexColorTexture2D, is_pod);
MAKE_TRAIT(Vertex3D, is_pod);
MAKE_TRAIT(VertexTexture3D, is_pod);
MAKE_TRAIT(VertexNormalTexture3D, is_pod);
MAKE_TRAIT(VertexColor3D, is_pod);
MAKE_TRAIT(VertexColorTexture3D, is_pod);
MAKE_TRAIT(VertexColorNormalTexture3D, is_pod);


CE_NAMESPACE_END



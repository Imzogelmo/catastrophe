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
#include "Catastrophe/Core/Math/MathUtil.h"
#include "Catastrophe/Core/Math/Rect.h"
#include "Catastrophe/Core/Math/Rectf.h"
#include "Catastrophe/Graphics/Vertex.h"


CE_NAMESPACE_BEGIN


/// @Quad2D
///
/// 2D quad containing four vertices of type VertexColorTexture2D. 
///
struct Quad2D
{
	// aggregate type

	VertexColorTexture2D vertices[4];

	constexpr FORCEINLINE void SetVertices(VertexColorTexture2D* pVertices)
	{
		vertices[0] = pVertices[0];
		vertices[1] = pVertices[1];
		vertices[2] = pVertices[2];
		vertices[3] = pVertices[3];
	}

	constexpr FORCEINLINE void SetVertices(
		const VertexColorTexture2D& v0,
		const VertexColorTexture2D& v1,
		const VertexColorTexture2D& v2,
		const VertexColorTexture2D& v3)
	{
		vertices[0] = v0;
		vertices[1] = v1;
		vertices[2] = v2;
		vertices[3] = v3;
	}

	constexpr FORCEINLINE void SetVertexUVColorData(float minX, float minY, float maxX, float maxY, float minU, float minV, float maxU, float maxV, Color color)
	{
		vertices[0].position.x = minX;
		vertices[0].position.y = minY;
		vertices[0].uv.x = minU;
		vertices[0].uv.y = minV;
		vertices[0].color = color;

		vertices[1].position.x = minX;
		vertices[1].position.y = maxY;
		vertices[1].uv.x = minU;
		vertices[1].uv.y = maxV;
		vertices[1].color = color;

		vertices[2].position.x = maxX;
		vertices[2].position.y = maxY;
		vertices[2].uv.x = maxU;
		vertices[2].uv.y = maxV;
		vertices[2].color = color;

		vertices[3].position.x = maxX;
		vertices[3].position.y = minY;
		vertices[3].uv.x = maxU;
		vertices[3].uv.y = minV;
		vertices[3].color = color;
	}

	constexpr FORCEINLINE void SetVertexUVColorData(const float* v, const float* uv, const Color& color)
	{
		vertices[0].position.x = v[0];
		vertices[0].position.y = v[1];
		vertices[0].uv.x = uv[0];
		vertices[0].uv.y = uv[1];
		vertices[0].color = color;

		vertices[1].position.x = v[0];
		vertices[1].position.y = v[3];
		vertices[1].uv.x = uv[0];
		vertices[1].uv.y = uv[3];
		vertices[1].color = color;

		vertices[2].position.x = v[2];
		vertices[2].position.y = v[3];
		vertices[2].uv.x = uv[2];
		vertices[2].uv.y = uv[3];
		vertices[2].color = color;

		vertices[3].position.x = v[2];
		vertices[3].position.y = v[1];
		vertices[3].uv.x = uv[2];
		vertices[3].uv.y = uv[1];
		vertices[3].color = color;
	}

	/// Sets the vertex and texture coordinate components of the quad vertices to the given data.
	constexpr FORCEINLINE void SetVertexUVData(const Vector2& minPosition, const Vector2& maxPosition, const Rectf& uv)
	{
		SetVertexUVData(minPosition.x, minPosition.y, maxPosition.x, maxPosition.y, uv[0], uv[1], uv[2], uv[3]);
	}

	constexpr FORCEINLINE void SetVertexUVData(float minX, float minY, float maxX, float maxY, float minU, float minV, float maxU, float maxV)
	{
		vertices[0].position.x = minX;
		vertices[0].position.y = minY;
		vertices[1].position.x = minX;
		vertices[1].position.y = maxY;
		vertices[2].position.x = maxX;
		vertices[2].position.y = maxY;
		vertices[3].position.x = maxX;
		vertices[3].position.y = minY;

		vertices[0].uv.x = minU;
		vertices[0].uv.y = minV;
		vertices[1].uv.x = minU;
		vertices[1].uv.y = maxV;
		vertices[2].uv.x = maxU;
		vertices[2].uv.y = maxV;
		vertices[3].uv.x = maxU;
		vertices[3].uv.y = minV;
	}

	constexpr FORCEINLINE void SetVertexData(float minX, float minY, float maxX, float maxY)
	{
		vertices[0].position.x = minX;
		vertices[0].position.y = minY;
		vertices[1].position.x = minX;
		vertices[1].position.y = maxY;
		vertices[2].position.x = maxX;
		vertices[2].position.y = maxY;
		vertices[3].position.x = maxX;
		vertices[3].position.y = minY;
	}

	/// Set vertices from rectangular bounds array. 
	/// Pointer expects the format: [4] = {min x, min y, max x, max y};
	constexpr FORCEINLINE void SetVertexData( const float* v )
	{
		vertices[0].position.x = v[0];
		vertices[0].position.y = v[1];
		vertices[1].position.x = v[0];
		vertices[1].position.y = v[3];
		vertices[2].position.x = v[2];
		vertices[2].position.y = v[3];
		vertices[3].position.x = v[2];
		vertices[3].position.y = v[1];
	}

	constexpr FORCEINLINE void SetVertexData( const Rectf& vertices )
	{
		SetVertexData((float*)&vertices);
	}

	constexpr FORCEINLINE void SetUVData(float minU, float minV, float maxU, float maxV)
	{
		vertices[0].uv.x = minU;
		vertices[0].uv.y = minV;
		vertices[1].uv.x = minU;
		vertices[1].uv.y = maxV;
		vertices[2].uv.x = maxU;
		vertices[2].uv.y = maxV;
		vertices[3].uv.x = maxU;
		vertices[3].uv.y = minV;
	}

	/// Set vertices from rectangular bounds array. 
	/// Pointer expects the format: [4] = {min x, min y, max x, max y};
	constexpr FORCEINLINE void SetUVData( const float* uv )
	{
		vertices[0].uv.x = uv[0];
		vertices[0].uv.y = uv[1];
		vertices[1].uv.x = uv[0];
		vertices[1].uv.y = uv[3];
		vertices[2].uv.x = uv[2];
		vertices[2].uv.y = uv[3];
		vertices[3].uv.x = uv[2];
		vertices[3].uv.y = uv[1];
	}

	constexpr FORCEINLINE void SetUVData(const Rectf& uv)
	{
		SetUVData((float*)&uv);
	}

	constexpr FORCEINLINE void SetColorData(const Color* colors)
	{
		vertices[0].color = colors[0];
		vertices[1].color = colors[1];
		vertices[2].color = colors[2];
		vertices[3].color = colors[3];
	}

	constexpr FORCEINLINE void SetColorData(const Color& color)
	{
		vertices[0].color = color;
		vertices[1].color = color;
		vertices[2].color = color;
		vertices[3].color = color;
	}

	void Transform( float rotation, const Vector2& scale, const Vector2& origin )
	{
		if( rotation != 0.f )
		{
			const Vector2 sincosRotation = Math::SinCosf(rotation);
			Math::RotateScalePoint( sincosRotation, scale, origin, vertices[0].position );
			Math::RotateScalePoint( sincosRotation, scale, origin, vertices[1].position );
			Math::RotateScalePoint( sincosRotation, scale, origin, vertices[2].position );
			Math::RotateScalePoint( sincosRotation, scale, origin, vertices[3].position );
		}
		else if( scale != Vector2::One )
		{
			Math::ScalePoint( scale, origin, vertices[0].position );
			Math::ScalePoint( scale, origin, vertices[1].position );
			Math::ScalePoint( scale, origin, vertices[2].position );
			Math::ScalePoint( scale, origin, vertices[3].position );
		}
	}

	void Rotate( float rotation, const Vector2& origin )
	{
		const Vector2 sincosRotation = Math::SinCosf(rotation);
		Math::RotatePoint( sincosRotation, origin, vertices[0].position );
		Math::RotatePoint( sincosRotation, origin, vertices[1].position );
		Math::RotatePoint( sincosRotation, origin, vertices[2].position );
		Math::RotatePoint( sincosRotation, origin, vertices[3].position );
	}

	void Scale( const Vector2& scale, const Vector2& origin )
	{
		Math::ScalePoint( scale, origin, vertices[0].position );
		Math::ScalePoint( scale, origin, vertices[1].position );
		Math::ScalePoint( scale, origin, vertices[2].position );
		Math::ScalePoint( scale, origin, vertices[3].position );
	}

};

MAKE_TRAIT(Quad2D, is_pod);




CE_NAMESPACE_END


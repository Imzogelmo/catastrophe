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

#include "../Common.h"
#include "Vertex.h"
#include "BlendMode.h"
#include "PrimitiveType.h"
#include "VertexArray.h"

#include "../Math/Rectf.h"
#include "../Math/Matrix.h"

CE_NAMESPACE_BEGIN


class CE_API Primitive : public VertexArray<VertexColor2D>
{
public:
	typedef VertexArray<VertexColor2D>		base_type;
	typedef base_type::vec_type				vec_type;

	using base_type::AddVertex;

	Primitive( PrimitiveType prim = PrimitiveType_Points, BlendMode blendmode = BlendMode() )
		: base_type(), m_blendmode(blendmode), m_primType(prim)
	{}

	Primitive  operator + ( const Primitive& p );
	Primitive& operator += ( const Primitive& p );

	void SetBlendMode( const BlendMode& blendmode ) { m_blendmode = blendmode; }
	void SetPrimitiveType( PrimitiveType type ) { m_primType = type; }

	BlendMode GetBlendMode() const { return m_blendmode; }
	PrimitiveType GetPrimitiveType() const { return m_primType; }
	Vector2 GetCenter() const;
	Vector2 GetCenter( size_t start, size_t n ) const;
	Rectf GetBoundingRect() const;

	void RotateVertices( float rotation, const Vector2 &origin );
	void ScaleVertices( const Vector2 &scale, const Vector2 &origin );
	void RotateScaleVertices( float rotation, const Vector2 &scale, const Vector2 &origin );

	void AddVertex( const Vector2 &pos, const Color &color );
	void AddVertex( const Vector2* pos, const Color* color, int num_vertices );

	void CreateCircle( const Vector2 &center, float radius, const Color &inner, const Color &outer, bool filled = true, int detail = 32 );
	void CreateEllipse( const Vector2 &center, const Vector2 &radius, float angle, const Color &inner, const Color &outer, bool filled = true, int detail = 32 );
	void CreateTriangle( const Vector2 &p1, const Vector2 &p2, const Vector2 &p3, const Color &c1, const Color &c2, const Color &c3, bool filled = true );
	void CreateRectangle( const Rectf &rect, const Color &bl, const Color &tl, const Color &tr, const Color &br, bool filled = true );

	void Render();
	void Render( size_t index, size_t n );
	void Render( const Matrix& transformation );

protected:
	BlendMode		m_blendmode;
	PrimitiveType	m_primType;

};



class CE_API PrimitiveObject : protected Primitive
{
public:
	typedef Primitive				base_type;
	typedef base_type::vec_type		vec_type;

	using base_type::operator +;
	using base_type::operator +=;
	using base_type::SetBlendMode;
	using base_type::GetBlendMode;
	using base_type::SetPrimitiveType;
	using base_type::GetPrimitiveType;
	using base_type::GetCenter;
	using base_type::GetBoundingRect;
	using base_type::Reserve;

	PrimitiveObject( PrimitiveType type = PrimitiveType_Points, BlendMode blendmode = BlendMode::Alpha );

	void SetPosition( const Vector2& value ) { m_pos = value; m_isDirty = true; }
	void SetAngle( float value ) { m_angle = value; m_isDirty = true; }
	void SetScale( const Vector2& value ) { m_scale = value; m_isDirty = true; }

	Vector2 GetPosition() const { return m_pos; }
	Vector2 GetScale() const { return m_scale; }
	float GetAngle() const { return m_angle; }
	
	void AddVertex( const Vector2 &pos, const Color &color );
	void AddVertex( const Vector2* pos, const Color* color, int num_vertices );
	void AddVertex( const VertexColor2D& vertex );
	void AddVertex( const VertexColor2D* vertices, int num_vertices );

	void CalculateTransformationMatrix();
	const Matrix& GetTransfomationMatrix();

	void Render();

protected:
	Matrix		m_transformation;
	Vector2		m_pos;
	Vector2		m_scale;
	float		m_angle;
	bool		m_isDirty;

};


CE_NAMESPACE_END


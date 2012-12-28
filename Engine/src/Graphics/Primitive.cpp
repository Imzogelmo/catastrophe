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

#include "Graphics/Primitive.h"
#include "Graphics/OpenGL.h"

#include "Math/Math.h"
#include "Math/Rectf.h"
#include "Math/Matrix.h"

CE_NAMESPACE_BEGIN


Primitive& Primitive::operator += ( const Primitive& p )
{
	base_type::Append(p);
	return *this;
}


Primitive Primitive::operator + ( const Primitive& p )
{
	Primitive prim;
	prim.Reserve( (Size() + p.Size()) + ((Size() + p.Size()) / 4) );
	prim += *this;
	prim += p;

	return prim;
}


Vector2 Primitive::GetCenter() const
{
	Vector2 center = Vector2::Zero;
	for( vec_type::const_iterator it = m_vertices.begin(); it != m_vertices.end(); ++it )
	{
		center += it->pos;
	}

	if( !m_vertices.empty() )
		center /= float(m_vertices.size());

	return center;
}


Rectf Primitive::GetBoundingRect() const
{
	Rectf r = Rectf::Zero;
	if( !m_vertices.empty() )
	{
		for( vec_type::const_iterator it = m_vertices.begin(); it != m_vertices.end(); ++it )
			r.Merge(it->pos.x);
	}

	return r;
}


void Primitive::RotateVertices( float rotation, const Vector2 &origin )
{
	Vector2 rot = Math::SinCos(rotation);
	for( vec_type::iterator it = m_vertices.begin(); it != m_vertices.end(); ++it )
	{
		Math::RotatePoint( rot, origin, it->pos );
	}
}


void Primitive::ScaleVertices( const Vector2 &scale, const Vector2 &origin )
{
	for( vec_type::iterator it = m_vertices.begin(); it != m_vertices.end(); ++it )
	{
		Math::ScalePoint( scale, origin, it->pos );
	}
}


void Primitive::RotateScaleVertices( float rotation, const Vector2 &scale, const Vector2 &origin )
{
	Vector2 rot = Math::SinCos(rotation);
	for( vec_type::iterator it = m_vertices.begin(); it != m_vertices.end(); ++it )
	{
		Math::RotateScalePoint( rot, scale, origin, it->pos );
	}
}


void Primitive::AddVertex( const Vector2 &pos, const Color &color )
{
	VertexColor & v = m_vertices.push_back_uninitialized();
	v.pos = pos;
	v.color = color;
}


void Primitive::AddVertex( const Vector2 *pos, const Color *color, int num_vertices )
{
	VertexColor * v = m_vertices.push_back_uninitialized( num_vertices );
	for( int i(0); i < num_vertices; ++i )
	{
		v[i].pos = pos[i];
		v[i].color = color[i];
	}
}


void Primitive::CreateCircle( const Vector2 &center, float radius, const Color &inner, const Color &outer, bool filled, int detail )
{
	CreateEllipse(center, radius, 0.f, inner, outer, filled, detail);
}


void Primitive::CreateEllipse( const Vector2 &center, const Vector2 &radius, float angle, const Color &inner, const Color &outer, bool filled, int detail )
{
	Clear();
	m_vertices.reserve( (size_t)(detail + 2) );

	if( filled )
	{
		m_primType = ptTRIANGLE_FAN;
		AddVertex(center, inner);
	}
	else
	{
		m_primType = ptLINE_STRIP;
	}

	float a = 0.f;
	float t = Math::TwoPi / float(detail);

	for( int i(0); i <= detail; ++i )
	{
		const Vector2 v = Math::SinCos(a) * radius;
		a += t;

		AddVertex(v, outer);
	}

	if(angle != 0.f)
	{
		RotateVertices(angle, GetCenter());
	}
}


void Primitive::CreateTriangle( const Vector2 &p1, const Vector2 &p2, const Vector2 &p3, const Color &c1, const Color &c2, const Color &c3, bool filled )
{
	Clear();
	m_vertices.reserve(size_t(3));

	if( filled )
	{
		m_primType = ptTRIANGLES;
	}
	else
	{
		m_primType = ptLINE_LOOP;
	}

	AddVertex(p1, c1);
	AddVertex(p2, c2);
	AddVertex(p3, c3);
}


void Primitive::CreateRectangle( const Rectf &rect, const Color &bl, const Color &tl, const Color &tr, const Color &br, bool filled )
{
	Clear();
	m_vertices.reserve(size_t(4));

	if( filled )
	{
		m_primType = ptQUADS;
	}
	else
	{
		m_primType = ptLINE_LOOP;
	}

	AddVertex(rect.BottomLeft(), bl);
	AddVertex(rect.TopLeft(), tl);
	AddVertex(rect.TopRight(), tr);
	AddVertex(rect.BottomRight(), br);
}


void Primitive::Render( size_t index, size_t n )
{
	m_blendmode.Apply();

	glVertexPointer( 2, GL_FLOAT, sizeof(VertexColor), &m_vertices[0].pos );
	glColorPointer( 4, GL_UNSIGNED_BYTE, sizeof(VertexColor), &m_vertices[0].color );
	glDrawArrays( m_primType, index, n );
}


void Primitive::Render()
{
	Render(0, m_vertices.size());
}


void Primitive::Render( const Matrix& transformation )
{
	glPushMatrix();
		glMultMatrixf( &transformation.m[0] );
		Render();
	glPopMatrix();
}




/////////////////////////////////////////////////////
//               PrimitiveObject
/////////////////////////////////////////////////////

PrimitiveObject::PrimitiveObject( PrimitiveType prim, BlendMode blendmode ) : 
	base_type(prim, blendmode),
	m_pos(Vector2::Zero),
	m_scale(Vector2::One),
	m_angle(0.f),
	m_isDirty(false)
{
}


void PrimitiveObject::AddVertex( const Vector2 &pos, const Color &color )
{
	m_isDirty = true;
	base_type::AddVertex(pos, color);
}


void PrimitiveObject::AddVertex( const Vector2* pos, const Color* color, int num_vertices )
{
	m_isDirty = true;
	base_type::AddVertex(pos, color, num_vertices);
}


void PrimitiveObject::AddVertex( const VertexColor& vertex )
{
	m_isDirty = true;
	base_type::base_type::AddVertex(vertex);
}


void PrimitiveObject::AddVertex( const VertexColor* vertices, int num_vertices )
{
	m_isDirty = true;
	base_type::base_type::AddVertex(vertices, num_vertices);
}


void PrimitiveObject::CalculateTransformationMatrix()
{
	if(m_isDirty)
	{
		//Vector3 scale = Vector3(m_scale, 1.f);
		m_transformation = Matrix::CreateTransformation( m_pos, m_angle, m_scale, GetCenter() );
	//	m_transformation = Matrix::Create2DTransformation( m_pos, m_angle, m_scale, GetCenter() );
		m_isDirty = false;
	}
}


const Matrix& PrimitiveObject::GetTransfomationMatrix()
{
	CalculateTransformationMatrix();
	return m_transformation;
}


void PrimitiveObject::Render()
{
	CalculateTransformationMatrix();

	glPushMatrix();
		glMultMatrixf( &m_transformation.m[0] );
		base_type::Render();
	glPopMatrix();
}



CE_NAMESPACE_END



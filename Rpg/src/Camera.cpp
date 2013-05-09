// catastrophe rpg engine
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

#include <Catastrophe/Math/Vector3.h>
#include <Catastrophe/Math/Rectf.h>

#include "Camera.h"


Camera::Camera() :
	m_projection(Matrix::Identity),
	m_transform(Matrix::Identity),
	m_view(Matrix::Identity),
	m_pos(Vector2::Zero),
	m_rotation(0.f),
	m_boundry(Rectf::Zero),
	m_transformDirty(true),
	m_viewDirty(true)
{
	SetBoundingArea( Rectf(-65536, -65536, 65536, 65536) );
}


void Camera::SetBoundingArea( const Rectf& boundingRect )
{
	m_boundry = boundingRect;
	if( !boundingRect.Contains(m_pos) )
	{
		ClampPosition(boundingRect.min, boundingRect.max);
	}
}


void Camera::SetProjectionMatrix( const Matrix& m )
{
	m_projection = m; //todo
	m_viewDirty = true;
}


void Camera::SetPosition( const Vector2& position )
{
	m_pos = position;
	m_transformDirty = true;
}


void Camera::SetRotation( float rotation )
{
	m_rotation = Math::WrapAngle(rotation);
	m_transformDirty = true;
}


void Camera::Move( const Vector2& dir )
{
	pos += dir;
	m_transformDirty = true;
}


void Camera::Rotate( float rotation )
{
	m_rot = Math::WrapAngle(m_rotation += rotation);
	m_transformDirty = true;
}


void Camera::ClampPosition( const Vector2& minv, const Vector2& maxv )
{
	m_pos.Clamp(minv, maxv);
	m_transformDirty = true;
}


void Camera::Update()
{
	Matrix mat = GetView();

	glMatrixMode( GL_PROJECTION );
	glLoadMatrixf( &mat[0] );
	glMatrixMode( GL_MODELVIEW );
	Matrix::LoadIdentity();
}


Rectf Camera::GetViewRect() const
{
	//todo:
	return Rectf(-128, -104, 128, 104);
}


const Matrix& Camera::GetProjection() const
{
	return m_projection;
}


const Matrix& Camera::GetTransform() const
{
	/*
		Matrix::CreateScale( scale ) *
		Matrix::CreateRotation( rot ) *
		Matrix::CreateTranslation( Vector3(-pos.x, -pos.y, pos.z) )
	*/

	if( m_transformDirty )
	{
		m_transform = 
			Matrix::CreateRotation( Vector3(0.f, 0.f, m_rot) ) *
			Matrix::CreateTranslation( Vector3(-pos.x, -pos.y, 0.f) );
		m_transformDirty = false;
	}

	return m_transform;
}


const Matrix& Camera::GetView() const
{
	if( m_viewDirty )
	{
		m_view = GetProjection() * GetTransform();
		m_viewDirty = false;
	}

	return m_view;
}

















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

#pragma once

#include <Catastrophe/Math/Vector2.h>
#include <Catastrophe/Math/Matrix.h>

#include "Common.h"


class Camera
{
public:
	Camera();

	void SetBoundingArea( const Rectf& boundingRect );
	void SetProjectionMatrix( const Matrix& m );
	void SetPosition( const Vector2& position );
	void SetRotation( float rotation );
	void Move( const Vector2& dir );
	void Rotate( float rotation );
	void ClampPosition( const Vector2& minv, const Vector2& maxv );
	void Update();

	const Vector2& GetPosition() const { return m_pos; }
	float GetRotation() const { return m_rotation; }
	Rectf GetViewRect() const;

	const Matrix& GetProjection() const;
	const Matrix& GetTransform() const;
	const Matrix& GetView() const;

protected:
	Vector2			m_pos;
	float			m_rotation;
	Rectf			m_boundry;
	mutable Matrix	m_projection;
	mutable Matrix	m_transform;
	mutable Matrix	m_view;
	mutable bool	m_transformDirty;
	mutable bool	m_viewDirty;

};




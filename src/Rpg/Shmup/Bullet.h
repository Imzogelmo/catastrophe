
#pragma once

#include <fc/math.h>
#include <Engine/Math/Vector2.h>
#include <Engine/Math/Rectf.h>
#include <Engine/Graphics/Sprite.h>
#include <Engine/Util/Indexable.h>
#include "../Common.h"


struct Bullet : public Indexable<>
{
	int type;
	Vector2 pos;
	Vector2 velocity;
	Vector2 accel;
	float angular_velocity;
	float rotation_speed;
	Rectf hitbox;
	AnimatedSprite sprite;
	bool is_alive;
	bool is_angular;

	Bullet() :
		type(0),
		pos(Vector2::Zero),
		velocity(Vector2::Zero),
		accel(Vector2::Zero),
		angular_velocity(0.f),
		rotation_speed(0.f),
		hitbox(Rectf::Zero),
		sprite(),
		is_alive(false),
		is_angular(false)
	{
	}

	void InitializeToZero()
	{
		type = 0;
		pos = 0.f;
		velocity = 0.f;
		accel = 0.f;
		angular_velocity = 0.f;
		rotation_speed = 0.f;
		hitbox = Rectf::Zero;
		sprite = AnimatedSprite(),
		is_alive = false;
		is_angular = false;
	}

	bool Update()
	{
		if( !is_alive )
			return false;

		sprite.angle += rotation_speed;
		if( is_angular )
		{
			float s, c;
			fc::fast_sincos(sprite.angle, s, c);
			velocity.x = angular_velocity * c;
			velocity.y = angular_velocity * s;
		}

		pos += velocity;
		velocity += accel;

		return true;
	}

	void Render()
	{
	}

	Rectf GetBoundingRect() const
	{
		return hitbox + pos;
	}
};


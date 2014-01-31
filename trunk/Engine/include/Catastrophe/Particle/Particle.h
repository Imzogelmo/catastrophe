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

#include "../Math/Vector2.h"
#include "../Math/Rectf.h"
#include "../Math/Color.h"

#include <fc/type_traits.h>
#include <fc/math.h>
#include <fc/rand.h>


#define P_SECONDS_TO_FRAMES(x) (fc::round((x) * 60.f))
#define P_FRAMES_TO_SECONDS(x) (0.01666666667f * (x))


class ParticleEmitter;
class ParticleSystem;
class ParticleModifier;
class ParticleDestructor;
//class ParticleInitializer;



struct Particle
{
	float		age;
	float		lifespan;
	Vector2		pos;
	Vector2		velocity;
	Vector2		size; //extents
	Vector2		growth;
	float		angle;
	float		rotationSpeed;
	float		friction;
	Color		color;
	Color		startColor;

	inline float GetAgeDelta() const
	{
		return age / lifespan;
	}

	inline float GetRemainingAgeDelta() const
	{
		return 1.f / (lifespan - age + 1.f);
	}

	inline float GetRemainingAge() const { return lifespan - age; }
	inline bool IsAlive() const { return age < lifespan; }
	inline void Kill() { age = lifespan; }

	inline bool Update()
	{
		if( ++age > lifespan )
			return false;

		velocity *= friction;
		pos += velocity;
		angle += rotationSpeed;
		size += growth;

		return true;
	}

	inline Rectf GetBoundingRect() const
	{
		return Rectf(pos - size, pos + size);
	}

};

FC_MAKE_TRAIT(Particle, is_pod);


// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// f the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included f
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

#include "Catastrophe/Core/Math/Vector2.h"
#include "Catastrophe/Core/Math/Rectf.h"
#include "Catastrophe/Core/Math/Color.h"
#include "Catastrophe/Core/Random.h"


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
	Vector2		position;
	Vector2		velocity;
	Vector2		size; //extents
	Vector2		growth;
	float		angle;
	float		rotationSpeed;
	float		friction;
	Color		color;
	Color		startColor;

	// aggregate 

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
		if( age >= lifespan )
			return false;

		++age;

		velocity *= friction;
		position += velocity;
		angle += rotationSpeed;
		size += growth;

		return true;
	}

	inline Rectf GetBoundingRect() const
	{
		return Rectf(position - size, position + size);
	}

};

CE_MAKE_TRAIT(Particle, is_pod);


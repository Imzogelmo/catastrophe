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


#include "Catastrophe/Core/Random.h"

CE_NAMESPACE_BEGIN


namespace Random
{
	namespace Internal
	{
		int gRandomSeed = 0;
	}

	int Rand()
	{
		using Internal::gRandomSeed;
		return(((gRandomSeed = gRandomSeed * 214013 + 2531011) >> 16) & CE_RAND_MAX);
	}

	void SeedRand(int seed)
	{
		Internal::gRandomSeed = seed;
	}

	void CircularRand( float &x, float &y )
	{
		float angle = Variance(PI);
		Math::ApproximateSinCosf(angle, y, x);
	}

	void CircularRand( float radius, float &x, float &y )
	{
		CircularRand(y, x);
		x *= radius;
		y *= radius;
	}

	void ArcRand( float minAngle, float maxAngle, float &x, float &y )
	{
		float angle = Float(minAngle, maxAngle);
		Math::ApproximateSinCosf( angle, y, x );
	}

	void ArcRand( float minAngle, float maxAngle, float radius, float &x, float &y )
	{
		ArcRand( minAngle, maxAngle, y, x );
		x *= radius;
		y *= radius;
	}

	Vector2 CircularRand( float radius )
	{
		Vector2 v;
		Random::CircularRand(radius, v.x, v.y);
		return v;
	}


	Vector2 ArcRand( float minAngle, float maxAngle, float radius )
	{
		Vector2 v;
		Random::ArcRand(minAngle, maxAngle, radius, v.x, v.y);
		return v;
	}

} // Random


CE_NAMESPACE_END




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
#include "Catastrophe/Core/PlatformMath.h"
#include "Catastrophe/Core/Math/Easing.h"

// Uses Robert Penner's easing equations for interpolation.
// (http://robertpenner.com/easing/)

CE_NAMESPACE_BEGIN


namespace Easing
{

	EasingFunctionPtr GetFunction( EasingEquation equation )
	{
		EasingFunctionPtr func = 0;
		switch(equation)
		{
			case EasingEquation_Linear: func = &Linear; break;
			case EasingEquation_QuadraticEaseOut: func = &QuadraticEaseOut; break;
			case EasingEquation_QuadraticEaseIn: func = &QuadraticEaseIn; break;
			case EasingEquation_QuadraticEaseInOut: func = &QuadraticEaseInOut; break;
			case EasingEquation_ExponentialEaseOut: func = &ExponentialEaseOut; break;
			case EasingEquation_ExponentialEaseIn: func = &ExponentialEaseIn; break;
			case EasingEquation_ExponentialEaseInOut: func = &ExponentialEaseInOut; break;
			case EasingEquation_CubicEaseOut: func = &CubicEaseOut; break;
			case EasingEquation_CubicEaseIn: func = &CubicEaseIn; break;
			case EasingEquation_CubicEaseInOut: func = &CubicEaseInOut; break;
			case EasingEquation_QuarticEaseOut: func = &QuarticEaseOut; break;
			case EasingEquation_QuarticEaseIn: func = &QuarticEaseIn; break;
			case EasingEquation_QuarticEaseInOut: func = &QuarticEaseInOut; break;
			case EasingEquation_QuinticEaseOut: func = &QuinticEaseOut; break;
			case EasingEquation_QuinticEaseIn: func = &QuinticEaseIn; break;
			case EasingEquation_QuinticEaseInOut: func = &QuinticEaseInOut; break;
			case EasingEquation_CircularEaseOut: func = &CircularEaseOut; break;
			case EasingEquation_CircularEaseIn: func = &CircularEaseIn; break;
			case EasingEquation_CircularEaseInOut: func = &CircularEaseInOut; break;
			case EasingEquation_SinusoidalEaseOut: func = &SinusoidalEaseOut; break;
			case EasingEquation_SinusoidalEaseIn: func = &SinusoidalEaseIn; break;
			case EasingEquation_SinusoidalEaseInOut: func = &SinusoidalEaseInOut; break;
			case EasingEquation_ElasticEaseOut: func = &ElasticEaseOut; break;
			case EasingEquation_ElasticEaseIn: func = &ElasticEaseIn; break;
			case EasingEquation_ElasticEaseInOut: func = &ElasticEaseInOut; break;
			case EasingEquation_BounceEaseOut: func = &BounceEaseOut; break;
			case EasingEquation_BounceEaseIn: func = &BounceEaseIn; break;
			case EasingEquation_BounceEaseInOut: func = &BounceEaseInOut; break;
			case EasingEquation_BackEaseOut: func = &BackEaseOut; break;
			case EasingEquation_BackEaseIn: func = &BackEaseIn; break;
			case EasingEquation_BackEaseInOut: func = &BackEaseInOut; break;
		}

		CE_ASSERT(func != 0);

		return func;
	}

	// t - current timestep
	// b - beginning value
	// c - value to move by
	// d - total timestep

	float Linear(float t, float b, float c, float d)
	{
		return c * t / d + b;
	}

	float QuadraticEaseIn(float t, float b, float c, float d)
	{
		t /= d;
		return c * t * t + b;
	}

	float QuadraticEaseOut(float t, float b, float c, float d)
	{
		t /= d;
		return -c * t * (t - 2.0f) + b;
	}

	float QuadraticEaseInOut(float t, float b, float c, float d)
	{
		t /= d / 2.0f;
		if(t < 1.0f) return c / 2.0f * t * t + b;
		t--;
		return -c / 2.0f * (t * (t - 2.0f) - 1.0f) + b;
	}

	float CubicEaseIn(float t, float b, float c, float d)
	{
		t /= d;
		return c * t * t * t + b;
	}

	float CubicEaseOut(float t, float b, float c, float d)
	{
		t /= d;
		t--;
		return c * (t * t * t + 1.0f) + b;
	}

	float CubicEaseInOut(float t, float b, float c, float d)
	{
		t /= d / 2.0f;
		if(t < 1.0f) return c / 2.0f * t * t * t + b;
		t -= 2.0f;
		return c / 2.0f * (t * t * t + 2.0f) + b;
	}

	float QuarticEaseIn(float t, float b, float c, float d)
	{
		t /= d;
		return c * t * t * t * t + b;
	}

	float QuarticEaseOut(float t, float b, float c, float d)
	{
		t /= d;
		t--;
		return -c * (t * t * t * t - 1.0f) + b;
	}

	float QuarticEaseInOut(float t, float b, float c, float d)
	{
		t /= d / 2.0f;
		if(t < 1.0f) return c / 2.0f * t * t * t * t + b;
		t -= 2.0f;
		return -c / 2.0f * (t * t * t * t - 2.0f) + b;
	}

	float QuinticEaseIn(float t, float b, float c, float d)
	{
		t /= d;
		return c * t * t * t * t * t + b;
	}

	float QuinticEaseOut(float t, float b, float c, float d)
	{
		t /= d;
		t--;
		return c * (t * t * t * t * t + 1.0f) + b;
	}

	float QuinticEaseInOut(float t, float b, float c, float d)
	{
		t /= d / 2.0f;
		if(t < 1.0f) return c / 2.0f * t * t * t * t * t + b;
		t -= 2.0f;
		return c / 2.0f * (t * t * t * t * t + 2.0f) + b;
	}

	float SinusoidalEaseIn(float t, float b, float c, float d)
	{
		return -c * cosf(t / d * (PI / 2.0f)) + c + b;
	}

	float SinusoidalEaseOut(float t, float b, float c, float d)
	{
		return c * sinf(t / d * (PI / 2.0f)) + b;
	}

	float SinusoidalEaseInOut(float t, float b, float c, float d)
	{
		return -c / 2.0f * (cosf(PI * t / d) - 1.0f) + b;
	}

	float ExponentialEaseIn(float t, float b, float c, float d)
	{
		return c * powf(2.0f, 10.0f * (t / d - 1.0f)) + b;
	}

	float ExponentialEaseOut(float t, float b, float c, float d)
	{
		return c * (-powf(2.0f, -10.0f * t / d) + 1.0f) + b;
	}

	float ExponentialEaseInOut(float t, float b, float c, float d)
	{
		t /= d / 2.0f;
		if(t < 1.0f) return c / 2.0f * powf(2.0f, 10.0f * (t - 1.0f)) + b;
		t--;
		return c / 2.0f * (-powf(2.0f, -10.0f * t) + 2.0f) + b;
	}

	float CircularEaseIn(float t, float b, float c, float d)
	{
		t /= d;
		return -c * (sqrtf(1.0f - t * t) - 1.0f) + b;
	}

	float CircularEaseOut(float t, float b, float c, float d)
	{
		t /= d;
		t--;
		return c * sqrtf(1.0f - t * t) + b;
	}

	float CircularEaseInOut(float t, float b, float c, float d)
	{
		t /= d / 2.0f;
		if(t < 1) return -c / 2.0f * (sqrtf(1.0f - t * t) - 1.0f) + b;
		t -= 2.0f;
		return c / 2.0f * (sqrtf(1.0f - t * t) + 1.0f) + b;
	}

	float BounceEaseIn(float t, float b, float c, float d)
	{
		return c - BounceEaseOut(d - t, 0.0f, c, d) + b;
	}

	float BounceEaseOut(float t, float b, float c, float d)
	{
		if((t /= d) < (1.0f / 2.75f))
		{
			return c * (7.5625f * t * t) + b;
		}
		else if(t < (2.0f / 2.75f))
		{
			return c * (7.5625f * (t -= (1.5f / 2.75f)) * t + .75f) + b;
		}
		else if(t < (2.5f / 2.75f))
		{
			return c * (7.5625f * (t -= (2.25f / 2.75f)) * t + .9375f) + b;
		}
		else
		{
			return c * (7.5625f * (t -= (2.625f / 2.75f)) * t + .984375f) + b;
		}
	}

	float BounceEaseInOut(float t, float b, float c, float d)
	{
		if(t < d / 2.0f) return BounceEaseIn(t * 2.0f, 0.0f, c, d) * .5f + b;
		else return BounceEaseOut(t * 2.0f - d, 0.0f, c, d) * .5f + c * .5f + b;
	}

	float ElasticEaseIn(float t, float b, float c, float d)
	{
		if(Math::EpsilonCompare(t, 0.0f)) return b;
		if(Math::EpsilonCompare((t /= d), 1.0f)) return b + c;  

		float p = d * .3f;
		float a = c;
		float s = p / 4.0f;

		return -(a * powf(2.0f, 10.0f * (t -= 1.0f)) * sinf((t * d - s) * (2.0f * PI) / p)) + b;
	}

	float ElasticEaseOut(float t, float b, float c, float d)
	{
		if(Math::EpsilonCompare(t, 0.0f)) return b;
		if(Math::EpsilonCompare((t /= d), 1.0f)) return b + c;

		float p = d * .3f;
		float a = c;
		float s = p / 4.0f;

		return (a * powf(2.0f, -10.0f * t) * sinf((t * d - s) * (2.0f * PI) / p) + c + b);
	}

	float ElasticEaseInOut(float t, float b, float c, float d)
	{
		if(Math::EpsilonCompare(t, 0.0f)) return b;
		if(Math::EpsilonCompare((t /= d / 2.0f), 2.0f)) return b + c;

		float p = d * (.3f * 1.5f);
		float a = c;
		float s = p / 4.0f;

		if(t < 1.0f) return -.5f * (a * powf(2.0f, 10.0f * (t -= 1.0f)) * sinf((t * d - s) * (2.0f * PI) / p)) + b;
		return a * powf(2.0f, -10.0f * (t -= 1.0f)) * sinf((t * d - s) * (2.0f * PI) / p) * .5f + c + b;
	}

	float BackEaseIn(float t, float b, float c, float d)
	{
		float s = 1.70158f;
		return c * (t /= d) * t * ((s + 1.0f) * t - s) + b;
	}

	float BackEaseOut(float t, float b, float c, float d)
	{
		float s = 1.70158f;
		return c * ((t = t / d - 1.0f) * t * ((s + 1.0f) * t + s) + 1.0f) + b;
	}

	float BackEaseInOut(float t, float b, float c, float d)
	{
		float s = 1.70158f;
		if((t /= d / 2.0f) < 1.0f) return c / 2.0f * (t * t * (((s *= (1.525f)) + 1.0f) * t - s)) + b;
		return c / 2.0f * ((t -= 2.0f) * t * (((s *= (1.525f)) + 1.0f) * t + s) + 2.0f) + b;
	}
}


CE_NAMESPACE_END

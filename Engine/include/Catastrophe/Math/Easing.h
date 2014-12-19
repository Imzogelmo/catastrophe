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

#include "Common.h"

CE_NAMESPACE_BEGIN


enum EasingEquation
{
	EasingEquation_Linear,
	EasingEquation_QuadraticEaseOut,
	EasingEquation_QuadraticEaseIn,
	EasingEquation_QuadraticEaseInOut,
	EasingEquation_ExponentialEaseOut,
	EasingEquation_ExponentialEaseIn,
	EasingEquation_ExponentialEaseInOut,
	EasingEquation_CubicEaseOut,
	EasingEquation_CubicEaseIn,
	EasingEquation_CubicEaseInOut,
	EasingEquation_QuarticEaseOut,
	EasingEquation_QuarticEaseIn,
	EasingEquation_QuarticEaseInOut,
	EasingEquation_QuinticEaseOut,
	EasingEquation_QuinticEaseIn,
	EasingEquation_QuinticEaseInOut,
	EasingEquation_CircularEaseOut,
	EasingEquation_CircularEaseIn,
	EasingEquation_CircularEaseInOut,
	EasingEquation_SinusoidalEaseOut,
	EasingEquation_SinusoidalEaseIn,
	EasingEquation_SinusoidalEaseInOut,
	EasingEquation_ElasticEaseOut,
	EasingEquation_ElasticEaseIn,
	EasingEquation_ElasticEaseInOut,
	EasingEquation_BounceEaseOut,
	EasingEquation_BounceEaseIn,
	EasingEquation_BounceEaseInOut,
	EasingEquation_BackEaseOut,
	EasingEquation_BackEaseIn,
	EasingEquation_BackEaseInOut
};


typedef float (*EasingFunctionPtr)(float, float, float, float);

EasingFunctionPtr GetFunction( EasingEquation equation );

namespace Easing
{
	// t - current timestep
	// b - beginning value
	// c - value to move by
	// d - total timestep

	float Linear(float t, float b, float c, float d);
	float QuadraticEaseIn(float t, float b, float c, float d);
	float QuadraticEaseOut(float t, float b, float c, float d);
	float QuadraticEaseInOut(float t, float b, float c, float d);
	float CubicEaseIn(float t, float b, float c, float d);
	float CubicEaseOut(float t, float b, float c, float d);
	float CubicEaseInOut(float t, float b, float c, float d);
	float QuarticEaseIn(float t, float b, float c, float d);
	float QuarticEaseOut(float t, float b, float c, float d);
	float QuarticEaseInOut(float t, float b, float c, float d);
	float QuinticEaseIn(float t, float b, float c, float d);
	float QuinticEaseOut(float t, float b, float c, float d);
	float QuinticEaseInOut(float t, float b, float c, float d);
	float SinusoidalEaseIn(float t, float b, float c, float d);
	float SinusoidalEaseOut(float t, float b, float c, float d);
	float SinusoidalEaseInOut(float t, float b, float c, float d);
	float ExponentialEaseIn(float t, float b, float c, float d);
	float ExponentialEaseOut(float t, float b, float c, float d);
	float ExponentialEaseInOut(float t, float b, float c, float d);
	float CircularEaseIn(float t, float b, float c, float d);
	float CircularEaseOut(float t, float b, float c, float d);
	float CircularEaseInOut(float t, float b, float c, float d);
	float BounceEaseIn(float t, float b, float c, float d);
	float BounceEaseOut(float t, float b, float c, float d);
	float BounceEaseInOut(float t, float b, float c, float d);
	float ElasticEaseIn(float t, float b, float c, float d);
	float ElasticEaseOut(float t, float b, float c, float d);
	float ElasticEaseInOut(float t, float b, float c, float d);
	float BackEaseIn(float t, float b, float c, float d);
	float BackEaseOut(float t, float b, float c, float d);
	float BackEaseInOut(float t, float b, float c, float d);

}


CE_NAMESPACE_END

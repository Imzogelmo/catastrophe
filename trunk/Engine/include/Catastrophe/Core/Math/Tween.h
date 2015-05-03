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
#include "Catastrophe/Core/Math/Easing.h"

#include "Catastrophe/Core/Containers/Vector.h"

CE_NAMESPACE_BEGIN


struct TweenValue
{
	float*	pValue;
	float	targetValue;
	float	startValue;

	TweenValue() : pValue(null), targetValue(0.f), startValue(0.f) {}
	TweenValue( float* pValue, float targetValue ) : pValue(pValue), targetValue(targetValue), startValue(*pValue)
	{}

};


/*
struct IntrusiveTweenBase
{
	EasingFunctionPtr easingFunction
	float elapsed;
	float duration;

	TweenValue() : elapsed(0.f), duration(0.f) {}
	TweenValue(EasingFunctionPtr f, float elapsed, float duration) : easingFunction(f), elapsed(elapsed), duration(duration) {}

	bool IsFinished() const { return elapsed >= duration; }

};


struct FloatTween : IntrusiveTweenBase
{
	float targetValue;
	float startValue;

	TweenValue() : IntrusiveTweenBase(), targetValue(0.f), startValue(0.f) {}
	TweenValue( const IntrusiveTweenBase& baseValues, float target, float start )
		: IntrusiveTweenBase(baseValues), targetValue(target), startValue(start)
	{}

	void Step(float dt, float* pValue)
	{
		elapsed += dt;
		if( elapsed < duration )
		{
			float diff = targetValue - startValue;
			*pValue = easingFunction(elapsed, startValue, diff, duration);
		}
		else
		{
			*pValue = targetValue;
		}
	}
};

struct Vector2Tween : IntrusiveTweenBase
{
	Vector2 targetValue;
	Vector2 startValue;

	TweenValue() : IntrusiveTweenBase(), targetValue(Vector2::Zero), startValue(Vector2::Zero) {}
	TweenValue( const IntrusiveTweenBase& baseValues, const Vector2& target, const Vector2& start )
		: IntrusiveTweenBase(baseValues), targetValue(target), startValue(start)
	{}

	void Step(float dt, Vector2* p)
	{
		elapsed += dt;
		if( elapsed < duration )
		{
			Vector2 diff = targetValue - startValue;
			p->x = easingFunction(elapsed, startValue.x, diff.x, duration);
			p->y = easingFunction(elapsed, startValue.y, diff.y, duration);
		}
		else
		{
			*p = targetValue;
		}
	}

};

struct ColorTween : IntrusiveTweenBase
{
	Colorf targetValue;
	Colorf startValue;

	TweenValue() : IntrusiveTweenBase(), targetValue(Colorf::White()), startValue(Colorf::White()) {}
	TweenValue( const IntrusiveTweenBase& baseValues, const Colorf& target, const Colorf& start )
		: IntrusiveTweenBase(baseValues), targetValue(target), startValue(start)
	{}

	void Step(float dt, Color* pColor)
	{
		elapsed += dt;
		if( elapsed < duration )
		{
			Colorf tempColor;
			Vector4 diff = *(Vector4*)&targetValue - *(Vector4*)&startValue;
			tempColor->r = easingFunction(elapsed, startValue.x, diff.x, duration);
			tempColor->g = easingFunction(elapsed, startValue.y, diff.y, duration);
			tempColor->b = easingFunction(elapsed, startValue.z, diff.z, duration);
			tempColor->a = easingFunction(elapsed, startValue.w, diff.w, duration);
			*pColor = (Color)tempColor;
		}
		else
		{
			*pColor = (Color)targetValue;
		}
	}

};
*/

class Tween
{
public:
	typedef Vector<TweenValue> VectorType;

	Tween();
	Tween( float duration, EasingEquation easingEquation );

	void AddValue( const TweenValue& value );
	void AddValue( float* pValue, float targetValue );

	void SetEquation( EasingEquation easingEquation );
	void SetDuration( float duration );

	EasingEquation GetEasingEquation() const { return m_easingEquation; }
	float GetDuration() const { return m_duration; }
	bool IsFinished() const { return m_elapsed >= m_duration; }

	void Step( float dt );

	static TweenValue MoveTo( float* pValue, float targetValue );
	static TweenValue MoveBy( float* pValue, float amount );

	VectorType& GetTweenValues() const { return const_cast<VectorType&>(m_tweenValues); }

protected:
	VectorType			m_tweenValues;
	EasingFunctionPtr	m_easingFunction;
	EasingEquation		m_easingEquation;
	float				m_elapsed;
	float				m_duration;

};



class TweenGroup
{
public:
	typedef Vector<Tween*> VectorType;

	TweenGroup();
	
	Tween* CreateTween( float duration, EasingEquation easingEquation );

	void AddTween( Tween* tween );
	void Step( float dt );

protected:
	VectorType m_tweens;

};


CE_NAMESPACE_END

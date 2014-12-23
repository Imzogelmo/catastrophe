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
#include "Easing.h"

#include <fc/vector.h>

CE_NAMESPACE_BEGIN


struct TweenValue
{
	float*	pValue;
	float	targetValue;
	float	startValue;

	TweenValue() : pValue(null), targetValue(0.f), startValue(0.f) {}
	TweenValue( float* pValue, float targetValue ) :
		pValue(pValue), targetValue(targetValue), startValue(*pValue) {}

};


class Tween
{
public:
	typedef fc::vector<TweenValue> vec_type;

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

	vec_type& GetTweenValues() const { return const_cast<vec_type&>(m_tweenValues); }

protected:
	vec_type			m_tweenValues;
	EasingFunctionPtr	m_function;
	EasingEquation		m_easingEquation;
	float				m_elapsed;
	float				m_duration;

};



class TweenGroup
{
public:
	typedef fc::vector<Tween*> vec_type;

	TweenGroup();
	
	Tween* CreateTween( float duration, EasingEquation easingEquation );

	void AddTween( Tween* tween );
	void Step( float dt );

protected:
	vec_type m_tweens;

};


CE_NAMESPACE_END

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
#include "Catastrophe/Core/Math/Tween.h"


CE_NAMESPACE_BEGIN


// Tween

Tween::Tween() :
	m_tweenValues(),
	m_easingFunction(&Easing::Linear),
	m_easingEquation(EasingEquation_Linear),
	m_elapsed(0.f),
	m_duration(0.f)
{
}


Tween::Tween( float duration, EasingEquation easingEquation ) :
	m_tweenValues(),
	m_easingFunction(&Easing::Linear),
	m_easingEquation(EasingEquation_Linear),
	m_elapsed(0.f),
	m_duration(duration)
{
	SetEquation(easingEquation);
}


void Tween::SetEquation( EasingEquation easingEquation )
{
	m_easingEquation = easingEquation;
	m_easingFunction = Easing::GetFunction(easingEquation);
}


void Tween::SetDuration( float duration )
{
	m_duration = duration;
}


void Tween::AddValue( const TweenValue& value )
{
	m_tweenValues.Add(value);
}


void Tween::AddValue( float* pValue, float targetValue )
{
	m_tweenValues.Add( TweenValue(pValue, targetValue) );
}


void Tween::Step( float dt )
{
	m_elapsed += dt;

	for(TweenValue* it = m_tweenValues.begin(); it != m_tweenValues.end(); ++it)
	{
		float changeValue = it->targetValue - it->startValue;
		*it->pValue = m_easingFunction(m_elapsed, it->startValue, changeValue, m_duration);

		if( m_elapsed >= m_duration )
			*it->pValue = it->targetValue;
	}
}


TweenValue Tween::MoveTo( float* pValue, float targetValue )
{
	return TweenValue(pValue, targetValue);
}


TweenValue Tween::MoveBy( float* pValue, float amount )
{
	return TweenValue(pValue, pValue ? *pValue + amount : amount );
}



// TweenGroup

TweenGroup::TweenGroup() :
	m_tweens()
{
}


Tween* TweenGroup::CreateTween( float duration, EasingEquation easingEquation )
{
	Tween* tween = new Tween(duration, easingEquation);
	m_tweens.Add(tween);

	return tween;
}


void TweenGroup::AddTween( Tween* tween )
{
	if( tween != null )
		m_tweens.Add(tween);
}


void TweenGroup::Step( float dt )
{
	for( Tween** it = m_tweens.begin(); it != m_tweens.end(); )
	{
		Tween* tween = *it;

		tween->Step(dt);
		if( tween->IsFinished() )
		{
			delete tween;
			m_tweens.Erase(it);
		}
		else
			++it;
	}
}




CE_NAMESPACE_END

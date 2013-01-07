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

#include <fc/string.h>
#include <fc/math.h>

#include "Graphics/Animation.h"
#include "Graphics/AnimationSet.h"

CE_NAMESPACE_BEGIN


void Animation::SetAnimationSpeed( float frameSpeed )
{
	m_frameSpeed = fc::max<float>(frameSpeed, 1.f);
	m_frameCounter = fc::min<float>(m_frameSpeed, m_frameCounter);
}


void Animation::SetCurrentFrame( size_t frame )
{
	m_currentFrame = fc::min<size_t>( frame, (size_t)NumFrames() - 1 );
	m_frameCounter = 0;
}


void Animation::Update()
{
	if( !IsAnimated() || m_paused )
		return;

	++m_frameCounter;
	if( m_frameCounter >= m_frameSpeed )
	{
		//advance frame.
		m_frameCounter -= m_frameSpeed;

		const size_t maxFrames = NumFrames();
		if( ++m_currentFrame >= maxFrames )
		{
			if(m_loop)
			{
				m_currentFrame -= maxFrames;
			}
			else
			{
				--m_currentFrame;
			}
		}
	}
}


float Animation::GetAnimSpeed() const
{
	return m_frameSpeed;
}



CE_NAMESPACE_END


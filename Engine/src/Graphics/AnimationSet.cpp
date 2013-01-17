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

#include <fc/math.h>
#include "Graphics/Animation.h"
#include "Graphics/AnimationSet.h"

CE_NAMESPACE_BEGIN


AnimationSet::AnimationSet() :
	base_type(),
	m_animations(),
	m_current_anim(0)
{
}


void AnimationSet::Reserve( size_t capacity )
{
	m_animations.reserve(capacity);
}


bool AnimationSet::Empty() const
{
	return m_animations.empty();
}


size_t AnimationSet::Size() const
{
	return m_animations.size();
}


void AnimationSet::SetCurrentAnimation( size_t index )
{
	if(index < m_animations.size())
		m_current_anim = index;
}


Animation& AnimationSet::operator []( size_t index )
{
	CE_ASSERT(index < m_animations.size());
	return m_animations[index];
}


const Animation& AnimationSet::operator []( size_t index ) const
{
	CE_ASSERT(index < m_animations.size());
	return m_animations[index];
}


Animation& AnimationSet::GetCurrentAnimation()
{
	CE_ASSERT(!m_animations.empty());
	return m_animations[m_current_anim];
}


const Animation& AnimationSet::GetCurrentAnimation() const
{
	CE_ASSERT(!m_animations.empty());
	return m_animations[m_current_anim];
}


void AnimationSet::AddAnimation( const Animation& anim )
{
	m_animations.push_back(anim);
}


void AnimationSet::RemoveAnimation( size_t index )
{
	if(index < m_animations.size())
	{
		m_animations.erase_at(index);
		if( m_current_anim >= m_animations.size() )
			m_current_anim = 0;
	}
}



CE_NAMESPACE_END


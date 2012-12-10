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


AnimationSet::AnimationSet() :
	m_animations(),
	m_current_anim(0)
{
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


Animation* AnimationSet::GetAnimation( size_t index )
{
	if(index < m_animations.size())
		return m_animations[index];

	return 0;
}


const Animation* AnimationSet::GetAnimation( size_t index ) const
{
	if(index < m_animations.size())
		return m_animations[index];

	return 0;
}


Animation* AnimationSet::GetCurrentAnimation()
{
	if(!m_animations.empty())
		return m_animations[m_current_anim];

	return 0;
}


const Animation* AnimationSet::GetCurrentAnimation() const
{
	if(!m_animations.empty())
		return m_animations[m_current_anim];

	return 0;
}


void AnimationSet::AddAnimation( Animation* anim )
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


void AnimationSet::RemoveAnimation( Animation* anim )
{
	for( vec_type::iterator it = m_animations.begin(); it != m_animations.end(); ++it )
		if( *it == anim )
			RemoveAnimation( size_t(it - m_animations.begin()) );
}




CE_NAMESPACE_END


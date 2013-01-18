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

#include "Graphics/AnimationFrames.h"

CE_NAMESPACE_BEGIN


AnimationFrames::AnimationFrames( const Rectf* uv, int numberOfFrames ) :
	m_uv()
{
	SetFrameData(uv, numberOfFrames);
}


void AnimationFrames::Clear()
{
	m_uv.reset();
}


void AnimationFrames::SetFrameData( const Rectf* uv, int numberOfFrames )
{
	Clear();
	m_uv.resize(numberOfFrames);
	for( int i(0); i < numberOfFrames; ++i )
	{
		m_uv[i] = uv[i];
	}
}


void AnimationFrames::AddFrame( const Rectf& uv )
{
	m_uv.push_back(uv);
}


void AnimationFrames::RemoveFrame( size_t loc )
{
	if( loc < m_uv.size() )
	{
		m_uv.erase_at( loc );
	}
}



CE_NAMESPACE_END


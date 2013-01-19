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

#include <fc/fixed_vector.h>

#include "../Common.h"
#include "../Math/Rectf.h"

CE_NAMESPACE_BEGIN


class CE_API AnimationFrames
{
public:
	typedef fc::fixed_vector<Rectf, 1> vec_type;

	AnimationFrames() : m_uv() {}
	AnimationFrames( const Rectf* uv, int numberOfFrames );

	void Clear();
	void SetFrameData( const Rectf* uv, int numberOfFrames );
	void AddFrame( const Rectf& uv );
	void RemoveFrame( size_t loc );

	inline bool IsEmpty() const { return m_uv.empty(); }
	inline bool IsAnimated() const { return m_uv.has_overflowed(); }
	inline size_t NumFrames() const { return m_uv.size(); }
	
	inline const Rectf& GetUVRect( size_t index = 0 ) const { return m_uv[ index ]; }
	inline const Rectf* GetUVArray() const { return m_uv.data(); }

protected:
	vec_type		m_uv;
};


CE_NAMESPACE_END


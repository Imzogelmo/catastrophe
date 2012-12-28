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

#include "Texture.h"

CE_NAMESPACE_BEGIN


class CE_API AnimationFrames
{
public:
	typedef fc::fixed_vector<Rectf, 1> vec_type;

	AnimationFrames( const Texture* texture = 0 );
	AnimationFrames( const Texture* texture,
		const Rect& sourceRect,
		int numberOfFrames = 1,
		int frameOffsetX = 0,
		int frameOffsetY = 0
	);

	void Clear();

	void SetTexture( const Texture* texture );
	void SetFrameData( const Rectf* uv, int numberOfFrames );
	void SetFrameData( const Rect* sourceRectangles, int numberOfFrames );
	void SetFrameData( const Rect& sourceRect, int numberOfFrames = 1, int frameOffsetX = 0, int frameOffsetY = 0 );

	void AddFrame( const Rect& sourceRect );
	void AddFrame( const Rectf& uv );
	void RemoveFrame( size_t loc );

	inline bool IsAnimated() const { return m_uv.has_overflowed(); }
	inline size_t NumFrames() const { return m_uv.size(); }
	
	inline gluint GetTextureID() const { return m_texture->GetTextureID(); }
	inline const Rectf& GetUVRect( size_t index = 0 ) const { return m_uv[ index ]; }
	inline const Rectf* GetUVArray() const { return m_uv.data(); }
	inline const Texture* GetTexture() const { return m_texture; }

protected:
	const Texture*	m_texture;
	vec_type		m_uv;

};


CE_NAMESPACE_END


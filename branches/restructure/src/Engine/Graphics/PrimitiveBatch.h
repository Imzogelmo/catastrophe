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

#include <fc/vector.h>

#include "Common.h"
#include "Primitive.h"

CE_NAMESPACE_BEGIN


class CE_API PrimitiveBatch
{
public:
	typedef fc::vector<Primitive>		vec_type;

	PrimitiveBatch() : m_queue()
	{}

	void Reserve( size_t reserve );
	void Clear();

	size_t Size() const { return m_queue.size(); }
	size_t Capacity() const { return m_queue.capacity(); }
	size_t GetPrimCount() const { return m_queue.size(); }
	size_t GetVertexCount() const;

	void DrawPrimitive( const Primitive &primitive );

	void Begin();
	void Render();
	void Render( const Matrix& transformation );
	void End();

protected:
	vec_type	m_queue;
};



CE_NAMESPACE_END

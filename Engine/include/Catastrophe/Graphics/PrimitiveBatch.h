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
#include "Catastrophe/Core/Containers/Vector.h"
#include "Catastrophe/Graphics/Common.h"
#include "Primitive.h"


CE_NAMESPACE_BEGIN


class CE_API PrimitiveBatch
{
public:
	typedef Vector<Primitive>		vec_type;

	PrimitiveBatch() : m_queue()
	{}

	void Reserve( u32 reserve );
	void Clear();

	u32 Size() const { return m_queue.size(); }
	u32 Capacity() const { return m_queue.Capacity(); }
	u32 GetPrimCount() const { return m_queue.size(); }
	u32 GetVertexCount() const;

	void DrawPrimitive( const Primitive &primitive );

	void Begin();
	void Render();
	void Render( const Matrix& transformation );
	void End();

protected:
	vec_type	m_queue;
};



CE_NAMESPACE_END


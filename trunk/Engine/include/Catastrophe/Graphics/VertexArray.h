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
#include "Catastrophe/Core/Math/Rectf.h"
#include "Catastrophe/Core/Containers/Vector.h"

#include "Catastrophe/Graphics/Common.h"
#include "Catastrophe/Graphics/Vertex.h"
#include "Catastrophe/Graphics/PrimitiveType.h"

CE_NAMESPACE_BEGIN


template <class T>
class VertexArray
{
public:
	typedef T						vertex_type;
	typedef VertexArray<T>			this_type;
	typedef Vector<T>			vec_type;

	VertexArray() : m_vertices() {}
	VertexArray(const T* vertex, int num_vertices) : m_vertices()
		{
			AddVertex(vertex, num_vertices);
		}

	T* GetVertexData() { return m_vertices.data(); }
	const T* GetVertexData() const { return m_vertices.data(); }

	void Clear() { m_vertices.Clear(); }
	void Reserve(u32 capacity) { m_vertices.Reserve(capacity); }

	bool Empty() const		{ return m_vertices.Empty(); }
	u32 Size() const		{ return m_vertices.size(); }
	u32 Capacity() const	{ return m_vertices.Capacity(); }
	u32 GetVertexCount() const { return m_vertices.size(); }

	this_type& operator += (const this_type& v) { return Append(v); }
	this_type& Append(const this_type& v)
	{
		if(!v.Empty())
		{
			const u32 vSize = v.Size();
			T* ptr = m_vertices.AddUninitialized(vSize);
			for(u32 i(0); i < vSize; ++i)
			{
				*ptr++ = v.m_vertices[i];
			}
		}

		return *this;
	}

	void AddVertex(const T& vertex)
	{
		*m_vertices.AddUninitialized() = vertex;
	}

	void AddVertex(const T* vertex, int numVertices)
	{
		T * v = m_vertices.AddUninitialized((u32)numVertices);
		for(int i(0); i < numVertices; ++i)
		{
			v[i] = vertex[i];
		}
	}

protected:
	vec_type m_vertices;
};


CE_NAMESPACE_END



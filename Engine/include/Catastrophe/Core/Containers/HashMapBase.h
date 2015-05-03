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

#include "Catastrophe/Core/Memory.h"
#include "Catastrophe/Core/IteratorTraits.h"
#include "Catastrophe/Core/Containers/KeyValuePair.h"

#ifdef _MSC_VER
	#pragma warning(push)
	#pragma warning(disable: 4512) // assignment operator could not be generated
#endif

CE_NAMESPACE_BEGIN


template<class T>
struct HashEntry
{
	enum ENUM_TYPE(u32)
	{
		kUnusedIndex = u32(-1)
	};

	u32 hashIndex;
	u32 hashCount;
	T data;
};


template<class NodeType, class PairType>
struct HashNodeIterator
{
	typedef NodeType				NodeType;
	typedef PairType				PairType;
	typedef forward_iterator_tag    iterator_type;

	HashNodeIterator() : pNode(null) {}
	explicit HashNodeIterator(NodeType* node) : pNode(node) {}

	template<class U, class V>
	HashNodeIterator(const HashNodeIterator<U, V>& rhs) : pNode((NodeType*)rhs.pNode) {}

	PairType& operator*() const
	{
		CE_ASSERT(pNode != null);
		return pNode->data;
	}

	PairType* operator->() const
	{
		return &pNode->data;
	}

	HashNodeIterator& operator++()
	{
		CE_ASSERT(pNode != null);
		while((++pNode)->hashIndex == NodeType::kUnusedIndex) ;
		return *this;
	}

	HashNodeIterator operator++(int)
	{
		HashNodeIterator temp(*this);
		++(*this);
		return temp;
	}

	bool operator ==(const HashNodeIterator& rhs) const { return rhs.pNode == pNode; }
	bool operator !=(const HashNodeIterator& rhs) const { return rhs.pNode != pNode; }

	//protected:
	NodeType* pNode;

};


CE_NAMESPACE_END


#ifdef _MSC_VER
	#pragma warning(pop)
#endif

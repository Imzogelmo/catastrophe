//////////////////////////////////////
// Fast Container Library           //
// MIT License - Copyright (c) 2012 //
//////////////////////////////////////

#pragma once

#include "Catastrophe/Core/Common.h"
#include "Catastrophe/Core/IteratorTraits.h"


//std Iterator compatibility
namespace std { struct random_access_iterator_tag; }


CE_NAMESPACE_BEGIN


template <class T>
class ReverseIterator
{
public:
	typedef typename IteratorTraits<T>::iterator_category	iterator_category;
	typedef typename IteratorTraits<T>::IteratorType		IteratorType;
	typedef typename IteratorTraits<T>::ValueType			ValueType;
	typedef typename IteratorTraits<T>::Pointer				Pointer;
	typedef typename IteratorTraits<T>::Reference			Reference;
	typedef typename IteratorTraits<T>::DifferenceType		DifferenceType;

	ReverseIterator() : ptr() {}
	explicit ReverseIterator( const T& p ) : ptr(p) {}
	ReverseIterator( const ReverseIterator<T>& r ) : ptr(r.ptr) {}

	T base() const { return ptr; }

	Pointer	operator ->() const { T temp(ptr); return &*(--temp); }
	Reference operator *() const { T temp(ptr); return *(--temp); }
	Reference operator []( DifferenceType i ) const { return *(ptr + i); } 

	ReverseIterator<T>& operator ++() { --ptr; return *this; }
	ReverseIterator<T>& operator --() { ++ptr; return *this; }
	ReverseIterator<T>  operator ++(int) { ReverseIterator<T> temp(*this); --ptr; return temp; }
	ReverseIterator<T>  operator --(int) { ReverseIterator<T> temp(*this); ++ptr; return temp; }

	ReverseIterator<T>  operator + ( DifferenceType i ) const { return ReverseIterator<T>(ptr - i); }
	ReverseIterator<T>  operator - ( DifferenceType i ) const { return ReverseIterator<T>(ptr + i); }
	ReverseIterator<T>& operator +=( DifferenceType i ) { ptr -= i; return *this; }
	ReverseIterator<T>& operator -=( DifferenceType i ) { ptr += i; return *this; }

protected:
	T ptr;

};


//difference between two iterators of different pointer const-ness
template <class T1, class T2> inline
ptrdiff_t operator -( const ReverseIterator<T1>& a, const ReverseIterator<T2>& b )
{
	return b.base() - a.base();
}

template <class T1, class T2> inline
ptrdiff_t operator +( const ReverseIterator<T1>& a, const ReverseIterator<T2>& b )
{
	return b.base() + a.base();
}

template <class T> inline
ReverseIterator<T> operator -( ptrdiff_t i, const ReverseIterator<T>& x )
{
	return x.base() + i;
}

template <class T> inline
ReverseIterator<T> operator +( ptrdiff_t i, const ReverseIterator<T>& x )
{
	return x.base() - i;
}

template <class T1, class T2> inline
bool operator ==( const ReverseIterator<T1>& a, const ReverseIterator<T2>& b )
{
	return a.base() == b.base();
}

template <class T1, class T2> inline
bool operator !=( const ReverseIterator<T1>& a, const ReverseIterator<T2>& b )
{
	return a.base() != b.base();
}

template <class T1, class T2> inline
bool operator <( const ReverseIterator<T1>& a, const ReverseIterator<T2>& b )
{
	return a.base() < b.base();
}

template <class T1, class T2> inline
bool operator >( const ReverseIterator<T1>& a, const ReverseIterator<T2>& b )
{
	return a.base() > b.base();
}

template <class T1, class T2> inline
bool operator <=( const ReverseIterator<T1>& a, const ReverseIterator<T2>& b )
{
	return a.base() <= b.base();
}

template <class T1, class T2> inline
bool operator >=( const ReverseIterator<T1>& a, const ReverseIterator<T2>& b )
{
	return a.base() >= b.base();
}




template <class Container>
class BackInsertIterator
{
public:
	typedef output_iterator_tag						IteratorType;
	typedef Container								ContainerType;

	BackInsertIterator() : ptr() {}
	explicit BackInsertIterator( Container& c ) : ptr(&c) {}

	BackInsertIterator<Container>& operator =( const typename Container::ElementType& value )
	{
		ptr->Add(value);
		return *this;
	}

	BackInsertIterator<Container>& operator*() { return *this; }
	BackInsertIterator<Container>& operator ++() { return *this; }
	BackInsertIterator<Container>  operator ++(int) { return *this; }

protected:
	Container* ptr;

};


template <class Container>
class FrontInsertIterator
{
public:
	typedef output_iterator_tag						IteratorType;
	typedef Container								ContainerType;

	FrontInsertIterator() : ptr() {}
	explicit FrontInsertIterator( Container& c ) : ptr(&c) {}

	FrontInsertIterator<Container>& operator =( const typename Container::ElementType& value )
	{
		ptr->PushFront(value);
		return *this;
	}

	FrontInsertIterator<Container>& operator*() { return *this; }
	FrontInsertIterator<Container>& operator ++() { return *this; }
	FrontInsertIterator<Container>  operator ++(int) { return *this; }

protected:
	Container* ptr;

};


template <class Container>
class InsertIterator
{
public:
	typedef std::output_iterator_tag				iterator_category;
	typedef output_iterator_tag						IteratorType;
	typedef Container								ContainerType;
	typedef typename Container::ElementType			ElementType;
	typedef typename Container::Iterator			Iterator;

	InsertIterator() : ptr() {}
	explicit InsertIterator( Container& c, Iterator i ) : ptr(&c), it(i) {}

	InsertIterator<Container>& operator =( const ElementType& value )
	{
		it = ptr->Insert(it, value);
		++it;
		return *this;
	}

	InsertIterator<Container>& operator*() { return *this; }
	InsertIterator<Container>& operator ++() { return *this; }
	InsertIterator<Container>  operator ++(int) { return *this; }

protected:
	Container* ptr;
	Iterator it;

};


CE_NAMESPACE_END

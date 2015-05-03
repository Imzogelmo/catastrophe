//////////////////////////////////////
// Fast Container Library           //
// MIT License - Copyright (c) 2012 //
//////////////////////////////////////

#pragma once

//#include "Catastrophe/Core/Common.h"


// iterator_category | IteratorType
//
// Note that we define iterator_category here as std::*_iterator_tag
// so that all containers and iterators can be used with stl by including
// the standard header <Iterator>. Internally fc will always use IteratorType
// so as not to require any dependencies on external libraries.


//std Iterator compatability
namespace std { struct random_access_iterator_tag; }
namespace std { struct bidirectional_iterator_tag; }
namespace std { struct forward_iterator_tag; }
namespace std { struct output_iterator_tag; }
namespace std { struct input_iterator_tag; }


CE_NAMESPACE_BEGIN


//c++ standard Iterator types
struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};
struct contiguous_iterator_tag : public random_access_iterator_tag {};


template<class Iterator>
struct IteratorTraits
{
	typedef ptrdiff_t								DifferenceType;
	typedef typename Iterator::ValueType			ValueType;
	typedef typename Iterator::pointer				Pointer;
	typedef typename Iterator::reference			Reference;
	typedef typename Iterator::IteratorType			IteratorType;
	typedef typename Iterator::iterator_category	iterator_category;
};


template <class T>
struct IteratorTraits<T*>
{
	typedef T								ValueType;
	typedef T*								Pointer;
	typedef T&								Reference;
	typedef ptrdiff_t						DifferenceType;
	typedef contiguous_iterator_tag			IteratorType;
	typedef std::random_access_iterator_tag iterator_category;

};


template <class T>
struct IteratorTraits<const T*>
{
	typedef T								ValueType;
	typedef const T*						Pointer;
	typedef const T&						Reference;
	typedef ptrdiff_t						DifferenceType;
	typedef contiguous_iterator_tag			IteratorType;
	typedef std::random_access_iterator_tag iterator_category;

};


template<class T1, class T2>
struct IteratorRange
{
	typedef T1 FirstType;
	typedef T2 SecondType;

	IteratorRange( const T1& first, const T2& last ) : first(first), last(last) {}

	template <typename U, typename V>
	IteratorRange( const IteratorRange<U, V>& p ) : first(p.first), last(p.last) {}

	bool Empty() const { return first == last; }

	T1 first;
	T2 last;
};


template<class T1, class T2> inline
bool operator ==( const IteratorRange<T1, T2>& a, const IteratorRange<T1, T2>& b )
{
	return a.first == b.first && a.last == b.last;
}

template<class T1, class T2> inline
bool operator !=( const IteratorRange<T1, T2>& a, const IteratorRange<T1, T2>& b )
{
	return !(a == b);
}

//template <class T1, class T2> struct is_pod< IteratorRange<T1, T2> >
//	: integral_constant<is_pod<T1>::value && is_pod<T2>::value> { };




namespace Internal
{
	template <class ForwardIterator> inline
	ptrdiff_t IteratorDistance( ForwardIterator first, ForwardIterator last, forward_iterator_tag )
	{
		ptrdiff_t d(0);
		for( ; first != last; ++first ) ++d;
		return d;
	}

	template <class RandomAccessIterator> inline
	ptrdiff_t IteratorDistance( RandomAccessIterator first, RandomAccessIterator last, random_access_iterator_tag )
	{
		return last - first;
	}

	template <class ForwardIterator> inline
	void IteratorAdvance( ForwardIterator& it, ptrdiff_t n, input_iterator_tag )
	{
		CE_ASSERT(n > 0);
		while( n-- ) ++it;
	}

	template <class BidirectionalIterator> inline
	void IteratorAdvance( BidirectionalIterator& it, ptrdiff_t n, bidirectional_iterator_tag )
	{
		if( n < 0 ) while( n-- ) --it;
		else while( n-- ) ++it;
	}

	template <class RandomAccessIterator> inline
	void IteratorAdvance( RandomAccessIterator& it, ptrdiff_t n, random_access_iterator_tag )
	{
		it += n;
	}

}


// distance

template <class InputIterator> inline
ptrdiff_t IteratorDistance( InputIterator first, InputIterator last )
{
	return Internal::IteratorDistance( first, last, typename IteratorTraits<InputIterator>::IteratorType() );
}

// IteratorAdvance

template <class InputIterator> inline
void IteratorAdvance( InputIterator& it, ptrdiff_t n )
{
	return Internal::IteratorAdvance( it, n, typename IteratorTraits<InputIterator>::IteratorType() );
}





CE_NAMESPACE_END

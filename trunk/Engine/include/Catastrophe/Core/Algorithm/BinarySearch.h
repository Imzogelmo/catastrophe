//////////////////////////////////////
// Fast Container Library           //
// MIT License - Copyright (c) 2012 //
//////////////////////////////////////

#pragma once

#include "Catastrophe/Core/Common.h"
#include "Catastrophe/Core/IteratorTraits.h"
#include "Catastrophe/Core/TypeTraits.h"


CE_NAMESPACE_BEGIN


// binary_search.h (binary search operations on sorted ranges)
//
// lower_bound
// upper_bound
// equal_range
// binary_find
// binary_search

namespace Algorithm
{

	// lower_bound

	template <class ForwardIterator, class T, class Compare> inline
	ForwardIterator LowerBound( ForwardIterator first, ForwardIterator last, const T& value, Compare compare )
	{
		typedef typename IteratorTraits<ForwardIterator>::DifferenceType DifferenceType;
		DifferenceType dist = IteratorDistance(first, last);

		while( dist > 0 )
		{
			const DifferenceType step = dist >> 1;
			ForwardIterator mid = first;
			IteratorAdvance(mid, step);

			if( compare(*mid, value) )
				first = ++mid, dist -= step + 1;
			else
				dist = step;
		}

		return first;
	}

	template <class ForwardIterator, class T> inline
	ForwardIterator LowerBound( ForwardIterator first, ForwardIterator last, const T& value )
	{
		typedef typename IteratorTraits<ForwardIterator>::DifferenceType DifferenceType;
		DifferenceType dist = IteratorDistance(first, last);

		while( dist > 0 )
		{
			const DifferenceType step = dist >> 1;
			ForwardIterator mid = first;
			IteratorAdvance(mid, step);

			if( *mid < value )
				first = ++mid, dist -= step + 1;
			else
				dist = step;
		}

		return first;
	}


	// upper_bound

	template <class ForwardIterator, class T, class Compare> inline
	ForwardIterator UpperBound( ForwardIterator first, ForwardIterator last, const T& value, Compare compare )
	{
		typedef typename IteratorTraits<ForwardIterator>::DifferenceType DifferenceType;
		DifferenceType dist = IteratorDistance(first, last);

		while( dist > 0 )
		{
			const DifferenceType step = dist >> 1;
			ForwardIterator mid = first;
			IteratorAdvance(mid, step);

			if( !compare(value, *mid) )
				first = ++mid, dist -= step + 1;
			else
				dist = step;
		}

		return first;
	}

	template <class ForwardIterator, class T> inline
	ForwardIterator UpperBound( ForwardIterator first, ForwardIterator last, const T& value )
	{
		typedef typename IteratorTraits<ForwardIterator>::DifferenceType DifferenceType;
		DifferenceType dist = IteratorDistance(first, last);

		while( dist > 0 )
		{
			const DifferenceType step = dist >> 1;
			ForwardIterator mid = first;
			IteratorAdvance(mid, step);

			if( !(value < *mid) )
				first = ++mid, dist -= step + 1;
			else
				dist = step;
		}

		return first;
	}


	// equal_range

	template <class ForwardIterator, class T, class Compare> inline
	IteratorRange<ForwardIterator, ForwardIterator>
	EqualRange( ForwardIterator first, ForwardIterator last, const T& value, Compare compare )
	{
		ForwardIterator it1 = LowerBound( first, last, value, compare );
		ForwardIterator it2 = UpperBound( it1, last, value, compare );
		return IteratorRange<ForwardIterator, ForwardIterator>(it1, it2);
	}

	template <class ForwardIterator, class T> inline
	IteratorRange<ForwardIterator, ForwardIterator>
	EqualRange( ForwardIterator first, ForwardIterator last, const T& value )
	{
		ForwardIterator it1 = LowerBound( first, last, value );
		ForwardIterator it2 = UpperBound( it1, last, value );
		return IteratorRange<ForwardIterator, ForwardIterator>(it1, it2);
	}


	// binary_find

	template <class InputIterator, class T> inline
	InputIterator BinaryFind( InputIterator first, InputIterator last, const T& value )
	{
		first = LowerBound(first, last, value);
		return (first != last && !(value < *first)) ? first : last;
	}

	template <class InputIterator, class T, class Compare> inline
	InputIterator BinaryFind( InputIterator first, InputIterator last, const T& value, Compare compare )
	{
		first = LowerBound(first, last, value, compare);
		return (first != last && !(value < *first)) ? first : last;
	}


	// binary_search

	template <class InputIterator, class T> inline
	bool BinarySearch( InputIterator first, InputIterator last, const T& value )
	{
		return BinaryFind(first, last, value) == last ? false : true;
	}

	template <class InputIterator, class T, class Compare> inline
	bool BinarySearch( InputIterator first, InputIterator last, const T& value, Compare compare )
	{
		return BinaryFind(first, last, value, compare) == last ? false : true;
	}

} // Algorithm


CE_NAMESPACE_END
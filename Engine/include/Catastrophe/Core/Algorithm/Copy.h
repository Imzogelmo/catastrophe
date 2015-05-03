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
#include "Catastrophe/Core/TypeTraits.h"
#include "Catastrophe/Core/IteratorTraits.h"
#include "Catastrophe/Core/Functional.h"
#include "Catastrophe/Core/Algorithm/AlgoBase.h"


// Copy.h (modifying sequence operations)
//
// Swap				(algobase.h)
// swap_ranges		(algobase.h)
// IterSwap			(algobase.h)
// Fill				(algobase.h)
// Fill				(algobase.h)
// FillValues		(algobase.h)
// Copy				(algobase.h)
// copy_n			(algobase.h)
// CopyBackward		(algobase.h)
// copy_if
// remove_copy
// remove_copy_if
// remove
// remove_if
// unique
// unique_copy
// replace
// replace_if
// replace_copy_if
// reverse
// reverse_copy	    (algobase.h)
// generate
// generate_n
// rotate
// rotate_copy
// transform

CE_NAMESPACE_BEGIN


namespace Algorithm
{

	// copy_if

	template <class InputIterator, class OutputIterator, class UnaryPredicate> inline
		OutputIterator CopyIf( InputIterator first, InputIterator last, OutputIterator result, UnaryPredicate predicate )
		{
			for( ; first != last; ++first )
				if( predicate(*first) )
					*result = *first, ++result;
			return result;
		}


	// remove_copy

	template <class InputIterator, class OutputIterator, class T> inline
		OutputIterator RemoveCopy( InputIterator first, InputIterator last, OutputIterator result, const T& value )
		{
			for( ; first != last; ++first )
				if( !(*first == value) )
					*result = *first, ++result;
			return result;
		}


	// remove_copy_if

	template <class InputIterator, class OutputIterator, class UnaryPredicate> inline
		OutputIterator RemoveCopyIf( InputIterator first, InputIterator last, OutputIterator result, UnaryPredicate predicate )
		{
			for( ; first != last; ++first )
				if( !predicate(*first) )
					*result = *first, ++result;
			return result;
		}


	// remove

	template <class ForwardIterator, class T> inline
		ForwardIterator Remove( ForwardIterator first, ForwardIterator last, const T& value )
		{
			first = Find<ForwardIterator, T>( first, last, value );
			if( first != last )
			{
				ForwardIterator it(first);
				return RemoveCopy( ++it, last, first, value );
			}

			return first;
		}


	// remove_if

	template <class ForwardIterator, class UnaryPredicate> inline
		ForwardIterator RemoveIf( ForwardIterator first, ForwardIterator last, UnaryPredicate predicate )
		{
			first = FindIf<ForwardIterator, UnaryPredicate>( first, last, predicate );
			if( first != last )
			{
				ForwardIterator it(first);
				return RemoveCopyIf<ForwardIterator, ForwardIterator, UnaryPredicate>( ++it, last, first, predicate );
			}

			return first;
		}


	// RemoveAll

	template <class ForwardIterator, class T> inline
		ForwardIterator RemoveAll( ForwardIterator first, ForwardIterator last, const T& value )
		{
			first = Find<ForwardIterator, T>( first, last, value );
			if( first != last )
			{
				ForwardIterator next = first;
				++next;

				for( ; next != last; ++next)
					if(*next != value)
						*first++ = *next;
			}

			return first;
		}


	/// RemoveIndices
	///
	/// Removes all elements at positions in the range first, last that correspond to the
	/// values of range first2, last2. The indices are expected to be sorted from least
	/// to highest and contain no duplicate values, otherwise the behavior is undefined.
	/// 
	/// Example:
	///     int array[10] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
	///     int removeAt[2] = { 2, 4 };
	/// 
	///     int* end_of_a = RemoveIndices(array, array + 10, removeAt, removeAt + 2);
	///     // a is now equal to { 9, 8, 6, 4, 3, 2, 1, 0 };
	///
	template <class ForwardIterator, class T> inline
		ForwardIterator RemoveIndices( ForwardIterator first1, ForwardIterator last1, const T* first2, const T* last2)
		{
			if( LIKELY(first2 != last2 && first1 != last1) )
			{
				ForwardIterator next1 = first1 + *first2;

				for( const T* next2 = first2 + 1; next2 != last2; ++next2 )
				{
					next1 = Copy(first1 + (*first2 + 1), first1 + *next2, next1);
					first2 = next2;
				}

				return Copy(first1 + (*first2 + 1), last1, next1);
			}

			return last1;
		}


	// unique

	template <class ForwardIterator, class BinaryPredicate> inline
		ForwardIterator Unique( ForwardIterator first, ForwardIterator last, BinaryPredicate predicate )
		{
			ForwardIterator result = first;

			if( LIKELY(first != last) )
			{
				while( ++first != last )
					if( !predicate(*result, *first) )
						*++result = *first;
			}

			return ++result;
		}

	template <class ForwardIterator> inline
		ForwardIterator Unique( ForwardIterator first, ForwardIterator last )
		{
			return Unique(first, last,
				EqualTo<typename IteratorTraits<BidirectionalIterator>::ValueType>());
		}


	// unique_copy

	template <class InputIterator, class OutputIterator, class BinaryPredicate> inline
		OutputIterator UniqueCopy( InputIterator first, InputIterator last, OutputIterator result, BinaryPredicate predicate )
		{
			if( LIKELY(first != last) )
			{
				*result = *first;
				while( ++first != last )
					if( !predicate(*result, *first) )
						*(++result) = *first;

				return ++result;
			}
			return result;
		}

	template <class InputIterator, class OutputIterator> inline
		OutputIterator UniqueCopy( InputIterator first, InputIterator last, OutputIterator result )
		{
			if( LIKELY(first != last) )
			{
				*result = *first;
				while( ++first != last )
					if( !(*result == *first) )
						*(++result) = *first;

				return ++result;
			}
			return result;
		}


	// replace

	template <class ForwardIterator, class T> inline
		void Replace( ForwardIterator first, ForwardIterator last, const T& oldValue, const T& newValue )
		{
			for( ; first != last; ++first )
				if( *first == oldValue )
					*first = newValue;
		}


	// replace_if

	template <class ForwardIterator, class UnaryPredicate, class T> inline
		void ReplaceIf( ForwardIterator first, ForwardIterator last, UnaryPredicate predicate, const T& newValue )
		{
			for( ; first != last; ++first )
				if( predicate(*first) )
					*first = newValue;
		}


	// replace_copy

	template <class InputIterator, class OutputIterator, class T> inline
		OutputIterator ReplaceCopy( InputIterator first, InputIterator last, OutputIterator result,
		const T& oldValue, const T& newValue )
		{
			for( ; first != last; ++first, ++result )
				*result = (*first == oldValue) ? newValue : *first;
			return result;
		}


	// replace_copy_if

	template <class InputIterator, class OutputIterator, class T, class UnaryPredicate> inline
		OutputIterator ReplaceCopyIf( InputIterator first, InputIterator last, OutputIterator result,
		UnaryPredicate predicate, const T& newValue )
		{
			for( ; first != last; ++first, ++result )
				*result = predicate(*first) ? newValue : *first;
			return result;
		}


	// reverse

	namespace Internal
	{
		template <class RandomAccessIterator> inline
		void Reverse( RandomAccessIterator first, RandomAccessIterator last, random_access_iterator_tag )
		{
			for( ; first < --last; ++first )
				IterSwap(first, last);
		}

		template <class BidirectionalIterator> inline
		void Reverse( BidirectionalIterator first, BidirectionalIterator last, bidirectional_iterator_tag )
		{
			for( ; (first != last) && (first != --last); ++first )
				IterSwap(first, last);
		}
	}

	template <class BidirectionalIterator> inline
		void Reverse( BidirectionalIterator first, BidirectionalIterator last )
		{
			Internal::Reverse( first, last,
				typename IteratorTraits<BidirectionalIterator>::IteratorType() );
		}


	// generate

	template <class ForwardIterator, class Generator> inline
		void Generate( ForwardIterator first, ForwardIterator last, Generator generator )
		{
			for( ; first != last; ++first )
				*first = generator();
		}


	// generate_n

	template <class ForwardIterator, class Generator> inline
		ForwardIterator Generate( ForwardIterator first, u32 numElements, Generator generator )
		{
			for( u32 i(0); i < numElements; ++first, --numElements )
				*first = generator();
			return first;
		}


	namespace Internal
	{
		// rotate
		// todo: this can be optimized...

		template <class ForwardIterator> inline
		void Rotate( ForwardIterator first, ForwardIterator middle, ForwardIterator last, forward_iterator_tag )
		{
			for( ForwardIterator next = middle; first != next; )
			{
				Swap(*first++, *next++);
				if( next == last )
					next = middle;
				else if( first == middle )
					middle = next;
			}
		}
	}


	// rotate

	template <class ForwardIterator> inline
		void Rotate( ForwardIterator first, ForwardIterator middle, ForwardIterator last )
		{
			Internal::Rotate( first, middle, last,
				typename IteratorTraits<ForwardIterator>::IteratorType() );
		}


	// rotate_copy

	template <class ForwardIterator, class OutputIterator> inline
		OutputIterator RotateCopy( ForwardIterator first, ForwardIterator middle, ForwardIterator last, OutputIterator result )
		{
			return Copy( first, middle, Copy(middle, last, result) );
		}


	// transform (unary)

	template <class InputIterator, class OutputIterator, class UnaryOperation> inline
		OutputIterator Transform( InputIterator first, InputIterator last, OutputIterator result, UnaryOperation op )
		{
			for( ; first != last; ++first, ++result )
				*result = op(*first);
			return result;
		}


	// transform (binary)

	template <class InputIterator1, class InputIterator2, class OutputIterator, class BinaryOperation> inline
		OutputIterator Transform( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2,
		OutputIterator result, BinaryOperation op )
		{
			for( ; first1 != last1; ++first1, ++first2, ++result )
				*result = op(*first1, *first2);
			return result;
		}

} // Algorithm


CE_NAMESPACE_END



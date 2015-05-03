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
#include "Catastrophe/Core/IteratorTraits.h"
#include "Catastrophe/Core/TypeTraits.h"
#include "Catastrophe/Core/Functional.h"
#include "Catastrophe/Core/Algorithm/AlgoBase.h"


CE_NAMESPACE_BEGIN


// search.h (non-modifying sequence operations)
//
// all_of
// any_of
// none_of
// for_each
// count
// count_if
// mismatch
// Equal				(algobase.h)
// Find					(algobase.h)
// FindIf				(algobase.h)
// find_if_not
// find_end
// FindFirstOf
// FindFirstNotOf
// FindLastOf
// FindLastNotOf
// adjacent_find
// search
// search_n


namespace Algorithm
{

	// all_of

	template <class InputIterator, class UnaryPredicate> inline
	bool AllOf( InputIterator first, InputIterator last, UnaryPredicate predicate )
	{
		for( ; first != last; ++first )
			if( !predicate(*first) )
				return false;
		return true;
	}


	// any_of

	template <class InputIterator, class UnaryPredicate> inline
	bool AnyOf( InputIterator first, InputIterator last, UnaryPredicate predicate )
	{
		for( ; first != last; ++first )
			if( predicate(*first) )
				return true;
		return false;
	}


	// none_of

	template <class InputIterator, class UnaryPredicate> inline
	bool NoneOf( InputIterator first, InputIterator last, UnaryPredicate predicate )
	{
		for( ; first != last; ++first )
			if( predicate(*first) )
				return false;
		return true;
	}


	// for_each

	template <class InputIterator, class UnaryFunction> inline
	void ForEach( InputIterator first, InputIterator last, UnaryFunction unaryFunction )
	{
		for( ; first != last; ++first )
			unaryFunction(*first);
	}


	// count

	template <class InputIterator, class T> inline
	u32 Count( InputIterator first, InputIterator last, const T& value )
	{
		u32 result = 0;
		for( ; first != last; ++first )
			if( *first == value )
				++result;

		return result;
	}


	// count_if

	template <class InputIterator, class UnaryPredicate> inline
	u32 CountIf( InputIterator first, InputIterator last, UnaryPredicate predicate )
	{
		u32 result = 0;
		for( ; first != last; ++first )
			if( predicate(*first) )
				++result;

		return result;
	}


	// mismatch

	template <class InputIterator, class BinaryPredicate> inline
	IteratorRange<InputIterator, InputIterator>
	Mismatch( InputIterator first1, InputIterator last1, InputIterator first2, BinaryPredicate predicate )
	{
		while( first1 != last1 && predicate(*first1, *first2) )
			++first1, ++first2;

		return IteratorRange<InputIterator, InputIterator>(first1, first2);
	}

	template <class InputIterator> inline
	IteratorRange<InputIterator, InputIterator> Mismatch( InputIterator first1, InputIterator last1, InputIterator first2 )
	{
		while( first1 != last1 && *first1 == *first2 )
			++first1, ++first2;

		return IteratorRange<InputIterator, InputIterator>(first1, first2);
	}


	// find_if_not

	template<class InputIterator, class UnaryPredicate>
	InputIterator FindIfNot( InputIterator first, InputIterator last, UnaryPredicate predicate )
	{
		while( (first != last) && predicate(*first) )
			++first;
		return first;
	}


	// FindFirstOf

	template <class ForwardIterator1, class ForwardIterator2> inline
	ForwardIterator1 FindFirstOf( ForwardIterator1 first1, ForwardIterator1 last1,
								   ForwardIterator2 first2, ForwardIterator2 last2 )
	{
		for( ForwardIterator2 i; first1 != last1; ++first1 )
		{
			for( i = first2; i != last2; ++i )
			{
				if( *first1 == *i )
					return first1;
			}
		}

		return last1;
	}

	template <class ForwardIterator, class T> inline
	ForwardIterator FindFirstOf( ForwardIterator first, ForwardIterator last, const T& value )
	{
		return Find(first, last, value);
	}


	// FindFirstNotOf

	template <class ForwardIterator1, class ForwardIterator2> inline
	ForwardIterator1 FindFirstNotOf( ForwardIterator1 first1, ForwardIterator1 last1,
									   ForwardIterator2 first2, ForwardIterator2 last2 )
	{
		for( ForwardIterator2 i; first1 != last1; ++first1 )
		{
			for( i = first2; i != last2; ++i )
			{
				if( *i == *first1 )
					break;
			}
			if( i == last2 )
				return first1;
		}

		return first1;
	}

	template <class ForwardIterator, class T> inline
	ForwardIterator FindFirstNotOf( ForwardIterator first, ForwardIterator last, const T& value )
	{
		while( first != last && *first == value ) ++first;
		return first;
	}


	// FindLastOf

	template <class BidirectionalIterator1, class BidirectionalIterator2> inline
	BidirectionalIterator1 FindLastOf( BidirectionalIterator1 first1, BidirectionalIterator1 last1,
										BidirectionalIterator2 first2, BidirectionalIterator2 last2 )
	{
		while( first1 != last1 )
		{
			--last1;
			for( BidirectionalIterator2 i = first2; i != last2; ++i )
			{
				if( *i == *last1 )
					return last1;
			}
		}

		return first1;
	}

	template <class BidirectionalIterator, class T> inline
	BidirectionalIterator FindLastOf( BidirectionalIterator first, BidirectionalIterator last, const T& value )
	{
		while( first != last && *--last != value ) ;
		return last;
	}


	// FindLastNotOf

	template <class BidirectionalIterator1, class BidirectionalIterator2> inline
	BidirectionalIterator1 FindLastNotOf( BidirectionalIterator1 first1, BidirectionalIterator1 last1,
											BidirectionalIterator2 first2, BidirectionalIterator2 last2 )
	{
		BidirectionalIterator2 i;
		while( first1 != last1 )
		{
			--last1;
			for( i = first2; i != last2; ++i )
			{
				if( *i == *last1 )
					break;
			}
			if( i == last2 )
				return last1;
		}

		return first1;
	}

	template <class BidirectionalIterator, class T> inline
	BidirectionalIterator FindLastNotOf( BidirectionalIterator first, BidirectionalIterator last, const T& value )
	{
		while( first != last && *--last == value ) ;
		return last;
	}


	// adjacent_find

	template <class ForwardIterator, class BinaryPredicate> inline
	ForwardIterator AdjacentFind( ForwardIterator first, ForwardIterator last, BinaryPredicate predicate )
	{
		if( LIKELY(first != last) )
		{
			ForwardIterator next = first;
			++next;
			while( next != last )
			{
				if( predicate(*first, *next) )
					return first;

				first = next;
				++next;
			}
		}
		return last;
	}

	template <class ForwardIterator> inline
	ForwardIterator AdjacentFind( ForwardIterator first, ForwardIterator last )
	{
		typedef typename EqualTo<typename IteratorTraits<ForwardIterator>::ValueType> BinaryPredicateType;
		return AdjacentFind(first, last, BinaryPredicateType());
	}



	namespace Internal
	{
		// search

		template <class ForwardIterator1, class ForwardIterator2, class BinaryPredicate> inline
			ForwardIterator1 Search( ForwardIterator1 first1, ForwardIterator1 last1,
			ForwardIterator2 first2, ForwardIterator2 last2, BinaryPredicate predicate,
			forward_iterator_tag, forward_iterator_tag )
		{
			if( UNLIKELY(first2 == last2) )
				return first1;

			ForwardIterator1 a;
			ForwardIterator2 b;

			while( first1 != last1 )
			{
				// Find next occurance of first value in sequence
				while( first1 != last1 && !predicate(*first1, *first2) )
					++first1;

				if( first1 != last1 )
				{
					a = first1;
					b = first2;

					do {
						if( ++a == last1 ) return last1;
						if( ++b == last2 ) return first1;
					} while( predicate(*a, *b) );

					++first1;
				}
			}

			return last1;
		}

		template <class RandomAccessIterator1, class RandomAccessIterator2, class BinaryPredicate> inline
			RandomAccessIterator1 Search( RandomAccessIterator1 first1, RandomAccessIterator1 last1,
			RandomAccessIterator2 first2, RandomAccessIterator2 last2, BinaryPredicate predicate,
			random_access_iterator_tag, random_access_iterator_tag )
		{
			typedef typename IteratorTraits<RandomAccessIterator1>::DifferenceType difference_type1;
			typedef typename IteratorTraits<RandomAccessIterator2>::DifferenceType difference_type2;
			const difference_type1 dist1 = difference_type1(last1 - first1);
			const difference_type2 dist2 = difference_type2(last2 - first2);

			if( UNLIKELY(dist2 == 0) )
				return first1;

			if( LIKELY(!(dist1 < dist2)) )
			{
				const RandomAccessIterator1 endFirst = last1 - dist2;
				for( ; first1 != endFirst; ++first1 )
				{
					if( predicate(*first1, *first2) )
					{
						RandomAccessIterator1 a = first1 + 1;
						RandomAccessIterator2 b = first2 + 1;
						for( ; ; ++a, ++b )
						{
							if( b == last2 )
								return first1; // match found

							if( !predicate(*a, *b) )
								break;
						}
					}
				}
			}

			return last1;
		}

	} //internal


	template <class ForwardIterator1, class ForwardIterator2, class BinaryPredicate> inline
	ForwardIterator1 Search( ForwardIterator1 first1, ForwardIterator1 last1,
							ForwardIterator2 first2, ForwardIterator2 last2, BinaryPredicate predicate )
	{
		return Internal::Search<ForwardIterator1, ForwardIterator2, BinaryPredicate>( first1, last1, first2, last2, predicate,
			typename IteratorTraits<ForwardIterator1>::IteratorType(),
			typename IteratorTraits<ForwardIterator2>::IteratorType()
			);
	}

	template <class ForwardIterator1, class ForwardIterator2> inline
	ForwardIterator1 Search( ForwardIterator1 first1, ForwardIterator1 last1,
							ForwardIterator2 first2, ForwardIterator2 last2 )
	{
		return Internal::Search( first1, last1, first2, last2, EqualTo< typename IteratorTraits<ForwardIterator1>::ValueType >(),
			typename IteratorTraits<ForwardIterator1>::IteratorType(),
			typename IteratorTraits<ForwardIterator2>::IteratorType()
			);
	}


	namespace Internal
	{
		// search_n

		template <class ForwardIterator, class Size, class T, class BinaryPredicate> inline
			ForwardIterator search_n( ForwardIterator first, ForwardIterator last,
			Size n, const T& value, BinaryPredicate predicate, forward_iterator_tag )
		{
			while( first != last )
			{
				if( predicate(*first, value) )
				{
					ForwardIterator f = first;
					Size i;
					for( i = 1; i < n; ++i )
					{
						if( ++first == last || !predicate(*first, value) )
							break;
					}
					if( i == n )
						return f;
				}
				else ++first;
			}

			return last;
		}

		// Much faster version of search_n which we can specialize
		// for random access iterators.

		template <class RandomAccessIterator, class Size, class T, class BinaryPredicate> inline
			RandomAccessIterator search_n( RandomAccessIterator first,
			RandomAccessIterator last, Size n, const T& value, BinaryPredicate predicate, random_access_iterator_tag )
		{
			if( n < 2 )
				return Find(first, last, value);

			Size skip = (n - 1);
			Size remainder;
			RandomAccessIterator lookAhead = first + skip;
			RandomAccessIterator backTrack;

			for( ; lookAhead < last; lookAhead += n )
			{
				if( predicate(*lookAhead, value) )
				{
					remainder = skip;
					for( backTrack = lookAhead - 1; predicate(*backTrack, value); --backTrack )
					{
						if( --remainder == 0 )
							return (lookAhead - skip);
					}

					while( *(++lookAhead) == value )
					{
						if( --remainder == 0 )
							return (lookAhead - skip);
					}

					// no match found and lookAhead is already optimally placed at
					// end of tested range, so do nothing.
				}
			}

			return last;
		}

		template <class ForwardIterator, class Size, class T> inline
			ForwardIterator search_n( ForwardIterator first, ForwardIterator last,
			Size n, const T& value, forward_iterator_tag )
		{
			while( first != last )
			{
				if( *first == value )
				{
					ForwardIterator f = first;
					Size i;
					for( i = 1; i < n; ++i )
					{
						if( ++first == last || !(*first == value) )
							break;
					}
					if( i == n )
						return f;
				}
				else ++first;
			}

			return last;
		}


		// Much faster version of search_n which we can specialize
		// for random access iterators.

		template <class RandomAccessIterator, class Size, class T> inline
			RandomAccessIterator search_n( RandomAccessIterator first,
			RandomAccessIterator last, Size n, const T& value, random_access_iterator_tag )
		{
			if( n < 2 )
				return Find(first, last, value);

			Size skip = (n - 1);
			Size remainder;
			RandomAccessIterator lookAhead = first + skip;
			RandomAccessIterator backTrack;

			for( ; lookAhead < last; lookAhead += n )
			{
				if( *lookAhead == value )
				{
					remainder = skip;
					for( backTrack = lookAhead - 1; *backTrack == value; --backTrack )
					{
						if( --remainder == 0 )
							return (lookAhead - skip);
					}

					while( *(++lookAhead) == value )
					{
						if( --remainder == 0 )
							return (lookAhead - skip);
					}

					// no match found and lookAhead is already optimally placed at
					// end of tested range, so do nothing.
				}
			}

			return last;
		}

	}



	// search_n

	template <class InputIterator, class Size, class T, class BinaryPredicate> FORCEINLINE
	InputIterator search_n( InputIterator first, InputIterator last, Size n, const T& value, BinaryPredicate predicate )
	{
		return Internal::search_n( first, last, n, value, predicate,
			typename IteratorTraits<InputIterator>::IteratorType() );
	}

	template <class InputIterator, class Size, class T> FORCEINLINE
	InputIterator search_n( InputIterator first, InputIterator last, Size n, const T& value )
	{
		return Internal::search_n( first, last, n, value,
			typename IteratorTraits<InputIterator>::IteratorType() );
	}

} // Algorithm


CE_NAMESPACE_END


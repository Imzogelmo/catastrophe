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
#include "Catastrophe/Core/Functional.h"
#include "Catastrophe/Core/Algorithm/AlgoBase.h"
#include "Catastrophe/Core/Algorithm/Heap.h"
#include "Catastrophe/Core/Algorithm/Merge.h"

// sort.h
//
// sort
// quick_sort
// insertion_sort
// merge_sort
// stable_sort
// heap_sort			(heap.h)
// partial_sort			(heap.h)
// partial_sort_copy	(heap.h)
// is_sorted
// is_sorted_until

CE_NAMESPACE_BEGIN

namespace Algorithm
{

	namespace Internal
	{
		template <class BidirectionalIterator, class Compare> inline
		void quick_sort_impl( BidirectionalIterator first, BidirectionalIterator last, Compare compare )
		{
			if( first != last )
			{
				BidirectionalIterator left = first;
				BidirectionalIterator right = --last;
				BidirectionalIterator pivot = left++;

				while( left != right )
				{
					if( compare(*left, *pivot) )
						++left;
					else
					{
						while( left != right && compare(*pivot, *right) )
							--right;
						iter_swap( left, right );
					}
				}

				--left;
				iter_swap( first, left );

				quick_sort_impl<BidirectionalIterator, Compare>( first, left, compare );
				quick_sort_impl<BidirectionalIterator, Compare>( right, last, compare );
			}
		}

		// @very fast median quicksort algorithm taken from http: //homepages.ihug.co.nz/~aurora76/Malc/
		template <class T, class Compare> inline
		void medianquicksortimpl( T* a, int l, int r, Compare compare )
		{
			enum{ Ideal = 16 };
			while (r - l > Ideal)
			{
				int i = (l+r)>>1, j = r-1;
				//pick median of 3 items as splitter
				if (compare(a[i], a[l])) Swap(a[i], a[l]);
				if (compare(a[j], a[l])) Swap(a[j], a[l]);
				if (compare(a[j], a[i])) Swap(a[j], a[i]);
				const T temp = a[i];
				i = l;
				for (;;) //partition items
				{
					do ++i; while (compare(a[i], temp));
					do --j; while (compare(temp, a[j]));
					if (j <= i) break;
					Swap(a[i], a[j]);
				}
				if (i-l <= r-i)
				{
					medianquicksortimpl(a, l, i, compare);
					l = i;
				}
				else
				{
					medianquicksortimpl(a, i, r, compare);
					r = i;
				}
			}
		}

		template <class Iter, class T, class Compare> inline
		void insertionsortimpl( Iter first, Iter last, T*, Compare compare )
		{
			for( Iter it = first + 1; it < last; ++it )
			{
				T value = *it;
				Iter next = it;
				for( ; next > first && compare(value, *(next - 1)); --next )
				{
					*next = *(next - 1);
				}
				*next = value;
			}
		}

		template <class Iter, class T> inline
		void insertionsortimpl( Iter first, Iter last, T* )
		{
			for( Iter it = first + 1; it < last; ++it )
			{
				T value = *it;
				Iter next = it;
				for( ; next > first && (value < *(next - 1)); --next )
				{
					*next = *(next - 1);
				}
				*next = value;
			}
		}

		template <class RandomAccessIterator, class Compare> inline
		void Sort( RandomAccessIterator first, RandomAccessIterator last, Compare compare )
		{
			quick_sort_impl( first, last, compare );
		}


		template <class RandomAccessIterator, class Size, class Compare> inline
		void merge_sort_impl( RandomAccessIterator first, RandomAccessIterator last, Size n, Compare compare )
		{
			typename IteratorTraits<RandomAccessIterator>::Pointer p = 0;
			if( n < 32 )
			{
				insertionsortimpl( first, last, p, compare );
			}
			else
			{
				Size dist = n >> 1;
				RandomAccessIterator mid = first + dist;

				merge_sort_impl<RandomAccessIterator, Size, Compare>( first, mid, dist, compare );
				merge_sort_impl<RandomAccessIterator, Size, Compare>( mid, last, dist, compare );
				InplaceMerge<RandomAccessIterator, Compare>( first, mid, last, compare );
			}
		}

		template <class RandomAccessIterator, class Size > inline
		void merge_sort_impl( RandomAccessIterator first, RandomAccessIterator last, Size n )
		{
			typename IteratorTraits<RandomAccessIterator>::Pointer p = 0;
			if( n < 32 )
			{
				insertionsortimpl( first, last, p );
			}
			else
			{
				Size dist = n >> 1;
				RandomAccessIterator mid = first + dist;

				merge_sort_impl<RandomAccessIterator, Size>( first, mid, dist );
				merge_sort_impl<RandomAccessIterator, Size>( mid, last, dist );
				InplaceMerge<RandomAccessIterator>( first, mid, last );
			}
		}

		/*
		template <class RandomAccessIterator, class Size, class T > inline
		void merge_sort_buffer_impl( RandomAccessIterator first, RandomAccessIterator last, Size n, T* buffer )
		{
			typename IteratorTraits<RandomAccessIterator>::pointer p = 0;
			if( n < 32 )
			{
				insertionsortimpl( first, last, p );
			}
			else
			{
				Size dist = n >> 1;
				RandomAccessIterator mid = first + dist;

				merge_sort_buffer_impl<RandomAccessIterator, Size>( first, mid, dist );
				merge_sort_buffer_impl<RandomAccessIterator, Size>( mid, last, dist );
				inplace_merge_buffer<RandomAccessIterator>( first, mid, last );
			}
		}
		*/

	} //internal


	// insertion_sort

	template <class Iter, class Compare> inline
		void InsertionSort( Iter first, Iter last, Compare compare )
		{
			Internal::insertionsortimpl( first, last, typename IteratorTraits<Iter>::Pointer(), compare );
		}

	template <class Iter> inline
		void InsertionSort( Iter first, Iter last )
		{
			InsertionSort( first, last,
				Less<typename IteratorTraits<Iter>::ValueType>() );
		}


	// sort

	template <class RandomAccessIterator, class Compare> inline
		void Sort( RandomAccessIterator first, RandomAccessIterator last, Compare compare )
		{
			//internal::sort( first, last, compare );
			///*
			ptrdiff_t dist = ptrdiff_t(last - first);
			CE_ASSERT(dist >= 0);

			enum { Ideal = 32 };
			if( dist > Ideal )
				Internal::medianquicksortimpl( &*first, 0, dist, compare );

			InsertionSort( first, last, compare );
			//*/
		}

	template <class RandomAccessIterator> inline
		void Sort( RandomAccessIterator first, RandomAccessIterator last )
		{
			Sort( first, last, Less<typename IteratorTraits<RandomAccessIterator>::ValueType>() );
		}


	// quick_sort

	template <class BidirectionalIterator, class Compare> inline
		void QuickSort( BidirectionalIterator first, BidirectionalIterator last, Compare compare )
		{
			quick_sort_impl( first, last, compare );
		}

	template <class BidirectionalIterator> inline
		void QuickSort( BidirectionalIterator first, BidirectionalIterator last )
		{
			quick_sort_impl( first, last,
				Less< typename IteratorTraits<BidirectionalIterator>::ValueType >() );
		}


	// merge_sort

	template <class RandomAccessIterator, class Compare> inline
		void MergeSort( RandomAccessIterator first, RandomAccessIterator last, Compare compare )
		{
			typedef typename IteratorTraits<RandomAccessIterator>::DifferenceType DifferenceType;
			const DifferenceType n = DifferenceType(last - first);

			Internal::merge_sort_impl<RandomAccessIterator, DifferenceType, Compare>( first, last, n, compare );
		}


	template <class RandomAccessIterator> inline
		void MergeSort( RandomAccessIterator first, RandomAccessIterator last )
		{
			typedef typename IteratorTraits<RandomAccessIterator>::DifferenceType DifferenceType;
			const DifferenceType n = DifferenceType(last - first);

			Internal::merge_sort_impl<RandomAccessIterator, DifferenceType>( first, last, n );
		}


	// stable_sort

	template <class RandomAccessIterator, class Compare> inline
		void StableSort( RandomAccessIterator first, RandomAccessIterator last, Compare compare )
		{
			MergeSort<RandomAccessIterator, Compare>( first, last, compare );
		}


	template <class RandomAccessIterator> inline
		void StableSort( RandomAccessIterator first, RandomAccessIterator last )
		{
			MergeSort<RandomAccessIterator>( first, last );
		}


	// is_sorted_until

	template <class ForwardIterator, class Compare> inline
		ForwardIterator IsSortedUntil( ForwardIterator first, ForwardIterator last, Compare compare )
		{
			if( LIKELY(first != last) )
				for( ForwardIterator prev = first; ++first != last && !compare(*first, *prev); prev = first ) ;
			return first;
		}

	template <class ForwardIterator> inline
		ForwardIterator IsSortedUntil( ForwardIterator first, ForwardIterator last )
		{
			if( LIKELY(first != last) )
				for( ForwardIterator prev = first; ++first != last && !(*first < *prev); prev = first ) ;
			return first;
		}


	// is_sorted

	template <class ForwardIterator, class Compare> inline
		bool IsSorted( ForwardIterator first, ForwardIterator last, Compare compare )
		{
			return IsSortedUntil<ForwardIterator, Compare>(first, last, compare) == last;
		}

	template <class ForwardIterator> inline
		bool IsSorted( ForwardIterator first, ForwardIterator last )
		{
			return IsSortedUntil<ForwardIterator>(first, last) == last;
		}

} // Algorithm


CE_NAMESPACE_END

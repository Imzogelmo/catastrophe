//////////////////////////////////////
// Fast Container Library           //
// MIT License - Copyright (c) 2012 //
//////////////////////////////////////

#pragma once

#include "Catastrophe/Core/Common.h"
#include "Catastrophe/Core/IteratorTraits.h"


// heap.h
//
// Implements a standard binary heap structure using random-access and sequential data.
// Binary heaps generally have an overall excellent worst-case of O(n log n).
// *Note* (This is very close to reference implementation and not micro-optimized in any meaningful way.)
// 
//      [0]
//     /   \
//   [1]   [2]
//   / \ 
// [3] [4]
//
//
// make_heap
// push_heap
// pop_heap
// is_heap
// is_heap_until
// sort_heap
// heap_sort
// partial_sort
// partial_sort_copy

CE_NAMESPACE_BEGIN

namespace Algorithm
{

	namespace Internal
	{
		template <class RandomAccessIterator, class T, class Compare> inline
		void PromoteHeap( RandomAccessIterator first, u32 hole, u32 top, const T& value, Compare compare )
		{
			u32 parent = (hole - 1) >> 1;
			while( hole > top && compare(first[parent], value) )
			{
				first[hole] = first[parent];
				hole = parent;
				parent = (parent - 1) >> 1;
			}

			first[hole] = value;
		}

		template <class RandomAccessIterator, class T> inline
		void PromoteHeap( RandomAccessIterator first, u32 hole, u32 top, const T& value )
		{
			u32 parent = (hole - 1) >> 1;
			while( hole > top && first[parent] < value )
			{
				first[hole] = first[parent];
				hole = parent;
				parent = (parent - 1) >> 1;
			}

			first[hole] = value;
		}

		template <class RandomAccessIterator, class T, class Compare> inline
		void AdjustHeap( RandomAccessIterator first, const u32 heapSize, u32 hole, const T& value, Compare compare ) 
		{
			u32 child = hole * 2 + 2;
			u32 top = hole;

			while( child < heapSize )
			{
				if( compare(first[child], first[child - 1]) )
					child--;
				first[hole] = first[child];
				hole = child;
				child = child * 2 + 2;
			}

			if( child == heapSize )
			{
				first[hole] = first[child - 1];
				hole = child - 1;
			}

			PromoteHeap<RandomAccessIterator, T, Compare>( first, hole, top, value, compare );
		}

		template <class RandomAccessIterator, class T> inline
		void AdjustHeap( RandomAccessIterator first, const u32 heapSize, u32 hole, const T& value ) 
		{
			u32 child = hole * 2 + 2;
			u32 top = hole;

			while( child < heapSize )
			{
				if( first[child] < first[child - 1] )
					child--;
				first[hole] = first[child];
				hole = child;
				child = child * 2 + 2;
			}

			if( child == heapSize )
			{
				first[hole] = first[child - 1];
				hole = child - 1;
			}

			PromoteHeap<RandomAccessIterator, T>( first, hole, top, value );
		}

	} //internal


	// MakeHeap

	template <class RandomAccessIterator, class Compare> inline
		void MakeHeap( RandomAccessIterator first, RandomAccessIterator last, Compare compare )
		{
			const u32 heapSize = u32(last - first);
			if( heapSize > 1 )
			{
				for( u32 parent = (heapSize >> 1) - 1; ; --parent )
				{
					typedef typename IteratorTraits<RandomAccessIterator>::ValueType ValueType;
					const ValueType temp(first[parent]);

					// heapify values by traversing downwards to the bottom.
					Internal::AdjustHeap<RandomAccessIterator, ValueType, Compare>( first, heapSize, parent, temp, compare ); 
					if( parent == 0 )
						break;
				}
			}
		}

	template <class RandomAccessIterator>
		void MakeHeap( RandomAccessIterator first, RandomAccessIterator last )
		{
			const u32 heapSize = u32(last - first);
			if( heapSize > 1 )
			{
				for( u32 parent = (heapSize >> 1) - 1; ; --parent )
				{
					typedef typename IteratorTraits<RandomAccessIterator>::ValueType ValueType;
					const ValueType temp(first[parent]);

					// heapify values by traversing downwards to the bottom.
					Internal::AdjustHeap<RandomAccessIterator, ValueType>( first, heapSize, parent, temp ); 
					if( parent == 0 )
						break;
				}
			}
		}


	// push_heap

	template <class RandomAccessIterator, class Compare>
		void PushHeap( RandomAccessIterator first, RandomAccessIterator last, Compare compare )
		{
			const u32 heapSize = u32(last - first - 1);

			typedef typename IteratorTraits<RandomAccessIterator>::ValueType ValueType;
			const ValueType temp(first[heapSize]);

			// use previous heapsize of [first. last-1) and trickle upwards from bottom, placing value.
			Internal::PromoteHeap<RandomAccessIterator, ValueType, Compare>( first, heapSize, 0, temp, compare );
		}

	template <class RandomAccessIterator>
		void PushHeap( RandomAccessIterator first, RandomAccessIterator last )
		{
			const u32 heapSize = u32(last - first - 1);

			typedef typename IteratorTraits<RandomAccessIterator>::ValueType ValueType;
			const ValueType temp(first[heapSize]);

			// use previous heapsize of [first. last-1) and trickle upwards from bottom, placing value.
			Internal::PromoteHeap<RandomAccessIterator, ValueType>( first, heapSize, 0, temp );
		}


	// pop_heap

	template <class RandomAccessIterator, class Compare> inline
		void PopHeap( RandomAccessIterator first, RandomAccessIterator last, Compare compare )
		{
			CE_ASSERT(first != last);

			// swap bottom with value, pop last, and adjust the heap.
			typedef typename IteratorTraits<RandomAccessIterator>::ValueType ValueType;
			const ValueType temp(*(--last));
			*last = *first;

			Internal::AdjustHeap<RandomAccessIterator, ValueType, Compare>( first, u32(last - first), 0, temp, compare );
		}

	template <class RandomAccessIterator>
		void PopHeap( RandomAccessIterator first, RandomAccessIterator last )
		{
			CE_ASSERT(first != last);

			// swap bottom with value, pop last, and adjust the heap.
			typedef typename IteratorTraits<RandomAccessIterator>::ValueType ValueType;
			const ValueType temp(*(--last));
			*last = *first;

			Internal::AdjustHeap<RandomAccessIterator, ValueType>( first, u32(last - first), 0, temp );
		}


	// is_heap_until

	template <class RandomAccessIterator, class Compare>
		RandomAccessIterator IsHeapUntil( RandomAccessIterator first, RandomAccessIterator last, Compare compare )
		{
			int i = 0;
			for( RandomAccessIterator child = first + 1; child < last; ++child, ++i )
			{
				if( compare(*first, *child) )
					return child;
				if( (i & 1) != 0 )
					++first;
			}

			return last;
		}

	template <class RandomAccessIterator>
		RandomAccessIterator IsHeapUntil( RandomAccessIterator first, RandomAccessIterator last )
		{
			int i = 0;
			for( RandomAccessIterator child = first + 1; child < last; ++child, ++i )
			{
				if( *first < *child )
					return child;
				if( (i & 1) != 0 )
					++first;
			}

			return last;
		}


	// is_heap

	template <class RandomAccessIterator, class Compare>
		bool IsHeap( RandomAccessIterator first, RandomAccessIterator last, Compare compare )
		{
			return IsHeapUntil<RandomAccessIterator, Compare>(first, last) == last;
		}

	template <class RandomAccessIterator>
		bool IsHeap( RandomAccessIterator first, RandomAccessIterator last )
		{
			return IsHeapUntil<RandomAccessIterator>(first, last) == last;
		}


	// SortHeap

	template <class RandomAccessIterator, class Compare>
		void SortHeap( RandomAccessIterator first, RandomAccessIterator last, Compare compare )
		{
			for( ; first != last; --last )
				PopHeap<RandomAccessIterator, Compare>( first, last, compare );
		}

	template <class RandomAccessIterator>
		void SortHeap( RandomAccessIterator first, RandomAccessIterator last )
		{
			for( ; first != last; --last )
				PopHeap<RandomAccessIterator>( first, last );
		}


	// heap_sort

	template <class RandomAccessIterator, class Compare> inline
		void HeapSort( RandomAccessIterator first, RandomAccessIterator last, Compare compare )
		{
			MakeHeap<RandomAccessIterator, Compare>( first, last, compare );
			SortHeap<RandomAccessIterator, Compare>( first, last, compare );
		}

	template <class RandomAccessIterator> inline
		void HeapSort( RandomAccessIterator first, RandomAccessIterator last )
		{
			MakeHeap<RandomAccessIterator>( first, last );
			SortHeap<RandomAccessIterator>( first, last );
		}


	// partial_sort

	template <class RandomAccessIterator, class Compare> inline
		void PartialSort( RandomAccessIterator first, RandomAccessIterator mid, RandomAccessIterator last, Compare compare )
		{
			MakeHeap<RandomAccessIterator, Compare>( first, mid, compare );

			for( RandomAccessIterator i = mid; i != last; ++i )
			{
				if( compare(*i, *first) )
				{
					// iterate through the remaining range and simply pop the max heap with the value at 'next'
					// and place it at at the current position in the unsorted range [mid, last).

					typedef typename IteratorTraits<RandomAccessIterator>::ValueType ValueType;
					const ValueType temp(*i);
					*i = *first;

					Internal::AdjustHeap<RandomAccessIterator, ValueType, Compare>( first, u32(mid - first), 0, temp, compare );
				}
			}

			SortHeap<RandomAccessIterator, Compare>( first, mid, compare );
		}

	template <class RandomAccessIterator> inline
		void PartialSort( RandomAccessIterator first, RandomAccessIterator mid, RandomAccessIterator last )
		{
			MakeHeap<RandomAccessIterator>( first, mid );

			for( RandomAccessIterator i = mid; i != last; ++i )
			{
				if( *i < *first )
				{
					typedef typename IteratorTraits<RandomAccessIterator>::ValueType ValueType;
					const ValueType temp(*i);
					*i = *first;

					Internal::AdjustHeap<RandomAccessIterator, ValueType>( first, u32(mid - first), 0, temp );
				}
			}

			SortHeap<RandomAccessIterator>( first, mid );
		}


	// partial_sort_copy

	template <class InputIterator, class RandomAccessIterator, class Compare> inline
		RandomAccessIterator PartialSortCopy( InputIterator first, InputIterator last,
		RandomAccessIterator resultFirst, RandomAccessIterator resultLast, Compare compare )
		{
			RandomAccessIterator resultMid = resultFirst;
			while( first != last && resultMid != resultLast )
			{
				*resultMid = *first;
				++first;
				++resultMid;
			}

			typedef typename IteratorTraits<RandomAccessIterator>::ValueType ValueType;
			const u32 numElements = u32(resultMid - resultFirst);

			MakeHeap<RandomAccessIterator, Compare>( resultFirst, resultMid, compare );

			for( ; first != last; ++first )
			{
				if( compare(*first, *resultFirst) )
				{
					const ValueType temp(*first);
					Internal::AdjustHeap<RandomAccessIterator, ValueType, Compare>( resultFirst, numElements, 0, temp, compare );
				}
			}

			SortHeap<RandomAccessIterator, Compare>( resultFirst, resultMid, compare );
			return resultMid;
		}

	template <class InputIterator, class RandomAccessIterator> inline
		RandomAccessIterator PartialSortCopy( InputIterator first, InputIterator last,
		RandomAccessIterator resultFirst, RandomAccessIterator resultLast )
		{
			RandomAccessIterator resultMid = resultFirst;
			while( first != last && resultMid != resultLast )
			{
				*resultMid = *first;
				++first;
				++resultMid;
			}

			typedef typename IteratorTraits<RandomAccessIterator>::ValueType ValueType;
			const u32 numElements = u32(resultMid - resultFirst);

			MakeHeap<RandomAccessIterator>( resultFirst, resultMid );

			for( ; first != last; ++first )
			{
				if( *first < *resultFirst )
				{
					const ValueType temp(*first);
					Internal::AdjustHeap<RandomAccessIterator, ValueType>( resultFirst, numElements, 0, temp );
				}
			}

			SortHeap<RandomAccessIterator>( resultFirst, resultMid );
			return resultMid;
		}

} // Algorithm


CE_NAMESPACE_END

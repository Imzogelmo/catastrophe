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


FC_NAMESPACE_BEGIN


// partition.h (partitioning operations)
//
// partition
// partition_copy
// stable_partition
// stable_partition_copy
// partition_point
// is_partitioned

namespace Algorithm
{

	// partition

	template <class BidirectionalIterator, class UnaryPredicate> inline
		BidirectionalIterator Partition( BidirectionalIterator first, BidirectionalIterator last, UnaryPredicate predicate )
		{
			for( ; ; ++first )
			{
				while( first != last && predicate(*first) ) ++first;
				if( first == last )
					break;

				while( first != --last && !predicate(*last) ) ;
				if( first == last )
					break;

				IterSwap( first, last );
			}

			return first;
		}


	// partition_copy

	template <class InputIterator, class OutputIterator1, class OutputIterator2, class UnaryPredicate> inline
		IteratorRange<OutputIterator1, OutputIterator2> PartitionCopy( InputIterator first, InputIterator last,
		OutputIterator1 outTrue, OutputIterator2 outFalse, UnaryPredicate predicate )
		{
			for( ; first != last; ++first )
			{
				if( predicate(*first) )
				{
					*outTrue = *first;
					++outTrue;
				}
				else
				{
					*outFalse = *first;
					++outFalse;
				}
			}

			return IteratorRange<OutputIterator1, OutputIterator2>(outTrue, outFalse);
		}


	// stable_partition_copy

	template <class InputIterator, class OutputIterator1, class OutputIterator2, class UnaryPredicate>
		IteratorRange<OutputIterator1,OutputIterator2> StablePartitionCopy( InputIterator first,
		InputIterator last, OutputIterator1 outTrue, OutputIterator2 outFalse, UnaryPredicate predicate )
		{
			// partition_copy is stable;
			return PartitionCopy<InputIterator, OutputIterator1, OutputIterator2, UnaryPredicate>
				( first, last, outTrue, outFalse, predicate );
		}


	// stable_partition

	template <class BidirectionalIterator, class UnaryPredicate> inline
		BidirectionalIterator stable_partition( BidirectionalIterator first, BidirectionalIterator last, UnaryPredicate predicate )
		{
			/*
			typedef typename iterator_traits<BidirectionalIterator>::value_type value_type;
			fc::temporary_buffer<value_type> buffer( first, last );

			BidirectionalIterator p1;
			p1 = copy_if<value_type*, BidirectionalIterator, UnaryPredicate>( buffer.begin(), buffer.end(), first, predicate );
			remove_copy_if<value_type*, BidirectionalIterator, UnaryPredicate>( buffer.begin(), buffer.end(), p1, predicate );

			return p1;
			*/

			typedef typename iterator_traits<BidirectionalIterator>::value_type value_type;
			fc::temporary_buffer<value_type> a( first, last );
			fc::temporary_buffer<value_type> b( first, last );

			IteratorRange<value_type*, value_type*> p = StablePartitionCopy<BidirectionalIterator, value_type*, value_type*, UnaryPredicate>
				( first, last, a.begin(), b.begin(), predicate );

			first = Copy( a.begin(), p.first, first );
			Copy( b.begin(), p.last, first );

			return first;
		}


	// partition_point

	template <class ForwardIterator, class UnaryPredicate> inline
		ForwardIterator PartitionPoint( ForwardIterator first, ForwardIterator last, UnaryPredicate predicate )
		{
			size_t dist = fc::distance( first, last );
			while( first != last )
			{
				size_t mid = dist >> 1;
				ForwardIterator f = first;
				fc::advance(f, mid);

				if( predicate(*f) )
				{
					first = ++f;
					dist -= mid + 1;
				}
				else
				{
					last = f;
					dist = mid;
				}
			}

			return first;
		}


	// is_partitioned

	template <class InputIterator, class UnaryPredicate> inline
		bool IsPartitioned( InputIterator first, InputIterator last, UnaryPredicate predicate )
		{
			for( ; first != last && predicate(*first); ++first ) ;
			for( ; first != last; ++first )
				if( predicate(*first) )
					return false;

			return true;
		}

} // Algorithm


FC_NAMESPACE_END
//////////////////////////////////////
// Fast Container Library           //
// MIT License - Copyright (c) 2012 //
//////////////////////////////////////

#pragma once

#include "Algobase.h"

CE_NAMESPACE_BEGIN


// merge.h (set operations on sorted ranges)
//
// merge
// inplace_merge
// inplace_merge_buffer
// set_difference
// set_intersection
// set_symmetric_difference
// set_union
// includes
// merge_sort					(sort.h)


namespace Algorithm
{

	// merge

	template <class InputIterator1, class InputIterator2, class OutputIterator> inline
		OutputIterator Merge( InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2, OutputIterator result )
		{
			while( first1 != last1 && first2 != last2 )
			{
				if( *first2 < *first1 )
				{
					*result = *first2;
					++first2;
				}
				else
				{
					*result = *first1;
					++first1;
				}

				++result;
			}

			result = copy( first1, last1, result );
			result = copy( first2, last2, result );
			return result;
		}

	template <class InputIterator1, class InputIterator2, class OutputIterator, class Compare> inline
		OutputIterator Merge( InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2, OutputIterator result, Compare compare )
		{
			while( first1 != last1 && first2 != last2 )
			{
				if( compare(*first2, *first1) )
				{
					*result = *first2;
					++first2;
				}
				else
				{
					*result = *first1;
					++first1;
				}

				++result;
			}

			result = copy( first1, last1, result );
			result = copy( first2, last2, result );
			return result;
		}


	// inplace_merge

	template <class RandomAccessIterator, class Compare>
		void InplaceMerge( RandomAccessIterator first, RandomAccessIterator mid, RandomAccessIterator last, Compare compare )
		{
			typedef typename iterator_traits<RandomAccessIterator>::value_type value_type;
			fc::temporary_buffer<value_type> a( first, mid );
			fc::temporary_buffer<value_type> b( mid, last );

			Merge<value_type*, value_type*, RandomAccessIterator, Compare>( a.begin(), a.end(), b.begin(), b.end(), first, compare );
		}

	template <class RandomAccessIterator>
		void InplaceMerge( RandomAccessIterator first, RandomAccessIterator mid, RandomAccessIterator last )
		{
			typedef typename iterator_traits<RandomAccessIterator>::value_type value_type;
			fc::temporary_buffer<value_type> a( first, mid );
			fc::temporary_buffer<value_type> b( mid, last );

			Merge<value_type*, value_type*, RandomAccessIterator>( a.begin(), a.end(), b.begin(), b.end(), first );
		}


	// inplace_merge_buffer

	template <class RandomAccessIterator, class T, class Compare>
		void InplaceMergeBuffer( RandomAccessIterator first, RandomAccessIterator mid, RandomAccessIterator last, T* buffer, Compare compare )
		{
			T* bufferMid = fc::copy( first, mid, buffer );
			T* bufferEnd = fc::copy( mid, last, bufferMid );

			Merge<T*, T*, RandomAccessIterator, Compare>( buffer, bufferMid, bufferMid, bufferEnd, first, compare );
		}

	template <class RandomAccessIterator, class T>
		void InplaceMergeBuffer( RandomAccessIterator first, RandomAccessIterator mid, RandomAccessIterator last, T* buffer )
		{
			T* bufferMid = fc::copy( first, mid, buffer );
			T* bufferEnd = fc::copy( mid, last, bufferMid );

			Merge<T*, T*, RandomAccessIterator>( buffer, bufferMid, bufferMid, bufferEnd, first );
		}


	// set_difference

	template <class InputIterator1, class InputIterator2, class OutputIterator> inline
		OutputIterator SetDifference( InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2, OutputIterator result )
		{
			while( first1 != last1 && first2 != last2 )
			{
				if( *first1 < *first2 )
				{
					*result = *first1;
					++first1;
					++result;
				}
				else if( *first2 < *first1 )
				{
					++first2;
				}
				else
				{
					++first1;
					++first2;
				}
			}

			return copy( first1, last1, result );
		}

	template<class InputIterator1, class InputIterator2, class OutputIterator, class Compare> inline
		OutputIterator SetDifference( InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2, OutputIterator result, Compare compare )
		{
			while( first1 != last1 && first2 != last2 )
			{
				if( compare(*first1, *first2) )
				{
					*result = *first1;
					++first1;
					++result;
				}
				else if( compare(*first2, *first1) )
				{
					++first2;
				}
				else
				{
					++first1;
					++first2;
				}
			}

			return copy( first1, last1, result );
		}


	// set_intersection

	template <class InputIterator1, class InputIterator2, class OutputIterator> inline
		OutputIterator SetIntersection( InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2, OutputIterator result )
		{
			while( first1 != last1 && first2 != last2 )
			{
				if( *first1 < *first2 ) ++first1;
				else if( *first2 < *first1 ) ++first2;
				else
				{
					*result = *first1;
					++first1;
					++first2;
					++result;
				}
			}

			return result;
		}

	template<class InputIterator1, class InputIterator2, class OutputIterator, class Compare> inline
		OutputIterator SetIntersection( InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2, OutputIterator result, Compare compare )
		{
			while( first1 != last1 && first2 != last2 )
			{
				if( compare(*first1, *first2) ) ++first1;
				else if( compare(*first2, *first1) ) ++first2;
				else
				{
					*result = *first1;
					++first1;
					++first2;
					++result;
				}
			}

			return result;
		}


	// set_symmetric_difference

	template <class InputIterator1, class InputIterator2, class OutputIterator> inline
		OutputIterator SetSymmetricDifference( InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2, OutputIterator result )
		{
			while( first1 != last1 && first2 != last2 )
			{
				if( *first1 < *first2 )
				{
					*result = *first1;
					++first1;
					++result;
				}
				else if( *first2 < *first1 )
				{
					*result = *first2;
					++first2;
					++result;
				}
				else
				{
					++first1;
					++first2;
				}
			}

			result = copy( first1, last1, result );
			result = copy( first2, last2, result );
			return result;
		}

	template <class InputIterator1, class InputIterator2, class OutputIterator, class Compare> inline
		OutputIterator SetSymmetricDifference( InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2, OutputIterator result, Compare compare )
		{
			while( first1 != last1 && first2 != last2 )
			{
				if( compare(*first1, *first2) )
				{
					*result = *first1;
					++first1;
					++result;
				}
				else if( compare(*first2, *first1) )
				{
					*result = *first2;
					++first2;
					++result;
				}
				else
				{
					++first1;
					++first2;
				}
			}

			result = copy( first1, last1, result );
			result = copy( first2, last2, result );
			return result;
		}


	// set_union

	template <class InputIterator1, class InputIterator2, class OutputIterator> inline
		OutputIterator SetUnion( InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2, OutputIterator result )
		{
			for( ; first1 != last1 && first2 != last2; ++result )
			{
				if( *first1 < *first2 )
				{
					*result = *first1;
					++first1;
				}
				else if( *first2 < *first1 )
				{
					*result = *first2;
					++first2;
				}
				else
				{
					*result = *first1;
					++first1;
					++first2;
				}
			}

			result = copy( first1, last1, result );
			result = copy( first2, last2, result );
			return result;
		}

	template <class InputIterator1, class InputIterator2, class OutputIterator, class Compare> inline
		OutputIterator SetUnion( InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2, OutputIterator result, Compare compare )
		{
			for( ; first1 != last1 && first2 != last2; ++result )
			{
				if( compare(*first1, *first2) )
				{
					*result = *first1;
					++first1;
				}
				else if( compare(*first2, *first1) )
				{
					*result = *first2;
					++first2;
				}
				else
				{
					*result = *first1;
					++first1;
					++first2;
				}
			}

			result = copy( first1, last1, result );
			result = copy( first2, last2, result );
			return result;
		}


	// includes

	template <class InputIterator1, class InputIterator2> inline
		bool Includes( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2 )
		{
			for( ; first1 != last1 && first2 != last2; ++first1 )
			{
				if( *first2 < *first1 )
					return false;
				if( !(*first1 < *first2) )
					++first2;
			}

			return first2 == last2;
		}

	template <class InputIterator1, class InputIterator2, class Compare> inline
		bool Includes( InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2, Compare compare )
		{
			for( ; first1 != last1 && first2 != last2; ++first1 )
			{
				if( compare(*first2, *first1) )
					return false;
				if( !compare(*first1, *first2) )
					++first2;
			}

			return first2 == last2;
		}

} // Algorithm


CE_NAMESPACE_END


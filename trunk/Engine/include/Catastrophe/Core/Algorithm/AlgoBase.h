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
#include "Catastrophe/Core/Memory.h"


CE_NAMESPACE_BEGIN


template <class T> inline
const T& Max( const T& a, const T& b )
{
	return a > b ? a : b;
}

template <class T> inline
const T& Min( const T& a, const T& b )
{
	return a < b ? a : b;
}

template <class T> FORCEINLINE
void FastClamp( T& value, const T& minValue, const T& maxValue )
{
	if( value < minValue ) value = minValue;
	else if( value > maxValue ) value = maxValue;
}

template <class T> inline
T Clamp( T value, T minValue, T maxValue )
{
	if( value < minValue ) value = minValue;
	else if( value > maxValue ) value = maxValue;
	return value;
}

template <class T> inline
void Swap( T& a, T& b )
{
	T temp(a);
	a = b;
	b = temp;
}

template <class InputIterator> FORCEINLINE
void IterSwap( InputIterator a, InputIterator b )
{
	Swap(*a, *b);
}


namespace Algorithm
{
	// swap_ranges

	template <class T> inline
		void SwapRanges( T* first, T* last, T* result )
	{
		for( ; first != last; ++result, ++first )
			Swap(*first, *result);
	}


	// clamp_range

	template <class ForwardIterator, class T> inline
		void ClampRange( ForwardIterator first, ForwardIterator last, const T& minValue, const T& maxValue )
	{
		for( ; first != last; ++first )
			FastClamp( *first, minValue, maxValue );
	}



	namespace Internal
	{

		template <class Iter, class T> FORCEINLINE
			T* CopyImpl( Iter first, Iter last, T* result, true_type )
		{
			return (T*)Memory::Memcpy( (void*)result, (const void*)first, (const char*)last - (const char*)first );
		}

		template <class InputIterator, class OutputIterator> inline
			OutputIterator CopyImpl( InputIterator first, InputIterator last, OutputIterator result, false_type )
		{
			for( ; first != last; ++result, ++first )
				*result = *first;
			return result;
		}

		template <class Iter, class T> FORCEINLINE
			T* CopyBackward( Iter first, Iter last, T* result, true_type )
		{
			const u32 nBytes = (u32)((const char*)last - (const char*)first);
			return (T*)((char*)Memory::Memmove((void*)result, (const void*)first, nBytes) - nBytes);
		}

		template <class Iter1, class Iter2> inline
			Iter2 CopyBackward( Iter1 first, Iter1 last, Iter2 result, false_type )
		{
			while( last != first )
				*(--result) = *(--last);
			return result;
		}

		template<class Iter, class T> inline
			T* copy_n( Iter first, u32 numElements, T* result, true_type )
		{
			if( LIKELY(numElements != 0) )
				Memory::Memcpy( (void*)result, (void*)first, numElements * sizeof(T) );
			return (result + numElements);
		}

		template<class Iter, class T> inline
			T* copy_n( Iter first, u32 numElements, T* result, false_type )
		{
			for( ; numElements != 0; ++result, ++first )
				*result = *first, --numElements;
			return result;
		}

		template <class Iter, class T> inline
			void Fill( Iter first, Iter last, const T& value, true_type )
		{
			Memory::Memset( (void*)first, (int)value, u32((const char*)last - (const char*)first) );
		}

		template <class Iter, class T> inline
			void Fill( Iter first, Iter last, const T& value, false_type )
		{
			for( ; first != last; ++first )
				*first = value;
		}

		template <class Iter, class T> inline
			Iter FillValues( Iter first, u32 numElements, const T& value, true_type )
		{
			return Memory::Memset( (void*)first, value, numElements );
		}

		template <class Iter, class T> inline
			Iter FillValues( Iter first, u32 numElements, const T& value, false_type )
		{
			while( numElements-- )
				*first++ = value;
			return first;
		}

	} //internal


	// Copy

	template <class InputIterator, class OutputIterator> FORCEINLINE
		OutputIterator Copy( InputIterator first, InputIterator last, OutputIterator result )
	{
		return Internal::CopyImpl( first, last, result, typename is_binary_copyable<
			is_pointer<InputIterator>::value, is_pointer<OutputIterator>::value,
			has_trivial_assign< typename IteratorTraits<InputIterator>::ValueType >::value,
			has_trivial_assign< typename IteratorTraits<OutputIterator>::ValueType >::value
		>::type()
		);
	}


	// ReverseCopy

	template <class BidirectionalIterator, class OutputIterator> FORCEINLINE
		OutputIterator ReverseCopy( BidirectionalIterator first, BidirectionalIterator last, OutputIterator result )
	{
		for( ; first != last; ++result )
			*result = *--last;
		return result;
	}


	// CopyBackward

	template <class InputIterator, class OutputIterator> FORCEINLINE
		OutputIterator CopyBackward( InputIterator first, InputIterator last, OutputIterator result )
	{
		return Internal::CopyBackward( first, last, result, typename is_binary_copyable<
			is_pointer<InputIterator>::value, is_pointer<OutputIterator>::value,
			has_trivial_assign< typename IteratorTraits<InputIterator>::ValueType >::value,
			has_trivial_assign< typename IteratorTraits<OutputIterator>::ValueType >::value
		>::type()
		);
	}


	// copy_n

	template<class InputIterator, class OutputIterator> FORCEINLINE
		OutputIterator CopyValues( InputIterator first, u32 numElements, OutputIterator result )
	{
		return Internal::copy_n( first, numElements, result, typename is_binary_copyable<
			is_pointer<InputIterator>::value, is_pointer<OutputIterator>::value,
			has_trivial_assign< typename IteratorTraits<InputIterator>::ValueType >::value,
			has_trivial_assign< typename IteratorTraits<OutputIterator>::ValueType >::value
		>::type()
		);
	}


	// Fill

	template <class ForwardIterator, class T> FORCEINLINE
		void Fill( ForwardIterator first, ForwardIterator last, const T& value )
	{
		return Internal::Fill( first, last, value, typename is_binary_copyable<
			is_pointer<ForwardIterator>::value,
			is_sizeof< typename IteratorTraits<ForwardIterator>::ValueType, 1 >::value
		>::type()
		);
	}

	// FillValues

	template <class ForwardIterator, class T> FORCEINLINE
		ForwardIterator FillValues( ForwardIterator first, u32 numElements, const T& value )
	{
		return Internal::FillValues( first, numElements, value, typename is_binary_copyable<
			is_pointer<ForwardIterator>::value,
			is_sizeof< typename IteratorTraits<ForwardIterator>::ValueType, 1 >::value
		>::type()
		);
	}


	// Find

	template <class ForwardIterator, class T> FORCEINLINE //inline
		ForwardIterator Find( ForwardIterator first, ForwardIterator last, const T& value )
	{
		while( (first != last) && !(*first == value) )
			++first;
		return first;
	}


	// FindIf

	template <class InputIterator, class UnaryPredicate> inline
		InputIterator FindIf( InputIterator first, InputIterator last, UnaryPredicate predicate )
	{
		for( ; first != last ; ++first )
			if( predicate(*first) )
				break;

		return first;
	}


	// ReverseFind

	template <class BidirectionalIterator, class T> inline
		BidirectionalIterator ReverseFind( BidirectionalIterator first, BidirectionalIterator last, const T& value )
		{
			BidirectionalIterator last2 = last;
			if( LIKELY(first != last) )
				for( --first, --last; (first != last) && !(*last == value); --last ) ;

			return (last == first) ? last2 : last;
		}


	// LexicographicalCompare

	template <class InputIterator1, class InputIterator2, class Compare> inline
		bool LexicographicalCompare( InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2, Compare compare )
		{
			for( ; first1 != last1 && first2 != last2; first1++, first2++ )
			{
				if( compare(*first1, *first2) ) return true;
				if( compare(*first2, *first1) ) return false;
			}
			return (first1 == last1) && (first2 != last2);
		}

	inline bool LexicographicalCompare( const char* first1, const char* last1, const char* first2, const char* last2 )
	{
		u32 a(last1 - first1), b(last2 - first2);
		int result = Memory::Memcmp( first1, first2, (a < b ? a : b) );
		return result ? (result < 0) : (a < b);
	}

	namespace Internal
	{
		template <class InputIterator1, class InputIterator2> FORCEINLINE
			bool LexicographicalCompare( InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, InputIterator2 last2, false_type )
			{
				return LexicographicalCompare( first1, last1, first2, last2,
					Less< typename IteratorTraits<InputIterator1>::ValueType >() );
			}

		template <class InputIterator1, class InputIterator2> FORCEINLINE
			bool LexicographicalCompare( InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, InputIterator2 last2, true_type )
			{
				return LexicographicalCompare((const char*)first1, (const char*)last1,
					(const char*)first2, (const char*)last2 );
			}

		template <class T> inline
			bool Equal( T* first, T* last, T* first2, true_type )
			{
				return Memory::Memcmp(first, last, u32(last - first)) == 0;
			}

		template <class InputIterator1, class InputIterator2> inline
			bool Equal( InputIterator1 first, InputIterator1 last, InputIterator2 first2, false_type )
			{
				for( ; first != last; ++first, ++first2 )
					if( !(*first == *first2) )
						return false;
				return true;
			}

	}

	template <class InputIterator1, class InputIterator2> inline
		bool LexicographicalCompare( InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2 )
		{
			return Internal::LexicographicalCompare( first1, last1, first2, last2, typename is_binary_comparable<
				is_pointer<InputIterator1>::value, is_pointer<InputIterator2>::value,
				is_sizeof< typename IteratorTraits<InputIterator1>::ValueType, 1 >::value,
				is_sizeof< typename IteratorTraits<InputIterator2>::ValueType, 1 >::value
			>::type()
			);
		}


	template <class InputIterator, class T> inline
		bool Contains( InputIterator first, InputIterator last, const T& value )
		{
			return Find( first, last, value ) != last;
		}


	// equal

	template <class InputIterator1, class InputIterator2, class BinaryPredicate> inline
		bool Equal( InputIterator1 first, InputIterator1 last, InputIterator2 first2, BinaryPredicate predicate )
		{
			for( ; first != last; ++first, ++first2 )
				if( !predicate(*first, *first2) )
					return false;
			return true;
		}

	template <class InputIterator1, class InputIterator2> inline
		bool Equal( InputIterator1 first, InputIterator1 last, InputIterator2 first2 )
		{
			return Internal::Equal( first, last, first2, typename is_binary_comparable<
				is_pointer<InputIterator1>::value, is_pointer<InputIterator2>::value,
				is_sizeof< typename IteratorTraits<InputIterator1>::ValueType, 1 >::value,
				is_sizeof< typename IteratorTraits<InputIterator2>::ValueType, 1 >::value
				>::type()
			);
		}

} // Algorithm


CE_NAMESPACE_END


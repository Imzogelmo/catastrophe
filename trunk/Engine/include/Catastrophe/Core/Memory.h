//////////////////////////////////////
// Fast Container Library           //
// MIT License - Copyright (c) 2012 //
//////////////////////////////////////

#pragma once

#include "Catastrophe/Core/Common.h"
#include "Catastrophe/Core/PlatformMemory.h"
#include "Catastrophe/Core/TypeTraits.h"

#include <new> // This is needed for placement new.


CE_NAMESPACE_BEGIN


namespace Memory
{

	namespace Internal
	{
		template <class ForwardIterator, class T> inline
			void ConstructValues( ForwardIterator first, u32 n, const T& value, true_type )
			{
				Memset( first, value, n * sizeof(T) );
			}

		template <class ForwardIterator, class T> inline
			void ConstructValues( ForwardIterator first, u32 n, const T& value, false_type )
			{
				for( ; n--; ++first )
					new (&*first) T(value);
			}

		template <class T> inline
			void Destroy( T*, true_type )
			{
				//do nothing
			}

		template <class T> inline
			void Destroy( T* ptr, false_type )
			{
				ptr->~T();
			}

		template <class Iter> inline
			void DestroyRange( Iter, Iter, true_type )
			{
				//do nothing
			}

		template <class BidirectionalIterator> FORCEINLINE
			void DestroyRange( BidirectionalIterator first, BidirectionalIterator last, false_type )
			{
				typedef typename IteratorTraits<BidirectionalIterator>::ValueType ValueType;
				while( first != last )
					(--last)->~ValueType();
			}

		template <class T> inline
			void DestroyValues( T*, u32, true_type )
			{
				//do nothing
			}

		template <class T> inline
			void DestroyValues( T* ptr, u32 n, false_type )
			{
				for( u32 i(n); i != 0; )
					(ptr + --i)->~T();
			}


		template <class InputIterator, class ForwardIterator> inline
			ForwardIterator UninitializedCopyImpl( InputIterator first, InputIterator last, ForwardIterator result, true_type )
			{
				const u32 nBytes = u32((const char*)last - (const char*)first);
				return (ForwardIterator)((char*)Memcpy( (void*)result, (const void*)first, nBytes) + nBytes);
			}

		template <class InputIterator, class ForwardIterator> inline
			ForwardIterator UninitializedCopyImpl( InputIterator first, InputIterator last, ForwardIterator result, false_type )
			{
				typedef typename IteratorTraits<ForwardIterator>::ValueType ValueType;
				for( ; first != last; ++first, ++result )
					new (&*result) ValueType(*first);
				return result;
			}

		template <class InputIterator, class BidirectionalIterator> inline
			BidirectionalIterator UninitializedCopyBackwardImpl( InputIterator first, InputIterator last, BidirectionalIterator result, true_type )
			{
				const u32 nBytes = u32((const char*)last - (const char*)first);
				return (BidirectionalIterator)((char*)Memmove((void*)((char*)result - nBytes), (void*)first, nBytes) - nBytes);
			}

		template <class InputIterator, class BidirectionalIterator> inline
			BidirectionalIterator UninitializedCopyBackwardImpl( InputIterator first, InputIterator last, BidirectionalIterator result, false_type )
			{
				typedef typename IteratorTraits<InputIterator>::ValueType ValueType;
				while( first != last )
					new (&*--result) ValueType(*--last);
				return result;
			}

		template <class ForwardIterator, class T> inline
			void UninitializedFillImpl( ForwardIterator first, ForwardIterator last, const T& value, true_type )
			{
				for( ; first != last; ++first )
					*first = value;
			}

		template <class ForwardIterator, class T> inline
			void UninitializedFillImpl( ForwardIterator first, ForwardIterator last, const T& value, false_type )
			{
				for( ; first != last; ++first )
					new (&*first) T(value);
			}
	}


	// Construct

	template <class T> FORCEINLINE
		void Construct( T* ptr )
		{
			new (ptr) T;
		}

	template <class T> FORCEINLINE
		void Construct( T* ptr, const T& value )
		{
			new (ptr) T(value);
		}

	template <class T, class ConstructableType> FORCEINLINE
		void ConstructAs( T* ptr, const ConstructableType& value )
		{
			new (ptr) T(value);
		}

	// ConstructValues

	template <class T> FORCEINLINE
		void ConstructValues( T* ptr, u32 numElements, const T& value = T() )
		{
			// If the sizeof(T) == 1 we can simply call memset on the memory range,
			// otherwize we will construct in place.
			return Internal::ConstructValues( ptr, numElements, value,
				typename is_binary_copyable< is_sizeof<T, 1>::value, true >::type() );
		}


	// Destroy

	template <class T> FORCEINLINE
		void Destroy( T* ptr )
		{
			Internal::Destroy( ptr, typename has_trivial_destructor<T>::type() );
		}


	// DestroyRange

	template <class BidirectionalIterator> FORCEINLINE
		void DestroyRange( BidirectionalIterator first, BidirectionalIterator last )
		{
			Internal::DestroyRange( first, last,
				typename has_trivial_destructor< typename IteratorTraits<BidirectionalIterator>::ValueType >::type() );
		}


	// DestroyValues

	template <class BidirectionalIterator> FORCEINLINE
		void DestroyValues( BidirectionalIterator first, u32 numElements )
		{
			Internal::DestroyRange( first, first + numElements,
				typename has_trivial_destructor< typename IteratorTraits<BidirectionalIterator>::ValueType >::type() );
		}


	// UninitializedCopy

	template <class InputIterator, class ForwardIterator> FORCEINLINE
		ForwardIterator UninitializedCopy( InputIterator first, InputIterator last, ForwardIterator result )
		{
			return Internal::UninitializedCopyImpl( first, last, result, typename is_binary_copyable<
				is_pointer<InputIterator>::value, is_pointer<ForwardIterator>::value,
				has_trivial_copy< typename IteratorTraits<InputIterator>::ValueType >::value,
				has_trivial_copy< typename IteratorTraits<ForwardIterator>::ValueType >::value
			>::type()
			);
		}


	// UninitializedCopyBackward

	template <class InputIterator, class ForwardIterator> FORCEINLINE
		ForwardIterator UninitializedCopyBackward( InputIterator first, InputIterator last, ForwardIterator result )
		{
			return Internal::UninitializedCopyBackwardImpl( first, last, result, typename is_binary_copyable<
				is_pointer<InputIterator>::value, is_pointer<ForwardIterator>::value,
				has_trivial_copy< typename IteratorTraits<InputIterator>::ValueType >::value,
				has_trivial_copy< typename IteratorTraits<ForwardIterator>::ValueType >::value
			>::type()
			);
		}


	// UninitializedFill

	template <class ForwardIterator, class T> FORCEINLINE
		void UninitializedFill( ForwardIterator first, ForwardIterator last, const T& value )
		{
			Internal::UninitializedFillImpl( first, last, value, typename has_trivial_copy<T>::type() );
		}


	// UninitializedFillValues

	template <class ForwardIterator, class T> FORCEINLINE
		void UninitializedFillValues( ForwardIterator first, u32 n, const T& value = T() )
		{
			Internal::ConstructValues( first, n, value, typename is_binary_copyable<
				is_pointer<ForwardIterator>::value, is_sizeof<T, 1>::value,
				is_sizeof< typename IteratorTraits<ForwardIterator>::ValueType, 1 >::value
			>::type()
			);
		}


	/// GetDefaultAllocator
	///
	/// Gets the default allocator used by all containers and classes requiring
	/// memory allocations when an instance of an allocator is not explicitly set.
	Allocator* CE_API GetDefaultAllocator();

	/// SetDefaultAllocator
	///
	/// Sets the default allocator to point to another allocator instance, which
	/// will then be returned through subsequent calls to the GetDefaultAllocator() method.
	/// This will not corrupt any memory of previous allocated memory, so long
	/// as pointers to the previous default allocator object remain valid.
	void CE_API SetDefaultAllocator(Allocator* allocator);


} //Memory



CE_NAMESPACE_END


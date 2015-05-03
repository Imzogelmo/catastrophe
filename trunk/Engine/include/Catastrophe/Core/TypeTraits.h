// Permission is hereby granted, free of charge, to any person obtaining a Copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, Copy, modify, merge, publish, distribute, sublicense, and/or sell
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

// MSVC has intrinsics for the following types.
#define IS_POD(T) __is_pod(T)
#define IS_ENUM(T) __is_enum(T)
#define IS_EMPTY(T) __is_empty(T)
#define HAS_TRIVIAL_COPY(T) __has_trivial_copy(T)
#define HAS_TRIVIAL_ASSIGN(T) __has_trivial_assign(T)
#define HAS_TRIVIAL_DESTRUCTOR(T) __has_trivial_destructor(T)
#define HAS_TRIVIAL_CONSTRUCTOR(T) __has_trivial_constructor(T)


/// CE_MAKE_TRAIT
/// 
/// Sets a type trait of the given class to true.
/// This allows all instances of class to be optimized by the engine, either
/// in memory operations, container use, or algorithms. This also allows the
/// compiled code to be smaller and faster in many cases.
/// 
/// Example Usage:
///    MAKE_TRAIT(MyPODClass, is_pod);
///
#define CE_MAKE_TRAIT(_class, _trait) \
	CE_NAMESPACE_BEGIN template<> struct _trait<_class > : true_type {}; CE_NAMESPACE_END

/// MAKE_TRAIT
///
/// Used internally by the engine.
/// Use CE_MAKE_TRAIT, which automatically resolves a trait to the
/// proper namespace. 
/// 
#define MAKE_TRAIT(_class, _trait) \
	template<> struct _trait<_class > : true_type {};


CE_NAMESPACE_BEGIN

template <bool v> struct integral_constant
{
	static const bool value = v;
	typedef integral_constant<v> type;
};

typedef integral_constant<true> true_type;
typedef integral_constant<false> false_type;


template <class T> struct is_integral : false_type { };
template<> struct is_integral<bool> : true_type { };
template<> struct is_integral<char> : true_type { };
template<> struct is_integral<signed char> : true_type { };
template<> struct is_integral<unsigned char> : true_type { };
template<> struct is_integral<short> : true_type { };
template<> struct is_integral<unsigned short> : true_type { };
template<> struct is_integral<int> : true_type { };
template<> struct is_integral<unsigned int> : true_type { };
template<> struct is_integral<long> : true_type { };
template<> struct is_integral<unsigned long> : true_type { };
template<> struct is_integral<long long> : true_type { };
template<> struct is_integral<unsigned long long> : true_type { };

template <class T> struct is_integral<const T> : is_integral<T> { };
template <class T> struct is_integral<volatile T> : is_integral<T> { };
template <class T> struct is_integral<const volatile T> : is_integral<T> { };

template <class T> struct is_floating_point : false_type { };
template<> struct is_floating_point<float> : true_type { };
template<> struct is_floating_point<double> : true_type { };
template<> struct is_floating_point<long double> : true_type { };

template <class T> struct is_floating_point<const T> : is_floating_point<T> { };
template <class T> struct is_floating_point<volatile T> : is_floating_point<T> { };
template <class T> struct is_floating_point<const volatile T> : is_floating_point<T> { };

template <class T, u32 N> struct is_sizeof : integral_constant <(sizeof(T) == N)> { };

template <class T> struct is_pointer : false_type { };
template <class T> struct is_pointer<T*> : true_type { };
template <class T> struct is_pointer<const T*> : true_type { };
template <class T> struct is_pointer<const T* const> : true_type { };
template <class T> struct is_pointer<T* volatile> : true_type { };
template <class T> struct is_pointer<const T* volatile> : true_type { };

template<class T> struct is_reference : false_type {};
template<class T> struct is_reference<T&> : true_type {};
template<class T> struct is_reference<const T&> : true_type {};

template<class T> struct is_const : false_type {};
template<class T> struct is_const<const T> : true_type {};

template <class T> struct is_fundamental : integral_constant <(is_integral<T>::value || is_floating_point<T>::value)> { };
template <class T> struct is_fundamental<const T> : is_fundamental<T> { };

template <class T> struct is_pod : integral_constant <(is_fundamental<T>::value || is_pointer<T>::value || IS_POD(T) || IS_ENUM(T) || IS_EMPTY(T))> { };
template <class T> struct is_pod<const T> : is_pod<T> { };

template <class T> struct has_trivial_constructor : is_pod<T> { };
template <class T> struct has_trivial_constructor<const T> : has_trivial_constructor<T> { };

template <class T> struct has_trivial_copy : is_pod<T> { };
template <class T> struct has_trivial_copy<const T> : has_trivial_copy<T> { };

template <class T> struct has_trivial_assign : is_pod<T> { };

template <class T> struct has_trivial_destructor : is_pod<T> { };
template <class T> struct has_trivial_destructor<const T> : has_trivial_destructor<T> { };

template <class T> struct is_array : false_type { };
template <class T> struct is_array<T[]> : true_type {};
template <class T, u32 N> struct is_array<T[N]> : true_type {};

// is_true_type
template <bool T> struct is_true_type : false_type { };
template <> struct is_true_type<true> : true_type { };

// is_binary_copyable
template <bool T1, bool T2, bool T3 = true, bool T4 = true> struct is_binary_copyable : false_type { };
template <> struct is_binary_copyable<true, true, true, true> : true_type { };

// is_binary_comparable
template <bool T1, bool T2, bool T3 = true, bool T4 = true> struct is_binary_comparable : false_type { };
template <> struct is_binary_comparable<true, true, true, true> : true_type { };


// type_select
template <bool Condition, class TrueType, class FalseType> struct type_select { typedef TrueType type; };
template <class TrueType, class FalseType> struct type_select<false, TrueType, FalseType> { typedef FalseType type; }; 



CE_NAMESPACE_END

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

#include "Catastrophe/Common.h"
#include "Catastrophe/Core/TypeTraits.h"

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4512) // assignment operator could not be generated
#endif

CE_NAMESPACE_BEGIN


///
/// @Pair
///
/// Generic container that holds objects of 2 types similar to
/// that of std::pair.
///
template<class T1, class T2>
struct Pair
{
	typedef T1 FirstType;
	typedef T2 SecondType;

	Pair() : first(), second() {}
	Pair( const T1& value ) : first(value), second() {}
	Pair( const T1& key, const T2& value ) : first(key), second(value) {}

	// Construct from different, but related types.
	template <typename U, typename V>
	Pair( const Pair<U, V>& p ) : first(p.first), second(p.second) {}

	T1 first;
	T2 second;
};


template<class T1, class T2> inline
bool operator ==( const Pair<T1, T2>& a, const Pair<T1, T2>& b )
{
	return a.first == b.first && a.second == b.second;
}

template<class T1, class T2, class U, class V> inline
bool operator ==( const Pair<T1, T2>& a, const Pair<U, V>& b )
{
	return a.first == b.first && a.second == b.second;
}

template<class T1, class T2> inline
bool operator !=( const Pair<T1, T2>& a, const Pair<T1, T2>& b )
{
	return !(a == b);
}

template<class T1, class T2, class U, class V> inline
bool operator !=( const Pair<T1, T2>& a, const Pair<U, V>& b )
{
	return !(a == b);
}



// Types of pair are considered trivial only if both templated types are trivial.

template <class T1, class T2> struct is_pod< Pair<T1, T2> > : integral_constant
<is_pod<T1>::value && is_pod<T2>::value> { };

template <class T1, class T2> struct has_trivial_constructor< Pair<T1, T2> > : integral_constant
<has_trivial_constructor<T1>::value && has_trivial_constructor<T2>::value> { };

template <class T1, class T2> struct has_trivial_copy< Pair<T1, T2> > : integral_constant
<has_trivial_copy<T1>::value && has_trivial_copy<T2>::value> { };

template <class T1, class T2> struct has_trivial_assign< Pair<T1, T2> > : integral_constant
<has_trivial_assign<T1>::value && has_trivial_assign<T2>::value> { };



CE_NAMESPACE_END


#ifdef _MSC_VER
#pragma warning(pop)
#endif

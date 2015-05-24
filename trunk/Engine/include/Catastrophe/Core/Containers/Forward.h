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

CE_NAMESPACE_BEGIN

// functional
template <class T> struct Less;

// string
class String;
template <u32 N> class StaticString;

// bitset
class Bitset;
template <u32 N> class StaticBitset;

typedef StaticBitset<32> StaticBitset32;

// array
template <class T> class Array;
template <class T> class Array2D;
template <class T, u32 N> struct StaticArray;
template <class T, u32 Y, u32 X> struct StaticArray2D;

// vector
template <class T> class Vector;
template <class T, u32 N> class StaticVector;

template <class Key, class Compare = Less<Key>, class Container = Vector<Key> > class VectorSet;
template <class Key, class Compare = Less<Key>, class Container = Vector<Key> > class VectorMultiset;

template <class Key, class Value, class Compare = Less<Key>, class Container = Vector< KeyValuePair<Key, Value> > > class VectorMap;
template <class Key, class Value, class Compare = Less<Key>, class Container = Vector< KeyValuePair<Key, Value> > > class VectorMultimap;



typedef Vector<String> StringVector;



//TODO
template <u32 N> struct is_pod< StaticString<N> > : true_type {};
template <class T, u32 N> struct is_pod< StaticVector<T, N> > : integral_constant<is_pod<T>::value> {};

// array
template <class T, u32 N> struct is_pod< StaticArray<T, N> > : integral_constant<is_pod<T>::value> {};
template <class T, u32 Y, u32 X> struct is_pod< StaticArray2D<T, Y, X> > : integral_constant<is_pod<T>::value> {};

template <class K, class V, class C, class A> struct is_pod< VectorMap<K, V, C, A> >
: integral_constant< is_pod<K>::value && is_pod<V>::value && is_pod<C>::value && is_pod<A>::value > {};

template <class K, class V, class C, class A> struct is_pod< VectorMultimap<K, V, C, A> >
: integral_constant< is_pod<K>::value && is_pod<V>::value && is_pod<C>::value && is_pod<A>::value > {};



CE_NAMESPACE_END

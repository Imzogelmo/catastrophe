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

#ifdef _MSC_VER
	#pragma warning(push)
	#pragma warning(disable: 4512) // assignment operator could not be generated
#endif

CE_NAMESPACE_BEGIN


///
/// @KeyValuePair
///
/// Template container similar to std::pair, except that types are
/// assumed to always be that of a type key and mapped value.
///
template<class Key, class Value>
struct KeyValuePair
{
	typedef Key KeyType;
	typedef Value ValueType;

	KeyValuePair() : key(), value() {}
	KeyValuePair( const Key& key ) : key(key), value() {}
	KeyValuePair( const Key& key, const Value& value ) : key(key), value(value) {}

	// Construct from different, but related types.
	template <typename U, typename V>
	KeyValuePair( const KeyValuePair<U, V>& p ) : key(p.key), value(p.value) {}

	//template <typename U, typename V>
	//KeyValuePair<Key, Value>& operator =( const KeyValuePair<U, V>& rhs )
	//{
	//	key = rhs.key;
	//	value = rhs.value;
	//}

	Key key;
	Value value;
};


template<class Key, class Value> inline
bool operator ==( const KeyValuePair<Key, Value>& a, const KeyValuePair<Key, Value>& b )
{
	return a.key == b.key && a.value == b.value;
}

template<class Key, class Value, class U, class V> inline
bool operator ==( const KeyValuePair<Key, Value>& a, const KeyValuePair<U, V>& b )
{
	return a.key == b.key && a.value == b.value;
}

template<class Key, class Value> inline
bool operator !=( const KeyValuePair<Key, Value>& a, const KeyValuePair<Key, Value>& b )
{
	return !(a == b);
}

template<class Key, class Value, class U, class V> inline
bool operator !=( const KeyValuePair<Key, Value>& a, const KeyValuePair<U, V>& b )
{
	return !(a == b);
}


// KeyValuePairComparer

template <class Key, class Value, class Compare>
struct KeyValuePairComparer
{
	typedef Key							KeyType;
	typedef Value						ValueType;
	typedef Compare						CompareType;
	typedef KeyValuePair<Key, Value>	KeyValuePairType;

	KeyValuePairComparer( const Compare& c = Compare() )
		: compare(c) {}

	FORCEINLINE bool operator()( const KeyValuePair<Key, Value>& lhs, const KeyValuePair<Key, Value>& x ) const { return compare(lhs.key, x.key); }
	FORCEINLINE bool operator()( const KeyValuePair<Key, Value>& lhs, const Key& x ) const { return compare(lhs.key, x); }
	FORCEINLINE bool operator()( const Key& lhs, const KeyValuePair<Key, Value>& x ) const { return compare(lhs, x.key); }
	FORCEINLINE bool operator()( const Key& lhs, const Key& x ) const { return compare(lhs, x); }

	Compare compare;
};



// Types of pair are considered trivial only if both templated types are trivial.

template <class Key, class Value> struct is_pod< KeyValuePair<Key, Value> > : integral_constant
<is_pod<Key>::value && is_pod<Value>::value> { };

template <class Key, class Value> struct has_trivial_constructor< KeyValuePair<Key, Value> > : integral_constant
<has_trivial_constructor<Key>::value && has_trivial_constructor<Value>::value> { };

template <class Key, class Value> struct has_trivial_copy< KeyValuePair<Key, Value> > : integral_constant
<has_trivial_copy<Key>::value && has_trivial_copy<Value>::value> { };

template <class Key, class Value> struct has_trivial_assign< KeyValuePair<Key, Value> > : integral_constant
<has_trivial_assign<Key>::value && has_trivial_assign<Value>::value> { };



CE_NAMESPACE_END


#ifdef _MSC_VER
	#pragma warning(pop)
#endif

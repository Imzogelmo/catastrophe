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
#include "Catastrophe/Core/Hash.h"

CE_NAMESPACE_BEGIN


struct CE_API StringHash
{
	/// The hashed value of a string.
	u32 value;

	StringHash() : value(0) {}
	StringHash(const StringHash& stringHash) : value(stringHash.value) {}
	StringHash(const char* str);
	StringHash(const String& str);
	explicit StringHash(u32 value) : value(value) {}

	template <u32 N>
	StringHash(const StaticString<N>& str)
		: value(0)
	{
		value = StringHash(str.CString());
	}

	StringHash& operator =(const char* str);
	StringHash& operator =(const String& str);
	StringHash& operator =(const StringHash& stringHash)
	{
		value = stringHash.value;
		return *this;
	}

	template <u32 N>
	StringHash& operator =(const StaticString<N>& str)
	{
		value = StringHash(str.CString());
		return *this;
	}

	/// Sets the hash value to the hash of this string.
	void SetString(const char* str);

	bool operator ==(const StringHash& rhs) const { return value == rhs.value; }
	bool operator !=(const StringHash& rhs) const { return value != rhs.value; }
	bool operator <(const StringHash& rhs) const { return value < rhs.value; }
	bool operator >(const StringHash& rhs) const { return value > rhs.value; }

	operator bool() const { return value != 0; }
	operator u32() const { return value; }

	/// Gets the hashed value of this string.
	u32 Value() const { return value; }

};



CE_NAMESPACE_END


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

#include "Catastrophe/Core/Memory.h"
#include "Catastrophe/Core/PlatformMath.h"
#include "Catastrophe/Core/PlatformString.h"
#include "Catastrophe/Core/Containers/StaticString.h"
#include "Catastrophe/Core/Containers/Forward.h"
#include "Catastrophe/Core/Containers/StringRef.h"
//#include "StringUtils.h"

#ifdef _MSC_VER
	#pragma warning (push)
	#pragma warning (disable : 4480)
	#pragma warning (disable : 4996)
#endif

CE_NAMESPACE_BEGIN


///
/// @String
///
/// A standard string class of chars with an enhanced feature set over std::string.
/// Supports SSO of up to 15 bytes on 32-bit, and 31 bytes on 64-bit.
///

class CE_API String
{
public:
	typedef char							ElementType;
	typedef char*							Iterator;
	typedef const char*						ConstIterator;
	typedef ReverseIterator<const char*>	ConstReverseIterator;
	typedef ReverseIterator<char*>			ReverseIterator;

	enum ENUM_TYPE(u32)
	{
		kShortCapacity = 15,
		kShortMask = 0x01,
		npos = UINT32_MAX
	};

	String();
	explicit String(char c);
	explicit String(int value);
	explicit String(float value);
	String(const char* str, u32 stringLength);
	String(const char* str);
	String(u32 numChars, char c);
	String(const String& str);
	String(const StringRef& str);
	String(const char* first, const char* last);
	String(u32 bufferLength, const char* format, ...);

	// Specialized constructor for operator +
	String(const char* str1, const u32 nBytes1, const char* str2, const u32 nBytes2, int allocationFlags = 0);

	~String()
	{
		// Deallocate will already do a check for short strings
		Deallocate();
	}

	/// Gets whether this string is currently SSO (Small String Optimized) and using an internal buffer.
	bool IsShort() const
	{
		// Short strings size mask is always 0x01, even when string size is 0.
		return _s.size != 0;
	}

	/// Gets whether this string is currently dynamically allocated.
	bool IsLong() const
	{
		// Size byte for short string is always 0 when the string is long.
		return _s.size == 0;
	}

	char&		operator [] (u32 index)			{ return _s.size ? _s.data[index] : *(_l.ptr + index); }
	const char& operator [] (u32 index) const	{ return _s.size ? _s.data[index] : *(_l.ptr + index); }
	char& at(u32 index)
	{
		CE_ASSERT(index < size());
		return _s.size ? _s.data[index] : *(_l.ptr + index);
	}

	const char& at(u32 index) const
	{
		CE_ASSERT(index < size());
		return _s.size ? _s.data[index] : *(_l.ptr + index);
	}

	char*		begin()			{ return _s.size ? _s.data : _l.ptr; }
	const char*	begin() const	{ return _s.size ? _s.data : _l.ptr; }
	char*		end()			{ return _s.size ? &_s.data[_s.size >> 1] : _l.end; }
	const char*	end() const		{ return _s.size ? &_s.data[_s.size >> 1] : _l.end; }
	char*		data()			{ return _s.size ? _s.data : _l.ptr; }
	const char*	data() const	{ return _s.size ? _s.data : _l.ptr; }
	const char*	c_str() const	{ return _s.size ? _s.data : _l.ptr; }

	u32 size() const	{ return _s.size ? u32(_s.size >> 1) : u32(_l.end - _l.ptr); }
	u32 length() const	{ return _s.size ? u32(_s.size >> 1) : u32(_l.end - _l.ptr); }

	const char*	CString() const	{ return _s.size ? _s.data : _l.ptr; }

	/// Gets the length of this string.
	u32 Size() const { return _s.size ? u32(_s.size >> 1) : u32(_l.end - _l.ptr); }

	/// Gets the internal buffer size; how many chars the string can hold without a reallocation).
	u32 Capacity() const { return _s.size ? (kShortCapacity - 1) : (_l.capacity - 1); }

	/// Gets the length of unused storage (ie., capacity - length).
	u32 Unused() const
	{
		return _s.size ? u32(kShortCapacity - (_s.size >> 1)) :
			_l.capacity - u32(_l.end - _l.ptr);
	}

	/// Returns true if string length is zero.
	bool Empty() const
	{
		return _s.size ? (_s.size >> 1) == 0 : _l.end - _l.ptr == 0;
	}

	/// Returns true if size == capacity.
	bool Full() const
	{
		return _s.size ? u32(_s.size >> 1) == kShortCapacity : u32(_l.end - _l.ptr) == _l.capacity;
	}

	char&		Front()			{ return *begin(); }
	const char& Front() const	{ return *begin(); }
	char&		Back()			{ return *(end() - 1); }
	const char& Back()	const	{ return *(end() - 1); }

	void PopFront() { Erase(begin()); }

	template <class Container>
	String& operator =(const Container& str) { return Assign(str.begin(), str.end()); }
	String& operator =(const String& str) { return Assign(str.begin(), str.end()); }
	String& operator =(const StringRef& str) { return Assign(str.m_begin, str.m_end); }
	String& operator =(const char* str) { return Assign(str, Strlen(str)); }
	String& operator =(char c) { return Assign(u32(1), c); }

	/// Concatenates an array of strings and appends them to this string.
	void Join(const StringVector& stringArray, const String& seperator);

	/// Concatenates an array of strings and appends them to this string.
	void Join(const String* stringArray, u32 arraySize, const String& seperator);

	/// Concatenates an array of strings to the end and returns the result.
	String Joined(const StringVector& stringArray, const String& seperator) const;

	/// Concatenates an array of strings to the end and returns the result.
	String Joined(const String* stringArray, u32 arraySize, const String& seperator) const;

	/// Splits this string into an array of tokens using the supplied delimiters.
	void Split(StringVector& outStrings, const String& delimiters, bool keepStringLiterals = true) const;

	/// Parses the string for the next token starting at position 'startIndex'.
	/// @return the end position of token within this string, or npos.
	u32 GetToken( String& outToken, u32 startIndex, const String& delimiters = " \t\n\r", bool keepStringLiterals = true ) const;

	/// Reverses the sequence of chars of this string.
	void Reverse();

	/// Trims the whitespace from the beginning of this string.
	String& TrimStart();

	/// Trims the matching delimiters from the beginning of this string.
	String& TrimStart(const String& delimiters);

	/// Trims the whitespace from the end of this string.
	String& TrimEnd();

	/// Trims the matching delimiters from the end of this string.
	String& TrimEnd(const String& delimiters);

	/// Trims the whitespace from both sides of this string.
	String& Trim();

	/// Trims the matching delimiters from both sides of this string.
	String& Trim(const String& delimiters);

	/// Returns a Copy of this string with whitespace trimmed from both sides.
	String Trimmed() const;

	/// Returns a reference to this string with whitespace trimmed from both sides.
	StringRef TrimmedRef() const;

	/// Adds '/' to the end of this string if the last char is not a slash.
	void AddTrailingSlash();

	/// Removes '/' or '\\' slashes from the very end of this string.
	void RemoveTrailingSlash();

	/// Returns true if this string contains the given substring.
	bool Contains(const String& substring, u32 startIndex = 0) const;

	/// Returns true if this string contains the given substring ref.
	bool Contains(const StringRef& substring, u32 startIndex = 0) const;

	/// Returns true if this string contains the specified char.
	bool Contains(char c, u32 startIndex = 0) const;

	/// Returns a file extension, or an empty string.
	/// @note This method assumes the string to be a valid path or filename.
	String GetFileExtension(bool lowercase = false) const;

	/// Returns a file name, with or without a file extention, or an empty string.
	/// @note This method assumes the string to be a valid path or filename.
	String GetFileName(bool stripExtension = true, bool lowercase = false) const;

	/// Returns a file path, or an empty string.
	/// @note This method assumes the string to be a valid path or filename.
	String GetFilePath(bool lowercase = false) const;

	/// Replaces the files' extension with a new one.
	String& ReplaceExtension(const char* newExtension);

	bool StartsWith(const String& str, bool caseSensitive = true) const { return StartsWith(str.begin(), str.size(), caseSensitive); }
	bool StartsWith(const StringRef& str, bool caseSensitive = true) const { return StartsWith(str.m_begin, str.size(), caseSensitive); }
	bool StartsWith(const char* str, bool caseSensitive = true) const { return StartsWith(str, Strlen(str), caseSensitive); }
	bool StartsWith(const char* str, u32 stringLength, bool caseSensitive = true) const;
	bool StartsWith(char c, bool caseSensitive = true) const;

	bool EndsWith(const String& str, bool caseSensitive = true) const { return EndsWith(str.begin(), str.size(), caseSensitive); }
	bool EndsWith(const StringRef& str, bool caseSensitive = true) const { return EndsWith(str.m_begin, str.size(), caseSensitive); }
	bool EndsWith(const char* str, bool caseSensitive = true) const { return EndsWith(str, Strlen(str), caseSensitive); }
	bool EndsWith(const char* str, u32 stringLength, bool caseSensitive = true) const;
	bool EndsWith(char c, bool caseSensitive = true) const;

	u32 FindFirstSubstring(const String& substring, u32 startIndex = 0) const { return FindFirstSubstring(substring.CString(), startIndex, substring.size()); }
	u32 FindFirstSubstring(const StringRef& substring, u32 startIndex = 0) const { return FindFirstSubstring(substring.CString(), startIndex, substring.size()); }
	u32 FindFirstSubstring(const char* substring, u32 startIndex = 0) const { return FindFirstSubstring(substring, startIndex, Strlen(substring)); }
	u32 FindFirstSubstring(const char* substring, u32 startIndex, u32 stringLength) const;

	u32 FindLastSubstring(const String& substring, u32 startIndex = npos) const { return FindLastSubstring(substring.CString(), startIndex, substring.size()); }
	u32 FindLastSubstring(const StringRef& substring, u32 startIndex = npos) const { return FindLastSubstring(substring.CString(), startIndex, substring.size()); }
	u32 FindLastSubstring(const char* substring, u32 startIndex = npos) const { return FindLastSubstring(substring, startIndex, Strlen(substring)); }
	u32 FindLastSubstring(const char* substring, u32 startIndex, u32 stringLength) const;

	u32 FindFirstOf(const String& delimiters, u32 startIndex = 0) const { return FindFirstOf(delimiters.begin(), startIndex, delimiters.size()); }
	u32 FindFirstOf(const StringRef& delimiters, u32 startIndex = 0) const { return FindFirstOf(delimiters.m_begin, startIndex, delimiters.size()); }
	u32 FindFirstOf(const char* delimiters, u32 startIndex = 0) const { return FindFirstOf(delimiters, startIndex, Strlen(delimiters)); }
	u32 FindFirstOf(const char* delimiters, u32 startIndex, u32 stringLength) const;
	u32 FindFirstOf(char c, u32 startIndex = 0) const;

	u32 FindFirstNotOf(const String& delimiters, u32 startIndex = 0) const { return FindFirstNotOf(delimiters.CString(), startIndex, delimiters.size()); }
	u32 FindFirstNotOf(const StringRef& delimiters, u32 startIndex = 0) const { return FindFirstNotOf(delimiters.CString(), startIndex, delimiters.size()); }
	u32 FindFirstNotOf(const char* delimiters, u32 startIndex = 0) const { return FindFirstNotOf(delimiters, startIndex, Strlen(delimiters)); }
	u32 FindFirstNotOf(const char* delimiters, u32 startIndex, u32 stringLength) const;
	u32 FindFirstNotOf(char c, u32 startIndex = 0) const;

	u32 FindLastOf(const String& delimiters, u32 startIndex = npos) const { return FindLastOf(delimiters.begin(), startIndex, delimiters.size()); }
	u32 FindLastOf(const StringRef& delimiters, u32 startIndex = npos) const { return FindLastOf(delimiters.m_begin, startIndex, delimiters.size()); }
	u32 FindLastOf(const char* delimiters, u32 startIndex = npos) const { return FindLastOf(delimiters, startIndex, Strlen(delimiters)); }
	u32 FindLastOf(const char* delimiters, u32 startIndex, u32 stringLength) const;
	u32 FindLastOf(char c, u32 startIndex = npos) const;

	u32 FindLastNotOf(const String& delimiters, u32 startIndex = npos) const { return FindLastNotOf(delimiters.CString(), startIndex, delimiters.size()); }
	u32 FindLastNotOf(const StringRef& delimiters, u32 startIndex = npos) const { return FindLastNotOf(delimiters.CString(), startIndex, delimiters.size()); }
	u32 FindLastNotOf(const char* delimiters, u32 startIndex = npos) const { return FindLastNotOf(delimiters, startIndex, Strlen(delimiters)); }
	u32 FindLastNotOf(const char* delimiters, u32 startIndex, u32 stringLength) const;
	u32 FindLastNotOf(char c, u32 startIndex = npos) const;

	int Compare(const String& str, bool caseSensitive = true) const { return Compare(begin(), end(), str.begin(), str.end(), caseSensitive); }
	int Compare(const StringRef& stringRef, bool caseSensitive = true) const { return Compare(begin(), end(), stringRef.m_begin, stringRef.m_end, caseSensitive); }
	int Compare(const char* str, bool caseSensitive = true) const { return Compare(begin(), end(), str, str + Strlen(str), caseSensitive); }
	int Compare(const char* str, u32 stringLength, bool caseSensitive = true) const
	{
		return String::Compare(begin(), end(), str, str + stringLength, caseSensitive);
	}

	static int Compare(const char* first1, const char* last1, const char* first2, const char* last2, bool caseSensitive = true);
	static int Compare(const char* str1, u32 stringLength1, const char* str2, u32 stringLength2, bool caseSensitive = true);

	String& MakeUpper();
	String& MakeLower();

	NOINLINE String& MakeUpper(u32 startIndex, u32 stringLength);
	NOINLINE String& MakeLower(u32 startIndex, u32 stringLength);

	String ToUpper() const;
	String ToLower() const;

	String& Assign(const String& str) { return Assign(str.begin(), str.size()); }
	String& Assign(const StringRef& stringRef) { return Assign(stringRef.m_begin, stringRef.size()); }
	String& Assign(const char* first, const char* last)
	{
		CE_ASSERT(first <= last);
		return Assign(first, u32(last - first)); 
	}

	String& Assign(const char* str) { return Assign(str, Strlen(str)); }
	String& Assign(const char* str, u32 stringLength);
	String& Assign(u32 bufferLength, const char* format, ...);
	String& Assign(u32 numChars, char c);

	void Resize(u32 newSize, char c = 0);
	void Reserve(u32 capacity );

	void ShrinkToFit() { SetCapacity(size()); }
	void SetCapacity(u32 newCapacity);

	String& operator +=(const String& str) { return Append(str.begin(), str.size()); }
	String& operator +=(const StringRef& str) { return Append(str.m_begin, str.size()); }
	String& operator +=(const char* s) { return Append(s, Strlen(s)); }
	String& operator +=(char c) { Append(c); return *this; }

	String& Append(const String& str) { return Append(str.begin(), str.size()); }
	String& Append(const StringRef& str) { return Append(str.m_begin, str.size()); }
	String& Append(const char* str) { return Append(str, Strlen(str)); }
	String& Append(const char* str, u32 stringLength);

	String& Append(char c)
	{
		AssureCapacity(u32(1));
		*end() = c;
		SetSize(size() + 1);

		return *this;
	}

	String& Append(u32 numChars, char c);

	String& Append(const char* first, const char* last)
	{
		CE_ASSERT(first <= last);
		return Append(first, u32(last - first));
	}

	String& Append(u32 bufferLength, const char* format, ...);

	/// Appends a string to the end of this string.
	/// This method does no memory checking and will overflow if there is not enough space allocated.
	String& AppendUnchecked(const String& str) { return AppendUnchecked(str.begin(), str.size()); }
	String& AppendUnchecked(const char* str) { return AppendUnchecked(str, Strlen(str)); }
	String& AppendUnchecked(const char* str, u32 stringLength);
	String& AppendUnchecked(const char* first, const char* last);

	/// Appends a sequence of num chars to the end of this string.
	/// This method does no memory checking and will overflow if there is not enough space allocated.
	String& AppendUnchecked(u32 numChars, char c);

	/// Appends a char to the end of this string.
	/// This method does no memory checking and will overflow if there is not enough space allocated.
	String& AppendUnchecked(char c)
	{
		CE_ASSERT(!Full());
		*end() = c;
		SetSize(size() + 1);
		return *this;
	}

	/// Appends a char to the end of string. (For compatability with back inserter)
	void Add(char c) { Append(c); }

	/// Removes the last character from this string.
	void PopBack()
	{
		CE_ASSERT(!Empty());
		SetSize(size() - 1);
	}

	/// Inserts a string into this string beginning at the given position.
	String& InsertAt(u32 position, const String& str)
	{
		return Insert(begin() + position, str.begin(), str.end());
	}

	String& InsertAt(u32 position, const StringRef& str)
	{
		return Insert(begin() + position, str.m_begin, str.m_end);
	}

	String& InsertAt(u32 position, const char* str)
	{
		return Insert(begin() + position, str, str + Strlen(str));
	}

	String& InsertAt(u32 position, const char* first, const char* last)
	{
		return Insert(begin() + position, first, last);
	}

	String& Insert(const char* position, const String& str)
	{
		return Insert(position, str.begin(), str.end());
	}

	String& Insert(const char* position, const StringRef& str)
	{
		return Insert(position, str.m_begin, str.m_end);
	}

	String& Insert(const char* position, const char* first, const char* last);

	/// Inserts a sequence of chars into this string beginning at 'position'.
	String& Insert(const char* position, char c) { return InsertAt(u32(position - begin()), u32(1), c); }
	String& Insert(const char* position, u32 numChars, char c) { return InsertAt(u32(position - begin()), numChars, c); }
	String& InsertAt(u32 position, char c) { return InsertAt(position, u32(1), c); }
	String& InsertAt(u32 position, u32 numChars, char c);

	/// Erase range of character at position within this string.
	void EraseAt(u32 position) { Erase(begin() + position); }
	void EraseAt(u32 position, u32 numChars = npos)
	{
		Iterator first = begin() + position;
		Iterator last = (numChars == npos ? end() : Math::Min(first + numChars, end()));
		Erase(first, last);
	}

	/// Erase sequence of character at position within this string.
	void Erase(const char* position);
	void Erase(const char* first, const char* last);

	void Clear()
	{
		SetSize(0);
	}

	String Substring(u32 position = 0, u32 stringLength = npos) const;
	String Substring(const char* first, const char* last) const
	{
		CE_ASSERT(IteratorIsValid(first) && IteratorIsValid(last) && first <= last);
		return String(first, last);
	}

	StringRef SubstringRef(u32 position = 0, u32 stringLength = npos) const;
	StringRef SubstringRef(const char* first, const char* last) const
	{
		CE_ASSERT(IteratorIsValid(first) && IteratorIsValid(last) && first <= last);
		return StringRef(first, last);
	}

	/// Replaces all occurrences of oldChar in this string with newChar.
	String& ReplaceAll(char oldChar, char newChar);

	/// Returns a new string that replaces all occurrences of oldChar with newChar.
	String Replaced(char oldChar, char newChar) const;

	/// Replaces each substring of this string that matches the given regular expression with the given replacement.
	String& ReplaceAll(const String& regex, const String& replacement);

	String& Replace(Iterator first, Iterator last, const String& str) { return Replace(first, last, str.begin(), str.end()); }
	String& Replace(Iterator first, Iterator last, const StringRef& str) { return Replace(first, last, str.begin(), str.end()); }
	String& Replace(Iterator first, Iterator last, const char* str, u32 stringLength) { return Replace(first, last, str, str + stringLength); }
	String& Replace(Iterator first, Iterator last, const char* str) { return Replace(first, last, str, str + Strlen(str)); }
	String& ReplaceAt(u32 position, u32 n, const char* str, u32 stringLength) { return Replace(begin() + position, begin() + position + n, str, str + stringLength); }
	String& ReplaceAt(u32 position, u32 n, const char* str) { return Replace(begin() + position, begin() + position + n, str, str + Strlen(str)); }
	String& ReplaceAt(u32 position, u32 n, const String& str) { return Replace(begin() + position, begin() + position + n, str.begin(), str.end()); }
	String& ReplaceAt(u32 position, u32 n, const String& str, u32 strPosition, u32 stringLength)
	{
		return Replace(begin() + position, begin() + position + n,
			str.begin() + strPosition, str.begin() + strPosition + stringLength);
	}

	/// Replaces the character sequence [first1, last1) in this string with the sequence
	/// pointed to by [first2, last2).
	NOINLINE String& Replace(Iterator first, Iterator last, const char* first2, const char* last2);
	NOINLINE String& Replace(Iterator first, Iterator last, u32 numChars, char c);

	String& ReplaceAt(u32 position, u32 count, u32 numChars, char c)
	{
		return Replace(begin() + position, begin() + position + count, numChars, c);
	}

	int ToInt() const
	{
		return Strtoi(data());
	}

	float ToFloat() const
	{
		return Strtof(data());
	}

	bool IteratorIsValid(const char* it) const
	{
		return (it >= begin() && it <= end());
	}

protected:
	struct __LongString
	{
		char* ptr;
		char* end;
		u32 capacity;
		char _padding[4];
	};

	struct __ShortString
	{
		// 16 bytes on 32-bit platforms (15 bytes of sso)
		// 24 bytes on 64-bit platforms (23 bytes of sso)
		char data[(sizeof(__LongString) + 4) / sizeof(char) - 1];
		u8 size;
	};

	union
	{
		__LongString _l;
		__ShortString _s;
	};

	void InitializeShort()
	{
		_s.data[0] = 0;
		_s.size = 0x01;
	}

	void InitializeLong(u32 nBytes);

	void InitializeCapacity(u32 nBytes)
	{
		// if nBytes == kShortCapacity there's not enough room for a terminating null.
		if(nBytes < kShortCapacity)
		{
			_s.data[0] = 0;
			_s.size = 0x01;
		}

		// Initialize as a long string and allocate memory
		else InitializeLong(nBytes);
	}

	void SetSize(u32 newSize)
	{
		if(_s.size)
		{
			_s.size = u8((newSize << 1) | kShortMask);
			_s.data[newSize] = 0;
		}
		else
		{
			_l.end = _l.ptr + newSize;
			*_l.end = 0;
		}
	}

	NOINLINE void GrowShortString(u32 amount);
	NOINLINE void GrowLongString(u32 amount);

	char* Allocate(u32 nBytes, int flags = 0);
	void Deallocate();

	/// Tells the string to make sure there is enough additional memory allocated to
	/// accomidate an additional number of bytes.
	void AssureCapacity(u32 nCharsToAdd);

	u32 CalculateNewCapacity(u32 growth);

};



// global operators

inline bool operator ==(const String& a, const String& b)
{
	return (a.size() == b.size() && Memory::Memcmp(a.CString(), b.CString(), a.size()) == 0);
}

inline bool operator !=(const String& a, const String& b)
{
	return !(a == b);
}

inline bool operator ==(const String& a, const char* s)
{
	const u32 stringLength = Strlen(s);
	return (a.size() == stringLength && Memory::Memcmp(a.CString(), s, stringLength) == 0);
}

inline bool operator !=(const String& a, const char* s)
{
	return !(a == s);
}

inline bool operator ==(const char* s, const String& b)
{
	const u32 stringLength = Strlen(s);
	return (b.size() == stringLength && Memory::Memcmp(b.CString(), s, stringLength) == 0);
}

inline bool operator !=(const char* s, const String& b)
{
	return !(b == s);
}

inline bool operator <(const String& a, const String& b)
{
	return Memory::Memcmp(a.begin(), a.end(), b.begin(), b.end()) < 0;
}

inline bool operator <(const String& a, const char* b)
{
	return Memory::Memcmp(a.begin(), a.size(), b, Strlen(b)) < 0;
}

inline bool operator <(const char* a, const String& b)
{
	return Memory::Memcmp(a, Strlen(a), b.begin(), b.size()) < 0;
}

inline bool operator >(const String& a, const String& b)
{
	return b < a;
}

inline bool operator >(const String& a, const char* b)
{
	return b < a;
}

inline bool operator >(const char* a, const String& b)
{
	return b < a;
}

inline bool operator <=(const String& a, const String& b)
{
	return !(b < a);
}

inline bool operator <=(const String& a, const char* b)
{
	return !(b < a);
}

inline bool operator <=(const char* a, const String& b)
{
	return !(b < a);
}

inline bool operator >=(const String& a, const String& b)
{
	return !(a < b);
}

inline bool operator >=(const String& a, const char* b)
{
	return !(a < b);
}

inline bool operator >=(const char* a, const String& b)
{
	return !(a < b);
}

// Concatenation operators optimized for fast creation and small footprint.

inline String operator +(const String& a, const char* b)
{
	return String(a.CString(), a.size(), b, Strlen(b), 1);
}

inline String operator +(const String& a, char b)
{
	return String(a.CString(), a.size(), &b, 1, 1);
}

inline String operator +(const char* a, const String& b)
{
	return String(a, Strlen(a), b.CString(), b.size(), 1);
}

inline String operator +(char a, const String& b)
{
	return String(&a, 1, b.CString(), b.size(), 1);
}

inline String operator +(const String& a, const String& b)
{
	return String(a.CString(), a.size(), b.CString(), b.size(), 1);
}



template <class StringType = String>
class StringTokenizer
{
public:
	typedef StringType										StringType;

	StringTokenizer( const StringType& str = StringType(), const StringType& delimiters = " \t\n\r" )
		: m_currentIndex(0), m_string(str), m_delimiters(delimiters)
	{
	}

	u32 Position() const { return m_currentIndex; }

	StringType& GetString() { return m_string; }
	const StringType& GetString() const { return m_string; }

	StringType& GetDelimiters() { return m_delimiters; }
	const StringType& GetDelimiters() const { return m_delimiters; }

	void SetString( const StringType& str, u32 startIndex = 0 )
	{
		m_currentIndex = startIndex;
		m_string = str;
	}

	void SetDelimiters( const StringType& delimiters ) { m_delimiters = delimiters; }
	void SetPosition( u32 position )
	{
		m_currentIndex = position < m_string.Size() ? position : m_string.Size();
	}

	bool Next( StringType& token, bool keepStringLiterals = true )
	{
		m_currentIndex = m_string.GetToken( token, m_currentIndex, m_delimiters, keepStringLiterals );
		return m_currentIndex != StringType::npos;
	}

	/// @depricated
	/// For backwards compatability with the old Tokenizer::GetToken();
	static bool GetToken(const String& str, const String& delimiters, u32& index, String& token)
	{
		index = str.GetToken(token, index, delimiters, true);
		return index != StringType::npos;
	}

protected:
	u32 m_currentIndex;
	StringType m_string;
	StringType m_delimiters;

};



#ifdef _MSC_VER
	#pragma warning (pop)
#endif


CE_NAMESPACE_END


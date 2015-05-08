//////////////////////////////////////
// Fast Container Library //
// MIT License - Copyright (c) 2012 //
//////////////////////////////////////

#pragma once

#include "Catastrophe/Core/PlatformString.h"
#include "Catastrophe/Core/Algorithm/Copy.h"
#include "Catastrophe/Core/Algorithm/Search.h"
#include "Catastrophe/Core/Containers/String.h"
#include "Catastrophe/Core/Containers/Vector.h"
#include "Catastrophe/Core/Containers/StringVector.h"

#ifdef _MSC_VER
	#pragma warning ( push )
	#pragma warning ( disable : 4706 ) // assignment within conditional expression
#endif

CE_NAMESPACE_BEGIN


String::String()
{
	InitializeShort();
}


String::String(int value)
{
	u32 size = Itoa(value, _s.data);
	SetSize(size);
}


String::String(float value)
{
	u32 size = Ftoa(value, _s.data);
	SetSize(size);
}


String::String(char c)
{
	InitializeShort();
	AppendUnchecked(c);
}


String::String(const char* str, u32 stringLength)
{
	InitializeCapacity(stringLength);
	AppendUnchecked(str, stringLength);
}


String::String(const char* str)
{
	const u32 stringLength = Strlen(str);
	InitializeCapacity(stringLength);
	AppendUnchecked(str, stringLength);
}


String::String(u32 numChars, char c)
{
	InitializeCapacity(numChars);
	AppendUnchecked(numChars, c);
}


String::String(const String& str)
{
	InitializeCapacity( str.size() );
	AppendUnchecked(str);
}


String::String(const StringRef& str)
{
	InitializeCapacity(str.size());
	AppendUnchecked(str.m_begin, str.m_end);
}


String::String(const char* first, const char* last)
{
	InitializeCapacity( u32(last - first) );
	AppendUnchecked( first, last );
}


String::String( u32 bufferLength, const char* format, ... )
{
	InitializeCapacity(bufferLength);

	va_list args;
	va_start(args, format);

	int numBytesWritten = vsnprintf(data(), Capacity(), format, args);
	if( numBytesWritten < 0 )
		numBytesWritten = 0; // Bad format?

	SetSize(numBytesWritten);

	va_end(args);
}


String::String(const char* str1, const u32 nBytes1, const char* str2, const u32 nBytes2, int allocationFlags)
{
	InitializeCapacity(nBytes1 + nBytes2);

	char* p = end();
	Memory::Memcpy(p, str1, nBytes1);
	Memory::Memcpy(p + nBytes1, str2, nBytes2);
	SetSize(nBytes1 + nBytes2);
}


void String::Join(const StringVector& stringArray, const String& seperator)
{
	Join(&*stringArray.begin(), stringArray.Size(), seperator);
}


void String::Join(const String* stringArray, u32 arraySize, const String& seperator)
{
	if( UNLIKELY(arraySize == 0) )
		return;

	// Iterate over the string array and Find the combined length to get
	// the total capacity for our allocator to prevent possible continuous reallocations.
	u32 capacity = seperator.size() * arraySize;
	for(u32 i(0); i != arraySize; ++i)
		capacity += stringArray[i].size();

	AssureCapacity(capacity);

	AppendUnchecked(stringArray[0]);
	for(u32 i(1); i != arraySize; ++i)
	{
		AppendUnchecked(seperator);
		AppendUnchecked(stringArray[i]);
	}
}


String String::Joined(const StringVector& stringArray, const String& seperator) const
{
	return Joined(&*stringArray.begin(), stringArray.Size(), seperator);
}


String String::Joined(const String* stringArray, u32 arraySize, const String& seperator) const
{
	String str(*this);
	str.Join(stringArray, arraySize, seperator);
	return str;
}


void String::Split(StringVector& outStrings, const String& delimiters, bool keepStringLiterals) const
{
	u32 currentIndex = 0;
	String token;
	while( (currentIndex = GetToken(token, currentIndex, delimiters, keepStringLiterals) != npos) )
		outStrings.Add(token);
}


u32 String::GetToken( String& token, u32 startIndex, const String& delimiters, bool keepStringLiterals ) const
{
	u32 beginIndex;
	u32 endIndex;

	beginIndex = FindFirstNotOf( delimiters, startIndex );

	if( beginIndex == npos ) 
		return npos;

	const char* pBegin = begin();
	const char* pEnd = end();

	if( keepStringLiterals && pBegin[beginIndex] == '"' ) //string literal can contain delimiters
	{
		endIndex = FindFirstOf( '"', beginIndex + 1 );
		if( endIndex < u32(pEnd - pBegin) )
			++endIndex;
	}
	else
	{
		endIndex = FindFirstOf( delimiters, beginIndex + 1 );
	}

	if( endIndex == npos )
		endIndex = size();

	CE_ASSERT(endIndex >= beginIndex);
	token.Assign( begin() + beginIndex, endIndex - beginIndex );

	return endIndex;
}


void String::Reverse()
{
	Algorithm::Reverse(begin(), end());
}


String& String::TrimStart()
{
	return TrimStart(" \t");
}


String& String::TrimStart(const String& delimiters)
{
	const char* first = delimiters.begin();
	const char* last = delimiters.end();
	if( LIKELY(first != last) )
	{
		const char* mBegin = begin();
		const char* i = mBegin;
		const char* j = end();
		for( ; i != j; ++i )
			if( Algorithm::Find(first, last, *i) == last )
				break;

		if(mBegin != i)
		{
			u32 newSize = u32(j - i);
			Memory::Memcpy((void*)mBegin, (const void*)i, newSize);
			SetSize(newSize);
		}
	}

	return *this;
}


String& String::TrimEnd()
{
	return TrimEnd(" \t");
}


String& String::TrimEnd(const String& delimiters)
{
	const char* first = delimiters.begin();
	const char* last = delimiters.end();
	if( LIKELY(first != last) )
	{
		const char* mBegin = begin();
		const char* mEnd = end();
		const char* i = mEnd;
		for( ; i != mBegin; --mEnd )
			if( Algorithm::Find(first, last, *--i) == last )
				break;

		SetSize(u32(mEnd - mBegin));
	}

	return *this;
}


String& String::Trim()
{
	TrimEnd();
	TrimStart();

	return *this;
}


String& String::Trim(const String& delimiters)
{
	TrimEnd(delimiters);
	TrimStart(delimiters);

	return *this;
}


String String::Trimmed() const
{
	return String(TrimmedRef());
}


StringRef String::TrimmedRef() const
{
	const char* trimBegin = begin();
	const char* trimEnd = end();

	for( ; trimBegin != trimEnd; ++trimBegin)
		if(!::IsWhitespace(*trimBegin))
			break;

	for( ; trimEnd != trimBegin; --trimEnd)
		if(!::IsWhitespace(*trimEnd - 1))
			break;

	return StringRef(trimBegin, trimEnd);
}


void String::AddTrailingSlash()
{
	if(!Empty())
	{
		const char lastChar = Back();
		if(lastChar != '/' || lastChar != '\\')
			Add('/');
	}
}


void String::RemoveTrailingSlash()
{
	if(!Empty())
	{
		const char lastChar = Back();
		if(lastChar == '/' || lastChar == '\\')
			PopBack();
	}
}


bool String::Contains(const String& substring, u32 startIndex) const
{
	return FindFirstSubstring(substring, startIndex) != npos;
}


bool String::Contains(const StringRef& substring, u32 startIndex) const
{
	return FindFirstSubstring(substring, startIndex) != npos;
}


bool String::Contains( char c, u32 startIndex ) const
{
	return FindFirstOf(c, startIndex) != npos;
}


String String::GetFileExtension(bool lowercase) const
{
	String extension;

	u32 position = FindLastOf('.');
	if(position != npos)
	{
		extension = Substring(position + 1);
		if(lowercase)
			extension.MakeLower();
	}

	return extension;
}


String String::GetFileName(bool stripExtension, bool lowercase) const
{
	String filename = Replaced('\\', '/');

	u32 position = filename.FindLastOf('/');
	if(position != npos)
	{
		if(stripExtension)
		{
			position = filename.FindLastOf('.', position + 1);
			filename = filename.Substring(position, position != npos ? position - position : npos);
		}

		if(lowercase)
			filename.MakeLower();

		return filename;
	}

	return String();
}


String String::GetFilePath(bool lowercase) const
{
	String path = Replaced('\\', '/');

	u32 position = path.FindLastOf('/');
	if(position != npos)
		path = path.Substring(0, position + 1);

	if(lowercase)
		path.MakeLower();

	return path;
}


String& String::ReplaceExtension(const char* newExtension)
{
	u32 position = FindLastOf('.');
	if(position != npos)
		SetSize(position);

	Append(newExtension);
	return *this;
}


bool String::StartsWith(const char* str, u32 stringLength, bool caseSensitive) const
{
	if(UNLIKELY(u32(length()) < stringLength))
		return false;

	return String::Compare(begin(), begin() + stringLength, str, str + stringLength, caseSensitive) == 0;
}


bool String::StartsWith(char c, bool caseSensitive) const
{
	return (caseSensitive ? c == Front() : ::ToLower(c) == ::ToLower(Front()));
}


bool String::EndsWith(const char* str, u32 stringLength, bool caseSensitive) const
{
	if(UNLIKELY(u32(end() - begin()) < stringLength))
		return false;

	return String::Compare(end() - stringLength, end(), str, str + stringLength, caseSensitive) == 0;
}


bool String::EndsWith(char c, bool caseSensitive) const
{
	return (caseSensitive ? c == Back() : ::ToLower(c) == ::ToLower(Back()));
}


u32 String::FindFirstSubstring(const char* substring, u32 startIndex, u32 stringLength) const
{
	const char* pBegin = begin();
	const char* pEnd = end();
	if(LIKELY(startIndex < length()))
	{
		if(UNLIKELY(!stringLength))
			return startIndex;

		// simply using the search algorithm here seems to be the most consistent.
		const char* const it = Algorithm::Search(pBegin + startIndex, pEnd, substring, substring + stringLength);
		if(it != pEnd)
			return u32(it - pBegin);
	}

	return npos;
}


u32 String::FindLastSubstring(const char* substring, u32 startIndex, u32 stringLength) const
{
	const u32 thisSize = size();
	const char* first = begin();
	const char* last = first + (Min(thisSize - stringLength, startIndex) + stringLength);

	if(LIKELY(startIndex + stringLength < thisSize))
	{
		// if !n then we cannot return npos.
		if(UNLIKELY(stringLength == 0))
			return Min(thisSize, startIndex);

		while(first < last)
			if(*--last == *substring && Memory::Memcmp(last, substring, stringLength) == 0)
				return u32(last - begin());
	}

	return npos;
}


u32 String::FindFirstOf(const char* delimiters, u32 startIndex, u32 stringLength) const
{
	const char* pBegin = begin();
	const char* pEnd = end();
	if(LIKELY(startIndex < u32(pEnd - pBegin)))
	{
		const char* const it = Algorithm::FindFirstOf(pBegin + startIndex, pEnd, delimiters, delimiters + stringLength);
		if(it != pEnd)
			return u32(it - pBegin);
	}

	return npos;
}


u32 String::FindFirstOf(char c, u32 startIndex) const
{
	const char* pBegin = begin();
	const char* pEnd = end();
	if(LIKELY(startIndex < u32(pEnd - pBegin)))
	{
		const char* it = Algorithm::Find(pBegin + startIndex, pEnd, c);
		if(it != pEnd)
			return u32(it - pBegin);
	}

	return npos;
}


u32 String::FindFirstNotOf(const char* delimiters, u32 startIndex, u32 stringLength) const
{
	const char* pBegin = begin();
	const char* pEnd = end();
	if(LIKELY(startIndex < u32(pEnd - pBegin)))
	{
		const char* it = Algorithm::FindFirstNotOf(pBegin + startIndex, pEnd, delimiters, delimiters + stringLength);
		if(it != pEnd)
			return u32(it - pBegin);
	}

	return npos;
}


u32 String::FindFirstNotOf(char c, u32 startIndex) const
{
	const char* pBegin = begin();
	const char* pEnd = end();
	for(const char* it = pBegin + startIndex; it < pEnd; ++it)
		if(*it != c)
			return u32(it - pBegin);

	return npos;
}


u32 String::FindLastOf(const char* delimiters, u32 startIndex, u32 stringLength) const
{
	const char* pBegin = begin();
	const char* pEnd = end();
	if(LIKELY(u32(pEnd - pBegin) && startIndex))
	{
		const char* first = pBegin;
		const char* last = pBegin + ::Min(u32(pEnd - pBegin) - stringLength, startIndex) + stringLength;
		const char* it = Algorithm::FindLastOf(first, last, delimiters, delimiters + stringLength);
		if(it != pEnd)
			return u32(it - pBegin);
	}

	return npos;
}


u32 String::FindLastOf(char c, u32 startIndex) const
{
	const char* pBegin = begin();
	const char* pEnd = end();
	const u32 thisSize = u32(pEnd - pBegin);
	if(LIKELY(thisSize > 0))
	{
		const char* first = pBegin;
		const char* last = pBegin + (Min(thisSize - 1, startIndex) + 1);

		while(first != last)
			if(*--last == c)
				return u32(last - first);
	}

	return npos;
}


u32 String::FindLastNotOf(const char* delimiters, u32 startIndex, u32 stringLength) const
{
	const char* pBegin = begin();
	const char* pEnd = end();
	if(LIKELY(u32(pEnd - pBegin) && startIndex))
	{
		const char* first = pBegin;
		const char* last = pBegin + (Min(u32(pEnd - pBegin) - stringLength, startIndex) + stringLength);
		const char* it = Algorithm::FindLastNotOf(first, last, delimiters, delimiters + stringLength);
		if(it != pEnd)
			return u32(it - pBegin);
	}

	return npos;
}


u32 String::FindLastNotOf(char c, u32 startIndex) const
{
	const char* pBegin = begin();
	const char* pEnd = end();
	const char* first = pBegin;
	const char* last = pBegin + Math::Min(u32(pEnd - pBegin) - 1, (u32)startIndex + 1);
	while(last != first)
		if(*--last != c)
			return u32(last - first);

	return npos;
}


int String::Compare(const char* first1, const char* last1, const char* first2, const char* last2, bool caseSensitive)
{
	if(!caseSensitive)
		return Algorithm::LexicographicalCompare(first1, last1, first2, last2, CaseInsensitiveCompare);

	return Memory::Memcmp( first1, last1, first2, last2 );
}


int String::Compare(const char* str1, u32 stringLength1, const char* str2, u32 stringLength2, bool caseSensitive)
{
	if(!caseSensitive)
		return Algorithm::LexicographicalCompare(str1, str1 + stringLength1, str2, str2 + stringLength2, CaseInsensitiveCompare);

	return Memory::Memcmp( str1, stringLength1, str2, stringLength2 );
}


String& String::MakeUpper(u32 startIndex, u32 stringLength)
{
	char* pBegin = begin();
	char* pEnd = end();
	char* first = pBegin + startIndex;
	char* last = (stringLength == npos ? pEnd : first + stringLength);

	CE_ASSERT(first <= last);
	CE_ASSERT(last <= pEnd);

	for( ; first != last; ++first )
		*first = ::ToUpper(*first);

	return *this;
}


String& String::MakeLower(u32 startIndex, u32 stringLength)
{
	char* pBegin = begin();
	char* pEnd = end();
	char* first = pBegin + startIndex;
	char* last = (stringLength == npos ? pEnd : first + stringLength);

	CE_ASSERT(first <= last);
	CE_ASSERT(last <= pEnd);

	for( ; first != last; ++first )
		*first = ::ToLower(*first);

	return *this;
}


String& String::MakeUpper()
{
	return MakeUpper(0, size());
}


String& String::MakeLower()
{
	return MakeLower(0, size());
}


String String::ToUpper() const
{
	return String(*this).MakeLower();
}


String String::ToLower() const
{
	return String(*this).MakeLower();
}


String& String::Assign(const char* str, u32 stringLength)
{
	AssureCapacity(stringLength);

	Memory::Memcpy(begin(), str, stringLength);
	SetSize(stringLength);

	return *this;
}


String& String::Assign(u32 bufferLength, const char* format, ...)
{
	va_list args;
	va_start(args, format);

	AssureCapacity(bufferLength);
	int numBytesWritten = vsnprintf(end(), Capacity(), format, args);
	if(numBytesWritten < 0)
		numBytesWritten = 0;

	SetSize(numBytesWritten);

	va_end(args);
	return *this;
}


void String::Resize(u32 newSize, char c)
{
	const u32 thisSize = size();

	if(newSize > thisSize)
		Append(u32(newSize - thisSize), c);

	else if(newSize < thisSize)
		SetSize(newSize);
}


void String::Reserve(u32 capacity)
{
	if(capacity > Capacity())
		SetCapacity(capacity);
}


void String::SetCapacity(u32 newCapacity)
{
	if( IsShort() )
	{
		if( newCapacity > kShortCapacity )
			GrowShortString(newCapacity);

		return;
	}

	//if( newCapacity <= kShortCapacity )

	// Align the memory size to prevent wasted bytes.
	newCapacity = Memory::Align(newCapacity + 1);
	if(newCapacity == Capacity())
		return;

	char* ptr = Allocate(newCapacity);
	const u32 thisSize = size();
	const u32 newSize = thisSize > newCapacity ? newCapacity : thisSize;

	if(thisSize > 0)
		Memory::Memcpy(ptr, begin(), newSize);

	Deallocate();

	_l.ptr = ptr;
	_l.capacity = newCapacity;
	_s.size = 0;

	SetSize(newSize);
}


String& String::Append(const char* str, u32 stringLength)
{
	if(LIKELY(stringLength != 0))
	{
		AssureCapacity(stringLength);
		AppendUnchecked(str, stringLength);
	}

	return *this;
}


String& String::Append(u32 numChars, char c)
{
	if(LIKELY(numChars != 0))
	{
		AssureCapacity(numChars);
		AppendUnchecked(numChars, c);
	}

	return *this;
}


String& String::Append(u32 bufferLength, const char* format, ...)
{
	va_list args;
	va_start(args, format);

	AssureCapacity(bufferLength);

	const u32 thisSize = size();
	int numBytesWritten = vsnprintf(end(), Unused(), format, args);
	if(numBytesWritten < 0)
		numBytesWritten = 0;

	SetSize(thisSize + numBytesWritten);

	va_end(args);
	return *this;
}


String& String::AppendUnchecked(const char* str, u32 stringLength)
{
	const u32 thisSize = size();
	CE_ASSERT(thisSize + stringLength <= Capacity());

	Memory::Memcpy(end(), str, stringLength);
	SetSize(thisSize + stringLength);

	return *this;
}


String& String::AppendUnchecked(const char* first, const char* last)
{
	const u32 stringLength = u32(last - first);
	const u32 thisSize = size();
	CE_ASSERT(thisSize + stringLength <= Capacity());

	Memory::Memcpy(end(), first, stringLength);
	SetSize(thisSize + stringLength);

	return *this;
}


String& String::AppendUnchecked(u32 numChars, char c)
{
	const u32 thisSize = size();
	CE_ASSERT(thisSize < Capacity());

	Memory::Memset(end(), c, numChars);
	SetSize(thisSize + numChars);

	return *this;
}


String& String::Insert(const char* position, const char* first, const char* last)
{
	CE_ASSERT(IteratorIsValid(position));
	CE_ASSERT(first <= last);

	char* pBegin = begin();
	char* pEnd = end();

	if(IteratorIsValid(first) && last > position)
	{
		//if we're inserting from ourself we have to create a temp object and recurse.
		String temp(first, last);
		return Insert(position, temp.begin(), temp.end());
	}

	u32 stringLength = u32(last - first);
	u32 thisSize = u32(pEnd - pBegin);

	if(LIKELY(stringLength != 0))
	{
		// If we're out of room, reallocate
		if(thisSize + stringLength > Capacity())
		{
			u32 newCapacity = CalculateNewCapacity(stringLength);
			char* ptr = Allocate(newCapacity);
			u32 distance = u32(position - pBegin);

			Memory::Memcpy(ptr, pBegin, distance);
			Memory::Memcpy(ptr + distance, first, stringLength);
			Memory::Memcpy(ptr + distance + stringLength, pBegin + distance, thisSize - distance);

			Deallocate();

			_l.ptr = ptr;
			_l.capacity = newCapacity;
			_s.size = 0;
		}

		else if(position == pEnd)
		{
			Memory::Memcpy(pEnd, first, stringLength);
		}

		else
		{
			Memory::Memmove((void*)(position + stringLength), position, u32(pEnd - position));
			Memory::Memcpy((void*)position, first, stringLength);
		}

		SetSize(thisSize + stringLength);
	}

	return *this;
}


String& String::InsertAt(u32 position, u32 numChars, char c)
{
	char* pBegin = begin();
	char* pEnd = end();
	const u32 thisSize = u32(pEnd - pBegin);

	CE_ASSERT(position <= thisSize);

	if(numChars > 0)
	{
		if(thisSize + numChars >= Capacity())
		{
			u32 newCapacity = CalculateNewCapacity(numChars);
			char* ptr = Allocate(newCapacity);

			Memory::Memcpy(ptr, pBegin, position);
			Memory::Memset(ptr + position, c, numChars);
			Memory::Memcpy(ptr, pBegin + position, thisSize - position);

			Deallocate();

			_l.ptr = ptr;
			_l.capacity = newCapacity;
			_s.size = 0;
		}

		else if(pBegin + position == pEnd)
		{
			Memory::Memset(pEnd, c, numChars);
		}

		else
		{
			char* first = pBegin + position;
			char* last = first + numChars;
			Memory::Memmove(last, first, u32(pEnd - first));
			Memory::Memset(first, c, numChars);
		}

		SetSize(thisSize + numChars);
	}

	return *this;
}


void String::Erase(const char* position)
{
	CE_ASSERT(IteratorIsValid(position));

	char* pEnd = end();
	if(position != pEnd - 1)
		Memory::Memmove((void*)position, position + 1, u32(pEnd - position));

	SetSize(size() - 1);
}


void String::Erase(const char* first, const char* last)
{
	CE_ASSERT( first <= last && IteratorIsValid(first) && IteratorIsValid(last));

	if(LIKELY(first != last))
	{
		char* pEnd = end();
		if(last != pEnd)
			Memory::Memmove((void*)first, last, u32(pEnd - last));

		SetSize(size() - u32(last - first));
	}
}


String String::Substring(u32 position, u32 stringLength) const
{
	const char* pEnd = end();
	const char* first = begin() + position;
	const char* last = (stringLength > size() ? pEnd : (first + stringLength > pEnd ? pEnd : first + stringLength));

	return String(first, last);
}


StringRef String::SubstringRef(u32 position, u32 stringLength) const
{
	const char* first = begin() + position;
	const char* last = (stringLength > size() ? end() : first + stringLength);

	return StringRef(first, last);
}


String& String::ReplaceAll(char oldChar, char newChar)
{
	Algorithm::Replace(begin(), end(), oldChar, newChar);
	return *this;
}


String String::Replaced(char oldChar, char newChar) const
{
	String str(*this);
	str.ReplaceAll(oldChar, newChar);
	return str;
}


String& String::Replace(char* beginPosition, char* endPosition, const char* first, const char* last)
{
	CE_ASSERT(IteratorIsValid(beginPosition) && IteratorIsValid(endPosition));
	CE_ASSERT(beginPosition <= endPosition && first <= last);

	const u32 stringLength1 = u32(endPosition - beginPosition);
	const u32 stringLength2 = u32(last - first);
	u32 difference(0);

	String self;
	if(first > beginPosition && beginPosition < end())
	{
		self.Assign(first, last);
		first = self.begin();
		last = self.end();
	}

	if(stringLength2 != stringLength1)
	{
		//difference = (stringLength2 > stringLength1) ? stringLength2 - stringLength1 : stringLength1 - stringLength2;
		difference = stringLength2 - stringLength1;

		if(stringLength2 > stringLength1)
			AssureCapacity(difference);

		Memory::Memmove(beginPosition + stringLength2, endPosition, u32(end() - endPosition));
		Memory::Memmove(beginPosition, first, stringLength2);

		SetSize(size() + difference);
	}
	else
	{
		Memory::Memmove(beginPosition, first, stringLength2);
	}

	return *this;
}


String& String::Replace(char* first, char* last, u32 numChars, char c)
{
	CE_ASSERT(IteratorIsValid(first) && IteratorIsValid(last));
	CE_ASSERT(first <= last);

	const u32 replaceSize = u32(last - first);
	const u32 minNum = Min(replaceSize, numChars);

	if(minNum > 0)
		Memory::Memset(first, c, minNum);

	if(numChars < replaceSize)
		Erase(first + numChars, first + replaceSize);
	else if(replaceSize < numChars)
		Insert(last, numChars - replaceSize, c);

	return *this;
}


String& String::ReplaceAll(const String& regex, const String& replacement)
{
	for(u32 position(0); (position = FindFirstSubstring(regex, position)) != npos; )
	{
		ReplaceAt(position, regex.length(), replacement);
		position += replacement.length();
	}

	return *this;
}


void String::InitializeLong(u32 nBytes)
{
	// Align capacity to prevent wasted memory.
	nBytes = Memory::Align(nBytes + 1);
	char* ptrMemory = Allocate(nBytes);

	_l.ptr = ptrMemory;
	_l.end = ptrMemory;
	_l.capacity = nBytes;
	*_l.end = 0;

	// Unset short mask
	_s.size = 0;
}


void String::GrowShortString(u32 amount)
{
	u32 newCapacity = Math::Max<int>(kShortCapacity + amount, kShortCapacity * 2 );
	newCapacity = Memory::Align(newCapacity + 1, CE_DEFAULT_STRING_SIZE_ALIGNMENT);

	char* p = Allocate(newCapacity);
	Memory::Memcpy(p, _s.data, size());

	_l.ptr = p;
	_l.end = p + size();
	_l.capacity = newCapacity;
	*_l.end = 0;

	// Unset short mask
	_s.size = 0;
}


void String::GrowLongString(u32 amount)
{
	u32 newCapacity = CalculateNewCapacity(amount);
	SetCapacity(newCapacity);
}


char* String::Allocate(u32 nBytes, int flags)
{
	// We must always zero any short bits when the string is dynamically allocated.
	// However, we need to hold on to the size value for a bit longer.
	//_s.size = 0;

	return (char*)Memory::AllocateString( nBytes * sizeof(char), flags );
}


void String::Deallocate()
{
	// Check to see whether we have any allocated memory first.
	if( _s.size == 0 )
		Memory::DeallocateString( begin(), size() * sizeof(char) );
}


void String::AssureCapacity(u32 nCharsToAdd)
{
	if(_s.size)
	{
		// Switch to long string if buffer is too small
		if( u32(_s.size >> 1) + nCharsToAdd >= kShortCapacity )
			GrowShortString(nCharsToAdd);
	}
	else
	{
		// Increase capacity if we don't have enough memoty
		if( u32(_l.end - _l.ptr) + nCharsToAdd + 1 >= _l.capacity )
			GrowLongString(nCharsToAdd);
	}
}


u32 String::CalculateNewCapacity(u32 growth)
{
	// Grow by at least double to avoid more reallocations.
	u32 oldCapacity = Capacity() + 1;
	return Math::Max(
		Math::Max<u32>(oldCapacity * 2, oldCapacity + growth + 1),
		(kShortCapacity + 1) * 2
	);
}




CE_NAMESPACE_END


#ifdef _MSC_VER
	#pragma warning ( pop )
#endif


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

#include "IO/Serializer.h"
#include "MathTypes.h"

CE_NAMESPACE_BEGIN


/*
#ifdef BIG_ENDIAN
template <class T, size_t N> inline
void __Internal_ByteSwap(T& value)
{
}

template <class T> inline
void __Internal_ByteSwap<T, 1>(T& value)
{
}

template <class T> inline
void __Internal_ByteSwap<T, 2>(T& value)
{
	value = (((value >> 8) & 0xff) | ((value & 0xff) << 8));
}

template <class T> inline
void __Internal_ByteSwap<T, 4>(T& value)
{
	value = ((val & 0xff000000) >> 24) | (val & 0x00ff0000) >>  8) |
			(val & 0x0000ff00) <<  8) | (val & 0x000000ff) << 24));
}

template <> inline void __Internal_ByteSwap<float, 4>(T& value)
{
	__Internal_ByteSwap<int, 4>(*reinterpret_cast<int*>(&value));
}

template <class T> inline
void __Internal_ByteSwap_Dispatch(T& value)
{
	__Internal_ByteSwap<T, sizeof(T)>(value);
}

#define BYTE_SWAP(x) __Internal_ByteSwap(x)
*/


bool Serializer::WriteInt(int value)
{
	return Write(&value, sizeof(value)) == sizeof(value);
}


bool Serializer::WriteShort(short value)
{
	return Write(&value, sizeof(value)) == sizeof(value);
}


bool Serializer::WriteByte(signed char value)
{
	return Write(&value, sizeof(value)) == sizeof(value);
}


bool Serializer::WriteUInt(unsigned int value)
{
	return Write(&value, sizeof(value)) == sizeof(value);
}


bool Serializer::WriteUShort(unsigned short value)
{
	return Write(&value, sizeof(value)) == sizeof(value);
}


bool Serializer::WriteUByte(unsigned char value)
{
	return Write(&value, sizeof(value)) == sizeof(value);
}


bool Serializer::WriteBool(bool value)
{
	return WriteUByte(value ? 1 : 0) == 1;
}


bool Serializer::WriteFloat(float value)
{
	return Write(&value, sizeof(value)) == sizeof(value);
}


bool Serializer::WritePoint(const Point& value)
{
	return WriteInt(value.x) && WriteInt(value.y);
}


bool Serializer::WriteRect(const Rect& value)
{
	return WritePoint(value.pos) && WritePoint(value.size);
}


bool Serializer::WriteRectf(const Rectf& value)
{
	return WriteVector2(value.min) && WriteVector2(value.max);
}


bool Serializer::WriteVector2(const Vector2& value)
{
	return WriteFloat(value.x) && WriteFloat(value.y);
}


bool Serializer::WriteVector3(const Vector3& value)
{
	return (WriteFloat(value.x) && WriteFloat(value.y) && WriteFloat(value.z));
}


bool Serializer::WriteVector4(const Vector4& value)
{
	return (WriteFloat(value.x) && WriteFloat(value.y) && WriteFloat(value.z) && WriteFloat(value.w));
}


bool Serializer::WriteColor(const Color& value)
{
	return WriteInt(value.packed_value);
}


bool Serializer::WriteColorf(const Colorf& value)
{
	return (WriteFloat(value.r) && WriteFloat(value.g) && WriteFloat(value.b) && WriteFloat(value.a));
}


bool Serializer::WriteMatrix(const Matrix& value)
{
	return WriteFloatArray(&value[0], 16);
}


bool Serializer::WriteShortArray(const short* ptr, size_t n)
{
	const size_t n_bytes = sizeof(short) * n;
	return Write(ptr, n_bytes) == n_bytes;
}


bool Serializer::WriteIntArray(const int* ptr, size_t n)
{
	const size_t n_bytes = sizeof(int) * n;
	return Write(ptr, n_bytes) == n_bytes;
}


bool Serializer::WriteFloatArray(const float* ptr, size_t n)
{
	const size_t n_bytes = sizeof(float) * n;
	return Write(ptr, n_bytes) == n_bytes;
}


bool Serializer::WriteString(const fc::string& value)
{
	size_t length = value.length();
	if( Write(&length, sizeof length) != sizeof length )
		return false;

	return Write(value.c_str(), length) == length;
}


bool Serializer::WriteString(const char* value)
{
	size_t length = strlen(value);
	if( Write(&length, sizeof length) != sizeof length )
		return false;

	return Write(value, length) == length;
}


bool Serializer::WriteLine(const fc::string& value, bool newline)
{
	bool success = true;
	success = Write(value.c_str(), value.length()) == value.length();
	if(newline && success)
	{
		success = WriteUByte(13) && WriteUByte(10);
	}

	return success;
}

/*
// operator << overloads
Serializer& Serializer::operator <<(int value) { bool success = WriteInt(value); CE_ASSERT(success); return *this; }
Serializer& Serializer::operator <<(short value) { bool success = WriteShort(value); CE_ASSERT(success); return *this; }
Serializer& Serializer::operator <<(char value) { bool success = WriteByte(value); CE_ASSERT(success); return *this; }
Serializer& Serializer::operator <<(unsigned int value) { bool success = WriteUInt(value); CE_ASSERT(success); return *this; }
Serializer& Serializer::operator <<(unsigned short value) { bool success = WriteUShort(value); CE_ASSERT(success); return *this; }
Serializer& Serializer::operator <<(unsigned char value) { bool success = WriteUByte(value); CE_ASSERT(success); return *this; }
Serializer& Serializer::operator <<(bool value) { bool success = WriteBool(value); CE_ASSERT(success); return *this; }
Serializer& Serializer::operator <<(float value) { bool success = WriteFloat(value); CE_ASSERT(success); return *this; }

Serializer& Serializer::operator <<(const Rect& value) { bool success = WriteRect(value); CE_ASSERT(success); return *this; }
Serializer& Serializer::operator <<(const Rectf& value) { bool success = WriteRectf(value); CE_ASSERT(success); return *this; }
Serializer& Serializer::operator <<(const Point& value) { bool success = WritePoint(value); CE_ASSERT(success); return *this; }
Serializer& Serializer::operator <<(const Vector2& value) { bool success = WriteVector2(value); CE_ASSERT(success); return *this; }
Serializer& Serializer::operator <<(const Vector3& value) { bool success = WriteVector3(value); CE_ASSERT(success); return *this; }
Serializer& Serializer::operator <<(const Vector4& value) { bool success = WriteVector4(value); CE_ASSERT(success); return *this; }
Serializer& Serializer::operator <<(const Color& value) { bool success = WriteColor(value); CE_ASSERT(success); return *this; }
Serializer& Serializer::operator <<(const Colorf& value) { bool success = WriteColorf(value); CE_ASSERT(success); return *this; }
Serializer& Serializer::operator <<(const Matrix& value) { bool success = WriteMatrix(value); CE_ASSERT(success); return *this; }

Serializer& Serializer::operator <<(const fc::string& value) { bool success = WriteString(value); CE_ASSERT(success); return *this; }
Serializer& Serializer::operator <<(const char* value) { bool success = WriteString(value); CE_ASSERT(success); return *this; }
*/

CE_NAMESPACE_END

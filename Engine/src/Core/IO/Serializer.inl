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

#include "Catastrophe/Core/IO/Serializer.h"
#include "Catastrophe/Core/Containers/String.h"
#include "MathTypes.h"

CE_NAMESPACE_BEGIN



bool Serializer::WriteInt(int value)
{
	return Write(&value, sizeof(value)) == sizeof(value);
}


bool Serializer::WriteShort(s16 value)
{
	return Write(&value, sizeof(value)) == sizeof(value);
}


bool Serializer::WriteChar(s8 value)
{
	return Write(&value, sizeof(value)) == sizeof(value);
}


bool Serializer::WriteUInt(u32 value)
{
	return Write(&value, sizeof(value)) == sizeof(value);
}


bool Serializer::WriteUShort(u16 value)
{
	return Write(&value, sizeof(value)) == sizeof(value);
}


bool Serializer::WriteByte(u8 value)
{
	return Write(&value, sizeof(value)) == sizeof(value);
}


bool Serializer::WriteBool(bool value)
{
	return WriteByte(value ? 1 : 0) == 1;
}


bool Serializer::WriteFloat(float value)
{
	return Write(&value, sizeof(value)) == sizeof(value);
}


bool Serializer::WritePackedRect( const PackedRect& value )
{
	return WritePackedPoint(value.position) && WritePackedPoint(value.size);
}


bool Serializer::WritePackedPoint( const PackedPoint& value )
{
	return WriteShort(value.x) && WriteShort(value.y);
}


bool Serializer::WritePoint(const Point& value)
{
	return WriteInt(value.x) && WriteInt(value.y);
}


bool Serializer::WriteRect(const Rect& value)
{
	return WritePoint(value.position) && WritePoint(value.size);
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


bool Serializer::WriteCharArray(const char* ptr, u32 numElements)
{
	const u32 nBytes = sizeof(char) * numElements;
	return Write(ptr, nBytes) == nBytes;
}


bool Serializer::WriteShortArray(const s16* ptr, u32 numElements)
{
	const u32 nBytes = sizeof(s16) * numElements;
	return Write(ptr, nBytes) == nBytes;
}


bool Serializer::WriteIntArray(const int* ptr, u32 numElements)
{
	const u32 nBytes = sizeof(int) * numElements;
	return Write(ptr, nBytes) == nBytes;
}


bool Serializer::WriteFloatArray(const float* ptr, u32 numElements)
{
	const u32 nBytes = sizeof(float) * numElements;
	return Write(ptr, nBytes) == nBytes;
}


bool Serializer::WriteString(const String& value)
{
	return WriteString(value.CString(), value.Length());
}


bool Serializer::WriteString(const char* value)
{
	return WriteString(value, (u32)strlen(value));
}


bool Serializer::WriteString(const char* value, u32 length)
{
	if( !WriteUInt(length) )
		return false;

	return Write(value, length) == length;
}


bool Serializer::WriteLine(const String& value, bool newline)
{
	bool success = true;
	success = Write(value.CString(), value.Length()) == value.Length();
	if(newline && success)
	{
		success = WriteByte(13) && WriteByte(10);
	}

	return success;
}


bool Serializer::WriteFileID( const char* id, u32 length )
{
	return Write(id, length) == length;
}


/*
// operator << overloads
Serializer& Serializer::operator <<(int value) { bool success = WriteInt(value); CE_ASSERT(success); return *this; }
Serializer& Serializer::operator <<(s16 value) { bool success = WriteShort(value); CE_ASSERT(success); return *this; }
Serializer& Serializer::operator <<(char value) { bool success = WriteByte(value); CE_ASSERT(success); return *this; }
Serializer& Serializer::operator <<(u32 value) { bool success = WriteUInt(value); CE_ASSERT(success); return *this; }
Serializer& Serializer::operator <<(u16 value) { bool success = WriteUShort(value); CE_ASSERT(success); return *this; }
Serializer& Serializer::operator <<(u8 value) { bool success = WriteUByte(value); CE_ASSERT(success); return *this; }
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

Serializer& Serializer::operator <<(const String& value) { bool success = WriteString(value); CE_ASSERT(success); return *this; }
Serializer& Serializer::operator <<(const char* value) { bool success = WriteString(value); CE_ASSERT(success); return *this; }
*/

CE_NAMESPACE_END

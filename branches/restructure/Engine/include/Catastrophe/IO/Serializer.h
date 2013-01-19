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

#include <fc/string.h>

#include "../Common.h"

CE_NAMESPACE_BEGIN


class CE_API Serializer
{
public:
	virtual ~Serializer() {}
	
	virtual size_t Write(const void* data, size_t size) = 0;
	
	bool WriteInt(int value);
	bool WriteShort(short value);
	bool WriteByte(signed char value);
	bool WriteUInt(unsigned int value);
	bool WriteUShort(unsigned short value);
	bool WriteUByte(unsigned char value);
	bool WriteBool(bool value);
	bool WriteFloat(float value);

	bool WriteRect(const Rect& value);
	bool WriteRectf(const Rectf& value);
	bool WritePoint(const Point& value);
	bool WriteVector2(const Vector2& value);
	bool WriteVector3(const Vector3& value);
	bool WriteVector4(const Vector4& value);
	bool WriteColor(const Color& value);
	bool WriteColorf(const Colorf& value);
	bool WriteMatrix(const Matrix& value);

	bool WriteShortArray(const short* ptr, size_t n);
	bool WriteIntArray(const int* ptr, size_t n);
	bool WriteFloatArray(const float* ptr, size_t n);

	bool WriteString(const fc::string& value);
	bool WriteString(const char* value);
	bool WriteLine(const fc::string& value, bool newline = true);

	/* //Should probably be formated...
	// operator << overloads for convenience.
	Serializer& operator <<(int value);
	Serializer& operator <<(short value);
	Serializer& operator <<(char value);
	Serializer& operator <<(unsigned int value);
	Serializer& operator <<(unsigned short value);
	Serializer& operator <<(unsigned char value);
	Serializer& operator <<(bool value);
	Serializer& operator <<(float value);

	Serializer& operator <<(const Rect& value);
	Serializer& operator <<(const Rectf& value);
	Serializer& operator <<(const Point& value);
	Serializer& operator <<(const Vector2& value);
	Serializer& operator <<(const Vector3& value);
	Serializer& operator <<(const Vector4& value);
	Serializer& operator <<(const Color& value);
	Serializer& operator <<(const Colorf& value);
	Serializer& operator <<(const Matrix& value);

	Serializer& operator <<(const fc::string& value);
	Serializer& operator <<(const char* value);
	*/

};



CE_NAMESPACE_END

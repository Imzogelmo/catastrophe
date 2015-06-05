// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files ( the "Software" ), to deal
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

CE_NAMESPACE_BEGIN


class CE_API Serializer
{
public:
	virtual ~Serializer() {}
	
	virtual u32 Write( const void* data, u32 size ) = 0;
	
	bool WriteBool( bool value );
	bool WriteChar( s8 value );
	bool WriteShort( s16 value );
	bool WriteInt( s32 value );
	bool WriteByte( u8 value );
	bool WriteUShort( u16 value );
	bool WriteUInt( u32 value );
	bool WriteFloat( float value );
	bool WritePackedRect( const PackedRect& value );
	bool WritePackedPoint( const PackedPoint& value );
	bool WriteRect( const Rect& value );
	bool WriteRectf( const Rectf& value );
	bool WritePoint( const Point& value );
	bool WriteVector2( const Vector2& value );
	bool WriteVector3( const Vector3& value );
	bool WriteVector4( const Vector4& value );
	bool WriteColor( const Color& value );
	bool WriteColorf( const Colorf& value );
	bool WriteMatrix( const Matrix& value );

	bool WriteCharArray( const char* ptr, u32 numElements );
	bool WriteShortArray( const s16* ptr, u32 numElements );
	bool WriteIntArray( const int* ptr, u32 numElements );
	bool WriteFloatArray( const float* ptr, u32 numElements );

	bool WriteString( const String& value );
	bool WriteString( const char* value );
	bool WriteString(const char* value, u32 length);
	bool WriteLine( const String& value, bool newline = true );
	bool WriteFileID( const char* id, u32 length );

	Serializer& operator <<(bool value) { WriteBool(value); return *this; }
	Serializer& operator <<(s8 value) { WriteByte(value); return *this; }
	Serializer& operator <<(s16 value) { WriteShort(value); return *this; }
	Serializer& operator <<(s32 value) { WriteInt(value); return *this; }
	Serializer& operator <<(u8 value) { WriteByte(value); return *this; }
	Serializer& operator <<(u16 value) { WriteUShort(value); return *this; }
	Serializer& operator <<(u32 value) { WriteUInt(value); return *this; }
	Serializer& operator <<(float value) { WriteFloat(value); return *this; }

	Serializer& operator <<(const Rect& value) { WriteRect(value); return *this; }
	Serializer& operator <<(const Rectf& value) { WriteRectf(value); return *this; }
	Serializer& operator <<(const Point& value) { WritePoint(value); return *this; }
	Serializer& operator <<(const PackedPoint& value) { WritePackedPoint(value); return *this; }
	Serializer& operator <<(const PackedRect& value) { WritePackedRect(value); return *this; }
	Serializer& operator <<(const Vector2& value) { WriteVector2(value); return *this; }
	Serializer& operator <<(const Vector3& value) { WriteVector3(value); return *this; }
	Serializer& operator <<(const Vector4& value) { WriteVector4(value); return *this; }
	Serializer& operator <<(const Color& value) { WriteColor(value); return *this; }
	Serializer& operator <<(const Colorf& value) { WriteColorf(value); return *this; }

	template <u32 N>
	Serializer& operator <<(const StaticString<N>& value)
	{
		WriteString(value.CString(), value.Size());
		return *this;
	}

	Serializer& operator <<(const String& value) { WriteString(value.CString(), value.Size()); return *this; }
	Serializer& operator <<(const char* value) { WriteString(value); return *this; }

};



CE_NAMESPACE_END

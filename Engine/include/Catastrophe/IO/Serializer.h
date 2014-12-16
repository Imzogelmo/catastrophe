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

#include <fc/string.h>

#include "../Common.h"

CE_NAMESPACE_BEGIN


class CE_API Serializer
{
public:
	virtual ~Serializer() {}
	
	virtual u32 Write( const void* data, u32 size ) = 0;
	
	bool WriteInt( int value );
	bool WriteShort( s16 value );
	bool WriteByte( s8 value );
	bool WriteUInt( u32 value );
	bool WriteUShort( u16 value );
	bool WriteUByte( u8 value );
	bool WriteBool( bool value );
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

	bool WriteShortArray( const s16* ptr, u32 n );
	bool WriteIntArray( const int* ptr, u32 n );
	bool WriteFloatArray( const float* ptr, u32 n );

	bool WriteString( const String& value );
	bool WriteString( const char* value );
	bool WriteLine( const String& value, bool newline = true );
	bool WriteFileID( const char* id, u32 length );

};



CE_NAMESPACE_END

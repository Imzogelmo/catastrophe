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

#include "Catastrophe/Core/Containers/String.h"

CE_NAMESPACE_BEGIN


class CE_API Deserializer
{
public:
	virtual ~Deserializer() {}
	
	virtual u32 Read( void* dest, u32 size ) = 0;
	virtual u32 Seek( u32 position ) = 0;
	virtual bool IsEof() const = 0;
	virtual u32 Position() const = 0;
	virtual u32 Size() const = 0;

	/// Reads a 8-bit boolean value
	bool ReadBool();

	/// Reads a 8-bit signed integer
	char ReadChar();

	/// Reads a 16-bit signed integer
	s16 ReadShort();

	/// Reads a 32-bit signed integer
	s32 ReadInt();

	/// Reads a 8-bit unsigned integer
	u8 ReadByte();

	/// Reads a 16-bit unsigned integer
	u16 ReadUShort();

	/// Reads a 32-bit unsigned integer
	u32 ReadUInt();

	/// Reads a 32-bit float
	float ReadFloat();

	bool ReadInt( int& value );
	bool ReadShort( s16& value );
	bool ReadChar( char& value );
	bool ReadUInt( u32& value );
	bool ReadUShort( u16& value );
	bool ReadByte( u8& value );
	bool ReadBool( bool& value );
	bool ReadFloat( float& value );

	/// Reads a PackedPoint value from a file stream.
	bool ReadPackedPoint( PackedPoint& value );
	bool ReadPackedRect( PackedRect& value );
	bool ReadPoint( Point& value );
	bool ReadRect( Rect& value );
	bool ReadVector2( Vector2& value );
	bool ReadVector3( Vector3& value );
	bool ReadVector4( Vector4& value );
	bool ReadRectf( Rectf& value );
	bool ReadColor( Color& value );
	bool ReadColorf( Colorf& value );

	bool ReadString( String& value );
	bool ReadLine( String& value );

	bool ReadShortArray( s16* ptr, u32 n );
	bool ReadIntArray( int* ptr, u32 n );
	bool ReadFloatArray( float* ptr, u32 n );

	String ReadString();
	String ReadLine();
	String ReadFileID( u32 length );

	Deserializer& operator >>(bool value) { ReadBool(value); return *this; }
	Deserializer& operator >>(s8 value) { ReadChar(value); return *this; }
	Deserializer& operator >>(s16 value) { ReadShort(value); return *this; }
	Deserializer& operator >>(s32 value) { ReadInt(value); return *this; }
	Deserializer& operator >>(u8 value) { ReadByte(value); return *this; }
	Deserializer& operator >>(u16 value) { ReadUShort(value); return *this; }
	Deserializer& operator >>(u32 value) { ReadUInt(value); return *this; }
	Deserializer& operator >>(float value) { ReadFloat(value); return *this; }

	Deserializer& operator >>(Rect& value) { ReadRect(value); return *this; }
	Deserializer& operator >>(Rectf& value) { ReadRectf(value); return *this; }
	Deserializer& operator >>(Point& value) { ReadPoint(value); return *this; }
	Deserializer& operator >>(PackedPoint& value) { ReadPackedPoint(value); return *this; }
	Deserializer& operator >>(PackedRect& value) { ReadPackedRect(value); return *this; }
	Deserializer& operator >>(Vector2& value) { ReadVector2(value); return *this; }
	Deserializer& operator >>(Vector3& value) { ReadVector3(value); return *this; }
	Deserializer& operator >>(Vector4& value) { ReadVector4(value); return *this; }
	Deserializer& operator >>(Color& value) { ReadColor(value); return *this; }
	Deserializer& operator >>(Colorf& value) { ReadColorf(value); return *this; }

	template <u32 N>
	Deserializer& operator >>(StaticString<N>& value)
	{
		u32 size;
		ReadUInt(size);
		Read(value.Data(), size > N : N : size);
		value.SetSize(size);

		return *this;
	}

	Deserializer& operator >>(String& value) { ReadString(value); return *this; }

};





CE_NAMESPACE_END

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


class CE_API Deserializer
{
public:
	virtual ~Deserializer() {}
	
	virtual u32 Read( void* dest, u32 size ) = 0;
	virtual u32 Seek( u32 position ) = 0;
	virtual bool IsEof() const = 0;
	virtual u32 Position() const = 0;

	//Unsafe overloads, for convenience.
	int ReadInt();
	s16 ReadShort();
	char ReadChar();
	u32 ReadUInt();
	u16 ReadUShort();
	u8 ReadByte();
	bool ReadBool();
	float ReadFloat();

	bool ReadInt( int& value );
	bool ReadShort( s16& value );
	bool ReadChar( char& value );
	bool ReadUInt( u32& value );
	bool ReadUShort( u16& value );
	bool ReadByte( u8& value );
	bool ReadBool( bool& value );
	bool ReadFloat( float& value );

	bool ReadPoint( Point& value );
	bool ReadRect( Rect& value );
	bool ReadVector2( Vector2& value );
	bool ReadVector3( Vector3& value );
	bool ReadVector4( Vector4& value );
	bool ReadRectf( Rectf& value );
	bool ReadColor( Color& value );
	bool ReadColorf( Colorf& value );
	bool ReadMatrix( Matrix& value );

	bool ReadString( String& value );
	bool ReadLine( String& value );

	bool ReadShortArray( s16* ptr, u32 n );
	bool ReadIntArray( int* ptr, u32 n );
	bool ReadFloatArray( float* ptr, u32 n );

	String ReadString();
	String ReadLine();

};



CE_NAMESPACE_END

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
	
	virtual size_t Read( void* dest, size_t size ) = 0;
	virtual size_t Seek( size_t position ) = 0;
	virtual bool IsEof() const = 0;
	virtual size_t Position() const = 0;

	//Unsafe overloads, for convenience.
	int ReadInt();
	short ReadShort();
	char ReadByte();
	unsigned int ReadUInt();
	unsigned short ReadUShort();
	unsigned char ReadUByte();
	bool ReadBool();
	float ReadFloat();

	bool ReadInt( int& value );
	bool ReadShort( short& value );
	bool ReadByte( char& value );
	bool ReadUInt( unsigned int& value );
	bool ReadUShort( unsigned short& value );
	bool ReadUByte( unsigned char& value );
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

	bool ReadString( fc::string& value );
	bool ReadLine( fc::string& value );

	bool ReadShortArray( short* ptr, size_t n );
	bool ReadIntArray( int* ptr, size_t n );
	bool ReadFloatArray( float* ptr, size_t n );

	fc::string ReadString();
	fc::string ReadLine();

	/* //Should probably be formated...
	// operator >> overloads for convenience.
	Deserializer& operator >>( int& value );
	Deserializer& operator >>( short& value );
	Deserializer& operator >>( char& value );
	Deserializer& operator >>( unsigned int& value );
	Deserializer& operator >>( unsigned short& value );
	Deserializer& operator >>( unsigned char& value );
	Deserializer& operator >>( bool& value );
	Deserializer& operator >>( float& value );

	Deserializer& operator >>( Rect& value );
	Deserializer& operator >>( Rectf& value );
	Deserializer& operator >>( Point& value );
	Deserializer& operator >>( Vector2& value );
	Deserializer& operator >>( Vector3& value );
	Deserializer& operator >>( Vector4& value );
	Deserializer& operator >>( Color& value );
	Deserializer& operator >>( Colorf& value );
	Deserializer& operator >>( Matrix& value );

	Deserializer& operator >>( fc::string& value );
	*/
};



CE_NAMESPACE_END

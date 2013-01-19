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

#include "IO/Deserializer.h"
#include "MathTypes.h"

CE_NAMESPACE_BEGIN


int Deserializer::ReadInt()
{
	int ret = 0;
	Read(&ret, sizeof(ret));
	return ret;
}


short Deserializer::ReadShort()
{
	short ret = 0;
	Read(&ret, sizeof(ret));
	return ret;
}


char Deserializer::ReadByte()
{
	signed char ret = 0;
	Read(&ret, sizeof(ret));
	return ret;
}


unsigned int Deserializer::ReadUInt()
{
	unsigned int ret = 0;
	Read(&ret, sizeof(ret));
	return ret;
}


unsigned short Deserializer::ReadUShort()
{
	unsigned short ret = 0;
	Read(&ret, sizeof(ret));
	return ret;
}


unsigned char Deserializer::ReadUByte()
{
	unsigned char ret = 0;
	Read(&ret, sizeof(ret));
	return ret;
}


bool Deserializer::ReadBool()
{
	return (ReadUByte() == 0 ? false : true);
}


float Deserializer::ReadFloat()
{
	float ret = 0.f;
	Read(&ret, sizeof(ret));
	return ret;
}


bool Deserializer::ReadInt( int& value )
{
	return Read(&value, sizeof(value)) == sizeof(value);
}


bool Deserializer::ReadShort( short& value )
{
	return Read(&value, sizeof(value)) == sizeof(value);
}


bool Deserializer::ReadByte( char& value )
{
	return Read(&value, sizeof(value)) == sizeof(value);
}


bool Deserializer::ReadUInt( unsigned int& value )
{
	return Read(&value, sizeof(value)) == sizeof(value);
}


bool Deserializer::ReadUShort( unsigned short& value )
{
	return Read(&value, sizeof(value)) == sizeof(value);
}


bool Deserializer::ReadUByte( unsigned char& value )
{
	return Read(&value, sizeof(value)) == sizeof(value);
}


bool Deserializer::ReadBool( bool& value )
{
	return Read(&value, sizeof(value)) == sizeof(value);
}


bool Deserializer::ReadFloat( float& value )
{
	return Read(&value, sizeof(value)) == sizeof(value);
}


bool Deserializer::ReadPoint( Point& value )
{
	return (ReadInt(value.x) && ReadInt(value.y));
}


bool Deserializer::ReadRect( Rect& value )
{
	return (ReadPoint(value.pos) && ReadPoint(value.size ));
}


bool Deserializer::ReadVector2( Vector2& value )
{
	return (ReadFloat(value.x) && ReadFloat(value.y));
}


bool Deserializer::ReadVector3( Vector3& value )
{
	return (ReadFloat(value.x) && ReadFloat(value.y) && ReadFloat(value.z));
}


bool Deserializer::ReadVector4( Vector4& value )
{
	return (ReadFloat(value.x) && ReadFloat(value.y) && ReadFloat(value.z) && ReadFloat(value.w));
}


bool Deserializer::ReadRectf( Rectf& value )
{
	return (ReadVector2(value.min ) && ReadVector2(value.max));
}


bool Deserializer::ReadColor( Color& value )
{
	return ReadUInt(value.packed_value);
}


bool Deserializer::ReadColorf( Colorf& value )
{
	return (ReadFloat(value.r) && ReadFloat(value.g) && ReadFloat(value.b) && ReadFloat(value.a));
}


bool Deserializer::ReadMatrix( Matrix& value )
{
	return ReadFloatArray(&value[0], 16);
}


bool Deserializer::ReadString( fc::string& value )
{
	size_t size;
	if( !ReadUInt(size) )
		return false;

	value.clear();
	value.reserve(size);

	for( size_t i(0); i < size; ++i )
	{
		char c;
		if(!ReadByte( c))
			return false;

		value += c;
	}

	return true;
}


bool Deserializer::ReadLine( fc::string& value )
{
	value.clear();
	while( !IsEof() )
	{
		char c = ReadByte();
		if( c == 10)
			break;
		if( c == 13)
		{
			if(!IsEof())
			{
				char next = ReadByte();
				if (next != 10)
					Seek(Position() - 1);
			}
			break;
		}

		value += c;
	}

	return !value.empty();
}


bool Deserializer::ReadShortArray( short* ptr, size_t n )
{
	const size_t n_bytes = sizeof(short) * n;
	return Read(ptr, n_bytes) == n_bytes;
}


bool Deserializer::ReadIntArray( int* ptr, size_t n )
{
	const size_t n_bytes = sizeof(int) * n;
	return Read(ptr, n_bytes) == n_bytes;
}


bool Deserializer::ReadFloatArray( float* ptr, size_t n )
{
	const size_t n_bytes = sizeof(float) * n;
	return Read(ptr, n_bytes) == n_bytes;
}


fc::string Deserializer::ReadString()
{
	fc::string ret;
	ReadString(ret);
	return ret;
}


fc::string Deserializer::ReadLine()
{
	fc::string ret;
	ReadLine(ret);
	return ret;
}

/*
// operator >> overloads
Deserializer& Deserializer::operator >>( int& value ) { ReadInt(value); return *this; }
Deserializer& Deserializer::operator >>( short& value ) { ReadShort(value); return *this; }
Deserializer& Deserializer::operator >>( char& value ) { ReadByte(value); return *this; }
Deserializer& Deserializer::operator >>( unsigned int& value ) { ReadUInt(value); return *this; }
Deserializer& Deserializer::operator >>( unsigned short& value ) { ReadUShort(value); return *this; }
Deserializer& Deserializer::operator >>( unsigned char& value ) { ReadUByte(value); return *this; }
Deserializer& Deserializer::operator >>( bool& value ) { ReadBool(value); return *this; }
Deserializer& Deserializer::operator >>( float& value ) { ReadFloat(value); return *this; }

Deserializer& Deserializer::operator >>( Rect& value ) { ReadRect(value); return *this; }
Deserializer& Deserializer::operator >>( Rectf& value ) { ReadRectf(value); return *this; }
Deserializer& Deserializer::operator >>( Point& value ) { ReadPoint(value); return *this; }
Deserializer& Deserializer::operator >>( Vector2& value ) { ReadVector2(value); return *this; }
Deserializer& Deserializer::operator >>( Vector3& value ) { ReadVector3(value); return *this; }
Deserializer& Deserializer::operator >>( Vector4& value ) { ReadVector4(value); return *this; }
Deserializer& Deserializer::operator >>( Color& value ) { ReadColor(value); return *this; }
Deserializer& Deserializer::operator >>( Colorf& value ) { ReadColorf(value); return *this; }
Deserializer& Deserializer::operator >>( Matrix& value ) { ReadMatrix(value); return *this; }

Deserializer& Deserializer::operator >>( fc::string& value ) { ReadString(value); return *this; }
*/


CE_NAMESPACE_END

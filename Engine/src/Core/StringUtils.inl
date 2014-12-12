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

#include <fc/string.h>
#include <fc/string_utils.h>

#include "Core/StringUtils.h"

CE_NAMESPACE_BEGIN


#ifdef _MSC_VER
	#pragma warning ( push )
	#pragma warning ( disable : 4996 )
#endif


bool ToBool( const char* s, bool defaultValue )
{
	if( s )
	{
		u32 length = strlen(s);
		for( u32 i(0); i < length; ++i )
		{
			char c = fc::to_lower(s[i]);
			if( c == 't' || c == '1' )
				return true;

			if( c == 'f' || c == '0' )
				return false;

			else if( c != ' ' && c != '\t' )
				break;
		}
	}

	return defaultValue;
}


u8 ToByte( const char* s, u8 defaultValue )
{
	return (u8)ToInt(s, (char**)0, (int)defaultValue);
}


s16 ToShort( const char* s, s16 defaultValue )
{
	return (s16)ToInt(s, (char**)0, (int)defaultValue);
}


int ToInt( const char* s, int defaultValue )
{
	return ToInt(s, (char**)0, defaultValue);
}


u32 ToUInt( const char* s, u32 defaultValue )
{
	return ToInt(s, (char**)0, defaultValue);
}


float ToFloat( const char* s, float defaultValue )
{
	return ToFloat(s, (char**)0, defaultValue);
}


int ToInt( const char* source, char** dest, int defaultValue )
{
	if( !source )
		return defaultValue;

	// bypass leading whitespace
	while( *source == ' ' || *source == '\t' || *source == ',' )
		++source;

	return fc::to_int(source, dest, defaultValue);
}


float ToFloat( const char* source, char** dest, float defaultValue )
{
	if( !source )
		return defaultValue;

	// bypass leading whitespace
	while( *source == ' ' || *source == '\t' || *source == ',' )
		++source;

	return fc::to_float(source, dest, defaultValue);
}


Color ToColor( const char* s, const Color& defaultValue )
{
	Color c = defaultValue;
	if( s )
	{
		char* ptr = (char*)s;
		c.r = (u8)ToInt(ptr, &ptr, (int)defaultValue.r);
		c.g = (u8)ToInt(ptr, &ptr, (int)defaultValue.g);
		c.b = (u8)ToInt(ptr, &ptr, (int)defaultValue.b);
		c.a = (u8)ToInt(ptr, &ptr, (int)defaultValue.a);
	}

	return c;
}


Colorf ToColorf( const char* s, const Colorf& defaultValue )
{
	Colorf c = defaultValue;
	if( s )
	{
		char* ptr = (char*)s;
		c.r = ToFloat(ptr, &ptr, defaultValue.r);
		c.g = ToFloat(ptr, &ptr, defaultValue.g);
		c.b = ToFloat(ptr, &ptr, defaultValue.b);
		c.a = ToFloat(ptr, &ptr, defaultValue.a);
	}

	return c;
}


Point ToPoint( const char* s, const Point& defaultValue )
{
	Point p = defaultValue;
	if( s )
	{
		char* ptr = (char*)s;
		p.x = ToInt(ptr, &ptr, defaultValue.x);
		p.y = ToInt(ptr, &ptr, defaultValue.y);
	}

	return p;
}


Rect ToRect( const char* s, const Rect& defaultValue )
{
	Rect r = defaultValue;
	if( s )
	{
		char* ptr = (char*)s;
		r.pos.x = ToInt(ptr, &ptr, defaultValue.pos.x);
		r.pos.y = ToInt(ptr, &ptr, defaultValue.pos.y);
		r.size.x = ToInt(ptr, &ptr, defaultValue.size.x);
		r.size.y = ToInt(ptr, &ptr, defaultValue.size.y);
	}

	return r;
}


Rectf ToRectf( const char* s, const Rectf& defaultValue )
{
	Rectf r = defaultValue;
	if( s )
	{
		char* ptr = (char*)s;
		r.min.x = ToFloat(ptr, &ptr, defaultValue.min.x);
		r.min.y = ToFloat(ptr, &ptr, defaultValue.min.y);
		r.max.x = ToFloat(ptr, &ptr, defaultValue.max.x);
		r.max.y = ToFloat(ptr, &ptr, defaultValue.max.y);
	}

	return r;
}


Vector2 ToVector2( const char* s, const Vector2& defaultValue )
{
	Vector2 v = defaultValue;
	if( s )
	{
		char* ptr = (char*)s;
		v.x = ToFloat(ptr, &ptr, defaultValue.x);
		v.y = ToFloat(ptr, &ptr, defaultValue.y);
	}

	return v;
}


Vector3 ToVector3( const char* s, const Vector3& defaultValue )
{
	Vector3 v = defaultValue;
	if( s )
	{
		char* ptr = (char*)s;
		v.x = ToFloat(ptr, &ptr, defaultValue.x);
		v.y = ToFloat(ptr, &ptr, defaultValue.y);
		v.z = ToFloat(ptr, &ptr, defaultValue.z);
	}

	return v;
}


Vector4 ToVector4( const char* s, const Vector4& defaultValue )
{
	Vector4 v = defaultValue;
	if( s )
	{
		char* ptr = (char*)s;
		v.x = ToFloat(ptr, &ptr, defaultValue.x);
		v.y = ToFloat(ptr, &ptr, defaultValue.y);
		v.z = ToFloat(ptr, &ptr, defaultValue.z);
		v.w = ToFloat(ptr, &ptr, defaultValue.w);
	}

	return v;
}


Quaternion ToQuaternion( const char* s, const Quaternion& defaultValue )
{
	Quaternion q = defaultValue;
	if( s )
	{
		char* ptr = (char*)s;
		q.x = ToFloat(ptr, &ptr, defaultValue.x);
		q.y = ToFloat(ptr, &ptr, defaultValue.y);
		q.z = ToFloat(ptr, &ptr, defaultValue.z);
		q.w = ToFloat(ptr, &ptr, defaultValue.w);
	}

	return q;
}


Matrix ToMatrix( const char* s, const Matrix& defaultValue )
{
	Matrix m = defaultValue;
	if( s )
	{
		char* ptr = (char*)s;
		for( int i(0); i < 16; ++i )
			m[i] = ToFloat(ptr, &ptr, defaultValue[i]);
	}

	return m;
}



String ToString( bool value )
{
	return fc::to_string<bool>(value);
}


String ToString( char value )
{
	return fc::to_string<char>(value);
}


String ToString( s16 value )
{
	return fc::to_string<s16>(value);
}


String ToString( int value )
{
	return fc::to_string<int>(value);
}


String ToString( u32 value )
{
	return fc::to_string<u32>(value);
}


String ToString( float value )
{
	return fc::to_string<float>(value);
}


String ToString( const Point& value )
{
	char buf[32];
	sprintf(buf, "%i %i", value.x, value.y);
	return String(buf);
}


String ToString( const Rect& value )
{
	char buf[64];
	sprintf(buf, "%i %i %i %i", value.pos.x, value.pos.y, value.size.x, value.size.y);
	return String(buf);
}


String ToString( const Rectf& value )
{
	char buf[64];
	sprintf(buf, "%f %f %f %f", value.min.x, value.min.y, value.max.x, value.max.y);
	return String(buf);
}


String ToString( const Color& value )
{
	char buf[32];
	int c[4] = { value.r, value.g, value.b, value.a };
	sprintf(buf, "%i %i %i %i", c[0], c[1], c[2], c[3]);
	return String(buf);
}


String ToString( const Colorf& value )
{
	char buf[64];
	sprintf(buf, "%f %f %f %f", value.r, value.g, value.b, value.a);
	return String(buf);
}


String ToString( const Vector2& value )
{
	char buf[32];
	sprintf(buf, "%f %f", value.x, value.y);
	return String(buf);
}


String ToString( const Vector3& value )
{
	char buf[64];
	sprintf(buf, "%f %f %f", value.x, value.y, value.z);
	return String(buf);
}


String ToString( const Vector4& value )
{
	char buf[64];
	sprintf(buf, "%f %f %f %f", value.x, value.y, value.z, value.w);
	return String(buf);
}


String ToString( const Quaternion& value )
{
	char buf[64];
	sprintf(buf, "%f %f %f %f", value.x, value.y, value.z, value.w);
	return String(buf);
}


String ToString( const Matrix& value )
{
	String ret;
	char buf[256];
	for( int i(0); i < 16; ++i )
	{
		sprintf(buf, "%f ", value[i]);
		ret += buf;
	}

	return ret;
}


String GetNativePath( const String& path )
{
#ifdef _WIN32
	String ret(path);
	for( String::iterator it = ret.begin(); it != ret.end(); ++it )
		if(*it == '/')
			*it = '\\';
	return ret;
#else
    return path;
#endif
}



#ifdef _MSC_VER
	#pragma warning ( pop )
#endif


CE_NAMESPACE_END


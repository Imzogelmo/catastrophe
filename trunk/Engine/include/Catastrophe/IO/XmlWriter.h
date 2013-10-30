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

#include "XmlElement.h"
#include "XmlDocument.h"

CE_NAMESPACE_BEGIN


class CE_API XmlWriter
{
public:
	XmlWriter();
	XmlWriter( const fc::string& filename );
	virtual ~XmlWriter();

	virtual bool IsOpen() const { return ( m_document != 0 ); }
	virtual bool Open( const fc::string& filename );
	virtual bool Close();

	virtual bool BeginNode( const char* name );
	virtual bool EndNode( const char* name = "" );

	virtual bool WriteBool( const char* name, bool value );
	virtual bool WriteByte( const char* name, byte value );
	virtual bool WriteShort( const char* name, short value );
	virtual bool WriteUShort( const char* name, ushort value );
	virtual bool WriteInt( const char* name, int value );
	virtual bool WriteUInt( const char* name, size_t value );
	virtual bool WriteFloat( const char* name, float value );
	virtual bool WriteString( const char* name, const fc::string& value );
	virtual bool WriteRect( const char* name, const Rect& value );
	virtual bool WriteRectf( const char* name, const Rectf& value );
	virtual bool WritePoint( const char* name, const Point& value );
	virtual bool WriteVector2( const char* name, const Vector2& value );
	virtual bool WriteVector3( const char* name, const Vector3& value );
	virtual bool WriteVector4( const char* name, const Vector4& value );
	virtual bool WriteColor( const char* name, const Color& value );
	virtual bool WriteColorf( const char* name, const Colorf& value );

	virtual bool WriteBoolElement( const char* name, bool value );
	virtual bool WriteByteElement( const char* name, byte value );
	virtual bool WriteShortElement( const char* name, short value );
	virtual bool WriteUShortElement( const char* name, ushort value );
	virtual bool WriteIntElement( const char* name, int value );
	virtual bool WriteUIntElement( const char* name, size_t value );
	virtual bool WriteFloatElement( const char* name, float value );
	virtual bool WriteStringElement( const char* name, const fc::string& value );
	virtual bool WriteRectElement( const char* name, const Rect& value );
	virtual bool WriteRectfElement( const char* name, const Rectf& value );
	virtual bool WritePointElement( const char* name, const Point& value );
	virtual bool WriteVector2Element( const char* name, const Vector2& value );
	virtual bool WriteVector3Element( const char* name, const Vector3& value );
	virtual bool WriteVector4Element( const char* name, const Vector4& value );
	virtual bool WriteColorElement( const char* name, const Color& value );
	virtual bool WriteColorfElement( const char* name, const Colorf& value );

	virtual bool WriteBoolArray( const char* name, const bool* ptr, size_t n );
	virtual bool WriteByteArray( const char* name, const byte* ptr, size_t n );
	virtual bool WriteShortArray( const char* name, const short* ptr, size_t n );
	virtual bool WriteIntArray( const char* name, const int* ptr, size_t n );
	virtual bool WriteFloatArray( const char* name, const float* ptr, size_t n );

	virtual bool WriteBoolArrayElement( const char* name, const bool* ptr, size_t n );
	virtual bool WriteByteArrayElement( const char* name, const byte* ptr, size_t n );
	virtual bool WriteShortArrayElement( const char* name, const short* ptr, size_t n );
	virtual bool WriteIntArrayElement( const char* name, const int* ptr, size_t n );
	virtual bool WriteFloatArrayElement( const char* name, const float* ptr, size_t n );

private:
	fc::string		m_filename;
	XmlDocument		m_document;
	XmlElement		m_element;
};


CE_NAMESPACE_END

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

#include "AttributeWriter.h"
#include "XmlElement.h"
#include "XmlDocument.h"

CE_NAMESPACE_BEGIN


class CE_API XmlWriter : public AttributeWriter
{
public:
	XmlWriter();
	XmlWriter( const fc::string& filename );
	virtual ~XmlWriter();

	virtual bool IsOpen() const { return ( m_document != 0 ); }
	virtual bool Open( const fc::string& filename );
	virtual bool Close();

	virtual bool CreateRoot( const char* name );
	virtual bool BeginNode( const char* name );
	virtual bool EndNode( const char* name = "" );

	virtual bool SetString( const char* name, const char* value );
	virtual bool SetString( const char* name, const fc::string& value );
	virtual bool SetBool( const char* name, bool value );
	virtual bool SetByte( const char* name, byte value );
	virtual bool SetShort( const char* name, short value );
	virtual bool SetUShort( const char* name, ushort value );
	virtual bool SetInt( const char* name, int value );
	virtual bool SetUInt( const char* name, size_t value );
	virtual bool SetFloat( const char* name, float value );
	virtual bool SetRect( const char* name, const Rect& value );
	virtual bool SetRectf( const char* name, const Rectf& value );
	virtual bool SetPoint( const char* name, const Point& value );
	virtual bool SetVector2( const char* name, const Vector2& value );
	virtual bool SetVector3( const char* name, const Vector3& value );
	virtual bool SetVector4( const char* name, const Vector4& value );
	virtual bool SetColor( const char* name, const Color& value );
	virtual bool SetColorf( const char* name, const Colorf& value );

	virtual bool SetBoolElement( const char* name, bool value );
	virtual bool SetByteElement( const char* name, byte value );
	virtual bool SetShortElement( const char* name, short value );
	virtual bool SetUShortElement( const char* name, ushort value );
	virtual bool SetIntElement( const char* name, int value );
	virtual bool SetUIntElement( const char* name, size_t value );
	virtual bool SetFloatElement( const char* name, float value );
	virtual bool SetStringElement( const char* name, const fc::string& value );
	virtual bool SetRectElement( const char* name, const Rect& value );
	virtual bool SetRectfElement( const char* name, const Rectf& value );
	virtual bool SetPointElement( const char* name, const Point& value );
	virtual bool SetVector2Element( const char* name, const Vector2& value );
	virtual bool SetVector3Element( const char* name, const Vector3& value );
	virtual bool SetVector4Element( const char* name, const Vector4& value );
	virtual bool SetColorElement( const char* name, const Color& value );
	virtual bool SetColorfElement( const char* name, const Colorf& value );

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

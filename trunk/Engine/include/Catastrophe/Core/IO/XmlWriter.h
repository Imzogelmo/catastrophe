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

#include "Catastrophe/Core/IO/AttributeWriter.h"
#include "Catastrophe/Core/IO/XmlElement.h"
#include "Catastrophe/Core/IO/XmlDocument.h"
#include "Catastrophe/Core/Containers/String.h"

CE_NAMESPACE_BEGIN


class CE_API XmlWriter : public AttributeWriter
{
public:
	XmlWriter();
	XmlWriter( const String& filename );
	virtual ~XmlWriter();

	virtual bool IsOpen() const { return ( m_document != 0 ); }
	virtual bool Open( const String& filename );
	virtual bool Close();

	virtual bool CreateRoot( const char* name );
	virtual bool BeginNode( const char* name );
	virtual bool EndNode( const char* name = "" );

	virtual bool SetString( const char* name, const char* value );
	virtual bool SetString( const char* name, const String& value );
	virtual bool SetAttribute( const char* name, bool value );
	virtual bool SetAttribute( const char* name, u8 value );
	virtual bool SetAttribute( const char* name, s16 value );
	virtual bool SetAttribute( const char* name, u16 value );
	virtual bool SetAttribute( const char* name, int value );
	virtual bool SetAttribute( const char* name, u32 value );
	virtual bool SetAttribute( const char* name, float value );
	virtual bool SetAttribute( const char* name, const Rect& value );
	virtual bool SetAttribute( const char* name, const Rectf& value );
	virtual bool SetAttribute( const char* name, const Point& value );
	virtual bool SetAttribute( const char* name, const Vector2& value );
	virtual bool SetAttribute( const char* name, const Vector3& value );
	virtual bool SetAttribute( const char* name, const Vector4& value );
	virtual bool SetAttribute( const char* name, const Color& value );
	virtual bool SetAttribute( const char* name, const Colorf& value );

	virtual bool SetBoolElement( const char* name, bool value );
	virtual bool SetByteElement( const char* name, u8 value );
	virtual bool SetShortElement( const char* name, s16 value );
	virtual bool SetUShortElement( const char* name, u16 value );
	virtual bool SetIntElement( const char* name, int value );
	virtual bool SetUIntElement( const char* name, u32 value );
	virtual bool SetFloatElement( const char* name, float value );
	virtual bool SetStringElement( const char* name, const String& value );
	virtual bool SetRectElement( const char* name, const Rect& value );
	virtual bool SetRectfElement( const char* name, const Rectf& value );
	virtual bool SetPointElement( const char* name, const Point& value );
	virtual bool SetVector2Element( const char* name, const Vector2& value );
	virtual bool SetVector3Element( const char* name, const Vector3& value );
	virtual bool SetVector4Element( const char* name, const Vector4& value );
	virtual bool SetColorElement( const char* name, const Color& value );
	virtual bool SetColorfElement( const char* name, const Colorf& value );

	virtual bool WriteBoolArray( const char* name, const bool* ptr, u32 n );
	virtual bool WriteByteArray( const char* name, const u8* ptr, u32 n );
	virtual bool WriteShortArray( const char* name, const s16* ptr, u32 n );
	virtual bool WriteIntArray( const char* name, const int* ptr, u32 n );
	virtual bool WriteFloatArray( const char* name, const float* ptr, u32 n );

	virtual bool WriteBoolArrayElement( const char* name, const bool* ptr, u32 n );
	virtual bool WriteByteArrayElement( const char* name, const u8* ptr, u32 n );
	virtual bool WriteShortArrayElement( const char* name, const s16* ptr, u32 n );
	virtual bool WriteIntArrayElement( const char* name, const int* ptr, u32 n );
	virtual bool WriteFloatArrayElement( const char* name, const float* ptr, u32 n );

private:
	String		m_filename;
	XmlDocument		m_document;
	XmlElement		m_element;
};


CE_NAMESPACE_END

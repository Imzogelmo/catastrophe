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

#include "Catastrophe/Core/IO/AttributeReader.h"
#include "Catastrophe/Core/IO/XmlElement.h"
#include "Catastrophe/Core/IO/XmlDocument.h"
#include "Catastrophe/Core/Containers/String.h"

CE_NAMESPACE_BEGIN


class CE_API XmlReader : public AttributeReader
{
public:
	enum eTokenType
	{
		Boolean,
		Integral,
		Float
	};

	XmlReader();
	XmlReader( const String& filename );
	virtual ~XmlReader();

	XmlElement GetElement() const { return m_element; }
	XmlDocument* GetDocument() { return &m_document; }

	virtual bool Open( const String& filename );
	virtual void Close();
	virtual bool IsOpen() const { return m_document && m_document.GetRoot(); }

	virtual String GetCurrentNodeName() const;
	virtual const char* GetCurrentNodeNameCStr() const;

	virtual bool FirstChild( const char* name = "" );
	virtual bool NextChild( const char* name = "" );
	virtual bool SetToParent();
	virtual bool SetToChild( const char* name );

	virtual bool HasAttribute( const char* name ) const;
	virtual const char* GetString( const char* name, const char* defaultValue = null ) const;
	virtual bool GetString( const char* name, String& value ) const;
	virtual bool GetString( const char* name, StaticString<32>& value ) const;
	virtual bool GetAttribute( const char* name, bool& value ) const;
	virtual bool GetAttribute( const char* name, u8& value ) const;
	virtual bool GetAttribute( const char* name, s16& value ) const;
	virtual bool GetAttribute( const char* name, u16& value ) const;
	virtual bool GetAttribute( const char* name, int& value ) const;
	virtual bool GetAttribute( const char* name, u32& value) const;
	virtual bool GetAttribute( const char* name, float& value ) const;
	virtual bool GetAttribute( const char* name, Rect& value ) const;
	virtual bool GetAttribute( const char* name, Rectf& value ) const;
	virtual bool GetAttribute( const char* name, Point& value ) const;
	virtual bool GetAttribute( const char* name, Vector2& value ) const;
	virtual bool GetAttribute( const char* name, Vector3& value ) const;
	virtual bool GetAttribute( const char* name, Vector4& value ) const;
	virtual bool GetAttribute( const char* name, Color& value ) const;
	virtual bool GetAttribute( const char* name, Colorf& value ) const;

	virtual bool GetStringElement( const char* name, String& value ) const;
	virtual bool GetBoolElement( const char* name, bool& value ) const;
	virtual bool GetByteElement( const char* name, u8& value ) const;
	virtual bool GetShortElement( const char* name, s16& value ) const;
	virtual bool GetIntElement( const char* name, int& value ) const;
	virtual bool GetUIntElement( const char* name, u32& value ) const;
	virtual bool GetFloatElement( const char* name, float& value ) const;
	virtual bool GetRectElement( const char* name, Rect& value ) const;
	virtual bool GetRectfElement( const char* name, Rectf& value ) const;
	virtual bool GetPointElement( const char* name, Point& value ) const;
	virtual bool GetVector2Element( const char* name, Vector2& value ) const;
	virtual bool GetVector3Element( const char* name, Vector3& value ) const;
	virtual bool GetVector4Element( const char* name, Vector4& value ) const;
	virtual bool GetColorElement( const char* name, Color& value ) const;
	virtual bool GetColorfElement( const char* name, Colorf& value ) const;

	virtual bool ReadBoolArray( const char* name, bool* ptr, u32 n ) const;
	virtual bool ReadByteArray( const char* name, u8* ptr, u32 n ) const;
	virtual bool ReadShortArray( const char* name, s16* ptr, u32 n ) const;
	virtual bool ReadIntArray( const char* name, int* ptr, u32 n ) const;
	virtual bool ReadUIntArray( const char* name, u32* ptr, u32 n ) const;
	virtual bool ReadFloatArray( const char* name, float* ptr, u32 n ) const;

	virtual bool ReadBoolArrayElement( const char* name, bool* ptr, u32 n ) const;
	virtual bool ReadByteArrayElement( const char* name, u8* ptr, u32 n ) const;
	virtual bool ReadShortArrayElement( const char* name, s16* ptr, u32 n ) const;
	virtual bool ReadIntArrayElement( const char* name, int* ptr, u32 n ) const;
	virtual bool ReadUIntArrayElement( const char* name, u32* ptr, u32 n ) const;
	virtual bool ReadFloatArrayElement( const char* name, float* ptr, u32 n ) const;

private:
	String			m_filename;
	XmlDocument		m_document;
	XmlElement		m_element;

};



CE_NAMESPACE_END

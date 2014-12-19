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

#include "AttributeReader.h"
#include "XmlElement.h"
#include "XmlDocument.h"

#include <fc/string.h>

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
	virtual const char* GetString( const char* name, const char* defaultValue = 0 ) const;
	virtual String GetString( const char* name, const String& defaultValue ) const;
	virtual bool GetBool( const char* name, bool defaultValue = false ) const;
	virtual u8 GetByte( const char* name, u8 defaultValue = 0 ) const;
	virtual s16 GetShort( const char* name, s16 defaultValue = 0 ) const;
	virtual u16 GetUShort( const char* name, u16 defaultValue = 0 ) const;
	virtual int GetInt( const char* name, int defaultValue = 0 ) const;
	virtual u32 GetUInt( const char* name, u32 defaultValue = 0 ) const;
	virtual float GetFloat( const char* name, float defaultValue = 0.f ) const;
	virtual Rect GetRect( const char* name, const Rect& defaultValue = Rect::Zero ) const;
	virtual Rectf GetRectf( const char* name, const Rectf& defaultValue = Rectf::Zero ) const;
	virtual Point GetPoint( const char* name, const Point& defaultValue = Point::Zero ) const;
	virtual Vector2 GetVector2( const char* name, const Vector2& defaultValue = Vector2::Zero ) const;
	virtual Vector3 GetVector3( const char* name, const Vector3& defaultValue = Vector3::Zero ) const;
	virtual Vector4 GetVector4( const char* name, const Vector4& defaultValue = Vector4::Zero ) const;
	virtual Color GetColor( const char* name, const Color& defaultValue = Color::White() ) const;
	virtual Colorf GetColorf( const char* name, const Colorf& defaultValue = Colorf() ) const;

	virtual String GetStringElement( const char* name, const String& defaultValue = "" ) const;
	virtual bool GetBoolElement( const char* name, bool defaultValue = false ) const;
	virtual u8 GetByteElement( const char* name, u8 defaultValue = 0 ) const;
	virtual s16 GetShortElement( const char* name, s16 defaultValue = 0 ) const;
	virtual int GetIntElement( const char* name, int defaultValue = 0 ) const;
	virtual u32 GetUIntElement( const char* name, u32 defaultValue = 0 ) const;
	virtual float GetFloatElement( const char* name, float defaultValue = 0.f ) const;
	virtual Rect GetRectElement( const char* name, const Rect& defaultValue = Rect::Zero ) const;
	virtual Rectf GetRectfElement( const char* name, const Rectf& defaultValue = Rectf::Zero ) const;
	virtual Point GetPointElement( const char* name, const Point& defaultValue = Point::Zero ) const;
	virtual Vector2 GetVector2Element( const char* name, const Vector2& defaultValue = Vector2::Zero ) const;
	virtual Vector3 GetVector3Element( const char* name, const Vector3& defaultValue = Vector3::Zero ) const;
	virtual Vector4 GetVector4Element( const char* name, const Vector4& defaultValue = Vector4::Zero ) const;
	virtual Color GetColorElement( const char* name, const Color& defaultValue = Color::White() ) const;
	virtual Colorf GetColorfElement( const char* name, const Colorf& defaultValue = Colorf() ) const;

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

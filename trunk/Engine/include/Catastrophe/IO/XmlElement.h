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
#include "../Math/Point.h"
#include "../Math/Rect.h"
#include "../Math/Rectf.h"
#include "../Math/Vector2.h"
#include "../Math/Vector3.h"
#include "../Math/Vector4.h"
#include "../Math/Color.h"
#include "../Math/Colorf.h"

CE_NAMESPACE_BEGIN


class CE_API XmlElement
{
public:
	XmlElement();
	XmlElement( XmlNode_t* element );

	bool BeginNode( const fc::string& name );
	bool BeginNode( const char* name );
	bool EndNode();

	bool SetToParent();
	bool SetToChild( const char* name );

	XmlElement CreateChild( const fc::string& name );
	XmlElement CreateChild( const char* name );
	XmlElement GetParent();

	XmlElement FirstChild( const fc::string& name ) const;
	XmlElement FirstChild( const char* name = "" ) const;
	XmlElement LastChild( const fc::string& name ) const;
	XmlElement LastChild( const char* name = "" ) const;
	XmlElement NextSibling( const fc::string& name ) const;
	XmlElement NextSibling( const char* name = "" ) const;
 
	void RemoveChildren();
	void RemoveChild( XmlElement element );
	void RemoveAttributes();
	void RemoveAttribute( const char* name );

	const char* GetCurrentNodeName() const;
	bool HasAttribute( const char* name ) const;

	bool SetAttribute( const char* name, const char* value );
	bool SetString( const char* name, const fc::string& value );
	bool SetBool( const char* name, bool value );
	bool SetByte( const char* name, byte value );
	bool SetShort( const char* name, short value );
	bool SetInt( const char* name, int value );
	bool SetUInt( const char* name, size_t value );
	bool SetFloat( const char* name, float value );
	bool SetRect( const char* name, const Rect& value );
	bool SetRectf( const char* name, const Rectf& value );
	bool SetPoint( const char* name, const Point& value );
	bool SetVector2( const char* name, const Vector2& value );
	bool SetVector3( const char* name, const Vector3& value );
	bool SetVector4( const char* name, const Vector4& value );
	bool SetColor( const char* name, const Color& value );
	bool SetColorf( const char* name, const Colorf& value );

	bool SetTextElement( const char* name, const char* value );
	bool SetBoolElement( const char* name, bool value );
	bool SetByteElement( const char* name, char value );
	bool SetShortElement( const char* name, short value );
	bool SetIntElement( const char* name, int value );
	bool SetUIntElement( const char* name, size_t value );
	bool SetFloatElement( const char* name, float value );
	bool SetRectElement( const char* name, const Rect& value );
	bool SetRectfElement( const char* name, const Rectf& value );
	bool SetPointElement( const char* name, const Point& value );
	bool SetVector2Element( const char* name, const Vector2& value );
	bool SetVector3Element( const char* name, const Vector3& value );
	bool SetVector4Element( const char* name, const Vector4& value );
	bool SetColorElement( const char* name, const Color& value );
	bool SetColorfElement( const char* name, const Colorf& value );

	bool WriteText( const fc::string& text );
	bool WriteText( const char* text );
	bool WriteByteArray( const char* name, const byte* ptr, size_t n );
	bool WriteShortArray( const char* name, const short* ptr, size_t n );
	bool WriteIntArray( const char* name, const int* ptr, size_t n );
	bool WriteFloatArray( const char* name, const float* ptr, size_t n );
	bool WriteArray( const char* name, const void* ptr, size_t strideInBytes, size_t n, bool isIntegral = true );

	bool WriteTextElement( const char* name, const fc::string& text );
	bool WriteTextElement( const char* name, const char* text );
	bool WriteByteArrayElement( const char* name, const byte* ptr, size_t n );
	bool WriteShortArrayElement( const char* name, const short* ptr, size_t n );
	bool WriteIntArrayElement( const char* name, const int* ptr, size_t n );
	bool WriteFloatArrayElement( const char* name, const float* ptr, size_t n );
	bool WriteArrayElement( const char* name, const void* ptr, size_t strideInBytes, size_t n, bool isIntegral = true );


	const char* GetText() const;
	const char* GetAttribute( const char* name ) const;
	bool GetAttribute( const char* name, fc::string& value ) const;
	fc::string GetString( const char* name ) const;
	bool GetBool( const char* name, bool defaultValue = false ) const;
	byte GetByte( const char* name, byte defaultValue = 0 ) const;
	short GetShort( const char* name, short defaultValue = 0 ) const;
	int GetInt( const char* name, int defaultValue = 0 ) const;
	size_t GetUInt( const char* name, size_t defaultValue = 0 ) const;
	float GetFloat( const char* name, float defaultValue = 0.f ) const;
	Rect GetRect( const char* name, const Rect& defaultValue = Rect::Zero ) const;
	Rectf GetRectf( const char* name, const Rectf& defaultValue = Rectf::Zero ) const;
	Point GetPoint( const char* name, const Point& defaultValue = Point::Zero ) const;
	Vector2 GetVector2( const char* name, const Vector2& defaultValue = Vector2::Zero ) const;
	Vector3 GetVector3( const char* name, const Vector3& defaultValue = Vector3::Zero ) const;
	Vector4 GetVector4( const char* name, const Vector4& defaultValue = Vector4::Zero ) const;
	Color GetColor( const char* name, const Color& defaultValue = Color::White() ) const;
	Colorf GetColorf( const char* name, const Colorf& defaultValue = Colorf() ) const;

	const char* GetTextElement( const char* name ) const;
	bool GetBoolElement( const char* name, bool defaultValue = false ) const;
	byte GetByteElement( const char* name, byte defaultValue = 0 ) const;
	short GetShortElement( const char* name, short defaultValue = 0 ) const;
	int GetIntElement( const char* name, int defaultValue = 0 ) const;
	size_t GetUIntElement( const char* name, size_t defaultValue = 0 ) const;
	float GetFloatElement( const char* name, float defaultValue = 0.f ) const;
	Rect GetRectElement( const char* name, const Rect defaultValue = Rect::Zero ) const;
	Rectf GetRectfElement( const char* name, const Rectf& defaultValue = Rectf::Zero ) const;
	Point GetPointElement( const char* name, const Point& defaultValue = Point::Zero ) const;
	Vector2 GetVector2Element( const char* name, const Vector2& defaultValue = Vector2::Zero ) const;
	Vector3 GetVector3Element( const char* name, const Vector3& defaultValue = Vector3::Zero ) const;
	Vector4 GetVector4Element( const char* name, const Vector4& defaultValue = Vector4::Zero ) const;
	Color GetColorElement( const char* name, const Color& defaultValue = Color::White() ) const;
	Colorf GetColorfElement( const char* name, const Colorf& defaultValue = Colorf() ) const;

	bool ReadByteArray( const char* name, ubyte* ptr, size_t n ) const;
	bool ReadShortArray( const char* name, short* ptr, size_t n ) const;
	bool ReadIntArray( const char* name, int* ptr, size_t n ) const;
	bool ReadFloatArray( const char* name, float* ptr, size_t n ) const;
	bool ReadArray( const char* name, void* ptr, size_t strideInBytes, size_t n, bool isIntegral ) const;

	bool ReadByteArrayElement( const char* name, ubyte* ptr, size_t n ) const;
	bool ReadShortArrayElement( const char* name, short* ptr, size_t n ) const;
	bool ReadIntArrayElement( const char* name, int* ptr, size_t n ) const;
	bool ReadFloatArrayElement( const char* name, float* ptr, size_t n ) const;
	bool ReadArrayElement( const char* name, void* ptr, size_t strideInBytes, size_t n, bool isIntegral ) const;

	static void PrintArray( const void* ptr, fc::string& str, size_t strideInBytes, size_t n, bool isIntegral );
	static bool ParseArray( void* ptr, const fc::string& str, size_t strideInBytes, size_t n, bool isIntegral );

	// operator overloads
	operator bool () const { return m_element != 0; }

protected:
	XmlNode_t*	m_element;

};



CE_NAMESPACE_END

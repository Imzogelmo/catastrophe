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

#include "Catastrophe/Core/Common.h"
#include "Catastrophe/Core/Math/Point.h"
#include "Catastrophe/Core/Math/Rect.h"
#include "Catastrophe/Core/Math/Rectf.h"
#include "Catastrophe/Core/Math/Vector2.h"
#include "Catastrophe/Core/Math/Vector3.h"
#include "Catastrophe/Core/Math/Vector4.h"
#include "Catastrophe/Core/Math/Color.h"
#include "Catastrophe/Core/Math/Colorf.h"
#include "Catastrophe/Core/Containers/String.h"


// rapidxml forward declared types
namespace rapidxml
{
	template <class Ch> class xml_document;
	template <class Ch> class xml_node;
}

typedef rapidxml::xml_document<char> XmlDocument_t;
typedef rapidxml::xml_node<char> XmlNode_t;


CE_NAMESPACE_BEGIN


class CE_API XmlElement
{
public:
	XmlElement();
	XmlElement( XmlNode_t* element );

	bool BeginNode( const String& name );
	bool BeginNode( const char* name );
	bool EndNode();

	bool SetToParent();
	bool SetToChild( const char* name );

	XmlElement CreateChild( const String& name );
	XmlElement CreateChild( const char* name );
	XmlElement GetParent();

	XmlElement FirstChild( const String& name ) const;
	XmlElement FirstChild( const char* name = "" ) const;
	XmlElement LastChild( const String& name ) const;
	XmlElement LastChild( const char* name = "" ) const;
	XmlElement NextSibling( const String& name ) const;
	XmlElement NextSibling( const char* name = "" ) const;
 
	void RemoveChildren();
	void RemoveChild( XmlElement element );
	void RemoveAttributes();
	void RemoveAttribute( const char* name );

	String GetCurrentNodeName() const;
	const char* GetCurrentNodeNameCStr() const;

	bool HasAttribute( const char* name ) const;
	bool SetAttribute( const char* name, const char* value );
	bool SetAttribute( const char* name, const String& value );
	bool SetAttribute( const char* name, bool value );
	bool SetAttribute( const char* name, u8 value );
	bool SetAttribute( const char* name, s16 value );
	bool SetAttribute( const char* name, int value );
	bool SetAttribute( const char* name, u32 value );
	bool SetAttribute( const char* name, float value );
	bool SetAttribute( const char* name, const Rect& value );
	bool SetAttribute( const char* name, const Rectf& value );
	bool SetAttribute( const char* name, const Point& value );
	bool SetAttribute( const char* name, const Vector2& value );
	bool SetAttribute( const char* name, const Vector3& value );
	bool SetAttribute( const char* name, const Vector4& value );
	bool SetAttribute( const char* name, const Color& value );
	bool SetAttribute( const char* name, const Colorf& value );


	bool SetTextElement( const char* name, const char* value );
	bool SetBoolElement( const char* name, bool value );
	bool SetByteElement( const char* name, char value );
	bool SetShortElement( const char* name, s16 value );
	bool SetIntElement( const char* name, int value );
	bool SetUIntElement( const char* name, u32 value );
	bool SetFloatElement( const char* name, float value );
	bool SetRectElement( const char* name, const Rect& value );
	bool SetRectfElement( const char* name, const Rectf& value );
	bool SetPointElement( const char* name, const Point& value );
	bool SetVector2Element( const char* name, const Vector2& value );
	bool SetVector3Element( const char* name, const Vector3& value );
	bool SetVector4Element( const char* name, const Vector4& value );
	bool SetColorElement( const char* name, const Color& value );
	bool SetColorfElement( const char* name, const Colorf& value );

	bool WriteText( const String& text );
	bool WriteText( const char* text );
	bool WriteByteArray( const char* name, const u8* ptr, u32 n );
	bool WriteShortArray( const char* name, const s16* ptr, u32 n );
	bool WriteIntArray( const char* name, const int* ptr, u32 n );
	bool WriteFloatArray( const char* name, const float* ptr, u32 n );
	bool WriteArray( const char* name, const void* ptr, u32 strideInBytes, u32 n, bool isIntegral = true );

	bool WriteTextElement( const char* name, const String& text );
	bool WriteTextElement( const char* name, const char* text );
	bool WriteByteArrayElement( const char* name, const u8* ptr, u32 n );
	bool WriteShortArrayElement( const char* name, const s16* ptr, u32 n );
	bool WriteIntArrayElement( const char* name, const int* ptr, u32 n );
	bool WriteFloatArrayElement( const char* name, const float* ptr, u32 n );
	bool WriteArrayElement( const char* name, const void* ptr, u32 strideInBytes, u32 n, bool isIntegral = true );


	const char* GetText() const;
	const char* GetAttribute( const char* name ) const;
	bool GetAttribute( const char* name, String& value ) const;
	const char* GetString( const char* name, const char* defaultValue = 0 ) const;
	bool GetAttribute( const char* name, bool& value ) const;
	bool GetAttribute( const char* name, u8& value ) const;
	bool GetAttribute( const char* name, s16& value ) const;
	bool GetAttribute( const char* name, u16& value ) const;
	bool GetAttribute( const char* name, int& value ) const;
	bool GetAttribute( const char* name, u32& value ) const;
	bool GetAttribute( const char* name, float& value ) const;
	bool GetAttribute( const char* name, Rect& value ) const;
	bool GetAttribute( const char* name, Rectf& value ) const;
	bool GetAttribute( const char* name, Point& value ) const;
	bool GetAttribute( const char* name, Vector2& value ) const;
	bool GetAttribute( const char* name, Vector3& value ) const;
	bool GetAttribute( const char* name, Vector4& value ) const;
	bool GetAttribute( const char* name, Color& value ) const;
	bool GetAttribute( const char* name, Colorf& value ) const;

	const char* GetTextElement( const char* name ) const;
	bool GetBoolElement( const char* name, bool& value ) const;
	bool GetByteElement( const char* name, u8& value ) const;
	bool GetShortElement( const char* name, s16& value ) const;
	bool GetIntElement( const char* name, int& value ) const;
	bool GetUIntElement( const char* name, u32& value ) const;
	bool GetFloatElement( const char* name, float& value ) const;
	bool GetRectElement( const char* name, Rect& value ) const;
	bool GetRectfElement( const char* name, Rectf& value ) const;
	bool GetPointElement( const char* name, Point& value ) const;
	bool GetVector2Element( const char* name, Vector2& value ) const;
	bool GetVector3Element( const char* name, Vector3& value ) const;
	bool GetVector4Element( const char* name, Vector4& value ) const;
	bool GetColorElement( const char* name, Color& value ) const;
	bool GetColorfElement( const char* name, Colorf& value ) const;

	bool ReadByteArray( const char* name, u8* ptr, u32 n ) const;
	bool ReadShortArray( const char* name, s16* ptr, u32 n ) const;
	bool ReadIntArray( const char* name, int* ptr, u32 n ) const;
	bool ReadFloatArray( const char* name, float* ptr, u32 n ) const;
	bool ReadArray( const char* name, void* ptr, u32 strideInBytes, u32 n, bool isIntegral ) const;

	bool ReadByteArrayElement( const char* name, u8* ptr, u32 n ) const;
	bool ReadShortArrayElement( const char* name, s16* ptr, u32 n ) const;
	bool ReadIntArrayElement( const char* name, int* ptr, u32 n ) const;
	bool ReadFloatArrayElement( const char* name, float* ptr, u32 n ) const;
	bool ReadArrayElement( const char* name, void* ptr, u32 strideInBytes, u32 n, bool isIntegral ) const;

	static void PrintArray( const void* ptr, String& str, u32 strideInBytes, u32 n, bool isIntegral );
	static bool ParseArray( void* ptr, const String& str, u32 strideInBytes, u32 n, bool isIntegral );

	// operator overloads
	operator bool () const { return m_element != 0; }

protected:
	XmlNode_t*	m_element;

};



CE_NAMESPACE_END

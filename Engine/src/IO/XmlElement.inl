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

#include <fc/tokenizer.h>
#include "xml/rapidxml.h"

#include "Common.h"
#include "IO/XmlElement.h"
#include "Core/StringUtils.h"


#ifdef _MSC_VER
	#pragma warning ( push )
	#pragma warning ( disable : 4996 )
#endif

CE_NAMESPACE_BEGIN


XmlElement::XmlElement() :
	m_element(0)
{
}


XmlElement::XmlElement( XmlNode_t* element ) :
	m_element(element)
{
}


bool XmlElement::BeginNode( const String& name )
{
	return BeginNode(name.c_str());
}


bool XmlElement::BeginNode( const char* name )
{
	XmlElement element = CreateChild(name);
	if( element )
		*this = element;

	return *this;
}


bool XmlElement::EndNode()
{
	return SetToParent();
}


bool XmlElement::SetToParent()
{
	CE_ASSERT(m_element);

	XmlNode_t* parent = m_element->parent();
	if( parent )
		m_element = parent;

	return parent != 0;
}


bool XmlElement::SetToChild( const char* name )
{
	CE_ASSERT(m_element);
	XmlElement element = FirstChild(name);
	if( element )
		*this = element;

	return element;
}


XmlElement XmlElement::CreateChild( const String& name )
{
	return CreateChild(name.c_str());
}


XmlElement XmlElement::CreateChild( const char* name )
{
	CE_ASSERT(m_element);

	XmlNode_t* node = 0;
	if( m_element )
	{
		XmlDocument_t* document = m_element->document();
		if( document )
		{
			char* nodeName = document->allocate_string(name);
			node = document->allocate_node(rapidxml::node_element, nodeName);
			m_element->append_node(node);
		}
	}

	return XmlElement(node);
}


XmlElement XmlElement::GetParent()
{
	CE_ASSERT(m_element);

	XmlNode_t* parent = 0;
	if( m_element )
		parent = m_element->parent();

	return XmlElement(parent);
}


XmlElement XmlElement::FirstChild( const String& name ) const
{
	return FirstChild(name.c_str());
}


XmlElement XmlElement::FirstChild( const char* name ) const
{
	CE_ASSERT(m_element);

	XmlNode_t* child = 0;
	if( m_element )
		child = m_element->first_node(name);

	return XmlElement(child);
}


XmlElement XmlElement::LastChild( const String& name ) const
{
	return LastChild(name.c_str());
}


XmlElement XmlElement::LastChild( const char* name ) const
{
	CE_ASSERT(m_element);

	XmlNode_t* child = 0;
	if( m_element )
		child = m_element->last_node(name);

	return XmlElement(child);
}


XmlElement XmlElement::NextSibling( const String& name ) const
{
	return NextSibling(name.c_str());
}


XmlElement XmlElement::NextSibling( const char* name ) const
{
	CE_ASSERT(m_element);

	XmlNode_t* sibling = 0;
	if( m_element )
		sibling = m_element->next_sibling(name);

	return XmlElement(sibling);
}


void XmlElement::RemoveChildren()
{
	CE_ASSERT(m_element);
	if( m_element )
		m_element->remove_all_nodes();
}


void XmlElement::RemoveChild( XmlElement element )
{
	CE_ASSERT(m_element);
	if( m_element )
		m_element->remove_node(element.m_element);
}


void XmlElement::RemoveAttributes()
{
	CE_ASSERT(m_element);
	if( m_element )
		m_element->remove_all_attributes();
}


void XmlElement::RemoveAttribute( const char* name )
{
	CE_ASSERT(m_element);
	if( m_element )
	{
		rapidxml::xml_attribute<>* attribute = m_element->first_attribute(name);
		m_element->remove_attribute(attribute);
	}
}


String XmlElement::GetCurrentNodeName() const
{
	return m_element ? m_element->name() : "";
}


const char* XmlElement::GetCurrentNodeNameCStr() const
{
	return m_element ? m_element->name() : 0;
}


bool XmlElement::HasAttribute( const char* name ) const
{
	CE_ASSERT(m_element);
	if( !m_element )
		return false;

	rapidxml::xml_attribute<>* attribute = m_element->first_attribute(name);
	return attribute != 0;
}



// write options

bool XmlElement::SetAttribute( const char* name, const char* value )
{
	CE_ASSERT(m_element);
	if( m_element )
	{
		rapidxml::xml_document<>* document = m_element->document();
		if( document )
		{
			char* attributeName = document->allocate_string(name);
			char* attributeValue = document->allocate_string(value);
			rapidxml::xml_attribute<>* attribute = document->allocate_attribute(attributeName, attributeValue);
			m_element->append_attribute(attribute);

			return true;
		}
	}

	return false;
}


bool XmlElement::SetString( const char* name, const String& value )
{
	return SetAttribute(name, value.c_str());
}


bool XmlElement::SetBool( const char* name, bool value )
{
	return SetAttribute(name, (value ? "true" : "false"));
}


bool XmlElement::SetByte( const char* name, u8 value )
{
	return SetInt(name, (int)value);
}


bool XmlElement::SetShort( const char* name, s16 value )
{
	return SetInt(name, (int)value);
}


bool XmlElement::SetInt( const char* name, int value )
{
	return SetAttribute(name, fc::to_string(value).c_str());
}


bool XmlElement::SetUInt( const char* name, u32 value )
{
	return SetAttribute(name, fc::to_string(value).c_str());
}


bool XmlElement::SetFloat( const char* name, float value )
{
	return SetAttribute(name, fc::to_string(value).c_str());
}


bool XmlElement::SetRect( const char* name, const Rect& value )
{
	return SetAttribute(name, ToString(value).c_str());
}


bool XmlElement::SetRectf( const char* name, const Rectf& value )
{
	return SetAttribute(name, ToString(value).c_str());
}


bool XmlElement::SetPoint( const char* name, const Point& value )
{
	return SetAttribute(name, ToString(value).c_str());
}


bool XmlElement::SetVector2( const char* name, const Vector2& value )
{
	return SetAttribute(name, ToString(value).c_str());
}


bool XmlElement::SetVector3( const char* name, const Vector3& value )
{
	return SetAttribute(name, ToString(value).c_str());
}


bool XmlElement::SetVector4( const char* name, const Vector4& value )
{
	return SetAttribute(name, ToString(value).c_str());
}


bool XmlElement::SetColor( const char* name, const Color& value )
{
	return SetAttribute(name, ToString(value).c_str());
}


bool XmlElement::SetColorf( const char* name, const Colorf& value )
{
	return SetAttribute(name, ToString(value).c_str());
}


bool XmlElement::SetTextElement( const char* name, const char* value )
{
	return CreateChild(name).WriteText(value);
}


bool XmlElement::SetBoolElement( const char* name, bool value )
{
	return SetTextElement(name, ToString(value).c_str());
}


bool XmlElement::SetByteElement( const char* name, char value )
{
	return SetTextElement(name, ToString(value).c_str());
}


bool XmlElement::SetShortElement( const char* name, s16 value )
{
	return SetTextElement(name, ToString(value).c_str());
}


bool XmlElement::SetIntElement( const char* name, int value )
{
	return SetTextElement(name, ToString(value).c_str());
}


bool XmlElement::SetUIntElement( const char* name, u32 value )
{
	return SetTextElement(name, ToString(value).c_str());
}


bool XmlElement::SetFloatElement( const char* name, float value )
{
	return SetTextElement(name, ToString(value).c_str());
}


bool XmlElement::SetRectElement( const char* name, const Rect& value )
{
	return SetTextElement(name, ToString(value).c_str());
}


bool XmlElement::SetRectfElement( const char* name, const Rectf& value )
{
	return SetTextElement(name, ToString(value).c_str());
}


bool XmlElement::SetPointElement( const char* name, const Point& value )
{
	return SetTextElement(name, ToString(value).c_str());
}


bool XmlElement::SetVector2Element( const char* name, const Vector2& value )
{
	return SetTextElement(name, ToString(value).c_str());
}


bool XmlElement::SetVector3Element( const char* name, const Vector3& value )
{
	return SetTextElement(name, ToString(value).c_str());
}


bool XmlElement::SetVector4Element( const char* name, const Vector4& value )
{
	return SetTextElement(name, ToString(value).c_str());
}


bool XmlElement::SetColorElement( const char* name, const Color& value )
{
	return SetTextElement(name, ToString(value).c_str());
}


bool XmlElement::SetColorfElement( const char* name, const Colorf& value )
{
	return SetTextElement(name, ToString(value).c_str());
}


bool XmlElement::WriteText( const String& s )
{
	return WriteText(s.c_str());
}


bool XmlElement::WriteText( const char* s )
{
	CE_ASSERT(m_element);
	if( m_element )
	{
		XmlDocument_t* document = m_element->document();
		if( document )
		{
			char* value = document->allocate_string(s);
			m_element->value(value);

			return true;
		}
	}

	return false;
}


bool XmlElement::WriteByteArray( const char* name, const u8* ptr, u32 n )
{
	return WriteArray(name, ptr, sizeof(u8), n, true);
}


bool XmlElement::WriteShortArray( const char* name, const s16* ptr, u32 n )
{
	return WriteArray(name, ptr, sizeof(s16), n, true);
}


bool XmlElement::WriteIntArray( const char* name, const int* ptr, u32 n )
{
	return WriteArray(name, ptr, sizeof(int), n, true);
}


bool XmlElement::WriteFloatArray( const char* name, const float* ptr, u32 n )
{
	return WriteArray(name, ptr, sizeof(float), n, false);
}


bool XmlElement::WriteArray( const char* name, const void* ptr, u32 strideInBytes, u32 n, bool isIntegral )
{
	String formatedString;
	PrintArray(ptr, formatedString, strideInBytes, n, isIntegral);
	return SetAttribute(name, formatedString.c_str());
}


void XmlElement::PrintArray( const void* ptr, String& str, u32 strideInBytes, u32 n, bool isIntegral )
{
	str.reserve(n * 4); //best guess

	char buf[64];
	for( u32 i(0); i < n; ++i )
	{
		u32 byteOffset = i * strideInBytes;

		if( isIntegral )
		{
			int value = 0;
			if( strideInBytes == sizeof(char) )
				value = *(char*)((char*)ptr + byteOffset);

			else if( strideInBytes == sizeof(s16) )
				value = *(s16*)((char*)ptr + byteOffset);

			else if( strideInBytes == sizeof(int) )
				value = *(int*)((char*)ptr + byteOffset);

			fc::to_string(value, buf);
		}
		else
		{
			float value = *(float*)((char*)ptr + byteOffset);
			fc::to_string(value, buf);
			//sprintf(buf, "%f", value);
		}

		str.append(buf).append(',');
	}

	//remove the trailing ',' character.
	if( !str.empty() && str.back() == ',' )
		str.pop_back();
}


bool XmlElement::WriteTextElement( const char* name, const String& text )
{
	return WriteTextElement(name, text.c_str());
}


bool XmlElement::WriteTextElement( const char* name, const char* text )
{
	return CreateChild(name).WriteText(text);
}


bool XmlElement::WriteByteArrayElement( const char* name, const u8* ptr, u32 n )
{
	return WriteArrayElement(name, ptr, sizeof(u8), n, true);
}


bool XmlElement::WriteShortArrayElement( const char* name, const s16* ptr, u32 n )
{
	return WriteArrayElement(name, ptr, sizeof(s16), n, true);
}


bool XmlElement::WriteIntArrayElement( const char* name, const int* ptr, u32 n )
{
	return WriteArrayElement(name, ptr, sizeof(int), n, true);
}


bool XmlElement::WriteFloatArrayElement( const char* name, const float* ptr, u32 n )
{
	return WriteArrayElement(name, ptr, sizeof(float), n, false);
}


bool XmlElement::WriteArrayElement( const char* name, const void* ptr, u32 strideInBytes, u32 n, bool isIntegral )
{
	String formatedString;
	PrintArray(ptr, formatedString, strideInBytes, n, isIntegral);
	return WriteTextElement(name, formatedString.c_str());
}




// read options

const char* XmlElement::GetText() const
{
	CE_ASSERT(m_element);
	return m_element ? m_element->value() : 0;
}


bool XmlElement::GetAttribute( const char* name, String& value ) const
{
	const char* s = GetAttribute(name);
	if( s )
		value = s;

	return s != 0;
}


const char* XmlElement::GetAttribute( const char* name ) const
{
	CE_ASSERT(m_element);
	if( m_element )
	{
		rapidxml::xml_attribute<>* attribute = m_element->first_attribute(name, 0, false);
		if( attribute )
			return attribute->value();
	}

	return 0;
}


const char* XmlElement::GetString( const char* name, const char* defaultValue ) const
{
	const char* str = GetAttribute(name);
	return str ? str : defaultValue;
}


bool XmlElement::GetBool( const char* name, bool defaultValue ) const
{
	return ToBool(GetAttribute(name), defaultValue);
}


u8 XmlElement::GetByte( const char* name, u8 defaultValue ) const
{
	return (u8)GetInt(name, (int)defaultValue);
}


s16 XmlElement::GetShort( const char* name, s16 defaultValue ) const
{
	return (s16)GetInt(name, (int)defaultValue);
}


u16 XmlElement::GetUShort( const char* name, u16 defaultValue ) const
{
	return (u16)GetInt(name, (int)defaultValue);
}


int XmlElement::GetInt( const char* name, int defaultValue ) const
{
	return ToInt(GetAttribute(name), defaultValue);
}


u32 XmlElement::GetUInt( const char* name, u32 defaultValue ) const
{
	return (u32)GetInt(name, (int)defaultValue);
}


float XmlElement::GetFloat( const char* name, float defaultValue ) const
{
	return ToFloat(GetAttribute(name), defaultValue);
}


Rect XmlElement::GetRect( const char* name, const Rect& defaultValue ) const
{
	return ToRect(GetAttribute(name), defaultValue);
}


Rectf XmlElement::GetRectf( const char* name, const Rectf& defaultValue ) const
{
	return ToRectf(GetAttribute(name), defaultValue);
}


Point XmlElement::GetPoint( const char* name, const Point& defaultValue ) const
{
	return ToPoint(GetAttribute(name), defaultValue);
}


Vector2 XmlElement::GetVector2( const char* name, const Vector2& defaultValue ) const
{
	return ToVector2(GetAttribute(name), defaultValue);
}


Vector3 XmlElement::GetVector3( const char* name, const Vector3& defaultValue ) const
{
	return ToVector3(GetAttribute(name), defaultValue);
}


Vector4 XmlElement::GetVector4( const char* name, const Vector4& defaultValue ) const
{
	return ToVector4(GetAttribute(name), defaultValue);
}


Color XmlElement::GetColor( const char* name, const Color& defaultValue ) const
{
	return ToColor(GetAttribute(name), defaultValue);
}


Colorf XmlElement::GetColorf( const char* name, const Colorf& defaultValue ) const
{
	return ToColorf(GetAttribute(name), defaultValue);
}


const char* XmlElement::GetTextElement( const char* name ) const
{
	return FirstChild(name).GetText();
}


bool XmlElement::GetBoolElement( const char* name, bool defaultValue ) const
{
	const char* s = FirstChild(name).GetText();
	return ToBool(s, defaultValue);
}


u8 XmlElement::GetByteElement( const char* name, u8 defaultValue ) const
{
	const char* s = FirstChild(name).GetText();
	return ToByte(s, defaultValue);
}


s16 XmlElement::GetShortElement( const char* name, s16 defaultValue ) const
{
	const char* s = FirstChild(name).GetText();
	return ToShort(s, defaultValue);
}


int XmlElement::GetIntElement( const char* name, int defaultValue ) const
{
	const char* s = FirstChild(name).GetText();
	return ToInt(s, defaultValue);
}


u32 XmlElement::GetUIntElement( const char* name, u32 defaultValue ) const
{
	const char* s = FirstChild(name).GetText();
	return ToUInt(s, defaultValue);
}


float XmlElement::GetFloatElement( const char* name, float defaultValue ) const
{
	const char* s = FirstChild(name).GetText();
	return ToFloat(s, defaultValue);
}


Rect XmlElement::GetRectElement( const char* name, const Rect defaultValue ) const
{
	const char* s = FirstChild(name).GetText();
	return ToRect(s, defaultValue);
}


Rectf XmlElement::GetRectfElement( const char* name, const Rectf& defaultValue ) const
{
	const char* s = FirstChild(name).GetText();
	return ToRectf(s, defaultValue);
}


Point XmlElement::GetPointElement( const char* name, const Point& defaultValue ) const
{
	const char* s = FirstChild(name).GetText();
	return ToPoint(s, defaultValue);
}


Vector2 XmlElement::GetVector2Element( const char* name, const Vector2& defaultValue ) const
{
	const char* s = FirstChild(name).GetText();
	return ToVector2(s, defaultValue);
}


Vector3 XmlElement::GetVector3Element( const char* name, const Vector3& defaultValue ) const
{
	const char* s = FirstChild(name).GetText();
	return ToVector3(s, defaultValue);
}


Vector4 XmlElement::GetVector4Element( const char* name, const Vector4& defaultValue ) const
{
	const char* s = FirstChild(name).GetText();
	return ToVector4(s, defaultValue);
}


Color XmlElement::GetColorElement( const char* name, const Color& defaultValue ) const
{
	const char* s = FirstChild(name).GetText();
	return ToColor(s, defaultValue);
}


Colorf XmlElement::GetColorfElement( const char* name, const Colorf& defaultValue ) const
{
	const char* s = FirstChild(name).GetText();
	return ToColorf(s, defaultValue);
}


bool XmlElement::ReadByteArray( const char* name, u8* ptr, u32 n ) const
{
	return ReadArray(name, ptr, sizeof(u8), n, true);
}


bool XmlElement::ReadShortArray( const char* name, s16* ptr, u32 n ) const
{
	return ReadArray(name, ptr, sizeof(s16), n, true);
}


bool XmlElement::ReadIntArray( const char* name, int* ptr, u32 n ) const
{
	return ReadArray(name, ptr, sizeof(int), n, true);
}


bool XmlElement::ReadFloatArray( const char* name, float* ptr, u32 n ) const
{
	return ReadArray(name, ptr, sizeof(float), n, false);
}


bool XmlElement::ReadArray( const char* name, void* ptr, u32 strideInBytes, u32 n, bool isIntegral ) const
{
	String str = GetAttribute(name);
	return ParseArray(ptr, str, strideInBytes, n, isIntegral);
}


bool XmlElement::ParseArray( void* ptr, const String& str, u32 strideInBytes, u32 n, bool isIntegral )
{
	if( str.empty() )
		return false;

	u32 index = 0;
	String token;
	String delimiters = ", \n\t()\"";

	for( u32 i(0); i < n; ++i )
	{
		int byteOffset = i * strideInBytes;
		if( fc::tokenizer::get_token(str, delimiters, index, token) )
		{
			if( isIntegral )
			{
				if( strideInBytes == sizeof(char) )
					*((char*)ptr + byteOffset) = (char)token.to_int();

				else if( strideInBytes == sizeof(s16) )
					*((s16*)((char*)ptr + byteOffset)) = (s16)token.to_int();
	
				else if( strideInBytes == sizeof(int) )
					*((int*)((char*)ptr + byteOffset)) = (int)token.to_int();

				else if( strideInBytes == sizeof(s64) )
					*((s64*)((char*)ptr + byteOffset)) = (s64)token.to_int();

				else
				{
					//unsupported type.
					return false;
				}
			}
			else
			{
				if( strideInBytes == sizeof(float) )
					*((float*)((char*)ptr + byteOffset)) = (float)token.to_float();

				else if( strideInBytes == sizeof(double) )
					*((double*)((char*)ptr + byteOffset)) = (double)token.to_float();
			}
		}
		else
		{
			return false;
		}
	}

	return true;
}


bool XmlElement::ReadByteArrayElement( const char* name, u8* ptr, u32 n ) const
{
	return ReadArrayElement(name, ptr, sizeof(u8), n, true);
}


bool XmlElement::ReadShortArrayElement( const char* name, s16* ptr, u32 n ) const
{
	return ReadArrayElement(name, ptr, sizeof(s16), n, true);
}


bool XmlElement::ReadIntArrayElement( const char* name, int* ptr, u32 n ) const
{
	return ReadArrayElement(name, ptr, sizeof(int), n, true);
}


bool XmlElement::ReadFloatArrayElement( const char* name, float* ptr, u32 n ) const
{
	return ReadArrayElement(name, ptr, sizeof(float), n, false);
}


bool XmlElement::ReadArrayElement( const char* name, void* ptr, u32 strideInBytes, u32 n, bool isIntegral ) const
{
	String str = GetTextElement(name);
	return ParseArray(ptr, str, strideInBytes, n, isIntegral);
}




CE_NAMESPACE_END


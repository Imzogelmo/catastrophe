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

#include "xml/rapidxml.h"

#include "Catastrophe/Core/Common.h"
#include "Catastrophe/Core/IO/XmlElement.h"
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
	return BeginNode(name.CString());
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
	CE_ASSERT(m_element != null);

	XmlNode_t* parent = m_element->parent();
	if( parent )
		m_element = parent;

	return parent != null;
}


bool XmlElement::SetToChild( const char* name )
{
	CE_ASSERT(m_element != null);
	XmlElement element = FirstChild(name);
	if( element )
		*this = element;

	return element;
}


XmlElement XmlElement::CreateChild( const String& name )
{
	return CreateChild(name.CString());
}


XmlElement XmlElement::CreateChild( const char* name )
{
	CE_ASSERT(m_element != null);

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
	CE_ASSERT(m_element != null);

	XmlNode_t* parent = 0;
	if( m_element )
		parent = m_element->parent();

	return XmlElement(parent);
}


XmlElement XmlElement::FirstChild( const String& name ) const
{
	return FirstChild(name.CString());
}


XmlElement XmlElement::FirstChild( const char* name ) const
{
	CE_ASSERT(m_element != null);

	XmlNode_t* child = null;
	if( m_element )
		child = m_element->first_node(name);

	return XmlElement(child);
}


XmlElement XmlElement::LastChild( const String& name ) const
{
	return LastChild(name.CString());
}


XmlElement XmlElement::LastChild( const char* name ) const
{
	CE_ASSERT(m_element != null);

	XmlNode_t* child = null;
	if( m_element )
		child = m_element->last_node(name);

	return XmlElement(child);
}


XmlElement XmlElement::NextSibling( const String& name ) const
{
	return NextSibling(name.CString());
}


XmlElement XmlElement::NextSibling( const char* name ) const
{
	CE_ASSERT(m_element != null);

	XmlNode_t* sibling = null;
	if( m_element )
		sibling = m_element->next_sibling(name);

	return XmlElement(sibling);
}


void XmlElement::RemoveChildren()
{
	CE_ASSERT(m_element != null);
	if( m_element )
		m_element->remove_all_nodes();
}


void XmlElement::RemoveChild( XmlElement element )
{
	CE_ASSERT(m_element != null);
	if( m_element )
		m_element->remove_node(element.m_element);
}


void XmlElement::RemoveAttributes()
{
	CE_ASSERT(m_element != null);
	if( m_element )
		m_element->remove_all_attributes();
}


void XmlElement::RemoveAttribute( const char* name )
{
	CE_ASSERT(m_element != null);
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
	return m_element ? m_element->name() : null;
}


bool XmlElement::HasAttribute( const char* name ) const
{
	CE_ASSERT(m_element != null);
	if( !m_element )
		return false;

	rapidxml::xml_attribute<>* attribute = m_element->first_attribute(name);
	return attribute != null;
}



// write options

bool XmlElement::SetAttribute( const char* name, const char* value )
{
	CE_ASSERT(m_element != null);
	if( m_element != null )
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


bool XmlElement::SetAttribute( const char* name, const String& value )
{
	return SetAttribute(name, value.CString());
}


bool XmlElement::SetAttribute( const char* name, bool value )
{
	return SetAttribute(name, (value ? "true" : "false"));
}


bool XmlElement::SetAttribute( const char* name, u8 value )
{
	return SetAttribute(name, (int)value);
}


bool XmlElement::SetAttribute( const char* name, s16 value )
{
	return SetAttribute(name, (int)value);
}


bool XmlElement::SetAttribute( const char* name, int value )
{
	return SetAttribute(name, ToString(value).CString());
}


bool XmlElement::SetAttribute( const char* name, u32 value )
{
	return SetAttribute(name, ToString(value).CString());
}


bool XmlElement::SetAttribute( const char* name, float value )
{
	return SetAttribute(name, ToString(value).CString());
}


bool XmlElement::SetAttribute( const char* name, const Rect& value )
{
	return SetAttribute(name, ToString(value).CString());
}


bool XmlElement::SetAttribute( const char* name, const Rectf& value )
{
	return SetAttribute(name, ToString(value).CString());
}


bool XmlElement::SetAttribute( const char* name, const Point& value )
{
	return SetAttribute(name, ToString(value).CString());
}


bool XmlElement::SetAttribute( const char* name, const PackedPoint& value )
{
	return SetAttribute(name, ToString(value).CString());
}


bool XmlElement::SetAttribute( const char* name, const PackedRect& value )
{
	return SetAttribute(name, ToString(value).CString());
}


bool XmlElement::SetAttribute( const char* name, const Vector2& value )
{
	return SetAttribute(name, ToString(value).CString());
}


bool XmlElement::SetAttribute( const char* name, const Vector3& value )
{
	return SetAttribute(name, ToString(value).CString());
}


bool XmlElement::SetAttribute( const char* name, const Vector4& value )
{
	return SetAttribute(name, ToString(value).CString());
}


bool XmlElement::SetAttribute( const char* name, const Color& value )
{
	return SetAttribute(name, ToString(value).CString());
}


bool XmlElement::SetAttribute( const char* name, const Colorf& value )
{
	return SetAttribute(name, ToString(value).CString());
}


bool XmlElement::SetTextElement( const char* name, const char* value )
{
	return CreateChild(name).WriteText(value);
}


bool XmlElement::SetBoolElement( const char* name, bool value )
{
	return SetTextElement(name, ToString(value).CString());
}


bool XmlElement::SetByteElement( const char* name, char value )
{
	return SetTextElement(name, ToString(value).CString());
}


bool XmlElement::SetShortElement( const char* name, s16 value )
{
	return SetTextElement(name, ToString(value).CString());
}


bool XmlElement::SetIntElement( const char* name, int value )
{
	return SetTextElement(name, ToString(value).CString());
}


bool XmlElement::SetUIntElement( const char* name, u32 value )
{
	return SetTextElement(name, ToString(value).CString());
}


bool XmlElement::SetFloatElement( const char* name, float value )
{
	return SetTextElement(name, ToString(value).CString());
}


bool XmlElement::SetRectElement( const char* name, const Rect& value )
{
	return SetTextElement(name, ToString(value).CString());
}


bool XmlElement::SetRectfElement( const char* name, const Rectf& value )
{
	return SetTextElement(name, ToString(value).CString());
}


bool XmlElement::SetPointElement( const char* name, const Point& value )
{
	return SetTextElement(name, ToString(value).CString());
}


bool XmlElement::SetPackedRectElement( const char* name, const PackedRect& value )
{
	return SetTextElement(name, ToString(value).CString());
}


bool XmlElement::SetPackedPointElement( const char* name, const PackedPoint& value )
{
	return SetTextElement(name, ToString(value).CString());
}


bool XmlElement::SetVector2Element( const char* name, const Vector2& value )
{
	return SetTextElement(name, ToString(value).CString());
}


bool XmlElement::SetVector3Element( const char* name, const Vector3& value )
{
	return SetTextElement(name, ToString(value).CString());
}


bool XmlElement::SetVector4Element( const char* name, const Vector4& value )
{
	return SetTextElement(name, ToString(value).CString());
}


bool XmlElement::SetColorElement( const char* name, const Color& value )
{
	return SetTextElement(name, ToString(value).CString());
}


bool XmlElement::SetColorfElement( const char* name, const Colorf& value )
{
	return SetTextElement(name, ToString(value).CString());
}


bool XmlElement::WriteText( const String& s )
{
	return WriteText(s.CString());
}


bool XmlElement::WriteText( const char* s )
{
	CE_ASSERT(m_element != null);
	if( m_element != null )
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
	return SetAttribute(name, formatedString.CString());
}


void XmlElement::PrintArray( const void* ptr, String& str, u32 strideInBytes, u32 n, bool isIntegral )
{
	str.Reserve(n * 4); //best guess

	char buf[64];
	for( u32 i(0); i < n; ++i )
	{
		u32 tokenLength = 0;
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

			tokenLength = Itoa(value, buf);
		}
		else
		{
			float value = *(float*)((char*)ptr + byteOffset);
			tokenLength = Ftoa(value, buf);
		}

		str.Append(buf, tokenLength).Append(',');
	}

	//remove the trailing ',' character.
	if( !str.Empty() && str.Back() == ',' )
		str.PopBack();
}


bool XmlElement::WriteTextElement( const char* name, const String& text )
{
	return WriteTextElement(name, text.CString());
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
	return WriteTextElement(name, formatedString.CString());
}




// read options

const char* XmlElement::GetText() const
{
	CE_ASSERT(m_element != null);
	return m_element ? m_element->value() : null;
}


bool XmlElement::GetAttribute( const char* name, String& value ) const
{
	const char* s = GetAttribute(name);
	if( s )
		value = s;

	return s != null;
}


const char* XmlElement::GetAttribute( const char* name ) const
{
	CE_ASSERT(m_element != null);
	if( m_element != null )
	{
		rapidxml::xml_attribute<>* attribute = m_element->first_attribute(name, 0, false);
		if( attribute )
			return attribute->value();
	}

	return null;
}


const char* XmlElement::GetString( const char* name, const char* defaultValue ) const
{
	const char* str = GetAttribute(name);
	return str ? str : defaultValue;
}


bool XmlElement::GetAttribute( const char* name, bool& value ) const
{
	const char* attribute = GetAttribute(name);
	if( attribute != null )
		value = ToBool(attribute);

	return (attribute != null);
}


bool XmlElement::GetAttribute( const char* name, u8& value ) const
{
	const char* attribute = GetAttribute(name);
	if( attribute != null )
		value = ToByte(attribute);

	return (attribute != null);
}


bool XmlElement::GetAttribute( const char* name, s16& value ) const
{
	const char* attribute = GetAttribute(name);
	if( attribute != null )
		value = ToShort(attribute);

	return (attribute != null);
}


bool XmlElement::GetAttribute( const char* name, u16& value ) const
{
	return (u16)GetAttribute(name, *(s16*)&value);
}


bool XmlElement::GetAttribute( const char* name, int& value ) const
{
	const char* attribute = GetAttribute(name);
	if( attribute != null )
		value = ToInt(attribute);

	return (attribute != null);
}


bool XmlElement::GetAttribute( const char* name, u32& value ) const
{
	return (u32)GetAttribute(name, *(int*)&value);
}


bool XmlElement::GetAttribute( const char* name, float& value ) const
{
	const char* attribute = GetAttribute(name);
	if( attribute != null )
		value = ToFloat(attribute);

	return (attribute != null);
}


bool XmlElement::GetAttribute( const char* name, Rect& value ) const
{
	const char* attribute = GetAttribute(name);
	if( attribute != null )
		value = ToRectf(attribute);

	return (attribute != null);
}


bool XmlElement::GetAttribute( const char* name, Rectf& value ) const
{
	const char* attribute = GetAttribute(name);
	if( attribute != null )
		value = ToRectf(attribute);

	return (attribute != null);
}


bool XmlElement::GetAttribute( const char* name, Point& value ) const
{
	const char* attribute = GetAttribute(name);
	if( attribute != null )
		value = ToPoint(attribute);

	return (attribute != null);
}


bool XmlElement::GetAttribute( const char* name, PackedPoint& value ) const
{
	const char* attribute = GetAttribute(name);
	if( attribute != null )
		value = ToPackedPoint(attribute);

	return (attribute != null);
}


bool XmlElement::GetAttribute( const char* name, PackedRect& value ) const
{
	const char* attribute = GetAttribute(name);
	if( attribute != null )
		value = ToPackedRect(attribute);

	return (attribute != null);
}


bool XmlElement::GetAttribute( const char* name, Vector2& value ) const
{
	const char* attribute = GetAttribute(name);
	if( attribute != null )
		value = ToVector2(attribute);

	return (attribute != null);
}


bool XmlElement::GetAttribute( const char* name, Vector3& value ) const
{
	const char* attribute = GetAttribute(name);
	if( attribute != null )
		value = ToVector3(attribute);

	return (attribute != null);
}


bool XmlElement::GetAttribute( const char* name, Vector4& value ) const
{
	const char* attribute = GetAttribute(name);
	if( attribute != null )
		value = ToVector4(attribute);

	return (attribute != null);
}


bool XmlElement::GetAttribute( const char* name, Color& value ) const
{
	const char* attribute = GetAttribute(name);
	if( attribute != null )
		value = ToColor(attribute);

	return (attribute != null);
}


bool XmlElement::GetAttribute( const char* name, Colorf& value ) const
{
	const char* attribute = GetAttribute(name);
	if( attribute != null )
		value = ToColorf(attribute);

	return (attribute != null);
}


const char* XmlElement::GetTextElement( const char* name ) const
{
	return FirstChild(name).GetText();
}


bool XmlElement::GetBoolElement( const char* name, bool& value ) const
{
	const char* s = FirstChild(name).GetText();
	if( s != null )
		value = ToBool(s);

	return (s != null);
}


bool XmlElement::GetByteElement( const char* name, u8& value ) const
{
	const char* s = FirstChild(name).GetText();
	if( s != null )
		value = ToByte(s);

	return (s != null);
}


bool XmlElement::GetShortElement( const char* name, s16& value ) const
{
	const char* s = FirstChild(name).GetText();
	if( s != null )
		value = ToShort(s);

	return (s != null);
}


bool XmlElement::GetIntElement( const char* name, int& value ) const
{
	const char* s = FirstChild(name).GetText();
	if( s != null )
		value = ToInt(s);

	return (s != null);
}


bool XmlElement::GetUIntElement( const char* name, u32& value ) const
{
	return GetIntElement(name, *(int*)&value);
}


bool XmlElement::GetFloatElement( const char* name, float& value ) const
{
	const char* s = FirstChild(name).GetText();
	if( s != null )
		value = ToFloat(s);

	return (s != null);
}


bool XmlElement::GetRectElement( const char* name, Rect& value ) const
{
	const char* s = FirstChild(name).GetText();
	if( s != null )
		value = ToRect(s);

	return (s != null);
}


bool XmlElement::GetRectfElement( const char* name, Rectf& value ) const
{
	const char* s = FirstChild(name).GetText();
	if( s != null )
		value = ToRectf(s);

	return (s != null);
}


bool XmlElement::GetPointElement( const char* name, Point& value ) const
{
	const char* s = FirstChild(name).GetText();
	if( s != null )
		value = ToPoint(s);

	return (s != null);
}


bool XmlElement::GetPackedPointElement( const char* name, PackedPoint& value ) const
{
	const char* s = FirstChild(name).GetText();
	if( s != null )
		value = ToPackedPoint(s);

	return (s != null);
}


bool XmlElement::GetPackedRectElement( const char* name, PackedRect& value ) const
{
	const char* s = FirstChild(name).GetText();
	if( s != null )
		value = ToPackedRect(s);

	return (s != null);
}


bool XmlElement::GetVector2Element( const char* name, Vector2& value ) const
{
	const char* s = FirstChild(name).GetText();
	if( s != null )
		value = ToVector2(s);

	return (s != null);
}


bool XmlElement::GetVector3Element( const char* name, Vector3& value ) const
{
	const char* s = FirstChild(name).GetText();
	if( s != null )
		value = ToVector3(s);

	return (s != null);
}


bool XmlElement::GetVector4Element( const char* name, Vector4& value ) const
{
	const char* s = FirstChild(name).GetText();
	if( s != null )
		value = ToVector4(s);

	return (s != null);
}


bool XmlElement::GetColorElement( const char* name, Color& value ) const
{
	const char* s = FirstChild(name).GetText();
	if( s != null )
		value = ToColor(s);

	return (s != null);
}


bool XmlElement::GetColorfElement( const char* name, Colorf& value ) const
{
	const char* s = FirstChild(name).GetText();
	if( s != null )
		value = ToColorf(s);

	return (s != null);
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
	if( str.Empty() )
		return false;

	u32 index = 0;
	String token;
	String delimiters = ", \n\t()\"";

	for( u32 i(0); i < n; ++i )
	{
		int byteOffset = i * strideInBytes;
		if( (index = str.GetToken(token, index, delimiters)) != String::npos )
		{
			if( isIntegral )
			{
				if( strideInBytes == sizeof(char) )
					*((char*)ptr + byteOffset) = (char)token.ToInt();

				else if( strideInBytes == sizeof(s16) )
					*((s16*)((char*)ptr + byteOffset)) = (s16)token.ToInt();
	
				else if( strideInBytes == sizeof(int) )
					*((int*)((char*)ptr + byteOffset)) = (int)token.ToInt();

				else if( strideInBytes == sizeof(s64) )
					*((s64*)((char*)ptr + byteOffset)) = (s64)token.ToInt();

				else
				{
					//unsupported type.
					return false;
				}
			}
			else
			{
				if( strideInBytes == sizeof(float) )
					*((float*)((char*)ptr + byteOffset)) = (float)token.ToFloat();

				else if( strideInBytes == sizeof(double) )
					*((double*)((char*)ptr + byteOffset)) = (double)token.ToFloat();
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


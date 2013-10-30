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
#include "xml/tinyxml2.h"

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


XmlElement::XmlElement( XmlElement_t* element ) :
	m_element(element)
{
}


bool XmlElement::BeginNode( const fc::string& name )
{
	return BeginNode(name.c_str());
}


bool XmlElement::BeginNode( const char* name )
{
	XmlElement element = CreateChild(name);
	if( element )
	{
		*this = element;
		return true;
	}

	return false;
}


bool XmlElement::EndNode()
{
	return SetToParent();
}


bool XmlElement::SetToParent()
{
	CE_ASSERT(m_element);
	CE_ASSERT((void*)m_element->GetDocument() != (void*)m_element);

	XmlNode_t* parent = m_element->Parent();
	if( parent )
	{
		m_element = parent->ToElement();
		return true;
	}

	return false;
}


bool XmlElement::SetToChild( const char* name )
{
	CE_ASSERT(m_element);
	XmlElement element = NextChild(name);
	if( element )
	{
		m_element = element.m_element;
		return true;
	}

	return false;
}


XmlElement XmlElement::CreateChild( const fc::string& name )
{
	return CreateChild(name.c_str());
}


XmlElement XmlElement::CreateChild( const char* name )
{
	CE_ASSERT(m_element);
	XmlDocument_t* document = m_element->GetDocument();

	XmlElement_t* element = 0;
	if(m_element)
	{
		XmlElement_t* e = document->NewElement(name);
		element = m_element->InsertEndChild(e)->ToElement();
	}
	else
	{
		XmlElement_t* e = document->NewElement(name);
		element = document->InsertEndChild(e)->ToElement();
	}

	return XmlElement(element);
}


XmlElement XmlElement::GetParent()
{
	XmlNode_t* parent = m_element->Parent();
	if( parent )
		return XmlElement(parent->ToElement());

	return XmlElement();
}


XmlElement XmlElement::FirstChild( const fc::string& name ) const
{
	return FirstChild(name.c_str());
}


XmlElement XmlElement::FirstChild( const char* name ) const
{
	CE_ASSERT(m_element != 0);
	XmlElement_t* child = m_element->FirstChildElement(name);
	return XmlElement(child);
}


XmlElement XmlElement::NextChild( const fc::string& name ) const
{
	return NextChild(name.c_str());
}


XmlElement XmlElement::NextChild( const char* name ) const
{
	CE_ASSERT(m_element);

	XmlElement_t* sibling = m_element->NextSiblingElement(name);
	if( !sibling ) 
	{
		//get the first child element if no sibling is found.
		sibling = m_element->FirstChildElement(name);
	}

	return XmlElement(sibling);
}


void XmlElement::DeleteChildren()
{
	CE_ASSERT(m_element);
	m_element->DeleteChildren();
}


void XmlElement::DeleteChild( XmlElement element )
{
	CE_ASSERT(m_element);
	m_element->DeleteChild(element.m_element);
}


const char* XmlElement::GetCurrentNodeName() const
{
	CE_ASSERT(m_element);
	return m_element->Value();
}


bool XmlElement::HasAttribute( const char* name ) const
{
	CE_ASSERT(m_element);
	return (m_element->Attribute(name) != 0);
}


void XmlElement::DeleteAttribute( const char* name )
{
	CE_ASSERT(m_element);
	m_element->DeleteAttribute(name);
}



// write options

bool XmlElement::SetAttribute( const char* name, const char* value )
{
	CE_ASSERT(m_element);
	if( m_element )
		m_element->SetAttribute(name, value);

	return m_element != 0;
}


bool XmlElement::SetString( const char* name, const fc::string& value )
{
	return SetAttribute(name, value.c_str());
}


bool XmlElement::SetBool( const char* name, bool value )
{
	return SetAttribute(name, (value ? "true" : "false"));
}


bool XmlElement::SetByte( const char* name, byte value )
{
	return SetInt(name, (int)value);
}


bool XmlElement::SetShort( const char* name, short value )
{
	return SetInt(name, (int)value);
}


bool XmlElement::SetInt( const char* name, int value )
{
	return SetAttribute(name, fc::to_string(value).c_str());
}


bool XmlElement::SetUInt( const char* name, size_t value )
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


bool XmlElement::SetShortElement( const char* name, short value )
{
	return SetTextElement(name, ToString(value).c_str());
}


bool XmlElement::SetIntElement( const char* name, int value )
{
	return SetTextElement(name, ToString(value).c_str());
}


bool XmlElement::SetUIntElement( const char* name, size_t value )
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


bool XmlElement::WriteText( const fc::string& s )
{
	return WriteText(s.c_str());
}


bool XmlElement::WriteText( const char* s )
{
	CE_ASSERT(m_element);
	if( m_element )
	{
		XmlDocument_t* document = m_element->GetDocument();
		if( document )
		{
			m_element->InsertEndChild( document->NewText(s) );
			return true;
		}
	}

	return false;
}


bool XmlElement::WriteByteArray( const char* name, const byte* ptr, size_t n )
{
	return WriteArray(name, ptr, sizeof(byte), n, true);
}


bool XmlElement::WriteShortArray( const char* name, const short* ptr, size_t n )
{
	return WriteArray(name, ptr, sizeof(short), n, true);
}


bool XmlElement::WriteIntArray( const char* name, const int* ptr, size_t n )
{
	return WriteArray(name, ptr, sizeof(int), n, true);
}


bool XmlElement::WriteFloatArray( const char* name, const float* ptr, size_t n )
{
	return WriteArray(name, ptr, sizeof(float), n, false);
}


bool XmlElement::WriteArray( const char* name, const void* ptr, size_t strideInBytes, size_t n, bool isIntegral )
{
	fc::string formatedString;
	PrintArray(ptr, formatedString, strideInBytes, n, isIntegral);
	return SetAttribute(name, formatedString.c_str());
}


void XmlElement::PrintArray( const void* ptr, fc::string& str, size_t strideInBytes, size_t n, bool isIntegral )
{
	str.reserve(n * 4); //best guess

	char buf[64];
	for( size_t i(0); i < n; ++i )
	{
		size_t byteOffset = i * strideInBytes;

		if( isIntegral )
		{
			int val = int(*((char*)ptr + byteOffset));
			sprintf(buf, "%i", val);
		}
		else
		{
			float val = float(*((char*)ptr + byteOffset));
			sprintf(buf, "%f", val);
		}

		str.append(buf).append(',');
	}

	//remove the trailing ',' character.
	if( !str.empty() )
		str.pop_back();
}


bool XmlElement::WriteTextElement( const char* name, const fc::string& text )
{
	return WriteTextElement(name, text.c_str());
}


bool XmlElement::WriteTextElement( const char* name, const char* text )
{
	return CreateChild(name).WriteText(text);
}


bool XmlElement::WriteByteArrayElement( const char* name, const byte* ptr, size_t n )
{
	return WriteArrayElement(name, ptr, sizeof(byte), n, true);
}


bool XmlElement::WriteShortArrayElement( const char* name, const short* ptr, size_t n )
{
	return WriteArrayElement(name, ptr, sizeof(short), n, true);
}


bool XmlElement::WriteIntArrayElement( const char* name, const int* ptr, size_t n )
{
	return WriteArrayElement(name, ptr, sizeof(int), n, true);
}


bool XmlElement::WriteFloatArrayElement( const char* name, const float* ptr, size_t n )
{
	return WriteArrayElement(name, ptr, sizeof(float), n, false);
}


bool XmlElement::WriteArrayElement( const char* name, const void* ptr, size_t strideInBytes, size_t n, bool isIntegral )
{
	fc::string formatedString;
	PrintArray(ptr, formatedString, strideInBytes, n, isIntegral);
	return WriteTextElement(name, formatedString.c_str());
}




// read options

const char* XmlElement::GetText() const
{
	CE_ASSERT(m_element);
	return m_element->GetText();
}


bool XmlElement::GetAttribute( const char* name, fc::string& value ) const
{
	CE_ASSERT(m_element);
	const char* s = m_element->Attribute(name);
	if( s )
		value = s;

	return s != 0;
}


const char* XmlElement::GetAttribute( const char* name ) const
{
	CE_ASSERT(m_element);
	return m_element->Attribute(name);
}


fc::string XmlElement::GetString( const char* name ) const
{
	return fc::string(GetAttribute(name));
}


bool XmlElement::GetBool( const char* name, bool defaultValue ) const
{
	return ToBool(GetAttribute(name), defaultValue);
}


byte XmlElement::GetByte( const char* name, byte defaultValue ) const
{
	return (byte)GetInt(name, (int)defaultValue);
}


short XmlElement::GetShort( const char* name, short defaultValue ) const
{
	return (short)GetInt(name, (int)defaultValue);
}


int XmlElement::GetInt( const char* name, int defaultValue ) const
{
	return ToInt(GetAttribute(name), defaultValue);
}


size_t XmlElement::GetUInt( const char* name, size_t defaultValue ) const
{
	return (size_t)GetInt(name, (int)defaultValue);
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


byte XmlElement::GetByteElement( const char* name, byte defaultValue ) const
{
	const char* s = FirstChild(name).GetText();
	return ToByte(s, defaultValue);
}


short XmlElement::GetShortElement( const char* name, short defaultValue ) const
{
	const char* s = FirstChild(name).GetText();
	return ToShort(s, defaultValue);
}


int XmlElement::GetIntElement( const char* name, int defaultValue ) const
{
	const char* s = FirstChild(name).GetText();
	return ToInt(s, defaultValue);
}


size_t XmlElement::GetUIntElement( const char* name, size_t defaultValue ) const
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


bool XmlElement::ReadByteArray( const char* name, ubyte* ptr, size_t n ) const
{
	return ReadArray(name, ptr, sizeof(ubyte), n, true);
}


bool XmlElement::ReadShortArray( const char* name, short* ptr, size_t n ) const
{
	return ReadArray(name, ptr, sizeof(short), n, true);
}


bool XmlElement::ReadIntArray( const char* name, int* ptr, size_t n ) const
{
	return ReadArray(name, ptr, sizeof(int), n, true);
}


bool XmlElement::ReadFloatArray( const char* name, float* ptr, size_t n ) const
{
	return ReadArray(name, ptr, sizeof(float), n, false);
}


bool XmlElement::ReadArray( const char* name, void* ptr, size_t strideInBytes, size_t n, bool isIntegral ) const
{
	fc::string str = GetAttribute(name);
	return ParseArray(ptr, str, strideInBytes, n, isIntegral);
}


bool XmlElement::ParseArray( void* ptr, const fc::string& str, size_t strideInBytes, size_t n, bool isIntegral )
{
	if( str.empty() )
		return false;

	size_t index = 0;
	fc::string token;
	fc::string delimiters = ", \n\t()\"";

	for( size_t i(0); i < n; ++i )
	{
		int byteOffset = i * strideInBytes;
		if( fc::tokenizer::get_token(str, delimiters, index, token) )
		{
			if( isIntegral )
			{
				if( strideInBytes == sizeof(char) )
					*((char*)ptr + byteOffset) = (char)token.to_int();

				else if( strideInBytes == sizeof(short) )
					*((short*)((char*)ptr + byteOffset)) = (short)token.to_int();
	
				else if( strideInBytes == sizeof(int) )
					*((int*)((char*)ptr + byteOffset)) = (int)token.to_int();

				else if( strideInBytes == sizeof(int64) )
					*((int64*)((char*)ptr + byteOffset)) = (int64)token.to_int();

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


bool XmlElement::ReadByteArrayElement( const char* name, byte* ptr, size_t n ) const
{
	return ReadArrayElement(name, ptr, sizeof(byte), n, true);
}


bool XmlElement::ReadShortArrayElement( const char* name, short* ptr, size_t n ) const
{
	return ReadArrayElement(name, ptr, sizeof(short), n, true);
}


bool XmlElement::ReadIntArrayElement( const char* name, int* ptr, size_t n ) const
{
	return ReadArrayElement(name, ptr, sizeof(int), n, true);
}


bool XmlElement::ReadFloatArrayElement( const char* name, float* ptr, size_t n ) const
{
	return ReadArrayElement(name, ptr, sizeof(float), n, false);
}


bool XmlElement::ReadArrayElement( const char* name, void* ptr, size_t strideInBytes, size_t n, bool isIntegral ) const
{
	fc::string str = GetTextElement(name);
	return ParseArray(ptr, str, strideInBytes, n, isIntegral);
}




CE_NAMESPACE_END


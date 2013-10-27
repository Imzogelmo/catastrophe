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
#include "IO/XmlReader.h"

#include "Math/Point.h"
#include "Math/Rect.h"
#include "Math/Rectf.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Vector4.h"
#include "Math/Color.h"
#include "Math/Colorf.h"
#include "Math/Matrix.h"


CE_NAMESPACE_BEGIN


XmlReader::XmlReader() :
	m_filename(),
	m_document(0),
	m_element(0)
{
}


XmlReader::XmlReader( const fc::string& filename ) :
	m_filename(),
	m_document(0),
	m_element(0)
{
	Open(filename);
}


XmlReader::~XmlReader()
{
	if( IsOpen() )
		Close();
}


bool XmlReader::Open( const fc::string& filename )
{
	if(IsOpen())
		Close();

	m_filename = filename;
	m_document = new XmlDocument_t();

	if( m_document->LoadFile(filename.c_str()) != 0 )
	{
		Close();
		Log("Failed to open file (%s)", filename.c_str());
		return false;
	}

	m_element = m_document->RootElement();
	return true;
}


void XmlReader::Close()
{
	if(m_document)
	{
		delete m_document;
		m_document = 0;
	}

	m_filename.clear();
	m_element = 0;
}


fc::string XmlReader::GetCurrentNodeName() const
{
	CE_ASSERT(m_element != 0);
	return fc::string(m_element->Value());
}


bool XmlReader::FirstChild( const fc::string& name )
{
	CE_ASSERT(m_element != 0);

	XmlElement_t* child = m_element->FirstChildElement(name.c_str());
	if( child )
	{
		m_element = child;
		return true;
	}

	return false;
}


bool XmlReader::NextChild( const fc::string& name )
{
	CE_ASSERT(m_element != 0);

	XmlElement_t* sibling = m_element->NextSiblingElement(name.c_str());
	if( !sibling ) 
	{
		//get the first child element if no sibling is found.
		sibling = m_element->FirstChildElement(name.c_str());
	}
	else
	{
		m_element = sibling;
		return true;
	}

	return false;
}


bool XmlReader::SetToParent()
{
	CE_ASSERT(m_element != 0);
	CE_ASSERT((void*)m_element != (void*)m_document);

	XmlNode_t* parent = m_element->Parent();
	if(parent)
	{
		m_element = parent->ToElement();
		return true;
	}

	return false;
}


bool XmlReader::HasAttribute( const fc::string& name ) const
{
	CE_ASSERT(m_element != 0);
	return (m_element->Attribute(name.c_str()) != 0);
}


bool XmlReader::ReadString( const char* name, fc::string& value ) const
{
	bool ret = false;
	const char* s = m_element->Attribute(name);
	if( s != 0 )
	{
		value = s;
		ret = true;
	}

	return ret;
}


bool XmlReader::ReadBool( const char* name, bool& value ) const
{
	CE_ASSERT(m_element != 0);
	return m_element->QueryBoolAttribute(name, &value) == tinyxml2::XML_NO_ERROR;
}


bool XmlReader::ReadByte( const char* name, byte& value ) const
{
	int v = 0;
	bool ret = false;
	if( GetInt(name, v) )
	{
		value = (byte)v;
		ret = true;
	}

	return ret;
}


bool XmlReader::ReadShort( const char* name, short& value ) const
{
	int v = 0;
	bool ret = false;
	if( GetInt(name, v) )
	{
		value = (short)v;
		ret = true;
	}

	return ret;
}


bool XmlReader::ReadInt( const char* name, int& value ) const
{
	CE_ASSERT(m_element != 0);
	return m_element->QueryIntAttribute(name, &value) == tinyxml2::XML_NO_ERROR;
}


bool XmlReader::ReadUInt( const char* name, size_t& value ) const
{
	int v = 0;
	bool ret = false;
	if( GetInt(name, v) )
	{
		value = (size_t)v;
		ret = true;
	}

	return ret;
}


bool XmlReader::ReadFloat( const char* name, float& value ) const
{
	CE_ASSERT(m_element != 0);
	return m_element->QueryFloatAttribute(name, &value) == tinyxml2::XML_NO_ERROR;
}



enum TypeAttributeEnum
{
	AttributeType_Bool,
	AttributeType_Byte,
	AttributeType_Short,
	AttributeType_Int,
	AttributeType_UInt,
	AttributeType_Float,
	AttributeType_String,
	AttributeType_Rect,
	AttributeType_Rectf,
	AttributeType_Point,
	AttributeType_Vector2,
	AttributeType_Vector3,
	AttributeType_Vector4,
	AttributeType_Color,
	AttributeType_Colorf,
	AttributeType_Matrix,

};


bool XmlReader::GetBoolElement( const char* name, bool& value )
{
	return GetTypeElement(name, (void*)&value, AttributeType_Bool);
}


bool XmlReader::GetByteElement( const char* name, char& value )
{
	return GetTypeElement(name, (void*)&value, AttributeType_Byte);
}


bool XmlReader::GetShortElement( const char* name, short& value )
{
	return GetTypeElement(name, (void*)&value, AttributeType_Short);
}


bool XmlReader::GetIntElement( const char* name, int& value )
{
	return GetTypeElement(name, (void*)&value, AttributeType_Int);
}


bool XmlReader::GetUIntElement( const char* name, size_t& value )
{
	return GetTypeElement(name, (void*)&value, AttributeType_UInt);
}


bool XmlReader::GetFloatElement( const char* name, float& value )
{
	return GetTypeElement(name, (void*)&value, AttributeType_Float);
}


bool XmlReader::GetStringElement( const char* name, fc::string& value )
{
	return GetTypeElement(name, (void*)&value, AttributeType_String);
}


bool XmlReader::GetRectElement( const char* name, Rect& value )
{
	return GetTypeElement(name, (void*)&value, AttributeType_Rect);
}


bool XmlReader::GetRectfElement( const char* name, Rectf& value )
{
	return GetTypeElement(name, (void*)&value, AttributeType_Rectf);
}


bool XmlReader::GetPointElement( const char* name, Point& value )
{
	return GetTypeElement(name, (void*)&value, AttributeType_Point);
}


bool XmlReader::GetVector2Element( const char* name, Vector2& value )
{
	return GetTypeElement(name, (void*)&value, AttributeType_Vector2);
}


bool XmlReader::GetVector3Element( const char* name, Vector3& value )
{
	return GetTypeElement(name, (void*)&value, AttributeType_Vector3);
}


bool XmlReader::GetVector4Element( const char* name, Vector4& value )
{
	return GetTypeElement(name, (void*)&value, AttributeType_Vector4);
}


bool XmlReader::GetColorElement( const char* name, Color& value )
{
	return GetTypeElement(name, (void*)&value, AttributeType_Color);
}


bool XmlReader::GetColorfElement( const char* name, Colorf& value )
{
	return GetTypeElement(name, (void*)&value, AttributeType_Colorf);
}


bool XmlReader::GetMatrixElement( const char* name, Matrix& value )
{
	return GetTypeElement(name, (void*)&value, AttributeType_Matrix);
}


bool XmlReader::GetTypeElement( const char* name, void* value, int type )
{
	bool ret = false;
	if( FirstChild(name) )
	{
		switch( type )
		{
			case AttributeType_Bool: ret = ReadBool("value", *(bool*)value); break;
			case AttributeType_Byte: ret = ReadByte("value", *(byte*)value); break;
			case AttributeType_Short: ret = ReadShort("value", *(short*)value); break;
			case AttributeType_Int: ret = ReadInt("value", *(int*)value); break;
			case AttributeType_UInt: ret = ReadUInt("value", *(unsigned int*)value); break;
			case AttributeType_Float: ret = ReadFloat("value", *(float*)value); break;
			case AttributeType_String: ret = ReadString("value", *(fc::string*)value); break;
			case AttributeType_Rect:
			{
				Rect& r = *(Rect*)value;
				ret = ReadInt("x", r.pos.x);
				ret &= ReadInt("y", r.pos.y);
				ret &= ReadInt("w", r.size.x);
				ret &= ReadInt("h", r.size.y);
				break;
			}
			case AttributeType_Rectf:
			{
				Rectf& r = *(Rectf*)value;
				ret = ReadFloat("min_x", r.min.x);
				ret &= ReadFloat("min_y", r.min.y);
				ret &= ReadFloat("max_x", r.max.x);
				ret &= ReadFloat("max_y", r.max.y);
				break;
			}
			case AttributeType_Point:
			{
				Point& p = *(Point*)value;
				ret = ReadInt("x", p.x);
				ret &= ReadInt("y", p.y);
				break;
			}
			case AttributeType_Vector2:
			{
				Vector2& v = *(Vector2*)value;
				ret = ReadFloat("x", v.x);
				ret &= ReadFloat("y", v.y);
				break;
			}
			case AttributeType_Vector3:
			{
				Vector3& v = *(Vector3*)value;
				ret = ReadFloat("x", v.x);
				ret &= ReadFloat("y", v.y);
				ret &= ReadFloat("z", v.z);
				break;
			}
			case AttributeType_Vector4:
			{
				Vector4& v = *(Vector4*)value;
				ret = ReadFloat("x", v.x);
				ret &= ReadFloat("y", v.y);
				ret &= ReadFloat("z", v.z);
				ret &= ReadFloat("w", v.w);
				break;
			}
			case AttributeType_Color:
			{
				Color& c = *(Color*)value;
				ret = ReadByte("r", c.r);
				ret &= ReadByte("g", c.g);
				ret &= ReadByte("b", c.b);
				ret &= ReadByte("a", c.a);
				break;
			}
			case AttributeType_Colorf:
			{
				Colorf& c = *(Colorf*)value;
				ret = ReadFloat("r", c.r);
				ret &= ReadFloat("g", c.g);
				ret &= ReadFloat("b", c.b);
				ret &= ReadFloat("a", c.a);
				break;
			}
			case AttributeType_Matrix:
			{
				ret = ReadFloatArray((float*)value, 16);
				break;
			}
			default:
			{
				Log("XmlReader::GetTypeElement: invalid AttributeType enum value.");
				break;
			}

		}

		SetToParent();
	}

	if( !ret )
	{
		Log("XmlReader: Failed to read from element (%s).", name);
	}

	return ret;
}


fc::string XmlReader::GetString( const char* name ) const
{
	fc::string ret;
	ReadString(name, ret);
	return ret;
}


bool XmlReader::GetBool( const char* name, bool defaultValue ) const
{
	ReadBool(name, defaultValue);
	return defaultValue;
}


byte XmlReader::GetByte( const char* name, byte defaultValue ) const
{
	ReadByte(name, defaultValue);
	return defaultValue;
}


short XmlReader::GetShort( const char* name, short defaultValue ) const
{
	ReadShort(name, defaultValue);
	return defaultValue;
}


int XmlReader::GetInt( const char* name, int defaultValue ) const
{
	ReadInt(name, defaultValue);
	return defaultValue;
}


size_t XmlReader::GetUInt( const char* name, size_t defaultValue ) const
{
	ReadUInt(name, defaultValue);
	return defaultValue;
}


float XmlReader::GetFloat( const char* name, float defaultValue ) const
{
	ReadFloat(name, defaultValue);
	return defaultValue;
}


fc::string XmlReader::ReadText() const
{
	CE_ASSERT(m_element != 0);

	XmlNode_t* child = m_element->FirstChild();
	if( !child )
		return fc::string();

	return fc::string(child->Value());
}


bool XmlReader::ReadByteArray( ubyte* ptr, size_t n )
{
	return ReadArray(ptr, sizeof(ubyte), n, true);
}


bool XmlReader::ReadShortArray( short* ptr, size_t n )
{
	return ReadArray(ptr, sizeof(short), n, true);
}


bool XmlReader::ReadIntArray( int* ptr, size_t n )
{
	return ReadArray(ptr, sizeof(int), n, true);
}


bool XmlReader::ReadFloatArray( float* ptr, size_t n )
{
	return ReadArray(ptr, sizeof(float), n, false);
}


bool XmlReader::ReadArray( void* ptr, size_t strideInBytes, size_t n, bool isIntegral )
{
	fc::string str = ReadText();
	if(str.empty())
		return false;

	fc::string token;
	fc::tokenizer t(str, ", \n\t()\"");
	for( size_t i(0); i < n; ++i )
	{
		int byteOffset = i * strideInBytes;
		if( t.next(token) )
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


CE_NAMESPACE_END

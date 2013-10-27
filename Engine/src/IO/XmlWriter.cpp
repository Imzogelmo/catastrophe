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

#include "xml/tinyxml2.h"

#include "Common.h"
#include "IO/XmlWriter.h"

#include "Math/Point.h"
#include "Math/Rect.h"
#include "Math/Rectf.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Vector4.h"
#include "Math/Color.h"
#include "Math/Colorf.h"
#include "Math/Matrix.h"


#ifdef _MSC_VER
	#pragma warning ( push )
	#pragma warning ( disable : 4996 )
#endif

CE_NAMESPACE_BEGIN


XmlWriter::XmlWriter() :
	m_filename(),
	m_document(0),
	m_element(0)
{
}


XmlWriter::XmlWriter( const fc::string& filename ) :
	m_filename(),
	m_document(0),
	m_element(0)
{
	Open(filename);
}


XmlWriter::~XmlWriter()
{
	Close();
}


bool XmlWriter::Open( const fc::string& filename )
{
	CE_ASSERT(!m_document);
	CE_ASSERT(!m_element);
	CE_ASSERT(!filename.empty());

	m_filename = filename;
	m_document = new XmlDocument_t;

	// <?xml version="1.0" encoding="UTF-8"?>
	tinyxml2::XMLDeclaration* declaration = m_document->NewDeclaration();
	m_document->LinkEndChild(declaration);

	return true;
}


bool XmlWriter::Close()
{
	if( !IsOpen() )
		return true;

	CE_ASSERT(m_document);
	bool success = (m_document->SaveFile(m_filename.c_str()) == 0);  

	delete m_document;
	m_document = 0;
	m_element = 0;

	return success;
}


bool XmlWriter::BeginNode( const fc::string& name )
{
	CE_ASSERT(IsOpen());

	XmlElement_t* node;
	if(m_element)
	{
		XmlElement_t* e = m_document->NewElement(name.c_str());
		node = m_element->InsertEndChild(e)->ToElement();
	}
	else
	{
		XmlElement_t* e = m_document->NewElement(name.c_str());
		node = m_document->InsertEndChild(e)->ToElement();
	}

	CE_ASSERT(node != 0);
	m_element = node;

	return (m_element != 0);
}


void XmlWriter::EndNode()
{
	CE_ASSERT(IsOpen());
	CE_ASSERT(m_element);

	XmlNode_t* parent = m_element->Parent();
	if(parent == m_document)
	{
		m_element = 0;
	}
	else
	{
		m_element = parent->ToElement();
	}
}


void XmlWriter::Write( const fc::string& s )
{
	Write(s.c_str());
}


void XmlWriter::Write( const char* s )
{
	CE_ASSERT(IsOpen());
	CE_ASSERT(m_element);
	m_element->InsertEndChild( m_document->NewText(s) )->ToElement();
}


void XmlWriter::WriteByteArray( const ubyte* ptr, size_t n )
{
	WriteArray(ptr, sizeof(ubyte), n, true);
}


void XmlWriter::WriteShortArray( const short* ptr, size_t n )
{
	WriteArray(ptr, sizeof(short), n, true);
}


void XmlWriter::WriteIntArray( const int* ptr, size_t n )
{
	WriteArray(ptr, sizeof(int), n, true);
}


void XmlWriter::WriteFloatArray( const float* ptr, size_t n )
{
	WriteArray(ptr, sizeof(float), n, false);
}


void XmlWriter::WriteArray( const void* ptr, size_t strideInBytes, size_t n, bool isIntegral )
{
	fc::string str;
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
	if(!str.empty())
		str.pop_back();

	Write(str.c_str());
}


void XmlWriter::SetString( const fc::string& name, const fc::string& value )
{
	SetString(name.c_str(), value.c_str());
}


void XmlWriter::SetString( const char* name, const char* value )
{
	CE_ASSERT(IsOpen());
	CE_ASSERT(m_element);
	m_element->SetAttribute(name, value);
}


void XmlWriter::SetBool( const fc::string& name, bool value )
{
	SetString(name.c_str(), (value ? "true" : "false"));
}


void XmlWriter::SetBool( const char* name, bool value )
{
	SetString(name, (value ? "true" : "false"));
}


void XmlWriter::SetByte( const fc::string& name, char value )
{
	SetInt(name.c_str(), (int)value);
}


void XmlWriter::SetByte( const char* name, char value )
{
	SetInt(name, (int)value);
}


void XmlWriter::SetShort( const fc::string& name, short value )
{
	SetInt(name.c_str(), (int)value);
}


void XmlWriter::SetShort( const char* name, short value )
{
	SetInt(name, (int)value);
}


void XmlWriter::SetInt( const fc::string& name, int value )
{
	SetInt(name.c_str(), value);
}


void XmlWriter::SetInt( const char* name, int value )
{
	CE_ASSERT(IsOpen());
	CE_ASSERT(m_element);
	m_element->SetAttribute(name, value);
}


void XmlWriter::SetUInt( const fc::string& name, size_t value )
{
	SetInt(name.c_str(), (int)value);
}


void XmlWriter::SetUInt( const char* name, size_t value )
{
	SetInt(name, (int)value);
}


void XmlWriter::SetFloat( const fc::string& name, float value )
{
	SetFloat(name.c_str(), value);
}


void XmlWriter::SetFloat( const char* name, float value )
{
	CE_ASSERT(IsOpen());
	CE_ASSERT(m_element);
	m_element->SetAttribute(name, fc::to_string(value).c_str());
}


void XmlWriter::SetStringElement( const char* name, const char* value )
{
	BeginNode(name);
	SetString("value", value);
	EndNode();
}


void XmlWriter::SetBoolElement( const char* name, bool value )
{
	BeginNode(name);
	SetBool("value", value);
	EndNode();
}


void XmlWriter::SetByteElement( const char* name, char value )
{
	BeginNode(name);
	SetByte("value", value);
	EndNode();
}


void XmlWriter::SetShortElement( const char* name, short value )
{
	BeginNode(name);
	SetShort("value", value);
	EndNode();
}


void XmlWriter::SetIntElement( const char* name, int value )
{
	BeginNode(name);
	SetInt("value", value);
	EndNode();
}


void XmlWriter::SetUIntElement( const char* name, size_t value )
{
	BeginNode(name);
	SetUInt("value", value);
	EndNode();
}


void XmlWriter::SetFloatElement( const char* name, float value )
{
	BeginNode(name);
	SetFloat("value", value);
	EndNode();
}


void XmlWriter::SetRectElement( const char* name, const Rect& value )
{
	BeginNode(name);
	SetInt("x", value.pos.x);
	SetInt("y", value.pos.y);
	SetInt("w", value.size.x);
	SetInt("h", value.size.y);
	EndNode();
}


void XmlWriter::SetRectfElement( const char* name, const Rectf& value )
{
	BeginNode(name);
	SetFloat("min_x", value.min.x);
	SetFloat("min_y", value.min.y);
	SetFloat("max_x", value.max.x);
	SetFloat("max_y", value.max.y);
	EndNode();
}


void XmlWriter::SetPointElement( const char* name, const Point& value )
{
	BeginNode(name);
	SetInt("x", value.x);
	SetInt("y", value.y);
	EndNode();
}


void XmlWriter::SetVector2Element( const char* name, const Vector2& value )
{
	BeginNode(name);
	SetFloat("x", value.x);
	SetFloat("y", value.y);
	EndNode();
}


void XmlWriter::SetVector3Element( const char* name, const Vector3& value )
{
	BeginNode(name);
	SetFloat("x", value.x);
	SetFloat("y", value.y);
	SetFloat("z", value.z);
	EndNode();
}


void XmlWriter::SetVector4Element( const char* name, const Vector4& value )
{
	BeginNode(name);
	SetFloat("x", value.x);
	SetFloat("y", value.y);
	SetFloat("z", value.z);
	SetFloat("w", value.w);
	EndNode();
}


void XmlWriter::SetColorElement( const char* name, const Color& value )
{
	BeginNode(name);
	SetByte("r", value.r);
	SetByte("g", value.g);
	SetByte("b", value.b);
	SetByte("a", value.a);
	EndNode();
}


void XmlWriter::SetColorfElement( const char* name, const Colorf& value )
{
	BeginNode(name);
	SetFloat("r", value.r);
	SetFloat("g", value.g);
	SetFloat("b", value.b);
	SetFloat("a", value.a);
	EndNode();
}


void XmlWriter::SetMatrixElement( const char* name, const Matrix& value )
{
	BeginNode(name);
	WriteFloatArray(&value[0], 16);
	EndNode();
}





#ifdef _MSC_VER
	#pragma warning ( pop )
#endif


CE_NAMESPACE_END



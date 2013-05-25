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

#include "xml/tinyxml2.cpp"

#include "Common.h"
#include "IO/XMLWriter.h"

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


void XmlWriter::WriteByteBlock( ubyte* ptr, size_t n )
{
	WriteBlock<ubyte>(ptr, n, true);
}


void XmlWriter::WriteShortBlock( short* ptr, size_t n )
{
	WriteBlock<short>(ptr, n, true);
}


void XmlWriter::WriteIntBlock( int* ptr, size_t n )
{
	WriteBlock<int>(ptr, n, true);
}


template <class T>
void XmlWriter::WriteBlock( T* ptr, size_t n, bool isIntegral )
{
	fc::string str;
	str.reserve(n * 4); //best guess

	char buf[64];
	for( size_t i(0); i < n; ++i )
	{
		if( isIntegral )
		{
			int val = (int)ptr[i];
			sprintf(buf, "%i", val);
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



#ifdef _MSC_VER
	#pragma warning ( pop )
#endif


CE_NAMESPACE_END



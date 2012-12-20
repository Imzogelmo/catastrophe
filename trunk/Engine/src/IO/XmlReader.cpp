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

CE_NAMESPACE_BEGIN


XmlReader::XmlReader() :
	m_filename(),
	m_document(0),
	m_element(0)
{
}


XmlReader::XmlReader(const fc::string& filename) :
	m_filename(),
	m_document(0),
	m_element(0)
{
	Open(filename);
}


XmlReader::~XmlReader()
{
	if(IsOpen())
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
	if(child)
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
	if(!sibling) 
	{
		//get the next child element if no sibling is found.
		sibling = m_element->FirstChildElement(name.c_str());
	}

	if(sibling)
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


fc::string XmlReader::GetString( const fc::string& name ) const
{
	CE_ASSERT(m_element != 0);

	fc::string ret = m_element->Attribute(name.c_str());    
	//if(ret.empty())
	//	n_error("XmlReader: attribute '%s' doesn't exist on node '%s'!", name.c_str(), m_element->Value());

	return ret;
}


bool XmlReader::GetBool( const fc::string& name, bool defaultValue ) const
{
	CE_ASSERT(m_element != 0);
	bool ret(defaultValue);
	m_element->QueryBoolAttribute(name.c_str(), &ret);

	return ret;
}


short XmlReader::GetShort( const fc::string& name, short defaultValue ) const
{
	return (short)GetInt(name, defaultValue);
}


int XmlReader::GetInt( const fc::string& name, int defaultValue ) const
{
	CE_ASSERT(m_element != 0);
	int ret(defaultValue);
	m_element->QueryIntAttribute(name.c_str(), &ret);

	return ret;
}


size_t XmlReader::GetUInt( const fc::string& name, size_t defaultValue ) const
{
	return (size_t)GetInt(name, defaultValue);
}


float XmlReader::GetFloat( const fc::string& name, float defaultValue ) const
{
	CE_ASSERT(m_element != 0);
	float ret(defaultValue);
	m_element->QueryFloatAttribute(name.c_str(), &ret);

	return ret;
}


fc::string XmlReader::ReadText() const
{
	CE_ASSERT(m_element != 0);

	XmlNode_t* child = m_element->FirstChild();
	if(!child)
		return fc::string();

	return fc::string(child->Value());
}


bool XmlReader::ReadShortBlock( short* ptr, size_t n )
{
	return ReadBlock<short>(ptr, n, true);
}


bool XmlReader::ReadIntBlock( int* ptr, size_t n )
{
	return ReadBlock<int>(ptr, n, true);
}


bool XmlReader::ReadFloatBlock( float* ptr, size_t n )
{
	return ReadBlock<float>(ptr, n, false);
}


template <class T>
bool XmlReader::ReadBlock( T* ptr, size_t n, bool isIntegral )
{
	fc::string str = ReadText();
	if(str.empty())
		return false;

	fc::string token;
	fc::tokenizer t(str, ", \n\t()\"");
	for( size_t i(0); i < n; ++i )
	{
		if(t.next(token))
		{
			if(isIntegral)
			{
				ptr[i] = (T)token.to_int();
			}
			else
			{
				ptr[i] = (T)token.to_float();
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

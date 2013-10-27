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
#include "xml/tinyxml2.cpp"

#include "Common.h"
#include "IO/XmlDocument.h"
#include "Core/StringUtils.h"

CE_NAMESPACE_BEGIN


XmlDocument::XmlDocument() :
	m_document(0)
{
	m_document = new XmlDocument_t();
}


XmlDocument::~XmlDocument()
{
	delete m_document;
}


bool XmlDocument::Load( const fc::string& filename )
{
	Reset();
	if( m_document->LoadFile(filename.c_str()) != 0 )
	{
		Log("Failed to load file (%s)", filename.c_str());
		m_document->PrintError();
		return false;
	}

	return true;
}


bool XmlDocument::Save( const fc::string& filename )
{
	if( m_document->SaveFile(filename.c_str()) != 0 )
	{
		Log("Failed to save file (%s)", filename.c_str());
		m_document->PrintError();
		return false;
	}

	return true;
}


bool XmlDocument::Parse( const fc::string& xml )
{
	if( m_document->Parse(xml.c_str(), xml.size()) != 0)
	{
		Log("Failed to parse string.");
		m_document->PrintError();
		return false;
	}

	return true;
}


void XmlDocument::CreateDeclaration()
{
	// <?xml version="1.0" encoding="UTF-8"?>
	tinyxml2::XMLDeclaration* declaration = m_document->NewDeclaration();
	m_document->LinkEndChild(declaration);
}


void XmlDocument::Reset()
{
	m_document->DeleteChildren();
}


XmlElement XmlDocument::GetRoot() const
{
	CE_ASSERT(m_document);
	return XmlElement(m_document->RootElement());
}


XmlElement XmlDocument::CreateRoot( const char* name )
{
	CE_ASSERT(m_document);

	//Reset();
	XmlElement_t* element = m_document->NewElement(name);
	XmlElement_t* root = m_document->InsertEndChild(element)->ToElement();

	return XmlElement(root);
}




CE_NAMESPACE_END


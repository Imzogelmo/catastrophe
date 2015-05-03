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
#include "Catastrophe/Core/IO/File.h"
#include "Catastrophe/Core/IO/XmlDocument.h"
#include "Core/StringUtils.h"

CE_NAMESPACE_BEGIN

bool xml_doc_has_parse_error = false;


XmlDocument::XmlDocument() :
	m_document(0)
{
	m_document = new XmlDocument_t();
}


XmlDocument::~XmlDocument()
{
	delete m_document;
}


bool XmlDocument::Load( const String& filename )
{
	Reset();

	File f(filename, FileRead);
	if( !f.IsOpen() )
		return false;

	//allocate buffer and terminate string.
	u32 size = f.Size();
	m_buffer.Resize(size + 1, 0);

	//read file into memory and close.
	f.Read(&m_buffer[0], size);
	f.Close();

	xml_doc_has_parse_error = false;

	m_document->parse<0>(&m_buffer[0]);
	if( xml_doc_has_parse_error )
		return false;

	return true;
}


bool XmlDocument::Save( const String& filename )
{
	String xmlString;
	xmlString.Reserve(RAPIDXML_STATIC_POOL_SIZE * 4);

	xml_doc_has_parse_error = false;
	rapidxml::print(BackInsertIterator<String>(xmlString), *m_document);

	File f(filename, FileWriteText);
	if( !xmlString.Empty() && f.IsOpen() )
	{
		f.Write((void*)&xmlString[0], xmlString.size() + 1);
		f.Close();

		return true;
	}

	return false;
}


void XmlDocument::CreateDeclaration()
{
	// <?xml version="1.0" encoding="UTF-8"?>
	rapidxml::xml_node<>* decl = m_document->allocate_node(rapidxml::node_declaration);
	decl->append_attribute(m_document->allocate_attribute("version", "1.0"));
	decl->append_attribute(m_document->allocate_attribute("encoding", "utf-8"));
	m_document->append_node(decl);
}


void XmlDocument::Reset()
{
	m_document->clear();
}


XmlElement XmlDocument::GetRoot() const
{
	CE_ASSERT(m_document != null);
	XmlNode_t* root = m_document->first_node();
	while( root && (
		root->type() == rapidxml::node_declaration ||
		root->type() == rapidxml::node_doctype ||
		root->type() == rapidxml::node_comment )
		)
	{
		root = root->next_sibling();
	}

	return XmlElement(root);
}


XmlElement XmlDocument::CreateRoot( const char* name )
{
	CE_ASSERT(m_document != null);
	CE_ASSERT(!GetRoot());

	char* nodeName = m_document->allocate_string(name);
	XmlNode_t* root = m_document->allocate_node(rapidxml::node_element, nodeName);
	m_document->append_node(root);

	return XmlElement(root);
}


//rapidxml required user error handler
void rapidxml::parse_error_handler( char const *msg, void* )
{
	xml_doc_has_parse_error = true;
	LogError(msg);
}


CE_NAMESPACE_END


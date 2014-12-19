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

#include "XmlElement.h"

#include <fc/string.h>

CE_NAMESPACE_BEGIN


class CE_API XmlDocument
{
public:
	XmlDocument();
	virtual ~XmlDocument();

	void Reset();
	bool Load( const String& filename );
	bool Save( const String& filename );
	bool Parse( const String& xml );

	void CreateDeclaration();
	XmlElement CreateRoot( const char* name );
	XmlElement GetRoot() const;
	XmlDocument_t* GetDocumentPtr() const { return m_document; }

	operator bool () const { return m_document != 0; }

private:
	XmlDocument( const XmlDocument& );
	XmlDocument& operator =( const XmlDocument& );

	XmlDocument_t*	m_document;
	String		m_buffer;
};


CE_NAMESPACE_END

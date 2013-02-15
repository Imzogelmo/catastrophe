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

#include <fc/string.h>

#include "../Common.h"

CE_NAMESPACE_BEGIN


class CE_API XmlWriter
{
public:
	XmlWriter();
	XmlWriter( const fc::string& filename );
	virtual ~XmlWriter();

	virtual bool Open( const fc::string& filename );
	virtual bool Close();

	bool BeginNode( const fc::string& nodeName );
	void EndNode();
	void Write( const fc::string& text );
	void Write( const char* text );
	void WriteByteBlock( ubyte* ptr, size_t n );
	void WriteShortBlock( short* ptr, size_t n );
	void WriteIntBlock( int* ptr, size_t n );
	template <class T> void WriteBlock( T* ptr, size_t n, bool isIntegral = true );

	void SetString( const fc::string& name, const fc::string& value );
	void SetBool( const fc::string& name, bool value );
	void SetShort( const fc::string& name, short value );
	void SetInt( const fc::string& name, int value );
	void SetUInt( const fc::string& name, size_t value );
	void SetFloat( const fc::string& name, float value );

	void SetString( const char* name, const char* value );
	void SetBool( const char* name, bool value );
	void SetShort( const char* name, short value );
	void SetInt( const char* name, int value );
	void SetUInt( const char* name, size_t value );
	void SetFloat( const char* name, float value );
	
	bool IsOpen() const { return ( m_document != 0 ); }

private:
	fc::string		m_filename;
	XmlDocument_t*	m_document;
	XmlElement_t*	m_element;
};


CE_NAMESPACE_END

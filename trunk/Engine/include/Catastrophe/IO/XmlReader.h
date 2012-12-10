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
#include <fc/tokenizer.h>

#include "../Common.h"

CE_NAMESPACE_BEGIN


class XmlReader
{
public:
	enum eTokenType
	{
		Boolean,
		Integral,
		Float
	};

	XmlReader();
	XmlReader( const fc::string& filename );
	virtual ~XmlReader();

	virtual bool Open( const fc::string& filename );
	virtual void Close();

	fc::string GetCurrentNodeName() const;

	bool FirstChild( const fc::string& name = "" );
	bool NextChild( const fc::string& name = "" );
	bool SetToParent();
	bool HasAttribute( const fc::string& attr ) const;

	fc::string ReadText() const;
	bool ReadShortBlock( short* ptr, size_t n );
	bool ReadIntBlock( int* ptr, size_t n );
	bool ReadFloatBlock( float* ptr, size_t n );
	template <class T> bool ReadBlock( T* ptr, size_t n, bool isIntegral = true );

	fc::string GetString( const fc::string& name ) const;
	bool GetBool( const fc::string& name ) const;
	short GetShort( const fc::string& name ) const;
	int GetInt( const fc::string& name ) const;
	size_t GetUInt( const fc::string& name ) const;
	float GetFloat( const fc::string& name ) const;

	bool IsOpen() const { return (m_document != 0); }

private:
	fc::string		m_filename;
	XmlDocument_t*	m_document;
	XmlElement_t*	m_element;

};



CE_NAMESPACE_END

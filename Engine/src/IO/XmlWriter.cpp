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


CE_NAMESPACE_BEGIN

#define XML_WRITER_CHECK()


XmlWriter::XmlWriter() :
	m_filename(),
	m_document(),
	m_element()
{
}


XmlWriter::XmlWriter( const fc::string& filename ) :
	m_filename(),
	m_document(),
	m_element()
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
	m_document.CreateDeclaration();
	//m_element = m_document.CreateRoot();

	return true;
}


bool XmlWriter::Close()
{
	if( !IsOpen() )
		return true;

	return m_document.Save(m_filename);
}


bool XmlWriter::BeginNode( const char* name )
{
	CE_ASSERT(IsOpen());
	if( !m_document.GetRoot() )
	{
		m_element = m_document.CreateRoot(name);
		return m_element;
	}

	return m_element.BeginNode(name);
}


bool XmlWriter::EndNode( const char* )
{
	CE_ASSERT(IsOpen());
	return m_element.SetToParent();
}


bool XmlWriter::WriteBool( const char* name, bool value )
{
	XML_WRITER_CHECK();
	return m_element.SetBool(name, value);
}


bool XmlWriter::WriteByte( const char* name, byte value )
{
	XML_WRITER_CHECK();
	return m_element.SetInt(name, (int)value);
}


bool XmlWriter::WriteShort( const char* name, short value )
{
	XML_WRITER_CHECK();
	return m_element.SetInt(name, (int)value);
}


bool XmlWriter::WriteUShort( const char* name, ushort value )
{
	XML_WRITER_CHECK();
	return m_element.SetInt(name, (int)value);
}


bool XmlWriter::WriteInt( const char* name, int value )
{
	XML_WRITER_CHECK();
	return m_element.SetInt(name, value);
}


bool XmlWriter::WriteUInt( const char* name, size_t value )
{
	XML_WRITER_CHECK();
	return m_element.SetUInt(name, value);
}


bool XmlWriter::WriteFloat( const char* name, float value )
{
	XML_WRITER_CHECK();
	return m_element.SetFloat(name, value);
}


bool XmlWriter::WriteString( const char* name, const fc::string& value )
{
	XML_WRITER_CHECK();
	return m_element.SetString(name, value);
}


bool XmlWriter::WriteRect( const char* name, const Rect& value )
{
	XML_WRITER_CHECK();
	return m_element.SetRect(name, value);
}


bool XmlWriter::WriteRectf( const char* name, const Rectf& value )
{
	XML_WRITER_CHECK();
	return m_element.SetRectf(name, value);
}


bool XmlWriter::WritePoint( const char* name, const Point& value )
{
	XML_WRITER_CHECK();
	return m_element.SetPoint(name, value);
}


bool XmlWriter::WriteVector2( const char* name, const Vector2& value )
{
	XML_WRITER_CHECK();
	return m_element.SetVector2(name, value);
}


bool XmlWriter::WriteVector3( const char* name, const Vector3& value )
{
	XML_WRITER_CHECK();
	return m_element.SetVector3(name, value);
}


bool XmlWriter::WriteVector4( const char* name, const Vector4& value )
{
	XML_WRITER_CHECK();
	return m_element.SetVector4(name, value);
}


bool XmlWriter::WriteColor( const char* name, const Color& value )
{
	XML_WRITER_CHECK();
	return m_element.SetColor(name, value);
}


bool XmlWriter::WriteColorf( const char* name, const Colorf& value )
{
	XML_WRITER_CHECK();
	return m_element.SetColorf(name, value);
}



bool XmlWriter::WriteBoolElement( const char* name, bool value )
{
	XML_WRITER_CHECK();
	return m_element.SetBoolElement(name, value);
}


bool XmlWriter::WriteByteElement( const char* name, byte value )
{
	XML_WRITER_CHECK();
	return m_element.SetByteElement(name, value);
}


bool XmlWriter::WriteShortElement( const char* name, short value )
{
	XML_WRITER_CHECK();
	return m_element.SetShortElement(name, value);
}


bool XmlWriter::WriteUShortElement( const char* name, ushort value )
{
	XML_WRITER_CHECK();
	return m_element.SetIntElement(name, (int)value);
}


bool XmlWriter::WriteIntElement( const char* name, int value )
{
	XML_WRITER_CHECK();
	return m_element.SetIntElement(name, value);
}


bool XmlWriter::WriteUIntElement( const char* name, size_t value )
{
	XML_WRITER_CHECK();
	return m_element.SetUIntElement(name, value);
}


bool XmlWriter::WriteFloatElement( const char* name, float value )
{
	XML_WRITER_CHECK();
	return m_element.SetFloatElement(name, value);
}


bool XmlWriter::WriteStringElement( const char* name, const fc::string& value )
{
	XML_WRITER_CHECK();
	return m_element.SetTextElement(name, value.c_str());
}


bool XmlWriter::WriteRectElement( const char* name, const Rect& value )
{
	XML_WRITER_CHECK();
	return m_element.SetRectElement(name, value);
}


bool XmlWriter::WriteRectfElement( const char* name, const Rectf& value )
{
	XML_WRITER_CHECK();
	return m_element.SetRectfElement(name, value);
}


bool XmlWriter::WritePointElement( const char* name, const Point& value )
{
	XML_WRITER_CHECK();
	return m_element.SetPointElement(name, value);
}


bool XmlWriter::WriteVector2Element( const char* name, const Vector2& value )
{
	XML_WRITER_CHECK();
	return m_element.SetVector2Element(name, value);
}


bool XmlWriter::WriteVector3Element( const char* name, const Vector3& value )
{
	XML_WRITER_CHECK();
	return m_element.SetVector3Element(name, value);
}


bool XmlWriter::WriteVector4Element( const char* name, const Vector4& value )
{
	XML_WRITER_CHECK();
	return m_element.SetVector4Element(name, value);
}


bool XmlWriter::WriteColorElement( const char* name, const Color& value )
{
	XML_WRITER_CHECK();
	return m_element.SetColorElement(name, value);
}


bool XmlWriter::WriteColorfElement( const char* name, const Colorf& value )
{
	XML_WRITER_CHECK();
	return m_element.SetColorfElement(name, value);
}


bool XmlWriter::WriteBoolArray( const char* name, const bool* ptr, size_t n )
{
	XML_WRITER_CHECK();
	return m_element.WriteByteArray(name, (const byte*)ptr, n);
}


bool XmlWriter::WriteByteArray( const char* name, const byte* ptr, size_t n )
{
	XML_WRITER_CHECK();
	return m_element.WriteByteArray(name, ptr, n);
}


bool XmlWriter::WriteShortArray( const char* name, const short* ptr, size_t n )
{
	XML_WRITER_CHECK();
	return m_element.WriteShortArray(name, ptr, n);
}


bool XmlWriter::WriteIntArray( const char* name, const int* ptr, size_t n )
{
	XML_WRITER_CHECK();
	return m_element.WriteIntArray(name, ptr, n);
}


bool XmlWriter::WriteFloatArray( const char* name, const float* ptr, size_t n )
{
	XML_WRITER_CHECK();
	return m_element.WriteFloatArray(name, ptr, n);
}


bool XmlWriter::WriteBoolArrayElement( const char* name, const bool* ptr, size_t n )
{
	XML_WRITER_CHECK();
	return m_element.WriteByteArrayElement(name, (const byte*)ptr, n);
}


bool XmlWriter::WriteByteArrayElement( const char* name, const byte* ptr, size_t n )
{
	XML_WRITER_CHECK();
	return m_element.WriteByteArrayElement(name, ptr, n);
}


bool XmlWriter::WriteShortArrayElement( const char* name, const short* ptr, size_t n )
{
	XML_WRITER_CHECK();
	return m_element.WriteShortArrayElement(name, ptr, n);
}


bool XmlWriter::WriteIntArrayElement( const char* name, const int* ptr, size_t n )
{
	XML_WRITER_CHECK();
	return m_element.WriteIntArrayElement(name, ptr, n);
}


bool XmlWriter::WriteFloatArrayElement( const char* name, const float* ptr, size_t n )
{
	XML_WRITER_CHECK();
	return m_element.WriteFloatArrayElement(name, ptr, n);
}



CE_NAMESPACE_END



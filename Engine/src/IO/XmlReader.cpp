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

#define XML_READER_CHECK()

CE_NAMESPACE_BEGIN


XmlReader::XmlReader() :
	m_filename(),
	m_document(),
	m_element()
{
}


XmlReader::XmlReader( const fc::string& filename ) :
	m_filename(),
	m_document(),
	m_element()
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
	if( !m_document.Load(m_filename) )
		return false;

	m_element = m_document.GetRoot();
	return true;
}


void XmlReader::Close()
{
	m_filename.clear();
	m_document.Reset();
	m_element = XmlElement();
}


fc::string XmlReader::GetCurrentNodeName() const
{
	CE_ASSERT(m_element);
	return fc::string(m_element.GetCurrentNodeName());
}


bool XmlReader::SetToParent()
{
	return m_element.SetToParent();
}


bool XmlReader::SetToChild( const char* name )
{
	return m_element.SetToChild(name);
}


bool XmlReader::HasAttribute( const char* name ) const
{
	CE_ASSERT(m_element);
	return m_element.HasAttribute(name);
}


fc::string XmlReader::ReadString( const char* name, const fc::string& ) const
{
	XML_READER_CHECK();
	return m_element.GetString(name); //fixme
}


bool XmlReader::ReadBool( const char* name, bool defaultValue ) const
{
	XML_READER_CHECK();
	return m_element.GetBool(name, defaultValue);
}


byte XmlReader::ReadByte( const char* name, byte defaultValue ) const
{
	XML_READER_CHECK();
	return m_element.GetByte(name, defaultValue);
}


short XmlReader::ReadShort( const char* name, short defaultValue ) const
{
	XML_READER_CHECK();
	return m_element.GetShort(name, defaultValue);
}


int XmlReader::ReadInt( const char* name, int defaultValue ) const
{
	XML_READER_CHECK();
	return m_element.GetInt(name, defaultValue);
}


size_t XmlReader::ReadUInt( const char* name, size_t defaultValue ) const
{
	XML_READER_CHECK();
	return m_element.GetUInt(name, defaultValue);
}


float XmlReader::ReadFloat( const char* name, float defaultValue ) const
{
	XML_READER_CHECK();
	return m_element.GetFloat(name, defaultValue);
}


Rect XmlReader::ReadRect( const char* name, const Rect& defaultValue ) const
{
	XML_READER_CHECK();
	return m_element.GetRect(name, defaultValue);
}


Rectf XmlReader::ReadRectf( const char* name, const Rectf& defaultValue ) const
{
	XML_READER_CHECK();
	return m_element.GetRectf(name, defaultValue);
}


Point XmlReader::ReadPoint( const char* name, const Point& defaultValue ) const
{
	XML_READER_CHECK();
	return m_element.GetPoint(name, defaultValue);
}


Vector2 XmlReader::ReadVector2( const char* name, const Vector2& defaultValue ) const
{
	XML_READER_CHECK();
	return m_element.GetVector2(name, defaultValue);
}


Vector3 XmlReader::ReadVector3( const char* name, const Vector3& defaultValue ) const
{
	XML_READER_CHECK();
	return m_element.GetVector3(name, defaultValue);
}


Vector4 XmlReader::ReadVector4( const char* name, const Vector4& defaultValue ) const
{
	XML_READER_CHECK();
	return m_element.GetVector4(name, defaultValue);
}


Color XmlReader::ReadColor( const char* name, const Color& defaultValue ) const
{
	XML_READER_CHECK();
	return m_element.GetColor(name, defaultValue);
}


Colorf XmlReader::ReadColorf( const char* name, const Colorf& defaultValue ) const
{
	XML_READER_CHECK();
	return m_element.GetColorf(name, defaultValue);
}


fc::string XmlReader::ReadStringElement( const char* name, const fc::string& ) const
{
	XML_READER_CHECK();
	return m_element.GetTextElement(name); //fixme
}


bool XmlReader::ReadBoolElement( const char* name, bool defaultValue ) const
{
	XML_READER_CHECK();
	return m_element.GetBoolElement(name, defaultValue);
}


byte XmlReader::ReadByteElement( const char* name, byte defaultValue ) const
{
	XML_READER_CHECK();
	return m_element.GetByteElement(name, defaultValue);
}


short XmlReader::ReadShortElement( const char* name, short defaultValue ) const
{
	XML_READER_CHECK();
	return m_element.GetShortElement(name, defaultValue);
}


int XmlReader::ReadIntElement( const char* name, int defaultValue ) const
{
	XML_READER_CHECK();
	return m_element.GetIntElement(name, defaultValue);
}


size_t XmlReader::ReadUIntElement( const char* name, size_t defaultValue ) const
{
	XML_READER_CHECK();
	return m_element.GetUIntElement(name, defaultValue);
}


float XmlReader::ReadFloatElement( const char* name, float defaultValue ) const
{
	XML_READER_CHECK();
	return m_element.GetFloatElement(name, defaultValue);
}


Rect XmlReader::ReadRectElement( const char* name, const Rect& defaultValue ) const
{
	XML_READER_CHECK();
	return m_element.GetRectElement(name, defaultValue);
}


Rectf XmlReader::ReadRectfElement( const char* name, const Rectf& defaultValue ) const
{
	XML_READER_CHECK();
	return m_element.GetRectfElement(name, defaultValue);
}


Point XmlReader::ReadPointElement( const char* name, const Point& defaultValue ) const
{
	XML_READER_CHECK();
	return m_element.GetPointElement(name, defaultValue);
}


Vector2 XmlReader::ReadVector2Element( const char* name, const Vector2& defaultValue ) const
{
	XML_READER_CHECK();
	return m_element.GetVector2Element(name, defaultValue);
}


Vector3 XmlReader::ReadVector3Element( const char* name, const Vector3& defaultValue ) const
{
	XML_READER_CHECK();
	return m_element.GetVector3Element(name, defaultValue);
}


Vector4 XmlReader::ReadVector4Element( const char* name, const Vector4& defaultValue ) const
{
	XML_READER_CHECK();
	return m_element.GetVector4Element(name, defaultValue);
}


Color XmlReader::ReadColorElement( const char* name, const Color& defaultValue ) const
{
	XML_READER_CHECK();
	return m_element.GetColorElement(name, defaultValue);
}


Colorf XmlReader::ReadColorfElement( const char* name, const Colorf& defaultValue ) const
{
	XML_READER_CHECK();
	return m_element.GetColorfElement(name, defaultValue);
}


bool XmlReader::ReadBoolArray( const char* name, bool* ptr, size_t n ) const
{
	XML_READER_CHECK();
	return m_element.ReadByteArray(name, (byte*)ptr, n);
}


bool XmlReader::ReadByteArray( const char* name, byte* ptr, size_t n ) const
{
	XML_READER_CHECK();
	return m_element.ReadByteArray(name, ptr, n);
}


bool XmlReader::ReadShortArray( const char* name, short* ptr, size_t n ) const
{
	XML_READER_CHECK();
	return m_element.ReadShortArray(name, ptr, n);
}


bool XmlReader::ReadIntArray( const char* name, int* ptr, size_t n ) const
{
	XML_READER_CHECK();
	return m_element.ReadIntArray(name, ptr, n);
}


bool XmlReader::ReadUIntArray( const char* name, size_t* ptr, size_t n ) const
{
	XML_READER_CHECK();
	return m_element.ReadIntArray(name, (int*)ptr, n);
}


bool XmlReader::ReadFloatArray( const char* name, float* ptr, size_t n ) const
{
	XML_READER_CHECK();
	return m_element.ReadFloatArray(name, ptr, n);
}


bool XmlReader::ReadBoolArrayElement( const char* name, bool* ptr, size_t n ) const
{
	XML_READER_CHECK();
	return m_element.ReadByteArrayElement(name, (byte*)ptr, n);
}


bool XmlReader::ReadByteArrayElement( const char* name, byte* ptr, size_t n ) const
{
	XML_READER_CHECK();
	return m_element.ReadByteArrayElement(name, ptr, n);
}


bool XmlReader::ReadShortArrayElement( const char* name, short* ptr, size_t n ) const
{
	XML_READER_CHECK();
	return m_element.ReadShortArrayElement(name, ptr, n);
}


bool XmlReader::ReadIntArrayElement( const char* name, int* ptr, size_t n ) const
{
	XML_READER_CHECK();
	return m_element.ReadIntArrayElement(name, ptr, n);
}


bool XmlReader::ReadUIntArrayElement( const char* name, size_t* ptr, size_t n ) const
{
	XML_READER_CHECK();
	return m_element.ReadIntArrayElement(name, (int*)ptr, n);
}


bool XmlReader::ReadFloatArrayElement( const char* name, float* ptr, size_t n ) const
{
	XML_READER_CHECK();
	return m_element.ReadFloatArrayElement(name, ptr, n);
}




CE_NAMESPACE_END

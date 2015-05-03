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

#include "Catastrophe/Core/Common.h"
#include "Catastrophe/Core/Containers/StaticString.h"
#include "Catastrophe/Core/IO/XmlReader.h"

#include "Catastrophe/Core/Math/Point.h"
#include "Catastrophe/Core/Math/Rect.h"
#include "Catastrophe/Core/Math/Rectf.h"
#include "Catastrophe/Core/Math/Vector2.h"
#include "Catastrophe/Core/Math/Vector3.h"
#include "Catastrophe/Core/Math/Vector4.h"
#include "Catastrophe/Core/Math/Color.h"
#include "Catastrophe/Core/Math/Colorf.h"
#include "Catastrophe/Core/Math/Matrix.h"

#define XML_READER_CHECK()

CE_NAMESPACE_BEGIN


XmlReader::XmlReader() :
	m_filename(),
	m_document(),
	m_element()
{
}


XmlReader::XmlReader( const String& filename ) :
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


bool XmlReader::Open( const String& filename )
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
	m_filename.Clear();
	m_document.Reset();
	m_element = XmlElement();
}


String XmlReader::GetCurrentNodeName() const
{
	return m_element.GetCurrentNodeName();
}


const char* XmlReader::GetCurrentNodeNameCStr() const
{
	return m_element.GetCurrentNodeNameCStr();
}


bool XmlReader::SetToParent()
{
	return m_element.SetToParent();
}


bool XmlReader::SetToChild( const char* name )
{
	return m_element.SetToChild(name);
}


bool XmlReader::FirstChild( const char* name )
{
	return m_element.SetToChild(name); //fixme
}


bool XmlReader::NextChild( const char* name )
{
	// FIXME: !!!
	XmlElement element = m_element.FirstChild(name);
	if( element == null )
		// Try and get the sibling... (intended?)
		element = m_element.NextSibling(name);

	if( element != null )
		m_element = element;

	return element;
	//return m_element.SetToChild(name);
}


bool XmlReader::HasAttribute( const char* name ) const
{
	CE_ASSERT(m_element);
	return m_element.HasAttribute(name);
}


const char* XmlReader::GetString( const char* name, const char* defaultValue ) const
{
	XML_READER_CHECK();
	return m_element.GetString(name, defaultValue);
}


bool XmlReader::GetString( const char* name, String& value ) const
{
	XML_READER_CHECK();
	const char* str = m_element.GetString(name);
	if( str != null )
		value = str;

	return (str != null);
}


bool XmlReader::GetString( const char* name, StaticString<32>& value ) const
{
	const char* str = GetString(name);
	if( str != null )
		value = str;

	return str != null;
}


bool XmlReader::GetAttribute( const char* name, bool& value ) const
{
	XML_READER_CHECK();
	return m_element.GetAttribute(name, value);
}


bool XmlReader::GetAttribute( const char* name, u8& value ) const
{
	XML_READER_CHECK();
	return m_element.GetAttribute(name, value);
}


bool XmlReader::GetAttribute( const char* name, s16& value ) const
{
	XML_READER_CHECK();
	return m_element.GetAttribute(name, value);
}


bool XmlReader::GetAttribute( const char* name, u16& value ) const
{
	XML_READER_CHECK();
	return m_element.GetAttribute(name, value);
}


bool XmlReader::GetAttribute( const char* name, int& value ) const
{
	XML_READER_CHECK();
	return m_element.GetAttribute(name, value);
}


bool XmlReader::GetAttribute( const char* name, u32& value ) const
{
	XML_READER_CHECK();
	return m_element.GetAttribute(name, value);
}


bool XmlReader::GetAttribute( const char* name, float& value ) const
{
	XML_READER_CHECK();
	return m_element.GetAttribute(name, value);
}


bool XmlReader::GetAttribute( const char* name, Rect& value ) const
{
	XML_READER_CHECK();
	return m_element.GetAttribute(name, value);
}


bool XmlReader::GetAttribute( const char* name, Rectf& value ) const
{
	XML_READER_CHECK();
	return m_element.GetAttribute(name, value);
}


bool XmlReader::GetAttribute( const char* name, Point& value ) const
{
	XML_READER_CHECK();
	return m_element.GetAttribute(name, value);
}


bool XmlReader::GetAttribute( const char* name, Vector2& value ) const
{
	XML_READER_CHECK();
	return m_element.GetAttribute(name, value);
}


bool XmlReader::GetAttribute( const char* name, Vector3& value ) const
{
	XML_READER_CHECK();
	return m_element.GetAttribute(name, value);
}


bool XmlReader::GetAttribute( const char* name, Vector4& value ) const
{
	XML_READER_CHECK();
	return m_element.GetAttribute(name, value);
}


bool XmlReader::GetAttribute( const char* name, Color& value ) const
{
	XML_READER_CHECK();
	return m_element.GetAttribute(name, value);
}


bool XmlReader::GetAttribute( const char* name, Colorf& value ) const
{
	XML_READER_CHECK();
	return m_element.GetAttribute(name, value);
}


bool XmlReader::GetStringElement( const char* name, String& value ) const
{
	XML_READER_CHECK();
	const char* str = m_element.GetTextElement(name);
	if( str != null )
		value = str;

	return (str != null);
}


bool XmlReader::GetBoolElement( const char* name, bool& value ) const
{
	XML_READER_CHECK();
	return m_element.GetBoolElement(name, value);
}


bool XmlReader::GetByteElement( const char* name, u8& value ) const
{
	XML_READER_CHECK();
	return m_element.GetByteElement(name, value);
}


bool XmlReader::GetShortElement( const char* name, s16& value ) const
{
	XML_READER_CHECK();
	return m_element.GetShortElement(name, value);
}


bool XmlReader::GetIntElement( const char* name, int& value ) const
{
	XML_READER_CHECK();
	return m_element.GetIntElement(name, value);
}


bool XmlReader::GetUIntElement( const char* name, u32& value ) const
{
	XML_READER_CHECK();
	return m_element.GetUIntElement(name, value);
}


bool XmlReader::GetFloatElement( const char* name, float& value ) const
{
	XML_READER_CHECK();
	return m_element.GetFloatElement(name, value);
}


bool XmlReader::GetRectElement( const char* name, Rect& value ) const
{
	XML_READER_CHECK();
	return m_element.GetRectElement(name, value);
}


bool XmlReader::GetRectfElement( const char* name, Rectf& value ) const
{
	XML_READER_CHECK();
	return m_element.GetRectfElement(name, value);
}


bool XmlReader::GetPointElement( const char* name, Point& value ) const
{
	XML_READER_CHECK();
	return m_element.GetPointElement(name, value);
}


bool XmlReader::GetVector2Element( const char* name, Vector2& value ) const
{
	XML_READER_CHECK();
	return m_element.GetVector2Element(name, value);
}


bool XmlReader::GetVector3Element( const char* name, Vector3& value ) const
{
	XML_READER_CHECK();
	return m_element.GetVector3Element(name, value);
}


bool XmlReader::GetVector4Element( const char* name, Vector4& value ) const
{
	XML_READER_CHECK();
	return m_element.GetVector4Element(name, value);
}


bool XmlReader::GetColorElement( const char* name, Color& value ) const
{
	XML_READER_CHECK();
	return m_element.GetColorElement(name, value);
}


bool XmlReader::GetColorfElement( const char* name, Colorf& value ) const
{
	XML_READER_CHECK();
	return m_element.GetColorfElement(name, value);
}


bool XmlReader::ReadBoolArray( const char* name, bool* ptr, u32 n ) const
{
	XML_READER_CHECK();
	return m_element.ReadByteArray(name, (u8*)ptr, n);
}


bool XmlReader::ReadByteArray( const char* name, u8* ptr, u32 n ) const
{
	XML_READER_CHECK();
	return m_element.ReadByteArray(name, ptr, n);
}


bool XmlReader::ReadShortArray( const char* name, s16* ptr, u32 n ) const
{
	XML_READER_CHECK();
	return m_element.ReadShortArray(name, ptr, n);
}


bool XmlReader::ReadIntArray( const char* name, int* ptr, u32 n ) const
{
	XML_READER_CHECK();
	return m_element.ReadIntArray(name, ptr, n);
}


bool XmlReader::ReadUIntArray( const char* name, u32* ptr, u32 n ) const
{
	XML_READER_CHECK();
	return m_element.ReadIntArray(name, (int*)ptr, n);
}


bool XmlReader::ReadFloatArray( const char* name, float* ptr, u32 n ) const
{
	XML_READER_CHECK();
	return m_element.ReadFloatArray(name, ptr, n);
}


bool XmlReader::ReadBoolArrayElement( const char* name, bool* ptr, u32 n ) const
{
	XML_READER_CHECK();
	return m_element.ReadByteArrayElement(name, (u8*)ptr, n);
}


bool XmlReader::ReadByteArrayElement( const char* name, u8* ptr, u32 n ) const
{
	XML_READER_CHECK();
	return m_element.ReadByteArrayElement(name, ptr, n);
}


bool XmlReader::ReadShortArrayElement( const char* name, s16* ptr, u32 n ) const
{
	XML_READER_CHECK();
	return m_element.ReadShortArrayElement(name, ptr, n);
}


bool XmlReader::ReadIntArrayElement( const char* name, int* ptr, u32 n ) const
{
	XML_READER_CHECK();
	return m_element.ReadIntArrayElement(name, ptr, n);
}


bool XmlReader::ReadUIntArrayElement( const char* name, u32* ptr, u32 n ) const
{
	XML_READER_CHECK();
	return m_element.ReadIntArrayElement(name, (int*)ptr, n);
}


bool XmlReader::ReadFloatArrayElement( const char* name, float* ptr, u32 n ) const
{
	XML_READER_CHECK();
	return m_element.ReadFloatArrayElement(name, ptr, n);
}




CE_NAMESPACE_END

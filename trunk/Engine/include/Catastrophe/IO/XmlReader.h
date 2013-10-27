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


class CE_API XmlReader
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
	virtual bool IsOpen() const { return (m_document != 0); }

	fc::string GetCurrentNodeName() const;

	bool FirstChild( const fc::string& name = "" );
	bool NextChild( const fc::string& name = "" );
	bool SetToParent();
	bool HasAttribute( const fc::string& attr ) const;

	fc::string ReadText() const;
	bool ReadByteArray( ubyte* ptr, size_t n );
	bool ReadShortArray( short* ptr, size_t n );
	bool ReadIntArray( int* ptr, size_t n );
	bool ReadFloatArray( float* ptr, size_t n );
	bool ReadArray( void* ptr, size_t strideInBytes, size_t n, bool isIntegral = true );

	bool ReadString( const char* name, fc::string& value ) const;
	bool ReadBool( const char* name, bool& value ) const;
	bool ReadByte( const char* name, byte& value ) const;
	bool ReadShort( const char* name, short& value ) const;
	bool ReadInt( const char* name, int& value ) const;
	bool ReadUInt( const char* name, size_t& value ) const;
	bool ReadFloat( const char* name, float& value ) const;

	bool GetStringElement( const char* name, fc::string& value );
	bool GetBoolElement( const char* name, bool& value );
	bool GetByteElement( const char* name, char& value );
	bool GetShortElement( const char* name, short& value );
	bool GetIntElement( const char* name, int& value );
	bool GetUIntElement( const char* name, size_t& value );
	bool GetFloatElement( const char* name, float& value );
	bool GetRectElement( const char* name, Rect& value );
	bool GetRectfElement( const char* name, Rectf& value );
	bool GetPointElement( const char* name, Point& value );
	bool GetVector2Element( const char* name, Vector2& value );
	bool GetVector3Element( const char* name, Vector3& value );
	bool GetVector4Element( const char* name, Vector4& value );
	bool GetColorElement( const char* name, Color& value );
	bool GetColorfElement( const char* name, Colorf& value );
	bool GetMatrixElement( const char* name, Matrix& value );

	CE_NO_INLINE bool GetTypeElement( const char* name, void* value, int type );

	fc::string GetString( const char* name ) const;
	bool GetBool( const char* name, bool defaultValue = false ) const;
	byte GetByte( const char* name, byte defaultValue = 0 ) const;
	short GetShort( const char* name, short defaultValue = 0 ) const;
	int GetInt( const char* name, int defaultValue = 0 ) const;
	size_t GetUInt( const char* name, size_t defaultValue = 0 ) const;
	float GetFloat( const char* name, float defaultValue = 0.f ) const;

private:
	fc::string		m_filename;
	XmlDocument_t*	m_document;
	XmlElement_t*	m_element;

};



CE_NAMESPACE_END

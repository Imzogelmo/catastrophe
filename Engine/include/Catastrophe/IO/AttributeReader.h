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

#include "../Common.h"
#include "../Math/Point.h"
#include "../Math/Rect.h"
#include "../Math/Rectf.h"
#include "../Math/Vector2.h"
#include "../Math/Vector3.h"
#include "../Math/Vector4.h"
#include "../Math/Color.h"
#include "../Math/Colorf.h"

CE_NAMESPACE_BEGIN


class CE_API AtributeDeserializer
{
public:
	AtributeDeserializer() {}
	virtual ~AtributeDeserializer() {}
	virtual bool IsOpen() const = 0;

	virtual bool PushNode( const fc::string& name ) { return PushNode(name.c_str()); }
	virtual bool PopNode( const fc::string& name ) { return PopNode(name.c_str()); }
	virtual bool PushNode( const char* name ) = 0;
	virtual bool PopNode( const char* name ) = 0;

	virtual fc::string ReadString( const char* name, const fc::string& defaultValue = "" ) const = 0;
	virtual bool ReadBool( const char* name, bool defaultValue = false ) const = 0;
	virtual byte ReadByte( const char* name, byte defaultValue = 0 ) const = 0;
	virtual short ReadShort( const char* name, short defaultValue = 0 ) const = 0;
	virtual int ReadInt( const char* name, int defaultValue = 0 ) const = 0;
	virtual size_t ReadUInt( const char* name, size_t defaultValue = 0 ) const = 0;
	virtual float ReadFloat( const char* name, float defaultValue = 0.f ) const = 0;
	virtual Rect ReadRect( const char* name, const Rect& defaultValue = Rect::Zero ) const = 0;
	virtual Rectf ReadRectf( const char* name, const Rectf& defaultValue = Rectf::Zero ) const = 0;
	virtual Point ReadPoint( const char* name, const Point& defaultValue = Point::Zero ) const = 0;
	virtual Vector2 ReadVector2( const char* name, const Vector2& defaultValue = Vector2::Zero ) const = 0;
	virtual Vector3 ReadVector3( const char* name, const Vector3& defaultValue = Vector3::Zero ) const = 0;
	virtual Vector4 ReadVector4( const char* name, const Vector4& defaultValue = Vector4::Zero ) const = 0;
	virtual Color ReadColor( const char* name, const Color& defaultValue = Color::White() ) const = 0;
	virtual Colorf ReadColorf( const char* name, const Colorf& defaultValue = Colorf() ) const = 0;

	virtual bool ReadBoolElement( const char* name, bool defaultValue = false ) const = 0;
	virtual byte ReadByteElement( const char* name, byte defaultValue = 0 ) const = 0;
	virtual short ReadShortElement( const char* name, short defaultValue = 0 ) const = 0;
	virtual int ReadIntElement( const char* name, int defaultValue = 0 ) const = 0;
	virtual size_t ReadUIntElement( const char* name, size_t defaultValue = 0 ) const = 0;
	virtual float ReadFloatElement( const char* name, float defaultValue = 0.f ) const = 0;
	virtual Rect ReadRectElement( const char* name, const Rect& defaultValue = Rect::Zero ) const = 0;
	virtual Rectf ReadRectfElement( const char* name, const Rectf& defaultValue = Rectf::Zero ) const = 0;
	virtual Point ReadPointElement( const char* name, const Point& defaultValue = Point::Zero ) const = 0;
	virtual Vector2 ReadVector2Element( const char* name, const Vector2& defaultValue = Vector2::Zero ) const = 0;
	virtual Vector3 ReadVector3Element( const char* name, const Vector3& defaultValue = Vector3::Zero ) const = 0;
	virtual Vector4 ReadVector4Element( const char* name, const Vector4& defaultValue = Vector4::Zero ) const = 0;
	virtual Color ReadColorElement( const char* name, const Color& defaultValue = Color::White() ) const = 0;
	virtual Colorf ReadColorfElement( const char* name, const Colorf& defaultValue = Colorf() ) const = 0;

	virtual bool ReadBoolArray( const char* name, bool* ptr, size_t n ) const = 0;
	virtual bool ReadByteArray( const char* name, byte* ptr, size_t n ) const = 0;
	virtual bool ReadShortArray( const char* name, short* ptr, size_t n ) const = 0;
	virtual bool ReadIntArray( const char* name, int* ptr, size_t n ) const = 0;
	virtual bool ReadUIntArray( const char* name, size_t* ptr, size_t n ) const = 0;
	virtual bool ReadFloatArray( const char* name, float* ptr, size_t n ) const = 0;

	virtual bool ReadBoolArrayElement( const char* name, bool* ptr, size_t n ) const = 0;
	virtual bool ReadByteArrayElement( const char* name, byte* ptr, size_t n ) const = 0;
	virtual bool ReadShortArrayElement( const char* name, short* ptr, size_t n ) const = 0;
	virtual bool ReadIntArrayElement( const char* name, int* ptr, size_t n ) const = 0;
	virtual bool ReadUIntArrayElement( const char* name, size_t* ptr, size_t n ) const = 0;
	virtual bool ReadFloatArrayElement( const char* name, float* ptr, size_t n ) const = 0;

};



CE_NAMESPACE_END

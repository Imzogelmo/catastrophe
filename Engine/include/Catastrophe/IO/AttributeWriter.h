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

CE_NAMESPACE_BEGIN


class CE_API AttributeWriter
{
public:
	AttributeWriter() {}
	virtual ~AttributeWriter() {}
	virtual bool IsOpen() const = 0;

	virtual bool PushNode( const fc::string& name ) { return PushNode(name.c_str()); }
	virtual bool PopNode( const fc::string& name ) { return PopNode(name.c_str()); }
	virtual bool PushNode( const char* name ) = 0;
	virtual bool PopNode( const char* name = "" ) = 0;

	virtual bool WriteBool( const char* name, bool value ) = 0;
	virtual bool WriteByte( const char* name, byte value ) = 0;
	virtual bool WriteShort( const char* name, short value ) = 0;
	virtual bool WriteUShort( const char* name, ushort value ) = 0;
	virtual bool WriteInt( const char* name, int value ) = 0;
	virtual bool WriteUInt( const char* name, size_t value ) = 0;
	virtual bool WriteFloat( const char* name, float value ) = 0;
	virtual bool WriteString( const char* name, const fc::string& value ) = 0;
	virtual bool WriteRect( const char* name, const Rect& value ) = 0;
	virtual bool WriteRectf( const char* name, const Rectf& value ) = 0;
	virtual bool WritePoint( const char* name, const Point& value ) = 0;
	virtual bool WriteVector2( const char* name, const Vector2& value ) = 0;
	virtual bool WriteVector3( const char* name, const Vector3& value ) = 0;
	virtual bool WriteVector4( const char* name, const Vector4& value ) = 0;
	virtual bool WriteColor( const char* name, const Color& value ) = 0;
	virtual bool WriteColorf( const char* name, const Colorf& value ) = 0;

	virtual bool WriteBoolElement( const char* name, bool value ) = 0;
	virtual bool WriteByteElement( const char* name, byte value ) = 0;
	virtual bool WriteShortElement( const char* name, short value ) = 0;
	virtual bool WriteUShortElement( const char* name, ushort value ) = 0;
	virtual bool WriteIntElement( const char* name, int value ) = 0;
	virtual bool WriteUIntElement( const char* name, size_t value ) = 0;
	virtual bool WriteFloatElement( const char* name, float value ) = 0;
	virtual bool WriteStringElement( const char* name, const fc::string& value ) = 0;
	virtual bool WriteRectElement( const char* name, const Rect& value ) = 0;
	virtual bool WriteRectfElement( const char* name, const Rectf& value ) = 0;
	virtual bool WritePointElement( const char* name, const Point& value ) = 0;
	virtual bool WriteVector2Element( const char* name, const Vector2& value ) = 0;
	virtual bool WriteVector3Element( const char* name, const Vector3& value ) = 0;
	virtual bool WriteVector4Element( const char* name, const Vector4& value ) = 0;
	virtual bool WriteColorElement( const char* name, const Color& value ) = 0;
	virtual bool WriteColorfElement( const char* name, const Colorf& value ) = 0;

	virtual bool WriteBoolArray( const char* name, const bool* ptr, size_t n ) = 0;
	virtual bool WriteByteArray( const char* name, const byte* ptr, size_t n ) = 0;
	virtual bool WriteShortArray( const char* name, const short* ptr, size_t n ) = 0;
	virtual bool WriteIntArray( const char* name, const int* ptr, size_t n ) = 0;
	virtual bool WriteFloatArray( const char* name, const float* ptr, size_t n ) = 0;

	virtual bool WriteBoolArrayElement( const char* name, const bool* ptr, size_t n ) = 0;
	virtual bool WriteByteArrayElement( const char* name, const byte* ptr, size_t n ) = 0;
	virtual bool WriteShortArrayElement( const char* name, const short* ptr, size_t n ) = 0;
	virtual bool WriteIntArrayElement( const char* name, const int* ptr, size_t n ) = 0;
	virtual bool WriteFloatArrayElement( const char* name, const float* ptr, size_t n ) = 0;

};



CE_NAMESPACE_END

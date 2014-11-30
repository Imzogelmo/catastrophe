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


class CE_API AttributeReader
{
public:
	AttributeReader() {}
	virtual ~AttributeReader() {}
	virtual bool IsOpen() const = 0;

	virtual bool FirstChild( const char* name = "" ) = 0;
	virtual bool NextChild( const char* name = "" ) = 0;
	virtual bool SetToParent() = 0;
	virtual bool SetToChild( const char* name ) = 0;

	virtual bool PopNode() { return SetToParent(); }
	virtual bool PushNode( const char* name ) { return NextChild(name); }

	virtual String GetCurrentNodeName() const = 0;
	virtual const char* GetCurrentNodeNameCStr() const = 0;

	virtual const char* GetString( const char* name, const char* defaultValue = 0 ) const = 0;
	virtual String GetString( const char* name, const String& defaultValue ) const = 0;
	virtual bool GetBool( const char* name, bool defaultValue = false ) const = 0;
	virtual u8 GetByte( const char* name, u8 defaultValue = 0 ) const = 0;
	virtual s16 GetShort( const char* name, s16 defaultValue = 0 ) const = 0;
	virtual u16 GetUShort( const char* name, u16 defaultValue = 0 ) const;
	virtual int GetInt( const char* name, int defaultValue = 0 ) const = 0;
	virtual u32 GetUInt( const char* name, u32 defaultValue = 0 ) const = 0;
	virtual float GetFloat( const char* name, float defaultValue = 0.f ) const = 0;
	virtual Rect GetRect( const char* name, const Rect& defaultValue = Rect::Zero ) const = 0;
	virtual Rectf GetRectf( const char* name, const Rectf& defaultValue = Rectf::Zero ) const = 0;
	virtual Point GetPoint( const char* name, const Point& defaultValue = Point::Zero ) const = 0;
	virtual Vector2 GetVector2( const char* name, const Vector2& defaultValue = Vector2::Zero ) const = 0;
	virtual Vector3 GetVector3( const char* name, const Vector3& defaultValue = Vector3::Zero ) const = 0;
	virtual Vector4 GetVector4( const char* name, const Vector4& defaultValue = Vector4::Zero ) const = 0;
	virtual Color GetColor( const char* name, const Color& defaultValue = Color::White() ) const = 0;
	virtual Colorf GetColorf( const char* name, const Colorf& defaultValue = Colorf() ) const = 0;

	virtual bool GetBoolElement( const char* name, bool defaultValue = false ) const = 0;
	virtual u8 GetByteElement( const char* name, u8 defaultValue = 0 ) const = 0;
	virtual s16 GetShortElement( const char* name, s16 defaultValue = 0 ) const = 0;
	virtual int GetIntElement( const char* name, int defaultValue = 0 ) const = 0;
	virtual u32 GetUIntElement( const char* name, u32 defaultValue = 0 ) const = 0;
	virtual float GetFloatElement( const char* name, float defaultValue = 0.f ) const = 0;
	virtual Rect GetRectElement( const char* name, const Rect& defaultValue = Rect::Zero ) const = 0;
	virtual Rectf GetRectfElement( const char* name, const Rectf& defaultValue = Rectf::Zero ) const = 0;
	virtual Point GetPointElement( const char* name, const Point& defaultValue = Point::Zero ) const = 0;
	virtual Vector2 GetVector2Element( const char* name, const Vector2& defaultValue = Vector2::Zero ) const = 0;
	virtual Vector3 GetVector3Element( const char* name, const Vector3& defaultValue = Vector3::Zero ) const = 0;
	virtual Vector4 GetVector4Element( const char* name, const Vector4& defaultValue = Vector4::Zero ) const = 0;
	virtual Color GetColorElement( const char* name, const Color& defaultValue = Color::White() ) const = 0;
	virtual Colorf GetColorfElement( const char* name, const Colorf& defaultValue = Colorf() ) const = 0;

	virtual bool ReadBoolArray( const char* name, bool* ptr, u32 n ) const = 0;
	virtual bool ReadByteArray( const char* name, u8* ptr, u32 n ) const = 0;
	virtual bool ReadShortArray( const char* name, s16* ptr, u32 n ) const = 0;
	virtual bool ReadIntArray( const char* name, int* ptr, u32 n ) const = 0;
	virtual bool ReadUIntArray( const char* name, u32* ptr, u32 n ) const = 0;
	virtual bool ReadFloatArray( const char* name, float* ptr, u32 n ) const = 0;

	virtual bool ReadBoolArrayElement( const char* name, bool* ptr, u32 n ) const = 0;
	virtual bool ReadByteArrayElement( const char* name, u8* ptr, u32 n ) const = 0;
	virtual bool ReadShortArrayElement( const char* name, s16* ptr, u32 n ) const = 0;
	virtual bool ReadIntArrayElement( const char* name, int* ptr, u32 n ) const = 0;
	virtual bool ReadUIntArrayElement( const char* name, u32* ptr, u32 n ) const = 0;
	virtual bool ReadFloatArrayElement( const char* name, float* ptr, u32 n ) const = 0;

};



CE_NAMESPACE_END

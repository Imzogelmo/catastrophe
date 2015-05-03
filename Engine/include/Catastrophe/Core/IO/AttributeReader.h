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

#include "Catastrophe/Core/Common.h"
#include "Catastrophe/Core/Math/Point.h"
#include "Catastrophe/Core/Math/Rect.h"
#include "Catastrophe/Core/Math/Rectf.h"
#include "Catastrophe/Core/Math/Vector2.h"
#include "Catastrophe/Core/Math/Vector3.h"
#include "Catastrophe/Core/Math/Vector4.h"
#include "Catastrophe/Core/Math/Color.h"
#include "Catastrophe/Core/Math/Colorf.h"

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
	virtual bool GetString( const char* name, String& value ) const = 0;
	virtual bool GetString( const char* name, StaticString<32>& value ) const = 0;

	virtual bool GetAttribute( const char* name, bool& value ) const = 0;
	virtual bool GetAttribute( const char* name, u8& value ) const = 0;
	virtual bool GetAttribute( const char* name, s16& value ) const = 0;
	virtual bool GetAttribute( const char* name, u16& value ) const = 0;
	virtual bool GetAttribute( const char* name, int& value ) const = 0;
	virtual bool GetAttribute( const char* name, u32& value) const = 0;
	virtual bool GetAttribute( const char* name, float& value ) const = 0;
	virtual bool GetAttribute( const char* name, Rect& value ) const = 0;
	virtual bool GetAttribute( const char* name, Rectf& value ) const = 0;
	virtual bool GetAttribute( const char* name, Point& value ) const = 0;
	virtual bool GetAttribute( const char* name, Vector2& value ) const = 0;
	virtual bool GetAttribute( const char* name, Vector3& value ) const = 0;
	virtual bool GetAttribute( const char* name, Vector4& value ) const = 0;
	virtual bool GetAttribute( const char* name, Color& value ) const = 0;
	virtual bool GetAttribute( const char* name, Colorf& value ) const = 0;

	virtual bool GetBoolElement( const char* name, bool& value ) const = 0;
	virtual bool GetByteElement( const char* name, u8& value ) const = 0;
	virtual bool GetShortElement( const char* name, s16& value ) const = 0;
	virtual bool GetIntElement( const char* name, int& value ) const = 0;
	virtual bool GetUIntElement( const char* name, u32& value ) const = 0;
	virtual bool GetFloatElement( const char* name, float& value ) const = 0;
	virtual bool GetRectElement( const char* name, Rect& value ) const = 0;
	virtual bool GetRectfElement( const char* name, Rectf& value ) const = 0;
	virtual bool GetPointElement( const char* name, Point& value ) const = 0;
	virtual bool GetVector2Element( const char* name, Vector2& value ) const = 0;
	virtual bool GetVector3Element( const char* name, Vector3& value ) const = 0;
	virtual bool GetVector4Element( const char* name, Vector4& value ) const = 0;
	virtual bool GetColorElement( const char* name, Color& value ) const = 0;
	virtual bool GetColorfElement( const char* name, Colorf& value ) const = 0;

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

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

#pragma once

#include "Catastrophe/Core/Common.h"
#include "Catastrophe/Core/PlatformString.h"
#include "Catastrophe/Core/Containers/String.h"
#include "Catastrophe/Core/Math/Point.h"
#include "Catastrophe/Core/Math/Rect.h"
#include "Catastrophe/Core/Math/Rectf.h"
#include "Catastrophe/Core/Math/Vector2.h"
#include "Catastrophe/Core/Math/Vector3.h"
#include "Catastrophe/Core/Math/Vector4.h"
#include "Catastrophe/Core/Math/Color.h"
#include "Catastrophe/Core/Math/Colorf.h"
#include "Catastrophe/Core/Math/Quaternion.h"
#include "Catastrophe/Core/Math/Matrix.h"
#include "Catastrophe/Core/Math/Packed/PackedPoint.h"
#include "Catastrophe/Core/Math/Packed/PackedRect.h"


CE_NAMESPACE_BEGIN


// string to value type overloads
CE_API bool ToBool( const char* s, bool defaultValue = false );
CE_API u8 ToByte( const char* s, u8 defaultValue = 0 );
CE_API s16 ToShort( const char* s, s16 defaultValue = 0 );
CE_API int ToInt( const char* s, int defaultValue = 0 );
CE_API u32 ToUInt( const char* s, u32 defaultValue = 0 );
CE_API float ToFloat( const char* s, float defaultValue = 0.f );
CE_API int ToInt( const char* source, char** dest, int defaultValue = 0 );
CE_API float ToFloat( const char* source, char** dest, float defaultValue = 0.f );
CE_API Color ToColor( const char* s, const Color& defaultValue = Color::White() );
CE_API Colorf ToColorf( const char* s, const Colorf& defaultValue = Colorf() );
CE_API Point ToPoint( const char* s, const Point& defaultValue = Point::Zero );
CE_API Rect ToRect( const char* s, const Rect& defaultValue = Rect::Zero );
CE_API Rectf ToRectf( const char* s, const Rectf& defaultValue = Rectf::Zero );
CE_API PackedPoint ToPackedPoint( const char* s, const PackedPoint& defaultValue = PackedPoint::Zero );
CE_API PackedRect ToPackedRect( const char* s, const PackedRect& defaultValue = PackedRect::Zero );
CE_API Vector2 ToVector2( const char* s, const Vector2& defaultValue = Vector2::Zero );
CE_API Vector3 ToVector3( const char* s, const Vector3& defaultValue = Vector3::Zero );
CE_API Vector4 ToVector4( const char* s, const Vector4& defaultValue = Vector4::Zero );
CE_API Quaternion ToQuaternion( const char* s, const Quaternion& defaultValue = Quaternion() );
CE_API Matrix ToMatrix( const char* s, const Matrix& defaultValue = Matrix::Identity );


// math types to string overloads
CE_API String ToString( bool value );
CE_API String ToString( char value );
CE_API String ToString( s16 value );
CE_API String ToString( int value );
CE_API String ToString( u32 value );
CE_API String ToString( float value );
CE_API String ToString( const Point& value );
CE_API String ToString( const Rect& value );
CE_API String ToString( const Rectf& value );
CE_API String ToString( const PackedPoint& value );
CE_API String ToString( const PackedRect& value );
CE_API String ToString( const Color& value );
CE_API String ToString( const Colorf& value );
CE_API String ToString( const Vector2& value );
CE_API String ToString( const Vector3& value );
CE_API String ToString( const Vector4& value );
CE_API String ToString( const Quaternion& value );
CE_API String ToString( const Matrix& value );



CE_NAMESPACE_END


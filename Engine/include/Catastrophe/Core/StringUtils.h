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

#include <fc/string.h>

#include "../Common.h"
#include "../Math/Point.h"
#include "../Math/Rect.h"
#include "../Math/Rectf.h"
#include "../Math/Vector2.h"
#include "../Math/Vector3.h"
#include "../Math/Vector4.h"
#include "../Math/Color.h"
#include "../Math/Colorf.h"
#include "../Math/Quaternion.h"
#include "../Math/Matrix.h"

CE_NAMESPACE_BEGIN


// string to value type overloads
bool ToBool( const char* s, bool defaultValue = false );
byte ToByte( const char* s, byte defaultValue = 0 );
short ToShort( const char* s, short defaultValue = 0 );
int ToInt( const char* s, int defaultValue = 0 );
size_t ToUInt( const char* s, size_t defaultValue = 0 );
float ToFloat( const char* s, float defaultValue = 0.f );
int ToInt( const char* source, char** dest, int defaultValue = 0 );
float ToFloat( const char* source, char** dest, float defaultValue = 0.f );
Color ToColor( const char* s, const Color& defaultValue = Color::White() );
Colorf ToColorf( const char* s, const Colorf& defaultValue = Colorf() );
Point ToPoint( const char* s, const Point& defaultValue = Point::Zero );
Rect ToRect( const char* s, const Rect& defaultValue = Rect::Zero );
Rectf ToRectf( const char* s, const Rectf& defaultValue = Rectf::Zero );
Vector2 ToVector2( const char* s, const Vector2& defaultValue = Vector2::Zero );
Vector3 ToVector3( const char* s, const Vector3& defaultValue = Vector3::Zero );
Vector4 ToVector4( const char* s, const Vector4& defaultValue = Vector4::Zero );
Quaternion ToQuaternion( const char* s, const Quaternion& defaultValue = Quaternion() );
Matrix ToMatrix( const char* s, const Matrix& defaultValue = Matrix::Identity );


// math types to string overloads
fc::string ToString( bool value );
fc::string ToString( char value );
fc::string ToString( short value );
fc::string ToString( int value );
fc::string ToString( size_t value );
fc::string ToString( float value );
fc::string ToString( const Point& value );
fc::string ToString( const Rect& value );
fc::string ToString( const Rectf& value );
fc::string ToString( const Color& value );
fc::string ToString( const Colorf& value );
fc::string ToString( const Vector2& value );
fc::string ToString( const Vector3& value );
fc::string ToString( const Vector4& value );
fc::string ToString( const Quaternion& value );
fc::string ToString( const Matrix& value );



CE_NAMESPACE_END


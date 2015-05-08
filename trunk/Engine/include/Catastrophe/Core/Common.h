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


#ifdef _MSC_VER
	#pragma warning ( disable : 4480 ) //warning C4480: nonstandard extension used: specifying underlying type for enum
#endif


// include this for common macros
#include "Catastrophe/Core/Config.h"
#include "Catastrophe/Core/TypeTraits.h"

// todo: name this better...
#if CE_DEBUG
	#define Debug(x) x
#else
	#define Debug(x)
#endif

#define LOG_DEBUG	0
#define LOG_INFO	1
#define LOG_WARNING	2
#define LOG_ERROR	3

#define Log(format, ...)		LogWrite(LOG_WARNING, format, __VA_ARGS__)
#define LogDebug(format, ...)	LogWrite(LOG_DEBUG, format, __VA_ARGS__)
#define LogInfo(format, ...)	LogWrite(LOG_INFO, format, __VA_ARGS__)
#define LogError(format, ...)	LogWrite(LOG_ERROR, format, __VA_ARGS__)
#define LogWarning(format, ...)	LogWrite(LOG_WARNING, format, __VA_ARGS__)

CE_API NOINLINE extern void LogWrite(int level, const char* format, ...);


CE_NAMESPACE_BEGIN


// Forward Declarations

class String;
class StringRef;
template <u32 N> class StaticString;


class Allocator;
class PoolAllocator;
class StackAllocator;


class Vector2;
class Vector3;
class Vector4;
class Point;
class PackedPoint;
class Rectf;
class Rect;
class PackedRect;
class Quaternion;
class Matrix;
class Circle;
class Color;
class Colorf;
class HSVColor;
class HSLColor;

class Line;
class Plane;
class Frustum;

struct TweenValue;
class Tween;
class TweenGroup;


// IO
class Serializer;
class Deserializer;
class File;
class MemoryFile;
class ConfigFile;
class PackFile;
class XmlReader;
class XmlWriter;
class XmlElement;
class XmlDocument;
class AttributeReader;
class AttributeWriter;



// Math
MAKE_TRAIT(Vector2, is_pod);
MAKE_TRAIT(Vector3, is_pod);
MAKE_TRAIT(Vector4, is_pod);
MAKE_TRAIT(Point, is_pod);
MAKE_TRAIT(PackedPoint, is_pod);
MAKE_TRAIT(Rectf, is_pod);
MAKE_TRAIT(Rect, is_pod);
MAKE_TRAIT(PackedRect, is_pod);
MAKE_TRAIT(Quaternion, is_pod);
MAKE_TRAIT(Matrix, is_pod);
MAKE_TRAIT(Circle, is_pod);
MAKE_TRAIT(Line, is_pod);
MAKE_TRAIT(Plane, is_pod);
MAKE_TRAIT(Frustum, is_pod);
MAKE_TRAIT(Color, is_pod);
MAKE_TRAIT(Colorf, is_pod);
MAKE_TRAIT(HSVColor, is_pod);
MAKE_TRAIT(HSLColor, is_pod);
MAKE_TRAIT(TweenValue, is_pod);



CE_NAMESPACE_END

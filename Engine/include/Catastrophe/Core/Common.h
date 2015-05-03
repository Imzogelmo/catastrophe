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


#define Log			__Internal_Log_Write
#define LogInfo		__Internal_Log_Write
#define LogError	__Internal_Log_Write
#define LogWarning	__Internal_Log_Write

#ifdef CE_DEBUG
	#define LogDebug	__Internal_Log_Write
#else
	#define LogDebug(x)

	/* disable "too many actual parameters for macro" */
	#ifdef _MSC_VER
		#pragma warning ( disable : 4002 )
	#endif
#endif


CE_NAMESPACE_BEGIN


// Logging functions
extern NOINLINE CE_API void __Internal_Log_Write( const char* format, ... );


// Forward Declarations

class String;
class StringRef;
template <u32 N> class StaticString;


class Allocator;
class PoolAllocator;
class StackAllocator;


class System;
class Window;

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

class BoundingBox;
class Sphere;
class Line;
class Plane;
class Ray;
class Frustum;

struct TweenValue;
class Tween;
class TweenGroup;


// IO
class Serializer;
class Deserializer;
class File;
class MemoryFile;
class CompressedFile;
class ConfigFile;
class PackFile;
class XmlReader;
class XmlWriter;
class XmlElement;
class XmlDocument;
class AttributeReader;
class AttributeWriter;


class Sound;
class SoundEngine;


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
MAKE_TRAIT(Ray, is_pod);
MAKE_TRAIT(Plane, is_pod);
MAKE_TRAIT(Frustum, is_pod);
MAKE_TRAIT(BoundingBox, is_pod);
MAKE_TRAIT(Color, is_pod);
MAKE_TRAIT(Colorf, is_pod);
MAKE_TRAIT(HSVColor, is_pod);
MAKE_TRAIT(HSLColor, is_pod);
MAKE_TRAIT(TweenValue, is_pod);



CE_NAMESPACE_END

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


typedef signed char			sbyte;
typedef unsigned char		ubyte;
typedef unsigned char		uchar;
typedef unsigned short		ushort;
typedef unsigned long		ulong;
typedef unsigned int		uint;
typedef unsigned int		gluint;
typedef unsigned int		glenum;
typedef int					glint;

#ifdef _MSC_VER
typedef unsigned __int64	uint64;
typedef __int64				int64;
#else
typedef unsigned long long	uint64;
typedef long long			int64;
#endif

//CE_API 
#if defined CE_EXPORT
	#define CE_API __declspec(dllexport)
#elif defined CE_IMPORT
	#define CE_API __declspec(dllimport)
#else
	#define CE_API
#endif

//CE_WANT_NAMESPACE must be defined in both lib and client.
#if defined CE_WANT_NAMESPACE
#define CE_NAMESPACE_BEGIN namespace ce {
#define CE_NAMESPACE_END }
#define USING_NAMESPACE_CE using namespace ce;
#else
#define CE_NAMESPACE_BEGIN
#define CE_NAMESPACE_END
#define USING_NAMESPACE_CE
#endif

#define CE_TRUE		1
#define CE_FALSE	0
#define CE_ZERO		0
#define CE_SUCCESS	0
#define CE_ERROR	-1


#if defined (DEBUG) || defined (_DEBUG)
	#define CE_DEBUG 1
#endif

#ifdef CE_DEBUG
	#define CE_ASSERT(x)	assert(x)
#else
	#define CE_ASSERT(x)
#endif


//include this for common macros
#include <fc/common.h>

#define CE_FORCE_INLINE FC_FORCE_INLINE
#define CE_NO_INLINE	FC_NO_INLINE
#define CE_LIKELY		FC_LIKELY
#define CE_UNLIKELY		FC_UNLIKELY

#define Log			__Internal_Log_Write
#define LogInfo		__Internal_Log_Write
#define LogError	__Internal_Log_Write
#define LogWarning	__Internal_Log_Write


//forward declare the fc::string type.
namespace fc
{
	//template <class T> class allocator;
	//template < class T, size_t BufferSize = FC_DEFAULT_STRING_BUFFER_SIZE, class Alloc = allocator<T> > class basic_string_with_buffer_storage;
	//template < class T, class Storage = basic_string_with_buffer_storage<T> > class basic_string;
}


CE_NAMESPACE_BEGIN

//logging functions
extern FC_NO_INLINE void __Internal_Log_Write( const char* format, ... );
//extern FC_NO_INLINE void __Internal_Log_Write( const fc::basic_string<char>& message );


/* Forward Declarations */
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

struct Glyph;
class Font;

class Image;
class Texture;
class BlendMode;
class Font;
class SpriteBatch;
class Primitive;
class PrimitiveBatch;
class ShaderObject;
class VertexShader;
class FragmentShader;
class Shader;
class TextureLoader;
class Viewport;

class AnimationFrames;
class Animation;
class AnimationSet;
class SpriteBase;
class Sprite;
class AnimatedSprite;

struct VertexColor;
struct VertexColorTexture;

class Serializer;
class Deserializer;
class File;
class PackFile;
class VectorBuffer;
class XmlReader;
class XmlWriter;

class Sound;
class SoundEngine;


// optimize for use with algorithms and containers
#include <fc/type_traits.h>

FC_MAKE_TRAIT(Vector2, is_pod);
FC_MAKE_TRAIT(Vector3, is_pod);
FC_MAKE_TRAIT(Vector4, is_pod);
FC_MAKE_TRAIT(Point, is_pod);
FC_MAKE_TRAIT(PackedPoint, is_pod);
FC_MAKE_TRAIT(Rectf, is_pod);
FC_MAKE_TRAIT(Rect, is_pod);
FC_MAKE_TRAIT(PackedRect, is_pod);
FC_MAKE_TRAIT(Quaternion, is_pod);
FC_MAKE_TRAIT(Matrix, is_pod);
FC_MAKE_TRAIT(Circle, is_pod);
FC_MAKE_TRAIT(Line, is_pod);
FC_MAKE_TRAIT(Ray, is_pod);
FC_MAKE_TRAIT(Plane, is_pod);
FC_MAKE_TRAIT(Frustum, is_pod);

FC_MAKE_TRAIT(Color, is_pod);
FC_MAKE_TRAIT(Colorf, is_pod);
FC_MAKE_TRAIT(HSVColor, is_pod);
FC_MAKE_TRAIT(HSLColor, is_pod);
FC_MAKE_TRAIT(VertexColor, is_pod);
FC_MAKE_TRAIT(VertexColorTexture, is_pod);

FC_MAKE_TRAIT(Glyph, is_pod);
FC_MAKE_TRAIT(Sprite, is_pod);


// tinyxml types
namespace tinyxml2
{
	class XMLDocument;
	class XMLElement;
	class XMLNode;
}


typedef tinyxml2::XMLDocument	XmlDocument_t;
typedef tinyxml2::XMLElement	XmlElement_t;
typedef tinyxml2::XMLNode		XmlNode_t;


CE_NAMESPACE_END

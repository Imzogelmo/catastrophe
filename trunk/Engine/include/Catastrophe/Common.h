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


#if defined (DEBUG) || defined (_DEBUG)
	#define CE_DEBUG 1
#endif

// disable all the extraneous bullshit
#if defined(_MSC_VER)
	#define _HAS_ITERATOR_DEBUGGING 0
	#if !CE_DEBUG
		#define _HAS_EXCEPTIONS 0
		#define _SECURE_SCL 0
	#endif
	//#define _STATIC_CPPLIB
#endif

// depricated
typedef char				sbyte;
typedef unsigned char		byte;
typedef unsigned long		ulong;
typedef unsigned int		uint;

#if defined(_MSC_VER)
	typedef __int8				s8;
	typedef __int16				s16;
	typedef __int32				s32;
	typedef __int64				s64;
	typedef unsigned __int8		u8;
	typedef unsigned __int16	u16;
	typedef unsigned __int32	u32;
	typedef unsigned __int64	u64;
	typedef float				f32;
	typedef double				f64;
#else
	typedef char				s8;
	typedef short				s16;
	typedef int					s32;
	typedef long long			s64;
	typedef unsigned char		u8;
	typedef unsigned short		u16;
	typedef unsigned int		u32;
	typedef unsigned long long	u64;
	typedef float				f32;
	typedef double				f64;
#endif


#if _MSC_VER >= 1600
	#define null nullptr
#else
	#define null 0
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

#ifdef CE_DEBUG
	#define CE_ASSERT(x)	assert(x)
#else
	#define CE_ASSERT(x)
#endif


//include this for common macros
#include <fc/common.h>
#include <fc/forward.h>

#define CE_FORCE_INLINE FC_FORCE_INLINE
#define CE_NO_INLINE	FC_NO_INLINE
#define CE_LIKELY		FC_LIKELY
#define CE_UNLIKELY		FC_UNLIKELY

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

//typedef String				String;
typedef fc::basic_string<char>		String;
typedef fc::basic_string_ref<char>	StringRef;

//todo: use c++11 template typedef support instead.
//typedef template<u32 N> using StaticString = fc::static_string<N>
#define StaticString	fc::static_string
//#define Array			fc::dynamic_array
//#define StaticArray		fc::static_array


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

struct TweenValue;
class Tween;
class TweenGroup;

struct Glyph;
struct RenderState;
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
class RenderTarget;

class SpriteAnimation;
class SpriteBase;
class Sprite;
class AnimatedSprite;
class AnimatedSpriteSet;
class PackedSprite;

// Vertex
struct Vertex2D;
struct VertexTexture2D;
struct VertexColor2D;
struct VertexColorTexture2D;

struct Vertex3D;
struct VertexTexture3D;
struct VertexNormalTexture3D;
struct VertexColor3D;
struct VertexColorTexture3D;
struct VertexColorNormalTexture3D;

// IO
class Serializer;
class Deserializer;
class File;
class FileBuffer;
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


// optimize for use with algorithms and containers
#include <fc/type_traits.h>

// Math
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
FC_MAKE_TRAIT(BoundingBox, is_pod);
FC_MAKE_TRAIT(Color, is_pod);
FC_MAKE_TRAIT(Colorf, is_pod);
FC_MAKE_TRAIT(HSVColor, is_pod);
FC_MAKE_TRAIT(HSLColor, is_pod);
FC_MAKE_TRAIT(TweenValue, is_pod);

FC_MAKE_TRAIT(Glyph, is_pod);
FC_MAKE_TRAIT(SpriteBase, is_pod);


// rapidxml forward declared types
namespace rapidxml
{
	template <class Ch> class xml_document;
	template <class Ch> class xml_node;
}

typedef rapidxml::xml_document<char> XmlDocument_t;
typedef rapidxml::xml_node<char> XmlNode_t;


#ifndef CE_NO_INTRUSIVE_PTRS

	#include <fc/intrusive_ptr.h>

	typedef fc::intrusive_ptr<Texture>	TexturePtr;
	typedef fc::intrusive_ptr<Font>		FontPtr;

#else
	typedef Texture*		TexturePtr;
	typedef Font*			FontPtr;

	// safe to memcopy raw pointer types
	FC_MAKE_TRAIT(Sprite, is_pod);
	FC_MAKE_TRAIT(AnimatedSprite, is_pod);
	FC_MAKE_TRAIT(SpriteAnimation, is_pod);
	FC_MAKE_TRAIT(PackedSprite, is_pod);
#endif


CE_NAMESPACE_END

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

#include "Common.h"
#include "Colorf.h"


/* disable nameless struct/union warning */
#ifdef _MSC_VER
	#pragma warning ( push )
	#pragma warning ( disable : 4201 )
#endif

CE_NAMESPACE_BEGIN


class CE_API Color
{
public:
	Color()												: packed_value(0xff000000) {}
	Color( u8 gray, u8 alpha )					{ packed_value = _Pack( gray, gray, gray, alpha ); }
	Color( u8 r, u8 g, u8 b, u8 a = 255 )	{ packed_value = _Pack( r, g, b, a ); }
	Color( const Colorf &c )							{ packed_value = _Pack( c ); }
	Color( const HSVColor &c );
	Color( const HSLColor &c );

	Color &operator = ( const Colorf &c ) { packed_value = _Pack( c ); return *this; }
	Color &operator = ( u32 val ) { packed_value = val; return *this; }
	Color &operator = ( const HSVColor &c );
	Color &operator = ( const HSLColor &c );

	u8		&operator []( int i )		{ return *(&r + i); }
	const u8 &operator []( int i ) const	{ return *(&r + i); }

	Color operator -() const { return Color( 255 - r, 255 - g, 255 - b, a ); }
	Color operator +() const { return Color( 255 - r, 255 - g, 255 - b, a ); }
	Color operator *( const Color &c ) const;

	bool operator == ( const Color &c )	const { return (packed_value == c.packed_value); }
	bool operator != ( const Color &c )	const { return (packed_value != c.packed_value); }

	bool Equals( const Color &c) const { return (packed_value == c.packed_value); }

	u32 Rgba() const { return packed_value; }
	u32 Bgra() const { return _Pack( b, g, r, a ); }
	u32 Argb() const { return _Pack( a, r, g, b ); }
	u32 Abgr()	const { return _Pack( a, b, g, r ); }

	void Set( u8 r, u8 g, u8 b, u8 a ) { packed_value = _Pack( r, g, b, a ); }
	void Set( const Color &c ) { *this = c; }
	void Set( const Colorf &c ) { packed_value = _Pack(c); }

	void Clamp( const Color &min, const Color &max )
	{
		Math::FastClamp(r, min.r, max.r);
		Math::FastClamp(g, min.g, max.g);
		Math::FastClamp(b, min.b, max.b);
		Math::FastClamp(a, min.a, max.a);
	}

	void CombineAlpha( u8 alpha ) { a = (u8)(((int)a * alpha) / 255); }
	void CombineRgb( const Color& rgb )
	{
		r = (u8)(((int)rgb.r * r) / 255);
		g = (u8)(((int)rgb.g * g) / 255);
		b = (u8)(((int)rgb.b * b) / 255);
	}

	Color GetCombinedRgb( const Color& rgb )
	{
		return Color(
			(u8)(((int)rgb.r * r) / 255),
			(u8)(((int)rgb.g * g) / 255),
			(u8)(((int)rgb.b * b) / 255),
			a);
	}

	Color GetCombinedAlpha( u8 alpha )
	{
		return Color(r, g, b, (u8)(((int)a * alpha) / 255));
	}

	Color Negative() const
	{
		return Color( (255 - r), (255 - g), (255 - b), a );
	}

	u8 Luminance() const
	{
		return (u8)(((299 * (int)r) + (587 * (int)g) + (114 * (int)b)) / 1000);
	}

	Color Grayscale( bool average = false ) const
	{
		if( average )
			return Color( (u8)((int)(r + g + b) / 3), a );

		return Color(Luminance(), a);
	}

	Colorf ToColorf()	const;
	Vector4 ToVector4() const;
	Vector3 ToVector3() const;

	static Color Lerp( const Color& c1, const Color& c2, float t);

	static Color AliceBlue( u8 alpha = 255 )		{ return Color(240, 248, 255, alpha); }
	static Color AntiqueWhite( u8 alpha = 255 )	{ return Color(250, 235, 215, alpha); }
	static Color Aqua( u8 alpha = 255 )			{ return Color(  0, 255, 255, alpha); }
	static Color Aquamarine( u8 alpha = 255 )		{ return Color(127, 255, 212, alpha); }
	static Color Azure( u8 alpha = 255 )			{ return Color(240, 255, 255, alpha); }
	static Color Beige( u8 alpha = 255 )			{ return Color(245, 245, 220, alpha); }
	static Color Bisque( u8 alpha = 255 )			{ return Color(255, 228, 196, alpha); }
	static Color Black( u8 alpha = 255 )			{ return Color(  0, 0, 0, alpha); }
	static Color BlanchedAlmond( u8 alpha = 255 )	{ return Color(255, 235, 205, alpha); }
	static Color Blue( u8 alpha = 255 )			{ return Color(  0, 0, 255, alpha); }
	static Color BlueViolet( u8 alpha = 255 )		{ return Color(138, 43, 226, alpha); }
	static Color Brown( u8 alpha = 255 )			{ return Color(165, 42, 42, alpha); }
	static Color Burlywood( u8 alpha = 255 )		{ return Color(222, 184, 135, alpha); }
	static Color CadetBlue( u8 alpha = 255 )		{ return Color( 95, 158, 160, alpha); }
	static Color Chartreuse( u8 alpha = 255 )		{ return Color(127, 255, 0, alpha); }
	static Color Chocolate( u8 alpha = 255 )		{ return Color(210, 105, 30, alpha); }
	static Color Coral( u8 alpha = 255 )			{ return Color(255, 127, 80, alpha); }
	static Color CornflowerBlue( u8 alpha = 255 )	{ return Color(100, 149, 237, alpha); }
	static Color Cornsilk( u8 alpha = 255 )		{ return Color(255, 248, 220, alpha); }
	static Color Crimson( u8 alpha = 255 )			{ return Color(220, 20, 60, alpha); }
	static Color Cyan( u8 alpha = 255 )			{ return Color(  0, 255, 255, alpha); }
	static Color DarkBlue( u8 alpha = 255 )		{ return Color(  0, 0, 139, alpha); }
	static Color DarkCyan( u8 alpha = 255 )		{ return Color(  0, 139, 139, alpha); }
	static Color DarkGoldenrod( u8 alpha = 255 )	{ return Color(184, 134, 11, alpha); }
	static Color DarkGray( u8 alpha = 255 )		{ return Color(64, 64, 64, alpha); }
	static Color DarkGreen( u8 alpha = 255 )		{ return Color(  0, 100, 0, alpha); }
	static Color DarkKhaki( u8 alpha = 255 )		{ return Color(189, 183, 107, alpha); }
	static Color DarkMagenta( u8 alpha = 255 )		{ return Color(139, 0, 139, alpha); }
	static Color DarkOliveGreen( u8 alpha = 255 )	{ return Color( 85, 107, 47, alpha); }
	static Color DarkOrange( u8 alpha = 255 )		{ return Color(255, 140, 0, alpha); }
	static Color DarkOrchid( u8 alpha = 255 )		{ return Color(153, 50, 204, alpha); }
	static Color DarkRed( u8 alpha = 255 )			{ return Color(139, 0, 0, alpha); }
	static Color DarkSalmon( u8 alpha = 255 )		{ return Color(233, 150, 122, alpha); }
	static Color DarkSeaGreen( u8 alpha = 255 )	{ return Color(143, 188, 143, alpha); }
	static Color DarkSlateBlue( u8 alpha = 255 )	{ return Color( 72, 61, 139, alpha); }
	static Color DarkSlateGray( u8 alpha = 255 )	{ return Color( 47, 79, 79, alpha); }
	static Color DarkTurquoise( u8 alpha = 255 )	{ return Color(  0, 206, 209, alpha); }
	static Color DarkViolet( u8 alpha = 255 )		{ return Color(148, 0, 211, alpha); }
	static Color DeepPink( u8 alpha = 255 )		{ return Color(255, 20, 147, alpha); }
	static Color DeepSkyBlue( u8 alpha = 255 )		{ return Color(  0, 191, 255, alpha); }
	static Color DimGray( u8 alpha = 255 )			{ return Color(105, 105, 105, alpha); }
	static Color DodgerBlue( u8 alpha = 255 )		{ return Color( 30, 144, 255, alpha); }
	static Color Firebrick( u8 alpha = 255 )		{ return Color(178, 34, 34, alpha); }
	static Color FloralWhite( u8 alpha = 255 )		{ return Color(255, 250, 240, alpha); }
	static Color ForestGreen( u8 alpha = 255 )		{ return Color( 34, 139, 34, alpha); }
	static Color Fuchsia( u8 alpha = 255 )			{ return Color(255, 0, 255, alpha); }
	static Color Gainsboro( u8 alpha = 255 )		{ return Color(220, 220, 220, alpha); }
	static Color GhostWhite( u8 alpha = 255 )		{ return Color(248, 248, 255, alpha); }
	static Color Gold( u8 alpha = 255 )			{ return Color(255, 215, 0, alpha); }
	static Color Goldenrod( u8 alpha = 255 )		{ return Color(218, 165, 32, alpha); }
	static Color Gray( u8 alpha = 255 )			{ return Color(128, 128, 128, alpha); }
	static Color Green( u8 alpha = 255 )			{ return Color(  0, 128, 0, alpha); }
	static Color GreenYellow( u8 alpha = 255 )		{ return Color(173, 255, 47, alpha); }
	static Color Honeydew( u8 alpha = 255 )		{ return Color(240, 255, 240, alpha); }
	static Color HotPink( u8 alpha = 255 )			{ return Color(255, 105, 180, alpha); }
	static Color IndianRed( u8 alpha = 255 )		{ return Color(205, 92, 92, alpha); }
	static Color Indigo( u8 alpha = 255 )			{ return Color( 75, 0, 130, alpha); }
	static Color Ivory( u8 alpha = 255 )			{ return Color(255, 255, 240, alpha); }
	static Color Khaki( u8 alpha = 255 )			{ return Color(240, 230, 140, alpha); }
	static Color Lavender( u8 alpha = 255 )		{ return Color(230, 230, 250, alpha); }
	static Color LavenderBlush( u8 alpha = 255 )	{ return Color(255, 240, 245, alpha); }
	static Color LawnGreen( u8 alpha = 255 )		{ return Color(124, 252, 0, alpha); }
	static Color LemonChiffon( u8 alpha = 255 )	{ return Color(255, 250, 205, alpha); }
	static Color LightBlue( u8 alpha = 255 )		{ return Color(173, 216, 230, alpha); }
	static Color LightCoral( u8 alpha = 255 )		{ return Color(240, 128, 128, alpha); }
	static Color LightCyan( u8 alpha = 255 )		{ return Color(224, 255, 255, alpha); }
	static Color LightGoldenrodYellow( u8 alpha = 255 ) { return Color(250, 250, 210, alpha); }
	static Color LightGray( u8 alpha = 255 )		{ return Color(211, 211, 211, alpha); }
	static Color LightGreen( u8 alpha = 255 )		{ return Color(144, 238, 144, alpha); }
	static Color LightPink( u8 alpha = 255 )		{ return Color(255, 182, 193, alpha); }
	static Color LightSalmon( u8 alpha = 255 )		{ return Color(255, 160, 122, alpha); }
	static Color LightSeaGreen( u8 alpha = 255 )	{ return Color( 32, 178, 170, alpha); }
	static Color LightSkyBlue( u8 alpha = 255 )	{ return Color(135, 206, 250, alpha); }
	static Color LightSlateGray( u8 alpha = 255 )	{ return Color(119, 136, 153, alpha); }
	static Color LightSteelBlue( u8 alpha = 255 )	{ return Color(176, 196, 222, alpha); }
	static Color LightYellow( u8 alpha = 255 )		{ return Color(255, 255, 224, alpha); }
	static Color Lime( u8 alpha = 255 )			{ return Color(  0, 255, 0, alpha); }
	static Color LimeGreen( u8 alpha = 255 )		{ return Color( 50, 205, 50, alpha); }
	static Color Linen( u8 alpha = 255 )			{ return Color(250, 240, 230, alpha); }
	static Color Magenta( u8 alpha = 255 )			{ return Color(255, 0, 255, alpha); }
	static Color Maroon( u8 alpha = 255 )			{ return Color(128, 0, 0, alpha); }
	static Color MediumAquamarine( u8 alpha = 255 ) { return Color(102, 205, 170, alpha); }
	static Color MediumBlue( u8 alpha = 255 )		{ return Color(  0, 0, 205, alpha); }
	static Color MediumOrchid( u8 alpha = 255 )	{ return Color(186, 85, 211, alpha); }
	static Color MediumPurple( u8 alpha = 255 )	{ return Color(147, 112, 219, alpha); }
	static Color MediumSeaGreen( u8 alpha = 255 )	{ return Color( 60, 179, 113, alpha); }
	static Color MediumSlateBlue( u8 alpha = 255 ) { return Color(123, 104, 238, alpha); }
	static Color MediumSpringGreen( u8 alpha = 255 ) { return Color( 0, 250, 154, alpha); }
	static Color MediumTurquoise( u8 alpha = 255 ) { return Color( 72, 209, 204, alpha); }
	static Color MediumVioletred( u8 alpha = 255 ) { return Color(199, 21, 133, alpha); }
	static Color MidnightBlue( u8 alpha = 255 )	{ return Color( 25, 25, 112, alpha); }
	static Color MintCream( u8 alpha = 255 )		{ return Color(245, 255, 250, alpha); }
	static Color MistyRose( u8 alpha = 255 )		{ return Color(255, 228, 225, alpha); }
	static Color Moccasin( u8 alpha = 255 )		{ return Color(255, 228, 181, alpha); }
	static Color NavajoWhite( u8 alpha = 255 )		{ return Color(255, 222, 173, alpha); }
	static Color Navy( u8 alpha = 255 )			{ return Color( 0, 0, 128, alpha); }
	static Color OldLace( u8 alpha = 255 )			{ return Color(253, 245, 230, alpha); }
	static Color Olive( u8 alpha = 255 )			{ return Color(128, 128, 0, alpha); }
	static Color OliveDrab( u8 alpha = 255 )		{ return Color(107, 142, 35, alpha); }
	static Color Orange( u8 alpha = 255 )			{ return Color(255, 165, 0, alpha); }
	static Color OrangeRed( u8 alpha = 255 )		{ return Color(255, 69, 0, alpha); }
	static Color Orchid( u8 alpha = 255 )			{ return Color(218, 112, 214, alpha); }
	static Color PaleGoldenrod( u8 alpha = 255 )	{ return Color(238, 232, 170, alpha); }
	static Color PaleGreen( u8 alpha = 255 )		{ return Color(152, 251, 152, alpha); }
	static Color PaleTurquoise( u8 alpha = 255 )	{ return Color(175, 238, 238, alpha); }
	static Color PaleVioletRed( u8 alpha = 255 )	{ return Color(219, 112, 147, alpha); }
	static Color PapayaWhip( u8 alpha = 255 )		{ return Color(255, 239, 213, alpha); }
	static Color PeachPuff( u8 alpha = 255 )		{ return Color(255, 218, 185, alpha); }
	static Color Peru( u8 alpha = 255 )			{ return Color(205, 133, 63, alpha); }
	static Color Pink( u8 alpha = 255 )			{ return Color(255, 192, 203, alpha); }
	static Color Plum( u8 alpha = 255 )			{ return Color(221, 160, 221, alpha); }
	static Color PowderBlue( u8 alpha = 255 )		{ return Color(176, 224, 230, alpha); }
	static Color Purple( u8 alpha = 255 )			{ return Color(128, 0, 128, alpha); }
	static Color Red( u8 alpha = 255 )				{ return Color(255, 0, 0, alpha); }
	static Color RosyBrown( u8 alpha = 255 )		{ return Color(188, 143, 143, alpha); }
	static Color RoyalBlue( u8 alpha = 255 )		{ return Color( 65, 105, 225, alpha); }
	static Color SaddleBrown( u8 alpha = 255 )		{ return Color(139, 69, 19, alpha); }
	static Color Salmon( u8 alpha = 255 )			{ return Color(250, 128, 114, alpha); }
	static Color SandyBrown( u8 alpha = 255 )		{ return Color(244, 164, 96, alpha); }
	static Color SeaGreen( u8 alpha = 255 )		{ return Color( 46, 139, 87, alpha); }
	static Color SeaShell( u8 alpha = 255 )		{ return Color(255, 245, 238, alpha); }
	static Color Sienna( u8 alpha = 255 )			{ return Color(160, 82, 45, alpha); }
	static Color Silver( u8 alpha = 255 )			{ return Color(192, 192, 192, alpha); }
	static Color SkyBlue( u8 alpha = 255 )			{ return Color(135, 206, 235, alpha); }
	static Color SlateBlue( u8 alpha = 255 )		{ return Color(106, 90, 205, alpha); }
	static Color SlateGray( u8 alpha = 255 )		{ return Color(112, 128, 144, alpha); }
	static Color Snow( u8 alpha = 255 )			{ return Color(255, 250, 250, alpha); }
	static Color SpringGreen( u8 alpha = 255 )		{ return Color(  0, 255, 127, alpha); }
	static Color SteelBlue( u8 alpha = 255 )		{ return Color( 70, 130, 180, alpha); }
	static Color Tan( u8 alpha = 255 )				{ return Color(210, 180, 140, alpha); }
	static Color Teal( u8 alpha = 255 )			{ return Color(  0, 128, 128, alpha); }
	static Color Thistle( u8 alpha = 255 )			{ return Color(216, 191, 216, alpha); }
	static Color Tomato( u8 alpha = 255 )			{ return Color(255, 99, 71, alpha); }
	static Color Turquoise( u8 alpha = 255 )		{ return Color( 64, 224, 208, alpha); }
	static Color Violet( u8 alpha = 255 )			{ return Color(238, 130, 238, alpha); }
	static Color Wheat( u8 alpha = 255 )			{ return Color(245, 222, 179, alpha); }
	static Color White( u8 alpha = 255 )			{ return Color(255, 255, 255, alpha); }
	static Color WhiteSmoke( u8 alpha = 255 )		{ return Color(245, 245, 245, alpha); }
	static Color Yellow( u8 alpha = 255 )			{ return Color(255, 255, 0, alpha); }
	static Color YellowGreen( u8 alpha = 255 )		{ return Color(154, 205, 50, alpha); }

	static Color TransparentWhite() { return Color(255, 255, 255, 0); }
	static Color TransparentBlack() { return Color(0, 0, 0, 0); }

protected:

#ifdef CE_BIG_ENDIAN
	#define BIT_SHIFT_24	0
	#define BIT_SHIFT_16	8
	#define BIT_SHIFT_8		16
	#define BIT_SHIFT_0		24
#else
	#define BIT_SHIFT_24	24
	#define BIT_SHIFT_16	16
	#define BIT_SHIFT_8		8
	#define BIT_SHIFT_0		0
#endif

	static u32 _Pack( float r, float g, float b, float a )
	{
		return (u32)( 
			(_ToByte(a) << BIT_SHIFT_24) |
			(_ToByte(b) << BIT_SHIFT_16) |
			(_ToByte(g) << BIT_SHIFT_8) |
			(_ToByte(r) << BIT_SHIFT_0)
		);
	}

	static u32 _Pack( int r, int g, int b, int a )
	{
		return (u32)( 
			(a << BIT_SHIFT_24) |
			(b << BIT_SHIFT_16) |
			(g << BIT_SHIFT_8) |
			(r << BIT_SHIFT_0)
		);
	}

	static u32 _Pack( u8 r, u8 g, u8 b, u8 a )
	{
		return (u32)( 
			(a << BIT_SHIFT_24) |
			(b << BIT_SHIFT_16) |
			(g << BIT_SHIFT_8) |
			(r << BIT_SHIFT_0)
		);
	}

	static u32 _Pack( const Colorf &c )
	{
		return _Pack( c.r, c.g, c.b, c.a );
	}

	static u8 _ToByte( float t )
	{
		return (u8) (t * 255.0f);
	}

	static float _ToFloat( u8 t )
	{
		const float inv = 1.f / 255.f;
		return (float) (t * inv);
	}

#undef BIT_SHIFT_24
#undef BIT_SHIFT_16
#undef BIT_SHIFT_8
#undef BIT_SHIFT_0

public:
	/* must be 32-bit aligned */
	#pragma pack(push, 1)
	union {
		struct { u8 r, g, b, a; };
		u32 packed_value;
	};
	#pragma pack(pop)
};




CE_NAMESPACE_END


#ifdef _MSC_VER
	#pragma warning ( pop )
#endif




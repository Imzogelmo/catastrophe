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


class Color
{
public:
	Color()												: packed_value(0xff000000) {}
	Color( ubyte gray, ubyte alpha )					{ packed_value = _Pack( gray, gray, gray, alpha ); }
	Color( ubyte r, ubyte g, ubyte b, ubyte a = 255 )	{ packed_value = _Pack( r, g, b, a ); }
	Color( const Colorf &c )							{ packed_value = _Pack( c ); }
	Color( const HSVColor &c );
	Color( const HSLColor &c );

	Color &operator = ( const Colorf &c ) { packed_value = _Pack( c ); return *this; }
	Color &operator = ( uint val ) { packed_value = val; return *this; }
	Color &operator = ( const HSVColor &c );
	Color &operator = ( const HSLColor &c );

	ubyte		&operator [] ( int i )			{ return *(&r + i); }
	const ubyte &operator [] ( int i ) const	{ return *(&r + i); }

	Color operator - () const { return Color( 255 - r, 255 - g, 255 - b, a ); }
	Color operator + () const { return Color( 255 - r, 255 - g, 255 - b, a ); }

	bool operator == ( const Color &c )	const { return (packed_value == c.packed_value); }
	bool operator != ( const Color &c )	const { return (packed_value != c.packed_value); }

	uint Rgba() const { return packed_value; }
	uint Bgra() const { return _Pack( b, g, r, a ); }
	uint Argb() const { return _Pack( a, r, g, b ); }
	uint Abgr()	const { return _Pack( a, b, g, r ); }

	void Set( ubyte r, ubyte g, ubyte b, ubyte a ) { packed_value = _Pack( r, g, b, a ); }
	void Set( const Color &c ) { *this = c; }
	void Set( const Colorf &c ) { packed_value = _Pack(c); }

	void Clamp( const Color &min, const Color &max )
	{
		Math::FastClamp(r, min.r, max.r);
		Math::FastClamp(g, min.g, max.g);
		Math::FastClamp(b, min.b, max.b);
		Math::FastClamp(a, min.a, max.a);
	}

	Color Negative() const
	{
		return Color( (255 - r), (255 - g), (255 - b), a );
	}

	Color Grayscale( bool average = false ) const
	{
		if( average )
			return Color( (ubyte)((int)(r + g + b) / 3), a );

		return Color( (ubyte)(((299 * (int)r) + (587 * (int)g) + (114 * (int)b)) / 1000), a );
	}

	Colorf ToColorf()	const;
	Vector4 ToVector4() const;
	Vector3 ToVector3() const;

	static Color Lerp( const Color& c1, const Color& c2, float t);

	static Color AliceBlue( ubyte alpha = 255 )		{ return Color(240, 248, 255, alpha); }
	static Color AntiqueWhite( ubyte alpha = 255 )	{ return Color(250, 235, 215, alpha); }
	static Color Aqua( ubyte alpha = 255 )			{ return Color(  0, 255, 255, alpha); }
	static Color Aquamarine( ubyte alpha = 255 )		{ return Color(127, 255, 212, alpha); }
	static Color Azure( ubyte alpha = 255 )			{ return Color(240, 255, 255, alpha); }
	static Color Beige( ubyte alpha = 255 )			{ return Color(245, 245, 220, alpha); }
	static Color Bisque( ubyte alpha = 255 )			{ return Color(255, 228, 196, alpha); }
	static Color Black( ubyte alpha = 255 )			{ return Color(  0, 0, 0, alpha); }
	static Color BlanchedAlmond( ubyte alpha = 255 )	{ return Color(255, 235, 205, alpha); }
	static Color Blue( ubyte alpha = 255 )			{ return Color(  0, 0, 255, alpha); }
	static Color BlueViolet( ubyte alpha = 255 )		{ return Color(138, 43, 226, alpha); }
	static Color Brown( ubyte alpha = 255 )			{ return Color(165, 42, 42, alpha); }
	static Color Burlywood( ubyte alpha = 255 )		{ return Color(222, 184, 135, alpha); }
	static Color CadetBlue( ubyte alpha = 255 )		{ return Color( 95, 158, 160, alpha); }
	static Color Chartreuse( ubyte alpha = 255 )		{ return Color(127, 255, 0, alpha); }
	static Color Chocolate( ubyte alpha = 255 )		{ return Color(210, 105, 30, alpha); }
	static Color Coral( ubyte alpha = 255 )			{ return Color(255, 127, 80, alpha); }
	static Color CornflowerBlue( ubyte alpha = 255 )	{ return Color(100, 149, 237, alpha); }
	static Color Cornsilk( ubyte alpha = 255 )		{ return Color(255, 248, 220, alpha); }
	static Color Crimson( ubyte alpha = 255 )			{ return Color(220, 20, 60, alpha); }
	static Color Cyan( ubyte alpha = 255 )			{ return Color(  0, 255, 255, alpha); }
	static Color DarkBlue( ubyte alpha = 255 )		{ return Color(  0, 0, 139, alpha); }
	static Color DarkCyan( ubyte alpha = 255 )		{ return Color(  0, 139, 139, alpha); }
	static Color DarkGoldenrod( ubyte alpha = 255 )	{ return Color(184, 134, 11, alpha); }
	static Color DarkGray( ubyte alpha = 255 )		{ return Color(169, 169, 169, alpha); }
	static Color DarkGreen( ubyte alpha = 255 )		{ return Color(  0, 100, 0, alpha); }
	static Color DarkKhaki( ubyte alpha = 255 )		{ return Color(189, 183, 107, alpha); }
	static Color DarkMagenta( ubyte alpha = 255 )		{ return Color(139, 0, 139, alpha); }
	static Color DarkOliveGreen( ubyte alpha = 255 )	{ return Color( 85, 107, 47, alpha); }
	static Color DarkOrange( ubyte alpha = 255 )		{ return Color(255, 140, 0, alpha); }
	static Color DarkOrchid( ubyte alpha = 255 )		{ return Color(153, 50, 204, alpha); }
	static Color DarkRed( ubyte alpha = 255 )			{ return Color(139, 0, 0, alpha); }
	static Color DarkSalmon( ubyte alpha = 255 )		{ return Color(233, 150, 122, alpha); }
	static Color DarkSeaGreen( ubyte alpha = 255 )	{ return Color(143, 188, 143, alpha); }
	static Color DarkSlateBlue( ubyte alpha = 255 )	{ return Color( 72, 61, 139, alpha); }
	static Color DarkSlateGray( ubyte alpha = 255 )	{ return Color( 47, 79, 79, alpha); }
	static Color DarkTurquoise( ubyte alpha = 255 )	{ return Color(  0, 206, 209, alpha); }
	static Color DarkViolet( ubyte alpha = 255 )		{ return Color(148, 0, 211, alpha); }
	static Color DeepPink( ubyte alpha = 255 )		{ return Color(255, 20, 147, alpha); }
	static Color DeepSkyBlue( ubyte alpha = 255 )		{ return Color(  0, 191, 255, alpha); }
	static Color DimGray( ubyte alpha = 255 )			{ return Color(105, 105, 105, alpha); }
	static Color DodgerBlue( ubyte alpha = 255 )		{ return Color( 30, 144, 255, alpha); }
	static Color Firebrick( ubyte alpha = 255 )		{ return Color(178, 34, 34, alpha); }
	static Color FloralWhite( ubyte alpha = 255 )		{ return Color(255, 250, 240, alpha); }
	static Color ForestGreen( ubyte alpha = 255 )		{ return Color( 34, 139, 34, alpha); }
	static Color Fuchsia( ubyte alpha = 255 )			{ return Color(255, 0, 255, alpha); }
	static Color Gainsboro( ubyte alpha = 255 )		{ return Color(220, 220, 220, alpha); }
	static Color GhostWhite( ubyte alpha = 255 )		{ return Color(248, 248, 255, alpha); }
	static Color Gold( ubyte alpha = 255 )			{ return Color(255, 215, 0, alpha); }
	static Color Goldenrod( ubyte alpha = 255 )		{ return Color(218, 165, 32, alpha); }
	static Color Gray( ubyte alpha = 255 )			{ return Color(128, 128, 128, alpha); }
	static Color Green( ubyte alpha = 255 )			{ return Color(  0, 128, 0, alpha); }
	static Color GreenYellow( ubyte alpha = 255 )		{ return Color(173, 255, 47, alpha); }
	static Color Honeydew( ubyte alpha = 255 )		{ return Color(240, 255, 240, alpha); }
	static Color HotPink( ubyte alpha = 255 )			{ return Color(255, 105, 180, alpha); }
	static Color IndianRed( ubyte alpha = 255 )		{ return Color(205, 92, 92, alpha); }
	static Color Indigo( ubyte alpha = 255 )			{ return Color( 75, 0, 130, alpha); }
	static Color Ivory( ubyte alpha = 255 )			{ return Color(255, 255, 240, alpha); }
	static Color Khaki( ubyte alpha = 255 )			{ return Color(240, 230, 140, alpha); }
	static Color Lavender( ubyte alpha = 255 )		{ return Color(230, 230, 250, alpha); }
	static Color LavenderBlush( ubyte alpha = 255 )	{ return Color(255, 240, 245, alpha); }
	static Color LawnGreen( ubyte alpha = 255 )		{ return Color(124, 252, 0, alpha); }
	static Color LemonChiffon( ubyte alpha = 255 )	{ return Color(255, 250, 205, alpha); }
	static Color LightBlue( ubyte alpha = 255 )		{ return Color(173, 216, 230, alpha); }
	static Color LightCoral( ubyte alpha = 255 )		{ return Color(240, 128, 128, alpha); }
	static Color LightCyan( ubyte alpha = 255 )		{ return Color(224, 255, 255, alpha); }
	static Color LightGoldenrodYellow( ubyte alpha = 255 ) { return Color(250, 250, 210, alpha); }
	static Color LightGray( ubyte alpha = 255 )		{ return Color(211, 211, 211, alpha); }
	static Color LightGreen( ubyte alpha = 255 )		{ return Color(144, 238, 144, alpha); }
	static Color LightGrey( ubyte alpha = 255 )		{ return Color(211, 211, 211, alpha); }
	static Color LightPink( ubyte alpha = 255 )		{ return Color(255, 182, 193, alpha); }
	static Color LightSalmon( ubyte alpha = 255 )		{ return Color(255, 160, 122, alpha); }
	static Color LightSeaGreen( ubyte alpha = 255 )	{ return Color( 32, 178, 170, alpha); }
	static Color LightSkyBlue( ubyte alpha = 255 )	{ return Color(135, 206, 250, alpha); }
	static Color LightSlateGray( ubyte alpha = 255 )	{ return Color(119, 136, 153, alpha); }
	static Color LightSteelBlue( ubyte alpha = 255 )	{ return Color(176, 196, 222, alpha); }
	static Color LightYellow( ubyte alpha = 255 )		{ return Color(255, 255, 224, alpha); }
	static Color Lime( ubyte alpha = 255 )			{ return Color(  0, 255, 0, alpha); }
	static Color LimeGreen( ubyte alpha = 255 )		{ return Color( 50, 205, 50, alpha); }
	static Color Linen( ubyte alpha = 255 )			{ return Color(250, 240, 230, alpha); }
	static Color Magenta( ubyte alpha = 255 )			{ return Color(255, 0, 255, alpha); }
	static Color Maroon( ubyte alpha = 255 )			{ return Color(128, 0, 0, alpha); }
	static Color MediumAquamarine( ubyte alpha = 255 ) { return Color(102, 205, 170, alpha); }
	static Color MediumBlue( ubyte alpha = 255 )		{ return Color(  0, 0, 205, alpha); }
	static Color MediumOrchid( ubyte alpha = 255 )	{ return Color(186, 85, 211, alpha); }
	static Color MediumPurple( ubyte alpha = 255 )	{ return Color(147, 112, 219, alpha); }
	static Color MediumSeaGreen( ubyte alpha = 255 )	{ return Color( 60, 179, 113, alpha); }
	static Color MediumSlateBlue( ubyte alpha = 255 ) { return Color(123, 104, 238, alpha); }
	static Color MediumSpringGreen( ubyte alpha = 255 ) { return Color( 0, 250, 154, alpha); }
	static Color MediumTurquoise( ubyte alpha = 255 ) { return Color( 72, 209, 204, alpha); }
	static Color MediumVioletred( ubyte alpha = 255 ) { return Color(199, 21, 133, alpha); }
	static Color MidnightBlue( ubyte alpha = 255 )	{ return Color( 25, 25, 112, alpha); }
	static Color MintCream( ubyte alpha = 255 )		{ return Color(245, 255, 250, alpha); }
	static Color MistyRose( ubyte alpha = 255 )		{ return Color(255, 228, 225, alpha); }
	static Color Moccasin( ubyte alpha = 255 )		{ return Color(255, 228, 181, alpha); }
	static Color NavajoWhite( ubyte alpha = 255 )		{ return Color(255, 222, 173, alpha); }
	static Color Navy( ubyte alpha = 255 )			{ return Color( 0, 0, 128, alpha); }
	static Color OldLace( ubyte alpha = 255 )			{ return Color(253, 245, 230, alpha); }
	static Color Olive( ubyte alpha = 255 )			{ return Color(128, 128, 0, alpha); }
	static Color OliveDrab( ubyte alpha = 255 )		{ return Color(107, 142, 35, alpha); }
	static Color Orange( ubyte alpha = 255 )			{ return Color(255, 165, 0, alpha); }
	static Color OrangeRed( ubyte alpha = 255 )		{ return Color(255, 69, 0, alpha); }
	static Color Orchid( ubyte alpha = 255 )			{ return Color(218, 112, 214, alpha); }
	static Color PaleGoldenrod( ubyte alpha = 255 )	{ return Color(238, 232, 170, alpha); }
	static Color PaleGreen( ubyte alpha = 255 )		{ return Color(152, 251, 152, alpha); }
	static Color PaleTurquoise( ubyte alpha = 255 )	{ return Color(175, 238, 238, alpha); }
	static Color PaleVioletRed( ubyte alpha = 255 )	{ return Color(219, 112, 147, alpha); }
	static Color PapayaWhip( ubyte alpha = 255 )		{ return Color(255, 239, 213, alpha); }
	static Color PeachPuff( ubyte alpha = 255 )		{ return Color(255, 218, 185, alpha); }
	static Color Peru( ubyte alpha = 255 )			{ return Color(205, 133, 63, alpha); }
	static Color Pink( ubyte alpha = 255 )			{ return Color(255, 192, 203, alpha); }
	static Color Plum( ubyte alpha = 255 )			{ return Color(221, 160, 221, alpha); }
	static Color PowderBlue( ubyte alpha = 255 )		{ return Color(176, 224, 230, alpha); }
	static Color Purple( ubyte alpha = 255 )			{ return Color(128, 0, 128, alpha); }
	static Color Red( ubyte alpha = 255 )				{ return Color(255, 0, 0, alpha); }
	static Color RosyBrown( ubyte alpha = 255 )		{ return Color(188, 143, 143, alpha); }
	static Color RoyalBlue( ubyte alpha = 255 )		{ return Color( 65, 105, 225, alpha); }
	static Color SaddleBrown( ubyte alpha = 255 )		{ return Color(139, 69, 19, alpha); }
	static Color Salmon( ubyte alpha = 255 )			{ return Color(250, 128, 114, alpha); }
	static Color SandyBrown( ubyte alpha = 255 )		{ return Color(244, 164, 96, alpha); }
	static Color SeaGreen( ubyte alpha = 255 )		{ return Color( 46, 139, 87, alpha); }
	static Color SeaShell( ubyte alpha = 255 )		{ return Color(255, 245, 238, alpha); }
	static Color Sienna( ubyte alpha = 255 )			{ return Color(160, 82, 45, alpha); }
	static Color Silver( ubyte alpha = 255 )			{ return Color(192, 192, 192, alpha); }
	static Color SkyBlue( ubyte alpha = 255 )			{ return Color(135, 206, 235, alpha); }
	static Color SlateBlue( ubyte alpha = 255 )		{ return Color(106, 90, 205, alpha); }
	static Color SlateGray( ubyte alpha = 255 )		{ return Color(112, 128, 144, alpha); }
	static Color Snow( ubyte alpha = 255 )			{ return Color(255, 250, 250, alpha); }
	static Color SpringGreen( ubyte alpha = 255 )		{ return Color(  0, 255, 127, alpha); }
	static Color SteelBlue( ubyte alpha = 255 )		{ return Color( 70, 130, 180, alpha); }
	static Color Tan( ubyte alpha = 255 )				{ return Color(210, 180, 140, alpha); }
	static Color Teal( ubyte alpha = 255 )			{ return Color(  0, 128, 128, alpha); }
	static Color Thistle( ubyte alpha = 255 )			{ return Color(216, 191, 216, alpha); }
	static Color Tomato( ubyte alpha = 255 )			{ return Color(255, 99, 71, alpha); }
	static Color Turquoise( ubyte alpha = 255 )		{ return Color( 64, 224, 208, alpha); }
	static Color Violet( ubyte alpha = 255 )			{ return Color(238, 130, 238, alpha); }
	static Color Wheat( ubyte alpha = 255 )			{ return Color(245, 222, 179, alpha); }
	static Color White( ubyte alpha = 255 )			{ return Color(255, 255, 255, alpha); }
	static Color WhiteSmoke( ubyte alpha = 255 )		{ return Color(245, 245, 245, alpha); }
	static Color Yellow( ubyte alpha = 255 )			{ return Color(255, 255, 0, alpha); }
	static Color YellowGreen( ubyte alpha = 255 )		{ return Color(154, 205, 50, alpha); }

	static Color TransparentWhite() { return Color(255, 255, 255, 0); }
	static Color TransparentBlack() { return Color(0, 0, 0, 0); }

protected:
	static uint _Pack( float r, float g, float b, float a )
	{
		return (uint) ( (_ToByte(a) << 24) | (_ToByte(b) << 16) | (_ToByte(g) <<  8) | (_ToByte(r)) );
	}

	static uint _Pack( int r, int g, int b, int a )
	{
		return (uint) ( (a<<24) | (b<<16) | (g<<8) | r );
	}

	static uint _Pack( ubyte r, ubyte g, ubyte b, ubyte a )
	{
		return (uint) ( (a<<24) | (b<<16) | (g<<8) | r );
	}

	static uint _Pack( const Colorf &c )
	{
		return _Pack( c.r, c.g, c.b, c.a );
	}

	static ubyte _ToByte( float t )
	{
		return (ubyte) (t * 255.0f);
	}

	static float _ToFloat( ubyte t )
	{
		const float inv = 1.f / 255.f;
		return (float) (t * inv);
	}

public:
	/* must be 32-bit aligned */
	#pragma pack(push, 1)
	union {
		struct { ubyte r, g, b, a; };
		uint packed_value;
	};
	#pragma pack(pop)
};




CE_NAMESPACE_END


#ifdef _MSC_VER
	#pragma warning ( pop )
#endif




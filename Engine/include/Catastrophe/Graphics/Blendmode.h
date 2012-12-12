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

#include "../Common.h"

#ifdef _MSC_VER
	#pragma warning ( push )
	#pragma warning ( disable : 4201 )
#endif

CE_NAMESPACE_BEGIN


class BlendMode
{
public:

	BlendMode() : src(0x0302), dst(0x0303) {}
	BlendMode( uint val ) : value(val) {}
	BlendMode( ushort sFactor, ushort dFactor ) : src(sFactor), dst(dFactor) {}

	BlendMode &operator = ( uint val ) { value = val; return *this; }

	bool operator == ( const BlendMode &b ) const { return (value == b.value); }
	bool operator != ( const BlendMode &b ) const { return (value != b.value); }
	
	static BlendMode Alpha;
	static BlendMode PreMultipliedAlpha;
	static BlendMode Additive;
	static BlendMode Subtractive;
	static BlendMode Multiply;
	static BlendMode InverseAlpha;

	void Apply() const;
	BlendMode &Separate( ushort sFactor, ushort dFactor )
	{
		src = sFactor, dst = dFactor;
		return *this;
	}

	#pragma pack(push, 1)
	union
	{
		struct { ushort src, dst; };
		uint value;
	};
	#pragma pack(pop)
};


CE_NAMESPACE_END


#ifdef _MSC_VER
	#pragma warning ( pop )
#endif


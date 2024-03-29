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

#include "Graphics/BlendMode.h"
#include "Graphics/OpenGL.h"

CE_NAMESPACE_BEGIN


BlendMode BlendMode::Alpha				= BlendMode( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
BlendMode BlendMode::PreMultipliedAlpha = BlendMode( GL_ONE, GL_ONE_MINUS_SRC_ALPHA );
BlendMode BlendMode::Additive			= BlendMode( GL_SRC_ALPHA, GL_ONE );
BlendMode BlendMode::Subtractive		= BlendMode( GL_ZERO, GL_ONE_MINUS_SRC_COLOR );
BlendMode BlendMode::Multiply			= BlendMode( GL_DST_COLOR, GL_ZERO );
BlendMode BlendMode::InverseAlpha		= BlendMode( GL_ONE_MINUS_DST_ALPHA, GL_DST_ALPHA );


void BlendMode::Apply() const
{
	glBlendFunc( src, dst );
}




CE_NAMESPACE_END


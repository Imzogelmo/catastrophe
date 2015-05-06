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

#include "Catastrophe/Core/Math/Matrix.h"
#include "Graphics/PrimitiveBatch.h"
#include "Graphics/OpenGL.h"

CE_NAMESPACE_BEGIN


void PrimitiveBatch::Reserve( u32 reserve )
{
	m_queue.Reserve( reserve );
}


void PrimitiveBatch::Clear()
{
	for( vec_type::Iterator it = m_queue.begin(); it != m_queue.end(); ++it )
		it->Clear();

	m_queue.Clear();
}


void PrimitiveBatch::Begin()
{
	Clear();
}


void PrimitiveBatch::DrawPrimitive( const Primitive &primitive )
{
	//TODO: need to cache the memory used to prevent deallocations.
	if( !m_queue.Empty() )
	{
		Primitive &p = m_queue.back();

		//find if previous is batch-compatible with current
		if( p.GetPrimitiveType() == primitive.GetPrimitiveType() && p.GetBlendMode() == primitive.GetBlendMode() )
		{
			switch( primitive.GetPrimitiveType() )
			{
				case GL_POINTS:
				case GL_LINES:
				case GL_TRIANGLES:
				case GL_QUADS:
				{
					p += primitive;
				}
			}
		}
	}

	m_queue.Add(primitive);
}


void PrimitiveBatch::Render()	
{
	if( m_queue.Empty() )
		return;

	glDisable( GL_TEXTURE_2D );
	for( vec_type::Iterator it = m_queue.begin(); it != m_queue.end(); ++it )
		it->Render();
}


void PrimitiveBatch::Render( const Matrix& transformation )
{
	glPushMatrix();
		glMultMatrixf( &transformation.m[0] );
		Render();
	glPopMatrix();
}


void PrimitiveBatch::End()
{
	//Clear();
	//glFlush();
}


u32 PrimitiveBatch::GetVertexCount() const
{
	u32 count(0);
	for( vec_type::ConstIterator it = m_queue.begin(); it != m_queue.end(); ++it )
		count += it->Size();

	return count;
}


CE_NAMESPACE_END


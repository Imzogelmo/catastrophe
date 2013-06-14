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

#include "Graphics/FBORenderTarget.h"
#include "Graphics/OpenGL.h"
//#include "Math/Matrix.h"

CE_NAMESPACE_BEGIN


FBORenderTarget::FBORenderTarget() :
	m_texturePtr(0),
	m_fbo(0)
{
	InternalGenerateFramebufferObject();
}


FBORenderTarget::~FBORenderTarget()
{
	if( m_fbo != 0 )
	{
		glDeleteFramebuffersEXT( 1, &m_fbo );
	}
}


void FBORenderTarget::AttachTexture( Texture* texture )
{
	CE_ASSERT(texture != 0);
	m_texturePtr = texture;

	if( m_texturePtr && m_fbo != 0 )
	{
		Bind();
		glFramebufferTexture2DEXT( GL_FRAMEBUFFER_EXT,
			GL_COLOR_ATTACHMENT0_EXT,
			GL_TEXTURE_2D,
			m_texturePtr->GetTextureID(),
			0
		);
		Unbind();
	}
}


void FBORenderTarget::RemoveTexture()
{
	m_texturePtr = 0;
}


Texture* FBORenderTarget::GetTexture() const
{
	return m_texturePtr;
}


void FBORenderTarget::Bind()
{
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_fbo);
	glClear(GL_COLOR_BUFFER_BIT);

	GLfloat mat[16] = {
		1.f, 0.f, 0.f, 0.f,
		0.f, -1.f, 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		0.f, 0.f, 0.f, 1.f
	};

	//glPushMatrix();
	glPushAttrib(GL_VIEWPORT_BIT);
	glViewport(0, 0, m_texturePtr->Width(), m_texturePtr->Height());

	//glMatrixMode(GL_TEXTURE);
	//glMatrixMode(GL_MODELVIEW);
	//glMultMatrixf(mat);
	//glMatrixMode(GL_MODELVIEW);
	//glViewport(0, 0, m_texturePtr->Width(), m_texturePtr->Height());

}


void FBORenderTarget::Unbind()
{
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

	//glPopMatrix();
	glPopAttrib();
}


bool FBORenderTarget::InternalGenerateFramebufferObject()
{
	//if( m_fbo != 0 )
		glGenFramebuffersEXT( 1, &m_fbo );

	return true;
}


CE_NAMESPACE_END


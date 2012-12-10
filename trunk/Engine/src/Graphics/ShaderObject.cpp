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


#include "Graphics/ShaderObject.h"
#include "Graphics/OpenGL.h"

#include "IO/File.h"

CE_NAMESPACE_BEGIN


ShaderObjectBase::ShaderObjectBase()
	: m_name(), m_source(), m_infolog(), m_shader_object(0), m_program_type(0), m_is_compiled(false)
{
}


VertexShader::VertexShader() : ShaderObjectBase()
{
	m_program_type = GL_VERTEX_SHADER;
}


FragmentShader::FragmentShader() : ShaderObjectBase()
{
	m_program_type = GL_FRAGMENT_SHADER;
}


void ShaderObjectBase::Dispose()
{
	if( m_shader_object > 0 )
	{
		GLboolean isShader = glIsShader( m_shader_object );
		if( isShader == GL_TRUE )
			glDeleteShader( m_shader_object );

		m_shader_object = 0;
	}

	m_source.clear();
	m_infolog.clear();
}


bool ShaderObjectBase::LoadFromMemory( const fc::string& code )
{
	Dispose();
	m_source = code;

	return Compile();
}


bool ShaderObjectBase::LoadFromFile( const fc::string& filename )
{
	Dispose();

	File f(filename, FileRead);
	if(!f.IsOpen())
	{
		//Log( "Failed to open %s " + filename );
		return false;
	}

	size_t size = f.Size();
	m_source.resize(size);
	if( f.Read(&m_source[0], size) != size )
	{
		printf( "Failed to load shader program." );
		return false;
	}

	return Compile();
}


bool ShaderObjectBase::Compile()
{
	InternalCreateShaderObject();

	const int length = m_source.size();
	const char *source = m_source.c_str();
	glShaderSource( m_shader_object, 1, &source, &length );
	glCompileShader( m_shader_object );

	glint status(0);
	glGetShaderiv( m_shader_object, GL_COMPILE_STATUS, &status );

	m_is_compiled = (status == GL_TRUE ? true : false);
	if(!m_is_compiled)
	{
		//Log("Fail");
	}

	return m_is_compiled;
}


const fc::string& ShaderObjectBase::GetInfoLog()
{
	int infolog_length(0);
	int length(0);

	if( m_shader_object > 0 && m_infolog.empty() && glIsShader(m_shader_object) )
	{
		glGetShaderiv( m_shader_object, GL_INFO_LOG_LENGTH, &length );
		m_infolog.resize( length );

		glGetShaderInfoLog( m_shader_object, length, &infolog_length, &m_infolog[0] );
	}

	return m_infolog;
}


const fc::string& ShaderObjectBase::GetSource()
{
	return m_source;
}


void ShaderObjectBase::InternalCreateShaderObject()
{
	if( m_shader_object == 0 && m_program_type > 0)
	{
		m_shader_object = glCreateShader( m_program_type );
	}
}


CE_NAMESPACE_END


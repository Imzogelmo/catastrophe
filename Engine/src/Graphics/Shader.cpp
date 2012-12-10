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

#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Vector4.h"
#include "Math/Color.h"
#include "Math/Colorf.h"
#include "Math/Matrix.h"

#include "Graphics/ShaderObject.h"
#include "Graphics/Shader.h"
#include "Graphics/OpenGL.h"

CE_NAMESPACE_BEGIN


Shader::Shader( VertexShader* vertex_shader, FragmentShader* fragment_shader ) :
	m_vertex_shader(vertex_shader),
	m_fragment_shader(fragment_shader),
	m_program_object(0),
	m_infolog(),
	m_uniform_locations(),
	m_linked(false),
	m_link_error(false)
{
}


void Shader::Dispose()
{
	//TODO: these can be shared shaders and should only be destroyed by the resource manager...
	//m_vertex_shader->Dispose();
	//m_fragment_shader->Dispose();

	if( m_program_object > 0 )
	{
		GLboolean isProgram = glIsProgram( m_program_object );
		if( isProgram == GL_TRUE )
			glDeleteProgram( m_program_object );

		m_program_object = 0;
	}

	m_infolog.clear();
}


void Shader::SetVertexShader( VertexShader* vertex_shader )
{
	//TODO: re-link program
	m_vertex_shader = vertex_shader;
}


void Shader::SetFragmentShader( FragmentShader* fragment_shader )
{
	m_fragment_shader = fragment_shader;
}


void Shader::Begin()
{
	if( !m_fragment_shader || !m_vertex_shader )
	{
		Log("Shader::Begin() error: shader is null.");
		return;
	}

	if( m_link_error )
	{
		return;
	}

	if( (!m_linked && !m_link_error) || m_program_object == 0 )
	{
		if( m_fragment_shader->IsCompiled() && m_vertex_shader->IsCompiled() )
		{
			if( !Link() )
				return;
		}
		else return;
	}

	glUseProgram( m_program_object );
}


void Shader::End()
{
	glUseProgram(0);
}


int Shader::GetUniformLocation(const fc::string& name)
{
	map_type::iterator it = m_uniform_locations.find(name);
	if( it != m_uniform_locations.end() )
	{
		return it->second;
	}

	int location = glGetUniformLocation( m_program_object, name.c_str() );
	if( location > 0 )
		m_uniform_locations[ name ] = location;

	return location;
}


bool Shader::GetUniform( const fc::string& name, float* values )
{
	int location = GetUniformLocation( name );
	if( location < 0 )
		return false;

	glGetUniformfv( m_program_object, location, values );
	return true;
}


bool Shader::GetUniform( const fc::string& name, int* values )
{
	int location = GetUniformLocation( name );
	if( location < 0 )
		return false;

	glGetUniformiv( m_program_object, location, values );
	return true;
}


bool Shader::SetUniform( const fc::string& name, float v0 )
{
	int location = GetUniformLocation( name );
	if( location < 0 )
		return false;

	glUniform1f( location, v0 );
	return true;
}


bool Shader::SetUniform( const fc::string& name, float v0, float v1 )
{
	int location = GetUniformLocation( name );
	if( location < 0 )
		return false;

	glUniform2f( location, v0, v1 );
	return true;
}


bool Shader::SetUniform( const fc::string& name, float v0, float v1, float v2 )
{
	int location = GetUniformLocation( name );
	if( location < 0 )
		return false;

	glUniform3f( location, v0, v1, v2 );
	return true;
}


bool Shader::SetUniform( const fc::string& name, float v0, float v1, float v2, float v3 )
{
	int location = GetUniformLocation( name );
	if( location < 0 )
		return false;

	glUniform4f( location, v0, v1, v2, v3 );
	return true;
}


bool Shader::SetUniform( const fc::string& name, int v0 )
{
	int location = GetUniformLocation( name );
	if( location < 0 )
		return false;

	glUniform1i( location, v0 );
	return true;
}


bool Shader::SetUniform( const fc::string& name, int v0, int v1 )
{
	int location = GetUniformLocation( name );
	if( location < 0 )
		return false;

	glUniform2i( location, v0, v1 );
	return true;
}


bool Shader::SetUniform( const fc::string& name, int v0, int v1, int v2 )
{
	int location = GetUniformLocation( name );
	if( location < 0 )
		return false;

	glUniform3i( location, v0, v1, v2 );
	return true;
}


bool Shader::SetUniform( const fc::string& name, int v0, int v1, int v2, int v3 )
{
	int location = GetUniformLocation( name );
	if( location < 0 )
		return false;

	glUniform4i( location, v0, v1, v2, v3 );
	return true;
}


bool Shader::SetUniform( const fc::string& name, const Vector2& v )
{
	return SetUniform( name, v.x, v.y );
}


bool Shader::SetUniform( const fc::string& name, const Vector3& v )
{
	return SetUniform( name, v.x, v.y, v.z );
}


bool Shader::SetUniform( const fc::string& name, const Vector4& v )
{
	return SetUniform( name, v.x, v.y, v.z, v.w );
}


bool Shader::SetUniformMatrix( const fc::string& name, const Matrix& matrix )
{
	int location = GetUniformLocation( name );
	if( location < 0 )
		return false;

	glUniformMatrix4fv( location, 1, GL_FALSE, &matrix[0] );
	return true;
}


bool Shader::SetUniformMatrix2fv( const fc::string& name, int count, bool transpose, const float* m )
{
	int location = GetUniformLocation( name );
	if( location < 0 )
		return false;

	glUniformMatrix2fv( location, count, transpose ? GL_TRUE : GL_FALSE, m );
	return true;
}


bool Shader::SetUniformMatrix3fv( const fc::string& name, int count, bool transpose, const float* m )
{
	int location = GetUniformLocation( name );
	if( location < 0 )
		return false;

	glUniformMatrix3fv( location, count, transpose ? GL_TRUE : GL_FALSE, m );
	return true;
}


bool Shader::SetUniformMatrix4fv( const fc::string& name, int count, bool transpose, const float* m )
{
	int location = GetUniformLocation( name );
	if( location < 0 )
		return false;

	glUniformMatrix4fv( location, count, transpose ? GL_TRUE : GL_FALSE, m );
	return true;
}


bool Shader::Link()
{
	InternalCreateProgramObject();
	if( !m_fragment_shader || !m_vertex_shader )
	{
		Log("Shader::Link() error: shader is null.");
		return false;
	}

	m_link_error = false;
	if( m_linked )
	{
		m_infolog.clear();
		glDetachShader( m_program_object, m_vertex_shader->GetObject() );
		glDetachShader( m_program_object, m_fragment_shader->GetObject() );
	}

	glAttachShader( m_program_object, m_vertex_shader->GetObject() );
	glAttachShader( m_program_object, m_fragment_shader->GetObject() );
	
	glLinkProgram( m_program_object );

	glint status(0);
	glGetProgramiv( m_program_object, GL_LINK_STATUS, &status );

	m_linked = (status == GL_TRUE ? true : false);
	m_link_error = !m_linked;

	return m_linked;
}


const fc::string& Shader::GetInfoLog()
{
	int infolog_length(0);
	int length(0);

	if( m_program_object > 0 && m_infolog.empty() && glIsProgram(m_program_object) )
	{
		glGetProgramiv( m_program_object, GL_INFO_LOG_LENGTH, &length );
		m_infolog.resize( length );

		glGetProgramInfoLog( m_program_object, length, &infolog_length, &m_infolog[0] );
	}

	return m_infolog;
}


void Shader::InternalCreateProgramObject()
{
	if( m_program_object == 0 )
	{
		m_program_object = glCreateProgram();
	}
}




CE_NAMESPACE_END


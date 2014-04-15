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


Shader::Shader( VertexShader* vertexShader, FragmentShader* fragmentShader ) :
	m_vertexShader(0),
	m_fragmentShader(0),
	m_programObject(0),
	m_infolog(),
	m_uniformLocations(),
	m_vertexShaderAttached(false),
	m_fragmentShaderAttached(false),
	m_isDirty(false),
	m_isLinked(false)
{
	SetVertexShader(vertexShader);
	SetFragmentShader(fragmentShader);
}


void Shader::Dispose()
{
	//TODO: these can be shared shaders and should only be destroyed by the resource manager...
	//m_vertexShader->Dispose();
	//m_fragmentShader->Dispose();

	if( m_programObject > 0 )
	{
		GLboolean isProgram = glIsProgram( m_programObject );
		if( isProgram == GL_TRUE )
			glDeleteProgram( m_programObject );

		m_programObject = 0;
	}

	m_infolog.clear();
}


void Shader::SetVertexShader( VertexShader* vertexShader )
{
	if( m_vertexShader != vertexShader )
	{
		if( m_vertexShader != 0 && m_vertexShaderAttached )
		{
			glDetachShader( m_programObject, m_vertexShader->GetObject() );
			m_vertexShaderAttached = false;
		}

		m_vertexShader = vertexShader;
		m_isDirty = true;
	}
}


void Shader::SetFragmentShader( FragmentShader* fragmentShader )
{
	m_fragmentShader = fragmentShader;
	if( m_fragmentShader != fragmentShader )
	{
		if( m_fragmentShader != 0 && m_fragmentShaderAttached )
		{
			glDetachShader( m_programObject, m_fragmentShader->GetObject() );
			m_fragmentShaderAttached = false;
		}

		m_fragmentShader = fragmentShader;
		m_isDirty = true;
	}
}


void Shader::Bind()
{
	if( m_isDirty )
		Link();

	if( !m_isLinked )
		return;

	glUseProgram( m_programObject );
}


void Shader::Unbind()
{
	glUseProgram(0);
}


int Shader::GetUniformLocation(const char* name)
{
	size_t stringHash = fc::fnv_hash(name);
	map_type::iterator it = m_uniformLocations.find(stringHash);
	if( it != m_uniformLocations.end() )
	{
		return it->second;
	}

	int location = glGetUniformLocation( m_programObject, name );
	if( location > 0 )
		m_uniformLocations[stringHash] = location;

	return location;
}


bool Shader::GetUniform( const char* name, float* values )
{
	int location = GetUniformLocation( name );
	if( location < 0 )
		return false;

	glGetUniformfv( m_programObject, location, values );
	return true;
}


bool Shader::GetUniform( const char* name, int* values )
{
	int location = GetUniformLocation( name );
	if( location < 0 )
		return false;

	glGetUniformiv( m_programObject, location, values );
	return true;
}


bool Shader::SetUniform( const char* name, float v0 )
{
	int location = GetUniformLocation( name );
	if( location < 0 )
		return false;

	glUniform1f( location, v0 );
	return true;
}


bool Shader::SetUniform( const char* name, float v0, float v1 )
{
	int location = GetUniformLocation( name );
	if( location < 0 )
		return false;

	glUniform2f( location, v0, v1 );
	return true;
}


bool Shader::SetUniform( const char* name, float v0, float v1, float v2 )
{
	int location = GetUniformLocation( name );
	if( location < 0 )
		return false;

	glUniform3f( location, v0, v1, v2 );
	return true;
}


bool Shader::SetUniform( const char* name, float v0, float v1, float v2, float v3 )
{
	int location = GetUniformLocation( name );
	if( location < 0 )
		return false;

	glUniform4f( location, v0, v1, v2, v3 );
	return true;
}


bool Shader::SetUniform( const char* name, int v0 )
{
	int location = GetUniformLocation( name );
	if( location < 0 )
		return false;

	glUniform1i( location, v0 );
	return true;
}


bool Shader::SetUniform( const char* name, int v0, int v1 )
{
	int location = GetUniformLocation( name );
	if( location < 0 )
		return false;

	glUniform2i( location, v0, v1 );
	return true;
}


bool Shader::SetUniform( const char* name, int v0, int v1, int v2 )
{
	int location = GetUniformLocation( name );
	if( location < 0 )
		return false;

	glUniform3i( location, v0, v1, v2 );
	return true;
}


bool Shader::SetUniform( const char* name, int v0, int v1, int v2, int v3 )
{
	int location = GetUniformLocation( name );
	if( location < 0 )
		return false;

	glUniform4i( location, v0, v1, v2, v3 );
	return true;
}


bool Shader::SetUniform( const char* name, const Vector2& v )
{
	return SetUniform( name, v.x, v.y );
}


bool Shader::SetUniform( const char* name, const Vector3& v )
{
	return SetUniform( name, v.x, v.y, v.z );
}


bool Shader::SetUniform( const char* name, const Vector4& v )
{
	return SetUniform( name, v.x, v.y, v.z, v.w );
}


bool Shader::SetUniformMatrix( const char* name, const Matrix& matrix )
{
	int location = GetUniformLocation( name );
	if( location < 0 )
		return false;

	glUniformMatrix4fv( location, 1, GL_FALSE, &matrix[0] );
	return true;
}


bool Shader::SetUniformMatrix2fv( const char* name, int count, bool transpose, const float* m )
{
	int location = GetUniformLocation( name );
	if( location < 0 )
		return false;

	glUniformMatrix2fv( location, count, transpose ? GL_TRUE : GL_FALSE, m );
	return true;
}


bool Shader::SetUniformMatrix3fv( const char* name, int count, bool transpose, const float* m )
{
	int location = GetUniformLocation( name );
	if( location < 0 )
		return false;

	glUniformMatrix3fv( location, count, transpose ? GL_TRUE : GL_FALSE, m );
	return true;
}


bool Shader::SetUniformMatrix4fv( const char* name, int count, bool transpose, const float* m )
{
	int location = GetUniformLocation( name );
	if( location < 0 )
		return false;

	glUniformMatrix4fv( location, count, transpose ? GL_TRUE : GL_FALSE, m );
	return true;
}


bool Shader::Link()
{
	if( !m_fragmentShader && !m_vertexShader )
		return false;

	m_infolog.clear();
	InternalCreateProgramObject();

	// attach vertex shader
	if( m_vertexShader != 0 && m_vertexShader->IsCompiled() )
	{
		glAttachShader( m_programObject, m_vertexShader->GetObject() );
		m_vertexShaderAttached = true;
	}

	// attach fragment shader
	if( m_fragmentShader != 0 && m_fragmentShader->IsCompiled() )
	{
		glAttachShader( m_programObject, m_fragmentShader->GetObject() );
		m_fragmentShaderAttached = true;
	}

	glint status(0);
	glLinkProgram( m_programObject );
	glGetProgramiv( m_programObject, GL_LINK_STATUS, &status );

	m_isLinked = (status == GL_TRUE ? true : false);
	m_isDirty = false;

	return m_isLinked;
}


const fc::string& Shader::GetInfoLog()
{
	int infolog_length(0);
	int length(0);

	if( m_programObject > 0 && m_infolog.empty() && glIsProgram(m_programObject) )
	{
		glGetProgramiv( m_programObject, GL_INFO_LOG_LENGTH, &length );
		m_infolog.resize( length );

		glGetProgramInfoLog( m_programObject, length, &infolog_length, &m_infolog[0] );
	}

	return m_infolog;
}


int Shader::GetMaxTextureUnits()
{
	int maxTextureUnits;
	glGetIntegerv(GL_MAX_TEXTURE_COORDS_ARB, &maxTextureUnits);
	return maxTextureUnits;
}


void Shader::InternalCreateProgramObject()
{
	if( m_programObject == 0 )
	{
		m_programObject = glCreateProgram();
	}
}




CE_NAMESPACE_END


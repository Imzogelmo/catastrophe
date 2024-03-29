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

#include "Catastrophe/Core/Common.h"
#include "Catastrophe/Core/PlatformMath.h"
#include "Catastrophe/Core/Containers/String.h"
#include "Catastrophe/Core/Containers/StaticArrayMap.h"

#include "Catastrophe/Graphics/Common.h"
#include "Catastrophe/Graphics/ShaderObject.h"

#define MAX_SHADER_UNIFORM_VARIABLES 16

CE_NAMESPACE_BEGIN


class CE_API Shader
{
public:
	//typedef VectorMap< u32, int, Less<u32>, StaticVector<KeyValuePair<u32, int>, 16> > map_type;
	typedef StaticArrayMap<int, int, MAX_SHADER_UNIFORM_VARIABLES> map_type;

	Shader( VertexShader* vertex_shader = 0, FragmentShader* fragment_shader = 0 );

	void Dispose();
	void SetVertexShader( VertexShader* vertex_shader );
	void SetFragmentShader( FragmentShader* fragment_shader );

	VertexShader* GetVertexShader() const { return m_vertexShader; }
	FragmentShader* GetFragmentShader() const { return m_fragmentShader; }

	void Bind();
	void Unbind();

	bool Link();
	bool IsLinked() const { return m_isLinked; }
	bool IsDirty() const { return m_isDirty; }

	const String& GetInfoLog();
	int GetUniformLocation(const char* name);

	bool GetUniform( const char* name, float* values );
	bool GetUniform( const char* name, int* values );

	bool SetUniform( const char* name, float v0 );
	bool SetUniform( const char* name, float v0, float v1 );
	bool SetUniform( const char* name, float v0, float v1, float v2 );
	bool SetUniform( const char* name, float v0, float v1, float v2, float v3 );
	bool SetUniform( const char* name, int v0 );
	bool SetUniform( const char* name, int v0, int v1 );
	bool SetUniform( const char* name, int v0, int v1, int v2 );
	bool SetUniform( const char* name, int v0, int v1, int v2, int v3 );
	bool SetUniform( const char* name, const Vector2& v );
	bool SetUniform( const char* name, const Vector3& v );
	bool SetUniform( const char* name, const Vector4& v );
	bool SetUniformMatrix( const char* name, const Matrix& matrix );
	bool SetUniformMatrix2fv( const char* name, int count, bool transpose, const float* m );
	bool SetUniformMatrix3fv( const char* name, int count, bool transpose, const float* m );
	bool SetUniformMatrix4fv( const char* name, int count, bool transpose, const float* m );

	static int GetMaxTextureUnits();

protected:
	void InternalCreateProgramObject();

	VertexShader*	m_vertexShader;
	FragmentShader*	m_fragmentShader;
	u32				m_programObject;
	String			m_infolog;
	map_type		m_uniformLocations;
	bool			m_vertexShaderAttached;
	bool			m_fragmentShaderAttached;
	bool			m_isDirty;
	bool			m_isLinked;
};




CE_NAMESPACE_END


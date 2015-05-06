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
#include "Catastrophe/Core/Containers/String.h"

#include "Catastrophe/Graphics/Common.h"

CE_NAMESPACE_BEGIN


enum ShaderType
{
	VertexShaderType = 0x8B31,
	FragmentShaderType = 0x8B30
};


class CE_API ShaderObject
{
public:
	ShaderObject( ShaderType type );

	void Dispose();
	bool LoadFromFile( const String& filename );
	bool LoadFromMemory( const String& code );
	bool Compile();
	const String& GetSource();
	const String& GetInfoLog();

	u32 GetObject() const { return m_shader_object; }
	bool IsCompiled() const { return m_is_compiled; }

protected:
	void InternalCreateShaderObject();

	//ShaderType	m_type;
	String	m_name;
	String	m_source;
	String	m_infolog;
	u32		m_shader_object;
	ShaderType	m_program_type;
	bool		m_is_compiled;
};


class CE_API VertexShader : public ShaderObject
{
public:
	VertexShader();
};


class CE_API FragmentShader : public ShaderObject
{
public:
	FragmentShader();
};



CE_NAMESPACE_END


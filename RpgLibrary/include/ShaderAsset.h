// catastrophe rpg engine
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

#pragma once

#include "Catastrophe/Core/Containers/String.h"
#include "RpgCommon.h"


class RPG_API ShaderAsset
{
public:
	int id;

	ShaderAsset();
	~ShaderAsset();

	void SetName( const String& name ) { m_name = name; }
	void SetVertexShaderFilename( const String& filename ) { m_vertexFilename = filename; }
	void SetFragmentShaderFilename( const String& filename ) { m_fragmentFilename = filename; }
	const String& GetName() const { return m_name; }
	const String& GetVertexShaderFilename() const { return m_vertexFilename; }
	const String& GetFragmentShaderFilename() const { return m_fragmentFilename; }

	Shader* LoadShader();
	void ReleaseShader();

	void Serialize( AttributeWriter* f );
	void Deserialize( AttributeReader* f );

	int GetMemoryUsage() const;

protected:
	String		m_name;
	String		m_vertexFilename;
	String		m_fragmentFilename;

	Shader*			m_shader;
};


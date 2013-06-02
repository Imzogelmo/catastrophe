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

#include <fc/string.h>
#include "RpgCommon.h"


class RPG_API ShaderAsset
{
public:
	int id;

	ShaderAsset();
	~ShaderAsset();

	void SetName( const fc::string& name ) { m_name = name; }
	void SetVertexShaderFilename( const fc::string& filename ) { m_vertexFilename = filename; }
	void SetFragmentShaderFilename( const fc::string& filename ) { m_fragmentFilename = filename; }
	const fc::string& GetName() const { return m_name; }
	const fc::string& GetVertexShaderFilename() const { return m_vertexFilename; }
	const fc::string& GetFragmentShaderFilename() const { return m_fragmentFilename; }

	Shader* LoadShader();
	void ReleaseShader();

	void SerializeXml( XmlWriter* xml );
	void DeserializeXml( XmlReader* xml );

protected:
	fc::string		m_name;
	fc::string		m_vertexFilename;
	fc::string		m_fragmentFilename;

	Shader*			m_shader;
};


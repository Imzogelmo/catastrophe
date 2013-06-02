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

#include <Catastrophe/IO/XmlWriter.h>
#include <Catastrophe/IO/XmlReader.h>
#include <Catastrophe/Graphics/ShaderObject.h>
#include <Catastrophe/Graphics/Shader.h>
#include "ShaderAsset.h"
#include "ShaderObjectManager.h"



ShaderAsset::ShaderAsset() :
	m_shader(0)
{
}


ShaderAsset::~ShaderAsset()
{
	if( m_shader != 0 )
	{
		delete m_shader;
	}
}


Shader* ShaderAsset::LoadShader()
{
	if( !m_shader )
	{
		VertexShader* vertexShader = 0;
		FragmentShader* fragmentShader = 0;

		if( !m_vertexFilename.empty() )
			vertexShader = g_shaderObjectManager->LoadVertexShader(m_vertexFilename);

		if( !m_fragmentFilename.empty() )
			fragmentShader = g_shaderObjectManager->LoadFragmentShader(m_fragmentFilename);

		// there needs to be a valid shader object to create a program.
		if( vertexShader != 0 || fragmentShader != 0 )
		{
			m_shader = new Shader();
			m_shader->SetVertexShader(vertexShader);
			m_shader->SetFragmentShader(fragmentShader);
			m_shader->Link();
		}
		else
		{
			LogError("Error: ShaderAsset::LoadShader() : no shader objects could be loaded.");
		}
	}

	return m_shader;
}


void ShaderAsset::ReleaseShader()
{
	// do nothing
}


void ShaderAsset::SerializeXml( XmlWriter* xml )
{
	xml->SetString("name", m_name);
	xml->SetString("vert", m_vertexFilename);
	xml->SetString("frag", m_fragmentFilename);
}


void ShaderAsset::DeserializeXml( XmlReader* xml )
{
	m_name = xml->GetString("name");
	m_vertexFilename = xml->GetString("vert");
	m_fragmentFilename = xml->GetString("frag");
}


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

#include <Catastrophe/Core/IO/AttributeWriter.h>
#include <Catastrophe/Core/IO/AttributeReader.h>
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

		if( !m_vertexFilename.Empty() )
			vertexShader = g_shaderObjectManager->LoadVertexShader(m_vertexFilename);

		if( !m_fragmentFilename.Empty() )
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


void ShaderAsset::Serialize( AttributeWriter* f )
{
	f->SetString("name", m_name);
	f->SetString("vert", m_vertexFilename);
	f->SetString("frag", m_fragmentFilename);
}


void ShaderAsset::Deserialize( AttributeReader* f )
{
	m_name = f->GetString("name");
	m_vertexFilename = f->GetString("vert");
	m_fragmentFilename = f->GetString("frag");
}



int ShaderAsset::GetMemoryUsage() const
{
	return (int)(m_name.Capacity() + m_vertexFilename.Capacity() + m_fragmentFilename.Capacity());
}

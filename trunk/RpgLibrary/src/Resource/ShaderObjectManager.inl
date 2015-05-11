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

#include <Catastrophe/Graphics/ShaderObject.h>
#include "ShaderObjectManager.h"



ShaderObjectManager::ShaderObjectManager()
{
	m_resourceCache.SetManager(this);
	m_resourceCache.SetResourceUsage(32);
}


ShaderObjectManager::~ShaderObjectManager()
{
	m_resourceCache.DeleteResources();
}


void ShaderObjectManager::DisposeResource( void* p )
{
	ShaderObject* shaderObject = (ShaderObject*)p;
	if( shaderObject )
	{
		shaderObject->Dispose();
		delete shaderObject;
	}
}


VertexShader* ShaderObjectManager::LoadVertexShader( const String& filename, int* id )
{
	return (VertexShader*)Load(filename, VertexShaderType, id);
}


FragmentShader* ShaderObjectManager::LoadFragmentShader( const String& filename, int* id )
{
	return (FragmentShader*)Load(filename, FragmentShaderType, id);
}


ShaderObject* ShaderObjectManager::Load( const String& filename, int type, int* id  )
{
	ShaderObject* shaderObject = GetResource(filename, id);
	if( shaderObject )
		return shaderObject;

	// else create a new resource.
	shaderObject = new ShaderObject((ShaderType)type);

	String fn = g_resourceDirectory->GetShaderDirectory();
	fn += filename;
	if( !shaderObject->LoadFromFile(fn) )
	{
		LogError("Failed to load shader object (%s)", fn.CString());
		SAFE_DELETE(shaderObject);
	}
	else
	{
		//shaderObject->SetName(filename);
		AddResource(shaderObject, filename, id);
	}

	return shaderObject;
}






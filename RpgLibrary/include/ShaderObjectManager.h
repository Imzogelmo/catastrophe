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

#include "ResourceManager.h"


class ShaderObjectManager : public ResourceManagerType<ShaderObject>
{
public:
	ShaderObjectManager();
	~ShaderObjectManager();

	VertexShader* LoadVertexShader( const String& filename, int* id = 0 );
	FragmentShader* LoadFragmentShader( const String& filename, int* id = 0 );
	ShaderObject* Load( const String& filename, int type, int* id = 0 );

protected:
	void DisposeResource( void* p );

};


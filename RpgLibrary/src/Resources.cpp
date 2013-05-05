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


// This file is part of my module based "unity build" experiment.
// A unity build is achieved by having a single .cpp file include all other .cpp files,
// allowing you to compile only a single file to build a project.
// Why would you do this, you ask? -Why not. ;)


// resource
#include "Resource.inl"
#include "ResourceManager.inl"
#include "TextureManager.inl"
#include "TilesetManager.inl"
#include "MapManager.inl"


ResourceDirectory*	g_resourceDirectory = 0;
TextureManager*		g_textureManager = 0;
TilesetManager*		g_tilesetManager = 0;


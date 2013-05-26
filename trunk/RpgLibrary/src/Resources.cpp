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
#include "ResourceDirectory.inl"
#include "ResourceManager.inl"
#include "TextureManager.inl"
#include "TilesetManager.inl"
#include "MapManager.inl"

#include "TextureAsset.inl"
#include "AnimatedSpriteAsset.inl"
#include "AnimatedSpriteSetAsset.inl"

#include "SerializeObject.inl"
#include "DeserializeObject.inl"


ResourceDirectory*	g_resourceDirectory = 0;
TextureManager*		g_textureManager = 0;
TilesetManager*		g_tilesetManager = 0;
MapManager*			g_mapManager = 0;



void RpgLibInit()
{
	g_resourceDirectory = new ResourceDirectory();
	g_textureManager = new TextureManager();
	g_tilesetManager = new TilesetManager();
	g_mapManager = new MapManager();
}


void RpgLibShutdown()
{
	delete g_resourceDirectory;
	delete g_textureManager;
	delete g_tilesetManager;
	delete g_mapManager;
}




void _test()
{
	Point p;
	SerializeObject(0,p);
	SerializeObject("test",0,p);

	DeserializeObject(0,p);
	DeserializeObject("test",0,p);

	Rect r;
	SerializeObject(0,r);
	SerializeObject("test",0,r);

	DeserializeObject(0,r);
	DeserializeObject("test",0,r);

}


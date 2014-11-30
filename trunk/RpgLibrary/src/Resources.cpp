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


#include "Database.h"

// resource
#include "Resource.inl"
#include "ResourceDirectory.inl"
#include "ResourceManager.inl"
#include "TextureManager.inl"
#include "FontManager.inl"

#include "TilesetManager.inl"
#include "MapManager.inl"
#include "ShaderObjectManager.inl"

#include "TextureAsset.inl"
#include "FontAsset.inl"
#include "SpriteAsset.inl"
#include "AnimatedSpriteAsset.inl"
#include "AnimatedSpriteSetAsset.inl"
#include "ShaderAsset.inl"

#include "SerializeObject.inl"
#include "DeserializeObject.inl"
#include "AttributeSerializer.inl"


ResourceDirectory*		g_resourceDirectory = 0;
TextureManager*			g_textureManager = 0;
FontManager*			g_fontManager = 0;
TilesetManager*			g_tilesetManager = 0;
MapManager*				g_mapManager = 0;
ShaderObjectManager*	g_shaderObjectManager = 0;



void RpgLibInit()
{
	g_resourceDirectory = new ResourceDirectory();
	g_textureManager = new TextureManager();
	g_fontManager = new FontManager();
	g_tilesetManager = new TilesetManager();
	g_mapManager = new MapManager();
	g_shaderObjectManager = new ShaderObjectManager();

	// register all object types (order does not matter).
	Attributes::RegisterObject();
	//Item::RegisterObject();
	//EquipmentItem::RegisterObject();
	MonsterData::RegisterObject();
	//MonsterGroup::RegisterObject();
	//MonsterTroop::RegisterObject();
	MonsterFormationCellData::RegisterObject();
	MonsterFormation::RegisterObject();

	CharacterData::RegisterObject();
	CharacterClass::RegisterObject();
	Race::RegisterObject();

}


void RpgLibShutdown()
{
	SAFE_DELETE(g_resourceDirectory);
	SAFE_DELETE(g_textureManager);
	SAFE_DELETE(g_fontManager);
	SAFE_DELETE(g_tilesetManager);
	SAFE_DELETE(g_mapManager);
	SAFE_DELETE(g_shaderObjectManager);

	ObjectAttributeSerializerFactory::GetInstance()->DeleteFactories();
}



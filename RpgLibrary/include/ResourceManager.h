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

#include <fc/vector.h>
#include <fc/string.h>

#include "RpgCommon.h"
#include "ResourceDirectory.h"


class Resource
{
public:
	//we don't need a template type for simple pointers.
	typedef void* pointer;

	pointer			ptr;
	fc::string		name;

	Resource( pointer p = 0, const fc::string& filename = "" )
		: ptr(p), name(filename), m_ref_count(1)
	{}

	void AddRef()
	{
		++m_ref_count;
	}

	void ReleaseRef()
	{
		--m_ref_count;
	}

	int GetRefCount()
	{
		return m_ref_count;
	}

protected:
	int m_ref_count;
};


class RPG_API ResourceCache
{
public:
	typedef	fc::vector<Resource>	vec_type;
	typedef	fc::vector<size_t>		store_type;

	ResourceCache();

	// since the needs of a resource cache can largely vary,
	// it is required to call this. 
	void SetResourceUsage( size_t maxCapacity = 256 );

	// this will invalidate all existing pointers to these resources.
	template <class T> void DeleteResources();
	template <class T> void DeleteResource( Resource* ptr );

	// these get functions have a linear time cost.
	Resource* GetResource( const fc::string& name );
	Resource* GetResource( const void* ptr );

	// fast lookup of resource.
	Resource* GetResource( int id );

	// returns the id of the newly added resource
	int AddResource( const Resource& resource );

protected:
	vec_type	m_resources;
	store_type	m_free_store;

};


class RPG_API ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	void DeleteResources();

	ResourceCache* GetTextureResourceCache() { return &m_textureCache; }
	ResourceCache* GetFontResourceCache() { return &m_fontCache; }
	ResourceCache* GetShaderResourceCache() { return &m_shaderCache; }
	const ResourceCache* GetTextureResourceCache() const { return &m_textureCache; }
	const ResourceCache* GetFontResourceCache() const { return &m_fontCache; }
	const ResourceCache* GetShaderResourceCache() const { return &m_shaderCache; }

	ResourceDirectory& GetResourceDirectory() { return m_directory; }
	const ResourceDirectory& GetResourceDirectory() const { return m_directory; }

	//
	// Load and Get functions return null if the resource does not exist.
	// the id of the resource can optionally be aquired as well.
	// id's will be eventually be recycled by the resource cache 
	// after destroying the actual resource.
	//
	Texture*		LoadTexture( const fc::string& filename, int* id = 0 );
	Font*			LoadFont( const fc::string& filename, int faceSize, int* id = 0 );
	ShaderObject*	LoadShaderObject( const fc::string& filename, int shaderType, int* id = 0 );

	Texture*		GetTexture( const fc::string& filename );
	Font*			GetFont( const fc::string& filename );
	ShaderObject*	GetShaderObject( const fc::string& filename );

	Texture*		GetTexture( int id );
	Font*			GetFont( int id );
	ShaderObject*	GetShaderObject( int id );

	void UnloadTexture( const fc::string& filename );
	void UnloadFont( const fc::string& filename );
	void UnloadShaderObject( const fc::string& filename );

	void UnloadTexture( int id );
	void UnloadFont( int id );
	void UnloadShaderObject( int id );

	// when we lose OpenGL context or switch video modes (ie; to-from fullscreen),
	// this invalidates all gpu data, so we must reload them.
	// *this will not invalidate any pointers*
	void ReloadGraphicsResources();

protected:
	void InternalReleaseTexture( Resource* resource );
	void InternalReleaseFont( Resource* resource );
	void InternalReleaseShaderObject( Resource* resource );

	ResourceCache		m_textureCache;
	ResourceCache		m_fontCache;
	ResourceCache		m_shaderCache;
	ResourceDirectory	m_directory;

private:
	//static ResourceManager m_singleton;

	//at any rate, this cannot be allowed to share resources.
	ResourceManager( const ResourceManager& );
	ResourceManager& operator =( const ResourceManager& );
};



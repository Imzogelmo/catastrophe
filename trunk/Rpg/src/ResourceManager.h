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
#include "Common.h"


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


class ResourceCache
{
public:
	typedef	fc::vector<Resource>	vec_type;
	typedef	fc::vector<size_t>		store_type;

	ResourceCache();

	void SetDirectory( const fc::string& directory );
	const fc::string& GetDirectory() const { return m_directory; };

	//this will invalidate all existing pointers to these resources.
	template <class T> void DeleteResources();
	template <class T> void DeleteResource( Resource* ptr );

	//get functions have a linear time cost.
	Resource* GetResource( const fc::string& name );
	Resource* GetResource( const void* ptr );

	void AddResource( const Resource& resource );

protected:
	vec_type	m_resources;
	store_type	m_free_store;
	fc::string	m_directory;

};


class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	void DeleteResources();

	void SetBaseDirectory( const fc::string& directory );
	void SetTextureDirectory( const fc::string& directory ) { GetTextureResourceCache()->SetDirectory(directory); }
	void SetFontDirectory( const fc::string& directory ) { GetFontResourceCache()->SetDirectory(directory); }

	const fc::string& GetBaseDirectory() const { return m_baseDirectory; }
	const fc::string& GetTextureDirectory() const { return GetTextureResourceCache()->GetDirectory(); }
	const fc::string& GetFontDirectory() const { return GetFontResourceCache()->GetDirectory(); }

	ResourceCache* GetTextureResourceCache() { return &m_textureCache; }
	ResourceCache* GetFontResourceCache() { return &m_textureCache; }
	const ResourceCache* GetTextureResourceCache() const { return &m_textureCache; }
	const ResourceCache* GetFontResourceCache() const { return &m_textureCache; }

	Texture*	LoadTexture( const fc::string& filename );
	Font*		LoadFont( const fc::string& filename, int faceSize );

	Texture*	GetTexture( const fc::string& filename );
	Font*		GetFont( const fc::string& filename );

	void UnloadTexture( const fc::string& filename );
	void UnloadFont( const fc::string& filename );

	//when we lose OpenGL context or switch video modes (ie; to-from fullscreen),
	//this invalidates all gpu data, so we must reload them.
	// *this will not invalidate any pointers*
	void ReloadGraphicsResources();

protected:
	ResourceCache		m_textureCache;
	ResourceCache		m_fontCache;

	fc::string			m_baseDirectory;

private:
	//ResourceManager does NOT follow the singleton pattern...
	//...though there could be use for one....
	//static ResourceManager m_singleton;

	//at any rate, this cannot be allowed to share resources.
	ResourceManager( const ResourceManager& );
	ResourceManager& operator =( const ResourceManager& );
};



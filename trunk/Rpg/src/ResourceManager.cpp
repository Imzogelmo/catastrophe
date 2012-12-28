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

#include <Catastrophe/Graphics/Texture.h>
#include <Catastrophe/Graphics/Font.h>
#include <Catastrophe/Graphics/ShaderObject.h>
#include "ResourceManager.h"


ResourceCache::ResourceCache()
{
	m_resources.reserve(256);
}


void ResourceCache::SetDirectory( const fc::string& directory )
{
	ASSERT(m_resources.empty());
	m_directory = directory;
}


template <class T>
void ResourceCache::DeleteResources()
{
	for( vec_type::iterator it = m_resources.begin(); it != m_resources.end(); ++it )
	{
		DeleteResource<T>(it);
	}

	m_resources.clear();
	m_free_store.clear();
}


template <class T>
void ResourceCache::DeleteResource( Resource* resource )
{
	if( resource && m_resources.iterator_is_valid(resource) )
	{
		//dont delete previously deleted resources.
		if( resource->ptr )
		{
			((T*)resource->ptr)->Dispose();
			delete resource->ptr;
			*resource = Resource();
			m_free_store.push_back( size_t(resource - m_resources.begin()) );
		}
	}
}


Resource* ResourceCache::GetResource( const fc::string& name )
{
	if( name.empty() )
		return 0;

	Resource* res = 0;
	for( vec_type::iterator it = m_resources.begin(); it != m_resources.end(); ++it )
	{
		if( it->name == name )
		{
			res = &(*it);
			break;
		}
	}

	return res;
}


Resource* ResourceCache::GetResource( const void* ptr )
{
	if(!ptr)
		return 0;

	Resource* res = 0;
	for( vec_type::iterator it = m_resources.begin(); it != m_resources.end(); ++it )
	{
		if( it->ptr == ptr )
		{
			res = &(*it);
			break;
		}
	}

	return res;
}


Resource* ResourceCache::GetResource( int id )
{
	Resource* res = 0;
	if( (size_t)id < m_resources.size() )
	{
		if( res->ptr )
			res = &m_resources[id];
	}

	return res;
}


int ResourceCache::AddResource( const Resource& resource )
{
	int id = -1;
	if( !m_free_store.empty() )
	{
		id = (int)m_free_store.back();
		m_resources[ m_free_store.back() ] = resource;
		m_free_store.pop_back();
	}
	else
	{
		ASSERT(!m_resources.full());

		id = (int)m_resources.size();
		m_resources.push_back(resource);
	}

	return id;
}


ResourceManager::ResourceManager()
{
}


ResourceManager::~ResourceManager()
{
	DeleteResources();
}


void ResourceManager::SetBaseDirectory( const fc::string& directory )
{
	//ASSERT(m_textures.empty() && m_fonts.empty());
	m_baseDirectory = directory;
}


void ResourceManager::DeleteResources()
{
	//releases all gpu data and deletes all resources.
	m_textureCache.DeleteResources<Texture>();
	m_fontCache.DeleteResources<Font>();
	m_shaderCache.DeleteResources<Font>();

}


Texture* ResourceManager::LoadTexture( const fc::string& filename, int* id  )
{
	Resource* resource = m_textureCache.GetResource(filename);
	Texture* texture = 0;
	if( resource != 0 )
	{
		resource->AddRef();
		texture = (Texture*)resource->ptr;
	}
	else
	{
		texture = new Texture();

		fc::string fn;
		fn.reserve(m_baseDirectory.size() + GetTextureDirectory().size() + filename.size() + 1);
		fn.append(m_baseDirectory).append(GetTextureDirectory()).append(filename);

		if( !texture->LoadFromFile(fn) )
		{
			LogError("Failed to load resource (%s)", fn.c_str());
			SAFE_DELETE(texture);
		}
		else
		{
			texture->SetName(filename);
			int resourceID = m_textureCache.AddResource( Resource(texture, filename) );
			if( id != 0 )
			{
				//the caller wants the resource id.
				*id = resourceID;
			}
		}
	}

	return texture;
}


Font* ResourceManager::LoadFont( const fc::string& filename, int faceSize, int* id  )
{
	//Fixme: You can load the same font multiple times with different face sizes...
	Resource* resource = m_fontCache.GetResource(filename);
	Font* font = 0;
	if( resource != 0 )
	{
		resource->AddRef();
		font = (Font*)resource->ptr;
	}
	else
	{
		font = new Font();

		fc::string fn;
		fn.reserve(m_baseDirectory.size() + GetFontDirectory().size() + filename.size() + 1);
		fn.append(m_baseDirectory).append(GetFontDirectory()).append(filename);

		if( !font->LoadFromFile(fn, faceSize) )
		{
			LogError("Failed to load resource (%s)", fn.c_str());
			SAFE_DELETE(font);
		}
		else
		{
			font->GetTexture()->SetName(filename);
			int resourceID = m_fontCache.AddResource( Resource(font, filename) );
			if( id != 0 )
			{
				//the caller wants the resource id.
				*id = resourceID;
			}
		}
	}

	return font;
}


ShaderObject* ResourceManager::LoadShaderObject( const fc::string& filename, int shaderType, int* id  )
{
	Resource* resource = m_shaderCache.GetResource(filename);
	ShaderObject* shader = 0;
	if( resource != 0 )
	{
		resource->AddRef();
		shader = (ShaderObject*)resource->ptr;
	}
	else
	{
		if( shaderType == VertexShaderType ) shader = new VertexShader();
		else if( shaderType == FragmentShaderType ) shader = new FragmentShader();
		else
		{
			LogError("Error: shader type unknown.");
			return 0;
		}

		fc::string fn;
		fn.reserve(m_baseDirectory.size() + GetShaderDirectory().size() + filename.size() + 1);
		fn.append(m_baseDirectory).append(GetShaderDirectory()).append(filename);

		if( !shader->LoadFromFile(fn) )
		{
			LogError("Failed to load resource (%s)", fn.c_str());
			SAFE_DELETE(shader);
		}
		else
		{
			int resourceID = m_shaderCache.AddResource( Resource(shader, filename) );
			if( id != 0 )
			{
				//the caller wants the resource id.
				*id = resourceID;
			}
		}
	}

	return shader;
}


Texture* ResourceManager::GetTexture( const fc::string& filename )
{
	Resource* resource = m_textureCache.GetResource(filename);
	if( resource )
	{
		return (Texture*)resource->ptr;
	}

	return 0;
}


Font* ResourceManager::GetFont( const fc::string& filename )
{
	Resource* resource = m_fontCache.GetResource(filename);
	if( resource )
	{
		return (Font*)resource->ptr;
	}

	return 0;
}


ShaderObject* ResourceManager::GetShaderObject( const fc::string& filename )
{
	Resource* resource = m_shaderCache.GetResource(filename);
	if( resource )
	{
		return (ShaderObject*)resource->ptr;
	}

	return 0;
}


Texture* ResourceManager::GetTexture( int id )
{
	Resource* resource = m_textureCache.GetResource(id);
	if( resource )
	{
		return (Texture*)resource->ptr;
	}

	return 0;
}


Font* ResourceManager::GetFont( int id )
{
	Resource* resource = m_fontCache.GetResource(id);
	if( resource )
	{
		return (Font*)resource->ptr;
	}

	return 0;
}


ShaderObject* ResourceManager::GetShaderObject( int id )
{
	Resource* resource = m_shaderCache.GetResource(id);
	if( resource )
	{
		return (ShaderObject*)resource->ptr;
	}

	return 0;
}


void ResourceManager::UnloadTexture( const fc::string& filename )
{
	Resource* resource = m_textureCache.GetResource(filename);
	if( resource )
	{
		resource->ReleaseRef();
		if( resource->GetRefCount() == 0 )
		{
			m_textureCache.DeleteResource<Texture>(resource);
		}
	}
}


void ResourceManager::UnloadFont( const fc::string& filename )
{
	Resource* resource = m_fontCache.GetResource(filename);
	if( resource )
	{
		resource->ReleaseRef();
		if( resource->GetRefCount() == 0 )
		{
			m_fontCache.DeleteResource<Font>(resource);
		}
	}
}


void ResourceManager::UnloadShaderObject( const fc::string& filename )
{
	Resource* resource = m_fontCache.GetResource(filename);
	if( resource )
	{
		resource->ReleaseRef();
		if( resource->GetRefCount() == 0 )
		{
			m_shaderCache.DeleteResource<ShaderObject>(resource);
		}
	}
}


void ResourceManager::ReloadGraphicsResources()
{
}



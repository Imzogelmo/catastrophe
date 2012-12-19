
#include <Catastrophe/Graphics/Texture.h>
#include <Catastrophe/Graphics/Font.h>
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


void ResourceCache::AddResource( const Resource& resource )
{
	if( !m_free_store.empty() )
	{
		m_resources[ m_free_store.back() ] = resource;
		m_free_store.pop_back();
	}
	else
	{
		m_resources.push_back(resource);
	}
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

}


Texture* ResourceManager::LoadTexture( const fc::string& filename )
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
			delete texture;
			texture = 0;
		}
		else
		{
			m_textureCache.AddResource( Resource(texture, filename) );
		}
	}

	return texture;
}


Font* ResourceManager::LoadFont( const fc::string& filename, int faceSize )
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
			delete font;
			font = 0;
		}
		else
		{
			m_fontCache.AddResource( Resource(font, filename) );
		}
	}

	return font;
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


void ResourceManager::ReloadGraphicsResources()
{
}



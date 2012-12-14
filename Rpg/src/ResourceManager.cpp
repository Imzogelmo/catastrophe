
#include "ResourceManager.h"



ResourceManager::ResourceManager()
{
}


ResourceManager::~ResourceManager()
{
	DeleteResources();
}


void ResourceManager::SetBaseDirectory( const fc::string& directory )
{
	m_baseDirectory = directory;
	//m_resourceDirectory = GetNativePath(resourceDirectoryBase);
	//if( !m_directory.empty() && (m_directory.back() != '/' || m_directory.back() != '\\' )
	{
		//todo: native paths.
	//	m_baseDirectory.push_back('/');
	}
}


void ResourceManager::SetTextureDirectory( const fc::string& directory )
{
	m_textureDirectory = directory;
}


void ResourceManager::SetFontDirectory( const fc::string& directory )
{
	m_fontDirectory = directory;
}


void ResourceManager::DeleteResources()
{
	//releases all gpu data and deletes all resources.
	DeleteTextures();
	DeleteFonts();

}


void ResourceManager::DeleteTextures()
{
	for( texture_vec_type::iterator it = m_textures.begin(); it != m_textures.end(); ++it )
	{
		((Texture*)it->ptr)->Dispose();
		delete it->ptr;
	}

	m_textures.clear();
}


void ResourceManager::DeleteFonts()
{
	for( font_vec_type::iterator it = m_fonts.begin(); it != m_fonts.end(); ++it )
	{
		((Font*)it->ptr)->Dispose();
		delete it->ptr;
	}

	m_fonts.clear();
}


Texture* ResourceManager::LoadTexture( const fc::string& filename )
{
	Texture* texture = GetTexture(filename);
	if( !texture )
	{
		texture = new Texture();

		fc::string fn;
		fn.reserve(m_baseDirectory.size() + m_textureDirectory.size() + filename.size() + 1);
		fn.append(m_baseDirectory).append(m_textureDirectory).append(filename);

		if( !texture->LoadFromFile(fn) )
		{
			LogError("Failed to load resource (%s)", fn.c_str());
			delete texture;
			texture = 0;
		}
		else
		{
			m_textures.push_back(Resource(texture, filename));
		}
	}

	return texture;
}


Font* ResourceManager::LoadFont( const fc::string& filename, int faceSize )
{
	//Fixme: You can load the same font multiple times with different face sizes...
	Font* font = GetFont(filename);
	if( !font )
	{
		font = new Font();

		fc::string fn;
		fn.reserve(m_baseDirectory.size() + m_fontDirectory.size() + filename.size() + 1);
		fn.append(m_baseDirectory).append(m_fontDirectory).append(filename);

		if( !font->LoadFromFile(fn, faceSize) )
		{
			LogError("Failed to load resource (%s)", fn.c_str());
			delete font;
			font = 0;
		}
		else
		{
			m_fonts.push_back(Resource(font, filename));
		}
	}

	return font;
}



Texture* ResourceManager::GetTexture( const fc::string& filename )
{
	Texture* texture = 0;
	for( texture_vec_type::iterator it = m_textures.begin(); it != m_textures.end(); ++it )
	{
		if( it->name == filename )
		{
			texture = (Texture*)it->ptr;
			break;
		}
	}

	return texture;
}


Font* ResourceManager::GetFont( const fc::string& filename )
{
	Font* font = 0;
	for( font_vec_type::iterator it = m_fonts.begin(); it != m_fonts.end(); ++it )
	{
		if( it->name == filename )
		{
			font = (Font*)it->ptr;
			break;
		}
	}

	return font;
}


void ResourceManager::ReloadGraphicsResources()
{
}



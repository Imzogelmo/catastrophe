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

#include "Catastrophe/Core/Common.h"
#include "Catastrophe/Core/Resource/Resource.h"
#include "Catastrophe/Core/Containers/String.h"
#include "Catastrophe/Core/Containers/HashMap.h"

CE_NAMESPACE_BEGIN


//typedef Resource* (*ResourceCreateFunc)();
//typedef void (*ResourceDeleteFunc)(Resource*);

namespace Internal
{
	template <class T> struct ResourceTypeInfo { static int typeID; };
	template <class T> int ResourceTypeInfo<T>::typeID = -1;

	class ResourceObjectFactory
	{
	public:
		virtual int GetResourceTypeID() = 0;
		virtual Resource* CreateResource() = 0;
		virtual void DeleteResource(Resource* resource) { delete resource; }
	};

	template <class T>
	class ResourceTypeObjectFactory : public ResourceObjectFactory
	{
	public:
		virtual int GetResourceTypeID() { return ResourceTypeInfo<T>::typeID; }
		virtual Resource* CreateResource() { return new T(); }
	};
}

struct FixMeMakeHash { int operator()(int v) const {return v;} };

class CE_API ResourceGroup
{
public:
	typedef HashMap<int, Resource*, FixMeMakeHash> ResourceMap;

	ResourceGroup(const char* name, u32 capacity);
	~ResourceGroup();

	template <class T>
	void SetFactoryType()
	{
		new (m_factoryBuffer) Internal::ResourceTypeObjectFactory<T>();
		m_factory = m_factoryBuffer;
		//new (&m_staticFactory) Internal::ResourceTypeObjectFactory<T>();
	}

	Internal::ResourceObjectFactory* GetResourceFactory() const
	{
		return (Internal::ResourceObjectFactory*)m_factoryBuffer;
	}

	/// Returs a previously loaded resource or creates a new resource if one does not exist.
	Resource* LoadResource(const String& filename);

	/// Creates a new resource using the supplied CreateResourceFunction type.
	/// This does not add the resource to the resource map.
	Resource* CreateResource()
	{
		Resource* resource = GetResourceFactory()->CreateResource();
		return resource;
	}

	/// Deletes all resources that are not referenced externally.
	void DeleteUnusedResources();

	/// Deletes all resources.
	void DeleteAllResources();

	/// 
	void DeleteResource(Resource* resource);

	Resource* FindResource(const String& name)
	{
		int hashedName = 0;
		ResourceMap::Iterator it = m_resourceMap.FindKey(hashedName);
		if( it != m_resourceMap.end() )
		{
			return it->value;
		}

		return null;
	}

	void AddResource( Resource* resource )
	{
		m_resourceMap.Add(0, resource);
	}

	void SetResourceDirectory(const String& directory)
	{
		m_directory = directory;
	}

	const String& GetResourceDirectory() const
	{
		return m_directory;
	}

protected:
	const char*				m_resourceName;
	ResourceMap				m_resourceMap;
	String					m_directory;
	Internal::ResourceObjectFactory*	m_factory;
	char					m_factoryBuffer[sizeof(Internal::ResourceObjectFactory)];
	//Internal::ResourceObjectFactory	m_staticFactory;

};




CE_NAMESPACE_END

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
#include "Catastrophe/Core/Resource/ResourceFactory.h"
#include "Catastrophe/Core/Containers/String.h"
#include "Catastrophe/Core/Containers/HashMap.h"
#include "Catastrophe/Core/Containers/VectorMap.h"
#include "Catastrophe/Core/Hash.h"

CE_NAMESPACE_BEGIN


struct FixMeMakeHash { int operator()(int v) const {return v;} };

class CE_API ResourceGroup
{
public:
	//typedef HashMap<int, Resource*, FixMeMakeHash> ResourceMap;
	typedef VectorMap<u32, Resource*> ResourceMap;

	ResourceGroup(const char* name, u32 capacity);
	~ResourceGroup();

	template <class T>
	void SetFactoryType()
	{
		new (m_factoryBuffer) ResourceTypeObjectFactory<T>();
		m_factory = (ResourceObjectFactory*)m_factoryBuffer;
		//new (&m_staticFactory) ResourceTypeObjectFactory<T>();
	}

	ResourceObjectFactory* GetResourceFactory() const
	{
		return (ResourceObjectFactory*)m_factoryBuffer;
	}

	/// Gets a resource or loads it from file if it is not already loaded.
	Resource* LoadResource(const String& filename);

	/// Returns a previously loaded resource or creates a new resource if one does not exist.
	/// @param directory - If the resource needs to be loaded, this directory will be checked first.
	Resource* LoadResource(const String& directory, const String& filename);

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

	Resource* FindResource(const String& name) const
	{
		const u32 nameHash = MakeHash(name);
		return FindResource(nameHash);
	}

	Resource* FindResource(u32 hashValue) const
	{
		ResourceMap::ConstIterator it = m_resourceMap.Find(hashValue);
		if( it != m_resourceMap.end() )
			return it->value;

		return null;
	}

	void AddResource( Resource* resource )
	{
		if(resource != null)
		{
			u32 nameHash = MakeHash(resource->GetResourceName());
			ResourceMap::Iterator it = m_resourceMap.Find(nameHash);
			if( it != m_resourceMap.end() )
			{
				m_resourceMap.Add(nameHash, resource);
			}
		}
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
	ResourceObjectFactory*	m_factory;
	char					m_factoryBuffer[sizeof(ResourceObjectFactory)];
	//ResourceObjectFactory	m_staticFactory;

};




CE_NAMESPACE_END

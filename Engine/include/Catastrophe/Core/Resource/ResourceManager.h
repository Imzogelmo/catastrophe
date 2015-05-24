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
#include "Catastrophe/Core/SharedPtr.h"
#include "Catastrophe/Core/Resource/Resource.h"
#include "Catastrophe/Core/Resource/ResourceGroup.h"

CE_NAMESPACE_BEGIN


#define MAX_RESOURCE_GROUPS 32


class CE_API ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	void InitializeResourceManager(u32 numRegisterableResourceTypes)
	{
	}

	/// Registers a new resource type that can be managed by the ResourceManager.
	/// New resource types must inherit from Resource base class and implement
	/// Resource::Load() handling.
	///
	/// Usage:
	///    class LevelInstance : public Resource {
	///        void Load(...);
	///    };
	///
	///    // Register the LevelInstance resource type with enough initial capacity
	///    // to hold a maximum of 8 hash keys and resource pointers.
	///    int typeID = resourceManager->RegisterResourceType<LevelInstance>("LevelInstance", 8); 
	///
	template <class T>
	int RegisterResourceType(const char* name, u32 capacity);

	/// Gets the ResourceGroup object that manages a resource type.
	template <class T>
	ResourceGroup* GetResourceGroup()
	{
		ResourceGroup* resourceGroup = m_resourceGroups[ResourceTypeInfo<T>::typeID];
		ASSERT(resourceGroup && "Resource type must be registered first");
		return resourceGroup;
	}

	/// Gets the typeID of a previously registered resource type.
	template <class T>
	int GetResourceGroupID()
	{
		return ResourceTypeInfo<T>::typeID;
	}

	/// Loads a resource from file if it does not exist.
	template <class T>
	T* Load(const String& filename)
	{
		return (T*)Load(GetResourceGroupID<T>(), filename);
	}

	template <class T>
	T* Load(const String& directory, const String& filename)
	{
		return (T*)Load(GetResourceGroupID<T>(), directory, filename);
	}

	/// Loads a resource of type from file if it does not already exist.
	Resource* Load(int resourceType, const String& filename);

	/// Loads a resource of type from file if it does not already exist.
	Resource* Load(int resourceType, const String& directory, const String& filename);

	/// Adds an user-created resource to this manager.
	template <class T>
	void AddResource(Resource* resource);

	/// Forcibly deletes all resources in each resource group.
	void DeleteAllResources();

private:
	ResourceManager( const ResourceManager& );
	ResourceManager& operator =( const ResourceManager& );

	//typedef StaticFreeList<MAX_RESOURCE_GROUPS, sizeof(ResourceObjectFactory) * MAX_RESOURCE_GROUPS> FactoryPoolType;

	// Unique typeID generator for resource types.
	static int m_resourceGroupIDGenerator;

	ResourceGroup*		m_resourceGroups[MAX_RESOURCE_GROUPS];
	//FactoryPoolType		m_factoryPool;
};



template <class T>
int ResourceManager::RegisterResourceType(const char* name, u32 capacity)
{
	ASSERT(m_resourceGroupIDGenerator < MAX_RESOURCE_GROUPS);

	int typeID = ResourceTypeInfo<T>::typeID;
	if(typeID == -1)
	{
		typeID = m_resourceGroupIDGenerator++;
		ResourceTypeInfo<T>::typeID = typeID;
	}

	//void* pFactory = m_factoryPool.Aquire();
	//ASSERT(pFactory);
	//new (pFactory) ResourceTypeObjectFactory<T>();

	ResourceGroup* resourceGroup = new ResourceGroup(name, capacity);
	resourceGroup->SetFactoryType<T>();

	m_resourceGroups[typeID] = resourceGroup;

	return typeID;
}



template <class T>
void ResourceManager::AddResource(Resource* resource)
{
	ResourceGroup* resourceGroup = GetResourceGroup<T>();
	resourceGroup->AddResource(resource);
}




CE_NAMESPACE_END

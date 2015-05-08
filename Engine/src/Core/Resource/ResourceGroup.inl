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
#include "Catastrophe/Core/Resource/ResourceGroup.h"

CE_NAMESPACE_BEGIN



ResourceGroup::ResourceGroup(const char* name, u32 capacity)
{
}


ResourceGroup::~ResourceGroup()
{
	DeleteAllResources();
}


Resource* ResourceGroup::LoadResource(const String& filename)
{
	Resource* resource = FindResource(filename);
	if(!resource)
	{
		// Try to create and load a new resource.
		resource = CreateResource();
		if(resource)
		{
			File file(GetResourceDirectory() + filename);
			if(!file.IsOpen())
				return null;

			if(resource->Load(&file))
			{
				resource->SetResourceName(filename);
				resource->AddRef();

				// Add the loaded resource to the map.
				AddResource(resource);
			}
			else
			{
				GetResourceFactory()->DeleteResource(resource);
				resource = null;
			}
		}
	}

	return resource;
}


void ResourceGroup::DeleteUnusedResources()
{
	for(ResourceMap::Iterator it = m_resourceMap.begin(); it != m_resourceMap.end(); ++it)
	{
		Resource* resource = it->value;
		if(resource != null && resource->GetRefCount() == 1)
		{
			DeleteResource(resource);
			m_resourceMap.Erase(it);
		}
	}
}


void ResourceGroup::DeleteAllResources()
{
	for(ResourceMap::Iterator it = m_resourceMap.begin(); it != m_resourceMap.end(); ++it)
	{
		Resource* resource = it->value;
		if(resource != null)
		{
			DeleteResource(resource);
			m_resourceMap.Erase(it);
		}
	}
}


void ResourceGroup::DeleteResource(Resource* resource)
{
	if(resource == null)
		return;

	LogInfo("Deleted resource \"%s\" with a reference count of %i",
		resource->GetResourceName().CString(),
		resource->GetRefCount()
		);

	GetResourceFactory()->DeleteResource(resource);
}

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
#include "Catastrophe/Core/Resource/ResourceGroup.h"
#include "Catastrophe/Core/Resource/ResourceManager.h"

CE_NAMESPACE_BEGIN


int ResourceManager::m_resourceGroupIDGenerator = 0;


ResourceManager::ResourceManager()
{
	memset(m_resourceGroups, 0, MAX_RESOURCE_GROUPS * sizeof(ResourceGroup*));
}


ResourceManager::~ResourceManager()
{
	DeleteAllResources();

	for(int i(0); i < MAX_RESOURCE_GROUPS; ++i)
	{
		ResourceGroup* resourceGroup = m_resourceGroups[i];
		if(resourceGroup != null)
			delete resourceGroup;
	}
}


void ResourceManager::DeleteAllResources()
{
	for(int i(0); i < MAX_RESOURCE_GROUPS; ++i)
	{
		ResourceGroup* resourceGroup = m_resourceGroups[i];
		if(resourceGroup != null)
			resourceGroup->DeleteAllResources();
	}
}





CE_NAMESPACE_END

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

CE_NAMESPACE_BEGIN


//typedef Resource* (*ResourceCreateFunc)();
//typedef void (*ResourceDeleteFunc)(Resource*);

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


CE_NAMESPACE_END


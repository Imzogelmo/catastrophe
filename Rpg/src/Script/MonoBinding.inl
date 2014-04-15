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

#include <mono/metadata/object.h>
#include <mono/metadata/loader.h>

#include "MonoUtils.h"
#include "MonoBinding.h"

#ifdef _MSC_VER
	#pragma warning ( push )
	#pragma warning ( disable : 4996 )
#endif


char MonoBinding::sCurrentMonoBindingNamespaceString[128] = { 0 };
int MonoBinding::sCurrentMonoBindingNamespaceLength = 0;


void MonoBinding::SetNamespace( const char* name )
{
	if( name )
	{
		sCurrentMonoBindingNamespaceLength = strlen(name);
		memcpy(sCurrentMonoBindingNamespaceString, name, sCurrentMonoBindingNamespaceLength);
		sCurrentMonoBindingNamespaceString[sCurrentMonoBindingNamespaceLength] = 0;
	}
	else
	{
		sCurrentMonoBindingNamespaceString[0] = 0;
		sCurrentMonoBindingNamespaceLength = 0;
	}
}


void MonoBinding::AddInternalCall( const char* name, const void* method )
{
	char buffer[256];
	memcpy(buffer, sCurrentMonoBindingNamespaceString, sCurrentMonoBindingNamespaceLength);
	strcpy(buffer + sCurrentMonoBindingNamespaceLength, name);

	// Debug
	//MonoUtils::GetClassFromName(mono_domain
	//MonoUtils::GetClassMethodFromDecl(0, buffer);

	mono_add_internal_call(buffer, method);
}



#ifdef _MSC_VER
	#pragma warning ( pop )
#endif

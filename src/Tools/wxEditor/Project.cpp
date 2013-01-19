//////////////////////////////////////////////////////////////////////////
// This program is free software: you can redistribute it and/or modify //
// it under the terms of the GNU General Public License as published by //
// the Free Software Foundation, either version 3 of the License, or    //
// (at your option) any later version.                                  //
//                                                                      //
// This program is distributed in the hope that it will be useful,      //
// but WITHOUT ANY WARRANTY; without even the implied warranty of       //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        //
// GNU General Public License for more details.                         //
//////////////////////////////////////////////////////////////////////////

#include "Precompiled.h"

#include "Project.h"
#include "Directory.h"



Project::Project( const wxString& name, const wxString& directory )
{
	m_name = name;
	m_rootDirectory = directory;
}


Project::map_type* Project::GetFileMapPtr( ProjectItem::DataType type )
{
	map_type* ptr = 0;

	switch( type )
	{
		case ProjectItem::TypeImage: ptr = &m_imageFiles; break;
		case ProjectItem::TypeTileset: ptr = &m_tilesetFiles; break;
		case ProjectItem::TypeMap: ptr = &m_mapFiles; break;
	}

	return ptr;
}


void Project::GetItemPathsOfType( ProjectItem::DataType type, wxArrayString& outPaths )
{
	outPaths.clear();
	map_type* mapPtr = GetFileMapPtr( type );
	if(!mapPtr)
		return;

	for( map_type_iter it = mapPtr->begin(); it != mapPtr->end(); ++it )
	{
		outPaths.push_back( it->second.GetFullPath() );
	}
}


bool Project::ItemExists( const ProjectItem& item )
{
	map_type* mapPtr = GetFileMapPtr( item.GetType() );
	if(!mapPtr)
		return false;

	for( map_type_iter it = mapPtr->begin(); it != mapPtr->end(); ++it )
	{
		if( it->second == item )
			return true;
	}

	return false;
}


bool Project::AddFile( const wxString& name, const ProjectItem& item )
{
	map_type* mapPtr = GetFileMapPtr( item.GetType() );
	if(!mapPtr)
		return false;

	insert_iter ret = mapPtr->insert( pair_type(name, item) );
	if( ret.second )
		SetModified();

	return ret.second;
}



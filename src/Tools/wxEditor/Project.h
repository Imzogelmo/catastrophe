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

#pragma once

#include <wx/string.h>
#include <wx/filename.h>
#include <fc/vector_map.h>


class ProjectItem
{
public:
	enum DataType
	{
		TypeVirtualFolder,
		TypeImage,
		TypeMap,
		TypeTileset
	};

	ProjectItem() : m_type(), m_fullPath() {}
	ProjectItem( DataType type, const wxString& path ) : m_type(type), m_fullPath(path) {}

	bool operator == ( const ProjectItem& rhs ) {
		return (m_type == rhs.m_type && m_fullPath == rhs.m_fullPath);
	}

	bool operator != ( const ProjectItem& rhs ) {
		return !(*this == rhs);
	}

	wxString&		GetFullPath() { return m_fullPath; }
	const wxString&	GetFullPath() const { return m_fullPath; }

	DataType		GetType() const { return m_type; }

	DataType	m_type;
	wxString	m_fullPath;

};



class Project
{
public:
	typedef fc::pair<wxString, ProjectItem> pair_type;
	typedef fc::vector_map<wxString, ProjectItem> map_type;

	Project( const wxString& name, const wxString& directory );


	bool ItemExists( const ProjectItem& item );
	bool AddFile( const wxString& name, const ProjectItem& item );

	bool IsModified() const { return m_isModified; }
	void SetModified( bool modified = true ) { m_isModified = modified; }

	map_type*	GetFileMapPtr( ProjectItem::DataType type );
	void		GetItemPathsOfType( ProjectItem::DataType type, wxArrayString& outPaths );

	wxString&		GetName() { return m_name; }
	const wxString&	GetName() const { return m_name; }
	wxString&		GetDirectory() { return m_rootDirectory; }
	const wxString&	GetDirectory() const { return m_rootDirectory; }

protected:
	wxString	m_name;
	wxString	m_rootDirectory;

	map_type	m_imageFiles;
	map_type	m_tilesetFiles;
	map_type	m_mapFiles;

	bool		m_isModified;

};


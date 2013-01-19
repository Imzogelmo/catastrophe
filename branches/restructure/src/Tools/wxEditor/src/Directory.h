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
#include <wx/filefn.h>
#include <wx/tokenzr.h>
#include <wx/arrstr.h>
#include <wx/filename.h>
#include <wx/debug.h>
#include <fc/vector.h>


class CwdSaver 
{
public:
	CwdSaver()
	{
		m_cwd = wxGetCwd();
	}

	virtual ~CwdSaver()
	{
		wxSetWorkingDirectory( m_cwd );
	}

	const wxString& GetSavedDir() const
	{
		return m_cwd;
	}

protected:
	wxString m_cwd;
};


class CwdStack 
{
public:
	CwdStack()
	{
		m_stack.reserve(16);
		Push( wxGetCwd() );
	}

	~CwdStack()
	{
		while( !m_stack.empty() )
			m_stack.pop_back();
	}

	void Push( const wxString& dir )
	{
		m_stack.push_back( CwdSaver() );
		wxSetWorkingDirectory( dir );
	}

	void Pop()
	{
		assert(!m_stack.empty());
		m_stack.pop_back();
	}

	const wxString& Top() const
	{
		assert(!m_stack.empty());
		return m_stack.back().GetSavedDir();
	}

protected:
	fc::vector<CwdSaver> m_stack;
};




/********************
 * Helper Functions
 ********************/
static wxFileName _wxfn;


static void ConvertAbsolutePathToRelative( const wxString& cwDir, const wxString& absPath, wxString& outRelativePath, bool incFileExt = true )
{
	_wxfn.Clear();
	_wxfn.Assign(absPath);
	if( !_wxfn.MakeRelativeTo(cwDir) )
		return; //return empty string

	if( incFileExt )
		outRelativePath = _wxfn.GetFullPath();
	else
		outRelativePath = _wxfn.GetPath();
}


static wxString ConvertAbsolutePathToRelative( const wxString& cwDir, const wxString& absPath, bool incFileExt = true )
{
	wxString relPath;
	ConvertAbsolutePathToRelative( cwDir, absPath, relPath, incFileExt );

	return relPath;
}


static wxString ConvertAbsolutePathToRelative( const wxString& absPath, bool incFileExt = true )
{
	wxString relPath;
	ConvertAbsolutePathToRelative( wxGetCwd(), absPath, relPath, incFileExt );

	return relPath;
}


static void ConvertRelativePathToAbsolute( const wxString& cwDir, const wxString& relPath, wxString& outAbsPath, bool incFileExt = true )
{
	_wxfn.Clear();
	_wxfn.Assign(relPath);
	if( !_wxfn.MakeAbsolute(cwDir) )
		return; //return empty string

	if( incFileExt )
		outAbsPath = _wxfn.GetFullPath();
	else
		outAbsPath = _wxfn.GetPath();
}


static wxString ConvertRelativePathToAbsolute( const wxString& cwDir, const wxString& relPath, bool incFileExt = true )
{
	wxString absPath;
	ConvertRelativePathToAbsolute( cwDir, relPath, absPath, incFileExt );

	return absPath;
}


static wxString ConvertRelativePathToAbsolute( const wxString& relPath, bool incFileExt = true )
{
	wxString absPath;
	ConvertRelativePathToAbsolute( wxGetCwd(), relPath, absPath, incFileExt );

	return absPath;
}



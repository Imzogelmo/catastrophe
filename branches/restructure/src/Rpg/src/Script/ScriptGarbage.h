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

#include "Common.h"


struct GCStatistics
{
	size_t size;
	size_t total_destroyed;
	size_t total_detected;
	size_t objects;
	size_t destroyed;

	GCStatistics() :
		size(0),
		total_destroyed(0),
		total_detected(0),
		objects(0),
		destroyed(0)
	{}
};


struct GCPolicy
{
};


class ScriptGarbage
{
public:
	ScriptGarbage();

	asIScriptEngine* GetEngine() const { return m_enginePtr; }

	GCStatistics GetLastStatistices() const { return m_statistics; }
	GCStatistics GetCurrentStatistices() const;

	void Update();
	void GarbageCollect();
	void LogStatistics( const GCStatistics& s ) const;
	void SetEngine( asIScriptEngine* parent ) { m_enginePtr = parent; }

protected:
	asIScriptEngine*	m_enginePtr;
	GCStatistics		m_statistics;
	GCPolicy			m_policy;
	int					m_counter;

};




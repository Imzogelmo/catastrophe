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

#include <fc/string.h>
#include <Catastrophe/Math/Point.h>
#include <Catastrophe/Graphics/SpriteBatch.h>

#include "Common.h"
#include "GlobalSettings.h"
#include "ScreenManager.h"
#include "ResourceManager.h"
#include "Database.h"

#include "Script/ScriptEngine.h"
#include "Entity.h"



const unsigned char* gGetSystemFontString();

/*
 * Game specific settings class.
 */
class GameSettings
{
public:
	GameSettings() {}


	Point	res; //display resolution

};


class Game
{
public:
	Game() {}

	//if the Init method returns anything other than zero,
	//this means failure and have to shut down.
	int Initialize();
	void Shutdown();

	GameSettings* GetSettings() { return &m_settings; }
	ScriptEngine* GetScriptEngine() { return &m_scriptEngine; }
	ScreenManager* GetScreenManager() { return &m_screenManager; }
	ResourceManager* GetResourceManager() { return &m_resourceManager; }
	Database* GetDatabase() { return &m_database; }

	SpriteBatch* GetSpriteBatch() { return &m_spriteBatch; }

	void Update();
	void Render();

protected:
	int InternalInitScriptEngine();



protected:
	GameSettings	m_settings;
	ScriptEngine	m_scriptEngine;
	ScreenManager	m_screenManager;
	ResourceManager	m_resourceManager;

	Database		m_database;


	SpriteBatch		m_spriteBatch;

};



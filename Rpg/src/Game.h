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

 //todo remove these and use forward declaration
#include <fc/string.h> //todo remove me
#include <Catastrophe/Math/Point.h> //todo remove me
#include <Catastrophe/Graphics/SpriteBatch.h> //todo remove me

#include "Common.h"
#include "GlobalSettings.h"

 //todo remove these and use forward declaration
#include "ScreenManager.h"
#include "MonoScriptEngine.h"
#include "Entity.h"



const unsigned char* gGetSystemFontString();

/*
 * Game specific settings class.
 */
class GameSettings
{
public:
	GameSettings() {}


	int	displayResolutionX;
	int	displayResolutionY;
	int frameRate;

	float battleSpeed;
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
	MonoScriptEngine* GetScriptEngine() { return &m_scriptEngine; }
	ScreenManager* GetScreenManager() { return &m_screenManager; }

	SpriteBatch* GetSpriteBatch() { return &m_spriteBatch; }

	void Update();
	void Render();

protected:
	int InternalInitScriptEngine();



protected:
	GameSettings		m_settings;
	ScreenManager		m_screenManager;
	MonoScriptEngine	m_scriptEngine;


	SpriteBatch		m_spriteBatch;

};



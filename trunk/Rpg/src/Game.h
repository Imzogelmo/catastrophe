
#pragma once

#include <fc/string.h>
#include <Catastrophe/Math/Point.h>

#include "Common.h"
#include "GlobalSettings.h"

#include "Script/ScriptEngine.h"

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

	GameSettings* GetSettings() { return &m_settings; }
	ScriptEngine* GetScriptEngine() { return &m_scriptEngine; }


protected:
	int InternalInitScriptEngine();



protected:
	GameSettings	m_settings;
	ScriptEngine	m_scriptEngine;

};




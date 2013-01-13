
#pragma once

#include "Common.h"


class GlobalSettings
{
public:
	GlobalSettings()
		: m_configfile(0)
	{}

	~GlobalSettings();

	void Initialize();

	ConfigFile* GetConfigFile() { return m_configfile; }

private:
	ConfigFile* m_configfile;
};


extern GlobalSettings g_settings;

extern ConfigFile* gGetConfigFile();

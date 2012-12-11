
#pragma once

#include "Common.h"
#include "ConfigFile.h"


class GlobalSettings
{
public:
	ConfigFile* GetConfigFile() { return &m_configfile; }


private:
	ConfigFile m_configfile;
};


extern GlobalSettings g_settings;

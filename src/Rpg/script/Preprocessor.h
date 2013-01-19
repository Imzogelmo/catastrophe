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

#include <Engine/Util/BasicTimer.h>
#include <fc/string.h>
#include <fc/vector.h>

#include "../Common.h"
#include "PostProcessor.h"


class CppPreprocessor
{
public:
	int ProcessFile(
		int argc,
		char *argv[],
		fc::string& out_file
	);

	int ProcessFile(
		const fc::vector<fc::string>& _Args,
		const fc::string& filename,
		fc::string& out_file
	);

};


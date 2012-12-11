
#pragma once

#include <Catastrophe/Util/BasicTimer.h>
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


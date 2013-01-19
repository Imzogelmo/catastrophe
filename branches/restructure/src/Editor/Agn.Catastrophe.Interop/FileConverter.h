using namespace System;

#include "agn.h"

ns_agn_catastrophe_start
	public ref class FileConverter {
	public:
		bool Convert(String^ sourceFile, String^ targetDirectory, String^% error);
	};
ns_agn_catastrophe_end

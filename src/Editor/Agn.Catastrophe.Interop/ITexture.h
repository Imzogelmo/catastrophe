using namespace System;

#pragma once

#include "agn.h"

ns_agn_catastrophe_start
	public interface class ITexture {
	public:
		bool LoadFromFile(String^ fileName);
		// TODO Fill with other Texture methods and fields.
	};
ns_agn_catastrophe_end

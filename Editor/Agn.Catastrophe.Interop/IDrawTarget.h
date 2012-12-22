using namespace System;

#pragma once

#include "agn.h"

ns_agn_catastrophe_start
	public interface class IDrawTarget {
		property int Height {
			int get();
		};
		property array<Byte>^ RawData {
			array<Byte>^ get();
		};
		property int Width {
			int get();
		};
	};
ns_agn_catastrophe_end

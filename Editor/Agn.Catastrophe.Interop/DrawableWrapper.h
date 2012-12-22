using namespace System;

#include "agn.h"
#include "IDrawTarget.h"

ns_agn_catastrophe_start
	public ref class DrawableWrapper {
	private:
		IDrawTarget^ _target;
		void (*draw)(unsigned char*, int, int);
	public:
		DrawableWrapper(IDrawTarget^);
		void Draw();
	};
ns_agn_catastrophe_end

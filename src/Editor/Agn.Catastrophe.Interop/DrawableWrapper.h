using namespace System;

#include <time.h>
#include "agn.h"
#include "IDrawTarget.h"

ns_agn_catastrophe_start
	public enum class Drawable {
		Mock = 1
	};

	public ref class DrawableWrapper {
	private:
		time_t _last_time;
		IDrawTarget^ _target;
		void (*draw)(time_t, unsigned char*, int, int);
	public:
		DrawableWrapper(IDrawTarget^, Drawable);
		void Draw();
	};
ns_agn_catastrophe_end

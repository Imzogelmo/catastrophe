
#include "Stdafx.h"
#include "DrawableWrapper.h"
#include "IDrawTarget.h"
#include "MockDrawable.h"

using namespace std;
using namespace System::Runtime::InteropServices;

// TODO Remove once the drawable factory is created.
void mock_draw(time_t dt, unsigned char* pointer, int width, int height) {
	int index = 0;

	// Draw all green.
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; ++j) {
			pointer[index++] = 0; // Red
			pointer[index++] = 255; // Green
			pointer[index++] = 0; // Blue
		}
	}
}

Agn::Catastrophe::DrawableWrapper::DrawableWrapper(IDrawTarget^ target, Drawable drawable) {
	this->_last_time = 0;
	this->_target = target;
	// TODO Replace with a mechanism to discover the appropriate drawing routine.
	switch (drawable) {
	case Drawable::Mock:
		this->draw = &mock_draw;
		break;
	}
}

void Agn::Catastrophe::DrawableWrapper::Draw() {
	// If there is no data to write to, then just return.
	array<Byte>^ managed = this->_target->RawData;
	if (managed->Length <= 0) {
		return;
	}

	// Create a pointer to the array.
	GCHandle handle = GCHandle::Alloc(managed, GCHandleType::Pinned);
	try {
		// Cast as an unsigned character.
		unsigned char* pointer = (unsigned char*)(void*)handle.AddrOfPinnedObject();

		// Get the width/height.
		int height = this->_target->Height;
		int width = this->_target->Width;

		// Calculate delta-time.
		time_t dt = 0;
		time_t current = time(NULL);
		if (this->_last_time != 0) {
			dt = this->_last_time - current;
		}
		this->_last_time = current;
		
		// Call the delegate to the drawing routine.
		this->draw(dt, pointer, width, height);

	} finally {
		handle.Free();
	}
}
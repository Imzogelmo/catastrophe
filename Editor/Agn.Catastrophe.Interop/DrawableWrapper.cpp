
#include "Stdafx.h"
#include "DrawableWrapper.h"
#include "IDrawTarget.h"
#include "MockDrawable.h"

using namespace std;
using namespace System::Runtime::InteropServices;

// TODO Remove once the drawable factory is created.
void mock_draw(unsigned char* pointer, int width, int height) {
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

Agn::Catastrophe::DrawableWrapper::DrawableWrapper(IDrawTarget^ target) {
	this->_target = target;
	// TODO Replace with a mechanism to discover the appropriate drawing routine.
	this->draw = &mock_draw;
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
		
		// Call the delegate to the drawing routine.
		this->draw(pointer, width, height);

	} finally {
		handle.Free();
	}
}
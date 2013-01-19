
#include "Stdafx.h"
#include "StringWrapper.h"
#include <string>

using namespace std;
using namespace System::Runtime::InteropServices;

Agn::Catastrophe::StringWrapper::StringWrapper() {
	this->_managedValue = String::Empty;
	this->_nativePointer = nullptr;
}

Agn::Catastrophe::StringWrapper::StringWrapper(String^ value) {
	this->_managedValue = value;
	this->_nativePointer = nullptr;
}

Agn::Catastrophe::StringWrapper::~StringWrapper() {
	this->CleanUp();
}

void Agn::Catastrophe::StringWrapper::CleanUp() {
	// Only clean up the native resource if it actually has a pointer.
	if (this->_nativePointer != nullptr) {
		// Dereference the pointer and clean it up.
		Marshal::FreeHGlobal(*this->_nativePointer);
		this->_nativePointer = nullptr;
	}
}

String^ Agn::Catastrophe::StringWrapper::ManagedValue::get() {
	return this->_managedValue;
}

void Agn::Catastrophe::StringWrapper::ManagedValue::set(String^ value) {
	this->CleanUp();
	this->_managedValue = value;
}

string Agn::Catastrophe::StringWrapper::NativeValue::get() {
	// If the pointer has yet to be initialized, then convert the
	// managed value to the native value.
	if (this->_nativePointer == nullptr) {
		this->_nativePointer = Marshal::StringToHGlobalAnsi(this->_managedValue);
	}
	return (const char*)this->_nativePointer->ToPointer();
}

void Agn::Catastrophe::StringWrapper::NativeValue::set(string value) {
	this->CleanUp();
	this->_managedValue = gcnew String(value.c_str());
}
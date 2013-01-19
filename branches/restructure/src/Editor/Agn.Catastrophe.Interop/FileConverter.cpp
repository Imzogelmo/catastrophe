
#include "Stdafx.h"
#include "FileConverter.h"
#include "StringWrapper.h"
#include <string>

using namespace std;
using namespace System::Runtime::InteropServices;

bool Agn::Catastrophe::FileConverter::Convert(String^ sourceFile, String^ targetDirectory, String^% error) {
	
	StringWrapper^ errorWrapper = nullptr;
	StringWrapper^ sourceWrapper = nullptr;
	StringWrapper^ targetWrapper = nullptr;

	try { 
		// Create the managed to native wrappers.
		sourceWrapper = gcnew StringWrapper(sourceFile);
		targetWrapper = gcnew StringWrapper(targetDirectory);

		// Get the native values.
		string source = sourceWrapper->NativeValue;
		string target = targetWrapper->NativeValue;

		// TODO Work with source and target.

		// Create an error as necessary.
		errorWrapper = gcnew StringWrapper();
		errorWrapper->NativeValue = "Not Implemented";

		// Convert the error back.
		error = errorWrapper->ManagedValue;

		return String::IsNullOrWhiteSpace(error);
	}
	finally {
		// Clean up the native references.
		if (errorWrapper != nullptr) {
			delete errorWrapper;
		}
		if (sourceWrapper != nullptr) {
			delete sourceWrapper;
		}
		if (targetWrapper != nullptr) {
			delete targetWrapper;
		}
	}
}

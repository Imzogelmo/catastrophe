#include <string>
#include "agn.h"

using namespace std;
using namespace System;

ns_agn_catastrophe_start
	public ref class StringWrapper {
	private:
		String^ _managedValue;
		IntPtr^ _nativePointer;
		void CleanUp();
	public:
		StringWrapper();
		StringWrapper(String^);
		~StringWrapper();
		property String^ ManagedValue {
			String^ get();
			void set(String^);
		}
		property string NativeValue {
			string get();
			void set(string);
		}
	};
ns_agn_catastrophe_end
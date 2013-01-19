//using namespace System;

#pragma once

#include "agn.h"
#include "ITexture.h"
#include "StringWrapper.h"

#include <fc/string.h>
#include <ResourceManager.h>

ns_agn_catastrophe_start
	public ref class ResourceManagerWrapper {
	private:
		StringWrapper^ _base_directory;
		StringWrapper^ _font_directory;
		ResourceManager* _resource_manager;
		StringWrapper^ _texture_directory;
	public:
		ResourceManagerWrapper();
		~ResourceManagerWrapper();

		property String^ BaseDirectory {
			String^ get();
			void set(String^);
		};
		property String^ FontDirectory {
			String^ get();
			void set(String^);
		};
		property String^ TextureDirectory {
			String^ get();
			void set(String^);
		};
		
		void DeleteResources();
		ITexture^ GetTexture(String^ fileName);
		ITexture^ LoadTexture(String^ fileName);
		void ReloadGraphicsResources();
		void UnloadTexture(String^ fileName);
	};
ns_agn_catastrophe_end

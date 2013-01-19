
#include "Stdafx.h"
#include "ResourceManagerWrapper.h"
#include "ITexture.h"

// Specify all unmanaged work to do.
#pragma managed(push, off)
//void set_base_directory(ResourceManager* resource_manager, const char* value) {
//	//resource_manager->SetBaseDirectory(value);
//}
//
//void set_font_directory(ResourceManager* resource_manager, const char* value) {
//	//resource_manager->SetFontDirectory(value);
//}
//
//void set_texture_directory(ResourceManager* resource_manager, const char* value) {
//	//resource_manager->SetTextureDirectory(value);
//}
//
//void unload_texture(ResourceManager* resource_manager, const char* file_name) {
//	//resource_manager->UnloadTexture(file_name);
//}
#pragma managed(pop)

Agn::Catastrophe::ResourceManagerWrapper::ResourceManagerWrapper() {
	this->_base_directory = gcnew StringWrapper();
	this->_font_directory = gcnew StringWrapper();
	this->_texture_directory = gcnew StringWrapper();
	//this->_resource_manager = new ResourceManager();
}

Agn::Catastrophe::ResourceManagerWrapper::~ResourceManagerWrapper() {
	delete this->_base_directory;
	delete this->_font_directory;
	delete this->_texture_directory;
	//delete this->_resource_manager;
}

String^ Agn::Catastrophe::ResourceManagerWrapper::BaseDirectory::get() {
	return this->_base_directory->ManagedValue;
}

void Agn::Catastrophe::ResourceManagerWrapper::BaseDirectory::set(String^ value) {
	this->_base_directory->ManagedValue = value;
	/*set_base_directory(
		this->_resource_manager, 
		this->_base_directory->NativeValue.c_str());*/
}

String^ Agn::Catastrophe::ResourceManagerWrapper::FontDirectory::get() {
	return this->_font_directory->ManagedValue;
}

void Agn::Catastrophe::ResourceManagerWrapper::FontDirectory::set(String^ value) {
	this->_font_directory->ManagedValue = value;
	/*set_font_directory(
		this->_resource_manager, 
		this->_font_directory->NativeValue.c_str());*/
}

String^ Agn::Catastrophe::ResourceManagerWrapper::TextureDirectory::get() {
	return this->_texture_directory->ManagedValue;
}

void Agn::Catastrophe::ResourceManagerWrapper::TextureDirectory::set(String^ value) {
	this->_texture_directory->ManagedValue = value;
	/*set_texture_directory(
		this->_resource_manager, 
		this->_texture_directory->NativeValue.c_str());*/
}

void Agn::Catastrophe::ResourceManagerWrapper::DeleteResources() {
	//this->_resource_manager->DeleteResources();
}

Agn::Catastrophe::ITexture^ Agn::Catastrophe::ResourceManagerWrapper::GetTexture(String^ fileName) {
	StringWrapper^ wrapper = nullptr;
	try {
		wrapper = gcnew StringWrapper(fileName);
		//this->_resource_manager->GetTexture(wrapper->FcValue);
	} finally {
		if (wrapper != nullptr) {
			delete wrapper;
		}
	}
	return nullptr;
}

Agn::Catastrophe::ITexture^ Agn::Catastrophe::ResourceManagerWrapper::LoadTexture(String^ fileName) {
	StringWrapper^ wrapper = nullptr;
	try {
		wrapper = gcnew StringWrapper(fileName);
		//this->_resource_manager->LoadTexture(wrapper->FcValue);
	} finally {
		if (wrapper != nullptr) {
			delete wrapper;
		}
	}
	return nullptr;
}

void Agn::Catastrophe::ResourceManagerWrapper::ReloadGraphicsResources() {
	//this->_resource_manager->ReloadGraphicsResources();
}

void Agn::Catastrophe::ResourceManagerWrapper::UnloadTexture(String^ fileName) {
	StringWrapper^ wrapper = nullptr;
	try {
		wrapper = gcnew StringWrapper(fileName);
		//unload_texture(this->_resource_manager, wrapper->NativeValue.c_str());
	} finally {
		if (wrapper != nullptr) {
			delete wrapper;
		}
	}
}

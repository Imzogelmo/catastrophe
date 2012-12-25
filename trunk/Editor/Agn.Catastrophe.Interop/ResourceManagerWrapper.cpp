
#include "Stdafx.h"
#include "ResourceManagerWrapper.h"
#include "ITexture.h"

Agn::Catastrophe::ResourceManagerWrapper::ResourceManagerWrapper() {
	this->_base_directory = gcnew StringWrapper();
	this->_font_directory = gcnew StringWrapper();
	this->_texture_directory = gcnew StringWrapper();
}

Agn::Catastrophe::ResourceManagerWrapper::~ResourceManagerWrapper() {
	delete this->_base_directory;
	delete this->_font_directory;
	delete this->_texture_directory;
}

void Agn::Catastrophe::ResourceManagerWrapper::UpdateBaseDirectory() {
}

String^ Agn::Catastrophe::ResourceManagerWrapper::BaseDirectory::get() {
	return this->_base_directory->ManagedValue;
}

void Agn::Catastrophe::ResourceManagerWrapper::BaseDirectory::set(String^ value) {
	this->_base_directory->ManagedValue = value;
}

String^ Agn::Catastrophe::ResourceManagerWrapper::FontDirectory::get() {
	return this->_font_directory->ManagedValue;
}

void Agn::Catastrophe::ResourceManagerWrapper::FontDirectory::set(String^ value) {
	this->_font_directory->ManagedValue = value;
}

String^ Agn::Catastrophe::ResourceManagerWrapper::TextureDirectory::get() {
	return this->_texture_directory->ManagedValue;
}

void Agn::Catastrophe::ResourceManagerWrapper::TextureDirectory::set(String^ value) {
	this->_texture_directory->ManagedValue = value;
}

void Agn::Catastrophe::ResourceManagerWrapper::DeleteResources() {
}

Agn::Catastrophe::ITexture^ Agn::Catastrophe::ResourceManagerWrapper::GetTexture(String^ fileName) {
	return nullptr;
}

Agn::Catastrophe::ITexture^ Agn::Catastrophe::ResourceManagerWrapper::LoadTexture(String^ fileName) {
	return nullptr;
}

void Agn::Catastrophe::ResourceManagerWrapper::ReloadGraphicsResources() {
}

void Agn::Catastrophe::ResourceManagerWrapper::UnloadTexture(String^ fileName) {
}

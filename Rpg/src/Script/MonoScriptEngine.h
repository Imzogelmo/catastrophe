
#pragma once

#include "MonoUtils.h"
#include "MonoGC.h"
#include "MonoScriptObject.h"
#include "MonoScriptAssembly.h"


class MonoScriptEngine
{
public:
	MonoScriptEngine();

	int Initialize();
	int Shutdown();

	bool LoadCoreLibAssembly( const char* filename );
	bool LoadFrameworkAssembly( const char* filename );
	bool LoadScriptAssembly( const char* filename );

	bool UnloadScriptAssembly();

	void SetDefaultEngineProperties();
	void SetDefaults();
	void SetDefaultSearchDirectories( const char* assemblyDirectory, const char* configDirectory );
	void SetAssembliesPath( const char* path );

	MonoAssembly* GetCoreLibrary() const;
	MonoAssembly* GetFrameworkLibrary() const;
	MonoScriptAssembly* GetScriptAssembly() const;

	// Helpers
	MonoScriptObject* CreateScriptObject( const char* className );
	MonoScriptObject* CreateScriptObject( const char* className, const char* namespaceName );
	void DestroyScriptObject( MonoScriptObject* object );

	// Bindings
	void BindFramework();

protected:
	MonoDomain*			m_domain;
	MonoAssembly*		m_corelib;
	MonoAssembly*		m_frameworklib;
	MonoScriptAssembly	m_scriptlib;

};


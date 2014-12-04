
#pragma once

#include "MonoUtils.h"
#include "MonoScriptObject.h"

#include <fc/string.h>
#include <fc/vector_map.h>


/// @MonoScriptAssembly
///
/// Class that encapsulates a scripting assembly. This represents
/// all of our game scripts.

class MonoScriptAssembly
{
public:
	MonoScriptAssembly();
	MonoScriptAssembly( MonoDomain* domain, MonoAssembly* assembly );

	bool SetActive( bool force = false );
	bool IsActive() const;

	MonoDomain* GetMonoDomain() const;
	MonoAssembly* GetMonoAssembly() const;

	bool Load( MonoDomain* domain, const char* filename );
	bool Unload();

	void CallApplicationMain();
	MonoScriptObject* CreateScriptObject( const char* className );
	MonoScriptObject* CreateScriptObject( const char* className, const char* namespaceName );
	void DestroyScriptObject( MonoScriptObject* object );

	// Internal
	void GenerateClassInfo( MonoClass* monoClass, MonoScriptClassInfo& classInfo );
	MonoScriptClassInfo GetClassInfo( MonoClass* monoClass );

protected:
	typedef fc::vector_map<MonoClass*, MonoScriptClassInfo> ClassInfoMapType;

	MonoDomain*			m_domain;
	MonoAssembly*		m_assembly;
	String				m_name;
	String				m_defaultNamespace;
	ClassInfoMapType	m_classInfoTable;

};


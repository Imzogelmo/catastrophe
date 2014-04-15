
#include "MonoUtils.h"
#include "MonoScriptAssembly.h"



MonoScriptAssembly::MonoScriptAssembly() :
	m_domain(0),
	m_assembly(0)
{
}


MonoScriptAssembly::MonoScriptAssembly( MonoDomain* domain, MonoAssembly* assembly ) :
	m_domain(domain),
	m_assembly(assembly)
{
}


bool MonoScriptAssembly::SetActive( bool force )
{
	return mono_domain_set(m_domain, force) == MONO_TRUE;
}


bool MonoScriptAssembly::IsActive() const
{
	return m_domain == mono_domain_get();
}


MonoDomain* MonoScriptAssembly::GetMonoDomain() const
{
	return m_domain;
}


MonoAssembly* MonoScriptAssembly::GetMonoAssembly() const
{
	return m_assembly;
}


bool MonoScriptAssembly::Load( MonoDomain* domain, const char* filename )
{
	if( !m_assembly )
	{
		//m_domain = mono_domain_create_appdomain(); //todo

		m_assembly = MonoUtils::LoadAssembly(domain, filename);
		if( !m_assembly )
			return false;

		m_domain = domain;
		m_name = filename;
	}

	return true;
}


bool MonoScriptAssembly::Unload()
{
	// domains can only be dynamically unloaded as app domains. If
	// this is the root domain we have to wait for the script engine
	// to unload it.

	if( m_domain != mono_get_root_domain() )
	{
		if( IsActive() )
			mono_domain_set(mono_get_root_domain(), false);

		MonoObject* exception = 0;

		mono_domain_finalize(m_domain, -1);
		mono_domain_try_unload(m_domain, &exception);
		MonoUtils::HandleException(exception);
	}

	m_domain = 0;
	m_assembly = 0;
	m_name.clear();
	m_defaultNamespace.clear();
	m_classInfoTable.clear();

	return true;
}


void MonoScriptAssembly::CallApplicationMain()
{
	int argc = 1;
	char* argv[1] = { (char*)m_name.c_str() };

	mono_jit_exec(m_domain, m_assembly, argc, argv);
}


MonoScriptObject* MonoScriptAssembly::CreateScriptObject( const char* className )
{
	return CreateScriptObject(className, m_defaultNamespace.c_str());
}


MonoScriptObject* MonoScriptAssembly::CreateScriptObject( const char* className, const char* namespaceName )
{
	//MONO_ASSERT(m_scriptlib);
	MonoClass* monoClass = MonoUtils::GetClassFromName(m_assembly, namespaceName, className);
	if( !monoClass )
		return 0;

	MonoScriptClassInfo infoCache = GetClassInfo(monoClass);
	if( !infoCache.ctorMethod )
		return 0;

	MonoObject* monoObject = mono_object_new(m_domain, monoClass);
	if( !monoObject )
		return 0;

	MonoScriptObject* runtimeObject = new MonoScriptObject(monoObject, infoCache);
	return runtimeObject;
}


void MonoScriptAssembly::DestroyScriptObject( MonoScriptObject* object )
{
	delete object;
}



void MonoScriptAssembly::GenerateClassInfo( MonoClass* monoClass, MonoScriptClassInfo& classInfo )
{
	classInfo.classType = monoClass;

	// Ctor method
	// We need the class to be default constructable by default as the thunk
	// pointer takes no arguments. If a non-default ctor is required it will
	// have to be explicitely called after generating the normal method pointers.
	//
	MonoMethod* method = 0;
	method = mono_class_get_method_from_name(monoClass, ".ctor", 0);
	if( method )
		classInfo.ctorMethod = (UnmanagedThunkType0)mono_method_get_unmanaged_thunk(method);

	// Update method
	method = MonoUtils::GetVirtualClassMethodFromDecl(monoClass, ":Update()");
	if( method )
		classInfo.updateMethod = (UnmanagedThunkType0)mono_method_get_unmanaged_thunk(method);

	// Render method
	method = MonoUtils::GetVirtualClassMethodFromDecl(monoClass, ":Render()");
	if( method )
		classInfo.renderMethod = (UnmanagedThunkType0)mono_method_get_unmanaged_thunk(method);

}


MonoScriptClassInfo MonoScriptAssembly::GetClassInfo( MonoClass* monoClass )
{
	MonoScriptClassInfo classInfo;
	::memset(&classInfo, 0, sizeof(MonoScriptClassInfo));

	if( monoClass )
	{
		ClassInfoMapType::iterator it = m_classInfoTable.find(monoClass);
		if( it != m_classInfoTable.end() )
		{
			classInfo = it->second;
		}
		else // generate a new class cache.
		{
			GenerateClassInfo(monoClass, classInfo);
			m_classInfoTable.insert(monoClass, classInfo);
		}
	}

	return classInfo;
}

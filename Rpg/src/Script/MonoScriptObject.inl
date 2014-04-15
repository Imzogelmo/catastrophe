
#include "MonoUtils.h"
#include "MonoScriptObject.h"


MonoScriptObject::MonoScriptObject( const MonoScriptClassInfo& classInfo ) :
	m_object(0),
	m_classInfo(classInfo)
{
	if( classInfo.classType )
	{
		m_object = mono_object_new(mono_domain_get(), classInfo.classType);
		m_gcHandle = mono_gchandle_new(m_object, MONO_TRUE);
	}
}


MonoScriptObject::MonoScriptObject( MonoObject* object, MonoScriptClassInfo& classInfo ) :
	m_object(object),
	m_classInfo(classInfo)
{
}


MonoScriptObject::~MonoScriptObject()
{
	// Freeing the memory to the object simply means releasing the handle 
	// to the GC so it can be collected.

	if( m_gcHandle != 0 )
		mono_gchandle_free(m_gcHandle);
}


MonoObject* MonoScriptObject::CallObjectMethod( const char* decl, void** params )
{
	MonoMethod* method = MonoUtils::GetClassMethodFromDecl( m_classInfo.classType, decl );
	if( method )
		return MonoUtils::CallObjectMethod(m_object, method, params);

	return (MonoObject*)0;
}


MonoObject* MonoScriptObject::CallObjectVirtualMethod( const char* decl, void** params )
{
	MonoMethod* method = MonoUtils::GetVirtualClassMethodFromDecl( m_classInfo.classType, decl );
	if( method )
		return MonoUtils::CallObjectMethod(m_object, method, params);

	return (MonoObject*)0;
}


void MonoScriptObject::CallDefaultCtor()
{
	//MonoObject* object = mono_gchandle_get_target(m_gcHandle);
	if( m_classInfo.ctorMethod )
		MonoUtils::CallObjectUnmanagedThunk0(m_object, m_classInfo.ctorMethod);
}


void MonoScriptObject::CallUpdateMethod()
{
	if( m_classInfo.updateMethod )
		MonoUtils::CallObjectUnmanagedThunk0(m_object, m_classInfo.updateMethod);
}


void MonoScriptObject::CallRenderMethod()
{
	if( m_classInfo.renderMethod )
		MonoUtils::CallObjectUnmanagedThunk0(m_object, m_classInfo.renderMethod);
}

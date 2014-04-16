
#include "MonoUtils.h"
#include "MonoScriptEngine.h"
#include "MonoEngineBinding.h"



MonoScriptEngine::MonoScriptEngine() :
	m_domain(0),
	m_corelib(0),
	m_frameworklib(0),
	m_scriptlib()
{
}


int MonoScriptEngine::Initialize()
{
	if( !m_domain )
	{
		m_domain = MonoUtils::CreateDomain("system");
		if( !m_domain )
			return -1;
	}

	if( !LoadFrameworkAssembly("../Framework/bin/Release/Framework.dll") )
		return -2;

	BindFramework();

	if( !LoadCoreLibAssembly("mscorlib.dll") )
		return -3;

	return 0;
}


int MonoScriptEngine::Shutdown()
{
	if( m_domain )
	{
		UnloadScriptAssembly();

		mono_jit_cleanup(m_domain);
		m_domain = 0;
		m_corelib = 0;
		m_frameworklib = 0;
	}

	return 0;
}


bool MonoScriptEngine::LoadCoreLibAssembly( const char* filename )
{
	if( !m_corelib )
	{
		MonoImage* image = mono_get_corlib();
		if( image )
			m_corelib = mono_image_get_assembly(image);
	}

	if( !m_corelib )
		m_corelib = MonoUtils::LoadAssembly(m_domain, filename);

	return m_corelib != 0;
}


bool MonoScriptEngine::LoadFrameworkAssembly( const char* filename )
{
	if( !m_frameworklib )
		m_frameworklib = MonoUtils::LoadAssembly(m_domain, filename);

	return m_frameworklib != 0;
}


bool MonoScriptEngine::LoadScriptAssembly( const char* filename )
{
	return m_scriptlib.Load(m_domain, filename);
}


bool MonoScriptEngine::UnloadScriptAssembly()
{
	return m_scriptlib.Unload();
}


void MonoScriptEngine::SetDefaultEngineProperties()
{
	// just set defaults for now...
	SetDefaults();
}

void MonoScriptEngine::SetDefaults()
{
	MonoUtils::SetTraceLevel("info");
	MonoUtils::SetDefaultSearchDirectories("C:/mono/2.0", "C:/mono/2.0");
	MonoUtils::SetAssembliesPath("C:/mono/2.0");
}


void MonoScriptEngine::SetDefaultSearchDirectories( const char* assemblyDirectory, const char* configDirectory )
{
	MonoUtils::SetDefaultSearchDirectories(assemblyDirectory, configDirectory);
}


void MonoScriptEngine::SetAssembliesPath( const char* path )
{
	MonoUtils::SetAssembliesPath(path);
}


MonoAssembly* MonoScriptEngine::GetCoreLibrary() const
{
	return m_corelib;
}


MonoAssembly* MonoScriptEngine::GetFrameworkLibrary() const
{
	return m_frameworklib;
}


MonoScriptAssembly* MonoScriptEngine::GetScriptAssembly() const
{
	return (MonoScriptAssembly*)&m_scriptlib;
}


MonoScriptObject* MonoScriptEngine::CreateScriptObject( const char* className )
{
	return m_scriptlib.CreateScriptObject(className);
}


MonoScriptObject* MonoScriptEngine::CreateScriptObject( const char* className, const char* namespaceName )
{
	return m_scriptlib.CreateScriptObject(className, namespaceName);
}


void MonoScriptEngine::DestroyScriptObject( MonoScriptObject* object )
{
	return m_scriptlib.DestroyScriptObject(object);
}


void MonoScriptEngine::BindFramework()
{
	MonoEngineBinding::BindStaticString();
	MonoEngineBinding::BindMathf();
	MonoEngineBinding::BindVector2();
	MonoEngineBinding::BindCollision();
	MonoEngineBinding::BindTexture();
	MonoEngineBinding::BindSprite();
	//MonoEngineBinding::BindAnimatedSprite();
	MonoEngineBinding::BindSpriteBatch();
	MonoEngineBinding::BindVertexArray();
	MonoEngineBinding::BindInput();

}

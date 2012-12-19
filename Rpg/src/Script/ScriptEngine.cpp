// catastrophe rpg engine
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

#include <cstring>
#include <angelscript.h>

#include "ScriptEngine.h"
#include "Compiler.h"
#include "ByteCode.h"


#ifdef _MSC_VER
	#pragma warning ( push )
	#pragma warning ( disable : 4996 )
#endif


ScriptEngine::ScriptEngine()
	: m_engine(0)
{
}


ScriptEngine::~ScriptEngine()
{
	if(m_engine)
		m_engine->Release();
}


void ScriptEngine::Update()
{
	m_gc.Update();
}


void ScriptEngine::Initialize()
{
	ASSERT(m_gamePtr != 0);

	// this should be the ONLY place where the engine is created.
	if(!m_engine)
		m_engine = asCreateScriptEngine(ANGELSCRIPT_VERSION);

	ASSERT(m_engine);

	m_gc.SetEngine(m_engine);
	m_engine->SetUserData(this);
	m_engine->SetMessageCallback( asFUNCTION(MessageCallback), 0, asCALL_CDECL );
	SetDefaultEngineProperties();

	engine = m_engine; //fixme;
}


void ScriptEngine::SetDefaultEngineProperties()
{
	m_engine->SetEngineProperty( asEP_ALLOW_UNSAFE_REFERENCES, 1 );
	m_engine->SetEngineProperty( asEP_OPTIMIZE_BYTECODE, 1 );
	m_engine->SetEngineProperty( asEP_BUILD_WITHOUT_LINE_CUES, 1 );
	m_engine->SetEngineProperty( asEP_EXPAND_DEF_ARRAY_TO_TMPL, 1 );
}


void ScriptEngine::MessageCallback( const asSMessageInfo *msg, void *param )
{
	const char *type = "ERROR";
	if( msg->type == asMSGTYPE_WARNING ) 
		type = "WARNING";
	else if( msg->type == asMSGTYPE_INFORMATION ) 
		type = "INFO";

	char buffer[ 1024 ];
	//sprintf( &buffer[0], "%s (line %d, column %d) : %s : %s\n", msg->section, msg->row, msg->col, type, msg->message);
	sprintf( &buffer[0], "%s(%d) : %s : %s\n", msg->section, msg->row, type, msg->message);
	Log(buffer);
}


void ScriptEngine::SetException( asIScriptContext *ctx, const fc::string &str )
{
	ctx->SetException(str.c_str());
	LogException(ctx);
}


void ScriptEngine::LogException( asIScriptContext *ctx )
{
	if( ctx->GetState() == asEXECUTION_EXCEPTION )
	{
		asIScriptFunction* function = ctx->GetExceptionFunction();

		Log( "\tfunc: %s,", function->GetDeclaration() );
		Log( "\tmodl: %s,", function->GetModuleName() );
		Log( "\tsect: %s,", function->GetScriptSectionName() );
		Log( "\tline: %d,", ctx->GetExceptionLineNumber() );
		Log( "\tdesc: %s,", ctx->GetExceptionString() );

		Log("--- call stack ---");
		for( asUINT n = 1; n < ctx->GetCallstackSize(); ++n )
		{
			function = ctx->GetFunction(n);
			Log("\t%s (%d): %s", 
				function->GetScriptSectionName(),
				ctx->GetLineNumber(n),
				function->GetDeclaration()
			);
		}
	}
}


int ScriptEngine::SaveByteCode( const fc::string filename )
{
	BytecodeOutStream bytestream(filename);

	asIScriptModule *module = m_engine->GetModule(0);
	if( !module )
		return -1;

	int retval = module->SaveByteCode(&bytestream);
	if( retval < 0 )
	{
		//whoops
	}

	return retval;
}


int ScriptEngine::LoadByteCode( const fc::string filename )
{
	BytecodeInStream bytestream(filename);

	asIScriptModule *module = m_engine->GetModule(0);
	if( !module )
		module = m_engine->GetModule( 0, asGM_CREATE_IF_NOT_EXISTS );

	int retval = module->LoadByteCode(&bytestream);
	if( retval < 0 )
	{
		//whoops
	}

	return retval;
}


int ScriptEngine::Compile( const fc::string& filename, const fc::vector<fc::string>& _Args )
{
	// A lot of things can go wrong! :P
	int r				= 0;
	int failed_returns	= 0;
	int retval			= 0;
	int compiler_retval	= 0;
	int preproc_retval	= 0;
	int postproc_retval = 0;

	BasicTimer compile_time;

	// time it. :)
	//compile_time.StartTimer();

	ScriptCompiler precompiler;
	ScriptCompiler::map_type scripts;
	compiler_retval = precompiler.Compile( _Args, filename, &scripts, &preproc_retval, &postproc_retval );

	if( compiler_retval != 0 )
	{
		//oh jeez...have fun with that
		Log( "Compilation terminated from file: %s.", filename.c_str() );
		return -1;
	}


	compile_time.StartTimer();


	m_engine->DiscardModule(0);
	asIScriptModule *module = m_engine->GetModule( 0, asGM_CREATE_IF_NOT_EXISTS );
	if( !module )
	{
		Log( "Fatal error: Unable to create script module." );
		return -1;
	}


	//internal types
	//std::string igameobj( ImportIGameObjectCode() );
	//module->AddScriptSection( "igameobj", &igameobj[0], igameobj.size() );

	ScriptCompiler::map_type::iterator it;
	for( it = scripts.begin(); it != scripts.end(); ++ it )
	{
		r = module->AddScriptSection( (*it).first.c_str(), (*it).second.code.c_str(), (*it).second.code.size(), 0 );
		if( r < 0 ) 
		{
			Log( "Failed to compile file: %s.", (*it).first.c_str() );
			++failed_returns;
		}
	}


	// FINALY! -Build the damn thing already!
	if( failed_returns == 0 )
	{
		r = module->Build();
		if( r < 0 )
			retval = -1;
	}

	compile_time.StopTimer();

	Log( "Build finished with status: %d. Elapsed time: %d minutes, %.2f seconds.\n",
		retval,
		compile_time.GetMinutes(),
		compile_time.GetSeconds()
		);

	if( retval != 0 || compiler_retval != 0 || preproc_retval != 0 || failed_returns != 0 )
	{
		Log( "Build Failed." );
	}
	else Log( "Build Succeeded." );


	return retval;
}


void ScriptEngine::RegisterScriptingInterfaces()
{
	//message callback for script errors
	m_engine->SetMessageCallback( asFUNCTION(MessageCallback), 0, asCALL_CDECL );

	/* 
		These can get really picky depending on the binding order.
		Be sure not to create circular references when regestering them.
	*/

	//register the container types first.
	RegisterString();
	RegisterArrayTemplate();
	RegisterVectorTemplate();

	RegisterMathInterface();
	RegisterInputInterface();
	RegisterGraphicsInterface();

	RegisterScriptArrayTemplateSpecializations();
	RegisterScriptVectorTemplateSpecializations();

	RegisterGlobalFunctions();
}



#ifdef _MSC_VER
	#pragma warning ( pop )
#endif





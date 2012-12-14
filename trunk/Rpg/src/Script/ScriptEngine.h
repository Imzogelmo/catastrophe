
#pragma once

//#include <angelscript.h>
#include <fc/vector.h>
#include <fc/string.h>

#include "../Common.h"


class ScriptEngine
{
public:
	ScriptEngine();
	~ScriptEngine();

	void Initialize();
	void RegisterScriptingInterfaces();
	void SetDefaultEngineProperties();

	int Compile( const fc::string& filename, const fc::vector<fc::string>& _Args );

	void SetException( asIScriptContext *ctx, const fc::string& str = "" );
	void LogException( asIScriptContext *ctx );

	int SaveByteCode( const fc::string filename );
	int LoadByteCode( const fc::string filename );

	asIScriptEngine* GetEngine() const { return m_engine; }

	void SetGame( Game* parent ) { m_gamePtr = parent; }
	Game* GetGame() const { return m_gamePtr; }
 
private:
	void RegisterScriptInterfaces();

	//string
	void RegisterString();

	//arrays
	void RegisterArrayTemplate();
	void RegisterScriptArrayTemplateSpecializations();
	template <class T> void RegisterArrayTemplateSpecialization( const fc::string decl, const fc::string type );

	//vectors
	void RegisterVectorTemplate();
	void RegisterScriptVectorTemplateSpecializations();
	template <class T> void RegisterVectorTemplateSpecialization( const fc::string decl, const fc::string type );

	//math
	void RegisterMathInterface();
	void RegisterPoint();
	void RegisterVector2();
	void RegisterVector3();
	void RegisterVector4();
	void RegisterRect();
	void RegisterRectf();
	void RegisterMatrix();
	void RegisterMathFunctions();

	//input
	void RegisterInputInterface();
	void RegisterInput();
	void RegisterJoystick();
	void RegisterKeyboard();
	void RegisterMouse();

	//graphics
	void RegisterGraphicsInterface();
	void RegisterColor();
	void RegisterColorf();
	void RegisterColorConversions();
	void RegisterBlendMode();
	void RegisterTexture();
	void RegisterFont();
	void RegisterVertex();
	template <class T> void RegisterSpriteBase( const char* name );
	void RegisterSprite();
	void RegisterAnimatedSprite();

	//sound


	void RegisterGlobalFunctions();


	static void MessageCallback( const asSMessageInfo *msg, void *param );
	//static const char *ImportIGameObjectCode();
	//static void BindIObjectProperties();

private:
	//ScriptCompiler _precompiler;
	asIScriptEngine*		m_engine;
	asIScriptEngine*		engine;
	Game*					m_gamePtr;

	ScriptEngine(const ScriptEngine &);
	ScriptEngine &operator = (const ScriptEngine &);

};




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

#pragma once

#include <fc/string.h>
#include <fc/vector.h>

#include "Common.h"
#include "ScriptGarbage.h"


class ScriptEngine
{
public:
	ScriptEngine();
	~ScriptEngine();

	void Update();
	void Initialize();
	void RegisterScriptingInterfaces();
	void SetDefaultEngineProperties();

	int Compile( const fc::string& filename, const fc::vector<fc::string>& _Args );

	NO_INLINE void SetException( const fc::string& str = "" );
	NO_INLINE void SetException( asIScriptContext *ctx, const fc::string& str = "" );
	NO_INLINE void LogException( asIScriptContext *ctx );

	int SaveByteCode( const fc::string filename );
	int LoadByteCode( const fc::string filename );

	asIScriptEngine* GetEngine() const { return m_engine; }

	void SetGame( Game* parent ) { m_gamePtr = parent; }
	Game* GetGame() const { return m_gamePtr; }
	ContextPool* GetContextPool() const { return m_contextPool; }
 
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
	template <class T> void RegisterSpriteBase( const char* name, int extraClassFlags = 0 );
	template <class T> void RegisterSpriteAnimationBase( const char* name );
	void RegisterSprite();
	void RegisterSpriteAnimation();
	void RegisterAnimatedSprite();
	void RegisterAnimatedSpriteSet();

	//sound
	void RegisterSoundInterface();
	void RegisterSound();

	//ui
	void RegisterGuiInterface();
	template <class T> void RegisterWidgetType( const char* name );
	void RegisterFrame();

	//rpg
	//void RegisterRpgInterface();
	void RegisterRpgDataTypes();
	void RegisterActor();
	template <class T> void RegisterClassContainingAttributes( const char* name );
	template <class T> void RegisterCombatant( const char* name );

	//game
	void RegisterGameInterface();
	void RegisterGame();

	//global
	void RegisterGlobalFunctions();


	static void MessageCallback( const asSMessageInfo *msg, void *param );
	//static const char *ImportIGameObjectCode();
	//static void BindIObjectProperties();

private:
	//ScriptCompiler _precompiler;
	asIScriptEngine*		m_engine;
	asIScriptEngine*		engine;
	Game*					m_gamePtr;
	ScriptGarbage			m_gc;
	ContextPool*			m_contextPool;

	ScriptEngine(const ScriptEngine &);
	ScriptEngine &operator = (const ScriptEngine &);

};




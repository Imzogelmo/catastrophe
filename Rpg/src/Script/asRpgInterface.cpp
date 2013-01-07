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


#include <cassert>
#include <angelscript.h>

#include "asBindUtil.h"
#include "ScriptEngine.h"
#include "../Game.h"
#include "../MonsterData.h"


namespace script
{
	MonsterData* MonsterConstructor()
	{
		static MonsterData uninitializedMonster; //fixme
		return &uninitializedMonster;
		//return gGetActiveGame()->GetDatabase()->GetMonsterList()->GetMonster(0);
	}

} //namespace script


namespace script
{
	#define CLAMP_INDEX(x,y) \
		if(FC_UNLIKELY(x >= y)) x = 0;

	#define DECLARE_ATTRIB_GET(ret, decl, max) \
	ret decl( size_t index, Attributes* self ) \
	{ \
		if(FC_UNLIKELY(index >= max)) index = 0; \
		return self->attributes.operator [](index); \
	}

	//DECLARE_ATTRIB_GET(int, AttributesGetAttribute, MAX_ATTRIBUTES);
	//DECLARE_ATTRIB_GET(short, AttributesGetElement, MAX_ELEMENTS);
	//DECLARE_ATTRIB_GET(short, AttributesGetStatus, MAX_STATUS);


	int AttributesGetAttribute( size_t index, Attributes* self )
	{
		CLAMP_INDEX(index, MAX_ATTRIBUTES);
		return self->attributes[index];
	}

	short AttributesGetElement( size_t index, Attributes* self )
	{
		CLAMP_INDEX(index, MAX_ELEMENTS);
		return self->elements[index];
	}

	short AttributesGetStatus( size_t index, Attributes* self )
	{
		CLAMP_INDEX(index, MAX_STATUS);
		return self->status[index];
	}

	void AttributesSetAttribute( size_t index, int value, Attributes* self )
	{
		CLAMP_INDEX(index, MAX_ATTRIBUTES);
		self->attributes[index] = value;
	}

	void AttributesSetElement( size_t index, short value, Attributes* self )
	{
		CLAMP_INDEX(index, MAX_ELEMENTS);
		self->elements[index] = value;
	}

	void AttributesSetStatus( size_t index, short value, Attributes* self )
	{
		CLAMP_INDEX(index, MAX_STATUS);
		self->status[index] = value;
	}

} //namespace script


void ScriptEngine::RegisterMonster()
{
	int r(0);
	using namespace script;
	//r = engine->RegisterObjectType( "monster", 0, asOBJ_REF | asOBJ_SCOPED ); assert( r >= 0 );
	//r = engine->RegisterObjectBehaviour( "monster", asBEHAVE_FACTORY, "monster@ f()", asFUNCTION(MonsterConstructor), asCALL_CDECL ); assert( r >= 0 );
	//r = engine->RegisterObjectBehaviour( "monster", asBEHAVE_RELEASE, "void f()", asFUNCTION(DummyReleaseRef), asCALL_CDECL_OBJLAST ); assert( r >= 0 );
	//r = engine->RegisterObjectMethod( "monster", "monster &opAssign(const monster &in)", asFUNCTION((RefAssignment<Keyboard, Keyboard>)), asCALL_CDECL_OBJLAST ); assert( r >= 0 );



	r = engine->RegisterObjectType( "attributes", sizeof(Attributes), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_CA ); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "attributes", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ValueConstruct<Attributes>), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "attributes", asBEHAVE_CONSTRUCT, "void f(const attributes &in)", asFUNCTION(ValueCopyConstruct<Point>), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "attributes", "attributes& opAddAssign(const attributes &in)", asMETHODPR(Attributes, operator+=, (const Attributes &), Attributes&), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "attributes", "attributes& opSubAssign(const attributes &in)", asMETHODPR(Attributes, operator-=, (const Attributes &), Attributes&), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "attributes", "attributes opAdd(const attributes &in) const", asMETHODPR(Attributes, operator +, (const Attributes&) const, Attributes), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "attributes", "attributes opSub(const attributes &in) const", asMETHODPR(Attributes, operator -, (const Attributes&) const, Attributes), asCALL_THISCALL); assert( r >= 0 );

	r = engine->RegisterObjectMethod( "attributes", "int get_stat(int) const", asFUNCTION(AttributesGetAttribute), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "attributes", "int16 get_element(int)", asFUNCTION(AttributesGetElement), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "attributes", "int16 get_status(int)", asFUNCTION(AttributesGetStatus), asCALL_CDECL_OBJLAST); assert( r >= 0 );

	r = engine->RegisterObjectMethod( "attributes", "void set_stat(int, int) const", asFUNCTION(AttributesSetAttribute), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "attributes", "void set_element(int, int16)", asFUNCTION(AttributesSetElement), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "attributes", "void set_status(int, int16)", asFUNCTION(AttributesSetStatus), asCALL_CDECL_OBJLAST); assert( r >= 0 );

}


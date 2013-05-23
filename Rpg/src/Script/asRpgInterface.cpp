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
#include "Game.h"

#include "MonsterData.h"
#include "CharacterData.h"


#include "Monster.h"
#include "Buff.h"
#include "Equipment.h"

// TODO: engine <--> script character integration.
//       
#include "Character.h"
#include "Actor.h"


namespace script
{
	Monster* MonsterConstructor()
	{
		static Monster uninitializedMonster; //fixme
		return &uninitializedMonster;
		//return gGetGame()->GetDatabase()->GetMonsterList()->GetMonster(0);
	}

	void BindPlayerCharacterProperties()
	{
		if( 1 )
		{
			asIScriptObject* obj = (asIScriptObject*)asGetActiveContext()->GetThisPointer();

			//p_ptr->sprite			= (Sprite*)obj->GetAddressOfProperty(0);
		}
	}

} //namespace script


namespace script
{
	#define CLAMP_INDEX(x,y) \
		if(FC_UNLIKELY(x >= y)) { x = 0; LogDebug("Attribute index out of range."); }

	int AttributesGetMaxParam( size_t index, Attributes* self )
	{
		CLAMP_INDEX(index, MAX_PARAMS);
		return self->max_params[index];
	}

	int AttributesGetStat( size_t index, Attributes* self )
	{
		CLAMP_INDEX(index, MAX_STATS);
		return self->stats[index];
	}
/*
	short AttributesGetElement( size_t index, Attributes* self )
	{
		CLAMP_INDEX(index, MAX_ELEMENTS);
		return self->elements[index];
	}
*/
	int AttributesGetStatusAtk( size_t index, Attributes* self )
	{
		CLAMP_INDEX(index, MAX_STATUS);
		return self->status_atk[index];
	}

	int AttributesGetStatusDef( size_t index, Attributes* self )
	{
		CLAMP_INDEX(index, MAX_STATUS);
		return self->status_def[index];
	}


	void AttributesSetMaxParam( size_t index, int value, Attributes* self )
	{
		CLAMP_INDEX(index, MAX_PARAMS);
		self->max_params[index] = value;
	}

	void AttributesSetStat( size_t index, int value, Attributes* self )
	{
		CLAMP_INDEX(index, MAX_STATS);
		self->stats[index] = value;
	}
/*
	void AttributesSetElement( size_t index, short value, Attributes* self )
	{
		CLAMP_INDEX(index, MAX_ELEMENTS);
		self->elements[index] = value;
	}
*/
	void AttributesSetStatusAtk( size_t index, int value, Attributes* self )
	{
		CLAMP_INDEX(index, MAX_STATUS);
		self->status_atk[index] = value;
	}

	void AttributesSetStatusDef( size_t index, int value, Attributes* self )
	{
		CLAMP_INDEX(index, MAX_STATUS);
		self->status_def[index] = value;
	}

} //namespace script




void ScriptEngine::RegisterRpgDataTypes()
{
	int r(0);
	using namespace script;

	// Attributes
	r = engine->RegisterObjectType( "attributes", sizeof(Attributes), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_CA ); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "attributes", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ValueConstruct<Attributes>), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "attributes", asBEHAVE_CONSTRUCT, "void f(const attributes &in)", asFUNCTION(ValueCopyConstruct<Attributes>), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "attributes", "attributes& opAddAssign(const attributes &in)", asMETHODPR(Attributes, operator+=, (const Attributes &), Attributes&), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "attributes", "attributes& opSubAssign(const attributes &in)", asMETHODPR(Attributes, operator-=, (const Attributes &), Attributes&), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "attributes", "attributes opAdd(const attributes &in) const", asMETHODPR(Attributes, operator +, (const Attributes&) const, Attributes), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "attributes", "attributes opSub(const attributes &in) const", asMETHODPR(Attributes, operator -, (const Attributes&) const, Attributes), asCALL_THISCALL); assert( r >= 0 );

	r = engine->RegisterObjectMethod( "attributes", "int get_max_param(int) const", asFUNCTION(AttributesGetMaxParam), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "attributes", "int get_stat(int) const", asFUNCTION(AttributesGetStat), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	//r = engine->RegisterObjectMethod( "attributes", "int get_element(int)", asFUNCTION(AttributesGetElement), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "attributes", "int get_status_atk(int)", asFUNCTION(AttributesGetStatusAtk), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "attributes", "int get_status_def(int)", asFUNCTION(AttributesGetStatusDef), asCALL_CDECL_OBJLAST); assert( r >= 0 );

	r = engine->RegisterObjectMethod( "attributes", "void set_max_param(int, int) const", asFUNCTION(AttributesSetMaxParam), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "attributes", "void set_stat(int, int) const", asFUNCTION(AttributesSetStat), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	//r = engine->RegisterObjectMethod( "attributes", "void set_element(int, int)", asFUNCTION(AttributesSetElement), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "attributes", "void set_status_atk(int, int)", asFUNCTION(AttributesSetStatusAtk), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "attributes", "void set_status_def(int, int)", asFUNCTION(AttributesSetStatusDef), asCALL_CDECL_OBJLAST); assert( r >= 0 );


	// Item
	r = engine->RegisterObjectType( "item", sizeof(Item), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_CA ); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "item", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ValueConstruct<Item>), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "item", asBEHAVE_CONSTRUCT, "void f(const attributes &in)", asFUNCTION(ValueCopyConstruct<Item>), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "item", "string name", offsetof(Item, name)); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "item", "string script", offsetof(Item, script)); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "item", "string description", offsetof(Item, description)); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "item", "int id", offsetof(Item, id)); assert( r >= 0 );



	// Equipment
	r = engine->RegisterObjectType( "equipment", sizeof(Equipment), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_CDAK ); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "equipment", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ValueConstruct<Equipment>), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "equipment", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(ValueDestruct<Equipment>), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "equipment", asBEHAVE_CONSTRUCT, "void f(const attributes &in)", asFUNCTION(ValueCopyConstruct<Equipment>), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "equipment", "equipment &opAssign(const equipment &in)", asFUNCTION((ValueAssignment<Equipment, Equipment>)), asCALL_CDECL_OBJLAST); assert( r >= 0 );



	// Buff
	r = engine->RegisterObjectType( "buff", sizeof(Buff), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_CDA ); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "buff", "attributes attributes", offsetof(Buff, attributes)); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "buff", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ValueConstruct<Buff>), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "buff", asBEHAVE_CONSTRUCT, "void f(const attributes &in)", asFUNCTION(ValueCopyConstruct<Buff>), asCALL_CDECL_OBJLAST); assert( r >= 0 );


	// CharacterData
	r = engine->RegisterObjectType( "character_data", sizeof(CharacterData), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_CDAK ); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "character_data", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ValueConstruct<CharacterData>), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "character_data", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(ValueDestruct<CharacterData>), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "character_data", asBEHAVE_CONSTRUCT, "void f(const monster_data &in)", asFUNCTION(ValueCopyConstruct<CharacterData>), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "character_data", "character_data &opAssign(const monster_data &in)", asFUNCTION((ValueAssignment<CharacterData, CharacterData>)), asCALL_CDECL_OBJLAST); assert( r >= 0 );

	r = engine->RegisterObjectProperty( "character_data", "string name", offsetof(CharacterData, name)); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "character_data", "string script", offsetof(CharacterData, script)); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "character_data", "string description", offsetof(CharacterData, description)); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "character_data", "int id", offsetof(CharacterData, id)); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "character_data", "int race_id", offsetof(CharacterData, race_id)); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "character_data", "int class_id", offsetof(CharacterData, class_id)); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "character_data", "int portrait_id", offsetof(CharacterData, portrait_id)); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "character_data", "int map_spriteset_id", offsetof(CharacterData, map_spriteset_id)); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "character_data", "int battle_spriteset_id", offsetof(CharacterData, battle_spriteset_id)); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "character_data", "int lv", offsetof(CharacterData, lv)); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "character_data", "int exp", offsetof(CharacterData, exp)); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "character_data", "int gold", offsetof(CharacterData, gold)); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "character_data", "attributes attributes", offsetof(CharacterData, attributes)); assert( r >= 0 );


	// MonsterData
	r = engine->RegisterObjectType( "monster_data", sizeof(MonsterData), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_CDAK ); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "monster_data", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ValueConstruct<MonsterData>), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "monster_data", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(ValueDestruct<MonsterData>), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "monster_data", asBEHAVE_CONSTRUCT, "void f(const monster_data &in)", asFUNCTION(ValueCopyConstruct<MonsterData>), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "monster_data", "monster_data &opAssign(const monster_data &in)", asFUNCTION((ValueAssignment<MonsterData, MonsterData>)), asCALL_CDECL_OBJLAST); assert( r >= 0 );

	r = engine->RegisterObjectProperty( "monster_data", "string name", offsetof(MonsterData, name)); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "monster_data", "string script", offsetof(MonsterData, script)); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "monster_data", "string description", offsetof(MonsterData, description)); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "monster_data", "int id", offsetof(MonsterData, id)); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "monster_data", "int portrait_id", offsetof(MonsterData, portrait_id)); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "monster_data", "int map_spriteset_id", offsetof(MonsterData, map_spriteset_id)); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "monster_data", "int battle_spriteset_id", offsetof(MonsterData, battle_spriteset_id)); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "monster_data", "int lv", offsetof(MonsterData, lv)); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "monster_data", "int exp", offsetof(MonsterData, exp)); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "monster_data", "int gold", offsetof(MonsterData, gold)); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "monster_data", "attributes attributes", offsetof(MonsterData, attributes)); assert( r >= 0 );
	//r = engine->RegisterObjectProperty( "monster_data", "item_dropset item_dropset", offsetof(MonsterData, item_dropset)); assert( r >= 0 );




}




void ScriptEngine::RegisterActor()
{
	int r(0);
	using namespace script;

	// CharacterData
	r = engine->RegisterObjectType( "actor", sizeof(Actor), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_CDAK ); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "actor", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ValueConstruct<Actor>), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "actor", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(ValueDestruct<Actor>), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "actor", asBEHAVE_CONSTRUCT, "void f(const monster_data &in)", asFUNCTION(ValueCopyConstruct<Actor>), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "actor", "character_data &opAssign(const monster_data &in)", asFUNCTION((ValueAssignment<Actor, Actor>)), asCALL_CDECL_OBJLAST); assert( r >= 0 );

	r = engine->RegisterObjectProperty( "actor", "string name", offsetof(Actor, name)); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "actor", "string script", offsetof(Actor, script)); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "actor", "int id", offsetof(Actor, id)); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "actor", "int portrait_id", offsetof(Actor, portrait_id)); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "actor", "int map_spriteset_id", offsetof(Actor, map_spriteset_id)); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "actor", "int battle_spriteset_id", offsetof(Actor, battle_spriteset_id)); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "actor", "int lv", offsetof(CharacterData, lv)); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "actor", "int exp", offsetof(CharacterData, exp)); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "actor", "int gold", offsetof(CharacterData, gold)); assert( r >= 0 );



	//test
	RegisterCombatant<Actor>("actor");




	//r = engine->RegisterObjectType( "monster", 0, asOBJ_REF | asOBJ_SCOPED ); assert( r >= 0 );
	//r = engine->RegisterObjectBehaviour( "monster", asBEHAVE_FACTORY, "monster@ f()", asFUNCTION(MonsterConstructor), asCALL_CDECL ); assert( r >= 0 );
	//r = engine->RegisterObjectBehaviour( "monster", asBEHAVE_RELEASE, "void f()", asFUNCTION(DummyReleaseRef), asCALL_CDECL_OBJLAST ); assert( r >= 0 );
	//r = engine->RegisterObjectMethod( "monster", "monster &opAssign(const monster &in)", asFUNCTION((RefAssignment<Keyboard, Keyboard>)), asCALL_CDECL_OBJLAST ); assert( r >= 0 );


}


template <class T>
void ScriptEngine::RegisterClassContainingAttributes( const char* name )
{
	int r(0);
	using namespace script;
	r = engine->RegisterObjectMethod( name, "int get_param(int) const", asMETHODPR(T, GetParam, (int) const, int), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( name, "int get_max_param(int) const", asMETHODPR(T, GetMaxParam, (int) const, int), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( name, "int get_base_max_param(int) const", asMETHODPR(T, GetBaseMaxParam, (int) const, int), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( name, "int get_stat(int) const", asMETHODPR(T, GetStat, (int) const, int), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( name, "int get_base_stat(int) const", asMETHODPR(T, GetBaseStat, (int) const, int), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( name, "int get_status_atk(int) const", asMETHODPR(T, GetStatusAtk, (int) const, int), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( name, "int get_status_def(int) const", asMETHODPR(T, GetStatusDef, (int) const, int), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( name, "int get_base_status_atk(int) const", asMETHODPR(T, GetBaseStatusAtk, (int) const, int), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( name, "int get_base_status_def(int) const", asMETHODPR(T, GetBaseStatusDef, (int) const, int), asCALL_THISCALL ); assert( r >= 0 );

	r = engine->RegisterObjectMethod( name, "void set_param(int, int) const", asMETHODPR(T, SetParam, (int, int), void), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( name, "void set_base_max_param(int, int) const", asMETHODPR(T, SetBaseMaxParam, (int, int), void), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( name, "void set_base_stat(int, int) const", asMETHODPR(T, SetBaseStat, (int, int), void), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( name, "void set_base_status_atk(int, int) const", asMETHODPR(T, SetBaseStatusAtk, (int, int), void), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( name, "void set_base_status_def(int, int) const", asMETHODPR(T, SetBaseStatusDef, (int, int), void), asCALL_THISCALL ); assert( r >= 0 );

	r = engine->RegisterObjectMethod( name, "const attributes& get_attributes() const", asMETHODPR(T, GetBaseAttributes, (void) const, const Attributes&), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( name, "const equipment& get_equipment() const", asMETHODPR(T, GetEquipment, (void) const, const Equipment&), asCALL_THISCALL ); assert( r >= 0 );
	//r = engine->RegisterObjectMethod( name, "const equipment& get_equipment() const", asMETHODPR(T, GetEquipment, (void) const, const Equipment&), asCALL_THISCALL ); assert( r >= 0 );

}


template <class T>
void ScriptEngine::RegisterCombatant( const char* name )
{
	fc::string decl = name;
	fc::string factory_decl = decl + "@ f()";
	fc::string const_ref = "const " + decl + " &in";
	fc::string opAssignString(decl);
	opAssignString.append(" &opAssign(").append(const_ref).append(")");

	int r(0);
	using namespace script;

	//Single handle type..?
	//r = engine->RegisterObjectType( "combatant", 0, asOBJ_REF | asOBJ_SCOPED ); assert( r >= 0 );
	//r = engine->RegisterObjectBehaviour( "combatant", asBEHAVE_FACTORY, "monster@ f()", asFUNCTION(MonsterConstructor), asCALL_CDECL ); assert( r >= 0 );
	//r = engine->RegisterObjectBehaviour( "combatant", asBEHAVE_RELEASE, "void f()", asFUNCTION(DummyReleaseRef), asCALL_CDECL_OBJLAST ); assert( r >= 0 );
	//r = engine->RegisterObjectMethod( name, "monster &opAssign(const monster &in)", asFUNCTION((RefAssignment<Keyboard, Keyboard>)), asCALL_CDECL_OBJLAST ); assert( r >= 0 );

	RegisterClassContainingAttributes<T>(name);

}




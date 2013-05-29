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

#include "Buff.h"
#include "Equipment.h"

// TODO: engine <--> script character integration.
//       
#include "Actor.h"
#include "Party.h"

#include "Entity.h"
#include "Combatant.h"


namespace script
{

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
		return (int)self->max_params[index];
	}

	int AttributesGetStat( size_t index, Attributes* self )
	{
		CLAMP_INDEX(index, MAX_STATS);
		return (int)self->stats[index];
	}

	int AttributesGetElementDef( size_t index, Attributes* self )
	{
		CLAMP_INDEX(index, MAX_ELEMENTS);
		return (int)self->elemental_def[index];
	}

	int AttributesGetStatusAtk( size_t index, Attributes* self )
	{
		CLAMP_INDEX(index, MAX_STATUS);
		return (int)self->status_atk[index];
	}

	int AttributesGetStatusDef( size_t index, Attributes* self )
	{
		CLAMP_INDEX(index, MAX_STATUS);
		return (int)self->status_def[index];
	}


	void AttributesSetMaxParam( size_t index, int value, Attributes* self )
	{
		CLAMP_INDEX(index, MAX_PARAMS);
		self->SetMaxParam(index, value);
	}

	void AttributesSetStat( size_t index, int value, Attributes* self )
	{
		CLAMP_INDEX(index, MAX_STATS);
		self->SetStat(index, value);
	}

	void AttributesSetElementalDef( size_t index, short value, Attributes* self )
	{
		CLAMP_INDEX(index, MAX_ELEMENTS);
		self->SetElementalDef(index, value);
	}

	void AttributesSetStatusAtk( size_t index, int value, Attributes* self )
	{
		CLAMP_INDEX(index, MAX_STATUS);
		self->SetStatusAtk(index, value);
	}

	void AttributesSetStatusDef( size_t index, int value, Attributes* self )
	{
		CLAMP_INDEX(index, MAX_STATUS);
		self->SetStatusDef(index, value);
	}

} //namespace script




void ScriptEngine::RegisterRpgDataTypes()
{
	int r(0);
	using namespace script;

	// Attributes
	r = engine->RegisterObjectType( "attributes", sizeof(Attributes), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_CA ); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "attributes", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ValueConstruct<Attributes>), asCALL_CDECL_OBJLAST ); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "attributes", asBEHAVE_CONSTRUCT, "void f(const attributes &in)", asFUNCTION(ValueCopyConstruct<Attributes>), asCALL_CDECL_OBJLAST ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "attributes", "attributes& opAddAssign(const attributes &in)", asMETHODPR(Attributes, operator+=, (const Attributes &), Attributes&), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "attributes", "attributes& opSubAssign(const attributes &in)", asMETHODPR(Attributes, operator-=, (const Attributes &), Attributes&), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "attributes", "attributes opAdd(const attributes &in) const", asMETHODPR(Attributes, operator +, (const Attributes&) const, Attributes), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "attributes", "attributes opSub(const attributes &in) const", asMETHODPR(Attributes, operator -, (const Attributes&) const, Attributes), asCALL_THISCALL ); assert( r >= 0 );

	r = engine->RegisterObjectMethod( "attributes", "int get_max_param(int) const", asFUNCTION(AttributesGetMaxParam), asCALL_CDECL_OBJLAST ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "attributes", "int get_stat(int) const", asFUNCTION(AttributesGetStat), asCALL_CDECL_OBJLAST ); assert( r >= 0 );
	//r = engine->RegisterObjectMethod( "attributes", "int get_element(int)", asFUNCTION(AttributesGetElement), asCALL_CDECL_OBJLAST ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "attributes", "int get_status_atk(int)", asFUNCTION(AttributesGetStatusAtk), asCALL_CDECL_OBJLAST ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "attributes", "int get_status_def(int)", asFUNCTION(AttributesGetStatusDef), asCALL_CDECL_OBJLAST ); assert( r >= 0 );

	r = engine->RegisterObjectMethod( "attributes", "void set_max_param(int, int) const", asFUNCTION(AttributesSetMaxParam), asCALL_CDECL_OBJLAST ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "attributes", "void set_stat(int, int) const", asFUNCTION(AttributesSetStat), asCALL_CDECL_OBJLAST ); assert( r >= 0 );
	//r = engine->RegisterObjectMethod( "attributes", "void set_element(int, int)", asFUNCTION(AttributesSetElement), asCALL_CDECL_OBJLAST ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "attributes", "void set_status_atk(int, int)", asFUNCTION(AttributesSetStatusAtk), asCALL_CDECL_OBJLAST ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "attributes", "void set_status_def(int, int)", asFUNCTION(AttributesSetStatusDef), asCALL_CDECL_OBJLAST ); assert( r >= 0 );


	// Item
	// ...BIG BUG... item < equipment_item. item is virtual, therefore item can never have attributes.
	r = engine->RegisterObjectType( "item", sizeof(Item), asOBJ_VALUE | asOBJ_APP_CLASS_CDAK ); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "item", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ValueConstruct<Item>), asCALL_CDECL_OBJLAST ); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "item", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(ValueDestruct<Item>), asCALL_CDECL_OBJLAST ); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "item", asBEHAVE_CONSTRUCT, "void f(const item &in)", asFUNCTION(ValueCopyConstruct<Item>), asCALL_CDECL_OBJLAST ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "item", "item &opAssign(const item &in)", asFUNCTION((ValueAssignment<Item, Item>)), asCALL_CDECL_OBJLAST ); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "item", "string name", offsetof(Item, name)); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "item", "string script", offsetof(Item, script)); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "item", "string description", offsetof(Item, description)); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "item", "int id", offsetof(Item, id)); assert( r >= 0 );


	// Inventory
	r = engine->RegisterObjectType( "inventory", sizeof(Inventory), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_CDAK ); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "inventory", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ValueConstruct<Inventory>), asCALL_CDECL_OBJLAST ); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "inventory", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(ValueDestruct<Inventory>), asCALL_CDECL_OBJLAST ); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "inventory", asBEHAVE_CONSTRUCT, "void f(const inventory &in)", asFUNCTION(ValueCopyConstruct<Inventory>), asCALL_CDECL_OBJLAST ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "inventory", "inventory &opAssign(const inventory &in)", asFUNCTION((ValueAssignment<Inventory, Inventory>)), asCALL_CDECL_OBJLAST ); assert( r >= 0 );


	// Equipment
	r = engine->RegisterObjectType( "equipment", sizeof(Equipment), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_CDAK ); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "equipment", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ValueConstruct<Equipment>), asCALL_CDECL_OBJLAST ); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "equipment", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(ValueDestruct<Equipment>), asCALL_CDECL_OBJLAST ); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "equipment", asBEHAVE_CONSTRUCT, "void f(const equipment &in)", asFUNCTION(ValueCopyConstruct<Equipment>), asCALL_CDECL_OBJLAST ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "equipment", "equipment &opAssign(const equipment &in)", asFUNCTION((ValueAssignment<Equipment, Equipment>)), asCALL_CDECL_OBJLAST ); assert( r >= 0 );


	// Buff
	r = engine->RegisterObjectType( "buff", sizeof(Buff), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_CDAK ); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "buff", "attributes attributes", offsetof(Buff, attributes)); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "buff", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ValueConstruct<Buff>), asCALL_CDECL_OBJLAST ); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "buff", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(ValueDestruct<Buff>), asCALL_CDECL_OBJLAST ); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "buff", asBEHAVE_CONSTRUCT, "void f(const buff &in)", asFUNCTION(ValueCopyConstruct<Buff>), asCALL_CDECL_OBJLAST ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "buff", "buff &opAssign(const buff &in)", asFUNCTION((ValueAssignment<Buff, Buff>)), asCALL_CDECL_OBJLAST ); assert( r >= 0 );


	// CharacterData
	r = engine->RegisterObjectType( "character_data", sizeof(CharacterData), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_CDAK ); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "character_data", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ValueConstruct<CharacterData>), asCALL_CDECL_OBJLAST ); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "character_data", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(ValueDestruct<CharacterData>), asCALL_CDECL_OBJLAST ); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "character_data", asBEHAVE_CONSTRUCT, "void f(const character_data &in)", asFUNCTION(ValueCopyConstruct<CharacterData>), asCALL_CDECL_OBJLAST ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "character_data", "character_data &opAssign(const character_data &in)", asFUNCTION((ValueAssignment<CharacterData, CharacterData>)), asCALL_CDECL_OBJLAST ); assert( r >= 0 );

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
	r = engine->RegisterObjectBehaviour( "monster_data", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ValueConstruct<MonsterData>), asCALL_CDECL_OBJLAST ); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "monster_data", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(ValueDestruct<MonsterData>), asCALL_CDECL_OBJLAST ); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "monster_data", asBEHAVE_CONSTRUCT, "void f(const monster_data &in)", asFUNCTION(ValueCopyConstruct<MonsterData>), asCALL_CDECL_OBJLAST ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "monster_data", "monster_data &opAssign(const monster_data &in)", asFUNCTION((ValueAssignment<MonsterData, MonsterData>)), asCALL_CDECL_OBJLAST ); assert( r >= 0 );

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



namespace script
{
	Actor* ActorFactory()
	{
		static Actor uninitializedActor; //fixme
		return &uninitializedActor;
	}
} //namespace script



void ScriptEngine::RegisterActor()
{
	int r(0);
	using namespace script;

	//r = engine->RegisterObjectType( "actor", sizeof(Actor), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_CDAK ); assert( r >= 0 );
	//r = engine->RegisterObjectBehaviour( "actor", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ValueConstruct<Actor>), asCALL_CDECL_OBJLAST ); assert( r >= 0 );
	//r = engine->RegisterObjectBehaviour( "actor", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(ValueDestruct<Actor>), asCALL_CDECL_OBJLAST ); assert( r >= 0 );
	//r = engine->RegisterObjectBehaviour( "actor", asBEHAVE_CONSTRUCT, "void f(const actor &in)", asFUNCTION(ValueCopyConstruct<Actor>), asCALL_CDECL_OBJLAST ); assert( r >= 0 );
	//r = engine->RegisterObjectMethod( "actor", "actor &opAssign(const actor &in)", asFUNCTION((ValueAssignment<Actor, Actor>)), asCALL_CDECL_OBJLAST ); assert( r >= 0 );

	r = engine->RegisterObjectType( "actor", 0, asOBJ_REF | asOBJ_SCOPED ); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "actor", asBEHAVE_FACTORY, "actor @f()", asFUNCTION(ActorFactory), asCALL_CDECL ); assert( r >= 0 );
	//r = engine->RegisterObjectBehaviour( "actor", asBEHAVE_FACTORY, "actor @f(const actor& in)", asFUNCTION(PointerCopyConstruct<Actor>), asCALL_CDECL_OBJLAST ); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "actor", asBEHAVE_RELEASE, "void f()", asFUNCTION(DummyReleaseRef), asCALL_CDECL_OBJLAST ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "actor", "actor &opAssign(const actor &in)", asFUNCTION((PointerAssignment<Actor>)), asCALL_CDECL_OBJLAST ); assert( r >= 0 );

	r = engine->RegisterObjectProperty( "actor", "string name", offsetof(Actor, name)); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "actor", "string script", offsetof(Actor, script)); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "actor", "int id", offsetof(Actor, id)); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "actor", "int portrait_id", offsetof(Actor, portrait_id)); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "actor", "int map_spriteset_id", offsetof(Actor, map_spriteset_id)); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "actor", "int battle_spriteset_id", offsetof(Actor, battle_spriteset_id)); assert( r >= 0 );

	r = engine->RegisterObjectMethod( "actor", "int get_lv() const", asMETHODPR(Actor, GetLv, () const, int), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "actor", "int get_exp() const", asMETHODPR(Actor, GetExp, () const, int), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "actor", "int get_gold() const", asMETHODPR(Actor, GetGold, () const, int), asCALL_THISCALL ); assert( r >= 0 );

	r = engine->RegisterObjectMethod( "actor", "void set_lv(int) const", asMETHODPR(Actor, SetLv, (int), void), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "actor", "void set_exp(int) const", asMETHODPR(Actor, SetExp, (int), void), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "actor", "void set_gold(int) const", asMETHODPR(Actor, SetGold, (int), void), asCALL_THISCALL ); assert( r >= 0 );


	//test
	RegisterClassContainingAttributes<Actor>("actor");




	//r = engine->RegisterObjectType( "monster", 0, asOBJ_REF | asOBJ_SCOPED ); assert( r >= 0 );
	//r = engine->RegisterObjectBehaviour( "monster", asBEHAVE_FACTORY, "monster@ f()", asFUNCTION(MonsterConstructor), asCALL_CDECL ); assert( r >= 0 );
	//r = engine->RegisterObjectBehaviour( "monster", asBEHAVE_RELEASE, "void f()", asFUNCTION(DummyReleaseRef), asCALL_CDECL_OBJLAST ); assert( r >= 0 );
	//r = engine->RegisterObjectMethod( "monster", "monster &opAssign(const monster &in)", asFUNCTION((RefAssignment<Keyboard, Keyboard>)), asCALL_CDECL_OBJLAST ); assert( r >= 0 );


}


namespace script
{
	Party* PartyFactory()
	{
		static Party uninitializedParty; //fixme
		return &uninitializedParty;
	}
} //namespace script


void ScriptEngine::RegisterParty()
{
	int r(0);
	using namespace script;
	r = engine->RegisterObjectType("party", 0, asOBJ_REF | asOBJ_SCOPED); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour("party", asBEHAVE_FACTORY, "party @f()", asFUNCTION(PartyFactory), asCALL_CDECL ); assert( r >= 0 );
	//r = engine->RegisterObjectBehaviour("party", asBEHAVE_FACTORY, "party @f(const party& in)", asFUNCTION(PointerCopyConstruct<Party>), asCALL_CDECL_OBJLAST ); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour("party", asBEHAVE_RELEASE, "void f()", asFUNCTION(DummyReleaseRef), asCALL_CDECL_OBJLAST ); assert( r >= 0 );
	r = engine->RegisterObjectMethod("party", "party &opAssign(const party &in)", asFUNCTION((PointerAssignment<Party>)), asCALL_CDECL_OBJLAST ); assert( r >= 0 );

	r = engine->RegisterObjectMethod( "party", "int get_gold() const", asMETHOD(Party, GetGold), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "party", "int get_size() const", asMETHOD(Party, GetPartySize), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "party", "int get_active_size() const", asMETHOD(Party, GetActivePartySize), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "party", "int get_reserve_size() const", asMETHOD(Party, GetReservePartySize), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "party", "int get_max_size() const", asMETHOD(Party, GetMaxPartySize), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "party", "int get_max_active_size() const", asMETHOD(Party, GetMaxActivePartySize), asCALL_THISCALL ); assert( r >= 0 );

	r = engine->RegisterObjectMethod( "party", "int get_active_member_id(int) const", asMETHOD(Party, GetActiveMemberId), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "party", "int get_reserve_member_id(int) const", asMETHOD(Party, GetReserveMemberId), asCALL_THISCALL ); assert( r >= 0 );

	r = engine->RegisterObjectMethod( "party", "inventory& get_inventory()", asMETHODPR(Party, GetInventory, (), Inventory&), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "party", "const inventory& get_inventory() const", asMETHODPR(Party, GetInventory, () const, const Inventory&), asCALL_THISCALL ); assert( r >= 0 );

	r = engine->RegisterObjectMethod( "party", "void set_gold(int)", asMETHOD(Party, SetGold), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "party", "void set_max_size(int)", asMETHOD(Party, SetMaxPartySize), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "party", "void set_max_active_size(int)", asMETHOD(Party, SetMaxActivePartySize), asCALL_THISCALL ); assert( r >= 0 );

	r = engine->RegisterObjectMethod( "party", "void add_gold(int)", asMETHOD(Party, AddGold), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "party", "void remove_gold(int)", asMETHOD(Party, RemoveGold), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "party", "void add_member(int)", asMETHOD(Party, AddMember), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "party", "void remove_member(int)", asMETHOD(Party, RemoveMember), asCALL_THISCALL ); assert( r >= 0 );

	r = engine->RegisterObjectMethod( "party", "bool has_member(int) const", asMETHOD(Party, HasMember), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "party", "bool is_member_active(int) const", asMETHODPR(Party, IsMemberInActiveParty, (int) const, bool), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "party", "bool is_member_in_reserve(int) const", asMETHODPR(Party, IsMemberInReserve, (int) const, bool), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "party", "bool is_full() const", asMETHOD(Party, IsFull), asCALL_THISCALL ); assert( r >= 0 );


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
	r = engine->RegisterObjectMethod( name, "int get_elem_def(int) const", asMETHODPR(T, GetElementalDef, (int) const, int), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( name, "int get_status_atk(int) const", asMETHODPR(T, GetStatusAtk, (int) const, int), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( name, "int get_status_def(int) const", asMETHODPR(T, GetStatusDef, (int) const, int), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( name, "int get_base_elem_def(int) const", asMETHODPR(T, GetBaseElementalDef, (int) const, int), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( name, "int get_base_status_atk(int) const", asMETHODPR(T, GetBaseStatusAtk, (int) const, int), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( name, "int get_base_status_def(int) const", asMETHODPR(T, GetBaseStatusDef, (int) const, int), asCALL_THISCALL ); assert( r >= 0 );

	r = engine->RegisterObjectMethod( name, "void set_param(int, int) const", asMETHODPR(T, SetParam, (int, int), void), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( name, "void set_base_max_param(int, int) const", asMETHODPR(T, SetBaseMaxParam, (int, int), void), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( name, "void set_base_stat(int, int) const", asMETHODPR(T, SetBaseStat, (int, int), void), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( name, "void set_base_elem_def(int, int) const", asMETHODPR(T, SetBaseElementalDef, (int, int), void), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( name, "void set_base_status_atk(int, int) const", asMETHODPR(T, SetBaseStatusAtk, (int, int), void), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( name, "void set_base_status_def(int, int) const", asMETHODPR(T, SetBaseStatusDef, (int, int), void), asCALL_THISCALL ); assert( r >= 0 );

	r = engine->RegisterObjectMethod( name, "const attributes& get_attributes() const", asMETHODPR(T, GetBaseAttributes, (void) const, const Attributes&), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( name, "const equipment& get_equipment() const", asMETHODPR(T, GetEquipment, (void) const, const Equipment&), asCALL_THISCALL ); assert( r >= 0 );
	//r = engine->RegisterObjectMethod( name, "const equipment& get_equipment() const", asMETHODPR(T, GetEquipment, (void) const, const Equipment&), asCALL_THISCALL ); assert( r >= 0 );

}



namespace script
{
	Entity* EntityFactory()
	{
		static Entity uninitializedEntity[4]; //fixme
		return &uninitializedEntity[0];
	}

} //namespace script


template <class T>
void ScriptEngine::RegisterEntityType( const char* name )
{
	fc::string decl = name;
	fc::string const_ref = "const " + decl + " &in";
	fc::string factory_decl = decl + "@ f()";
	//fc::string factory_copy_decl = decl + "@ f(" + const_ref + ")";
	fc::string opAssignString = decl;
	opAssignString.append(" &opAssign(").append(const_ref).append(")");

	int r(0);
	using namespace script;

	/*
	r = engine->RegisterObjectType( name, 0, asOBJ_REF | asOBJ_SCOPED ); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( name, asBEHAVE_FACTORY, factory_decl.c_str(), asFUNCTION(EntityFactory), asCALL_CDECL ); assert( r >= 0 );
	//r = engine->RegisterObjectBehaviour( name, asBEHAVE_FACTORY, factory_copy_decl.c_str(), asFUNCTION(PointerCopyConstruct<T>), asCALL_CDECL_OBJLAST ); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( name, asBEHAVE_RELEASE, "void f()", asFUNCTION(DummyReleaseRef), asCALL_CDECL_OBJLAST ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( name, opAssignString.c_str(), asFUNCTION((PointerAssignment<T>)), asCALL_CDECL_OBJLAST ); assert( r >= 0 );
	*/

	r = engine->RegisterObjectType( name, 0, asOBJ_REF ); assert( r >= 0 );
	//r = engine->RegisterObjectBehaviour( name, asBEHAVE_FACTORY, factory_decl.c_str(), asFUNCTION(EntityFactory), asCALL_CDECL ); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( name, asBEHAVE_ADDREF, "void f()", asFUNCTION(DummyAddRef), asCALL_CDECL_OBJLAST ); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( name, asBEHAVE_RELEASE, "void f()", asFUNCTION(DummyReleaseRef), asCALL_CDECL_OBJLAST ); assert( r >= 0 );
	//r = engine->RegisterObjectMethod( name, opAssignString.c_str(), asFUNCTION((PointerAssignment<T>)), asCALL_CDECL_OBJLAST ); assert( r >= 0 );

}


template <class T>
void ScriptEngine::RegisterEntityBaseProperties( const char* name )
{
	int r(0);
	using namespace script;
	r = engine->RegisterObjectProperty( name, "vec2 pos", offsetof(T, pos)); assert( r >= 0 );
	r = engine->RegisterObjectProperty( name, "vec2 velocity", offsetof(T, velocity)); assert( r >= 0 );
	r = engine->RegisterObjectProperty( name, "rectf hitbox", offsetof(T, hitbox)); assert( r >= 0 );

	r = engine->RegisterObjectMethod( name, "rectf get_aabb() const", asMETHOD(Entity, GetBoundingRect), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( name, "bool get_alive() const", asMETHOD(Entity, IsAlive), asCALL_THISCALL ); assert( r >= 0 );

}


void ScriptEngine::RegisterCombatant()
{
	int r(0);
	using namespace script;

	RegisterEntityType<Combatant>("combatant");
	RegisterEntityBaseProperties<Combatant>("combatant");
	RegisterClassContainingAttributes<Combatant>("combatant");

	/*
	r = engine->RegisterObjectType( "combatant", 0, asOBJ_REF | asOBJ_SCOPED ); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour("combatant", asBEHAVE_FACTORY, "combatant @f()", asFUNCTION(ActorFactory), asCALL_CDECL ); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour("combatant", asBEHAVE_FACTORY, "combatant @f(const combatant& in)", asFUNCTION(PointerCopyConstruct<Combatant>), asCALL_CDECL_OBJLAST ); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour("combatant", asBEHAVE_RELEASE, "void f()", asFUNCTION(DummyReleaseRef), asCALL_CDECL_OBJLAST ); assert( r >= 0 );
	r = engine->RegisterObjectMethod("combatant", "combatant &opAssign(const combatant &in)", asFUNCTION((PointerAssignment<Combatant>)), asCALL_CDECL_OBJLAST ); assert( r >= 0 );
	*/

	r = engine->RegisterObjectMethod( "combatant", "spriteset& get_spriteset()", asMETHODPR(Combatant, GetAnimatedSpriteSet, (void), AnimatedSpriteSet&), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "combatant", "const spriteset& get_spriteset() const", asMETHODPR(Combatant, GetAnimatedSpriteSet, (void) const, const AnimatedSpriteSet&), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "combatant", "actor@ get_actor() const", asMETHODPR(Combatant, GetActor, () const, Actor*), asCALL_THISCALL ); assert( r >= 0 );

}








void ScriptEngine::RegisterRpgInterface()
{
	RegisterRpgDataTypes();
	RegisterActor();
	RegisterParty();
	RegisterCombatant();
}




/*
template <class T>
void ScriptEngine::RegisterCombatant2( const char* name )
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
*/



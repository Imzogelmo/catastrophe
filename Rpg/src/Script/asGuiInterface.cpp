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

#include <cassert>
#include <angelscript.h>

#include <Catastrophe/Gui/Widget.h>

#include "asBindUtil.h"
#include "ScriptEngine.h"


namespace script
{
	Widget* WidgetConstructor()
	{
		static Widget uninitializedWidget = Widget();
		return &uninitializedWidget;
	}

} //namespace script


template <class T>
void RegisterWidgetType( asIScriptEngine* engine, const char* name )
{
	fc::string decl = name;
	fc::string const_ref = "const " + decl + " &in";
	fc::string opAssignString(decl).append(" &opAssign(").append(const_ref).append(")");

	//todo:these need to be memory pooled or ref counted.
	int r(0);
	using namespace script;
	r = engine->RegisterObjectType( name, 0, asOBJ_REF | asOBJ_SCOPED ); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( name, asBEHAVE_FACTORY, "texture@ f()", asFUNCTION(WidgetConstructor), asCALL_CDECL); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( name, asBEHAVE_RELEASE, "void f()", asFUNCTION(DummyReleaseRef), asCALL_CDECL_OBJLAST ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( name, opAssignString.c_str(), asFUNCTION((RefAssignment<Widget, Widget>)), asCALL_CDECL_OBJLAST ); assert( r >= 0 );

	engine->RegisterObjectMethod( name, "void set_x(int)", asMETHOD(T, SetX), asCALL_THISCALL );
	engine->RegisterObjectMethod( name, "void set_y(int)", asMETHOD(T, SetY), asCALL_THISCALL );
	engine->RegisterObjectMethod( name, "void set_width(int)", asMETHOD(T, SetWidth), asCALL_THISCALL );
	engine->RegisterObjectMethod( name, "void set_height(int)", asMETHOD(T, SetHeight), asCALL_THISCALL );
	engine->RegisterObjectMethod( name, "void set_pos(const point &in)", asMETHODPR(T, SetPosition, (const Point &), void), asCALL_THISCALL );
	engine->RegisterObjectMethod( name, "void set_size(const point &in)", asMETHODPR(T, SetPosition, (const Point &), void), asCALL_THISCALL );
	engine->RegisterObjectMethod( name, "void set_color(const color &in)", asMETHOD(T, SetColor), asCALL_THISCALL );
	engine->RegisterObjectMethod( name, "void set_visible(bool)", asMETHOD(T, SetVisible), asCALL_THISCALL );
	engine->RegisterObjectMethod( name, "void set_selected(bool)", asMETHOD(T, SetSelected), asCALL_THISCALL );
	engine->RegisterObjectMethod( name, "void set_active(bool)", asMETHOD(T, SetActive), asCALL_THISCALL );
	
	engine->RegisterObjectMethod( name, "int get_x() const", asMETHOD(T, GetX), asCALL_THISCALL );
	engine->RegisterObjectMethod( name, "int get_y() const", asMETHOD(T, GetY), asCALL_THISCALL );
	engine->RegisterObjectMethod( name, "int get_width() const", asMETHOD(T, GetWidth), asCALL_THISCALL );
	engine->RegisterObjectMethod( name, "int get_height() const", asMETHOD(T, GetHeight), asCALL_THISCALL );
	engine->RegisterObjectMethod( name, "const point& get_pos() const", asMETHOD(T, GetPosition), asCALL_THISCALL );
	engine->RegisterObjectMethod( name, "const point& get_size() const", asMETHOD(T, GetSize), asCALL_THISCALL );
	engine->RegisterObjectMethod( name, "const color& get_color() const", asMETHOD(T, GetColor), asCALL_THISCALL );
	engine->RegisterObjectMethod( name, "point get_screen_pos()", asMETHOD(T, GetScreenPosition), asCALL_THISCALL );
	engine->RegisterObjectMethod( name, "widget@ get_child(int) const", asMETHODPR(T, GetChild, (size_t) const, Widget*), asCALL_THISCALL );
	engine->RegisterObjectMethod( name, "widget@ get_parent() const", asMETHOD(T, GetParent), asCALL_THISCALL );
	engine->RegisterObjectMethod( name, "widget@ get_root() const", asMETHOD(T, GetRoot), asCALL_THISCALL );
	engine->RegisterObjectMethod( name, "bool get_visible() const", asMETHOD(T, IsVisible), asCALL_THISCALL );
	engine->RegisterObjectMethod( name, "bool get_selected() const", asMETHOD(T, IsSelected), asCALL_THISCALL );
	engine->RegisterObjectMethod( name, "bool get_active() const", asMETHOD(T, IsActive), asCALL_THISCALL );
	engine->RegisterObjectMethod( name, "int get_num_children() const", asFUNCTION(GetNumChildren), asCALL_CDECL_OBJLAST );

	engine->RegisterObjectMethod( name, "void add_child(widget@)", asMETHOD(T, AddChild), asCALL_THISCALL );
	engine->RegisterObjectMethod( name, "void insert_child(int, widget@)", asMETHOD(T, InsertChild), asCALL_THISCALL );
	engine->RegisterObjectMethod( name, "void remove_child(widget@)", asMETHOD(T, RemoveChild), asCALL_THISCALL );
	engine->RegisterObjectMethod( name, "void remove()", asMETHOD(T, Remove), asCALL_THISCALL );

	//engine->RegisterObjectBehaviour( name, asBEHAVE_IMPLICIT_REF_CAST, (decl + "@ f()").c_str(), asFUNCTION((RefCast<T, U>)), asCALL_CDECL_OBJLAST );
	//engine->RegisterObjectBehaviour( "widget", asBEHAVE_IMPLICIT_REF_CAST, "widget@ f()", asFUNCTION((RefCast<U, T>)), asCALL_CDECL_OBJLAST );

}









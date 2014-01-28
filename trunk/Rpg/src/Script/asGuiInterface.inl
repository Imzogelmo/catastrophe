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
#include <Catastrophe/Gui/Frame.h>

#include "asBindUtil.h"
#include "ScriptEngine.h"


namespace script
{
	void WidgetAddRef()
	{
	}

	void WidgetReleaseRef()
	{
	}

	Widget* WidgetConstructor()
	{
		static Widget uninitializedWidget = Widget();
		return &uninitializedWidget;
	}

} //namespace script


template <class T>
void ScriptEngine::RegisterWidgetType( const char* name )
{
	fc::string decl = name;
	fc::string factory_decl = decl + "@ f()";
	fc::string const_ref = "const " + decl + " &in";
	fc::string opAssignString(decl);
	opAssignString.append(" &opAssign(").append(const_ref).append(")");

	int r(0);
	using namespace script;
	r = engine->RegisterObjectType( name, 0, asOBJ_REF ); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( name, asBEHAVE_FACTORY, factory_decl.c_str(), asFUNCTION(WidgetConstructor), asCALL_CDECL); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( name, asBEHAVE_ADDREF, "void f()", asMETHOD(T, AddRef), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( name, asBEHAVE_RELEASE, "void f()", asMETHOD(T, ReleaseRef), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( name, opAssignString.c_str(), asFUNCTION((RefAssignment<Widget, Widget>)), asCALL_CDECL_OBJLAST ); assert( r >= 0 );

	//r = engine->RegisterObjectMethod( name, "void set_x(float)", asMETHOD(T, SetX), asCALL_THISCALL ); assert( r >= 0 );
	//r = engine->RegisterObjectMethod( name, "void set_y(float)", asMETHOD(T, SetY), asCALL_THISCALL ); assert( r >= 0 );
	//r = engine->RegisterObjectMethod( name, "void set_width(float)", asMETHOD(T, SetWidth), asCALL_THISCALL ); assert( r >= 0 );
	//r = engine->RegisterObjectMethod( name, "void set_height(float)", asMETHOD(T, SetHeight), asCALL_THISCALL ); assert( r >= 0 );
//	r = engine->RegisterObjectMethod( name, "void set_pos(const vec2 &in)", asMETHODPR(T, SetPosition, (const Point &), void), asCALL_THISCALL ); assert( r >= 0 );
//	r = engine->RegisterObjectMethod( name, "void set_size(const vec2 &in)", asMETHODPR(T, SetPosition, (const Point &), void), asCALL_THISCALL ); assert( r >= 0 );
//	r = engine->RegisterObjectMethod( name, "void set_color(const color &in)", asMETHOD(T, SetColor), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( name, "void set_visible(bool)", asMETHOD(T, SetVisible), asCALL_THISCALL ); assert( r >= 0 );
	//engine->RegisterObjectMethod( name, "void set_selected(bool)", asMETHOD(T, SetSelected), asCALL_THISCALL ); assert( r >= 0 );
	//engine->RegisterObjectMethod( name, "void set_active(bool)", asMETHOD(T, SetActive), asCALL_THISCALL ); assert( r >= 0 );

	//engine->RegisterObjectMethod( name, "float get_x() const", asMETHOD(T, GetX), asCALL_THISCALL ); assert( r >= 0 );
	//engine->RegisterObjectMethod( name, "float get_y() const", asMETHOD(T, GetY), asCALL_THISCALL ); assert( r >= 0 );
	//r = engine->RegisterObjectMethod( name, "float get_width() const", asMETHOD(T, GetWidth), asCALL_THISCALL ); assert( r >= 0 );
	//r = engine->RegisterObjectMethod( name, "float get_height() const", asMETHOD(T, GetHeight), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( name, "const vec2& get_pos() const", asMETHOD(T, GetPosition), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( name, "const vec2& get_size() const", asMETHOD(T, GetSize), asCALL_THISCALL ); assert( r >= 0 );
//	r = engine->RegisterObjectMethod( name, "const color& get_color() const", asMETHOD(T, GetColor), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( name, "vec2 get_screen_pos() const", asMETHOD(T, GetScreenPosition), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( name, "bool get_visible() const", asMETHOD(T, IsVisible), asCALL_THISCALL ); assert( r >= 0 );
	//engine->RegisterObjectMethod( name, "bool get_selected() const", asMETHOD(T, IsSelected), asCALL_THISCALL ); assert( r >= 0 );
	//engine->RegisterObjectMethod( name, "bool get_active() const", asMETHOD(T, IsActive), asCALL_THISCALL ); assert( r >= 0 );

	//r = engine->RegisterObjectBehaviour( name, asBEHAVE_IMPLICIT_REF_CAST, (decl + "@ f()").c_str(), asFUNCTION((RefCast<T, U>)), asCALL_CDECL_OBJLAST ); assert( r >= 0 );
	//r = engine->RegisterObjectBehaviour( "widget", asBEHAVE_IMPLICIT_REF_CAST, "widget@ f()", asFUNCTION((RefCast<U, T>)), asCALL_CDECL_OBJLAST ); assert( r >= 0 );

}


template <class T>
void ScriptEngine::RegisterWidgetContainerMethods( const char* name )
{
	int r(0);
	using namespace script;
	r = engine->RegisterObjectMethod( name, "widget@ get_child(int) const", asMETHODPR(T, GetChild, (size_t) const, Widget*), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( name, "widget@ get_parent() const", asMETHOD(T, GetParent), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( name, "widget@ get_root() const", asMETHOD(T, GetRoot), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( name, "int get_num_children() const", asMETHOD(T, GetNumChildren), asCALL_THISCALL ); assert( r >= 0 );

	r = engine->RegisterObjectMethod( name, "void add_child(widget@)", asMETHOD(T, AddChild), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( name, "void insert_child(int, widget@)", asMETHOD(T, InsertChild), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( name, "void remove_child(widget@)", asMETHOD(T, RemoveChild), asCALL_THISCALL ); assert( r >= 0 );
	//r = engine->RegisterObjectMethod( name, "void remove()", asMETHOD(T, Remove), asCALL_THISCALL ); assert( r >= 0 );

}


void ScriptEngine::RegisterFrame()
{
	int r(0);
	using namespace script;
	RegisterWidgetType<Frame>("frame");
	RegisterWidgetContainerMethods<Frame>("frame");
	r = m_engine->RegisterObjectMethod( "frame", "void set_blendmode(const blendmode &in)", asMETHOD(Frame, SetBlendMode), asCALL_THISCALL ); assert( r >= 0 );
	r = m_engine->RegisterObjectMethod( "frame", "const blendmode& get_blendmode() const", asMETHOD(Frame, GetBlendMode), asCALL_THISCALL ); assert( r >= 0 );

}


void ScriptEngine::RegisterGuiInterface()
{
	RegisterWidgetType<Widget>("widget");
	RegisterFrame();

}






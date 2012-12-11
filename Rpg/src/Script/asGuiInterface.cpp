
#pragma once

#include <cassert>
#include <angelscript.h>

#include <Catastrophe/Math/Math.h>
#include <Catastrophe/MathTypes.h>

#include "asBindUtil.h"
#include "ScriptEngine.h"



namespace script
{
	Texture* TextureConstructor()
	{
		static Texture uninitializedTexture = Texture();
		return &uninitializedTexture;
	}

} //namespace script


template <class T, class U>
void RegisterImplicitRefCast( asIScriptEngine* engine, const char* t, const char* u )
{
	engine->RegisterObjectBehaviour(classNameT, asBEHAVE_IMPLICIT_REF_CAST, (t + "@ f()").c_str(), asFUNCTION((RefCast<T, U>)), asCALL_CDECL_OBJLAST);
	engine->RegisterObjectBehaviour(classNameU, asBEHAVE_IMPLICIT_REF_CAST, (u + "@ f()").c_str(), asFUNCTION((RefCast<U, T>)), asCALL_CDECL_OBJLAST);
}


template <class T>
void RegisterWidgetType( asIScriptEngine* engine, const char* name )
{
	fc::string decl = name;
	fc::string const_ref = "const " + decl + " &in";
	fc::string opAssignString(decl).append(" &opAssign(").append(const_ref).append(")");

	int r(0);
	using namespace script;
	r = engine->RegisterObjectType( name, 0, asOBJ_REF | asOBJ_SCOPED ); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( name, asBEHAVE_FACTORY, "texture@ f()", asFUNCTION(TextureConstructor), asCALL_CDECL); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( name, asBEHAVE_RELEASE, "void f()", asFUNCTION(DummyReleaseRef), asCALL_CDECL_OBJLAST ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( name, opAssignString.c_str(), asFUNCTION((RefAssignment<Texture, Texture>)), asCALL_CDECL_OBJLAST ); assert( r >= 0 );

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

	RegisterImplicitRefCast<T, Widget>(engine, name, "widget")
	engine->RegisterObjectBehaviour( name, asBEHAVE_IMPLICIT_REF_CAST, (t + "@ f()").c_str(), asFUNCTION((RefCast<T, U>)), asCALL_CDECL_OBJLAST );
	engine->RegisterObjectBehaviour( classNameU, asBEHAVE_IMPLICIT_REF_CAST, (u + "@ f()").c_str(), asFUNCTION((RefCast<U, T>)), asCALL_CDECL_OBJLAST );



}









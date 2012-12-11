
#include <cassert>
#include <angelscript.h>

#include <Catastrophe/Math/Color.h>
#include <Catastrophe/Math/Colorf.h>
#include <Catastrophe/Graphics/Texture.h>
#include <Catastrophe/Graphics/Font.h>
#include <Catastrophe/Graphics/BlendMode.h>
#include <Catastrophe/Graphics/Primitive.h>
#include <Catastrophe/Graphics/Sprite.h>

#include "asBindUtil.h"
#include "ScriptEngine.h"


namespace script
{
	void ColorDefaultConstructor( Color *self )
	{
		new (self) Color(0, 0, 0, 255);
	}

	void ColorfDefaultConstructor( Colorf *self )
	{
		new (self) Colorf(0.f, 0.f, 0.f, 1.f);
	}

	void VertexColorDefaultConstructor( VertexColor *self )
	{
		new (self) VertexColor(Vector2::Zero, Color::White());
	}

	void VertexColorInitConstructor( const Vector2& pos, const Color& color, VertexColor *self )
	{
		new (self) VertexColor(pos, color);
	}

} //namespace script


void ScriptEngine::RegisterColor()
{
	int r;
	using namespace script;
	r = engine->RegisterObjectType( "color", sizeof(Color), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_C); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "color", "uint8 r", 0); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "color", "uint8 g", 1); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "color", "uint8 b", 2); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "color", "uint8 a", 3); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "color", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ColorDefaultConstructor), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "color", asBEHAVE_CONSTRUCT, "void f(const color &in)", asFUNCTION(ValueCopyConstruct<Color>), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "color", asBEHAVE_CONSTRUCT, "void f(uint8, uint8, uint8, uint8)", asFUNCTION((ValueInitConstruct_4Arg<Color, ubyte>)), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	//r = engine->RegisterObjectMethod( "color" , "color& clamp(const color &, const color &)", asMETHODPR(Color, Clamp, (const Color&, const Color&), void), asCALL_THISCALL); assert( r >= 0 );
	//r = engine->RegisterObjectMethod( "color", "color& lerp(const color &in, float)", asMETHODPR(Color, Lerp, (const Color&, float), Color), asCALL_THISCALL); assert( r >= 0 );

}


void ScriptEngine::RegisterColorf()
{
	int r;
	using namespace script;
	r = engine->RegisterObjectType( "colorf", sizeof(Colorf), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_CA); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "colorf", "float r", offsetof(Colorf, r)); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "colorf", "float g", offsetof(Colorf, g)); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "colorf", "float b", offsetof(Colorf, b)); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "colorf", "float a", offsetof(Colorf, a)); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "colorf", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ColorfDefaultConstructor), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "colorf", asBEHAVE_CONSTRUCT, "void f(const colorf &in)", asFUNCTION(ValueCopyConstruct<Colorf>), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "colorf", asBEHAVE_CONSTRUCT, "void f(float, float, float, float)", asFUNCTION((ValueInitConstruct_4Arg<Colorf, float>)), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "colorf", "colorf &opAssign(const colorf &in)", asFUNCTION((ValueAssignment<Colorf, Colorf>)), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	//r = engine->RegisterObjectMethod( "colorf", "colorf& clamp(const colorf &, const colorf &)", asMETHODPR(Colorf, Clamp, (const Colorf&, const Colorf&), Color&), asCALL_THISCALL); assert( r >= 0 );
	//r = engine->RegisterObjectMethod( "colorf", "colorf& lerp(const colorf &in, float)", asMETHODPR(Colorf, Lerp, (const Colorf&, float), Colorf&), asCALL_THISCALL); assert( r >= 0 );

	//r = engine->RegisterGlobalFunction( "color lerp( const color &in, const color &in, float )", asFUNCTIONPR( Color::Lerp, ( const Color&, const Color&, float ), Color), CALL_TYPE ); assert( r >= 0 );
	//r = engine->RegisterGlobalFunction( "colorf lerp( const colorf &in, const colorf &in, float )", asFUNCTIONPR( Colorf::Lerp, ( const Colorf&, const Colorf&, float ), Colorf), CALL_TYPE ); assert( r >= 0 );

}


void ScriptEngine::RegisterColorConversions()
{
	int r;
	using namespace script;
	r = engine->RegisterObjectBehaviour( "colorf", asBEHAVE_CONSTRUCT, "void f(const color &in)", asFUNCTION((ValueCopyConstruct<Colorf, Color>)), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "color" , asBEHAVE_CONSTRUCT, "void f(const colorf &in)", asFUNCTION((ValueCopyConstruct<Color, Colorf>)), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "colorf", asBEHAVE_VALUE_CAST, "color f()", asMETHODPR(Colorf, ToColor, (void) const, Color), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "color" , asBEHAVE_VALUE_CAST, "colorf f()", asMETHODPR(Color, ToColorf, (void) const, Colorf), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "colorf", asBEHAVE_IMPLICIT_VALUE_CAST, "color f()", asMETHODPR(Colorf, ToColor, (void) const, Color), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "color" , asBEHAVE_IMPLICIT_VALUE_CAST, "colorf f()", asMETHODPR(Color, ToColorf, (void) const, Colorf), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "colorf", "colorf &opAssign(const color &in)", asFUNCTION((ValueAssignment<Colorf, Color>)), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "color" , "color &opAssign(const colorf &in)", asFUNCTION((ValueAssignment<Color, Colorf>)), asCALL_CDECL_OBJLAST); assert( r >= 0 );
}


void ScriptEngine::RegisterBlendMode()
{
	int r(0);
	using namespace script;
	r = engine->RegisterObjectType( "blendmode", sizeof(BlendMode), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_CA ); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "blendmode", "uint16 src", offsetof(BlendMode, src)); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "blendmode", "uint16 dst", offsetof(BlendMode, dst)); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "blendmode", asBEHAVE_CONSTRUCT,  "void f()", asFUNCTION(ValueConstruct<BlendMode>), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "blendmode", asBEHAVE_CONSTRUCT,  "void f(uint16, uint16)", asFUNCTION((ValueInitConstruct_2Arg<BlendMode, ushort>)), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "blendmode", asBEHAVE_CONSTRUCT,  "void f(const blendmode &in)", asFUNCTION((ValueCopyConstruct<BlendMode, BlendMode>)), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	//r = engine->RegisterObjectMethod( "blendmode", "blendMode &opAssign(const blendmode &in)", asFUNCTION((ValueAssignment<BlendMode, BlendMode>)), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "blendmode", "bool opEquals(const blendmode &in) const", asMETHODPR(BlendMode, operator ==, (const BlendMode&) const, bool), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "blendmode", "blendmode &set(uint16, uint16)", asMETHODPR(BlendMode, Separate, (ushort, ushort), BlendMode&), asCALL_THISCALL ); assert( r >= 0 );
}


namespace script
{
	Texture* TextureConstructor()
	{
		static Texture uninitializedTexture = Texture();
		return &uninitializedTexture;
	}

} //namespace script


void ScriptEngine::RegisterTexture()
{
	int r(0);
	using namespace script;
	//r = engine->RegisterObjectType( "texture", 0, asOBJ_REF | asOBJ_SCOPED ); assert( r >= 0 );
	//r = engine->RegisterObjectBehaviour("texture", asBEHAVE_FACTORY, "texture@ f()", asFUNCTION(TextureConstructor), asCALL_CDECL); assert( r >= 0 );
	//r = engine->RegisterObjectBehaviour( "texture", asBEHAVE_RELEASE, "void f()", asFUNCTION(DummyReleaseRef), asCALL_CDECL_OBJLAST ); assert( r >= 0 );

	r = engine->RegisterObjectType( "texture", 0, asOBJ_REF | asOBJ_SCOPED ); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "texture", asBEHAVE_FACTORY, "texture@ f()", asFUNCTION(TextureConstructor), asCALL_CDECL); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "texture", asBEHAVE_RELEASE, "void f()", asFUNCTION(DummyReleaseRef), asCALL_CDECL_OBJLAST ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "texture", "texture &opAssign(const texture &in)", asFUNCTION((RefAssignment<Texture, Texture>)), asCALL_CDECL_OBJLAST ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "texture", "bool is_valid()", asMETHOD(Texture, IsValid), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "texture", "bool get_width()", asMETHOD(Texture, Width), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "texture", "bool get_height()", asMETHOD(Texture, Height), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "texture", "int get_id()", asMETHOD(Texture, GetTextureID), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "texture", "vec2 uv(const point& in)", asMETHODPR(Texture, GetUV, (const Point &) const, Vector2), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "texture", "vec2 uv(int, int)", asMETHODPR(Texture, GetUV, (int, int) const, Vector2), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "texture", "rectf uv_rect(const rect& in)", asMETHODPR(Texture, GetUVRect, (const Rect &) const, Rectf), asCALL_THISCALL ); assert( r >= 0 );

}


void ScriptEngine::RegisterFont()
{
	int r(0);
	using namespace script;
	r = engine->RegisterObjectType( "font", 0, asOBJ_REF | asOBJ_SCOPED ); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "font", asBEHAVE_FACTORY, "font@ f()", asFUNCTION(TextureConstructor), asCALL_CDECL); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "font", asBEHAVE_RELEASE, "void f()", asFUNCTION(DummyReleaseRef), asCALL_CDECL_OBJLAST ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "font", "font &opAssign(const font &in)", asFUNCTION((RefAssignment<Font, Font>)), asCALL_CDECL_OBJLAST ); assert( r >= 0 );
	//r = engine->RegisterObjectMethod( "font", "bool is_valid()", asMETHOD(Font, IsValid), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "font", "texture@ get_texture()", asMETHOD(Font, GetTexture), asCALL_THISCALL ); assert( r >= 0 );

}


template <class T>
void ScriptEngine::RegisterSpriteBase( const char* name )
{
	int r;
	using namespace script;
	r = engine->RegisterObjectType( name, sizeof(T), asOBJ_VALUE | asOBJ_APP_CLASS_CDAK ); assert( r >= 0 );
	r = engine->RegisterObjectProperty( name, "vec2 size", offsetof(T, size)); assert( r >= 0 );
	r = engine->RegisterObjectProperty( name, "colorf color", offsetof(T, tint)); assert( r >= 0 );
	r = engine->RegisterObjectProperty( name, "blendmode blendmode", offsetof(T, blendmode)); assert( r >= 0 );
	r = engine->RegisterObjectProperty( name, "int layer", offsetof(T, layer)); assert( r >= 0 );
	r = engine->RegisterObjectProperty( name, "int depth", offsetof(T, depth)); assert( r >= 0 );
	r = engine->RegisterObjectProperty( name, "vec2 scale", offsetof(T, scale)); assert( r >= 0 );
	r = engine->RegisterObjectProperty( name, "float angle", offsetof(T, angle)); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( name, asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ValueConstruct<T>), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( name, asBEHAVE_DESTRUCT, "void f()", asFUNCTION(ValueDestruct<T>), asCALL_CDECL_OBJLAST); assert( r >= 0 );

	r = engine->RegisterObjectMethod( "sprite", "void set_texture(const texture &in)", asMETHODPR(T, SetTexture, (const Texture*), void), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "sprite", "texture get_texture() const", asMETHODPR(T, GetTexture, () const, const Texture*), asCALL_THISCALL); assert( r >= 0 );

	fc::string method_decl = name + fc::string(" &opAssign(const ") + name + fc::string(" &in)");
	r = engine->RegisterObjectMethod( name, method_decl.c_str(), asFUNCTION((ValueAssignment<T, T>)), asCALL_CDECL_OBJLAST); assert( r >= 0 );

	//r = engine->RegisterObjectMethod( "sprite", "int get_layer() const", asMETHOD(GetLayer), asCALL_THISCALL); assert( r >= 0 );
	//r = engine->RegisterObjectMethod( "sprite", "void set_layer(int)", asFUNCTION(SetLayer), asCALL_THISCALL); assert( r >= 0 );
	//r = engine->RegisterObjectMethod( "sprite", "int get_index() const", asFUNCTION(GetIndex), asCALL_THISCALL); assert( r >= 0 );
	//r = engine->RegisterObjectMethod( "sprite", "void set_index(int)", asFUNCTION(SetIndex), asCALL_THISCALL); assert( r >= 0 );
	//r = engine->RegisterObjectMethod( "Sprite", "void flip(int flags)", asFUNCTION(Flip), asCALL_CDECL_OBJFIRST); assert( r >= 0 );

}


void ScriptEngine::RegisterSprite()
{
	int r;
	using namespace script;
	RegisterSpriteBase<Sprite>("sprite");
	r = engine->RegisterObjectMethod( "sprite", "void set_uv(const rectf &in)", asMETHODPR(Sprite, SetUVRect, (const Rectf&), void), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "sprite", "const rectf& get_uv() const", asMETHODPR(Sprite, GetUVRect, () const, const Rectf&), asCALL_THISCALL); assert( r >= 0 );

}


void ScriptEngine::RegisterAnimatedSprite()
{
	int r;
	using namespace script;
	RegisterSpriteBase<AnimatedSprite>("animated_sprite");
	r = engine->RegisterObjectMethod( "animated_sprite", "bool is_animated() const", asMETHODPR(AnimatedSprite, IsAnimated, () const, bool), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "animated_sprite", "int get_num_frames() const", asMETHODPR(AnimatedSprite, NumFrames, () const, size_t), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "animated_sprite", "float get_animation_speed() const", asMETHODPR(AnimatedSprite, GetAnimSpeed, () const, float), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "animated_sprite", "bool get_paused() const", asMETHODPR(AnimatedSprite, IsPaused, () const, bool), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "animated_sprite", "bool get_loop() const", asMETHODPR(AnimatedSprite, IsLooping, () const, bool), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "animated_sprite", "int get_frame() const", asMETHODPR(AnimatedSprite, GetCurrentFrame, () const, size_t), asCALL_THISCALL); assert( r >= 0 );

	r = engine->RegisterObjectMethod( "animated_sprite", "void set_animation_speed(float)", asMETHODPR(AnimatedSprite, SetAnimationSpeed, (float), void), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "animated_sprite", "void set_paused(bool)", asMETHODPR(AnimatedSprite, SetPaused, (bool), void), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "animated_sprite", "void set_loop(bool)", asMETHODPR(AnimatedSprite, SetLooping, (bool), void), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "animated_sprite", "void set_frame(int)", asMETHODPR(AnimatedSprite, SetCurrentFrame, (size_t), void), asCALL_THISCALL); assert( r >= 0 );

	//r = engine->RegisterObjectMethod( "sprite", "int get_layer() const", asMETHOD(AnimatedSprite, GetLayer), asCALL_THISCALL); assert( r >= 0 );
	//r = engine->RegisterObjectMethod( "sprite", "void set_layer(int)", asFUNCTION(AnimatedSprite, SetLayer), asCALL_THISCALL); assert( r >= 0 );
	//r = engine->RegisterObjectMethod( "sprite", "int get_index() const", asFUNCTION(AnimatedSprite, GetIndex), asCALL_THISCALL); assert( r >= 0 );
	//r = engine->RegisterObjectMethod( "sprite", "void set_index(int)", asFUNCTION(AnimatedSprite, SetIndex), asCALL_THISCALL); assert( r >= 0 );

	r = engine->RegisterObjectMethod( "animated_sprite", "void update()", asMETHOD(AnimatedSprite, Update), asCALL_THISCALL); assert( r >= 0 );
	//r = engine->RegisterObjectMethod( "Sprite", "void flip(int flags)", asFUNCTION(AnimatedSprite, Flip), asCALL_CDECL_OBJFIRST); assert( r >= 0 );

}

/*
void ScriptEngine::RegisterAnimatedSprite()
{
	int r;
	using namespace script;
	r = engine->RegisterObjectType( "sprite", sizeof(Sprite), asOBJ_VALUE | asOBJ_APP_CLASS_CAD ); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "sprite", "vec2 size", offsetof(Sprite, size)); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "sprite", "colorf color", offsetof(Sprite, tint)); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "sprite", "blendmode blendmode", offsetof(Sprite, blendmode)); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "sprite", "int layer", offsetof(Sprite, layer)); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "sprite", "int depth", offsetof(Sprite, depth)); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "sprite", "vec2 scale", offsetof(Sprite, scale)); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "sprite", "float angle", offsetof(Sprite, angle)); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "sprite", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ValueConstruct<Sprite>), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "sprite", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(ValueDestruct<Sprite>), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "sprite", "sprite &opAssign(const sprite &in)", asFUNCTION((ValueAssignment<Sprite, Sprite>)), asCALL_CDECL_OBJLAST); assert( r >= 0 );

	r = engine->RegisterObjectMethod( "sprite", "bool is_animated() const", asMETHOD(IsAnimated), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "sprite", "int get_num_frames() const", asMETHOD(NumFrames), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "sprite", "float get_animation_speed() const", asMETHOD(GetAnimSpeed), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "sprite", "bool get_paused() const", asMETHOD(IsPaused), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "sprite", "bool get_loop() const", asMETHOD(IsLooping), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "sprite", "int get_frame() const", asMETHOD(GetCurrentframe), asCALL_THISCALL); assert( r >= 0 );

	r = engine->RegisterObjectMethod( "sprite", "void set_animation_speed(float)", asMETHOD(SetAnimSpeed), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "sprite", "void set_paused(bool) const", asMETHOD(SetPaused), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "sprite", "void set_loop(bool) const", asMETHOD(SetLooping), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "sprite", "void set_frame(int)", asMETHOD(SetCurrentframe), asCALL_THISCALL); assert( r >= 0 );

	//r = engine->RegisterObjectMethod( "sprite", "int get_layer() const", asMETHOD(GetLayer), asCALL_THISCALL); assert( r >= 0 );
	//r = engine->RegisterObjectMethod( "sprite", "void set_layer(int)", asFUNCTION(SetLayer), asCALL_THISCALL); assert( r >= 0 );
	//r = engine->RegisterObjectMethod( "sprite", "int get_index() const", asFUNCTION(GetIndex), asCALL_THISCALL); assert( r >= 0 );
	//r = engine->RegisterObjectMethod( "sprite", "void set_index(int)", asFUNCTION(SetIndex), asCALL_THISCALL); assert( r >= 0 );

	r = engine->RegisterObjectMethod( "sprite", "void update()", asMETHOD(Update), asCALL_THISCALL); assert( r >= 0 );
	//r = engine->RegisterObjectMethod( "Sprite", "void flip(int flags)", asFUNCTION(Flip), asCALL_CDECL_OBJFIRST); assert( r >= 0 );

}
*/


void ScriptEngine::RegisterVertex()
{
	int r;
	using namespace script;
	r = engine->RegisterObjectType( "vertex", sizeof(VertexColor), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_C); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "vertex", "vec2 pos", offsetof(VertexColor, pos) ); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "vertex", "color color", offsetof(VertexColor, color) ); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "vertex", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(VertexColorDefaultConstructor), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "vertex", asBEHAVE_CONSTRUCT, "void f(const vertex &in)", asFUNCTION(ValueCopyConstruct<VertexColor>), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "vertex", asBEHAVE_CONSTRUCT, "void f(const vec2 &in, const color &in)", asFUNCTION(ValueCopyConstruct<VertexColor>), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	//r = engine->RegisterObjectMethod( "vertex", "vertex &opAssign(const vertex &in)", asFUNCTION((ValueAssignment<VertexColor, VertexColor>)), asCALL_CDECL_OBJLAST); assert( r >= 0 );
}


namespace script
{
	void PrimitiveRender( int layer, Primitive *self )
	{
	}

} //namespace script

/*
void ScriptingEngine::RegisterPrimitive()
{
	int r(0);
	using namespace script;
	//r = engine->RegisterObjectType( "primitive", sizeof(Primitive), asOBJ_VALUE | asOBJ_APP_CLASS_CDA); assert( r >= 0 );
	r = engine->RegisterObjectType( "primitive", 0, asOBJ_REF | asOBJ_SCOPED ); assert( r >= 0 );
	//r = engine->RegisterObjectProperty( "primitive", "blendmode blend", offsetof(Primitive, _blender)); assert( r >= 0 );

	r = engine->RegisterObjectBehaviour( "primitive", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ValueConstruct<Primitive>), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	//r = engine->RegisterObjectBehaviour( "primitive", asBEHAVE_CONSTRUCT, "void f(int, const blendmode &in)", asFUNCTION(PrimitiveInitConstructor), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "primitive", asBEHAVE_CONSTRUCT, "void f(const primitive &in)", asFUNCTION(ValueCopyConstruct<Primitive>), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "primitive", asBEHAVE_DESTRUCT, "void f()",  asFUNCTION(ValueDestruct<Primitive>), asCALL_CDECL_OBJLAST); assert( r >= 0 );

	r = engine->RegisterObjectMethod( "primitive", "primitive &opAssign(const primitive &in)", asFUNCTION(PrimitiveAssignmentOperator), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "primitive", "vertex& opIndex(int)", asFUNCTION(PrimitiveIndex), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "primitive", "const vertex& opIndex(int)", asFUNCTION(PrimitiveIndex), asCALL_CDECL_OBJLAST); assert( r >= 0 );

	r = engine->RegisterObjectMethod( "primitive", "void clear()", asMETHODPR( Primitive, Clear, (void), void), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "primitive", "void reserve(int)", asMETHODPR( Primitive, Reserve, (size_t), void), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "primitive", "int size(int) const", asMETHODPR( Primitive, Size, (void) const, size_t), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "primitive", "int capacity(int) const", asMETHODPR( Primitive, Capacity, (void) const, size_t), asCALL_THISCALL ); assert( r >= 0 );

	r = engine->RegisterObjectMethod( "primitive", "void set_blendmode(const blendmode &in)", asMETHODPR( Primitive, SetBlendMode, (const BlendMode &), void), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "primitive", "blendmode get_blendmode() const", asMETHODPR( Primitive, GetBlendMode, (void) const, BlendMode), asCALL_THISCALL ); assert( r >= 0 );

	//r = engine->RegisterObjectMethod( "primitive", "void set_type(int)", asMETHODPR( Primitive, Begin, (int), void), asCALL_THISCALL ); assert( r >= 0 );

	r = engine->RegisterObjectMethod( "primitive", "void translate(const vec2 &in)", asMETHOD(Primitive, Translate), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "primitive", "void rotate_vertices(float, const vec2 &in)", asMETHODPR(Primitive, RotateVertices, (float, const Vector2 &), void), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "primitive", "void scale_vertices(const vec2 &in, const vec2 &in)", asMETHODPR(Primitive, ScaleVertices, (const Vector2 &, const Vector2 &), void), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "primitive", "void rotate_scale_vertices(float, const vec2 &in, const vec2 &in)", asMETHODPR(Primitive, RotateScaleVertices, (float, const Vector2 &, const Vector2 &), void), asCALL_THISCALL ); assert( r >= 0 );

	r = engine->RegisterObjectMethod( "primitive", "void add_vertex(const vec2 &in, const color &in)", asMETHODPR( Primitive, AddVertex, (const Vector2 &, const Color &), void), asCALL_THISCALL ); assert( r >= 0 );

	//rendering functions
	//r = engine->RegisterObjectMethod( "primitive", "void render(int)", asFUNCTION(PrimitiveRender), asCALL_CDECL_OBJLAST); assert( r >= 0 );

}
*/


void ScriptEngine::RegisterGraphicsInterface()
{
	RegisterColor();
	RegisterColorf();
	RegisterColorConversions();
	RegisterBlendMode();
	RegisterTexture();
	RegisterFont();
	//RegisterVertex();

	void RegisterSprite();
	void RegisterAnimatedSprite();

}



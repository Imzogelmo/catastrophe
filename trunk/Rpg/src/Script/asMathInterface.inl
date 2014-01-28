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

#include <cmath>
#include <cassert>
#include <fc/math.h>
#include <fc/rand.h>
#include <angelscript.h>

#include <Catastrophe/Math/Math.h>
#include <Catastrophe/MathTypes.h>

#include "asBindUtil.h"
#include "ScriptEngine.h"

/*
#include <Catastrophe/Math/Vector3.h>
#include <Catastrophe/Math/Point.h>
#include <Catastrophe/Math/Rect.h>
#include <Catastrophe/Math/Rectf.h>
#include <Catastrophe/Math/Vector2.h>
#include <Catastrophe/Math/Vector3.h>
#include <Catastrophe/Math/Vector4.h>
*/



namespace script
{
	void PointDefaultConstructor( Point *self )
	{
		new (self) Point(0, 0); //initialize to zero.
	}

} //namespace script


void ScriptEngine::RegisterPoint()
{
	int r;
	using namespace script;
	r = engine->RegisterObjectType( "point", sizeof(Point), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_CA ); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "point", "int x", offsetof(Point, x)); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "point", "int y", offsetof(Point, y)); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "point", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(PointDefaultConstructor), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "point", asBEHAVE_CONSTRUCT, "void f(const point &in)", asFUNCTION(ValueCopyConstruct<Point>), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "point", asBEHAVE_CONSTRUCT, "void f(int, int)", asFUNCTION((ValueInitConstruct_2Arg<Point, int>)), asCALL_CDECL_OBJLAST); assert( r >= 0 );

	// operator overloads
	r = engine->RegisterObjectMethod( "point", "bool opEquals(const point &in) const", asMETHODPR(Point, operator ==, (const Point&) const, bool), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "point", "point& opAddAssign(const point &in)", asMETHODPR(Point, operator+=, (const Point &), Point&), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "point", "point& opSubAssign(const point &in)", asMETHODPR(Point, operator-=, (const Point &), Point&), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "point", "point& opMulAssign(const point &in)", asMETHODPR(Point, operator*=, (const Point &), Point&), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "point", "point& opDivAssign(const point &in)", asMETHODPR(Point, operator/=, (const Point &), Point&), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "point", "point opAdd(const point &in) const", asMETHODPR(Point, operator +, (const Point&) const, Point), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "point", "point opSub(const point &in) const", asMETHODPR(Point, operator -, (const Point&) const, Point), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "point", "point opMul(const point &in) const", asMETHODPR(Point, operator *, (const Point&) const, Point), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "point", "point opDiv(const point &in) const", asMETHODPR(Point, operator /, (const Point&) const, Point), asCALL_THISCALL); assert( r >= 0 );
}


namespace script
{
	void RectDefaultConstructor( Rect *self )
	{
		new (self) Rect(0, 0, 0, 0); //initialize to zero.
	}

	void RectInitConstructFromPoint( const Point &p, const Point &s, Rect *self )
	{
		new (self) Rect(p, s);
	}

	fc::string ToString( Rect *self )
	{
		//fixme
		return fc::string();
	}

	void RectSetX( int x, Rect *self )
	{
		self->pos.x = x;
	}

	void RectSetY( int y, Rect *self )
	{
		self->pos.y = y;
	}

	void RectSetWidth( int w, Rect *self )
	{
		self->size.x = w;
	}

	void RectSetHeight( int h, Rect *self )
	{
		self->size.y = h;
	}

} //namespace script


void ScriptEngine::RegisterRect()
{
	int r(0);
	using namespace script;
	r = engine->RegisterObjectType( "rect", sizeof(Rect), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_CA); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "rect", "point pos", offsetof(Rect, pos)); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "rect", "point size", offsetof(Rect, size)); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "rect", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(RectDefaultConstructor), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "rect", asBEHAVE_CONSTRUCT, "void f(const rect &in)", asFUNCTION(ValueCopyConstruct<Rect>), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "rect", asBEHAVE_CONSTRUCT, "void f(int, int, int, int)", asFUNCTION((ValueInitConstruct_4Arg<Rect, int>)), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "rect", asBEHAVE_CONSTRUCT, "void f(const point &in, const point &in)", asFUNCTION(RectInitConstructFromPoint), asCALL_CDECL_OBJLAST); assert( r >= 0 );

	// operator overloads
	r = engine->RegisterObjectMethod( "rect", "rect &opAssign(const rect &in)", asMETHODPR(Rect, operator =, (const Rect&), Rect&), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "rect", "bool opEquals(const rect &in) const", asMETHODPR(Rect, operator ==, (const Rect&) const, bool), asCALL_THISCALL); assert( r >= 0 );
	//r = engine->RegisterObjectMethod( "rect", "bool opEquals(const rect &in) const", asMETHODPR(Rect, operator !=, (const Rect&) const, bool), asCALL_THISCALL); assert( r >= 0 );

	r = engine->RegisterObjectMethod( "rect", "int get_x() const", asMETHOD(Rect, Left), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "rect", "int get_y() const", asMETHOD(Rect, Top), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "rect", "int get_width() const", asMETHOD(Rect, Width), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "rect", "int get_height() const", asMETHOD(Rect, Height), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "rect", "void set_x(int)", asFUNCTION(RectSetX), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "rect", "void set_y(int)", asFUNCTION(RectSetY), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "rect", "void set_width(int)", asFUNCTION(RectSetWidth), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "rect", "void set_height(int)", asFUNCTION(RectSetHeight), asCALL_CDECL_OBJLAST); assert( r >= 0 );

	//todo: should be getters setters..
	//...Also, make rect & rectf API the same...
	r = engine->RegisterObjectMethod( "rect", "int top() const", asMETHOD(Rect, Top), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "rect", "int bottom() const", asMETHOD(Rect, Bottom), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "rect", "int left() const", asMETHOD(Rect, Left), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "rect", "int right() const", asMETHOD(Rect, Right), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "rect", "point top_left() const", asMETHOD(Rect, TopLeft), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "rect", "point bottom_left() const", asMETHOD(Rect, BottomLeft), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "rect", "point bottom_right() const", asMETHOD(Rect, BottomRight), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "rect", "point top_right() const", asMETHOD(Rect, TopRight), asCALL_THISCALL); assert( r >= 0 );

	r = engine->RegisterObjectMethod( "rect", "string to_string()", asFUNCTION(ToString), asCALL_CDECL_OBJLAST); assert( r >= 0 );
}


namespace script
{
	void Vector2DefaultConstructor( Vector2 *self )
	{
		new (self) Vector2(0.f, 0.f); //initialize to zero for scripts.
	}

	// swizzle operator declarations
#define vec2_DECLARE_2D_SWIZZLE(a, b) \
	void Vector2SwizzleSet##a##b( const Vector2& v, Vector2* self ){ \
		self->a = v.x; \
		self->b = v.y; \
	} \
	Vector2 Vector2SwizzleGet##a##b( Vector2* self ){ \
		return Vector2( self->a, self->b ); \
	}

	vec2_DECLARE_2D_SWIZZLE(x,y)
	vec2_DECLARE_2D_SWIZZLE(y,x)

#undef vec2_DECLARE_2D_SWIZZLE

	fc::string Vector2ToString( Vector2 *self )
	{
		return fc::string();
	}

} //namespace script


void ScriptEngine::RegisterVector2()
{
	int r(0);
	using namespace script;
	r = engine->RegisterObjectType( "vec2", sizeof(Vector2), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_CA); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "vec2", "float x", offsetof(Vector2, x)); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "vec2", "float y", offsetof(Vector2, y)); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "vec2", asBEHAVE_CONSTRUCT,  "void f()", asFUNCTION(Vector2DefaultConstructor), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "vec2", asBEHAVE_CONSTRUCT,  "void f(const vec2 &in)", asFUNCTION(ValueCopyConstruct<Vector2>), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "vec2", asBEHAVE_CONSTRUCT,  "void f(float)", asFUNCTION((ValueInitConstruct_1Arg<Vector2, float>)), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "vec2", asBEHAVE_CONSTRUCT,  "void f(float, float)", asFUNCTION((ValueInitConstruct_2Arg<Vector2, float>)), asCALL_CDECL_OBJLAST); assert( r >= 0 );

	// operator overloads
	r = engine->RegisterObjectMethod( "vec2", "vec2 &opAssign(const vec2 &in)", asMETHODPR(Vector2, operator =, (const Vector2&), Vector2&), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec2", "vec2 &opAssign(float)", asMETHODPR(Vector2, operator =, (float), Vector2&), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec2", "bool opEquals(const vec2 &in) const", asMETHODPR(Vector2, operator ==, (const Vector2&) const, bool), asCALL_THISCALL); assert( r >= 0 );
	//r = engine->RegisterObjectMethod( "vec2", "bool opEquals(const vec2 &in) const", asMETHODPR(Vector2, operator !=, (const Vector2&) const, bool), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec2", "vec2 &opAddAssign(const vec2 &in)", asMETHODPR(Vector2, operator +=, (const Vector2&), Vector2&), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec2", "vec2 &opSubAssign(const vec2 &in)", asMETHODPR(Vector2, operator -=, (const Vector2&), Vector2&), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec2", "vec2 &opMulAssign(const vec2 &in)", asMETHODPR(Vector2, operator *=, (const Vector2&), Vector2&), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec2", "vec2 &opDivAssign(const vec2 &in)", asMETHODPR(Vector2, operator /=, (const Vector2&), Vector2&), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec2", "vec2 &opAddAssign(float)", asMETHODPR(Vector2, operator +=, (float), Vector2&), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec2", "vec2 &opSubAssign(float)", asMETHODPR(Vector2, operator -=, (float), Vector2&), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec2", "vec2 &opMulAssign(float)", asMETHODPR(Vector2, operator *=, (float), Vector2&), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec2", "vec2 &opDivAssign(float)", asMETHODPR(Vector2, operator /=, (float), Vector2&), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec2", "vec2 opAdd(const vec2 &in) const", asMETHODPR(Vector2, operator +, (const Vector2&) const, Vector2), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec2", "vec2 opSub(const vec2 &in) const", asMETHODPR(Vector2, operator -, (const Vector2&) const, Vector2), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec2", "vec2 opMul(const vec2 &in) const", asMETHODPR(Vector2, operator *, (const Vector2&) const, Vector2), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec2", "vec2 opDiv(const vec2 &in) const", asMETHODPR(Vector2, operator /, (const Vector2&) const, Vector2), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec2", "vec2 opAdd(float) const", asMETHODPR(Vector2, operator +, (float) const, Vector2), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec2", "vec2 opSub(float) const", asMETHODPR(Vector2, operator -, (float) const, Vector2), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec2", "vec2 opMul(float) const", asMETHODPR(Vector2, operator *, (float) const, Vector2), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec2", "vec2 opDiv(float) const", asMETHODPR(Vector2, operator /, (float) const, Vector2), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec2", "vec2 opAdd(float, const vec2 &in) const", asFUNCTIONPR(operator +, (float, const Vector2&), Vector2), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec2", "vec2 opSub(float, const vec2 &in) const", asFUNCTIONPR(operator -, (float, const Vector2&), Vector2), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec2", "vec2 opMul(float, const vec2 &in) const", asFUNCTIONPR(operator *, (float, const Vector2&), Vector2), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec2", "vec2 opDiv(float, const vec2 &in) const", asFUNCTIONPR(operator /, (float, const Vector2&), Vector2), asCALL_CDECL_OBJLAST); assert( r >= 0 );

	// swizzles
	r = engine->RegisterObjectMethod( "vec2", "vec2 get_xy() const", asFUNCTION(Vector2SwizzleGetxy), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec2", "vec2 get_yx() const", asFUNCTION(Vector2SwizzleGetyx), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec2", "void set_xy(const vec2&)", asFUNCTION(Vector2SwizzleSetxy), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec2", "void set_yx(const vec2&)", asFUNCTION(Vector2SwizzleSetyx), asCALL_CDECL_OBJLAST); assert( r >= 0 );

	// Register the object methods
	r = engine->RegisterObjectMethod( "vec2", "vec2& normalize()", asMETHODPR( Vector2, Normalize, (void), Vector2&), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec2", "vec2 normal() const", asMETHODPR( Vector2, Normal, (void) const, Vector2), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec2", "float length() const", asMETHODPR( Vector2, Length, (void) const, float), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec2", "float length_squared() const", asMETHODPR( Vector2, LengthSquared, (void) const, float), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec2", "float distance(const vec2 &in) const", asMETHODPR( Vector2, Distance, (const Vector2 &v) const, float), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec2", "float distance_squared(const vec2 &in) const", asMETHODPR( Vector2, DistanceSquared, (const Vector2 &v) const, float), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec2", "float dot(const vec2 &in) const", asMETHODPR( Vector2, Dot, (const Vector2 &v) const, float), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec2", "float cross(const vec2 &in) const", asMETHODPR( Vector2, Cross, (const Vector2 &v) const, float), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec2", "float angle() const", asMETHODPR( Vector2, Angle, (void) const, float), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec2", "float angle(const vec2 &in) const", asMETHODPR( Vector2, Angle, (const Vector2 &) const, float), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec2", "vec2& clamp(const vec2 &in, const vec2 &in)", asMETHODPR( Vector2, Clamp, (const Vector2&, const Vector2&), Vector2&), asCALL_THISCALL ); assert( r >= 0 );

	r = engine->RegisterObjectMethod( "vec2", "float min() const", asMETHODPR( Vector2, Min, (void) const, float), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec2", "float max() const", asMETHODPR( Vector2, Max, (void) const, float), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec2", "vec2 abs() const", asMETHODPR( Vector2, Abs, (void) const, Vector2), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec2", "vec2 ceil() const", asMETHODPR( Vector2, Ceil, (void) const, Vector2), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec2", "vec2 round() const", asMETHODPR( Vector2, Round, (void) const, Vector2), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec2", "vec2 floor() const", asMETHODPR( Vector2, Floor, (void) const, Vector2), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec2", "vec2 negate() const", asMETHODPR( Vector2, Negate, (void) const, Vector2), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec2", "vec2 polar(const vec2 &in, float) const", asMETHODPR( Vector2, Polar, (const Vector2&, float) const, Vector2), asCALL_THISCALL ); assert( r >= 0 );

	r = engine->RegisterObjectMethod( "vec2", "string to_string()", asFUNCTION(Vector2ToString), asCALL_CDECL_OBJFIRST); assert( r >= 0 );
}


namespace script
{
	void RectfDefaultConstructor( Rectf *self )
	{
		new (self) Rectf(0.f, 0.f, 0.f, 0.f);
	}

	void RectfInitConstructFromVector2( const Vector2 &p, const Vector2 &s, Rectf *self )
	{
		new (self) Rectf(p, s);
	}

	fc::string RectfToString( Rectf *self )
	{
		return fc::string();
	}

	void RectfSetX( float x, Rectf *self )
	{
		self->min.x = x;
	}

	void RectfSetY( float y, Rectf *self )
	{
		self->min.y = y;
	}

	void RectfSetWidth( float w, Rectf *self )
	{
		self->max.x = self->min.x + w;
	}

	void RectfSetHeight( float h, Rectf *self )
	{
		self->max.y = self->min.y + h;
	}

	Vector2 RectfGetPosition( Rectf *self )
	{
		return self->min;
	}


} //namespace script


void ScriptEngine::RegisterRectf()
{
	int r(0);
	using namespace script;
	r = engine->RegisterObjectType( "rectf", sizeof(Rectf), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_CA); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "rectf", "vec2 min", offsetof(Rectf, min)); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "rectf", "vec2 max", offsetof(Rectf, max)); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "rectf", asBEHAVE_CONSTRUCT,  "void f()", asFUNCTION(RectDefaultConstructor), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "rectf", asBEHAVE_CONSTRUCT,  "void f(const rectf &in)", asFUNCTION(ValueCopyConstruct<Rectf>), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "rectf", asBEHAVE_CONSTRUCT,  "void f(float, float, float, float)", asFUNCTION((ValueInitConstruct_4Arg<Rectf, float>)), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "rectf", asBEHAVE_CONSTRUCT,  "void f(const vec2 &in, const vec2 &in)", asFUNCTION(RectfInitConstructFromVector2), asCALL_CDECL_OBJLAST); assert( r >= 0 );

	// operator overloads
	r = engine->RegisterObjectMethod( "rectf", "rectf &opAssign(const rectf &in)", asMETHODPR(Rectf, operator =, (const Rectf&), Rectf&), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "rectf", "bool opEquals(const rectf &in) const", asMETHODPR(Rectf, operator ==, (const Rectf&) const, bool), asCALL_THISCALL); assert( r >= 0 );
	//r = engine->RegisterObjectMethod( "rectf", "bool opEquals(const rectf &in) const", asMETHODPR(Rectf, operator !=, (const Rectf&) const, bool), asCALL_THISCALL); assert( r >= 0 );

	// getters, setters
	r = engine->RegisterObjectMethod( "rectf", "float get_x() const", asMETHOD(Rectf, Top), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "rectf", "float get_y() const", asMETHOD(Rectf, Bottom), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "rectf", "float get_width() const", asMETHOD(Rectf, Width), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "rectf", "float get_height() const", asMETHOD(Rectf, Height), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "rectf", "void set_x(float)", asFUNCTION(RectfSetX), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "rectf", "void set_y(float)", asFUNCTION(RectfSetY), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "rectf", "void set_width(float)", asFUNCTION(RectfSetWidth), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "rectf", "void set_height(float)", asFUNCTION(RectfSetHeight), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "rectf", "vec2 get_pos() const", asFUNCTION(RectfGetPosition), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "rectf", "vec2 get_size() const", asMETHOD(Rectf, Size), asCALL_THISCALL); assert( r >= 0 );

	r = engine->RegisterObjectMethod( "rectf", "float top() const", asMETHOD(Rectf, Top), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "rectf", "float bottom() const", asMETHOD(Rectf, Bottom), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "rectf", "float left() const", asMETHOD(Rectf, Left), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "rectf", "float right() const", asMETHOD(Rectf, Right), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "rectf", "vec2 top_left() const", asMETHOD(Rectf, TopLeft), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "rectf", "vec2 bottom_left() const", asMETHOD(Rectf, BottomLeft), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "rectf", "vec2 bottom_right() const", asMETHOD(Rectf, BottomRight), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "rectf", "vec2 top_right() const", asMETHOD(Rectf, TopRight), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "rectf", "vec2 center() const", asMETHOD(Rectf, Center), asCALL_THISCALL); assert( r >= 0 );

	r = engine->RegisterObjectMethod( "rectf", "string to_string()", asFUNCTION(RectfToString), asCALL_CDECL_OBJFIRST); assert( r >= 0 );

}


namespace script
{
	void Vector3DefaultConstructor( Vector3 *self )
	{
		new (self) Vector3(0.f, 0.f);
	}

	// swizzle operator declarations
#define vec3_DECLARE_2D_SWIZZLE(a, b) \
	void Vector3SwizzleSet##a##b( const Vector2& v, Vector3* self ){ \
		self->a = v.x; \
		self->b = v.y; \
	} \
	Vector2 Vector3SwizzleGet##a##b( Vector3* self ){ \
		return Vector2( self->a, self->b ); \
	}

#define vec3_DECLARE_3D_SWIZZLE(a, b, c) \
	void Vector3SwizzleSet##a##b##c( const Vector3& v, Vector3* self ){ \
		self->a = v.x; \
		self->b = v.y; \
		self->c = v.z; \
	} \
	Vector3 Vector3SwizzleGet##a##b##c( Vector3* self ){ \
		return Vector3( self->a, self->b, self->c ); \
	}

	vec3_DECLARE_2D_SWIZZLE(x,y);
	vec3_DECLARE_2D_SWIZZLE(x,z);
	vec3_DECLARE_2D_SWIZZLE(y,x);
	vec3_DECLARE_2D_SWIZZLE(y,z);
	vec3_DECLARE_2D_SWIZZLE(z,x);
	vec3_DECLARE_2D_SWIZZLE(z,y);
	vec3_DECLARE_3D_SWIZZLE(x,y,z);
	vec3_DECLARE_3D_SWIZZLE(x,z,y);
	vec3_DECLARE_3D_SWIZZLE(y,x,z);
	vec3_DECLARE_3D_SWIZZLE(y,z,x);
	vec3_DECLARE_3D_SWIZZLE(z,x,y);
	vec3_DECLARE_3D_SWIZZLE(z,y,x);

#undef vec3_DECLARE_2D_SWIZZLE
#undef vec3_DECLARE_3D_SWIZZLE

	fc::string Vector3ToString( Vector3 *self )
	{
		return fc::string();
	}

} //namespace script


void ScriptEngine::RegisterVector3()
{
	int r;
	using namespace script;
	r = engine->RegisterObjectType( "vec3", sizeof(Vector3), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_CA); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "vec3", "float x", offsetof(Vector3, x)); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "vec3", "float y", offsetof(Vector3, y)); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "vec3", "float z", offsetof(Vector3, z)); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "vec3", asBEHAVE_CONSTRUCT,  "void f()", asFUNCTION(Vector3DefaultConstructor), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "vec3", asBEHAVE_CONSTRUCT,  "void f(const vec3 &in)", asFUNCTION(ValueCopyConstruct<Vector3>), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "vec3", asBEHAVE_CONSTRUCT,  "void f(float, float, float)", asFUNCTION((ValueInitConstruct_3Arg<Vector3, float>)), asCALL_CDECL_OBJLAST); assert( r >= 0 );

	r = engine->RegisterObjectMethod( "vec3", "vec3 &opAddAssign(const vec3 &in)", asMETHODPR(Vector3, operator+=, (const Vector3 &), Vector3&), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec3", "vec3 &opSubAssign(const vec3 &in)", asMETHODPR(Vector3, operator-=, (const Vector3 &), Vector3&), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec3", "vec3 &opMulAssign(const vec3 &in)", asMETHODPR(Vector3, operator *=, (const Vector3&), Vector3&), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec3", "vec3 &opDivAssign(const vec3 &in)", asMETHODPR(Vector3, operator /=, (const Vector3&), Vector3&), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec3", "vec3 &opMulAssign(float)", asMETHODPR(Vector3, operator*=, (float), Vector3&), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec3", "vec3 &opDivAssign(float)", asMETHODPR(Vector3, operator/=, (float), Vector3&), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec3", "vec3 &opAddAssign(float)", asMETHODPR(Vector3, operator +=, (float), Vector3&), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec3", "vec3 &opSubAssign(float)", asMETHODPR(Vector3, operator -=, (float), Vector3&), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec3", "vec3 opAdd(const vec3 &in) const", asMETHODPR(Vector3, operator +, (const Vector3&) const, Vector3), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec3", "vec3 opSub(const vec3 &in) const", asMETHODPR(Vector3, operator -, (const Vector3&) const, Vector3), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec3", "vec3 opMul(const vec3 &in) const", asMETHODPR(Vector3, operator *, (const Vector3&) const, Vector3), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec3", "vec3 opDiv(const vec3 &in) const", asMETHODPR(Vector3, operator /, (const Vector3&) const, Vector3), asCALL_THISCALL); assert( r >= 0 );

	r = engine->RegisterObjectMethod( "vec3", "vec2 get_xy() const", asFUNCTION(Vector3SwizzleGetxy), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec3", "vec2 get_xz() const", asFUNCTION(Vector3SwizzleGetxz), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec3", "vec2 get_yx() const", asFUNCTION(Vector3SwizzleGetyx), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec3", "vec2 get_yz() const", asFUNCTION(Vector3SwizzleGetyz), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec3", "vec2 get_zx() const", asFUNCTION(Vector3SwizzleGetzy), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec3", "vec2 get_zy() const", asFUNCTION(Vector3SwizzleGetzy), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec3", "vec3 get_xyz() const", asFUNCTION(Vector3SwizzleGetxyz), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec3", "vec3 get_xzy() const", asFUNCTION(Vector3SwizzleGetxzy), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec3", "vec3 get_yxz() const", asFUNCTION(Vector3SwizzleGetyxz), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec3", "vec3 get_yzx() const", asFUNCTION(Vector3SwizzleGetyzx), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec3", "vec3 get_zxy() const", asFUNCTION(Vector3SwizzleGetzxy), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec3", "vec3 get_zyx() const", asFUNCTION(Vector3SwizzleGetzyx), asCALL_CDECL_OBJLAST); assert( r >= 0 );

	r = engine->RegisterObjectMethod( "vec3", "void set_xy(const vec2&)", asFUNCTION(Vector3SwizzleSetxy), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec3", "void set_xz(const vec2&)", asFUNCTION(Vector3SwizzleSetxz), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec3", "void set_yx(const vec2&)", asFUNCTION(Vector3SwizzleSetyx), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec3", "void set_yz(const vec2&)", asFUNCTION(Vector3SwizzleSetyz), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec3", "void set_zx(const vec2&)", asFUNCTION(Vector3SwizzleSetzx), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec3", "void set_zy(const vec2&)", asFUNCTION(Vector3SwizzleSetzy), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec3", "void set_xyz(const vec3&)", asFUNCTION(Vector3SwizzleSetxyz), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec3", "void set_xzy(const vec3&)", asFUNCTION(Vector3SwizzleSetxzy), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec3", "void set_yxz(const vec3&)", asFUNCTION(Vector3SwizzleSetyxz), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec3", "void set_yzx(const vec3&)", asFUNCTION(Vector3SwizzleSetyzx), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec3", "void set_zxy(const vec3&)", asFUNCTION(Vector3SwizzleSetzxy), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec3", "void set_zyx(const vec3&)", asFUNCTION(Vector3SwizzleSetzyx), asCALL_CDECL_OBJLAST); assert( r >= 0 );

	r = engine->RegisterObjectMethod( "vec3", "vec3& normalize()", asMETHODPR( Vector3, Normalize, (void), Vector3&), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec3", "vec3 normal() const", asMETHODPR( Vector3, Normal, (void) const, Vector3), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec3", "float length() const", asMETHODPR( Vector3, Length, (void) const, float), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec3", "float length_squared() const", asMETHODPR( Vector3, LengthSquared, (void) const, float), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec3", "float distance(const vec3 &in) const", asMETHODPR( Vector3, Distance, (const Vector3 &) const, float), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec3", "float distance_squared(const vec3 &in) const", asMETHODPR( Vector3, DistanceSquared, (const Vector3 &) const, float), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec3", "float dot(const vec3 &in) const", asMETHODPR( Vector3, Dot, (const Vector3 &) const, float), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec3", "vec3 cross(const vec3 &in) const", asMETHODPR( Vector3, Cross, (const Vector3 &) const, Vector3), asCALL_THISCALL ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "vec3", "vec3& clamp(const vec3 &in, const vec3 &in)", asMETHODPR( Vector3, Clamp, (const Vector3&, const Vector3&), Vector3&), asCALL_THISCALL ); assert( r >= 0 );

	r = engine->RegisterObjectMethod( "vec3", "string to_string()", asFUNCTION(Vector3ToString), asCALL_CDECL_OBJFIRST); assert( r >= 0 );
}


namespace script
{
	void Vector4DefaultConstructor( Vector4 *self )
	{
		new (self) Vector4(0.f, 0.f, 0.f, 0.f);
	}
}


void ScriptEngine::RegisterVector4()
{
	int r;
	using namespace script;
	r = engine->RegisterObjectType( "vec4", sizeof(Vector4), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_CA); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "vec4", "float x", offsetof(Vector4, x)); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "vec4", "float y", offsetof(Vector4, y)); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "vec4", "float z", offsetof(Vector4, z)); assert( r >= 0 );
	r = engine->RegisterObjectProperty( "vec4", "float w", offsetof(Vector4, z)); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "vec4", asBEHAVE_CONSTRUCT,  "void f()", asFUNCTION(Vector4DefaultConstructor), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "vec4", asBEHAVE_CONSTRUCT,  "void f(const vec4 &in)", asFUNCTION(ValueCopyConstruct<Vector4>), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "vec4", asBEHAVE_CONSTRUCT,  "void f(float, float, float, float)", asFUNCTION((ValueInitConstruct_4Arg<Vector4, float>)), asCALL_CDECL_OBJLAST); assert( r >= 0 );
}


void ScriptEngine::RegisterMatrix()
{
	int r(0);
	using namespace script;
	r = engine->RegisterObjectType( "matrix", sizeof(Matrix), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_C); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "matrix", asBEHAVE_CONSTRUCT,  "void f()", asFUNCTION(ValueConstruct<Matrix>), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( "matrix", asBEHAVE_CONSTRUCT,  "void f(const matrix &in)", asFUNCTION(ValueCopyConstruct<Matrix>), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "matrix", "float &opIndex(int)", asMETHODPR(Matrix, operator [], (int), float&), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "matrix", "const float &opIndex(int) const", asMETHODPR(Matrix, operator [], (int) const, const float&), asCALL_THISCALL); assert( r >= 0 );
	//r = engine->RegisterObjectMethod( "matrix", "matrix &opAssign(const matrix &in)", asMETHODPR(Matrix, operator =, (const Matrix&), Matrix&), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "matrix", "bool opEquals(const matrix &in) const", asMETHODPR(Matrix, operator ==, (const Matrix&) const, bool), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "matrix", "matrix opMul(const matrix &in) const", asMETHODPR(Matrix, operator *, (const Matrix&) const, Matrix), asCALL_THISCALL); assert( r >= 0 );
/*
	r = engine->RegisterObjectMethod( "matrix", "matrix opDiv(const matrix &in) const", asMETHODPR(Matrix, operator /, (const Matrix&) const, Matrix), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "matrix", "matrix opAdd(const matrix &in) const", asMETHODPR(Matrix, operator +, (const Matrix&) const, Matrix), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "matrix", "matrix opSub(const matrix &in) const", asMETHODPR(Matrix, operator -, (const Matrix&) const, Matrix), asCALL_THISCALL); assert( r >= 0 );

	r = engine->RegisterObjectMethod( "matrix", "matrix opMul(float) const", asMETHODPR(Matrix, operator *, (float) const, Matrix), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "matrix", "matrix opDiv(float) const", asMETHODPR(Matrix, operator /, (float) const, Matrix), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "matrix", "matrix create_orthographic(float, float, float, float, float, float) const", asFUNCTIONPR(Matrix::CreateOrthographic, (float, float, float, float, float, float), Matrix), asCALL_CDECL_OBJLAST ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "matrix", "matrix create_perspective(float, float, float, float, float) const", asFUNCTIONPR(Matrix::CreatePerspective, (float, float, float, float, float), Matrix), asCALL_CDECL_OBJLAST ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "matrix", "matrix create_look_at(const vec3& in, const vec3& in, const vec3& in) const", asFUNCTIONPR(Matrix::CreateLookAt, (const Vector3& , const Vector3& , const Vector3&), Matrix), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "matrix", "matrix create_translation(const vec3& in) const", asFUNCTIONPR(Matrix::CreateTranslation, (const Vector3&), Matrix), asCALL_CDECL_OBJLAST ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "matrix", "matrix create_scale(const vec3& in) const", asFUNCTIONPR(Matrix::CreateScale, (const Vector3& ), Matrix), asCALL_CDECL_OBJLAST ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "matrix", "matrix create_rotation(const vec3& in) const", asFUNCTIONPR(Matrix::CreateRotation, (const Vector3& ), Matrix), asCALL_CDECL_OBJLAST ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "matrix", "matrix create_rotation_x(float) const", asFUNCTIONPR(Matrix::CreateRotationX, (float ), Matrix), asCALL_CDECL_OBJLAST ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "matrix", "matrix create_rotation_y(float) const", asFUNCTIONPR(Matrix::CreateRotationY, (float ), Matrix), asCALL_CDECL_OBJLAST ); assert( r >= 0 );
	r = engine->RegisterObjectMethod( "matrix", "matrix create_rotation_z(float) const", asFUNCTIONPR(Matrix::CreateRotationZ, (float ), Matrix), asCALL_CDECL_OBJLAST ); assert( r >= 0 );
*/
	//r = engine->RegisterObjectMethod( "matrix", "matrix identity() const", asFUNCTION(MatrixGetIdentity), asCALL_CDECL_OBJLAST); assert( r >= 0 );

}


void ScriptEngine::RegisterMathFunctions()
{
	int r(0);
	const int CALL_TYPE = asCALL_CDECL;

	r = engine->RegisterGlobalFunction( "float cos(float)", asFUNCTIONPR(cosf, (float), float), CALL_TYPE); assert( r >= 0 );
	r = engine->RegisterGlobalFunction( "float sin(float)", asFUNCTIONPR(sinf, (float), float), CALL_TYPE); assert( r >= 0 );
	r = engine->RegisterGlobalFunction( "float tan(float)", asFUNCTIONPR(tanf, (float), float), CALL_TYPE); assert( r >= 0 );
	r = engine->RegisterGlobalFunction( "float acos(float)", asFUNCTIONPR(acosf, (float), float), CALL_TYPE); assert( r >= 0 );
	r = engine->RegisterGlobalFunction( "float asin(float)", asFUNCTIONPR(asinf, (float), float), CALL_TYPE); assert( r >= 0 );
	r = engine->RegisterGlobalFunction( "float atan(float)", asFUNCTIONPR(atanf, (float), float), CALL_TYPE); assert( r >= 0 );
	r = engine->RegisterGlobalFunction( "float atan2(float, float)", asFUNCTIONPR(atan2f, (float, float), float), CALL_TYPE); assert( r >= 0 );
	r = engine->RegisterGlobalFunction( "float cosh(float)", asFUNCTIONPR(coshf, (float), float), CALL_TYPE); assert( r >= 0 );
	r = engine->RegisterGlobalFunction( "float sinh(float)", asFUNCTIONPR(sinhf, (float), float), CALL_TYPE); assert( r >= 0 );
	r = engine->RegisterGlobalFunction( "float tanh(float)", asFUNCTIONPR(tanhf, (float), float), CALL_TYPE); assert( r >= 0 );
	r = engine->RegisterGlobalFunction( "float log(float)", asFUNCTIONPR(logf, (float), float), CALL_TYPE); assert( r >= 0 );
	r = engine->RegisterGlobalFunction( "float log10(float)", asFUNCTIONPR(log10f, (float), float), CALL_TYPE); assert( r >= 0 );
	r = engine->RegisterGlobalFunction( "float pow(float, float)", asFUNCTIONPR(powf, (float, float), float), CALL_TYPE); assert( r >= 0 );
	r = engine->RegisterGlobalFunction( "float sqrt(float)", asFUNCTIONPR(sqrtf, (float), float), CALL_TYPE); assert( r >= 0 );
	r = engine->RegisterGlobalFunction( "float ceil(float)", asFUNCTIONPR(ceilf, (float), float), CALL_TYPE); assert( r >= 0 );
	r = engine->RegisterGlobalFunction( "float abs(float)", asFUNCTIONPR(fabsf, (float), float), CALL_TYPE); assert( r >= 0 );
	r = engine->RegisterGlobalFunction( "float floor(float)", asFUNCTIONPR(floorf, (float), float), CALL_TYPE); assert( r >= 0 );
	r = engine->RegisterGlobalFunction( "float fmod(float, float)", asFUNCTIONPR(fmodf, (float, float), float), CALL_TYPE); assert( r >= 0 );

	r = engine->RegisterGlobalFunction( "void sincos(float, float&, float&)", asFUNCTIONPR(fc::sincos, (float, float&, float&), void), CALL_TYPE); assert( r >= 0 );
	r = engine->RegisterGlobalFunction( "void dsincos(float, float&, float&)", asFUNCTIONPR(fc::dsincos, (float, float&, float&), void), CALL_TYPE); assert( r >= 0 );
	r = engine->RegisterGlobalFunction( "vec2 sincos(float)", asFUNCTIONPR(Math::SinCos, (float), Vector2), CALL_TYPE); assert( r >= 0 );

	r = engine->RegisterGlobalFunction( "int distance( int, int, int, int )", asFUNCTIONPR( Math::Distance<int>, ( int, int, int, int ), int), CALL_TYPE ); assert( r >= 0 );
	r = engine->RegisterGlobalFunction( "int distance_squared( int, int, int, int )", asFUNCTIONPR( Math::DistanceSquared<int>, ( int, int, int, int ), int), CALL_TYPE ); assert( r >= 0 );
	r = engine->RegisterGlobalFunction( "float distance( float, float, float, float )", asFUNCTIONPR( Math::Distance<float>, ( float, float, float, float ), float), CALL_TYPE ); assert( r >= 0 );
	r = engine->RegisterGlobalFunction( "float distance_squared( float, float, float, float )", asFUNCTIONPR( Math::DistanceSquared<float>, ( float, float, float, float ), float), CALL_TYPE ); assert( r >= 0 );
	//r = engine->RegisterGlobalFunction( "float turn_towards(const vec2& in, const vec2& in, float, float)", asFUNCTION( Math::TurnTorwards ), CALL_TYPE ); assert( r >= 0 );

	r = engine->RegisterGlobalFunction( "float dcos(float)", asFUNCTIONPR( Math::Dcos, ( float ), float), CALL_TYPE ); assert( r >= 0 );
	r = engine->RegisterGlobalFunction( "float dsin(float)", asFUNCTIONPR( Math::Dsin, ( float ), float), CALL_TYPE ); assert( r >= 0 );
	r = engine->RegisterGlobalFunction( "float to_degrees(float)", asFUNCTIONPR( Math::ToDegrees, ( float ), float), CALL_TYPE ); assert( r >= 0 );
	r = engine->RegisterGlobalFunction( "float to_radians(float)", asFUNCTIONPR( Math::ToRadians, ( float ), float), CALL_TYPE ); assert( r >= 0 );

	r = engine->RegisterGlobalFunction( "int min(int, int)", asFUNCTIONPR( Math::Min, ( int, int ), int), CALL_TYPE ); assert( r >= 0 );
	r = engine->RegisterGlobalFunction( "int min(int, int, int)", asFUNCTIONPR( Math::Min, ( int, int, int ), int), CALL_TYPE ); assert( r >= 0 );
	r = engine->RegisterGlobalFunction( "float min(float, float)", asFUNCTIONPR( Math::Min, ( float, float ), float), CALL_TYPE ); assert( r >= 0 );
	r = engine->RegisterGlobalFunction( "float min(float, float, float)", asFUNCTIONPR( Math::Min, ( float, float, float ), float), CALL_TYPE ); assert( r >= 0 );
	r = engine->RegisterGlobalFunction( "int max(int, int)", asFUNCTIONPR( Math::Max, ( int, int ), int), CALL_TYPE ); assert( r >= 0 );
	r = engine->RegisterGlobalFunction( "int max(int, int, int)", asFUNCTIONPR( Math::Max, ( int, int, int ), int), CALL_TYPE ); assert( r >= 0 );
	r = engine->RegisterGlobalFunction( "float max(float, float)", asFUNCTIONPR( Math::Max, ( float, float ), float), CALL_TYPE ); assert( r >= 0 );
	r = engine->RegisterGlobalFunction( "float max(float, float, float)", asFUNCTIONPR( Math::Max, ( float, float, float ), float), CALL_TYPE ); assert( r >= 0 );

	r = engine->RegisterGlobalFunction( "int clamp( int, int, int )", asFUNCTIONPR( Math::Clamp, ( int, int, int ), int), CALL_TYPE ); assert( r >= 0 );
	r = engine->RegisterGlobalFunction( "float clamp( float, float, float )", asFUNCTIONPR( Math::Clamp, ( float, float, float ), float), CALL_TYPE ); assert( r >= 0 );
	r = engine->RegisterGlobalFunction( "vec2 clamp( const vec2& in, const vec2& in, const vec2& in )", asFUNCTIONPR( Math::Clamp, ( const Vector2&, const Vector2&, const Vector2& ), Vector2), CALL_TYPE ); assert( r >= 0 );
	r = engine->RegisterGlobalFunction( "vec3 clamp( const vec3& in, const vec3& in, const vec3& in )", asFUNCTIONPR( Math::Clamp, ( const Vector3&, const Vector3&, const Vector3& ), Vector3), CALL_TYPE ); assert( r >= 0 );

	// Collisions
	r = engine->RegisterGlobalFunction( "float distance_to_line_segment( const vec2& in, const vec2& in, const vec2& in )", asFUNCTIONPR( Math::DistancetoLineSegment, ( const Vector2&, const Vector2&, const Vector2& ), float), CALL_TYPE ); assert( r >= 0 );
	r = engine->RegisterGlobalFunction( "float distance_to_line_segment( const vec3& in, const vec3& in, const vec3& in )", asFUNCTIONPR( Math::DistancetoLineSegment, ( const Vector3&, const Vector3&, const Vector3& ), float), CALL_TYPE ); assert( r >= 0 );

	// Interpolation functions
	r = engine->RegisterGlobalFunction( "float smooth_step( float, float, float )", asFUNCTIONPR( Math::SmoothStep, ( float, float, float ), float), CALL_TYPE ); assert( r >= 0 );
	r = engine->RegisterGlobalFunction( "float lerp( float, float, float )", asFUNCTIONPR( Math::Lerp, ( float, float, float ), float), CALL_TYPE ); assert( r >= 0 );
	r = engine->RegisterGlobalFunction( "float bezier( float, float, float, float )", asFUNCTIONPR( Math::Bezier, ( float, float, float, float ), float), CALL_TYPE ); assert( r >= 0 );
	r = engine->RegisterGlobalFunction( "float bezier( float, float, float, float, float )", asFUNCTIONPR( Math::Bezier, ( float, float, float, float, float ), float), CALL_TYPE ); assert( r >= 0 );
	r = engine->RegisterGlobalFunction( "float bezier( float, float, float, float, float, float )", asFUNCTIONPR( Math::Bezier, ( float, float, float, float, float, float ), float), CALL_TYPE ); assert( r >= 0 );
	r = engine->RegisterGlobalFunction( "float catmull_rom( float, float, float, float, float )", asFUNCTIONPR( Math::CatmullRom, ( float, float, float, float, float ), float), CALL_TYPE ); assert( r >= 0 );

	r = engine->RegisterGlobalFunction( "vec2 smooth_step( const vec2& in, const vec2& in, float )", asFUNCTIONPR( Math::SmoothStep, ( const Vector2&, const Vector2&, float ), Vector2), CALL_TYPE ); assert( r >= 0 );
	r = engine->RegisterGlobalFunction( "vec2 lerp( const vec2& in, const vec2& in, float )", asFUNCTIONPR( Math::Lerp, ( const Vector2&, const Vector2&, float ), Vector2), CALL_TYPE ); assert( r >= 0 );
	r = engine->RegisterGlobalFunction( "vec2 bezier( const vec2& in, const vec2& in, const vec2& in, float )", asFUNCTIONPR( Math::Bezier, ( const Vector2&, const Vector2&, const Vector2&, float ), Vector2), CALL_TYPE ); assert( r >= 0 );
	r = engine->RegisterGlobalFunction( "vec2 bezier( const vec2& in, const vec2& in, const vec2& in, const vec2& in, float )", asFUNCTIONPR( Math::Bezier, ( const Vector2&, const Vector2&, const Vector2&, const Vector2&, float ), Vector2), CALL_TYPE ); assert( r >= 0 );
	r = engine->RegisterGlobalFunction( "vec2 bezier( const vec2& in, const vec2& in, const vec2& in, const vec2& in, const vec2& in, float )", asFUNCTIONPR( Math::Bezier, ( const Vector2&, const Vector2&, const Vector2&, const Vector2&, const Vector2&, float ), Vector2), CALL_TYPE ); assert( r >= 0 );
	r = engine->RegisterGlobalFunction( "vec2 catmull_rom( const vec2& in, const vec2& in, const vec2& in, const vec2& in, float )", asFUNCTIONPR( Math::CatmullRom, ( const Vector2&, const Vector2&, const Vector2&, const Vector2&, float ), Vector2), CALL_TYPE ); assert( r >= 0 );

	r = engine->RegisterGlobalFunction( "vec3 smooth_step( const vec3& in, const vec3& in, float )", asFUNCTIONPR( Math::SmoothStep, ( const Vector3&, const Vector3&, float ), Vector3), CALL_TYPE ); assert( r >= 0 );
	r = engine->RegisterGlobalFunction( "vec3 lerp( const vec3& in, const vec3& in, float )", asFUNCTIONPR( Math::Lerp, ( const Vector3&, const Vector3&, float ), Vector3), CALL_TYPE ); assert( r >= 0 );
	r = engine->RegisterGlobalFunction( "vec3 bezier( const vec3& in, const vec3& in, const vec3& in, float )", asFUNCTIONPR( Math::Bezier, ( const Vector3&, const Vector3&, const Vector3&, float ), Vector3), CALL_TYPE ); assert( r >= 0 );
	r = engine->RegisterGlobalFunction( "vec3 bezier( const vec3& in, const vec3& in, const vec3& in, const vec3& in, float )", asFUNCTIONPR( Math::Bezier, ( const Vector3&, const Vector3&, const Vector3&, const Vector3&, float ), Vector3), CALL_TYPE ); assert( r >= 0 );
	r = engine->RegisterGlobalFunction( "vec3 bezier( const vec3& in, const vec3& in, const vec3& in, const vec3& in, const vec3& in, float )", asFUNCTIONPR( Math::Bezier, ( const Vector3&, const Vector3&, const Vector3&, const Vector3&, const Vector3&, float ), Vector3), CALL_TYPE ); assert( r >= 0 );
	r = engine->RegisterGlobalFunction( "vec3 catmull_rom( const vec3& in, const vec3& in, const vec3& in, const vec3& in, float )", asFUNCTIONPR( Math::CatmullRom, ( const Vector3&, const Vector3&, const Vector3&, const Vector3&, float ), Vector3), CALL_TYPE ); assert( r >= 0 );

	// Random number functions
	r = engine->RegisterGlobalFunction( "int rand()", asFUNCTIONPR(fc::rand, (void), int), CALL_TYPE); assert( r >= 0 );
	r = engine->RegisterGlobalFunction( "int rand(int)", asFUNCTIONPR(fc::rand, (int), int), CALL_TYPE); assert( r >= 0 );
	r = engine->RegisterGlobalFunction( "int rand(int, int)", asFUNCTIONPR(fc::rand, (int, int), int), CALL_TYPE); assert( r >= 0 );
	r = engine->RegisterGlobalFunction( "float randf()", asFUNCTIONPR(fc::randf, (), float), CALL_TYPE); assert( r >= 0 );
	r = engine->RegisterGlobalFunction( "float randf(float)", asFUNCTIONPR(fc::randf, (float), float), CALL_TYPE); assert( r >= 0 );
	r = engine->RegisterGlobalFunction( "float randf(float, float)", asFUNCTIONPR(fc::randf, (float, float), float), CALL_TYPE); assert( r >= 0 );
	r = engine->RegisterGlobalFunction( "vec2 circular_rand(float r = 1.0f)", asFUNCTIONPR(Math::CircularRand, (float), Vector2), CALL_TYPE); assert( r >= 0 );
	r = engine->RegisterGlobalFunction( "vec2 arc_rand(float, float, float r = 1.0f)", asFUNCTIONPR(Math::ArcRand, (float, float, float), Vector2), CALL_TYPE); assert( r >= 0 );

	r = engine->RegisterGlobalFunction( "bool probability(int)", asFUNCTIONPR(fc::probability, (int), bool), CALL_TYPE); assert( r >= 0 );
	r = engine->RegisterGlobalFunction( "bool probability(int, int)", asFUNCTIONPR(fc::probability, (int, int), bool), CALL_TYPE); assert( r >= 0 );
	r = engine->RegisterGlobalFunction( "int variance(int, int)", asFUNCTIONPR(fc::variance, (int, int), int), CALL_TYPE); assert( r >= 0 );
	r = engine->RegisterGlobalFunction( "float variance(float, float)", asFUNCTIONPR(fc::variance, (float, float), float), CALL_TYPE); assert( r >= 0 );

}


void ScriptEngine::RegisterMathInterface()
{
	RegisterPoint();
	RegisterVector2();
	RegisterVector3();
	RegisterVector4();
	RegisterRect();
	RegisterRectf();
	//RegisterColor();
	//RegisterColorf();
	RegisterMatrix();
	RegisterMathFunctions();
}


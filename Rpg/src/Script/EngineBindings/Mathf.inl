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


#include <mono/metadata/object.h>
#include <mono/metadata/loader.h>

#include <fc/math.h>
#include <fc/rand.h>
#include <Catastrophe/Math/Vector2.h>
#include <Catastrophe/Math/Vector3.h>
#include <Catastrophe/Math/Math.h>

#include "Script/MonoEngineBinding.h"


void MonoEngineBinding::Math_SinCos(float* s, float* c, float angle)
{
	fc::sincos(angle, *s, *c);
}


Vector2 MonoEngineBinding::Math_SinCosv(float angle)
{
	return Math::SinCos(angle);
}


float MonoEngineBinding::Math_Sin(float x)
{
	return sinf(x);
}


float MonoEngineBinding::Math_Cos(float x)
{
	return cosf(x);
}


float MonoEngineBinding::Math_Atan2(float y, float x)
{
	return atan2f(y, x);
}


int MonoEngineBinding::Math_Rand(int n)
{
	return fc::rand(n);
}


int MonoEngineBinding::Math_RandRange(int min, int max)
{
	return fc::rand(min, max);
}


float MonoEngineBinding::Math_RandUnitf()
{
	return fc::randf();
}


float MonoEngineBinding::Math_Randf(float n)
{
	return fc::randf(n);
}


float MonoEngineBinding::Math_RandRangef(float min, float max)
{
	return fc::randf(min, max);
}


float MonoEngineBinding::Math_Bezier4pt( float value1, float tangent1, float value2, float tangent2, float t )
{
	return Math::Bezier(value1, tangent1, value2, tangent2, t);
}


float MonoEngineBinding::Math_Hermite( float value1, float tangent1, float value2, float tangent2, float t )
{
	return Math::Hermite(value1, tangent1, value2, tangent2, t);
}


float MonoEngineBinding::Math_CatmullRom( float value1, float value2, float value3, float value4, float t )
{
	return Math::CatmullRom(value1, value2, value3, value4, t);
}


void MonoEngineBinding::BindMathf()
{
	SetNamespace("CatastropheEngine.Mathf::");

	//cmath
	AddInternalCall("SinCos(out float, out float, float)", Math_SinCos);
	AddInternalCall("SinCos(float)", Math_SinCosv);
	AddInternalCall("Sin", Math_Sin);
	AddInternalCall("Cos", Math_Cos);
	AddInternalCall("Atan2", Math_Atan2);

	//random
	AddInternalCall("RandInt(int)", Math_Rand);
	AddInternalCall("RandInt(int, int)", Math_RandRange);
	AddInternalCall("RandFloat()", Math_RandUnitf);
	AddInternalCall("RandFloat(float)", Math_Randf);
	AddInternalCall("RandFloat(float, float)", Math_RandRangef);

	//interpolation
	AddInternalCall("Bezier(float, float, float, float, float)", Math_Bezier4pt);
	AddInternalCall("Hermite", Math_Hermite);
	AddInternalCall("CatmullRom", Math_CatmullRom);

}


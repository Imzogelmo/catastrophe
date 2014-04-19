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


#include <Catastrophe/Math/Vector3.h>
#include <Catastrophe/Math/Matrix.h>

#include "Script/MonoEngineBinding.h"


float MonoEngineBinding::Matrix_Determinant( Matrix* matrix )
{
	return matrix->Determinant();
}


Matrix MonoEngineBinding::Matrix_Transpose( Matrix* matrix )
{
	return matrix->Transpose();
}


Matrix MonoEngineBinding::Matrix_Inverse( Matrix* matrix )
{
	return matrix->Inverse();
}


float MonoEngineBinding::Matrix_GetIndex( Matrix* matrix, int i )
{
	return matrix->m[i];
}


void MonoEngineBinding::Matrix_SetIndex( Matrix* matrix, int i, float value )
{
	matrix->m[i] = value;
}


Matrix MonoEngineBinding::Matrix_Lerp( Matrix* matrix, Matrix* a, Matrix* b, float t )
{
	return matrix->Lerp(*a, *b, t);
}


void MonoEngineBinding::Matrix_Multiply( Matrix* a, Matrix* b, Matrix* out )
{
	*out = *a * *b;
}


Matrix MonoEngineBinding::Matrix_CreateLookAt( Matrix* matrix, Vector3 camera, Vector3 target, Vector3 up )
{
	return matrix->CreateLookAt(camera, target, up);
}


Matrix MonoEngineBinding::Matrix_CreateOrthographic( Matrix* matrix, float left, float right, float bottom, float top, float zNear, float zFar )
{
	return matrix->CreateOrthographic(left, right, bottom, top, zNear, zFar);
}


Matrix MonoEngineBinding::Matrix_CreatePerspective( Matrix* matrix, float fov, float aspect, float up, float zNear, float zFar )
{
	return matrix->CreatePerspective(fov, aspect, up, zNear, zFar);
}


Matrix MonoEngineBinding::Matrix_CreateRotation( Matrix* matrix, Vector3 rotation )
{
	return matrix->CreateRotation(rotation);
}


Matrix MonoEngineBinding::Matrix_CreateTransformation( Matrix* matrix, Vector3 pos, float rotation, Vector3 scale, Vector3 origin )
{
	return matrix->CreateTransformation(pos, rotation, scale, origin);
}


Matrix MonoEngineBinding::Matrix_CreateTranslation( Matrix* matrix, Vector3 pos )
{
	return matrix->CreateTranslation(pos);
}


Matrix MonoEngineBinding::Matrix_CreateScale( Matrix* matrix, Vector3 scale )
{
	return matrix->CreateScale(scale);
}


Matrix MonoEngineBinding::Matrix_CreateRotationX( Matrix* matrix, float radians )
{
	return matrix->CreateRotationX(radians);
}


Matrix MonoEngineBinding::Matrix_CreateRotationY( Matrix* matrix, float radians )
{
	return matrix->CreateRotationY(radians);
}


Matrix MonoEngineBinding::Matrix_CreateRotationZ( Matrix* matrix, float radians )
{
	return matrix->CreateRotationZ(radians);
}



void MonoEngineBinding::BindMatrix4()
{
	AddInternalCall("GetIndex", Matrix_GetIndex);
	AddInternalCall("SetIndex", Matrix_SetIndex);
	AddInternalCall("Determinant", Matrix_Determinant);
	AddInternalCall("Transpose", Matrix_Transpose);
	AddInternalCall("Inverse", Matrix_Inverse);
	AddInternalCall("Lerp", Matrix_Lerp);
	AddInternalCall("Multiply", Matrix_Multiply);
	AddInternalCall("CreateLookAt", Matrix_CreateLookAt);
	AddInternalCall("CreateOrthographic", Matrix_CreateOrthographic);
	AddInternalCall("CreatePerspective", Matrix_CreatePerspective);
	AddInternalCall("CreateRotation", Matrix_CreateRotation);
	AddInternalCall("CreateTransformation", Matrix_CreateTransformation);
	AddInternalCall("CreateTranslation", Matrix_CreateTranslation);
	AddInternalCall("CreateScale", Matrix_CreateScale);
	AddInternalCall("CreateRotationX", Matrix_CreateRotationX);
	AddInternalCall("CreateRotationY", Matrix_CreateRotationY);
	AddInternalCall("CreateRotationZ", Matrix_CreateRotationZ);
}

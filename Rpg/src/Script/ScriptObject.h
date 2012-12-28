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

#include <fc/string.h>

#include "Common.h"
#include "ScriptClass.h"



class ScriptObject : public ScriptClass
{
public:
	ScriptObject( ContextPool* contextPool );
	~ScriptObject();

	void Initialize( const fc::string& class_decl, const fc::string& method_decl = "void run()" );
	asIScriptObject *CreateObject();

	void Update();

	//void DeepCopy( ScriptObject* &_out );

};



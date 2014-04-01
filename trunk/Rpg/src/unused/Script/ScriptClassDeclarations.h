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


struct ScriptClassDeclarations
{
	fc::string class_decl;
	fc::string base_class_decl;
	fc::string method_decl;

	explicit ScriptClassDeclarations(
		const fc::string& classDecl = "",
		const fc::string& baseClassDecl = ""
		) :
		class_decl(classDecl),
		base_class_decl(baseClassDecl),
		method_decl("void update()")
	{}

	ScriptClassDeclarations(
		const fc::string& classDecl,
		const fc::string& baseClassDecl,
		const fc::string& methodDecl
		) :
		class_decl(classDecl),
		base_class_decl(baseClassDecl),
		method_decl(methodDecl)
	{}
};


struct ScriptClassMonsterDeclarations : public ScriptClassDeclarations
{
	ScriptClassMonsterDeclarations() :
		ScriptClassDeclarations("", "Monster")
	{}
};


struct ScriptClassCharacterDeclarations : public ScriptClassDeclarations
{
	ScriptClassCharacterDeclarations() :
		ScriptClassDeclarations("", "Character")
	{}
};


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

#include "Catastrophe/Core/Containers/String.h"
#include "Catastrophe/Core/Containers/StaticString.h"
#include "RpgCommon.h"


/*
 * Contains strings of all the defined terminology used in the game.
 */
class RpgStrings
{
public:

	// Title of the game
	String title;

	// Attributes
	StaticString<16> stats[MAX_STATS];
	StaticString<16> elements[MAX_ELEMENTS];
	StaticString<16> status[MAX_STATUS];
	StaticString<16> classFlags[MAX_CLASS_FLAGS];
	StaticString<16> familyFlags[MAX_FAMILY_FLAGS];
	StaticString<16> itemFlags[MAX_ITEM_FLAGS];

	// In-game terms
	StaticString<16> gold;



	Strings()
	{
		gold = "gil";


	}

	void Serialize( AttributeWriter* f )
	{
		f->BeginNode("Strings");

		Util::SerializeStringArray(xml, "Stats", stats, MAX_STATS);
		Util::SerializeStringArray(xml, "Elements", elements, MAX_ELEMENTS);
		Util::SerializeStringArray(xml, "Status", status, MAX_STATUS);
		Util::SerializeStringArray(xml, "ClassFlags", classFlags, MAX_CLASS_FLAGS);
		Util::SerializeStringArray(xml, "FamilyFlags", familyFlags, MAX_FAMILY_FLAGS);

		f->SetString("title", title.CString());
		f->SetString("gold", gold.CString());
		f->EndNode();
	}

	void Deserialize( AttributeReader* f )
	{
		if( f->NextChild("Strings") )
		{
			Util::DeserializeStringArray(f, "Stats", stats, MAX_STATS);
			Util::DeserializeStringArray(f, "Elements", elements, MAX_ELEMENTS);
			Util::DeserializeStringArray(f, "Status", status, MAX_STATUS);
			Util::DeserializeStringArray(f, "ClassFlags", classFlags, MAX_CLASS_FLAGS);
			Util::DeserializeStringArray(f, "FamilyFlags", familyFlags, MAX_FAMILY_FLAGS);
		}

		title = f->GetString("title");
		gold = f->GetString("gold");
		f->SetToParent();
	}

};

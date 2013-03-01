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
#include <fc/tiny_string.h>
#include "RpgCommon.h"


/*
 * Contains strings of all the defined terminology used in the game.
 */
class RpgStrings
{
public:
	//attributes
	fc::tiny_string<32> stats[MAX_STATS];
	fc::tiny_string<32> elements[MAX_ELEMENTS];
	fc::tiny_string<32> status[MAX_STATUS];
	fc::tiny_string<32> class_flags[MAX_CLASS_FLAGS];
	fc::tiny_string<32> family_flags[MAX_FAMILY_FLAGS];
	fc::tiny_string<32> item_flags[MAX_ITEM_FLAGS];

	//in-game terms
	fc::string title;
	fc::string gold;



	Strings()
	{
		gold = "gil";


	}

	void SerializeXml( XmlWriter* xml )
	{
		xml->BeginNode("Strings");

		Util::SerializeStringArray(xml, "Stats", stats, MAX_STATS);
		Util::SerializeStringArray(xml, "Elements", elements, MAX_ELEMENTS);
		Util::SerializeStringArray(xml, "Status", status, MAX_STATUS);
		Util::SerializeStringArray(xml, "ClassFlags", class_flags, MAX_CLASS_FLAGS);
		Util::SerializeStringArray(xml, "FamilyFlags", family_flags, MAX_FAMILY_FLAGS);

		xml->SetString("title", title.c_str());
		xml->SetString("gold", gold.c_str());
		xml->EndNode();
	}

	void DeserializeXml( XmlReader* xml )
	{
		if( xml->NextChild("Strings") )
		{
			Util::DeserializeStringArray(xml, "Stats", stats, MAX_STATS);
			Util::DeserializeStringArray(xml, "Elements", elements, MAX_ELEMENTS);
			Util::DeserializeStringArray(xml, "Status", status, MAX_STATUS);
			Util::DeserializeStringArray(xml, "ClassFlags", class_flags, MAX_CLASS_FLAGS);
			Util::DeserializeStringArray(xml, "FamilyFlags", family_flags, MAX_FAMILY_FLAGS);
		}

		title = xml->GetString("title");
		gold = xml->GetString("gold");
		xml->SetToParent();
	}

};

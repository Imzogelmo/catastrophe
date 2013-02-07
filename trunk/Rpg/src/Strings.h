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


/*
 * Contains strings of all the defined terminology used in the game.
 */
class Strings
{
public:
	//attributes
	fc::string stats[MAX_STATS];
	fc::string elements[MAX_ELEMENTS];
	fc::string status[MAX_STATUS];

	fc::string title;
	fc::string gold;



	Strings()
	{
		gold = "gil";


	}

	void SerializeXml( XmlWriter* xml )
	{
		xml->BeginNode("Strings");

		SerializeStringArray(xml, "Stats", stats, MAX_STATS);
		SerializeStringArray(xml, "Elements", elements, MAX_ELEMENTS);
		SerializeStringArray(xml, "Status", status, MAX_STATUS);

		xml->SetString("title", title.c_str());
		xml->SetString("gold", gold.c_str());
		xml->EndNode();
	}

	void DeserializeXml( XmlReader* xml )
	{
		if( xml->NextChild("Strings") )
		{
			SerializeStringArray(xml, "Stats", stats, MAX_STATS);
			SerializeStringArray(xml, "Elements", elements, MAX_ELEMENTS);
			SerializeStringArray(xml, "Status", status, MAX_STATUS);
		}

		title = xml->GetString("title");
		gold = xml->GetString("gold");
		xml->SetToParent();
	}

};

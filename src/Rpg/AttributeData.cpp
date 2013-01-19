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


#include <Engine/IO/XmlWriter.h>
#include <Engine/IO/XmlReader.h>
#include "AttributeData.h"


AttributeData::AttributeData( const fc::string& name, const fc::string& scriptName, const fc::string& description ) :
	name(name), 
	script(scriptName),
	description(description)
{
}


void AttributeData::SerializeXml( XmlWriter* xml )
{
	xml->SetString("name", name.c_str());
	xml->SetString("script", script.c_str());
	xml->SetString("description", description.c_str());

	attributes.SerializeXml(xml);
	attribute_flags.SerializeXml(xml);
}


void AttributeData::DeserializeXml( XmlReader* xml )
{
	name = xml->GetString("name");
	script = xml->GetString("script");
	description = xml->GetString("description");

	attributes.DeserializeXml(xml);
	attribute_flags.DeserializeXml(xml);
}


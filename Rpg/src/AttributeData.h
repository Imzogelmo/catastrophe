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
#include "Attributes.h"
#include "AttributeFlags.h"


struct RPG_API AttributeData
{
	fc::string		name;
	fc::string		script;
	fc::string		description;
	Attributes		attributes;
	AttributeFlags	attribute_flags;

	AttributeData( const fc::string& name = "", const fc::string& scriptName = "", const fc::string& description = "" );

	void SetName( const fc::string& str ) { name = str; }
	void SetDescription( const fc::string& str ) { description = str; }
	void SetScript( const fc::string& str ) { script = str; }

	void SetAttributes( const Attributes& attrib ) { attributes = attrib; }
	void SetAttributeFlags( const AttributeFlags& flags ) { attribute_flags = flags; }

	const fc::string& GetName() const { return name; }
	const fc::string& GetDescription() const { return name; }
	const fc::string& GetScript() const { return script; }

	Attributes& GetAttributes() { return attributes; }
	AttributeFlags& GetAttributeFlags() { return attribute_flags; }

	NO_INLINE void SerializeXml( XmlWriter* xml );
	NO_INLINE void DeserializeXml( XmlReader* xml );

};

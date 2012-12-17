
#pragma once

#include <fc/string.h>

#include "Common.h"
#include "Attributes.h"
#include "AttributeFlags.h"


struct AttributeData
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

	void SerializeXml( XmlWriter* xml );
	void DeserializeXml( XmlReader* xml );

};

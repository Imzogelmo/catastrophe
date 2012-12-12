
#pragma once

#include <Catastrophe/Graphics/Sprite.h>

#include "Common.h"
#include "Attributes.h"
#include "AttributeFlags.h"


struct ItemData
{
	fc::string		name;
	fc::string		description;
	Attributes		attributes;
	AttributeFlags	attribute_flags;
	Flags32			usage_flags;

	//int sprite_index;
	AnimatedSprite	sprite; //icon?

	ItemData(const fc::string& name = "", const fc::string& description = "") :
		name(name), 
		description(description)
	{
	}

	void SetName( const fc::string& str ) { name = str; }
	void SetDescription( const fc::string& str ) { description = str; }
	void SetAttributes( const Attributes& a ) { attributes = a; }
	void SetAttributeFlags( const AttributeFlags& f ) { attribute_flags = f; }

	const fc::string& GetName() const { return name; }
	const fc::string& GetDescription() const { return name; }
	const Attributes& GetAttributes() const { return attributes; }
	const AttributeFlags& GetAttributeFlags() const { return attribute_flags; }

	void SerializeXml( XmlWriter* xml );
	void DeserializeXml( XmlReader* xml );

};
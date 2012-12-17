

#include <Catastrophe/FileIO.h>
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


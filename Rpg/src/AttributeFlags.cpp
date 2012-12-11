

#include <Catastrophe/FileIO.h>

#include "AttributeFlags.h"


void AttributeFlags::SerializeXml( XmlWriter* xml )
{
	xml->BeginNode("Flags");
	xml->SetInt("attrib", attribute_flags.bits);
	xml->SetInt("elements", elem_flags.bits);
	xml->SetInt("status", status_flags.bits);
	xml->SetInt("family", family_flags.bits);
	xml->SetInt("class", class_flags.bits);
	xml->SetInt("misc", misc_flags.bits);
	xml->EndNode();
}


void AttributeFlags::DeserializeXml( XmlReader* xml )
{
	xml->FirstChild("Flags");
	attribute_flags.bits = xml->GetInt("attrib");
	elem_flags.bits = xml->GetInt("elements");
	status_flags.bits = xml->GetInt("status");
	family_flags.bits = xml->GetInt("family");
	class_flags.bits = xml->GetInt("class");
	misc_flags.bits = xml->GetInt("misc");
	xml->SetToParent();
}



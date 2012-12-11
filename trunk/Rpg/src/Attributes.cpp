
#include <Catastrophe/FileIO.h>

#include "Attributes.h"



void Attributes::ApplyPercentageModifier(const Attributes& modifier)
{
	attributes.ApplyPercentageModifier(modifier.attributes);
	elements.ApplyPercentageModifier(modifier.elements);
	status.ApplyPercentageModifier(modifier.status);
}


void Attributes::ApplyMin(const Attributes& value)
{
	attributes.ApplyMin(value.attributes);
	elements.ApplyMin(value.elements);
	status.ApplyMin(value.status);
}


void Attributes::ApplyMax(const Attributes& value)
{
	attributes.ApplyMax(value.attributes);
	elements.ApplyMax(value.elements);
	status.ApplyMax(value.status);
}


void Attributes::Clamp(const Attributes& min, const Attributes& max)
{
	attributes.Clamp(min.attributes, max.attributes);
	elements.Clamp(min.elements, max.elements);
	status.Clamp(min.status, max.status);
}


void Attributes::SerializeXml( XmlWriter* xml )
{
	xml->BeginNode("Attributes");
	xml->Write(&attributes[0], MAX_ATTRIBUTES);
	xml->EndNode();

	xml->BeginNode("Elements");
	xml->Write(&elements[0], MAX_ELEMENTS);
	xml->EndNode();

	xml->BeginNode("Status");
	xml->Write(&status[0], MAX_STATUS);
	xml->EndNode();
}


void Attributes::DeserializeXml( XmlReader* xml )
{
	xml->FirstChild("Attributes");
	xml->ReadBlock(&attributes[0], MAX_ATTRIBUTES);
	xml->SetToParent();

	xml->FirstChild("Elements");
	xml->ReadBlock(&elements[0], MAX_ELEMENTS);
	xml->SetToParent();

	xml->FirstChild("Status");
	xml->ReadBlock(&status[0], MAX_STATUS);
	xml->SetToParent();
}


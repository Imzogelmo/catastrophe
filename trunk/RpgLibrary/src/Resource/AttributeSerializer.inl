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

#include <Catastrophe/IO/XmlWriter.h>
#include <Catastrophe/IO/XmlReader.h>
#include "AttributeSerializer.h"

// static initialization
int AttributeAccessorObjectTypeBase::m_typeIdGenerator = 0;
ObjectAttributeSerializerFactory ObjectAttributeSerializerFactory::m_instance = ObjectAttributeSerializerFactory();



// AttributeAccessorObjectTypeBase

void AttributeAccessorObjectTypeBase::RegisterAttributeAccessor( const AttributeAccessorInfo& attrInfo )
{
	m_attributes.push_back(attrInfo);
}


void AttributeAccessorObjectTypeBase::SerializeObjectAttributesXml( void* obj, XmlWriter* xml )
{
	for( vec_type::const_iterator it = m_attributes.begin(); it != m_attributes.end(); ++it )
	{
		int retVal = OnWriteAttributeInfoXml(obj, xml, *it);
	}
}


void AttributeAccessorObjectTypeBase::DeserializeObjectAttributesXml( void* obj, XmlReader* xml )
{
	for( vec_type::const_iterator it = m_attributes.begin(); it != m_attributes.end(); ++it )
	{
		int retVal = OnReadAttributeInfoXml(obj, xml, *it);

		// if we have an invalid node error, skip ahead.
		if( retVal == VAR_TYPE_PUSH_NODE )
		{
			for( ; it != m_attributes.end(); ++it )
				if( it->type == VAR_TYPE_POP_NODE )
					break;
		}
	}
}


int AttributeAccessorObjectTypeBase::OnReadAttributeInfoXml( void* obj, XmlReader* xml, const AttributeAccessorInfo& attr )
{
	// get address of variable
	void* dest = (void*)(((ubyte*)obj) + attr.offset);

	switch( attr.type )
	{
		case VAR_TYPE_BOOL:
		{
			*((bool*)dest) = xml->GetBool(attr.name);
			break;
		}
		case VAR_TYPE_BYTE:
		{
			*((byte*)dest) = xml->GetByte(attr.name);
			break;
		}
		case VAR_TYPE_SHORT:
		{
			*((short*)dest) = xml->GetShort(attr.name);
			break;
		}
		case VAR_TYPE_INT:
		{
			*((int*)dest) = xml->GetInt(attr.name);
			break;
		}
		case VAR_TYPE_INT64:
		{
			*((int64*)dest) = (int)xml->GetInt(attr.name);
			break;
		}
		case VAR_TYPE_FLOAT:
		{
			*((float*)dest) = xml->GetFloat(attr.name);
			break;
		}
		case VAR_TYPE_FLOAT64:
		{
			*((double*)dest) = (float)xml->GetFloat(attr.name);
			break;
		}
		case VAR_TYPE_VECTOR2:
		case VAR_TYPE_VECTOR3:
		case VAR_TYPE_VECTOR4:
		case VAR_TYPE_QUATERNION:
		case VAR_TYPE_MATRIX:
		case VAR_TYPE_COLOR:
		case VAR_TYPE_COLORF:
		case VAR_TYPE_RECT:
		case VAR_TYPE_RECTF:
		{
			ASSERT(false); //not implemented
			break;
		}
		case VAR_TYPE_STRING:
		{
			*((fc::string*)dest) = xml->GetString(attr.name);
			break;
		}
		case VAR_TYPE_OBJECT_ARRAY:
		{
			AttributeAccessorTemplateTypeInfo* typeInfo = (AttributeAccessorTemplateTypeInfo*)&attr.typeInfo;
			typeInfo->OnReadAttributeArrayXml(dest, attr.name, xml);
			break;
		}
		case VAR_TYPE_OBJECT_ARRAY_SET_SIZE:
		{
			AttributeAccessorTemplateTypeInfo* typeInfo = (AttributeAccessorTemplateTypeInfo*)&attr.typeInfo;
			typeInfo->OnReadAttributeArraySizeXml(dest, attr.name, xml);
			break;
		}
		case VAR_TYPE_PUSH_NODE:
		{
			if( !xml->NextChild(attr.name) )
				return VAR_TYPE_PUSH_NODE;
			break;
		}
		case VAR_TYPE_POP_NODE:
		{
			xml->SetToParent();
			break;
		}

		default:
		{
			LogDebug("Unknown VAR_TYPE, attribute cannot be read.");
			break;
		}
	}

	return 0;
}


int AttributeAccessorObjectTypeBase::OnWriteAttributeInfoXml( void* obj, XmlWriter* xml, const AttributeAccessorInfo& attr )
{
	// address of variable
	void* dest = (void*)(((ubyte*)obj) + attr.offset);

	switch( attr.type )
	{
		case VAR_TYPE_BOOL:
		{
			xml->SetBool(attr.name, *((const bool*)dest));
			break;
		}
		case VAR_TYPE_BYTE:
		{
			xml->SetByte(attr.name, *((const byte*)dest));
			break;
		}
		case VAR_TYPE_SHORT:
		{
			xml->SetShort(attr.name, *((const short*)dest));
			break;
		}
		case VAR_TYPE_INT:
		{
			xml->SetInt(attr.name, *((const int*)dest));
			break;
		}
		case VAR_TYPE_INT64:
		{
			xml->SetInt(attr.name, (int)*((const int64*)dest));
			break;
		}
		case VAR_TYPE_FLOAT:
		{
			xml->SetFloat(attr.name, *((const float*)dest));
			break;
		}
		case VAR_TYPE_FLOAT64:
		{
			xml->SetFloat(attr.name, (float)*((const double*)dest));
			break;
		}
		case VAR_TYPE_VECTOR2:
		case VAR_TYPE_VECTOR3:
		case VAR_TYPE_VECTOR4:
		case VAR_TYPE_QUATERNION:
		case VAR_TYPE_MATRIX:
		case VAR_TYPE_COLOR:
		case VAR_TYPE_COLORF:
		case VAR_TYPE_RECT:
		case VAR_TYPE_RECTF:
		{
			ASSERT(false); //not implemented
			break;
		}
		case VAR_TYPE_STRING:
		{
			xml->SetString(attr.name, *((const fc::string*)dest));
			break;
		}
		case VAR_TYPE_OBJECT_ARRAY:
		{
			AttributeAccessorTemplateTypeInfo* typeInfo = (AttributeAccessorTemplateTypeInfo*)&attr.typeInfo;
			typeInfo->OnWriteAttributeArrayXml(dest, attr.name, xml);
			break;
		}
		case VAR_TYPE_OBJECT_ARRAY_SET_SIZE:
		{
			AttributeAccessorTemplateTypeInfo* typeInfo = (AttributeAccessorTemplateTypeInfo*)&attr.typeInfo;
			typeInfo->OnWriteAttributeArraySizeXml(dest, attr.name, xml);
			break;
		}
		case VAR_TYPE_PUSH_NODE:
		{
			xml->BeginNode(attr.name);
			break;
		}
		case VAR_TYPE_POP_NODE:
		{
			xml->EndNode();
			break;
		}

		default:
		{
			LogDebug("Unknown VAR_TYPE, attribute cannot be set.");
			break;
		}
	}

	return 0;
}

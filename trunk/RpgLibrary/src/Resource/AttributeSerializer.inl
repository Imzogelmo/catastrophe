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

#include <Catastrophe/IO/AttributeWriter.h>
#include <Catastrophe/IO/AttributeReader.h>
#include "AttributeSerializer.h"

// static initialization
int AttributeAccessorObjectTypeBase::m_typeIdGenerator = 0;
ObjectAttributeSerializerFactory ObjectAttributeSerializerFactory::m_instance = ObjectAttributeSerializerFactory();



// AttributeAccessorObjectTypeBase

void AttributeAccessorObjectTypeBase::RegisterAttributeAccessor( const AttributeAccessorInfo& attrInfo )
{
	m_attributes.push_back(attrInfo);
}


void AttributeAccessorObjectTypeBase::SerializeObjectAttributesXml( void* obj, AttributeWriter* f )
{
	for( vec_type::const_iterator it = m_attributes.begin(); it != m_attributes.end(); ++it )
	{
		int retVal = OnWriteAttributeInfoXml(obj, f, *it);
	}
}


void AttributeAccessorObjectTypeBase::DeserializeObjectAttributesXml( void* obj, AttributeReader* f )
{
	for( vec_type::const_iterator it = m_attributes.begin(); it != m_attributes.end(); ++it )
	{
		int retVal = OnReadAttributeInfoXml(obj, f, *it);

		// if we have an invalid node error, skip ahead.
		if( retVal == VAR_TYPE_PUSH_NODE )
		{
			for( ; it != m_attributes.end(); ++it )
				if( it->type == VAR_TYPE_POP_NODE )
					break;
		}
	}
}


int AttributeAccessorObjectTypeBase::OnReadAttributeInfoXml( void* obj, AttributeReader* f, const AttributeAccessorInfo& attr )
{
	// get address of variable
	void* dest = (void*)(((ubyte*)obj) + attr.offset);

	switch( attr.type )
	{
		case VAR_TYPE_BOOL:
		{
			*((bool*)dest) = f->GetBool(attr.name);
			break;
		}
		case VAR_TYPE_BYTE:
		{
			*((byte*)dest) = f->GetByte(attr.name);
			break;
		}
		case VAR_TYPE_SHORT:
		{
			*((short*)dest) = f->GetShort(attr.name);
			break;
		}
		case VAR_TYPE_INT:
		{
			*((int*)dest) = f->GetInt(attr.name);
			break;
		}
		case VAR_TYPE_INT64:
		{
			*((int64*)dest) = (int)f->GetInt(attr.name);
			break;
		}
		case VAR_TYPE_FLOAT:
		{
			*((float*)dest) = f->GetFloat(attr.name);
			break;
		}
		case VAR_TYPE_FLOAT64:
		{
			*((double*)dest) = (float)f->GetFloat(attr.name);
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
			*((fc::string*)dest) = f->GetString(attr.name);
			break;
		}
		case VAR_TYPE_OBJECT:
		{
			// not implemented
			break;
		}
		case VAR_TYPE_BYTE_ARRAY:
		{
			//if( f->FirstChild(attr.name) ) {
				f->ReadByteArrayElement(attr.name, (byte*)dest, *((size_t*)&attr.typeInfo));
			//	f->SetToParent();
			//}
			break;
		}
		case VAR_TYPE_SHORT_ARRAY:
		{
			f->ReadShortArrayElement(attr.name, (short*)dest, *((size_t*)&attr.typeInfo));
			break;
		}
		case VAR_TYPE_INT_ARRAY:
		{
			f->ReadIntArrayElement(attr.name, (int*)dest, *((size_t*)&attr.typeInfo));
			break;
		}
		case VAR_TYPE_FLOAT_ARRAY:
		{
			f->ReadFloatArrayElement(attr.name, (float*)dest, *((size_t*)&attr.typeInfo));
			break;
		}
		case VAR_TYPE_OBJECT_ARRAY:
		{
			AttributeAccessorTemplateTypeInfo* typeInfo = (AttributeAccessorTemplateTypeInfo*)&attr.typeInfo;
			typeInfo->OnReadAttributeArrayXml(dest, attr.name, f);
			break;
		}
		case VAR_TYPE_OBJECT_ARRAY_SET_SIZE:
		{
			AttributeAccessorTemplateTypeInfo* typeInfo = (AttributeAccessorTemplateTypeInfo*)&attr.typeInfo;
			typeInfo->OnReadAttributeArraySizeXml(dest, attr.name, f);
			break;
		}
		case VAR_TYPE_PUSH_NODE:
		{
			if( !f->NextChild(attr.name) )
				return VAR_TYPE_PUSH_NODE;
			break;
		}
		case VAR_TYPE_POP_NODE:
		{
			f->SetToParent();
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


int AttributeAccessorObjectTypeBase::OnWriteAttributeInfoXml( void* obj, AttributeWriter* f, const AttributeAccessorInfo& attr )
{
	// address of variable
	void* dest = (void*)(((ubyte*)obj) + attr.offset);

	switch( attr.type )
	{
		case VAR_TYPE_BOOL:
		{
			f->SetBool(attr.name, *((const bool*)dest));
			break;
		}
		case VAR_TYPE_BYTE:
		{
			f->SetByte(attr.name, *((const byte*)dest));
			break;
		}
		case VAR_TYPE_SHORT:
		{
			f->SetShort(attr.name, *((const short*)dest));
			break;
		}
		case VAR_TYPE_INT:
		{
			f->SetInt(attr.name, *((const int*)dest));
			break;
		}
		case VAR_TYPE_INT64:
		{
			f->SetInt(attr.name, (int)*((const int64*)dest));
			break;
		}
		case VAR_TYPE_FLOAT:
		{
			f->SetFloat(attr.name, *((const float*)dest));
			break;
		}
		case VAR_TYPE_FLOAT64:
		{
			f->SetFloat(attr.name, (float)*((const double*)dest));
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
			f->SetString(attr.name, *((const fc::string*)dest));
			break;
		}
		case VAR_TYPE_OBJECT:
		{
			// not implemented
			break;
		}
		case VAR_TYPE_BYTE_ARRAY:
		{
			//f->BeginNode(attr.name);
			f->WriteByteArrayElement(attr.name, (byte*)dest, *((size_t*)&attr.typeInfo));
			//f->EndNode();
			break;
		}
		case VAR_TYPE_SHORT_ARRAY:
		{
			f->WriteShortArrayElement(attr.name, (short*)dest, *((size_t*)&attr.typeInfo));
			break;
		}
		case VAR_TYPE_INT_ARRAY:
		{
			f->WriteIntArrayElement(attr.name, (int*)dest, *((size_t*)&attr.typeInfo));
			break;
		}
		case VAR_TYPE_FLOAT_ARRAY:
		{
			f->WriteFloatArrayElement(attr.name, (float*)dest, *((size_t*)&attr.typeInfo));
			break;
		}
		case VAR_TYPE_OBJECT_ARRAY:
		{
			AttributeAccessorTemplateTypeInfo* typeInfo = (AttributeAccessorTemplateTypeInfo*)&attr.typeInfo;
			typeInfo->OnWriteAttributeArrayXml(dest, attr.name, f);
			break;
		}
		case VAR_TYPE_OBJECT_ARRAY_SET_SIZE:
		{
			AttributeAccessorTemplateTypeInfo* typeInfo = (AttributeAccessorTemplateTypeInfo*)&attr.typeInfo;
			typeInfo->OnWriteAttributeArraySizeXml(dest, attr.name, f);
			break;
		}
		case VAR_TYPE_PUSH_NODE:
		{
			f->BeginNode(attr.name);
			break;
		}
		case VAR_TYPE_POP_NODE:
		{
			f->EndNode();
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
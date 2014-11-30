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
#include <fc/vector.h>
#include <fc/fixed_vector.h>

#include "RpgCommon.h"


enum AttributeAccessorVariableType
{
	VAR_TYPE_NONE,
	VAR_TYPE_BOOL,
	VAR_TYPE_BYTE,
	VAR_TYPE_SHORT,
	VAR_TYPE_INT,
	VAR_TYPE_INT64,
	VAR_TYPE_FLOAT,
	VAR_TYPE_FLOAT64,
	VAR_TYPE_VECTOR2,
	VAR_TYPE_VECTOR3,
	VAR_TYPE_VECTOR4,
	VAR_TYPE_QUATERNION,
	VAR_TYPE_MATRIX,
	VAR_TYPE_COLOR,
	VAR_TYPE_COLORF,
	VAR_TYPE_RECT,
	VAR_TYPE_RECTF,
	VAR_TYPE_STRING,
	VAR_TYPE_OBJECT,
	VAR_TYPE_BYTE_ARRAY,
	VAR_TYPE_SHORT_ARRAY,
	VAR_TYPE_INT_ARRAY,
	VAR_TYPE_FLOAT_ARRAY,
	VAR_TYPE_OBJECT_ARRAY,
	VAR_TYPE_OBJECT_ARRAY_SET_SIZE,
	VAR_TYPE_PUSH_NODE,
	VAR_TYPE_POP_NODE,
	VAR_TYPE_MAX //always last
};



template <class T>
void SerializeObjectArrayXml( T* obj, const char* node, AttributeWriter* f )
{
	u32 n = obj->size();
	for( u32 i(0); i < n; ++i )
	{
		f->BeginNode(node);
		(*obj)[i].Serialize(xml);
		f->EndNode();
	}
}


template <class T>
void DeserializeObjectArrayXml( T* obj, const char* node, AttributeReader* f )
{
	bool nested = false;
	for( u32 i(0); i < obj->size(); ++i )
	{
		if( f->NextChild(node) )
		{
			(*obj)[i].Deserialize(xml);
			nested = true;
		}
		else
		{
			break;
		}
	}

	if( nested )
		f->SetToParent();
}



template <class T>
void SerializeObjectArraySizeXml( T* obj, const char* node, AttributeWriter* f )
{
	f->SetUInt(node, obj->size());
}


template <class T>
void DeserializeObjectArraySizeXml( T* obj, const char* node, AttributeReader* f )
{
	u32 n = f->GetUInt(node);
	obj->resize(n);
}


struct AttributeAccessorTemplateTypeInfo
{
	virtual void OnReadAttributeArrayXml( void* obj, const char* node, AttributeReader* f ) const {}
	virtual void OnWriteAttributeArrayXml( void* obj, const char* node, AttributeWriter* f ) const {}
	virtual void OnReadAttributeArraySizeXml( void* obj, const char* node, AttributeReader* f ) const {}
	virtual void OnWriteAttributeArraySizeXml( void* obj, const char* node, AttributeWriter* f ) const {}
};


template <class T>
struct AttributeAccessorTemplateTypeInfoImpl : public AttributeAccessorTemplateTypeInfo
{
	virtual void OnReadAttributeArrayXml( void* obj, const char* node, AttributeReader* f ) const {
		::DeserializeObjectArrayXml<T>((T*)obj, node, xml);
	}
	virtual void OnWriteAttributeArrayXml( void* obj, const char* node, AttributeWriter* f ) const {
		::SerializeObjectArrayXml<T>((T*)obj, node, xml);
	}
	virtual void OnReadAttributeArraySizeXml( void* obj, const char* node, AttributeReader* f ) const {
		::DeserializeObjectArraySizeXml<T>((T*)obj, node, xml);
	}
	virtual void OnWriteAttributeArraySizeXml( void* obj, const char* node, AttributeWriter* f ) const {
		::SerializeObjectArraySizeXml<T>((T*)obj, node, xml);
	}
};


struct AttributeAccessorInfo
{
public:
	typedef fc::aligned_buffer<sizeof(AttributeAccessorTemplateTypeInfo), FC_ALIGNOF(AttributeAccessorTemplateTypeInfo)> buffer_type;

	buffer_type							typeInfo;
	AttributeAccessorVariableType		type;
	const char*							name;
	int									offset;

	AttributeAccessorInfo() : typeInfo(), type(VAR_TYPE_NONE), name(0), offset(0) {}
	AttributeAccessorInfo( AttributeAccessorVariableType type, const char* name, int offset )
		: typeInfo(), type(type), name(name), offset(offset)
	{
	}

	AttributeAccessorInfo( AttributeAccessorVariableType type, u32 arraySize, const char* name, int offset )
		: typeInfo(), type(type), name(name), offset(offset)
	{
		// store pod-type array sizes in typeInfo.
		*((u32*)&typeInfo) = arraySize;
	}

	template <class T>
	AttributeAccessorInfo& SetTypeInfo()
	{
		new (typeInfo.data) AttributeAccessorTemplateTypeInfoImpl<T>();
		return *this;
	}

};


class AttributeAccessorObjectTypeBase
{
public:
	typedef fc::vector<AttributeAccessorInfo>	vec_type;

	AttributeAccessorObjectTypeBase( const char* className ) : m_className(className) {}
	virtual ~AttributeAccessorObjectTypeBase()
	{}

	void RegisterAttributeAccessor( const AttributeAccessorInfo& attrInfo );

	NO_INLINE void SerializeObjectAttributesXml( void* obj, AttributeWriter* f );
	NO_INLINE void DeserializeObjectAttributesXml( void* obj, AttributeReader* f );

	int OnReadAttributeInfoXml( void* obj, AttributeReader* f, const AttributeAccessorInfo& attr );
	int OnWriteAttributeInfoXml( void* obj, AttributeWriter* f, const AttributeAccessorInfo& attr );

	template <class T> static void OnReadAttributeArrayXml( T* obj, AttributeReader* f );
	template <class T> static void OnWriteAttributeArrayXml( T* obj, AttributeWriter* f );

protected:
	static int m_typeIdGenerator;

	static int GenerateTypeId()
	{
		int currentVal = m_typeIdGenerator++;
		return currentVal;
	}

	const char*	m_className;
	vec_type	m_attributes;
};


template<class T>
class AttributeAccessorObjectTypeInfo : public AttributeAccessorObjectTypeBase
{
public:
	AttributeAccessorObjectTypeInfo( const char* className )
		: AttributeAccessorObjectTypeBase(className)
	{}

	static int GetTypeId()
	{
		static int typeId = AttributeAccessorObjectTypeBase::GenerateTypeId();
		return typeId;
	}
};


class ObjectAttributeSerializerFactory
{
public:
	enum : u32
	{
		MaxBufferBytes = 512
	};

	typedef fc::fixed_vector<AttributeAccessorObjectTypeBase*, MaxBufferBytes / sizeof(AttributeAccessorObjectTypeBase*)> vec_type;
	typedef fc::aligned_buffer<MaxBufferBytes, FC_ALIGNOF(AttributeAccessorObjectTypeBase*)> buffer_type;

	ObjectAttributeSerializerFactory() :
		m_factories(),
		m_buffer(),
		m_offset(0)
	{
	}

	static ObjectAttributeSerializerFactory* GetInstance()
	{
		return &m_instance;
	}

	template <class T>
	void RegisterAttribute( const AttributeAccessorInfo& attrInfo )
	{
		int registeredTypeId = AttributeAccessorObjectTypeInfo<T>::GetTypeId();

		// assert validation
		ASSERT((u32)registeredTypeId < m_factories.size());
		m_instance.m_factories[registeredTypeId]->RegisterAttributeAccessor(attrInfo);
	}

	template <class T>
	void RegisterFactoryType( const char* className )
	{
		int registeredTypeId = AttributeAccessorObjectTypeInfo<T>::GetTypeId();
		ASSERT((u32)registeredTypeId <= m_factories.size());

		// only register a new factory if typeId is a valid type.
		if( (u32)registeredTypeId == m_factories.size() )
		{
			ASSERT(m_offset <= MaxBufferBytes - sizeof(AttributeAccessorObjectTypeInfo<T>));

			AttributeAccessorObjectTypeInfo<T>* p = new (m_buffer.data + m_offset) AttributeAccessorObjectTypeInfo<T>(className);
			m_offset += sizeof(AttributeAccessorObjectTypeInfo<T>);
			m_factories.push_back(p);
		}
	}

	template <class T>
	void SerializeObjectAttributesXml( T* obj, AttributeWriter* f )
	{
		int registeredTypeId = AttributeAccessorObjectTypeInfo<T>::GetTypeId();

		// verify type has been registered.
		ASSERT((u32)registeredTypeId < m_factories.size());
		m_instance.m_factories[registeredTypeId]->SerializeObjectAttributesXml(obj, xml);
	}

	template <class T>
	void DeserializeObjectAttributesXml( T* obj, AttributeReader* f )
	{
		int registeredTypeId = AttributeAccessorObjectTypeInfo<T>::GetTypeId();

		// verify type has been registered.
		ASSERT((u32)registeredTypeId < m_factories.size());
		m_instance.m_factories[registeredTypeId]->DeserializeObjectAttributesXml(obj, xml);
	}

	void DeleteFactories()
	{
		m_factories.clear();
	}

private:
	// There's zero point in having more than one instance
	// of a factory that depends on compile-time constants
	// and static template typeid generation.
	static ObjectAttributeSerializerFactory m_instance;

	vec_type		m_factories;
	buffer_type		m_buffer;
	u32			m_offset;

};


#define REGISTER_ATTRIBUTE_FACTORY_TYPE(class_) \
	ObjectAttributeSerializerFactory::GetInstance()->RegisterFactoryType<class_>(#class_)

#define PUSH_ATTRIBUTE_NODE(class_, nodeName) \
	ObjectAttributeSerializerFactory::GetInstance()->RegisterAttribute<class_> \
		(AttributeAccessorInfo(VAR_TYPE_PUSH_NODE, nodeName, 0))

#define POP_ATTRIBUTE_NODE(class_) \
	ObjectAttributeSerializerFactory::GetInstance()->RegisterAttribute<class_> \
		(AttributeAccessorInfo(VAR_TYPE_POP_NODE, "", 0))

#define REGISTER_ATTRIBUTE(class_, type, name, var) \
	ObjectAttributeSerializerFactory::GetInstance()->RegisterAttribute<class_> \
		(AttributeAccessorInfo(type, name, offsetof(class_, var)))

#define REGISTER_ATTRIBUTE_ARRAY(class_, type, arraySize, name, var) \
	ObjectAttributeSerializerFactory::GetInstance()->RegisterAttribute<class_> \
		(AttributeAccessorInfo(type, arraySize, name, offsetof(class_, var)))

// not implemented
#define REGISTER_ATTRIBUTE_OBJECT(class_, T_, obj) \
	ObjectAttributeSerializerFactory::GetInstance()->RegisterAttribute<class_> \
		(AttributeAccessorInfo(VAR_TYPE_OBJECT, 0, offsetof(class_, obj)).SetTypeInfo<T_>());

#define REGISTER_ATTRIBUTE_OBJECT_ARRAY(class_, name, resizeName, T_, array_) \
	ObjectAttributeSerializerFactory::GetInstance()->RegisterAttribute<class_> \
		(AttributeAccessorInfo(VAR_TYPE_OBJECT_ARRAY_SET_SIZE, resizeName, offsetof(class_, array_)).SetTypeInfo<T_>()); \
	ObjectAttributeSerializerFactory::GetInstance()->RegisterAttribute<class_> \
		(AttributeAccessorInfo(VAR_TYPE_OBJECT_ARRAY, name, offsetof(class_, array_)).SetTypeInfo<T_>())


// xml serialization
#define SERIALIZE_OBJECT_ATTRIBUTES_XML(obj, xml) \
	ObjectAttributeSerializerFactory::GetInstance()->SerializeObjectAttributesXml(obj, xml)

#define DESERIALIZE_OBJECT_ATTRIBUTES_XML(obj, xml) \
	ObjectAttributeSerializerFactory::GetInstance()->DeserializeObjectAttributesXml(obj, xml)


// binary serialization
#define SERIALIZE_OBJECT_ATTRIBUTES(obj, f)
#define DESERIALIZE_OBJECT_ATTRIBUTES(obj, f)


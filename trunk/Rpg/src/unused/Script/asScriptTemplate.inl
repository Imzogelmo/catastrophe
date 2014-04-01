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

#include <angelscript.h>

#include "asScriptTemplate.h"



ScriptTemplateClass::ScriptTemplateClass( asIObjectType *objectType )
{
	ASSERT(objectType != 0);

	m_refCount		= 1;
	m_gcFlag		= false;
	m_objType		= objectType;
	m_typeId		= m_objType->GetTypeId();
	m_subtypeId		= m_objType->GetSubTypeId();
	m_isHandle		= m_subtypeId & asTYPEID_OBJHANDLE ? true : false;
	m_isMaskObject	= m_subtypeId & asTYPEID_MASK_OBJECT ? true : false;	
	m_objType->AddRef();

	//save the primitive type for fast lookup
	if( m_subtypeId == asTYPEID_BOOL || m_subtypeId == asTYPEID_INT8 || m_subtypeId == asTYPEID_UINT8 ) m_valueType = 1;
	else if( m_subtypeId == asTYPEID_INT16 || m_subtypeId == asTYPEID_UINT16 ) m_valueType = 2;
	else if( m_subtypeId == asTYPEID_INT32 || m_subtypeId == asTYPEID_UINT32 || m_subtypeId == asTYPEID_FLOAT ) m_valueType = 3;
	else if( m_subtypeId == asTYPEID_INT64 || m_subtypeId == asTYPEID_UINT64 || m_subtypeId == asTYPEID_DOUBLE ) m_valueType = 4;
	else m_valueType = 0;

	if( m_isMaskObject )
	{
		m_needsStorage = m_isHandle;
		m_elementSize = sizeof(asPWORD);
	}
	else
	{
		m_needsStorage = true;
		m_elementSize = m_objType->GetEngine()->GetSizeOfPrimitiveType( m_subtypeId );
	}

	// Notify the GC of the successful creation
	if( m_objType->GetFlags() & asOBJ_GC )
		m_objType->GetEngine()->NotifyGarbageCollectorOfNewObject( this, objectType );
}


ScriptTemplateClass::~ScriptTemplateClass()
{
	if( m_objType )
		m_objType->Release();
}


ScriptTemplateClass &ScriptTemplateClass::operator =( const ScriptTemplateClass &other )
{
	// Only perform the copy if the array types are the same
	if( &other != this && other.GetArrayObjectType() == GetArrayObjectType() )
	{

	}

	return *this;
}


void ScriptTemplateClass::SetValue( storage_type *ptr, void *value )
{
	if( (m_subtypeId & ~asTYPEID_MASK_SEQNBR) && !(m_isHandle) )
	{
	//if( m_isMaskObject )
		//valStruct.valueObj = engine->CreateScriptObjectCopy(value, typeId);
		m_objType->GetEngine()->AssignScriptObject( ptr->ptr, value, m_objType->GetSubType() );
	}

	else if( m_isHandle )
	{
		*(void**)ptr = *(void**)value;
		m_objType->GetEngine()->AddRefScriptObject(*(void**)value, m_objType->GetSubType());

		//void* tmp = *(void**)ptr;
		//if( *(void**)ptr )
		//	objType->GetEngine()->ReleaseScriptObject(*(void**)ptr, m_subtypeId);
	}

	else
	{
		switch( m_valueType )
		{
			case 0:
				//throw("Unknown type");
				break;
			case 1: 
				*(char*)ptr = *(char*)value;
				break;
			case 2: 
				*(short*)ptr = *(short*)value;
				break;
			case 3: 
				*(int*)ptr = *(int*)value;
				break;
			case 4: // 64 bit depricated
				*(double*)ptr = *(double*)value;
				break;
		}
	}

}


void ScriptTemplateClass::ConstructObject( storage_type *ptr )
{
	if( m_isHandle )
		ptr->ptr = 0;

	else if( m_isMaskObject )
	{
		ptr->ptr = m_objType->GetEngine()->CreateScriptObject(m_objType->GetSubType());
		//ptr->ptr = m_objType->GetEngine()->CreateScriptObjectCopy(value, typeId);
	}
}


void ScriptTemplateClass::DestructObject( storage_type *ptr )
{
	if( m_isHandle )
		//m_objType->GetEngine()->ReleaseScriptObject( *(void**)ptr->ptr, m_subtypeId );
		m_objType->GetEngine()->ReleaseScriptObject( ptr->ptr, m_objType->GetSubType() );

	else if( m_isMaskObject ) //the same?
	{
		m_objType->GetEngine()->ReleaseScriptObject( ptr->ptr, m_objType->GetSubType() );
	}
}


int ScriptTemplateClass::GetArrayTypeId() const
{
	return m_objType->GetTypeId();
}


int ScriptTemplateClass::GetElementTypeId() const
{
	return m_objType->GetSubTypeId();
}


// This optional callback is called when the template type is first used by the compiler.
// It allows the application to validate if the template can be instanciated for the requested 
// subtype at compile time, instead of at runtime. The output argument dontGarbageCollect
// allow the callback to tell the engine if the template instance type shouldn't be garbage collected, 
// i.e. no asOBJ_GC flag. 
bool ScriptTemplateClass::TemplateContainerCallback( asIObjectType *ot, bool &dontGarbageCollect )
{
	// Make sure the subtype can be instanciated with a default factory/constructor, 
	// otherwise we won't be able to instanciate the elements. 
	int typeId = ot->GetSubTypeId();
	if( typeId == asTYPEID_VOID )
		return false;
	if( (typeId & asTYPEID_MASK_OBJECT) && !(typeId & asTYPEID_OBJHANDLE) )
	{
		asIObjectType *subtype = ot->GetEngine()->GetObjectTypeById(typeId);
		asDWORD flags = subtype->GetFlags();
		if( (flags & asOBJ_VALUE) && !(flags & asOBJ_POD) )
		{
			// Verify that there is a default constructor
			bool found = false;
			for( asUINT n = 0; n < subtype->GetBehaviourCount(); n++ )
			{
				asEBehaviours beh;
				asIScriptFunction *func = subtype->GetBehaviourByIndex(n, &beh);
				if( beh != asBEHAVE_CONSTRUCT ) continue;

				if( func->GetParamCount() == 0 )
				{
					// Found the default constructor
					found = true;
					break;
				}
			}

			if( !found )
			{
				// There is no default constructor
				return false;
			}
		}
		else if( (flags & asOBJ_REF) )
		{
			// Verify that there is a default factory
			bool found = false;
			for( asUINT n = 0; n < subtype->GetFactoryCount(); n++ )
			{
				asIScriptFunction *func = subtype->GetFactoryByIndex(n);
				if( func->GetParamCount() == 0 )
				{
					// Found the default factory
					found = true;
					break;
				}
			}	

			if( !found )
			{
				// No default factory
				return false;
			}
		}

		// If the object type is not garbage collected then the array also doesn't need to be
		if( !(flags & asOBJ_GC) )
			dontGarbageCollect = true;
	}
	else if( !(typeId & asTYPEID_OBJHANDLE) )
	{
		// Arrays with primitives cannot form circular references, 
		// thus there is no need to garbage collect them
		dontGarbageCollect = true;
	}

	// The type is ok
	return true;
}

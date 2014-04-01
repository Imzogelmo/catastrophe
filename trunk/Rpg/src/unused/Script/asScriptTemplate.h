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

#include "Common.h"


class ScriptTemplateClass
{
public:
	struct InternalStorageValueType32
	{
		InternalStorageValueType32( int val = 0 ) : value(val) {}
		union
		{
			int		value;
			float	real;
			void*	ptr;
		};
	};

	typedef InternalStorageValueType32 storage_type;

	ScriptTemplateClass( asIObjectType *objectType );
	virtual ~ScriptTemplateClass();

	ScriptTemplateClass &operator =( const ScriptTemplateClass& );

	void*			AquirePtr();
	void			ReleasePtr( void *ptr );

	void*			GetReturnObjectPtr( storage_type *ptr );
	void			ConstructObject( storage_type *ptr );
	void			DestructObject( storage_type *ptr );
	void			SetValue( storage_type *ptr, void *value );

	// GC methods
	int				GetRefCount();
	void			SetFlag();
	bool			GetFlag();
	virtual void	EnumReferences( asIScriptEngine *engine ) = 0;
	virtual void	ReleaseAllHandles( asIScriptEngine *engine ) = 0;

	void			AddRef() const;
	void			Release() const;

	asIObjectType*	GetArrayObjectType() const;
	int				GetArrayTypeId() const;
	int				GetElementTypeId() const;

	static bool		TemplateContainerCallback( asIObjectType *ot, bool &dontGarbageCollect );
protected:
	int				m_valueType;
	int				m_typeId;
	int				m_subtypeId;
	int				m_elementSize;
	asIObjectType*	m_objType;
	mutable int		m_refCount;
	mutable bool	m_gcFlag;
	bool			m_isHandle;
	bool			m_isMaskObject;
	bool			m_needsStorage;

};


inline void* ScriptTemplateClass::GetReturnObjectPtr( storage_type* ptr )
{
	//
	//
	//
	//
	//

	if( m_isMaskObject )
		return (void*)ptr->ptr;

	return (void*)ptr;
}


inline asIObjectType *ScriptTemplateClass::GetArrayObjectType() const
{
	return m_objType;
}


inline void ScriptTemplateClass::AddRef() const
{
	// Clear the GC flag then increase the counter
	m_gcFlag = false;
	m_refCount++;
}


inline void ScriptTemplateClass::Release() const
{
	// Now do the actual releasing (clearing the flag set by GC)
	m_gcFlag = false;
	if( --m_refCount == 0 )
	{
		delete this;
	}
}


inline int ScriptTemplateClass::GetRefCount()
{
	return m_refCount;
}


inline void ScriptTemplateClass::SetFlag()
{
	m_gcFlag = true;
}


inline bool ScriptTemplateClass::GetFlag()
{
	return m_gcFlag;
}


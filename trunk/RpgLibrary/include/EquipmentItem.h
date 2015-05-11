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

#include "Catastrophe/Core/Containers/String.h"

#include "RpgCommon.h"
#include "Item.h"
#include "Attributes.h"



struct RPG_API EquipmentItem : public Item
{
	EquipmentItem();

	Attributes attributes;

	virtual bool HasAttributes() const { return true; }
	virtual Attributes& GetAttributes() const { return const_cast<Attributes&>(attributes); }

	virtual void Serialize( AttributeWriter* f );
	virtual void Deserialize( AttributeReader* f );

};



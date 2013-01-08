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

#include "Common.h"
#include "DataList.h"


struct RPG_API Shop
{
	typedef fc::vector<size_t>	vec_type;

	vec_type		items;
	fc::string		name;
	fc::string		greeting;
	fc::string		transaction;
	fc::string		buy;
	fc::string		sell;

	void SerializeXml( XmlWriter* xml );
	void DeserializeXml( XmlReader* xml );

};



class RPG_API ShopList : public DataList<Shop>
{
public:
	typedef DataList<Shop>	base_type;

	ShopList() : base_type()
	{}

	Shop& GetShop( size_t index ) { return base_type::operator [](index);  }
	const Shop& GetShop( size_t index ) const { return base_type::operator [](index);  }

	NO_INLINE bool SerializeXml( const fc::string& filename );
	NO_INLINE bool DeserializeXml( const fc::string& filename );

};


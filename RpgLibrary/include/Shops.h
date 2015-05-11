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
#include "Catastrophe/Core/Containers/Vector.h"

#include "RpgCommon.h"


struct RPG_API ShopItem
{
	enum ShopItemProperties
	{
		DefaultPrice = -1
	};

	int item_id;
	int price;

	ShopItem( int itemId = 0, int price = DefaultPrice )
		: item_id(itemId), price(price)
	{}

	void Serialize( AttributeWriter* f );
	void Deserialize( AttributeReader* f );

};


struct RPG_API Shop
{
	typedef Vector<ShopItem>	vec_type;

	vec_type		items;
	String		name;
	String		greeting;
	String		transaction;
	String		buy;
	String		sell;
	int				markup_percent;
	int				devaluation_percent;

	Shop();

	int GetMarkup() const { return markup_percent; }
	int GetMarkdown() const { return devaluation_percent; }

	void Serialize( AttributeWriter* f );
	void Deserialize( AttributeReader* f );

	// all shop strings are initialized to these in the ctor.
	static String default_greeting_message;
	static String default_transaction_message;
	static String default_buy_message;
	static String default_sell_message;
};


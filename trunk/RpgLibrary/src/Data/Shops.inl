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
#include "Shops.h"



void ShopItem::SerializeXml( AttributeWriter* f )
{
	f->BeginNode("Item");

	f->SetInt("id", item_id);
	f->SetInt("price", price);

	f->EndNode();
}


void ShopItem::DeserializeXml( AttributeReader* f )
{
	item_id = f->GetInt("id");
	price = f->GetInt("price");
}



fc::string Shop::default_greeting_message = "Welcome";
fc::string Shop::default_transaction_message = "Anything else?";
fc::string Shop::default_buy_message = "Which one?";
fc::string Shop::default_sell_message = "Sell what?";

Shop::Shop() :
	items(),
	name(),
	greeting(default_greeting_message),
	transaction(default_transaction_message),
	buy(default_buy_message),
	sell(default_sell_message),
	markup_percent(0),
	devaluation_percent(50)
{
}


void Shop::SerializeXml( AttributeWriter* f )
{
	f->BeginNode("Shop");

	f->SetUInt("num_items", items.size());
	f->SetString("name", name.c_str());
	f->SetString("greeting", greeting.c_str());
	f->SetString("transaction", greeting.c_str());
	f->SetString("buy", greeting.c_str());
	f->SetString("sell", greeting.c_str());
	f->SetInt("markup", markup_percent);
	f->SetInt("devaluation", devaluation_percent);

	for( vec_type::iterator it = items.begin(); it < items.end(); ++it )
	{
		it->SerializeXml(f);
	}

	f->EndNode();
}


void Shop::DeserializeXml( AttributeReader* f )
{
	size_t n = f->GetUInt("num_items");
	name = f->GetString("name");
	greeting = f->GetString("greeting");
	transaction = f->GetString("transaction");
	buy = f->GetString("buy");
	sell = f->GetString("sell");
	markup_percent = f->GetInt("markup");
	devaluation_percent = f->GetInt("devaluation");

	items.reserve(n);
	while( f->NextChild("Item") )
	{
		items.push_back();
		items.back().DeserializeXml(f);
	}

	f->SetToParent();
}


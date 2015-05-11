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


#include <Catastrophe/Core/IO/AttributeWriter.h>
#include <Catastrophe/Core/IO/AttributeReader.h>
#include "Shops.h"



void ShopItem::Serialize( AttributeWriter* f )
{
	f->BeginNode("Item");

	f->SetAttribute("id", item_id);
	f->SetAttribute("price", price);

	f->EndNode();
}


void ShopItem::Deserialize( AttributeReader* f )
{
	f->GetAttribute("id", item_id);
	f->GetAttribute("price", price);
}



String Shop::default_greeting_message = "Welcome";
String Shop::default_transaction_message = "Anything else?";
String Shop::default_buy_message = "Which one?";
String Shop::default_sell_message = "Sell what?";

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


void Shop::Serialize( AttributeWriter* f )
{
	f->BeginNode("Shop");

	f->SetAttribute("num_items", items.Size());
	f->SetString("name", name.CString());
	f->SetString("greeting", greeting.CString());
	f->SetString("transaction", greeting.CString());
	f->SetString("buy", greeting.CString());
	f->SetString("sell", greeting.CString());
	f->SetAttribute("markup", markup_percent);
	f->SetAttribute("devaluation", devaluation_percent);

	for( vec_type::Iterator it = items.begin(); it < items.end(); ++it )
	{
		it->Serialize(f);
	}

	f->EndNode();
}


void Shop::Deserialize( AttributeReader* f )
{
	u32 n = 0;
	f->GetAttribute("num_items", n);

	name = f->GetString("name");
	greeting = f->GetString("greeting");
	transaction = f->GetString("transaction");
	buy = f->GetString("buy");
	sell = f->GetString("sell");

	f->GetAttribute("markup", markup_percent);
	f->GetAttribute("devaluation", devaluation_percent);

	items.Reserve(n);
	while( f->NextChild("Item") )
	{
		items.Add();
		items.Back().Deserialize(f);
	}

	f->SetToParent();
}


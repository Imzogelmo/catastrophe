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


#include <Engine/IO/XmlWriter.h>
#include <Engine/IO/XmlReader.h>
#include "Shops.h"



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                ShopItem
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void ShopItem::SerializeXml( XmlWriter* xml )
{
	xml->BeginNode("Item");

	xml->SetInt("id", id);
	xml->SetInt("price", price);

	xml->EndNode();
}


void ShopItem::DeserializeXml( XmlReader* xml )
{
	id = xml->GetInt("id");
	price = xml->GetInt("price");
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                  Shop
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

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


void Shop::SerializeXml( XmlWriter* xml )
{
	xml->BeginNode("Shop");

	xml->SetUInt("num_items", items.size());
	xml->SetString("name", name.c_str());
	xml->SetString("greeting", greeting.c_str());
	xml->SetString("transaction", greeting.c_str());
	xml->SetString("buy", greeting.c_str());
	xml->SetString("sell", greeting.c_str());
	xml->SetInt("markup", markup_percent);
	xml->SetInt("devaluation", devaluation_percent);

	for( vec_type::iterator it = items.begin(); it < items.end(); ++it )
	{
		it->SerializeXml(xml);
	}

	xml->EndNode();
}


void Shop::DeserializeXml( XmlReader* xml )
{
	size_t n = xml->GetUInt("num_items");
	name = xml->GetString("name");
	greeting = xml->GetString("greeting");
	transaction = xml->GetString("transaction");
	buy = xml->GetString("buy");
	sell = xml->GetString("sell");
	markup_percent = xml->GetInt("markup");
	devaluation_percent = xml->GetInt("devaluation");

	items.reserve(n);
	while( xml->NextChild("Item") )
	{
		items.push_back();
		items.back().DeserializeXml(xml);
	}

	xml->SetToParent();
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 ShopList
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

bool ShopList::SerializeXml( const fc::string& filename )
{
	XmlWriter xml(filename);
	if( !xml.IsOpen() )
	{
		Log("Could not open file (%s)", filename.c_str());
		return false;
	}

	xml.BeginNode("ShopList");
	xml.SetUInt("count", m_items.size());

	xml.SetString("def_greeting", Shop::default_greeting_message.c_str());
	xml.SetString("def_transaction", Shop::default_transaction_message.c_str());
	xml.SetString("def_buy", Shop::default_buy_message.c_str());
	xml.SetString("def_sell", Shop::default_sell_message.c_str());

	for( size_t i(0); i < m_items.size(); ++i )
	{
		m_items[i].SerializeXml(&xml);
	}

	xml.EndNode();
	xml.Close();

	return true;
}


bool ShopList::DeserializeXml( const fc::string& filename )
{
	XmlReader xml(filename);
	if( !xml.IsOpen() )
	{
		Log("Could not open file (%s)", filename.c_str());
		return false;
	}

	if( xml.GetCurrentNodeName() == "ShopList" )
	{
		size_t n = xml.GetUInt("count");

		Shop::default_greeting_message = xml.GetString("def_greeting");
		Shop::default_transaction_message = xml.GetString("def_transaction");
		Shop::default_buy_message = xml.GetString("def_buy");
		Shop::default_sell_message = xml.GetString("def_sell");

		m_items.clear();
		m_items.reserve(n);

		while( xml.NextChild("Shop") )
		{
			m_items.push_back();
			m_items.back().DeserializeXml(&xml);
		}
	}
	else
	{
		Log("Error parsing (%s). Root item not found", filename.c_str());
		return false;
	}

	xml.Close();

	return true;
}

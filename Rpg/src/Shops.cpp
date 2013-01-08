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


#include <Catastrophe/IO/XmlWriter.h>
#include <Catastrophe/IO/XmlReader.h>
#include "Shops.h"



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                  Shop
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void Shop::SerializeXml( XmlWriter* xml )
{
	xml->BeginNode("Shop");

	xml->SetUInt("num_items", items.size());
	xml->SetString("name", name.c_str());
	xml->SetString("greeting", greeting.c_str());
	xml->SetString("transaction", greeting.c_str());
	xml->SetString("buy", greeting.c_str());
	xml->SetString("sell", greeting.c_str());

	for( vec_type::iterator it = items.begin(); it < items.end(); ++it )
	{
		xml->BeginNode("Item");
		xml->SetUInt("id", *it);
		xml->EndNode();
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

	items.reserve(n);
	while( xml->NextChild("Item") )
	{
		items.push_back();
		items.back() = xml->GetUInt("id");
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
		if( n == 0 )
			return false;

		m_items.clear();
		m_items.resize(n);

		for( size_t i(0); i < n; ++i )
		{
			m_items[i].DeserializeXml(&xml);
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

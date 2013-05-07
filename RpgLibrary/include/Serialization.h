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
#include "RpgCommon.h"
#include "ResourceManager.h"



template <class T> void SerializeObject( XmlWriter* xml, const T& val );
template <class T> void SerializeObject( const char* nodeName, XmlWriter* xml, const T& val );
template <class T> void SerializeStringArray( XmlWriter* xml, const char* node, const T* stringArray, int n );


template <class T> void DeserializeObject( XmlReader* xml, T& val );
template <class T> void DeserializeObject( const char* nodeName, XmlReader* xml, T& val );
template <class T> void DeserializeStringArray( XmlReader* xml, const char* node, T* stringArray, int n );



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



template <class T> void SerializeObject( AttributeWriter* f, const T& val );
template <class T> void SerializeObject( const char* nodeName, AttributeWriter* f, const T& val );
template <class T> void SerializeStringArray( AttributeWriter* f, const char* node, const T* stringArray, int n );

// template specializations
template <> void SerializeObject<SpriteBase>( AttributeWriter* f, const SpriteBase& val );
template <> void SerializeObject<SpriteAnimation>( AttributeWriter* f, const SpriteAnimation& val );




template <class T> void DeserializeObject( AttributeReader* f, T& val );
template <class T> void DeserializeObject( const char* nodeName, AttributeReader* f, T& val );
template <class T> void DeserializeStringArray( AttributeReader* f, const char* node, T* stringArray, int n );


// template specializations
template <> void DeserializeObject<SpriteBase>( AttributeReader* f, SpriteBase& val );
template <> void DeserializeObject<SpriteAnimation>( AttributeReader* f, SpriteAnimation& val );



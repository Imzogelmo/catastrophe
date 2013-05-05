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


class RpgSerializer
{

	static void SerializePoint( XmlWriter* xml, const Point& p );
	static void SerializePoint( const char* nodeName, XmlWriter* xml, const Point& p );
	static void SerializeRect( XmlWriter* xml, const Rect& r );
	static void SerializeRect( const char* nodeName, XmlWriter* xml, const Rect& r );
	static void SerializeSpriteBase( XmlWriter* xml, const SpriteBase& s );

	void SerializeSprite( XmlWriter* xml, const Sprite& s );
	void SerializeAnimatedSprite( XmlWriter* xml, const AnimatedSprite& a );
	void SerializeAnimationSet( XmlWriter* xml, const AnimationSet& a );
	void SerializeAnimation( XmlWriter* xml, const Animation& a );
	void SerializeTile( XmlWriter* xml, const Tile& t );
	template <class T> static void SerializeStringArray( XmlWriter* xml, const char* node, const T* stringArray, int n );



	static void DeserializePoint( XmlReader* xml, Point& p );
	static void DeserializePoint( const char* nodeName, XmlReader* xml, Point& p );
	static void DeserializeRect( XmlReader* xml, Rect& r );
	static void DeserializeRect( const char* nodeName, XmlReader* xml, Rect& r );
	static void DeserializeSpriteBase( XmlReader* xml, SpriteBase& s );

	void DeserializeSprite( XmlReader* xml, Sprite& s );
	void DeserializeAnimatedSprite( XmlReader* xml, AnimatedSprite& a );
	void DeserializeAnimationSet( XmlReader* xml, AnimationSet& a );
	void DeserializeAnimation( XmlReader* xml, Animation& a );
	void DeserializeAnimationFrames( XmlReader* xml, Animation& a );
	void DeserializeTile( XmlReader* xml, Tile& t );
	template <class T> static void DeserializeStringArray( XmlReader* xml, const char* node, T* stringArray, int n );


};


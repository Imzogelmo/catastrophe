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

#include "../Common.h"


namespace Util
{

	void SerializePoint( XmlWriter* xml, const Point& p );
	void SerializeRect( XmlWriter* xml, const Rect& r );
	void SerializeRect( const char* nodeName, XmlWriter* xml, const Rect& r );
	void SerializeSpriteBase( XmlWriter* xml, const SpriteBase& s );
	void SerializeSprite( XmlWriter* xml, const Sprite& s );
	void SerializeAnimatedSprite( XmlWriter* xml, const AnimatedSprite& a );
	void SerializeAnimationSet( XmlWriter* xml, const AnimationSet& a );
	void SerializeAnimation( XmlWriter* xml, const Animation& a );
	void SerializeTile( XmlWriter* xml, const Tile& t );
	void SerializeStringArray( XmlWriter* xml, const char* node, const fc::string* stringArray, int n );



	void DeserializePoint( XmlReader* xml, Point& p );
	void DeserializeRect( XmlReader* xml, Rect& r );
	void DeserializeRect( const char* nodeName, XmlReader* xml, Rect& r );
	void DeserializeSpriteBase( XmlReader* xml, SpriteBase& s );
	void DeserializeSprite( XmlReader* xml, Sprite& s );
	void DeserializeAnimatedSprite( XmlReader* xml, AnimatedSprite& a );
	void DeserializeAnimationSet( XmlReader* xml, AnimationSet& a );
	void DeserializeAnimation( XmlReader* xml, Animation& a );
	void DeserializeAnimationFrames( XmlReader* xml, Animation& a );
	void DeserializeTile( XmlReader* xml, Tile& t );
	void DeserializeStringArray( XmlReader* xml, const char* node, fc::string* stringArray, int n );


}


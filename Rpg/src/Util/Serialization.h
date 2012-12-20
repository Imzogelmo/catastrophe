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
	// Workaround for the fact that in order to serialize we 
	// need need access to the current resources we are working with.
	// *** This must be set before calling any serialization methods! ***
	void SetResourceManager( ResourceManager* current );

	void SerializePoint( XmlWriter* xml, const Point& p );
	void SerializeRect( XmlWriter* xml, const Rect& r );
	void SerializeAnimation( XmlWriter* xml, const Animation& a );
	void SerializeAnimationFrames( XmlWriter* xml, const AnimationFrames& a );
	void SerializeTile( XmlWriter* xml, const Tile& t );




	void DeserializePoint( XmlReader* xml, Point& p );
	void DeserializeRect( XmlReader* xml, Rect& r );
	void DeserializeAnimation( XmlReader* xml, Animation& a );
	void DeserializeAnimationFrames( XmlReader* xml, AnimationFrames& a );
	void DeserializeTile( XmlReader* xml, Tile& t );



}


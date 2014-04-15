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

#include <Catastrophe/Graphics/SpriteBatch.h>
#include <Catastrophe/Math/Math.h>

#include "Script/MonoEngineBinding.h"


SpriteBatch* MonoEngineBinding::SpriteBatch_Create()
{
	return new SpriteBatch();
}


void MonoEngineBinding::SpriteBatch_Destroy( SpriteBatch* spriteBatch )
{
	delete spriteBatch;
}


void MonoEngineBinding::SpriteBatch_Draw( SpriteBatch* spriteBatch, gluint texture, Rectf* vertices, Rectf* uv, Color color)
{
	spriteBatch->Draw(
		texture,
		*vertices,
		*uv,
		color
	);
}


void MonoEngineBinding::SpriteBatch_DrawRotated( SpriteBatch* spriteBatch, gluint texture, float rotation, Vector2* origin, Rectf* vertices, Rectf* uv, Color color)
{
	spriteBatch->DrawRotated(
		texture,
		rotation,
		*origin,
		*vertices,
		*uv,
		color
	);
}


void MonoEngineBinding::SpriteBatch_DrawScaled( SpriteBatch* spriteBatch, gluint texture, Vector2* scale, Vector2* origin, Rectf* vertices, Rectf* uv, Color color)
{
	spriteBatch->DrawScaled(
		texture,
		*scale,
		*origin,
		*vertices,
		*uv,
		color
	);
}


void MonoEngineBinding::SpriteBatch_DrawRotatedScaled( SpriteBatch* spriteBatch, gluint texture, float rotation, Vector2* scale, Vector2* origin, Rectf* vertices, Rectf* uv, Color color)
{
	spriteBatch->DrawRotatedScaled(
		texture,
		rotation,
		*scale,
		*origin,
		*vertices,
		*uv,
		color
	);
}


void MonoEngineBinding::SpriteBatch_DrawSprite( SpriteBatch* spriteBatch, Sprite* sprite, Vector2* pos )
{
	if( sprite )
		spriteBatch->DrawSprite(*sprite, *pos);
}


void MonoEngineBinding::SpriteBatch_DrawAnimatedSprite( SpriteBatch* spriteBatch, AnimatedSprite* sprite, Vector2* pos )
{
	if( sprite )
		spriteBatch->DrawAnimatedSprite(*sprite, *pos);
}


void MonoEngineBinding::SpriteBatch_Begin( SpriteBatch* spriteBatch )
{
	spriteBatch->Begin();
}


void MonoEngineBinding::SpriteBatch_End( SpriteBatch* spriteBatch )
{
	spriteBatch->End();
}


void MonoEngineBinding::SpriteBatch_Render( SpriteBatch* spriteBatch )
{
	spriteBatch->Render();
}


void MonoEngineBinding::BindSpriteBatch()
{
	SetNamespace("CatastropheEngine.Graphics.SpriteBatch::");

	AddInternalCall("InternalCreate", SpriteBatch_Create);
	AddInternalCall("InternalDestroy", SpriteBatch_Destroy);
	AddInternalCall("Draw", SpriteBatch_Draw);
	AddInternalCall("DrawRotated", SpriteBatch_DrawRotated);
	AddInternalCall("DrawScaled", SpriteBatch_DrawScaled);
	AddInternalCall("DrawRotatedScaled", SpriteBatch_DrawRotatedScaled);
	AddInternalCall("DrawSprite", SpriteBatch_DrawSprite);
	AddInternalCall("DrawAnimatedSprite", SpriteBatch_DrawAnimatedSprite);
	AddInternalCall("Begin", SpriteBatch_Begin);
	AddInternalCall("End", SpriteBatch_End);
	AddInternalCall("Render", SpriteBatch_Render);

}

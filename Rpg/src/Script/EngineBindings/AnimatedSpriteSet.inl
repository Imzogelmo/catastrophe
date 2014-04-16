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


#include <mono/metadata/object.h>
#include <mono/metadata/loader.h>

#include <Catastrophe/Graphics/AnimatedSpriteSet.h>

#include "Script/MonoEngineBinding.h"


AnimatedSpriteSet* MonoEngineBinding::AnimatedSpriteSet_Create()
{
	AnimatedSpriteSet* animatedSpriteSet = new AnimatedSpriteSet();
	return animatedSpriteSet;
}


void MonoEngineBinding::AnimatedSpriteSet_Dispose( AnimatedSpriteSet* animatedSpriteSet )
{
	delete animatedSpriteSet;
}


void MonoEngineBinding::AnimatedSpriteSet_AddAnimation( AnimatedSpriteSet* animatedSpriteSet, SpriteAnimation* spriteAnimation )
{
	SAFE_CALL(animatedSpriteSet, AddAnimation(*spriteAnimation));
}


void MonoEngineBinding::AnimatedSpriteSet_InsertAnimation( AnimatedSpriteSet* animatedSpriteSet, SpriteAnimation* spriteAnimation, int index )
{
	SAFE_CALL(animatedSpriteSet, InsertAnimation(*spriteAnimation, index));
}


void MonoEngineBinding::AnimatedSpriteSet_RemoveAnimation( AnimatedSpriteSet* animatedSpriteSet, int index )
{
	SAFE_CALL(animatedSpriteSet, RemoveAnimation(index));
}


void MonoEngineBinding::AnimatedSpriteSet_SetTexture( AnimatedSpriteSet* animatedSpriteSet, Texture* texture )
{
	SAFE_CALL(animatedSpriteSet, SetTexture(texture));
}


void MonoEngineBinding::AnimatedSpriteSet_SetCurrentAnimation( AnimatedSpriteSet* animatedSpriteSet, int index )
{
	SAFE_CALL(animatedSpriteSet, SetCurrentAnimation(index));
}


void MonoEngineBinding::AnimatedSpriteSet_Reserve( AnimatedSpriteSet* animatedSpriteSet, int capacity )
{
	SAFE_CALL(animatedSpriteSet, Reserve(capacity));
}


void MonoEngineBinding::AnimatedSpriteSet_Resize( AnimatedSpriteSet* animatedSpriteSet, int newSize )
{
	SAFE_CALL(animatedSpriteSet, Resize(newSize));
}


void MonoEngineBinding::AnimatedSpriteSet_Update( AnimatedSpriteSet* animatedSpriteSet )
{
	SAFE_CALL(animatedSpriteSet, Update());
}


int MonoEngineBinding::AnimatedSpriteSet_GetNumAnimations( AnimatedSpriteSet* animatedSpriteSet )
{
	SAFE_CALL_RETURN(animatedSpriteSet, GetNumAnimations(), 0);
}


int MonoEngineBinding::AnimatedSpriteSet_GetCurrentAnimationIndex( AnimatedSpriteSet* animatedSpriteSet )
{
	SAFE_CALL_RETURN(animatedSpriteSet, GetCurrentAnimationIndex(), 0);
}


Texture* MonoEngineBinding::AnimatedSpriteSet_GetTexture( AnimatedSpriteSet* animatedSpriteSet )
{
	SAFE_CALL_RETURN(animatedSpriteSet, GetTexture(), 0);
}


SpriteAnimation MonoEngineBinding::AnimatedSpriteSet_GetAnimation( AnimatedSpriteSet* animatedSpriteSet, int index )
{
	SAFE_CALL_RETURN(animatedSpriteSet, GetAnimation(index), SpriteAnimation());
}


SpriteAnimation MonoEngineBinding::AnimatedSpriteSet_GetCurrentAnimation( AnimatedSpriteSet* animatedSpriteSet )
{
	SAFE_CALL_RETURN(animatedSpriteSet, GetCurrentAnimation(), SpriteAnimation());
}



void MonoEngineBinding::BindAnimatedSpriteSet()
{
	AddInternalCall("Create", AnimatedSpriteSet_Create);
	AddInternalCall("Dispose", AnimatedSpriteSet_Dispose);
	AddInternalCall("AddAnimation", AnimatedSpriteSet_AddAnimation);
	AddInternalCall("InsertAnimation", AnimatedSpriteSet_InsertAnimation);
	AddInternalCall("RemoveAnimation", AnimatedSpriteSet_RemoveAnimation);
	AddInternalCall("SetTexture", AnimatedSpriteSet_SetTexture);
	AddInternalCall("SetCurrentAnimation", AnimatedSpriteSet_SetCurrentAnimation);
	AddInternalCall("Reserve", AnimatedSpriteSet_Reserve);
	AddInternalCall("Resize", AnimatedSpriteSet_Resize);
	AddInternalCall("Update", AnimatedSpriteSet_Update);
	AddInternalCall("GetNumAnimations", AnimatedSpriteSet_GetNumAnimations);
	AddInternalCall("GetCurrentAnimationIndex", AnimatedSpriteSet_GetCurrentAnimationIndex);
	AddInternalCall("GetTexture", AnimatedSpriteSet_GetTexture);
	AddInternalCall("GetAnimation", AnimatedSpriteSet_GetAnimation);
	AddInternalCall("GetCurrentAnimation", AnimatedSpriteSet_GetCurrentAnimation);
	//AddInternalCall("GetAnimations", AnimatedSpriteSet_GetAnimations);
}






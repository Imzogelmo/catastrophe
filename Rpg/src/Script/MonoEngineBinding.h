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

#include <Catastrophe/Common.h>
#include "Common.h"
#include "MonoBinding.h"


class MonoEngineBinding : public MonoBinding
{
public:

	// Math
	static void Math_SinCos( float* s, float* c, float angle );
	static Vector2 Math_SinCosv( float angle );
	static float Math_Sin( float x );
	static float Math_Cos( float x );
	static float Math_Atan2( float y, float x );
	static int Math_Rand( int n );
	static int Math_RandRange( int min, int max );
	static float Math_RandUnitf();
	static float Math_Randf( float n );
	static float Math_RandRangef( float min, float max );
	static float Math_Bezier4pt( float value1, float tangent1, float value2, float tangent2, float t );
	static float Math_Hermite( float value1, float tangent1, float value2, float tangent2, float t );
	static float Math_CatmullRom( float value1, float value2, float value3, float value4, float t );


	// Vector2
	static void Vector2_Rotate( Vector2* self, float angle );
	static void Vector2_RotateOrigin( Vector2* self, float angle, Vector2 origin );
	static Vector2 Vector2_Rotated( Vector2* self, float angle );
	static Vector2 Vector2_RotatedOrigin( Vector2* self, float angle, Vector2 origin );

	// Matrix4
	static float Matrix_Determinant( Matrix* self );
	static Matrix Matrix_Transpose( Matrix* self );
	static Matrix Matrix_Inverse( Matrix* self );
	static float Matrix_GetIndex( Matrix* self, int index );
	static void Matrix_SetIndex( Matrix* self, int index, float value );
	static Matrix Matrix_Lerp( Matrix* self, Matrix* a, Matrix* b, float t );
	static void Matrix_Multiply( Matrix* self, Matrix* a, Matrix* b );
	static Matrix Matrix_CreateLookAt( Matrix* self, Vector3 camera, Vector3 target, Vector3 up );
	static Matrix Matrix_CreateOrthographic( Matrix* self, float left, float right, float bottom, float top, float zNear, float zFar );
	static Matrix Matrix_CreatePerspective( Matrix* self, float fov, float aspect, float up, float zNear, float zFar );
	static Matrix Matrix_CreateRotation( Matrix* self, Vector3 rotation );
	static Matrix Matrix_CreateTransformation( Matrix* self, Vector3 pos, float rotation, Vector3 scale, Vector3 origin );
	static Matrix Matrix_CreateTranslation( Matrix* self, Vector3 pos );
	static Matrix Matrix_CreateScale( Matrix* self, Vector3 scale );
	static Matrix Matrix_CreateRotationX( Matrix* self, float radians );
	static Matrix Matrix_CreateRotationY( Matrix* self, float radians );
	static Matrix Matrix_CreateRotationZ( Matrix* self, float radians );

	
	// Collision
	static float Collision_DistanceToLineSegment2D( Vector2 a, Vector2 b, Vector2 point );
	static float Collision_DistanceToLineSegment3D( Vector3 a, Vector3 b, Vector3 point );


	// Input
	static int Keyboard_GetKeyState( int key );
	static int Joystick_GetButtonState( int joystickID, int button );
	static float Joystick_GetAxis( int joystickID, int axis );
	static Vector2 Joystick_GetAnalog( int joystickID, int analog );
	static int Joystick_GetDPad( int joystickID );

	// Texture
	static Texture* Texture_LoadFromFile( MonoString* str );
	static Texture* Texture_Create( int width, int height );
	static void Texture_Dispose( Texture* texture );
	static void Texture_AddRef( Texture* texture );
	static void Texture_ReleaseRef( Texture* texture );
	static int Texture_GetTextureID( Texture* texture );
	static int Texture_GetWidth( Texture* texture );
	static int Texture_GetHeight( Texture* texture );
	static Vector2 Texture_CalculateUV( Texture* texture, Point* point );
	static Rectf Texture_CalculateUVRect( Texture* texture, Rect* rect );

	// Font
	static Font* Font_LoadFromFile( MonoString* str );
	static void Font_Dispose( Font* self );
	static void Font_SetAdvance( Font* self, int advance );
	static void Font_SetLineHeight( Font* self, int height );
	static int Font_GetTextWidth( Font* self, MonoString* str );
	static Texture* Font_GetTexture( Font* self );
	static int Font_GetLineHeight( Font* self );
	static Glyph Font_GetGlyph( Font* self, byte i );
	static void Font_SetGlyph( Font* self, byte i, Glyph* glyph );

	// Sprite
	static Sprite* Sprite_Create();
	static void Sprite_Dispose( Sprite* sprite );
	static void Sprite_SetTexture( Sprite* sprite, Texture* texture );
	static Vector2 Sprite_GetSize( Sprite* sprite );
	static void Sprite_SetSize( Sprite* sprite, Vector2 value );
	static Vector2 Sprite_GetScale( Sprite* sprite );
	static void Sprite_SetScale( Sprite* sprite, Vector2 value );
	static Color Sprite_GetColor( Sprite* sprite );
	static void Sprite_SetColor( Sprite* sprite, Color value );
	static BlendMode Sprite_GetBlendMode( Sprite* sprite );
	static void Sprite_SetBlendMode( Sprite* sprite, BlendMode value );
	static float Sprite_GetAngle( Sprite* sprite );
	static void Sprite_SetAngle( Sprite* sprite, float value );
	static Rectf Sprite_GetUVRect( Sprite* sprite );
	static void Sprite_SetUVRect( Sprite* sprite, Rectf* value );
	static Rect Sprite_GetSourceRect( Sprite* sprite );
	static void Sprite_SetSourceRect( Sprite* sprite, Rect* value );


	// AnimatedSprite
	static AnimatedSprite* AnimatedSprite_Create();
	static void AnimatedSprite_Dispose( AnimatedSprite* sprite );
	static void AnimatedSprite_Update( AnimatedSprite* sprite );
	static Rectf AnimatedSprite_GetUVRect( AnimatedSprite* sprite );
	static void AnimatedSprite_SetUVRect( AnimatedSprite* sprite, Rectf* value );
	static Rect AnimatedSprite_GetSourceRect( AnimatedSprite* sprite );
	static void AnimatedSprite_SetSourceRect( AnimatedSprite* sprite, Rect* value );
	static int AnimatedSprite_GetNumFrames( AnimatedSprite* sprite );
	static void AnimatedSprite_SetNumFrames( AnimatedSprite* sprite, int value );
	static int AnimatedSprite_GetCurrentFrame( AnimatedSprite* sprite );
	static void AnimatedSprite_SetCurrentFrame( AnimatedSprite* sprite, int value );
	static float AnimatedSprite_GetAnimationSpeed( AnimatedSprite* sprite );
	static void AnimatedSprite_SetAnimationSpeed( AnimatedSprite* sprite, float value );


	// AnimatedSpriteSet
	static AnimatedSpriteSet* AnimatedSpriteSet_Create();
	static void AnimatedSpriteSet_Dispose( AnimatedSpriteSet* animatedSpriteSet );
	static void AnimatedSpriteSet_AddAnimation( AnimatedSpriteSet* animatedSpriteSet, SpriteAnimation* spriteAnimation );
	static void AnimatedSpriteSet_InsertAnimation( AnimatedSpriteSet* animatedSpriteSet, SpriteAnimation* spriteAnimation, int index );
	static void AnimatedSpriteSet_RemoveAnimation( AnimatedSpriteSet* animatedSpriteSet, int index );
	static void AnimatedSpriteSet_SetTexture( AnimatedSpriteSet* animatedSpriteSet, Texture* texture );
	static void AnimatedSpriteSet_SetCurrentAnimation( AnimatedSpriteSet* animatedSpriteSet, int index );
	static void AnimatedSpriteSet_Reserve( AnimatedSpriteSet* animatedSpriteSet, int capacity );
	static void AnimatedSpriteSet_Resize( AnimatedSpriteSet* animatedSpriteSet, int newSize );
	static void AnimatedSpriteSet_Update( AnimatedSpriteSet* animatedSpriteSet );
	static int AnimatedSpriteSet_GetNumAnimations( AnimatedSpriteSet* animatedSpriteSet );
	static int AnimatedSpriteSet_GetCurrentAnimationIndex( AnimatedSpriteSet* animatedSpriteSet );
	static Texture* AnimatedSpriteSet_GetTexture( AnimatedSpriteSet* animatedSpriteSet );
	static SpriteAnimation AnimatedSpriteSet_GetAnimation( AnimatedSpriteSet* animatedSpriteSet, int index );
	static SpriteAnimation AnimatedSpriteSet_GetCurrentAnimation( AnimatedSpriteSet* animatedSpriteSet );
	//static vec_type AnimatedSpriteSet_GetAnimations( AnimatedSpriteSet* animatedSpriteSet );


	// SpriteBatch
	static SpriteBatch* SpriteBatch_Create();
	static void SpriteBatch_Destroy( SpriteBatch* spriteBatch );
	static void SpriteBatch_Draw( SpriteBatch* spriteBatch, gluint texture, Rectf* vertices, Rectf* uv, Color color);
	static void SpriteBatch_DrawRotated( SpriteBatch* spriteBatch, gluint texture, float rotation, Vector2* origin, Rectf* vertices, Rectf* uv, Color color);
	static void SpriteBatch_DrawScaled( SpriteBatch* spriteBatch, gluint texture, Vector2* scale, Vector2* origin, Rectf* vertices, Rectf* uv, Color color);
	static void SpriteBatch_DrawRotatedScaled( SpriteBatch* spriteBatch, gluint texture, float rotation, Vector2* scale, Vector2* origin, Rectf* vertices, Rectf* uv, Color color);
	static void SpriteBatch_DrawSprite( SpriteBatch* spriteBatch, Sprite* sprite, Vector2* pos );
	static void SpriteBatch_DrawAnimatedSprite( SpriteBatch* spriteBatch, AnimatedSprite* sprite, Vector2* pos );
	static void SpriteBatch_Begin( SpriteBatch* spriteBatch );
	static void SpriteBatch_End( SpriteBatch* spriteBatch );
	static void SpriteBatch_Render( SpriteBatch* spriteBatch );


	// VertexArray
	static void VertexArray_Render( int primitiveType, void* vertices, int first, int count, int stride, void* elements );


	// StaticString
	static MonoString* StaticString_ToString( const char* ptr );



	static void BindMathf();
	static void BindVector2();
	static void BindMatrix4();
	static void BindCollision();
	static void BindTexture();
	static void BindFont();
	static void BindSprite();
	static void BindAnimatedSprite();
	static void BindAnimatedSpriteSet();
	static void BindSpriteBatch();
	static void BindVertexArray();
	static void BindStaticString();
	static void BindInput();

};


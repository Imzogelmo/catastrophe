
#pragma once

#ifndef __DEFINED__


//----------------------------------
// * Color
//----------------------------------
class color
{
public:
	uint8 r, g, b, a;

	color();
	color( uint8 r, uint8 g, uint8 b );
	color( uint8 r, uint8 g, uint8 b, uint8 a );
	color( const color& );

	color& operator = ( const color& );
	bool operator == ( const color& ) const;
	bool operator != ( const color& ) const;

	color& set( uint8 r, uint8 g, uint8 b, uint8 a );
	color& lerp( const color& c, float t );

	string to_string() const;

};


//----------------------------------
// * Colorf
//----------------------------------
class colorf
{
public:
	float r, g, b, a;

	colorf();
	colorf( float r, float g, float b );
	colorf( float r, float g, float b, float a );
	colorf( const colorf& );

	colorf& operator = ( const colorf& );
	bool operator == ( const colorf& ) const;
	bool operator != ( const colorf& ) const;

	//colorf& set( float r, float g, float b, float a );
	//colorf& lerp( const colorf& other, float t );

	string to_string() const;
};



//----------------------------------
// * Blendmode
//----------------------------------
class blendmode
{
public:
	uint16 src;
	uint16 dst;

	blendmode();
	blendmode( uint16 sourceFactor, uint16 destFactor );
	blendmode( const blendmode& );

	blendmode& operator = ( const blendmode& );

	bool operator == ( const blendmode& ) const;
	bool operator != ( const blendmode& ) const;

	blendmode &set( uint16 sourceFactor, uint16 destFactor );
};



//----------------------------------
// * Sprite
//----------------------------------
class sprite
{
public:
	vec2 size;
	vec2 scale;
	color color;
	blendmode blendmode;
	float angle;
	rectf uv;

	sprite();
	sprite(const sprite&);
	sprite &operator =(const sprite&);

};



//----------------------------------
// * SpriteAnimation
//----------------------------------
class sprite_animation 
{
public:
	int animation_speed;
	int frame;
	int num_frames;
	rect source_rect;
	rectf uv;


	bool is_animated() const;
	//void flip(int flags);

};


//----------------------------------
// * AnimatedSprite
//----------------------------------
class animated_sprite : public sprite_animation
{
public:
	vec2 size;
	vec2 scale;
	color color;
	blendmode blendmode;
	float angle;

	animated_sprite();
	animated_sprite(const animated_sprite&);
	animated_sprite &operator =(const sprite&);
	animated_sprite &operator =(const animated_sprite&);

};


//----------------------------------
// * AnimatedSpriteSet
//----------------------------------
class animated_spriteset
{
public:
	sprite_animation animation[];
	vec2 size;
	vec2 scale;
	color color;
	blendmode blendmode;
	float angle;
	int num_animations; //get
	int state;

	animated_spriteset();
	animated_spriteset(const animated_spriteset&);
	animated_spriteset &operator =(const animated_spriteset&);

	//void add_animation(const rect& sourceRect, float speed, int numFrames, int frameOffsetX, int frameOffsetY);
	//void remove_animation(int index);

};



void f()
{
	pos + sprite.size / 2f;

	spriteset s;
	spriteset[4].frame = 3;

	spriteset.state = WALKING;
	int n = spriteset.animation[WALKING].num_frames;



}



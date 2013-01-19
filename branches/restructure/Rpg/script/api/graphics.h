
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




/*
class Sprite
{
public:
	vec2 size;
	vec2 scale;
	float angle;
	color tint;

	Sprite();
	Sprite( const Sprite& );
	Sprite( int sprite_index );

	Sprite &operator = ( const Sprite& );

	//getters
	bool is_animated() const;
	float get_animation_speed() const;
	int get_num_frames() const;
	int get_frame() const;
	int get_layer() const;
	int get_index() const;

	//setters
	void set_animation_speed(float speed);
	void set_frame(int frame);
	void set_layer(int layer);
	void set_index(int sprite_index);

	void flip(int flags);
	void animate();

protected:
	int animation_speed;
	int frame;
	int layer;
	int index;
};
*/

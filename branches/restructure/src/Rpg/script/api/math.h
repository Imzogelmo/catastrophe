
#pragma once

#ifndef __DEFINED__


//----------------------------------
// * Vec2
//----------------------------------
class vec2
{
public:
	float x, y;

	//swizzle getters/setters
	vec2 xy;
	vec2 yx;

	vec2();
	vec2( float x, float y );
	vec2( const vec2& );

	float length() const;
	float length_squared() const;
	float distance( const vec2& v ) const;
	float distance_squared( const vec2& v ) const;
	float dot( const vec2& v ) const;
	float cross( const vec2& v ) const;
	float angle() const;
	float angle( const vec2& v ) const;

	vec2& normalize();
	vec2 normal() const;
	vec2 abs() const;
	vec2 ceil() const;
	vec2 floor() const;
	vec2 round() const;
	vec2 negate() const;
	vec2 min( const vec2& v ) const;
	vec2 max( const vec2& v ) const;
	vec2 lerp( const vec2& v, float t ) const;
	//vec2 polar( const vec2& dist, float angle ) const;
	vec2 direction( const vec2& to ) const;

	vec2& operator = ( const vec2& );

	vec2 operator + ( float ) const;
	vec2 operator - ( float ) const;
	vec2 operator * ( float ) const;
	vec2 operator / ( float ) const;
	vec2 operator + ( const vec2& ) const;
	vec2 operator - ( const vec2& ) const;
	vec2 operator * ( const vec2& ) const;
	vec2 operator / ( const vec2& ) const;
	vec2 operator + ( float, const vec2& ) const;
	vec2 operator - ( float, const vec2& ) const;
	vec2 operator * ( float, const vec2& ) const;
	vec2 operator / ( float, const vec2& ) const;
	vec2& operator += ( float );
	vec2& operator -= ( float );
	vec2& operator *= ( float );
	vec2& operator /= ( float );
	vec2& operator += ( const vec2& );
	vec2& operator -= ( const vec2& );
	vec2& operator *= ( const vec2& );
	vec2& operator /= ( const vec2& );
	bool operator == ( const vec2& ) const;
	bool operator != ( const vec2& ) const;

	string to_string() const;
};


//----------------------------------
// * Rectf
//----------------------------------
class rectf
{
public:
	vec2 pos, size; //get/set
	vec2 min, max;

	rectf();
	rectf( float x, float y, float w, float h );
	rectf( const vec2& min, const vec2& max );
	rectf( const rectf& );

	float top() const;
	float bottom() const;
	float left() const;
	float right() const;
	vec2 top_left() const;
	vec2 bottom_left() const;
	vec2 bottom_right() const;
	vec2 top_right() const;

	vec2 center() const;

	//get/set
	float x;
	float y;
	float width;
	float height;
	//float area() const;

	//rectf& scale( float x, float y );
	//rectf& inflate( float x, float y );
	//rectf& deflate( float x, float y );

	bool empty() const;
	bool intersects( const rectf& r ) const;
	bool intersects( const vec2& point ) const;

	rectf& operator = ( const rectf& );

	bool operator == ( const Rect& ) const;
	bool operator != ( const Rect& ) const;

	string to_string() const;
};


//----------------------------------
// * Rect
//----------------------------------
class rect
{
public:
	point pos, size;

	rect();
	rect( int x, int y, int w, int h );
	rect( const point& pos, const point& size );
	rect( const rect& );

	int top() const;
	int bottom() const;
	int left() const;
	int right() const;
	point top_left() const;
	point bottom_left() const;
	point bottom_right() const;
	point top_right() const;

	bool empty() const;
	bool intersects( const rect& r ) const;
	bool intersects( const point& point ) const;

	rect& operator = ( const rect& );
	string to_string() const;

};



//----------------------------------
// * Matrix
//----------------------------------
class matrix
{
public:
	/* OpenGl matrix:
        [x],   0,    0,   0,
         0,   [y],   0,   0,
         0,    0,  [z],   0,
        (x,    y,   z),   1 (translation)
	*/

	matrix();
	matrix( const matrix& );

	matrix& operator = ( const matrix& );
	bool operator == ( const matrix& ) const;
	bool operator != ( const matrix& ) const;

	float &operator [] ( int index );
	float &operator [] ( int y, int x );
	const float &operator [] ( int index ) const;
	const float &operator [] ( int y, int x ) const;

	/*
	matrix create_look_at( const vector3& camera, const vector3& target, const vector3& up ) const;
	matrix create_orthographic( float left, float right, float bottom, float top, float near, float far ) const;
	matrix create_perspective( float left, float right, float bottom, float top, float near, float far ) const;
	matrix create_perspective_fov( float fov, float aspectRatio, float up, float near, float far ) const;
	matrix create_transformation( const vector3& translation, const vector3& rotation, const vector3& scale ) const;
	matrix create_translation( const vector3& in ) const;
	matrix create_rotation( const vector3& rotation ) const;
	matrix create_scale( const vector3& scale ) const;
	matrix create_rotation_x( float rotation ) const;
	matrix create_rotation_y( float rotation ) const;
	matrix create_rotation_z( float rotation ) const;
	matrix identity() const;
	*/

	//matrix operator * ( float ) const;
	//matrix operator / ( float ) const;
	//matrix operator + ( const matrix& ) const;
	//matrix operator - ( const matrix& ) const;
	matrix operator * ( const matrix& ) const;
	string to_string() const;
};


//----------------------------------
// * Math Functions
//----------------------------------
float cos( float x );
float sin( float x );
float tan( float x );
float dcos( float x );
float dsin( float x );
float acos( float x );
float asin( float x );
float atan( float x );
float cosh( float x );
float sinh( float x );
float tanh( float x );
float atan2( float y, float x );
float log( float x );
float log10( float x );
float pow( float y, float x );
float sqrt( float x );
float abs( float x );
float ceil( float x );
float floor( float x );
float fmod( float y, float x );
void sincos( float x, float& s, float& c );
vec2 sincos( float x );

// random number functions
int rand();
int rand( int x );
int rand( int x, int y );
float randf();
float randf( float x );
float randf( float x, float y );
vec2 randv();
vec2 randv( const vec2 &x );
vec2 randv( const vec2 &x, const vec2 &y );
vec2 arc_rand( float min, float max, float radii = 1.f );
vec2 circular_rand( float radii = 1.f );
int variance( int number, int variance );
float variance( float number, float variance );
bool probability( int percent );
bool probability( int percent, int total );

// general math utility functions
float distance( float x1, float y1, float x2, float y2 );
float distance_to_line_segment( const vec2&, const vec2&, const vec2& );
//float distance_to_line_segment( const vec3&, const vec3&, const vec3& );
float to_degrees( float x );
float to_radians( float x );

int min( int a, int b );
int min( int a, int b, int c );
int min( int a, int b, int c, int d );
int max( int a, int b );
int max( int a, int b, int c );
int max( int a, int b, int c, int d );
float min( float a, float b );
float min( float a, float b, float c );
float min( float a, float b, float c, float d );
float max( float a, float b );
float max( float a, float b, float c );
float max( float a, float b, float c, float d );

int clamp( int val, int min, int max );
float clamp( float val, float min, float max );
color clamp( const color& val, const color& min, const color& max );
vec2 clamp( const vec2& val, const vec2& min, const vec2& max );
vec3 clamp( const vec3& val, const vec3& min, const vec3& max );

// interpolation functions
float lerp( float a, float b, float t );
vec2 lerp( const vec2& a, const vec2& b, float t );
vec3 lerp( const vec3& a, const vec3& b, float t );
vec4 lerp( const vec4& a, const vec4& b, float t );
color lerp( const color& a, const color& b, float t );
colorf lerp( const colorf& a, const colorf& b, float t );

float smooth_step( float a, float b, float t );
float bezier( float a, float b, float c, float t );
float bezier( float a, float b, float c, float d, float t );
float bezier( float a, float b, float c, float d, float e, float t );
float catmull_rom( float a, float b, float c, float d, float t );

vec2 smooth_step( const vec2& a, const vec2& b, float t );
vec2 bezier( const vec2& a, const vec2& b, const vec2& c, float t );
vec2 bezier( const vec2& a, const vec2& b, const vec2& c, const vec2& d, float t );
vec2 bezier( const vec2& a, const vec2& b, const vec2& c, const vec2& d, const vec2& e, float t );
vec2 catmull_rom( const vec2& a, const vec2& b, const vec2& c, const vec2& d, float t );

vec3 smooth_step( const vec3& a, const vec3& b, float t );
vec3 bezier( const vec3& a, const vec3& b, const vec3& c, float t );
vec3 bezier( const vec3& a, const vec3& b, const vec3& c, const vec3& d, float t );
vec3 bezier( const vec3& a, const vec3& b, const vec3& c, const vec3& d, const vec3& e, float t );
vec3 catmull_rom( const vec3& a, const vec3& b, const vec3& c, const vec3& d, float t );


//////////////////////////////////////
// Fast Container Library           //
// MIT License - Copyright (c) 2012 //
//////////////////////////////////////

#pragma once

#include "Catastrophe/Core/Common.h"
#include <math.h>

CE_NAMESPACE_BEGIN


template <class T> FORCEINLINE
bool IsWhitespace( T c )
{
	return (c == T(' ') || c == T('\t'));
}

template <class T> FORCEINLINE
bool IsDigit( T c )
{
	return (c >= T('0') && c <= T('9'));
}

template <class T> FORCEINLINE
bool IsUppercase( T c )
{
	return ((c >= 'A') && (c <= 'Z'));
}

template <class T> FORCEINLINE
bool IsLowercase( T c )
{
	return ((c >= 'a') && (c <= 'z'));
}

template <class T> FORCEINLINE
T ToLower(T c)
{
	if ( (c >= 'A') && (c <= 'Z') )
		c = c + ('a' - 'A');
	return c;
}

template <class T> FORCEINLINE
T ToUpper(T c)
{
	if( (c >= 'a') && (c <= 'z') )
		c = c - ('a' - 'A');
	return c;
}


inline bool CaseInsensitiveCompare(char a, char b)
{
	return ToLower(a) == ToLower(b);
}


int Strtoi( const char* source, char** endptr, int defaultValue = 0 );

inline int Strtoi( const char *p )
{
	return Strtoi(p, (char**)null, 0);
}


double Strtod( const char* source, char** endptr, double defaultValue = 0.0 );

inline double Strtod( const char *p )
{
	return Strtod(p, (char**)null, 0.0);
}

inline float Strtof( const char *p, char** endptr, float defaultValue = 0.f )
{
	return (float)Strtod(p, endptr, (double)defaultValue);
}

inline float Strtof( const char *p )
{
	return (float)Strtod(p, (char**)null, 0.0);
}

u32 Itoa( u32 value, char* bufptr );
u32 Itoa( int value, char* bufptr );
u32 Dtoa( double value, char* bufptr );

inline u32 Ftoa( float value, char* bufptr )
{
	return Dtoa((double)value, bufptr);
}


FORCEINLINE u32 Strlen( const char* str )
{
	return ::strlen(str);
}

constexpr FORCEINLINE u32 Strnlen(const char* str, u32 maxLength)
{
	return ::strnlen(str, maxLength);
	//u32 i(0);
	//for( ; (i < maxLength) && str[i]; ++i ) ;
	//return i;
}

int Sprintf( char* str, const char* format, ... );
int Snprintf( char* str, u32 nBytes, const char* format, ... );


CE_NAMESPACE_END


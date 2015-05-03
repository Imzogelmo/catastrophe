//////////////////////////////////////
// Fast Container Library           //
// MIT License - Copyright (c) 2012 //
//////////////////////////////////////

#pragma once

#include "Catastrophe/Core/Common.h"
#include "Catastrophe/Core/PlatformMath.h"

#include <stdarg.h> // for va_list

CE_NAMESPACE_BEGIN


// 
void NonInlinedDebugAssertLog( bool condition, int line, const char* file, const char* fn )
{
	// Log the assertion failure and break into the debugger where it failed if Assert is called.
	if( UNLIKELY(!condition) )
		LogError("Assertion failed! Line %i, File: %s, Function: %s", line, file, fn);
}


int Strtoi( const char* source, char** endptr, int defaultValue )
{
	int c, sign, n = 0;
	const char* digitptr;
	const char *p = (const char *)source;

	if( !source )
		return defaultValue;

	// bypass leading whitespace
	while( (*p == ' ' || *p == '\t') )
		++p;

	c = *p++;
	sign = c;
	if( c == '-' || c == '+' )
		c = *p++;

	digitptr = p;
	while( c >= '0' && c <= '9' )
	{
		n = 10 * n + (c - '0');
		c = *p++;
	}

	if( digitptr == p ) n = defaultValue; //invalid string
	else if (sign == '-') n = -n;

	if( endptr )
		*endptr = (char*)p;

	return n;
}


// StringToDouble function based on fast atof code by Tom Van Baak
double Strtod( const char* source, char** endptr, double defaultValue )
{
	int frac;
	double sign, value, scale;
	const char *p = (const char *)source;

	if( !p )
		return defaultValue;

	// bypass leading whitespace
	while( *p == ' ' || *p == '\t' )
		++p;

	sign = 1.0;
	if( *p == '-' ) sign = -1.0, ++p;
	else if (*p == '+') ++p;

	const char* digitptr = p;
	for( value = 0.0; IsDigit(*p); ++p )
		value = value * 10.0 + (*p - '0');

	if( *p == '.' )
	{
		double pow10 = 10.0;
		while( IsDigit(*++p) )
		{
			value += (*p - '0') / pow10;
			pow10 *= 10.0;
		}
	}

	frac = 0;
	scale = 1.0;
	if( *p == 'e' || *p == 'E' )
	{
		unsigned int exponent;

		++p;
		if (*p == '-') frac = 1, ++p;
		else if (*p == '+') ++p;

		for( exponent = 0; IsDigit(*p); ++p )
			exponent = exponent * 10 + (*p - '0');

		if( exponent > 308 ) exponent = 308;
		while (exponent >= 50) { scale *= 1E50; exponent -= 50; }
		while (exponent >=  8) { scale *= 1E8;  exponent -=  8; }
		while (exponent >   0) { scale *= 10.0; exponent -=  1; }
	}

	if( endptr )
		*endptr = (char*)p;

	if( digitptr == p )
		return defaultValue;

	return (sign * (frac ? (value / scale) : (value * scale)));
}


u32 Itoa( u32 value, char* bufptr )
{
	char buffer[16];
	char* p = buffer;

	do {
		*p++ = (value % 10) + '0';
		value /= 10;
	}
	while( value != 0 );

	char* begin = bufptr;
	while( p-- != buffer )
		*bufptr++ = *p;

	*bufptr = 0;
	return u32(bufptr - begin);
}


u32 Itoa( int value, char* bufptr )
{
	char* p = bufptr;
	if( value < 0 )
	{
		value = -value;
		*p++ = '-';
	}

	return Itoa((u32)value, p);
}


u32 Dtoa( double value, char* bufptr )
{
	char buffer[16];

	//nan
	if( value != value)
	{
		bufptr[0] = '0';
		bufptr[1] = 0;
		return (u32)2;
	}

	int neg = 0;
	if( value < 0.0 )
		neg = 1, value = -value;

	int whole = (int)value;
	int frac = (int)((value - (double)whole) * 1000000.0);
	char* p = buffer;

	//exponent
	if( value > (float)(0x07FFFFFF) )
	{
		*p++ = 'e';
		*p++ = neg ? '-' : '+';

		int m = (int)log10(value);
		while( m > 0 )
		{
			*p++ = '0' + m % 10;
			m /= 10;
			m++;
		}
	}
	else
	{
		//decimal
		if( frac != 0 )
		{
			while( frac && !(frac % 10) )
				frac /= 10;

			do *p++ = (char)('0' + (frac % 10)); while (frac /= 10);
			*p++ = '.';
		}

		//whole
		do *p++ = (char)('0' + (whole % 10)); while (whole /= 10);
		if( neg ) *p++ = '-';
	}

	char* begin = bufptr;
	while( p-- != buffer )
		*bufptr++ = *p;

	*bufptr = 0;
	return (u32)(bufptr - begin);
}


int Sprintf( char* str, const char* format, ... )
{
	va_list args;
	va_start(args, format);
	int retValue = vsprintf(str, format, args);
	va_end(args);

	return retValue;
}


int Snprintf( char* str, u32 nBytes, const char* format, ... )
{
	va_list args;
	va_start(args, format);
	int retValue = vsnprintf(str, nBytes, format, args);
	va_end(args);

	return retValue;
}


CE_NAMESPACE_END



#pragma once

//this is defined by the compiler
#ifndef __DEFINED__
	typedef char				int8;
	typedef short				int16;
	typedef int					int32;
	typedef __int64				int64;

	typedef unsigned char		uint8;
	typedef unsigned short		uint16;
	typedef unsigned int		uint32;
	typedef unsigned __int64	uint64;
	typedef unsigned int		uint;

	typedef point				vec2i;

#endif


#define SYSTEM_FONT	0

#define NULL	0
#define NONE	0
#define ZERO	0
#define ONE		1
#define TRUE	1
#define FALSE	0

// primitive types
#define POINTS			0x0000
#define LINES			0x0001
#define LINE_LOOP		0x0002
#define LINE_STRIP		0x0003
#define TRIANGLES		0x0004
#define TRIANGLE_STRIP	0x0005
#define TRIANGLE_FAN	0x0006
#define QUADS			0x0007
#define QUAD_STRIP		0x0008
#define POLYGON			0x0009


// blendmode source factors
/*      ZERO				*/
/*      ONE					*/
#define SRC_COLOR				0x0300
#define ONE_MINUS_SRC_COLOR		0x0301
#define SRC_ALPHA				0x0302
#define ONE_MINUS_SRC_ALPHA		0x0303
#define DST_ALPHA				0x0304
#define ONE_MINUS_DST_ALPHA		0x0305


// blendmode destination factors
/*      ZERO				*/
/*      ONE					*/
#define DST_COLOR				0x0306
#define ONE_MINUS_DST_COLOR		0x0307
#define SRC_ALPHA_SATURATE		0x0308
/*      SRC_ALPHA			*/
/*      ONE_MINUS_SRC_ALPHA */
/*      DST_ALPHA			*/
/*      ONE_MINUS_DST_ALPHA */


//common blendmodes
#define BLENDMODE_ALPHA					blendmode(SRC_ALPHA, ONE_MINUS_SRC_ALPHA)
#define BLENDMODE_PREMULTIPLIEDALPHA	blendmode(ONE, ONE_MINUS_SRC_ALPHA)
#define BLENDMODE_ADDITIVE				blendmode(SRC_ALPHA, ONE)
#define BLENDMODE_SUBTRACTIVE			blendmode(ZERO, ONE_MINUS_SRC_COLOR)


// Garbage collection flags
#define gcFULL_CYCLE      0x0001
#define gcONE_STEP        0x0002
#define gcDESTROY_GARBAGE 0x0004
#define gcDETECT_GARBAGE  0x0008



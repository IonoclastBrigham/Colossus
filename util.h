// util.h
// Useful utility stuff that doesn't really go anywhere else
//
// Copyright ©2009 - 2010 Brigham Toskin
// This software is part of the Rogue-Opcode game framework. It is distributable
// under the terms of a modified MIT License. You should have received a copy of
// the license in the file LICENSE. If not, see:
// <http://code.google.com/p/rogue-op/wiki/LICENSE>
//
// Formatting:
//	80 cols ; tabwidth 4
////////////////////////////////////////////////////////////////////////////////


#pragma once

// mathy stuff
#define PI				3.141592653589793227020265931059839203954
#define THETA_RATIO		PI / 180.0000000000000000000000000000000000000
#define deg2rad(theta)	(THETA_RATIO * theta)

#define ROUND(f)			((int)(f+0.5))
#define ROUND_DIV(a, b)		ROUND(a / (float)b)
#define RAND_NORM()			(rand() / (float)RAND_MAX)

#define MIN(a, b)			(a <= b ? a : b) // default to first if equal
#define MAX(a, b)			(a >= b ? a : b)
#define SETMIN(var, val)	if(var > val) \
								var = val;
#define SETMAX(var, val)	if(var < val) \
								var = val;
#define CLAMP(var, r1, r2)	SETMAX(var, r1) ; SETMIN(var, r2) ;
#define WRAP_END(var, max)	while(var >= max) var -= max;
#define WRAP_START(var,max)	while(var < 0) var += max;

//
// NOTE: The following binary manipulation macros are NOT protable /////////////
//

// return the nth byte of multibyte value v
// numbering starts at offset 0
#define NBYTE(v,n)			((char*)(&v))[n]
#define NUBYTE(v,n)			((unsigned char*)(&v))[n]

// combine 4 bytes into a 32 bit target
#define UNITEBYTES(target,a,b,c,d)	\
			((char*)(&target))[0] = a; \
			((char*)(&target))[1] = b; \
			((char*)(&target))[2] = c; \
			((char*)(&target))[3] = d;

// convert a floating point value to a raw bitfield
#define RAWBITS(f)		( *((unsigned int*)(&f)) )

// convert a raw bitfield back to a float
#define FLOATBITS(r)	( *((float*)(&r)) )

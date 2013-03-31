///////////////////////////////////////////////////////////////////////////////
// RTPS
// Copyright 1996-2013, Michael T. Mayers
// Provided under the MIT License (see LICENSE.txt)
///////////////////////////////////////////////////////////////////////////////

#pragma once

///////////////////////////////////////////////////////////////////////////
//			bamdtypes.h
//			COMMON BinaryArtsMeDia Types
//			Michael T. Mayers
//			Binary Arts, Inc
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
// Common Defines

#define PI	3.14159265358979323846
#define PI2	6.2831853
#define NEGPI2 -6.2831853
#define DEG2RAD	0.017453293
#define RAD2DEG	57.29678

#ifndef	NULL
#define NULL	0
#endif

#define ZERO	0

#define NO	0
#define YES	1
#define FALSE	0
#define TRUE	1

#define BAD	1
#define GOOD	0
#define PASS	0
#define FAIL	1
#define ERR	1
#define NOERR	0

///////////////////////////////////////////////////////////////////////////
// Common Types

#ifdef IRIX
typedef unsigned long long int	    U64;
typedef signed long long int	    S64;
#endif
#ifdef WIN32
typedef unsigned __int64			U64;
typedef signed __int64				S64;		
#endif

typedef char			    		UBOOL;

typedef unsigned long int	    	U32;
typedef signed long int		    	S32;
typedef unsigned short int	    	U16;
typedef signed short int	    	S16;
typedef unsigned char		    	U8;
typedef signed char		    		S8;
typedef float			    		F32;
typedef double			    		F64;
typedef float			    		FLOAT;
typedef char *			    		STRING;
typedef void *			    		ADDRESS;

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
// metric conversion constants

#include "metric.h"

///////////////////////////////////////////////////////////////////////////////

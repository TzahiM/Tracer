/*!
  \file macross.h

  Created on: 19 αιεπ 2018
      \author Admin

Copyright (c) 2018
Provided as is according to MIT open source license
GIT repository: https://github.com/TzahiM/TestAbles.git
Tzahi Manistersky.

mailto:tzahimanmobile@gmail.com
+972(52)2947775


  \brief Exported definitions for macros_testables

---------------------------------------------------------------------------
1. GENERAL DESIGN DESCRIPTION:

2. DETAILED DESIGN DESCRIPTION:

3. DESIGN CONSIDERATIONS AND ALTERNATIVES:

4. MISCELLANEOUS:

=========================================================================*/
#ifndef ANY_APP_INCLUDES_MACROS_TESTABLES_H_
#define ANY_APP_INCLUDES_MACROS_TESTABLES_H_

// includes
#include "string.h" //for prototype of memset()
#include "TTypes.h"



//Constants

#define END_OF_LINE "\r\n"

#ifndef BIG_ENDIAN
#  define   LITTLE_ENDIAN 1234
#  define   BIG_ENDIAN    4321
#endif

#ifndef BYTE_ORDER

/* Test for a little-endian machine */
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define   BYTE_ORDER    LITTLE_ENDIAN
#else
#define   BYTE_ORDER    BIG_ENDIAN
#endif

#endif

/* Useful macros: */
#ifndef MIN
  #define  MIN(x,y)    ((x)  <  (y)   ?  (x)   :  (y))
#endif
#ifndef MAX
  #define  MAX(x,y)    ((x)  >  (y)   ?  (x)   :  (y))
#endif

#define CHECK_LIMIT( val, min, max )\
{                                   \
    if( val < min || val > max)     \
    {                               \
        REC_ERROR( val,min,max);    \
    }                               \
}


#define ZERO_X(mem_to_zero) memset( &mem_to_zero, 0, sizeof(mem_to_zero))


#define NUM_ARRAY_ELEMENTS( X ) ((int)sizeof(X)/(int)sizeof( X[0]))


#ifndef SWAP16
  #define SWAP16(X) ((((uint16_t)(X) & 0xFF00) >> 8) | (((uint16_t)(X) & 0x00FF) << 8))
#endif

#ifndef SWAP32
  #define SWAP32(X) ((((uint32_t)(X) & 0xFF000000U) >> 24) | \
                     (((uint32_t)(X) & 0x00FF0000U) >>  8) | \
                     (((uint32_t)(X) & 0x0000FF00U) <<  8) | \
                     (((uint32_t)(X) & 0x000000FFU) << 24))
#endif



#ifndef ROUND_UP
  #define ROUND_UP(x,align)     (((int) (x) + ((align) - 1)) & ~((align) - 1))
#endif
#ifndef ROUND_DOWN
  #define ROUND_DOWN(x, align)  ((int)(x) & ~((align) - 1))
#endif
#ifndef ALIGNED
  #define ALIGNED(x, align)     (((int)(x) & ((align) - 1)) == 0)
#endif

#if BYTE_ORDER == BIG_ENDIAN
#define IP_BYTES(a)            ((a)&0xFF) , (((a)>> 8)&0xFF), (((a)>>16)&0xFF) ,(((a)>>24)&0xFF)
#else
#define IP_BYTES(a)            (((a)>>24)&0xFF),(((a)>>16)&0xFF),(((a)>> 8)&0xFF),((a)&0xFF)
#endif

#define IPADDR(a,b,c,d)       ((((UINT4)(a)&0xFF)<<24)|(((UINT4)(b)&0xFF)<<16)|(((UINT4)(c)&0xFF)<<8)|((UINT4)(d)&0xFF))

#define NUMBER_OF_PATH_BYTES  11

#define REC_ERROR( val,min,max)\
{\
    TM_DebugASSERT( __FILE__  + NUMBER_OF_PATH_BYTES, __LINE__ , (int)val,(int)min,(int)max);\
}


#define TEST_NOT_EQUAL( a , b)  \
{                               \
    if( (a) == (b))             \
    {                           \
        REC_ERROR(a,b, 0 );     \
    }                           \
}

#define TEST_EQUAL( a , b)\
{                             \
    if( (a) != (b))           \
    {                         \
        REC_ERROR(a,b,0);     \
    }                         \
}

//when porting, implement your own print function
#define DEBUG_OUTPUT printf

//Types

#ifdef __cplusplus
extern "C" {
#endif
// Exported functions

int cli_printf(const char  *format, ...);

void TM_DebugASSERT(const char * FunctionName,
        int Line  ,
        int Val   ,
        int Min   ,
        int Max );



#ifdef __cplusplus
}
#endif


#endif /* ANY_APP_INCLUDES_MACROS_TESTABLES_H_ */

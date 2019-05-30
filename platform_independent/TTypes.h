/*!
  \file TTypes.h

  Created on: 30 במאי 2019
  \author     Admin

 Copyright (c) 2019 Tzahi Manistersky tzahimanmobile@gmail.com +972(52)2947775

 \brief Exported definitions for TTypes

---------------------------------------------------------------------------
1. GENERAL DESIGN DESCRIPTION:

2. DETAILED DESIGN DESCRIPTION:

3. DESIGN CONSIDERATIONS AND ALTERNATIVES:

4. MISCELLANEOUS:

=========================================================================*/
#ifndef TTYPES_H_
#define TTYPES_H_

// ===========================< Header Files >============================


//=======================< Constant Definitions >=======================
#define TU8   unsigned char
#define TU16  unsigned short
#define TU32  unsigned int
#define TU64  unsigned long
#define TU128 unsigned long long

#define TI8   signed char
#define TI16  signed short
#define TI32  signed int
#define TI64  signed long
#define TI128 signed long long

#define TU32 unsigned int
#define TU32 unsigned int
#define TI8  signed char

//=========================< Type Declaration >==========================

#pragma pack() // Add here the requested memory bytes alignments


#pragma pack() //revert to system default memory bytes alignments

#ifdef __cplusplus
extern "C" {
#endif
// ====================< Global Functions Prototype >=====================


// ===================< Global Variable Declaration >=====================
#ifdef TTypes_UNFOLD
#else
#endif

#ifdef __cplusplus
}
#endif

#endif /* TTYPES_H_ */

//End of TTypes.h file

/*!
  \file tracer.h

  Created on: 13 בדצמ 2018
  \author     Tzahi Manistersky

Copyright (c) 2018
Provided as is according to MIT open source license
Tzahi Manistersky.

mailto:tzahimanmobile@gmail.com
+972(52)2947775

 \brief Exported definitions for tracer

---------------------------------------------------------------------------
1. GENERAL DESIGN DESCRIPTION:

2. DETAILED DESIGN DESCRIPTION:

3. DESIGN CONSIDERATIONS AND ALTERNATIVES:

4. MISCELLANEOUS:

In this reference implementation the TRACE duration is 12 t0 14 microsecond (see in tracer.c)
=========================================================================*/
#ifndef SOURCES_TRACER_H_
#define SOURCES_TRACER_H_

// ===========================< Header Files >============================
#include "TTypes.h"


//=======================< Constant Definitions >=======================
#define TRACING 1

#if TRACING



//!< this macro is used for save a set of traced values into the tracing memory
#define TRACE( string, p1,p2,p3)\
{\
    register s_trace* p_next_trace = &p_tracer->traces_array[p_tracer->next_trace_index & NUM_TRACE_MASK];\
    p_next_trace->timestamp = tracer_get_timestamp() ;                                                    \
    p_next_trace->p_latest_string = string           ;                                                    \
    p_next_trace->parameter_1     = (TU32)p1     ;                                                    \
    p_next_trace->parameter_2     = (TU32)p2     ;                                                    \
    p_next_trace->parameter_3     = (TU32)p3     ;                                                    \
    p_tracer->next_trace_index += p_tracer->increment;                                                    \
}

#else

#define TRACE( string, p1,p2,p3)

#endif

#define TST_IO_ON  GPIO_DRV_ClearPinOutput(TP_192)
#define TST_IO_OFF GPIO_DRV_SetPinOutput(TP_192)

//=========================< Type Declaration >==========================

#pragma pack(4) // Add here the requested memory bytes alignments

typedef struct
{
    TU32       timestamp      ;
    const TI8* p_latest_string;
    TU32    parameter_1    ;
    TU32    parameter_2    ;
    TU32    parameter_3    ;
}s_trace;

#define MAX_NUM_TRACE  0x200 //! should be a power of 2
#define NUM_TRACE_MASK 0x1FF //! should be a power of 2 - 1

typedef struct
{
    s_trace  traces_array[MAX_NUM_TRACE];
    TU32 next_trace_index;
    TU8  increment;
}s_tracer;

#pragma pack() //revert to system default memory bytes alignments


#ifdef __cplusplus
extern "C" {
#endif
// ====================< Global Functions Prototype >=====================

void tracer_print_all();

void tracer_set_enabling( int is_enabled);

TU32 tracer_get_timestamp();//platform specific timestamping method

// ===================< Global Variable Declaration >=====================
#ifdef tracer_UNFOLD
s_tracer g_trace =
{
        0
};
s_tracer* p_tracer = &g_trace;
#else
extern s_tracer* p_tracer;
#endif

#ifdef __cplusplus
}
#endif

#endif /* SOURCES_TRACER_H_ */

//End of tracer.h file

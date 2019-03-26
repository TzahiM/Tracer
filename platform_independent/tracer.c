/*!
  \file tracer.c

  Created on: 13 בדצמ 2018
  \author     Tzahi Manistersky

Copyright (c) 2018
Provided as is according to MIT open source license
Tzahi Manistersky.

mailto:tzahimanmobile@gmail.com
+972(52)2947775
 
 \brief Implementation for tracer
---------------------------------------------------------------------------
1. GENERAL DESIGN DESCRIPTION:

2. DETAILED DESIGN DESCRIPTION:

3. DESIGN CONSIDERATIONS AND ALTERNATIVES:

4. MISCELLANEOUS:


tracer performance can be measured this way:
        tracer_set_enabling( 0);
        tracer_set_enabling( 1);
        TRACE( __FUNCTION__, __LINE__ , 0, 0);
        TRACE( __FUNCTION__, __LINE__ , 0, 0);
        TRACE( __FUNCTION__, __LINE__ , 0, 0);
        TRACE( __FUNCTION__, __LINE__ , 0, 0);
        TRACE( __FUNCTION__, __LINE__ , 0, 0);
        TRACE( __FUNCTION__, __LINE__ , 0, 0);
        TRACE( __FUNCTION__, __LINE__ , 0, 0);
        TRACE( __FUNCTION__, __LINE__ , 0, 0);
        TRACE( __FUNCTION__, __LINE__ , 0, 0);
        TRACE( __FUNCTION__, __LINE__ , 0, 0);
        TRACE( __FUNCTION__, __LINE__ , 0, 0);
        TRACE( __FUNCTION__, __LINE__ , 0, 0);
        TRACE( __FUNCTION__, __LINE__ , 0, 0);
        TRACE( __FUNCTION__, __LINE__ , 0, 0);
        TRACE( __FUNCTION__, __LINE__ , 0, 0);
        TRACE( __FUNCTION__, __LINE__ , 0, 0);
        TRACE( __FUNCTION__, __LINE__ , 0, 0);
        TRACE( __FUNCTION__, __LINE__ , 0, 0);
        TRACE( __FUNCTION__, __LINE__ , 0, 0);
        TRACE( __FUNCTION__, __LINE__ , 0, 0);
        TRACE( __FUNCTION__, __LINE__ , 0, 0);
        TRACE( __FUNCTION__, __LINE__ , 0, 0);
        TRACE( __FUNCTION__, __LINE__ , 0, 0);
        TRACE( __FUNCTION__, __LINE__ , 0, 0);
        TRACE( __FUNCTION__, __LINE__ , 0, 0);
        TRACE( __FUNCTION__, __LINE__ , 0, 0);
        TRACE( __FUNCTION__, __LINE__ , 0, 0);
        TRACE( __FUNCTION__, __LINE__ , 0, 0);
        TRACE( __FUNCTION__, __LINE__ , 0, 0);
        tracer_set_enabling( 0);
        tracer_print_all();


        cli_printf( "PIT_RD_CVAL duration is %d microseconds %d %d" END_OF_LINE,
                (((~PIT_RD_CVAL(((PIT_Type *)PIT_BASE), FSL_PIT1_CHANNEL)) >> 1) - ((~PIT_RD_CVAL(((PIT_Type *)PIT_BASE), FSL_PIT1_CHANNEL)) >> 1)),
                ((~PIT_RD_CVAL(((PIT_Type *)PIT_BASE), FSL_PIT1_CHANNEL)) >> 1),
                ((~PIT_RD_CVAL(((PIT_Type *)PIT_BASE), FSL_PIT1_CHANNEL)) >> 1)
        );
        cli_printf( "tracer_get_timestamp() duration is %d microseconds " END_OF_LINE, tracer_get_timestamp() - tracer_get_timestamp());

Current measure is:
2147283669:(2147283669)    682      0      0 command_handler_iteration line 682
2147283746:(       77)    683      0      0 command_handler_iteration line 683
2147283758:(       12)    684      0      0 command_handler_iteration line 684
2147283770:(       12)    685      0      0 command_handler_iteration line 685
2147283783:(       13)    686      0      0 command_handler_iteration line 686
2147283795:(       12)    687      0      0 command_handler_iteration line 687
2147283808:(       13)    688      0      0 command_handler_iteration line 688
2147283820:(       12)    689      0      0 command_handler_iteration line 689
2147283833:(       13)    690      0      0 command_handler_iteration line 690
2147283846:(       13)    691      0      0 command_handler_iteration line 691
2147283858:(       12)    692      0      0 command_handler_iteration line 692
2147283870:(       12)    693      0      0 command_handler_iteration line 693
2147283883:(       13)    694      0      0 command_handler_iteration line 694
2147283896:(       13)    695      0      0 command_handler_iteration line 695
2147283909:(       13)    696      0      0 command_handler_iteration line 696
2147283921:(       12)    697      0      0 command_handler_iteration line 697
2147283933:(       12)    698      0      0 command_handler_iteration line 698
2147283946:(       13)    699      0      0 command_handler_iteration line 699
2147283959:(       13)    700      0      0 command_handler_iteration line 700
2147283971:(       12)    701      0      0 command_handler_iteration line 701
2147283983:(       12)    702      0      0 command_handler_iteration line 702
2147283997:(       14)    703      0      0 command_handler_iteration line 703
2147284009:(       12)    704      0      0 command_handler_iteration line 704
2147284021:(       12)    705      0      0 command_handler_iteration line 705
2147284034:(       13)    706      0      0 command_handler_iteration line 706
2147284047:(       13)    707      0      0 command_handler_iteration line 707
2147284060:(       13)    708      0      0 command_handler_iteration line 708
2147284072:(       12)    709      0      0 command_handler_iteration line 709
2147284084:(       12)    710      0      0 command_handler_iteration line 710
PIT_RD_CVAL duration is -1 microseconds 2147419263 2147419264
tracer_get_timestamp() duration is -4 microseconds



=========================================================================*/


#define tracer_UNFOLD
// ===========================< Header Files >============================

#include "tracer.h"
#include "macros.h"

// ==================< Private Constant Definition >======================

// =======================< Private Data Types >===========================

// ====================< Private Data Definition >========================

// ===================< Private Functions Implementation >=====================
TU32 prev_ts = 0;//!< used for calculating dime differences between current and previous trace
/*!
 * print of a single trace in ascii format
 * @param p_trace_to_print
 */
static void tracer_print_single_trace(s_trace* p_trace_to_print)
{
    if (p_trace_to_print == NULL || p_trace_to_print->p_latest_string == 0)
    {
        return;
    }//end of if (p_trace_to_print == NULL || p_trace_to_print->p_latest_string == 0))

    //!< calculating a wraparound according to timer rate and maximum count value
    if( prev_ts > p_trace_to_print->timestamp)
    {
        prev_ts -= 200000;
    }
    DEBUG_OUTPUT( "%9u:(%9u) %6d %6d %6d %s line %d" END_OF_LINE,
                    p_trace_to_print->timestamp                 ,
                    p_trace_to_print->timestamp - prev_ts       ,
                    p_trace_to_print->parameter_1               ,
                    p_trace_to_print->parameter_2               ,
                    p_trace_to_print->parameter_3               ,
                    p_trace_to_print->p_latest_string           ,
                    p_trace_to_print->parameter_1
    );

    prev_ts = p_trace_to_print->timestamp;

}
// ====================< Public Function Implementation >=====================

/*!
 * iterate through all traces and print them
 */
void tracer_print_all()
{
    //!< if there had already been a wrap around whithin traces array we start with the next trace to use  which is the first known traced entry
    if ((p_tracer->next_trace_index & NUM_TRACE_MASK) != 0)
    {
        for (int var = (p_tracer->next_trace_index + 1) & NUM_TRACE_MASK; var < NUM_ARRAY_ELEMENTS(p_tracer->traces_array); var++)
        {
            tracer_print_single_trace( &p_tracer->traces_array[var]);
        }//end of for (var = 0; var < max; var++)
    }//end of if ((p_tracer->next_trace_index & NUM_TRACE_MASK) != 0))


    //!< iterate from the begining of the tracs array
    for (int var = 0 ; var < (p_tracer->next_trace_index  & NUM_TRACE_MASK) ; var++)
    {
        tracer_print_single_trace( &p_tracer->traces_array[var]);
    }//end of for (var = 0; var < max; var++)
}

/*!
 * start or stop tracing
 * good idea is to start before a posisble event and stop after the first encountered problem
 * @param is_enabled
 */
void tracer_set_enabling( int is_enabled)
{
    if (is_enabled)
    {
        p_tracer->next_trace_index = 0;
        p_tracer->increment = 1;
    }//end of if (condition))
    else
    {
        p_tracer->increment = 0;
    }

}


//End of tracer.c file

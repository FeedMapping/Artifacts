/* TA-LIB Copyright (c) 1999-2003, Mario Fortier
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or
 * without modification, are permitted provided that the following
 * conditions are met:
 *
 * - Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in
 *   the documentation and/or other materials provided with the
 *   distribution.
 *
 * - Neither name of author nor the names of its contributors
 *   may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * REGENTS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* List of contributors:
 *
 *  Initial  Name/description
 *  -------------------------------------------------------------------
 *  MF       Mario Fortier
 *
 *
 * Change history:
 *
 *  MMDDYY BY   Description
 *  -------------------------------------------------------------------
 *  112400 MF   Template creation.
 *  052603 MF   Adapt code to compile with .NET Managed C++
 *
 */

/**** START GENCODE SECTION 1 - DO NOT DELETE THIS LINE ****/
/* All code within this section is automatically
 * generated by gen_code. Any modification will be lost
 * next time gen_code is run.
 */

#if defined( _MANAGED )
   #using <mscorlib.dll>
   #include "Core.h"
   namespace TA { namespace Lib {
#else
   #include <string.h>
   #include <math.h>
   #include "ta_func.h"
#endif

#ifndef TA_UTILITY_H
   #include "ta_utility.h"
#endif

#ifndef TA_MEMORY_H
   #include "ta_memory.h"
#endif

#if defined( _MANAGED )
int Core::RSI_Lookback( int           optInTimePeriod_0 )  /* From 2 to TA_INTEGER_MAX */

#else
int TA_RSI_Lookback( int           optInTimePeriod_0 )  /* From 2 to TA_INTEGER_MAX */

#endif
/**** END GENCODE SECTION 1 - DO NOT DELETE THIS LINE ****/
{
   /* insert lookback code here. */
   int retValue;

   retValue = optInTimePeriod_0 + TA_Globals->unstablePeriod[TA_FUNC_UNST_RSI];
   if( TA_Globals->compatibility == TA_COMPATIBILITY_METASTOCK )
      retValue--;

   return retValue;
}

/**** START GENCODE SECTION 2 - DO NOT DELETE THIS LINE ****/
/*
 * TA_RSI - Relative Strength Index
 * 
 * Input  = double
 * Output = double
 * 
 * Optional Parameters
 * -------------------
 * optInTimePeriod_0:(From 2 to TA_INTEGER_MAX)
 *    Number of period
 * 
 * 
 */


#if defined( _MANAGED )
enum TA_RetCode Core::RSI( int    startIdx,
                           int    endIdx,
                           double       inReal_0 __gc [],
                           int           optInTimePeriod_0, /* From 2 to TA_INTEGER_MAX */
                           [OutAttribute]Int32 *outBegIdx,
                           [OutAttribute]Int32 *outNbElement,
                           double        outReal_0 __gc [] )
#else
TA_RetCode TA_RSI( int    startIdx,
                   int    endIdx,
                   const double inReal_0[],
                   int           optInTimePeriod_0, /* From 2 to TA_INTEGER_MAX */
                   int          *outBegIdx,
                   int          *outNbElement,
                   double        outReal_0[] )
#endif
/**** END GENCODE SECTION 2 - DO NOT DELETE THIS LINE ****/
{
   /* Insert local variables here. */
   int outIdx;

   int today, lookbackTotal, unstablePeriod, i;
   double prevGain, prevLoss, prevValue, savePrevValue;
   double tempValue1, tempValue2;

/**** START GENCODE SECTION 3 - DO NOT DELETE THIS LINE ****/

#ifndef TA_FUNC_NO_RANGE_CHECK

   /* Validate the requested output range. */
   if( startIdx < 0 )
      return TA_OUT_OF_RANGE_START_INDEX;
   if( (endIdx < 0) || (endIdx < startIdx))
      return TA_OUT_OF_RANGE_END_INDEX;

   /* Validate the parameters. */
   if( !inReal_0 ) return TA_BAD_PARAM;
   /* min/max are checked for optInTimePeriod_0. */
   if( (int)optInTimePeriod_0 == TA_INTEGER_DEFAULT )
      optInTimePeriod_0 = 14;
   else if( ((int)optInTimePeriod_0 < 2) || ((int)optInTimePeriod_0 > 2147483647) )
      return TA_BAD_PARAM;

   if( outReal_0 == NULL )
      return TA_BAD_PARAM;

#endif /* TA_FUNC_NO_RANGE_CHECK */

/**** END GENCODE SECTION 3 - DO NOT DELETE THIS LINE ****/

   /* Insert TA function code here. */

   /* The following algorithm is base on the original 
    * work from Wilder's and shall represent the
    * original idea behind the classic RSI.
    *
    * Metastock is starting the calculation one price
    * bar earlier. To make this possible, they assume
    * that the very first bar will be identical to the
    * previous one (no gain or loss).
    */

   *outBegIdx    = 0;
   *outNbElement = 0;
   
   /* Adjust startIdx to account for the lookback period. */
   lookbackTotal = TA_RSI_Lookback( optInTimePeriod_0 );

   if( startIdx < lookbackTotal )
      startIdx = lookbackTotal;

   /* Make sure there is still something to evaluate. */
   if( startIdx > endIdx )
      return TA_SUCCESS;

   outIdx = 0; /* Index into the output. */

   /* Trap special case where the period is '1'.
    * In that case, just copy the input into the
    * output for the requested range (as-is !)
    */
   if( optInTimePeriod_0 == 1 )
   {
      *outBegIdx = startIdx;
      i = (endIdx-startIdx)+1;
      *outNbElement = i;
      ARRAY_MEMMOVE( outReal_0, 0, inReal_0, startIdx, i );
      return TA_SUCCESS;
   }

   /* Accumulate Wilder's "Average Gain" and "Average Loss" 
    * among the initial period.
    */
   today = startIdx-lookbackTotal;
   prevValue = inReal_0[today];

   unstablePeriod = TA_Globals->unstablePeriod[TA_FUNC_UNST_RSI];

   /* If there is no unstable period,
    * calculate the 'additional' initial
    * price bar who is particuliar to
    * metastock.
    * If there is an unstable period,
    * no need to calculate since this
    * first value will be surely skip.
    */
   if( (unstablePeriod == 0) && 
       (TA_Globals->compatibility == TA_COMPATIBILITY_METASTOCK))
   {
      /* Preserve prevValue because it may get 
       * overwritten by the output.
       *(because output ptr could be the same as input ptr).
       */
      savePrevValue = prevValue;

      /* No unstable period, so must calculate first output
       * particular to Metastock.
       * (Metastock re-use the first price bar, so there
       *  is no loss/gain at first. Beats me why they
       *  are doing all this).
       */
      prevGain = 0.0;
      prevLoss = 0.0;
      for( i=optInTimePeriod_0; i > 0; i-- )
      {
         tempValue1 = inReal_0[today++];
         tempValue2 = tempValue1 - prevValue;
         prevValue  = tempValue1;
         if( tempValue2 < 0 )
            prevLoss -= tempValue2;
         else
            prevGain += tempValue2;
      }


      tempValue1 = prevLoss/optInTimePeriod_0;
      tempValue2 = prevGain/optInTimePeriod_0;

      /* Write the output. */
      outReal_0[outIdx++] = 100*(tempValue2/(tempValue2+tempValue1));

      /* Are we done? */
      if( today > endIdx )
      {
         *outBegIdx    = startIdx;
         *outNbElement = outIdx;
         return TA_SUCCESS;
      }

      /* Start over for the next price bar. */
      today -= optInTimePeriod_0;
      prevValue = savePrevValue;
   }


   /* Remaining of the processing is identical
    * for both Classic calculation and Metastock.
    */
   prevGain = 0.0;
   prevLoss = 0.0;
   today++;
   for( i=optInTimePeriod_0; i > 0; i-- )
   {
      tempValue1 = inReal_0[today++];
      tempValue2 = tempValue1 - prevValue;
      prevValue  = tempValue1;
      if( tempValue2 < 0 )
         prevLoss -= tempValue2;
      else
         prevGain += tempValue2;
   }

   
   /* Subsequent prevLoss and prevGain are smoothed
    * using the previous values (Wilder's approach).
    *  1) Multiply the previous by 'period-1'. 
    *  2) Add today value.
    *  3) Divide by 'period'.
    */
   prevLoss /= optInTimePeriod_0;
   prevGain /= optInTimePeriod_0;

   /* Often documentation present the RSI calculation as follow:
    *    RSI = 100 - (100 / 1 + (prevGain/prevLoss))
    *
    * The following is equivalent:
    *    RSI = 100 * (prevGain/(prevGain+prevLoss))
    *
    * The second equation is used here for speed optimization.
    */
   if( today > startIdx )
      outReal_0[outIdx++] = 100.0*(prevGain/(prevGain+prevLoss));
   else
   {
      /* Skip the unstable period. Do the processing 
       * but do not write it in the output.
       */   
      while( today < startIdx )
      {
         tempValue1 = inReal_0[today];
         tempValue2 = tempValue1 - prevValue;
         prevValue  = tempValue1;

         prevLoss *= (optInTimePeriod_0-1);
         prevGain *= (optInTimePeriod_0-1);
         if( tempValue2 < 0 )
            prevLoss -= tempValue2;
         else
            prevGain += tempValue2;

         prevLoss /= optInTimePeriod_0;
         prevGain /= optInTimePeriod_0;

         today++;
      }
   }

   /* Unstable period skipped... now continue
    * processing if needed.
    */
   while( today <= endIdx )
   {
      tempValue1 = inReal_0[today++];
      tempValue2 = tempValue1 - prevValue;
      prevValue  = tempValue1;

      prevLoss *= (optInTimePeriod_0-1);
      prevGain *= (optInTimePeriod_0-1);
      if( tempValue2 < 0 )
         prevLoss -= tempValue2;
      else
         prevGain += tempValue2;

      prevLoss /= optInTimePeriod_0;
      prevGain /= optInTimePeriod_0;

      outReal_0[outIdx++] = 100.0*(prevGain/(prevGain+prevLoss));
   }

   *outBegIdx = startIdx;
   *outNbElement = outIdx;

   return TA_SUCCESS;
}


/**** START GENCODE SECTION 4 - DO NOT DELETE THIS LINE ****/
#if defined( _MANAGED )
   }} // Close namespace TA.Lib
#endif
/**** END GENCODE SECTION 4 - DO NOT DELETE THIS LINE ****/


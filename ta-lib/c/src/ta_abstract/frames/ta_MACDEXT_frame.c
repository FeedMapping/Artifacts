/* TA-LIB Copyright (c) 1999-2002, Mario Fortier
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

/* DO NOT MODIFY this file.
 * This file is automatically generated by gen_Code.
 *
 * The function define in this file allows to have a consistent
 * framework for calling all the TA function through
 * the TA_CallFunc mechanism.
 *
 * See "ta_abstract.h"
 */

#ifndef TA_FUNC_H
   #include "ta_func.h"
#endif

#ifndef TA_FRAME_PRIV_H
   #include "ta_frame_priv.h"
#endif

#ifndef TA_FRAME_H
   #include "ta_frame.h"
#endif

/* NEVER CALL directly this function! Use TA_CallFunc. */
 
TA_RetCode TA_MACDEXT_FramePP( const TA_ParamHolderPriv *params,
                          TA_Integer            startIdx,
                          TA_Integer            endIdx,
                          TA_Integer           *outBegIdx,
                          TA_Integer           *outNbElement )

{
   return TA_MACDEXT(
                startIdx,
                endIdx,
                params->in[0].data.inReal, /* inReal_0 */
                params->optIn[0].data.optInInteger, /* optInFastPeriod_0 */
                params->optIn[1].data.optInInteger, /* optInFastMAType_1 */
                params->optIn[2].data.optInInteger, /* optInSlowPeriod_2 */
                params->optIn[3].data.optInInteger, /* optInSlowMAType_3 */
                params->optIn[4].data.optInInteger, /* optInSignalPeriod_4 */
                params->optIn[5].data.optInInteger, /* optInSignalMAType_5 */
                outBegIdx, 
                outNbElement, 
                params->out[0].data.outReal, /*  outRealMACD_0 */
                params->out[1].data.outReal, /*  outRealMACDSignal_1 */
                params->out[2].data.outReal /*  outRealMACDHist_2 */ );
}

/***************
 * End of File *
 ***************/


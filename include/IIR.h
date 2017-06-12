// @(#)signal:$Id$
// Author: Jeremy Lopez   03/06/2017

/*************************************************************************
 * Copyright (C) 2017, Jeremy Lopez                                      *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see LICENSE.                                  *
 *                                                                       *
 *************************************************************************/
#ifndef SIGNAL_TDISCRETEFILTER_H
#define SIGNAL_TDISCRETEFILTER_H

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TDiscreteFilter                                                      //
//                                                                      //
// Base class for discrete filters. Takes in a double array and         //
// and outputs a smoothed array and an array of residuals.              //
//                                                                      //
//////////////////////////////////////////////////////////////////////////


#include <Rtypes.h>
#include <vector>

namespace signal
{
   class TDiscreteFilter
   {
      public:

         enum {
            kNoOffset=-1,
            kMiddleOffset = -2,
            kMaxOffset=-3
         };

         TDiscreteFilter(){}

         virtual ~TDiscreteFilter(){}

         virtual int GetOutputSize(Int_n inputsize){ return inputsize; };

         virtual void Smooth(Int_t inputsize, const Double_t input[], 
                             Double_t output[], Double_t residual[]=nullptr,
                             Int_t offset=kMiddleOffset);

         virtual void Smooth(const std::vector<Double_t>& input, 
                             std::vector<Double_t>& output, 
                             std::vector<Double_t>& residual,
                             Int_t offset=kMaxOffset);

   };

}

#endif

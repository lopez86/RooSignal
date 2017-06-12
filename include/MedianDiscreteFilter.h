// @(#)signal:$Id$
// Author: Jeremy Lopez   03/06/2017

/*************************************************************************
 * Copyright (C) 2017, Jeremy Lopez                                      *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see LICENSE.                                  *
 *                                                                       *
 *************************************************************************/
#ifndef SIGNAL_MEDIANDISCFILTER_H
#define SIGNAL_MEDIANDISCFILTER_H

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// MedianDiscreteFilter                                                     //
//                                                                      //
// Discrete median filter. Takes in a double array and                  //
// and outputs a smoothed array and an array of residuals.              //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include <Rtypes.h>
#include "DiscreteFilter.h"
#include <vector>

namespace signal
{
   class MedianDiscreteFilter : public DiscreteFilter
   {

      protected:
         Int_t fFilterSize;

      public:

         MedianDiscreteFilter(Int_t halfwidth=2) : fFilterSize(halfwidth*2+1) {}

         virtual ~MedianDiscreteFilter(){}

         virtual int GetOutputSize(Int_t inputsize)
                     { return inputsize - fFilterSize + 1; };

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

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
// DiscreteFilter                                                      //
//                                                                      //
// Base class for discrete filters. Takes in a double array and         //
// outputs a smoothed array and an array of residuals.                  //
//                                                                      //
//////////////////////////////////////////////////////////////////////////


#include <Rtypes.h>
#include <vector>

namespace signal
{
   class DiscreteFilter
   {
      public:

         enum {
            kNoOffset=-1,
            kMiddleOffset = -2,
            kMaxOffset=-3
         };

         DiscreteFilter(){}

         virtual ~DiscreteFilter(){}

         virtual Int_t GetOutputSize(const Int_t inputsize) const { return inputsize; };

         virtual void Smooth(const Int_t inputsize, const Double_t input[], 
                             Double_t output[], Double_t residual[]=nullptr,
                             Int_t offset=kMiddleOffset) const;

         virtual void Smooth(const std::vector<Double_t>& input, 
                             std::vector<Double_t>& output, 
                             std::vector<Double_t>& residual,
                             Int_t offset=kMaxOffset) const;

   };

}

#endif
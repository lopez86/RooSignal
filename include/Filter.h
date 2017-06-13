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
// Filter                                                      //
//                                                                      //
// Base class for discrete filters. Takes in a double array and         //
// outputs a smoothed array and an array of residuals.                  //
//                                                                      //
//////////////////////////////////////////////////////////////////////////


#include <Rtypes.h>
#include <vector>

namespace signal
{
   class Filter
   {
      public:

         enum {
            kNoOffset=-1,
            kMiddleOffset = -2,
            kMaxOffset=-3
         };

         Filter(){}

         virtual ~Filter(){}

         virtual Int_t GetOutputSize(Int_t inputsize) const { return inputsize; };

         virtual void Smooth(Int_t inputsize, const Double_t inputx[],
                             const Double_t input[], Double_t output[], 
                             Double_t residual[]=nullptr) const;

         virtual void Smooth(const std::vector<Double_t>& inputx,
                             const std::vector<Double_t>& inputy, 
                             std::vector<Double_t>& output, 
                             std::vector<Double_t>& residual,
                             Bool_t set_residual=false) const;

   };

}

#endif

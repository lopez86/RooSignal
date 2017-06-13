// @(#)signal:$Id$
// Author: Jeremy Lopez   03/06/2017

/*************************************************************************
 * Copyright (C) 2017, Jeremy Lopez                                      *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see LICENSE.                                  *
 *                                                                       *
 *************************************************************************/
#ifndef SIGNAL_MEDIANFILTER_H
#define SIGNAL_MEDIANFILTER_H

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// MedianFilter                                                     //
//                                                                      //
// Discrete median filter. Takes in a double array and                  //
// and outputs a smoothed array and an array of residuals.              //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include <Rtypes.h>
#include "Filter.h"
#include <vector>

namespace signal
{
   class MedianFilter : public Filter
   {

      protected:
         Int_t fFilterSize;
         Int_t fOffset;

      public:

         MedianDiscreteFilter(Int_t halfwidth=2) : fFilterSize(halfwidth*2+1) {}

         virtual ~MedianFilter(){}

         virtual int GetOutputSize(Int_t inputsize)
                     { return inputsize - fFilterSize + 1; };

         virtual void Smooth(Int_t inputsize, const Double_t inputx[], 
                             const Double_t inputy[],Double_t output[], 
                             Double_t residual[]=nullptr);

         virtual void Smooth(const std::vector<Double_t>& inputx, 
                             const std::vector<Double_t>& inputy, 
                             std::vector<Double_t>& output, 
                             std::vector<Double_t>& residual,
                             Bool_t set_residual);

   };

}

#endif

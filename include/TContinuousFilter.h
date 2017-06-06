// @(#)signal:$Id$
// Author: Jeremy Lopez   03/06/2017

/*************************************************************************
 * Copyright (C) 2017, Jeremy Lopez                                      *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see LICENSE.                                  *
 *                                                                       *
 *************************************************************************/
#ifndef SIGNAL_TCONTINUOUSFILTER_H
#define SIGNAL_TCONTINUOUSFILTER_H

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TContinuousFilter                                                    //
//                                                                      //
// Base class for continous filters. Takes in a double array and        //
// and outputs a smoothed array and an array of residuals.              //
// Can also output the smoothed value at any real value.                //
//                                                                      //
//////////////////////////////////////////////////////////////////////////


#include <Rtypes.h>
#include <vector>

namespace signal
{
   class TContinuousFilter
   {
      public:

         TContinuousFilter(){}

         virtual ~TDiscreteFilter(){}

         virtual Int_t GetOutputSize(Int_n inputsize) const { return inputsize; };

         virtual void Smooth(const Int_t inputsize, const Double_t input[], 
                             Double_t output[], Double_t residual[]=nullptr) const;

         virtual void Smooth(const std::vector<Double_t>& input, 
                             std::vector<Double_t>& output, 
                             std::vector<Double_t>& residual) const;

         virtual Double_t Calculate(const Int_t inputsize, const Double_t input[], Double_t x) const{return 0;}
         virtual Double_t Calculate(const Int_t inputsize, const std::vector<Double_t>& input[], Double_t x) const{return 0;}
 
   };

}

#endif

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
// ContinuousFilter                                                     //
//                                                                      //
// Base class for continuous filters. Takes in a double array and       //
// and outputs a smoothed array and an array of residuals.              //
// Here I define a continuous filter as one where the                   //
// Can also output the smoothed value at any real value.                //
//                                                                      //
//////////////////////////////////////////////////////////////////////////


#include <Rtypes.h>
#include <vector>

namespace signal
{
   class ContinuousFilter : public Filter
   {
      public:

         ContinuousFilter(){}

         virtual ~ContinuousFilter(){}

         virtual Int_t GetOutputSize(Int_t inputsize) const { return inputsize; };

         virtual void Smooth(Int_t inputsize,const Double_t inputx[],
                             const Double_t inputy[],Double_t output[], 
                             Double_t residual[]=nullptr) const;

         virtual void Smooth(const std::vector<Double_t>& inputx, 
                             const std::vector<Double_t>& inputy, 
                             std::vector<Double_t>& output, 
                             std::vector<Double_t>& residual, 
                             Bool_t set_residual=false) const;

         virtual Double_t Calculate(const Int_t inputsize, 
                                    const Double_t inputx[], 
                                    const Double_t inputy[], 
                                    Double_t x) const{return 0;}

         virtual Double_t Calculate(const std::vector<Double_t>& inputx, 
                                    const std::vector<Double_t>& inputy,
                                    Double_t x) const{return 0;}
   };

}

#endif

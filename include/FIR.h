// @(#)signal:$Id$
// Author: Jeremy Lopez   03/06/2017

/*************************************************************************
 * Copyright (C) 2017, Jeremy Lopez                                      *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see LICENSE.                                  *
 *                                                                       *
 *************************************************************************/
#ifndef SIGNAL_FIR_H
#define SIGNAL_FIR_H

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// FIR                                                                 //
//                                                                      //
// Class for finite impulse response filters. Takes in a double array   //
// and outputs a smoothed array and an array of residuals.              //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include "DiscreteFilter.h"

namespace signal
{
   class FIR : public DiscreteFilter
   {

      protected:

         std::vector<Double_t> fCoeffs;

      public:

         FIR();

         virtual ~FIR(){}

         virtual int GetOutputSize(Int_t inputsize)
                     { return inputsize - fCoeffs.size() + 1; };

         virtual void Smooth(Int_t inputsize, const Double_t input[], 
                             Double_t output[], Double_t residual[]=nullptr,
                             Int_t offset=kMiddleOffset);

         virtual void Smooth(const std::vector<Double_t>& input, 
                             std::vector<Double_t>& output, 
                             std::vector<Double_t>& residual,
                             Int_t offset=kMiddleOffset);

         void TransferFunction(Double_t re, Double_t im, Double_t& zr, 
                          Double_t& zi) const;
         Double_t Power(Double_t re, Double_t im=0) const;
         Double_t Magnitude(Double_t re, Double_t im=0) const;
         Double_t PhaseShift(Double_t re, Double_t im=0) const;

   };

}

#endif

// @(#)signal:$Id$
// Author: Jeremy Lopez   03/06/2017

/*************************************************************************
 * Copyright (C) 2017, Jeremy Lopez                                      *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see LICENSE.                                  *
 *                                                                       *
 *************************************************************************/
#ifndef SIGNAL_IIR_H
#define SIGNAL_IIR_H

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
   class IIR
   {

      protected:
         std::vector<Double_t> fCoeffs;
         std::vector<Double_t> fCoeffsDenom;

      public:

         IIR(){}

         virtual ~IIR(){}

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

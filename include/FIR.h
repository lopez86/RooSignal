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

#include "Filter.h"

namespace signal
{
   class FIR : public Filter
   {

      protected:

         Int_t fOffset;
         std::vector<Double_t> fCoeffs;

      public:

         FIR();

         virtual ~FIR(){}

         void SetOffset(Int_t off){fOffset = off;}

         virtual Int_t GetOutputSize(Int_t inputsize) const
                     { return inputsize - fCoeffs.size() + 1; };

         const std::vector<Double_t>& GetCoeffs() const
                     { return fCoeffs;}

         virtual void SetCoeffs(Int_t inputsize,const Double_t coeffs[]);
         virtual void SetCoeffs(const std::vector<Double_t>& coeffs);

         virtual void Smooth(Int_t inputsize,const Double_t inputx[],
                             const Double_t inputy[],Double_t output[], 
                             Double_t residual[]=nullptr) const;

         virtual void Smooth(const std::vector<Double_t>& inputx, 
                             const std::vector<Double_t>& inputy, 
                             std::vector<Double_t>& output, 
                             std::vector<Double_t>& residual, 
                             Bool_t set_residual=false) const;

         void TransferFunction(Double_t re, Double_t im, Double_t& zr, 
                          Double_t& zi,Int_t offset=kMiddleOffset) const;
         Double_t Power(Double_t re, Double_t im=0,
                        Int_t offset=kMiddleOffset) const;
         Double_t Magnitude(Double_t re, Double_t im=0,
                            Int_t offset=kMiddleOffset) const;
         Double_t PhaseShift(Double_t re, Double_t im=0,
                             Int_t offset=kMiddleOffset) const;

   };

}

#endif

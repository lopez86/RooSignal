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
// IIR                                                                  //
//                                                                      //
// Base class for IIR (infinite impulse response) filters.              //
// Takes in a double array and outputs a smoothed array and an array    //
// of residuals.                                                        //
//                                                                      //
//////////////////////////////////////////////////////////////////////////


#include <Rtypes.h>
#include <vector>

namespace signal
{
   class IIR : public Filter
   {

      protected:
         Int_t fOffset;
         std::vector<Double_t> fCoeffs;
         std::vector<Double_t> fCoeffsDenom;
         std::vector<Double_t> fInitCond;

      public:

         IIR();

         virtual ~IIR(){}

         void SetOffset(Int_t off){fOffset = off;}

         virtual Int_t GetOutputSize(Int_n inputsize) const 
                 { return inputsize + 1 - (Int_t)fCoeffs.size(); };

         const std::vector<Double_t>& GetNumeratorCoeffs() const
                 {return fCoeffs;}

         const std::vector<Double_t>& GetDenominatorCoeffs() const
                 {return fCoeffsDenom;}

         const std::vector<Double_t>& GetInitialConditions() const
                 {return fInitCond;}

         virtual void SetCoeffs(Int_t size_num, const Double_t coeffs_num[],
                                Int_t size_den,const Double_t coeffs_den[]);
         virtual void SetCoeffs(const std::vector<Double_t>& const_num , 
                                const std::vector<Double_t>& coeffs_den;);

         virtual void SetInitialConditions(const Double_t vals[]);
         virtual void SetInitialConditions(const std::vector<Double_t>& vals);

         virtual void Smooth(Int_t inputsize,const Double_t inputx[],
                             const Double_t inputy[],Double_t output[], 
                             Double_t residual[]=nullptr) const;

         virtual void Smooth(const std::vector<Double_t>& inputx, 
                             const std::vector<Double_t>& inputy, 
                             std::vector<Double_t>& output, 
                             std::vector<Double_t>& residual, 
                             Bool_t set_residual=false) const;
   };

}

#endif

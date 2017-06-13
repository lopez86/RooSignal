// @(#)signal:$Id$
// Author: Jeremy Lopez   03/06/2017

/*************************************************************************
 * Copyright (C) 2017, Jeremy Lopez                                      *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see LICENSE.                                  *
 *                                                                       *
 *************************************************************************/
#ifndef SIGNAL_KDE_H
#define SIGNAL_KDE_H

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// KDE                                                                  //
//                                                                      //
// Base class for KDE (kernel density estimate) filters.                //
// Takes in a double array and                                          //
// and outputs a smoothed array and an array of residuals.              //
// Here I define a continuous filter as one where the                   //
// Can also output the smoothed value at any real value.                //
//                                                                      //
//////////////////////////////////////////////////////////////////////////


#include <Rtypes.h>
#include <vector>

namespace signal
{
   class KDE : public ContinuousFilter
   {

      protected:

         std::vector<Double_t> fPars;
         Double_t (*fKernel)(Double_t,Double_t,Double_t[]);

      public:

         KDE(){}

         virtual ~KDE(){}

         void SetKernel( Double_t(*k)(Double_t,Double_t,Double_t[]))
                        {fKernel = k;}

         void SetParameters(Int_t npar, Double_t pars[]);
         void SetParameters(const std::vector<Double_t>& pars);

         Double_t Kernel(Double_t x1, Double_t x2) const;
        

         virtual void Smooth(Int_t inputsize,const Double_t inputx[],
                             const Double_t inputy[],Double_t output[], 
                             Double_t residual[]=nullptr) const;

         virtual void Smooth(const std::vector<Double_t>& inputx, 
                             const std::vector<Double_t>& inputy, 
                             std::vector<Double_t>& output, 
                             std::vector<Double_t>& residual, 
                             Bool_t set_residual=false) const;

         virtual Double_t Calculate(Int_t inputsize, 
                                    const Double_t inputx[], 
                                    const Double_t inputy[], 
                                    Double_t x) const;

         virtual Double_t Calculate(const std::vector<Double_t>& inputx, 
                                    const std::vector<Double_t>& inputy,
                                    Double_t x) const;
 
   };

}

#endif

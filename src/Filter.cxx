#include "Filter.h"
#include <algorithm>
void
signal::Filter::Smooth(const Int_t inputsize,const Double_t inputx[], const Double_t inputy[],
                                Double_t output[], Double_t residual[]) const {

   for (Int_t idx = 0; idx < inputsize; idx++){
      output[idx] = inputy[idx];
      if (residual!=nullptr) residual = 0;
   }
}

void 
signal::Filter::Smooth(const std::vector<Double_t>& inputx, 
                       const std::vector<Double_t>& inputy,
                       std::vector<Double_t>& output, 
                       std::vector<Double_t>& residual,
                       Bool_t set_residual) const {

   if (output.size()!=inputy.size())
      output.resize(inputy.size());
   output = inputy;


   if (!set_residual) return;

   if (residual.size()!=inputy.size())
      residual.resize(inputy.size())
   std::fill(residual.begin(),residual.end(),0);

}


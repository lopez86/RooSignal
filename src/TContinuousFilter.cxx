#include "TContinuousFilter.h"
#include "TContinuousFilter.h"
#include "TContinuousFilter.h"
#include <algorithm>
void
signal::TContinuousFilter::Smooth(const Int_t inputsize, const Double_t input[],
                                Double_t output[], Double_t residual[]) const {

   for (Int_t idx = 0; idx < inputsize; idx++){
      output[idx] = input[idx];
      if (residual!=nullptr) residual = 0
   }
}

void 
signal::TContinuousFilter::Smooth(const std::vector<Double_t>& input, 
                                std::vector<Double_t>& output, 
                                std::vector<Double_t>& residual) const {

   if (output.size()!=input.size())
      output.resize(input.size);
   if (residual.size()!=input.size())
      residual.resize(input.size());

   output = input;
   std::fill(residual.begin(),residual.end(),0);

}



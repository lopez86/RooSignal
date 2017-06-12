#include "FIR.h"
#include <algorithm>
using std::vector;


signal::FIR::FIR() : DiscreteFilter(), fCoeffs(0){}

void
signal::FIR::Smooth(Int_t inputsize, const Double_t input[], 
                     Double_t output[], Double_t residual[],
                     Int_t offset){

   Int_t outputsize = GetOutputSize(inputsize);
   Int_t filtersize = (Int_t) fCoeffs.size();

   if (offset == kNoOffset) offset = 0;
   else if (offset == kMiddleOffset) offset = filtersize / 2;
   else if (offset == kMaxOffset) offset = filtersize - 1;

   for (Int_t i = 0; i < outputsize; i++){
      output[i] = 0;
      for (Int_t j = 0; j < filtersize; j++){
         output[i] = input[i+j] * fCoeffs[j];
      }//Loop over filter elements

      if (residual!=nullptr) 
         residual[i] = input[i+offset] - output[i];

   }//Loop over output elements


}

void 
signal::FIR::Smooth(const std::vector<Double_t>& input, 
                     std::vector<Double_t>& output, 
                     std::vector<Double_t>& residual,
                     Int_t offset){

   Int_t outputsize = GetOutputSize((Int_t)input.size());
   if (output.size()!=outputsize)
      output.resize(outputsize);
   if (residual.size()!=outputsize)
      residual.resize(outputsize);

   Smooth( (Int_t)input.size(),&input[0],&output[0],&residual[0],offset);

}


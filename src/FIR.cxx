#include "FIR.h"
#include <algorithm>
using std::vector;


signal::FIR::FIR() : DiscreteFilter(), fCoeffs(0){}

void
signal::FIR::SetCoeffs(Int_t inputsize,const Double_t coeffs[]){
  fCoeffs.assign(coeffs,coeffs+inputsize);
}

void
signal::FIR::SetCoeffs(const vector<Double_t>& coeffs){
  fCoeffs = coeffs;
}

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
         output[i] += input[i+j] * fCoeffs[j];
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

void
signal::FIR::TransferFunction(Double_t re, Double_t im, 
                              Double_t& zr, Double_t& zi,
                              Int_t offset) const{

   Int_t filtersize = (Int_t) fCoeffs.size();
   if (offset == kNoOffset) offset = 0;
   else if (offset == kMiddleOffset) offset = filtersize / 2;
   else if (offset == kMaxOffset) offset = filtersize - 1;

   zr = 0;
   zi = 0;
   for (Int_t idx = 0; idx < (Int_t)fCoeffs.size(); idx++){
      Double_t A = exp(-re * (idx-offset));
      zr += A * cos(im * (idx-offset)) * fCoeffs[idx];
      im -= A * sin(im *(idx-offset)) * fCoeffs[idx];

   }

}

Double_t
signal::FIR::Power(Double_t re, Double_t im, Int_t offset) const{
   Double_t zr,zi;
   TransferFunction(re,im,zr,zi,offset);
   return zr*zr + zi*zi;
}

Double_t
signal::FIR::Magnitude(Double_t re, Double_t im, Int_t offset) const{
   return sqrt(Power(re,im,offset));
}

Double_t
signal::FIR::PhaseShift(Double_t re, Double_t im, Int_t offset) const{
   Double_t zr,zi;
   TransferFunction(re,im,zr,zi,offset);
   return atan2(zi,zr);
}


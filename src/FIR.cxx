#include "FIR.h"
#include <algorithm>
using std::vector;


signal::FIR::FIR() : Filter(), fOffset(0),fCoeffs(0){}

void
signal::FIR::SetCoeffs(Int_t inputsize,const Double_t coeffs[]){
  fCoeffs.assign(coeffs,coeffs+inputsize);
}

void
signal::FIR::SetCoeffs(const vector<Double_t>& coeffs){
  fCoeffs = coeffs;
}

void
signal::FIR::Smooth(Int_t inputsize, const Double_t inputx[], 
                    const Double_t inputy[],Double_t output[], 
                    Double_t residual[]){

   Int_t outputsize = GetOutputSize(inputsize);
   Int_t filtersize = (Int_t) fCoeffs.size();

   Int_t offset = fOffset;
   if (fOffset == kNoOffset) offset = 0;
   else if (fOffset == kMiddleOffset) offset = filtersize / 2;
   else if (fOffset == kMaxOffset) offset = filtersize - 1;

   for (Int_t i = 0; i < outputsize; i++){
      output[i] = 0;
      for (Int_t j = 0; j < filtersize; j++){
         output[i] += inputy[i+j] * fCoeffs[j];
      }//Loop over filter elements

      if (residual!=nullptr) 
         residual[i] = inputy[i+offset] - output[i];

   }//Loop over output elements


}

void 
signal::FIR::Smooth(const std::vector<Double_t>& inputx,
                    const std::vector<Double_t>& inputy, 
                    std::vector<Double_t>& output, 
                    std::vector<Double_t>& residual,
                    Bool_t use_residual){

   Int_t outputsize = GetOutputSize((Int_t)inputy.size());
   if (output.size()!=outputsize)
      output.resize(outputsize);

   if (set_residual){
      if (residual.size()!=outputsize)
         residual.resize(outputsize);

      Smooth( (Int_t)input.size(),&inputx[0],&inputy[0],&output[0],&residual[0]);
   }else{
      Smooth( (Int_t)input.size(),&inputx[0],&inputy[0],&output[0],nullptr);
   }
}

void
signal::FIR::TransferFunction(Double_t re, Double_t im, 
                              Double_t& zr, Double_t& zi) const{

   Int_t offset = fOffset;
   Int_t filtersize = (Int_t) fCoeffs.size();
   if (fOffset == kNoOffset) offset = 0;
   else if (fOffset == kMiddleOffset) offset = filtersize / 2;
   else if (fOffset == kMaxOffset) offset = filtersize - 1;

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


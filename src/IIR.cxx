#include "IIR.h"
#include <algorithm>
using std::vector;


signal::IIR::IIR() : DiscreteFilter(), fOffset(0),fCoeffs(0),
                     fCoeffsDenom(0), fInitCond(0){}

void
signal::IIR::SetCoeffs(Int_t size_num, const Double_t coeffs_num[],
                       Int_t size_den,const Double_t coeffs_den[]){
    fCoeffs.assign(coeffs_num,coeffs_num+size_num);
    fCoeffsDenom.assign(coeffs_den,coeffs_den+size_den);
}

void
signal::IIR::SetCoeffs(const vector<Double_t>& coeffs_num,
                       const vector<Double_t>& coeffs_den){
   fCoeffs = coeffs_num;
   fCoeffsDenom = coeffs_den;
}

void
signal::IIR::SetInitialConditions(const Double_t vals[]){
   fInitCond.assign(vals,vals+fCoeffsDenom.size());
}

void
signal::IIR::SetInitialConditions(const vector<Double_t>& vals){
   fInitCond = vals;
}

void
signal::IIR::Smooth(Int_t inputsize, const Double_t inputx[], 
                    const Double_t inputy[], Double_t output[], 
                    Double_t residual[]){

   Int_t outputsize = GetOutputSize(inputsize);
   Int_t firsize = (Int_t) fCoeffs.size();
   Int_t iirsize = (Int_t) fCoeffsDenom.size();
   Int_t offset = fOffset;
   if (fOffset == kNoOffset) offset = 0;
   else if (fOffset == kMiddleOffset) offset = firsize / 2;
   else if (fOffset == kMaxOffset) offset = firsize - 1;

   for (Int_t i = 0; i < outputsize; i++){
      output[i] = 0;
      for (Int_t j = 0; j < firsize; j++){
         output[i] += inputy[i+j] * fCoeffs[j];
      } // FIR part loop
      for (Int_t j = 0; j < iirsize; j++){
         Double_t value = 0;
         if (i-j > 1) value = output[i-j-1];
         else if (j-i < (Int_t)fInitCond.size())
            value = fInitCond[j-i];
         output[i] -= value * fCoeffsDenom[j];
      }//IIR part loop

      if (residual!=nullptr) 
         residual[i] = inputy[i+offset] - output[i];

   }//Loop over output elements


}

void 
signal::IIR::Smooth(const std::vector<Double_t>& inputx, 
                    const std::vector<Double_t>& inputy,
                    std::vector<Double_t>& output, 
                    std::vector<Double_t>& residual,
                    Bool_t set_residual){

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
signal::IIR::TransferFunction(Double_t re, Double_t im, 
                              Double_t& zr, Double_t& zi,
                              Int_t offset) const{

   Int_t filtersize = (Int_t) fCoeffs.size();
   Int_t offset = fOffset;
   if (fOffset == kNoOffset) offset = 0;
   else if (fOffset == kMiddleOffset) offset = filtersize / 2;
   else if (fOffset == kMaxOffset) offset = filtersize - 1;

   Double_t zrn = 0;//Real numerator
   Double_t zin = 0;//Imag numerator
   Double_t zrd = 1;//Real denominator
   Double_t zid = 0;//Imag denominator
   Double_t A = exp(-re * (idx-offset));
   for (Int_t idx = 0; idx < (Int_t)fCoeffs.size(); idx++){
      zrn += A * cos(im * (idx-offset)) * fCoeffs[idx];
      zin -= A * sin(im *(idx-offset)) * fCoeffs[idx];
   }

   for (Int_t idx = 0; idx < (Int_t) fCoeffsDenom.size(); idx++){
      zrd += A * cos(im * (idx-offset)) * fCoeffsDenom[idx];
      zid -= A * sin(im * (idx-offset)) * fCoeffsDenom[idx];
   }

   invmag_denom = 1.0/sqrt(zrd*zrd + zid*zid);
   zr = invmag_denom * (zrn*zrd + zin*zid);
   zi = invmag_denom * (zin * zrd - zrn * zid);

}

Double_t
signal::IIR::Power(Double_t re, Double_t im, Int_t offset) const{
   Double_t zr,zi;
   TransferFunction(re,im,zr,zi,offset);
   return zr*zr + zi*zi;
}

Double_t
signal::IIR::Magnitude(Double_t re, Double_t im, Int_t offset) const{
   return sqrt(Power(re,im,offset));
}

Double_t
signal::IIR::PhaseShift(Double_t re, Double_t im, Int_t offset) const{
   Double_t zr,zi;
   TransferFunction(re,im,zr,zi,offset);
   return atan2(zi,zr);
}


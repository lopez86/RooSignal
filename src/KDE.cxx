#include "KDE.h"
#include <vector>
using std::vector;

void
signal::KDE::SetParameters(Int_t npar, Double_t pars[]){
   fPars.assign(pars,pars+npar);
}

void
signal::KDE::SetParameters(const vector<Double_t>& pars){
   fPars = pars;
}

Double_t
signal::KDE::Kernel(Double_t x1, Double_t x2) const{
  return fKernel(x1,x2,fPars);
}

Double_t 
signal::KDE::Calculate(Int_t inputsize, const Double_t inputx[],
                   const Double_t inputy[], Double_t x) const{
   Double_t weight = 0;
   Double smoothed = 0;
   for (Int_t i = 0; i <inputsize; i++){
      Double_t val = fKernel(x,inputx[i],fPars);
      smoothed += val * inputy[i];
      weight += val;

   }

   if (weight>0)
      smoothed /= weight;
   return smoothed;
}

Double_t 
signal::KDE::Calculate(const vector<Double_t>& inputx,
                   const vector<Double_t>& inputy, Double_t x) const{

   return Calculate((Int_t)inputx.size(),&inputx[0],&inputy[0],x);
}

void 
signal::KDE::Smooth(Int_t inputsize,const Double_t inputx[],
                    const Double_t inputy[],Double_t output[], 
                    Double_t residual[]=nullptr) const{

   for (Int_t i = 0; i < inputsize; i++){
      output[i] = Calculate(inputsize,inputx,inputy,inputx[i]);
      if (residual!=nullptr) residual[i] = inputy[i] - output[i];
   }
}

void 
signal::KDE::Smooth(const std::vector<Double_t>& inputx, 
                    const std::vector<Double_t>& inputy, 
                    std::vector<Double_t>& output, 
                    std::vector<Double_t>& residual, 
                    Bool_t set_residual=false) const{

   if (output.size()!=inputy.size())
      output.resize(inputy.size());
   if (set_residual==true && residual.size()!=inputy.size())
      residual.resize(inputy.size());
   for (Int_t i = 0; i < inputsize; i++){
      output[i] = Calculate(inputx,inputy,inputx[i]);
      if (set_residual) residual[i] = inputy[i] - output[i];
   }


}


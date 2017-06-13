#include "MedianFilter.h"
#include <vector>
#include <algorithm>
void 
signal::MedianFilter::Smooth(Int_t inputsize, const Double_t inputx[], 
                         const Double_t inputy[],
                         Double_t output[], Double_t residual[]){

   std::vector<Double_t> vec(fFilterSize);
   Int_t outputsize = GetOutputSize(inputsize);
   for (Int_t idx = 0; idx < outputsize; idx++){
      vec.assign(inputy+idx,inputy+idx+fFilterSize);
      std::sort(vec.begin(),vec.end());
      Double_t med;
      if (fFilterSize%2==0) //even
         med = 0.5*(vec[fFilterSize/2]+vec[fFilterSize/2-1]);
      else//odd
         med = vec[fFilterSize / 2];
      output[idx] = med;
      if (residual!=nullptr)
         residual[idx] = inputy[idx+offset] - med;
   }

}

void 
signal::MedianFilter::Smooth(const std::vector<Double_t>& inputx,
                         const std::vector<Double_t>& inputy, 
                         std::vector<Double_t>& output, 
                         std::vector<Double_t>& residual,
                         Bool_t set_residual){

   if (output.size()!=inputy.size())
      output.resize(inputy.size());

   if (set_residual){
   if (residual.size()!=inputy.size())
      residual.resize(inputy.size());
      Smooth((Int_t)input.size(),&inputx[0],&inputy[0],&output[0],
             &residual[0]);

   }else{
      Smooth((Int_t)input.size(),&inputx[0],&inputy[0],&output[0],
             nullptr);
   }
}


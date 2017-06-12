#include "MedianDiscreteFilter.h"
#include <vector>
#include <algorithm>
void 
signal::MedianDiscreteFilter::Smooth(Int_t inputsize, const Double_t input[], 
                         Double_t output[], Double_t residual[],
                         Int_t offset){

   std::vector<Double_t> vec(fFilterSize);
   Int_t outputsize = GetOutputSize(inputsize);
   for (Int_t idx = 0; idx < outputsize; idx++){
      vec.assign(input+idx,input+idx+fFilterSize);
      std::sort(vec.begin(),vec.end());
      Double_t med;
      if (fFilterSize%2==0) //even
         med = 0.5*(vec[fFilterSize/2]+vec[fFilterSize/2-1]);
      else//odd
         med = vec[fFilterSize / 2];
      output[idx] = med;
      residual[idx] = input[idx+offset] - med;
   }

}

void 
signal::MedianDiscreteFilter::Smooth(const std::vector<Double_t>& input, 
                         std::vector<Double_t>& output, 
                         std::vector<Double_t>& residual,
                         Int_t offset){

   if (output.size()!=input.size())
      output.resize(input.size());
   if (residual.size()!=input.size())
      residual.resize(input.size());

   Smooth((Int_t)input.size(),&input[0],&output[0],
          &residual[0],offset);

}


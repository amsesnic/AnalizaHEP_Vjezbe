#define Analyzer_cxx
#include "Analyzer.h"

Analyzer::Analyzer()
{
    //prazan
}

Double_t Analyzer::Binomial(Int_t r, Double_t p, Int_t N)
{
    return TMath::Factorial(N)/(TMath::Factorial(r)*TMath::Factorial(N-r)) * TMath::Power(p,r) * TMath::Power(1.-p,N-r);

}

Double_t* Analyzer::ClopperPearson(Int_t m, Int_t N, Double_t C)
{
    static Double_t pBoundaries[2] = {0., 1.};
    Double_t p = 0., step = 0.001, suma0 = 0., suma1 = 0.;
    Bool_t nasliGranicu[2] = {0, 0};

    while(p <= 1.0){
        suma0 = 0.;
        suma1 = 0.;
        if(nasliGranicu[0] == false){ 
            for(int r = 0; r<m; r++){
                suma0 += Binomial(r,p,N);
            }
            if( suma0 <= 1.-(1.-C)/2. ){
                pBoundaries[0] = p;
                nasliGranicu[0] = true;
            }
        }
        if(nasliGranicu[1] == false){
            for(int r = m+1; r<=N; r++){
                suma1 += Binomial(r,p,N);
            }
            if( suma1 >= 1.-(1.-C)/2. ){
                pBoundaries[1] = p;
                nasliGranicu[1] = true;
                if(nasliGranicu[0]) break;
            }
        }

        p += step;
        
    }

    return pBoundaries;
}





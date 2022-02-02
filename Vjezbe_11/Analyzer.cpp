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





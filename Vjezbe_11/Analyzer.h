//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Jan 19 12:24:29 2022 by ROOT version 6.24/06
// from TTree Tree/Height of woman in ...
// found on file: /home/public/data/Height/Height.root
//////////////////////////////////////////////////////////

#ifndef Analyzer_h
#define Analyzer_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TRandom3.h>
#include <iostream>
#include <TMath.h>
#include <TF1.h>
#include <TFitResult.h>
#include <TGraph.h>
#include <TLine.h>
#include <TColor.h>


class Analyzer {
public :

   Analyzer();
   Double_t     Binomial(Int_t r, Double_t p, Int_t N);
   Double_t*    ClopperPearson(Int_t m, Int_t N, Double_t C);
   void         PojasPouzdanosti(Int_t r);

};
#endif



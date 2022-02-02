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
//#include <ParameterSettings.h> //za step size?

// Header file for the classes stored in the TTree if any.

class Analyzer {
public :

   Int_t       mH_brBinova, t_brBinova, sirinaProzora;
   Double_t    pValue, zeta, mH_min, mH_max, tStat_max;
   TH1F       *h_tstat, *h_pdf;
   TF1        *f_pdf_SM;

   Analyzer();
   void     GenerateTstatistic();
   void     PvalueScan();

};
#endif



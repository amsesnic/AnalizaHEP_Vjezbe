#define Analyzer_cxx
#include "Analyzer.h"


void Analyzer::GenerateTstatistic()
{
    const double h_AVG = 164.7, h_SIGMA = 7.1, Pvalue = 0.05;
    const int N = 100, M = 1.0e6;
    Double_t height_pseudo, t, z_score;

    TRandom3 *rand_gen = new TRandom3();
    TH1F *hist = new TH1F("t statistic", "t statistic", 100., 160., 170.);
    
    for(int j = 0; j < M; j++){
        t = 0.;
        for(int i = 0; i < N; i++){
            height_pseudo = rand_gen->Gaus(h_AVG, h_SIGMA);
            if(j==0) std::cout << height_pseudo << "\n";

            t += height_pseudo; 
        }
        t = t/N;
        hist->Fill(t);
    }

    TCanvas *c = new TCanvas("c", "test statistic", 0,0,1000,800);
    gStyle->SetOptStat(0);
    hist->Scale( 1.0/hist->Integral() );
    hist->Draw("hist");
    c->SaveAs("t_statistic.png");

    pValue = hist->Integral( hist->FindBin(tStat), hist->FindBin(170.) );
    std::cout << "P value observed = " << pValue << "\n";

    z_score = TMath::Sqrt(2)*TMath::ErfcInverse(2*pValue);
    std::cout << "significance observed = " << z_score << "\n";


}

void Analyzer::Loop()
{
//   In a ROOT session, you can do:
//      root> .L Analyzer.C
//      root> Analyzer t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch

   tStat = 0.; //public variable
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      tStat+=height;
   }

   tStat = tStat/nentries;
   std::cout << "t observed = " << tStat << "\n";

}

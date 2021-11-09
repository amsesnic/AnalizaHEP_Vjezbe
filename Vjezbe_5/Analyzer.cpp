#define Analyzer_cxx
#include "Analyzer.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <iostream>


void Analyzer::PlotHistogram()
{
    TH1F *h1 = new TH1F("h1", "Transverse P 1", 100, 0., 135.);
    TH1F *h2 = new TH1F("h2", "Transverse P 2", 100, 0., 135.);
    TCanvas c("c", "V5 ZAD2", 0,0,400,300);
    TFile *fout = TFile::Open("H_TransP_12.root", "RECREATE");
    
    this->Loop(h1, h2);
    //h->Fill(TransP_1); // Punjenje je u metodi Loop(TH1F* h)
    h1->GetXaxis()->SetTitle("P_t (GeV/c)");
    h1->GetYaxis()->SetTitle("Number of particles");
    h1->SetLineColor(kMagenta);
    h1->SetFillColor(kMagenta);
    h1->SetStats(0);
    h1->SetTitle("Transverse momentum");
    h1->Draw();

    //h2->GetXaxis()->SetTitle("P_t (GeV/c)");
    //h2->GetYaxis()->SetTitle("Number of particles");
    h2->SetLineColor(kGreen+2);
    //h2->SetFillColor(kMagenta);
    h2->SetStats(0);
    h2->SetTitle("");
    h2->Draw("same"); // same canvas!

    //Create legend
    TLegend* leg = new TLegend(0.6, 0.7, 0.9, 0.9); // constructor takes coord of lower left and upper right corners
    leg->SetHeader("Higgs boson decay simulation", "C");
    leg->AddEntry(h1, "Decay Particle 1", "f");
    leg->AddEntry(h2, "Decay Particle 2", "l");
    leg->Draw();

    c.Print("H_TransP_12.png");
    c.SaveAs("H_TransP_12.pdf");
    c.Write(); //write to root file (from canvas!)
    delete h1;
    delete h2;
    delete fout;
    delete leg;
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
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      if(jentry%100==0) {
         fChain->Show(); //ovo ok radi

         std::cout << Particle_name_1->c_str() << "  " << this->TransP_1 << "\n";
         std::cout << Particle_name_2->c_str() << "  " << this->TransP_2 << "\n\n"; //ako nema ->c_str() onda printa adrese varijabli, ne imena
      }
   }
}


void Analyzer::Loop(TH1F *h1, TH1F *h2)
{
//Overload funkcije Loop za punjenje histograma
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      h1->Fill(TransP_1);
      h2->Fill(TransP_2);
   }
}

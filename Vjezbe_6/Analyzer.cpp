#define Analyzer_cxx
#include "Analyzer.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLorentzVector.h>

void Analyzer::PlotHistogram()
{
    TCanvas *c   = new TCanvas("c", "Histogrami", 0, 0, 1000, 1000);
    TCanvas *c_H = new TCanvas("c_H", "Histogram_H", 0, 0, 1000, 1000);
    TH1F *h1     = new TH1F("h11", "histo11", 100, 0., 100.); //ne znam granice
    TH1F *h2     = new TH1F("h12", "histo12", 100, 0., 100.); 
    TH1F *h3     = new TH1F("h13", "histo13", 100, 0., 100.); 
    TH1F *h4     = new TH1F("h14", "histo14", 100, 0., 100.); 
    TH1F *h_H    = new TH1F("h_H", "histo_H", 100, 100., 150.); 
    
    //napuni histograme u Loop
    this->Loop(h1,h2,h3,h4,h_H);

    c->SetLeftMargin(0.15);
    c->Divide(2,2);
    gStyle->SetOptStat(0);

    /******* PANEL 1 (gore lijevo): Pt *******/
    c->cd(1);
    h3->GetXaxis()->SetTitle("Pt (GeV/c)");
    h3->GetYaxis()->SetTitle("Number of particles");
    h3->SetLineColor(kBlue+1);
    h3->SetTitle("Lepton transverse momentum");
    h3->Draw();

    h4->SetLineColor(kMagenta+2);
    h4->SetTitle("");
    h4->Draw("same");

    h1->SetLineColor(kRed+1);
    h1->SetTitle("");
    h1->Draw("same");
    
    h2->SetLineColor(kGreen+2);
    h2->SetTitle("");
    h2->Draw("same");
   
    
    /*LEGENDA, OSI, OSTALE VARIJABLE, LINIJE, BOJE...*/
    
    c->Print("H-4l.png");
    
    c_H->cd();
    h_H->Draw();
    c_H->Print("Higgs.png");
    delete h1;
    delete h2;
    delete h3;
    delete h4;
    delete c;
}

void Analyzer::Loop(TH1F *h1, TH1F *h2, TH1F *h3, TH1F *h4, TH1F *h_H)
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

   TLorentzVector p_L1, p_L2, p_L3, p_L4, p_Z1, p_Z2, p_H4L;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      h1->Fill(LepPt->at(0)); //ovako se pristupa elementu vectora s pokazivacem na taj vector
      h2->Fill(LepPt->at(1));
      h3->Fill(LepPt->at(2));
      h4->Fill(LepPt->at(3));

      //4-momentum calculation
      p_L1.SetPtEtaPhiM( LepPt->at(0), LepEta->at(0), LepPhi->at(0), 0.); //masa=0
      p_L2.SetPtEtaPhiM( LepPt->at(1), LepEta->at(1), LepPhi->at(1), 0.);
      p_L3.SetPtEtaPhiM( LepPt->at(2), LepEta->at(2), LepPhi->at(2), 0.);
      p_L4.SetPtEtaPhiM( LepPt->at(3), LepEta->at(3), LepPhi->at(3), 0.);
      
      p_Z1 = p_L1 + p_L2;
      p_Z2 = p_L3 + p_L4;
      p_H4L = p_Z1 + p_Z2;
      h_H->Fill( p_H4L.M() );
   }
}



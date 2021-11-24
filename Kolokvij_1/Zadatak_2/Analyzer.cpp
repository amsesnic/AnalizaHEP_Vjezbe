#define Analyzer_cxx
#include "Analyzer.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLegend.h>


void Analyzer::PlotHistogram()
{
    TCanvas *c   = new TCanvas("c", "Histogrami", 0, 0, 1200, 400);
    c->Divide(3,1);
    gStyle->SetOptStat(0);

    TH1F *h_ele_pt = new TH1F("h_ele_pt", "", 50, 0., 150.);
    TH2F *h_2d     = new TH2F("h_2d", "", 50, 0., 150.,  50, -3., 3.);
    TH1F *h_ele_eelepout = new TH1F("h_ele_eelepout", "ele_eelepout", 50, -100., 100.);

    //Loop over events
    if (fChain == 0) return;
    Long64_t nentries = 100000; //Long64_t nentries = fChain->GetEntriesFast();
    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry=0; jentry<nentries;jentry++) {
        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0) break;
        nb = fChain->GetEntry(jentry);   nbytes += nb;
       // if (Cut(ientry) < 0) continue;

        h_ele_pt->Fill(ele_pt);
        h_2d->Fill(ele_pt, scl_eta);
        h_ele_eelepout->Fill(ele_eelepout);

    }
    
    //Draw histos on canvas
    c->cd(1);
    gPad->SetLeftMargin(0.15);
    h_ele_pt->GetXaxis()->SetTitle("ele_pt");
    h_ele_pt->GetYaxis()->SetTitle("Number of events");
    h_ele_pt->SetLineColor(kRed);
    h_ele_pt->SetLineWidth(2);
    h_ele_pt->DrawCopy("hist");

    c->cd(2);
    gPad->SetLeftMargin(0.15);
    gPad->SetRightMargin(0.15);
    h_2d->GetXaxis()->SetTitle("ele_pt");
    h_2d->GetYaxis()->SetTitle("scl_eta");
    h_2d->SetMinimum(-0.01);
    h_2d->Draw("colz");



    c->cd(3);
    gPad->SetLeftMargin(0.15);

    Double_t scale_factor;

    scale_factor = 1.0/( h_ele_pt->Integral() );
    h_ele_pt->Scale(scale_factor);
    h_ele_pt->SetLineStyle(2);
    h_ele_pt->Draw("hist");

    scale_factor = 1.0/( h_ele_eelepout->Integral() );
    h_ele_eelepout->Scale(scale_factor);
    h_ele_eelepout->SetFillColor(kAzure);
    h_ele_eelepout->Draw("hist same");

    TLegend *leg = new TLegend(0.65, 0.75, 0.9, 0.9);
    leg->AddEntry(h_ele_pt, "ele_pt", "l");
    leg->AddEntry(h_ele_eelepout, "ele_eelepout", "f");
    leg->Draw();
 
    c->Print("Zad2_histos.png");


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
   }
}

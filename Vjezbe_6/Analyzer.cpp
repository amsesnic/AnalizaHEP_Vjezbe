#define Analyzer_cxx
#include <Analyzer.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLorentzVector.h>

void Analyzer::PlotHistogram()
{
    TCanvas *c   = new TCanvas("c", "Histogrami", 0, 0, 1000, 1000);
    TCanvas *c_H = new TCanvas("c_H", "Histogram_H", 0, 0, 1000, 1000);
   
    TH1F *h_Higgs    = new TH1F("h_Higgs", "h_Higgs", 100, 100., 150.);
    TH1F *h_LepPt[4];
    TH1F *h_LepEta[4];
    TH1F *h_LepPhi[4];
    TH1F *h_LepBDT[4];
    int i;
    std::string naslov;
    for(i=0; i<4; i++){
        naslov = "h_LepPt"+std::to_string(i);
        h_LepPt[i]  = new TH1F(naslov.c_str(),  naslov.c_str(),  100, 0., 100.);

        naslov = "h_LepEta"+std::to_string(i);
        h_LepEta[i] = new TH1F(naslov.c_str(),  naslov.c_str(), 100, 0., 100.);

        naslov = "h_LepPhi"+std::to_string(i);
        h_LepPhi[i] = new TH1F(naslov.c_str(),  naslov.c_str(), 100, 0., 100.);

        naslov = "h_LepBDT"+std::to_string(i);
        h_LepBDT[i] = new TH1F(naslov.c_str(),  naslov.c_str(), 100, 0., 100.);
    }
    
    /*******   NAPUNI HISTOGRAME U Loop   *******/
    //Kod kopiran iz Loop() metode
    if (fChain == 0) return;

    TLorentzVector p_Leptons[4];
    TLorentzVector p_Z1, p_Z2, p_H4L;

    Long64_t nentries = fChain->GetEntriesFast();

    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry=0; jentry<nentries;jentry++) {
       Long64_t ientry = LoadTree(jentry);
       if (ientry < 0) break;
       nb = fChain->GetEntry(jentry);   nbytes += nb;
       // if (Cut(ientry) < 0) continue;
       
       for(i=0; i<4; i++){
           h_LepPt[i] ->Fill(LepPt->at(i)); //ovako se pristupa elementu vectora s pokazivacem na taj vector
           h_LepEta[i]->Fill(LepEta->at(i));
           h_LepPhi[i]->Fill(LepPhi->at(i));
           h_LepBDT[i]->Fill(LepBDT->at(i));
       }

       //4-momentum calculation
       for(i=0; i<4; i++)
           p_Leptons[i].SetPtEtaPhiM( LepPt->at(i), LepEta->at(i), LepPhi->at(i), 0.); //masa=0
      
       p_Z1 = p_Leptons[0] + p_Leptons[1];
       p_Z2 = p_Leptons[2] + p_Leptons[3];
       p_H4L = p_Z1 + p_Z2;
       h_Higgs ->Fill( p_H4L.M() );
    }
    /*****************************************/

    c->SetLeftMargin(0.15);
    c->Divide(2,2);
    gStyle->SetOptStat(0);

    /******* PANEL 1 (gore lijevo): LepPt *******/
    c->cd(1);

    h_LepPt[2]->GetXaxis()->SetTitle("Pt (GeV/c)");
    h_LepPt[2]->GetYaxis()->SetTitle("Number of particles");
    h_LepPt[2]->SetLineColor(kBlue+1);
    h_LepPt[2]->SetTitle("Lepton transverse momentum");
    h_LepPt[2]->Draw();

    h_LepPt[3]->SetLineColor(kMagenta+2);
    h_LepPt[3]->SetTitle("");
    h_LepPt[3]->Draw("same");

    h_LepPt[0]->SetLineColor(kRed+1);
    h_LepPt[0]->SetTitle("");
    h_LepPt[0]->Draw("same");
    
    h_LepPt[1]->SetLineColor(kGreen+2);
    h_LepPt[1]->SetTitle("");
    h_LepPt[1]->Draw("same");
   
    /******* PANEL 2 (gore desno): LepEta *******/
    c->cd(2);
    h_LepEta[2]->GetXaxis()->SetTitle("Eta");
    h_LepEta[2]->GetYaxis()->SetTitle("Number of particles");
    h_LepEta[2]->SetLineColor(kBlue+1);
    h_LepEta[2]->SetTitle("Pseudorapidity");
    h_LepEta[2]->Draw();

    h_LepEta[3]->SetLineColor(kMagenta+2);
    h_LepEta[3]->SetTitle("");
    h_LepEta[3]->Draw("same");

    h_LepEta[0]->SetLineColor(kRed+1);
    h_LepEta[0]->SetTitle("");
    h_LepEta[0]->Draw("same");
    
    h_LepEta[1]->SetLineColor(kGreen+2);
    h_LepEta[1]->SetTitle("");
    h_LepEta[1]->Draw("same");

    /******* PANEL 3 (dolje lijevo): LepPhi *******/
    c->cd(3);
    h_LepPhi[2]->GetXaxis()->SetTitle("Phi");
    h_LepPhi[2]->GetYaxis()->SetTitle("Number of particles");
    h_LepPhi[2]->SetLineColor(kBlue+1);
    h_LepPhi[2]->SetTitle("Azimuthal angle");
    h_LepPhi[2]->Draw();

    h_LepPhi[3]->SetLineColor(kMagenta+2);
    h_LepPhi[3]->SetTitle("");
    h_LepPhi[3]->Draw("same");

    h_LepPhi[0]->SetLineColor(kRed+1);
    h_LepPhi[0]->SetTitle("");
    h_LepPhi[0]->Draw("same");
    
    h_LepPhi[1]->SetLineColor(kGreen+2);
    h_LepPhi[1]->SetTitle("");
    h_LepPhi[1]->Draw("same");

    /******* PANEL 4 (dolje desno): LepBDT *******/
    c->cd(4);
    h_LepBDT[2]->GetXaxis()->SetTitle("BDT");
    h_LepBDT[2]->GetYaxis()->SetTitle("Number of particles");
    h_LepBDT[2]->SetLineColor(kBlue+1);
    h_LepBDT[2]->SetTitle("BDT");
    h_LepBDT[2]->Draw();

    h_LepBDT[3]->SetLineColor(kMagenta+2);
    h_LepBDT[3]->SetTitle("");
    h_LepBDT[3]->Draw("same");

    h_LepBDT[0]->SetLineColor(kRed+1);
    h_LepBDT[0]->SetTitle("");
    h_LepBDT[0]->Draw("same");
    
    h_LepBDT[1]->SetLineColor(kGreen+2);
    h_LepBDT[1]->SetTitle("");
    h_LepBDT[1]->Draw("same");

    /*LEGENDA, OSI, OSTALE VARIJABLE, LINIJE, BOJE...*/
    
    c->Print("4l-distribucije.png");
    
    c_H->cd();
    h_Higgs->Draw();
    c_H->Print("Higgs.png");

    for(i=0; i<4; i++){
        delete h_LepPt[i];
        delete h_LepEta[i];
        delete h_LepPhi[i];
        delete h_LepBDT[i];
    }
    delete h_Higgs;
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

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

   }
}


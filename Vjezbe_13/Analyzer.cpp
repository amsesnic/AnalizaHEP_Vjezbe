#define Analyzer_cxx
#include "Analyzer.h"


void Analyzer::GenerateTstatistic()
{
    const double h_AVG_fr = 164.7, h_SIGMA_fr = 7.1, Pvalue = 0.05;
    const double h_AVG_sp = 168.0, h_SIGMA_sp = 7.0;
    const double h_AVG_it = 166.1, h_SIGMA_it = 6.5;
    const double h_AVG_ni = 170.3, h_SIGMA_ni = 7.5;
    const int N = 100, M = 1.0e6;
    Double_t height_pseudo_fr, t_fr, z_score;
    Double_t height_pseudo_sp, t_sp;
    Double_t height_pseudo_it, t_it;
    Double_t height_pseudo_ni, t_ni;
    Double_t CL_notFra, CL_notIta, CL_notNiz;

    TRandom3 *rand_gen = new TRandom3();
    TH1F *hist_fr = new TH1F("t_statistic_fr", "t statistic;t / cm;g(t,H_{0})", 300., 160., 175.); //(name, title, ...)
    TH1F *hist_sp = new TH1F("t_statistic_sp", "t statistic;t / cm;g(t,H_{0})", 300., 160., 175.);
    TH1F *hist_it = new TH1F("t_statistic_it", "t statistic;t / cm;g(t,H_{0})", 300., 160., 175.);
    TH1F *hist_ni = new TH1F("t_statistic_ni", "t statistic;t / cm;g(t,H_{0})", 300., 160., 175.);
    
    for(int j = 0; j < M; j++){
        t_fr = 0.;
        t_sp = 0.;
        t_it = 0.;
        t_ni = 0.;
        for(int i = 0; i < N; i++){
            height_pseudo_fr = rand_gen->Gaus(h_AVG_fr, h_SIGMA_fr);
            height_pseudo_sp = rand_gen->Gaus(h_AVG_sp, h_SIGMA_sp);
            height_pseudo_it = rand_gen->Gaus(h_AVG_it, h_SIGMA_it);
            height_pseudo_ni = rand_gen->Gaus(h_AVG_ni, h_SIGMA_ni);
            //if(j==0) std::cout << height_pseudo_fr << "\n";

            t_fr += height_pseudo_fr; 
            t_sp += height_pseudo_sp; 
            t_it += height_pseudo_it; 
            t_ni += height_pseudo_ni; 
        }
        t_fr = t_fr/N;
        t_sp = t_sp/N;
        t_it = t_it/N;
        t_ni = t_ni/N;

        hist_fr->Fill(t_fr);
        hist_sp->Fill(t_sp);
        hist_it->Fill(t_it);
        hist_ni->Fill(t_ni);
    }

    hist_fr->Scale( 1.0/hist_fr->Integral() );
    hist_sp->Scale( 1.0/hist_sp->Integral() );
    hist_it->Scale( 1.0/hist_it->Integral() );
    hist_ni->Scale( 1.0/hist_ni->Integral() );
    hist_fr->SetLineColor(kBlue);
    hist_sp->SetLineColor(kRed);
    hist_it->SetLineColor(kGreen);
    hist_ni->SetLineColor(kViolet);

    TCanvas *c = new TCanvas("c", "test statistic", 0,0,1000,800);
    gStyle->SetOptStat(0);

    TLine *line = new TLine(tStat, 0., tStat, hist_sp->GetBinContent(hist_sp->GetMaximumBin()) );
    line->SetLineColor(kGray);
    line->SetLineWidth(2);

    /* SPA-FRA */
    hist_sp->Draw("hist");
    hist_fr->Draw("hist same");
    line->Draw();
    TLegend *leg = new TLegend(0.70,0.80,0.9,0.9);
    leg->AddEntry(line, "t observed", "l");
    leg->AddEntry(hist_sp, "H_{0}: Spain", "l");
    leg->AddEntry(hist_fr, "H_{1}: France", "l");
    leg->Draw();
    c->SaveAs("t_stat_Spain-France.png");

    CL_notFra = hist_fr->Integral( hist_fr->FindBin(160.), hist_fr->FindBin(tStat) );
    std::cout << "Odbacujemo alternativnu hipotezu H1: Francuska s visinom pouzdanosti:\n    CL = " << CL_notFra << "\n";

    /* SPA-ITA */
    c->Clear();
    leg->Clear();
    hist_it->Draw("hist");
    hist_sp->Draw("hist same");
    line->Draw();
    leg->AddEntry(line, "t observed", "l");
    leg->AddEntry(hist_sp, "H_{0}: Spain", "l");
    leg->AddEntry(hist_it, "H_{1}: Italy", "l");
    leg->Draw();
    c->SaveAs("t_stat_Spain-Italy.png");

    CL_notIta = hist_it->Integral( hist_it->FindBin(160.), hist_it->FindBin(tStat) );
    std::cout << "Odbacujemo alternativnu hipotezu H1: Italija s visinom pouzdanosti:\n    CL = " << CL_notIta << "\n";

    /* SPA-NIZ */
    c->Clear();
    leg->Clear();
    hist_sp->Draw("hist");
    hist_ni->Draw("hist same");
    line->Draw();
    leg->AddEntry(line, "t observed", "l");
    leg->AddEntry(hist_sp, "H_{0}: Spain", "l");
    leg->AddEntry(hist_ni, "H_{1}: The Netherlands", "l");
    leg->Draw();
    c->SaveAs("t_stat_Spain-Netherlands.png");

    CL_notNiz = hist_ni->Integral( hist_ni->FindBin(tStat), hist_ni->FindBin(175.) );
    std::cout << "Odbacujemo alternativnu hipotezu H1: Nizozemska s visinom pouzdanosti:\n    CL = " << CL_notNiz << "\n";

    //pValue = hist_fr->Integral( hist_fr->FindBin(tStat), hist_fr->FindBin(170.) );
    //std::cout << "P value observed = " << pValue << "\n";

    //z_score = TMath::Sqrt(2)*TMath::ErfcInverse(2*pValue);
    //std::cout << "significance observed = " << z_score << "\n";


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

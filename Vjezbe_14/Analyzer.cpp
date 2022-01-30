#define Analyzer_cxx
#include "Analyzer.h"


void Analyzer::GenerateTstatistic()
{
    const double zeta = 100., Pvalue = 0.05;
    const int Nevents = 1.0e4, Mexperiments = 1000, sirinaProzora = 20, histoXmax = 400.;
    Double_t masaFotona, xmin, xmax, xProzor, chi2;
    int Nprozora = histoXmax/sirinaProzora;

    TRandom3 *rand_gen = new TRandom3();
    TH1F *h_tstat = new TH1F("t statistic", "t statistic", 100., 0., 400.);
    TH1F *h_pdf  = new TH1F("pdf", "pdf", 100., 0., histoXmax);

    TF1 *f_pdf;
    
    for(int j = 0; j < Mexperiments; j++){

        h_pdf->Reset(); //isprazni h_pdf
        for(int i = 0; i < Nevents; i++){
            masaFotona = rand_gen->Exp(zeta);
            if(j==0 && i%10==0) std::cout << masaFotona << "\n";
            
            h_pdf->Fill(masaFotona);
            h_pdf->Scale( 1.0/h_pdf->Integral() );
        }
        
        // I sad nakon svakog eksperimenta fitat po prozorima sirine 20 GeV-a
        for(int k = 0; k < Nprozora; k++){
            xmin = k*sirinaProzora;
            xmax = xmin + sirinaProzora;
            //std::cout << xmin << "   " << xmax << "\n";
            f_pdf = new TF1("f_pdf", "[0]*exp(-x/[1])", xmin, xmax);
            f_pdf->FixParameter(1, zeta);
            f_pdf->SetParameter(0, 1000.);
            f_pdf->SetParNames("N_{SM}", "#zeta_{SM}");

            /*auto ptr = h_pdf->Fit(f_pdf);
            chi2 = ptr->Chi2();*/
            // ILI
            chi2 = f_pdf->GetChisquare();
            h_tstat->Fill(chi2);            

        } 


    }

    TCanvas *c = new TCanvas("c", "pdf", 0,0,1000,800);
    gStyle->SetOptStat(0);
    gStyle->SetOptFit();
    //hist->Scale( 1.0/hist->Integral() );
    h_pdf->Draw("hist");
    c->SaveAs("pdf.png");

    TCanvas *c1 = new TCanvas("c1", "t statistic", 0,0,1000,800);
    h_tstat->Draw("hist");
    c1->SaveAs("t_stat_chi2.png");

    /*pValue = hist->Integral( hist->FindBin(tStat), hist->FindBin(170.) );
    std::cout << "P value observed = " << pValue << "\n";

    z_score = TMath::Sqrt(2)*TMath::ErfcInverse(2*pValue);
    std::cout << "significance observed = " << z_score << "\n";*/


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

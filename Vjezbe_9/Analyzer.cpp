#define Analyzer_cxx
#include "Analyzer.h"

void Analyzer::PlotHistogram()
{
    TCanvas *c   = new TCanvas("c", "Histogram", 0, 0, 1500, 400);

    Float_t sum_t = 0.;

    std::ofstream fout;
    fout.open("mjerenje.txt");
    fout << "#     tau\n";

    /*petlja iz Loop()*/
    if (fChain == 0) return;
    Long64_t nentries = fChain->GetEntriesFast();
    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry=0; jentry<nentries;jentry++) {
        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0) break;
        nb = fChain->GetEntry(jentry);   nbytes += nb;
        // if (Cut(ientry) < 0) continue;

        h_t->Fill(t);
        fout << (jentry+1) << " " << t << "\n";
        sum_t += t;
    }

    std::cout << "sum_t = " << sum_t << std::endl;
    std::cout << "nentries = " << nentries << std::endl;

    gStyle->SetOptFit();
    gStyle->SetOptStat(0);
    gPad->SetLeftMargin(0.15);

    c->Divide(3,1);

    c->cd(1);
    h_t->SetTitle("Vrijeme poluraspada");
    h_t->GetXaxis()->SetTitle("t_{1/2}");
    h_t->GetYaxis()->SetTitle("Number of events");
    h_t->SetLineColor(kMagenta+1);
    h_t->Draw("E1 X0");

    TF1 *fja = new TF1("fja", "1./[0]*[1]*exp(-x/[0])", 0., 12.);
    fja->SetParNames("#tau", "N_{0}");
    fja->SetParameters(5., 1000.);
    fja->SetLineColor(kSpring-1);

    h_t->Fit(fja);
    Double_t tau_fit = fja->GetParameter("#tau");
    Double_t N_0     = fja->GetParameter("N_{0}");

    fja->Draw("same");

    c->cd(2);
    TF1 *f_likelihood = new TF1("f_likelihood", "[0]/x*exp(-1./x)", 0., 12.);
    f_likelihood->SetParameter(0, N_0);
    f_likelihood->SetLineColor(kRed);
    f_likelihood->SetTitle("Likelihood function;#tau / 1 s;L(#tau)");
    f_likelihood->Draw();

    TLegend *leg = new TLegend(0.60,0.75,0.9,0.9);
    leg->AddEntry(f_likelihood, "N_{0}#frac{1}{#tau}e^{-1/#tau}", "l");
    leg->Draw();

    c->cd(3);
    gPad->SetLeftMargin(0.15);
    TF1 *f_logL = new TF1("f_logL", "2.*([0]*TMath::Log(x) + [1]/x - [0]*TMath::Log([2]) )", 0.2, 5.0);
    f_logL->SetParameters(nentries, sum_t, N_0);
    f_logL->SetLineColor(kBlue);
    f_logL->SetTitle("-2lnL(#tau); #tau / 1 s; -2lnL(#tau)");
    f_logL->Draw();

    TLegend *leg2 = new TLegend(0.45,0.75,0.9,0.9);
    leg2->AddEntry(f_logL, "2(Nln#tau + #frac{1}{#tau}#Sigma_{i=1}^{N}t_{i} - NlnN_{0})", "l");
    leg2->Draw();     

    c->SaveAs("poluraspad.png");

    Double_t tau_analytical = sum_t/nentries;
    Double_t err_analytical = TMath::Sqrt( TMath::Power(tau_analytical,3) / (2.*sum_t - nentries*tau_analytical) );

    Double_t tau_logmin = f_logL->GetMinimumX();
    Double_t err_logmin_left = tau_logmin - f_logL->GetX(f_logL->GetMinimum()+1., 0.5, tau_logmin); //ogranicih domenu potrage
    Double_t err_logmin_right = f_logL->GetX(f_logL->GetMinimum()+1., tau_logmin, 3.) - tau_logmin;

    std::cout << "\nParameter estimation via function fitting:\n";
    std::cout << "  tau = " << tau_fit << " +- " << fja->GetParError(0) << std::endl;
    std::cout << "Parameter estimation using Max likelihood method:\n";
    std::cout << "  tau = " << tau_analytical << " +- " << err_analytical << std::endl;
    std::cout << "Parameter estimation using -2lnL:\n";
    std::cout << "  tau = " << tau_logmin << " + " << err_logmin_right << " - " << err_logmin_left << std::endl;
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

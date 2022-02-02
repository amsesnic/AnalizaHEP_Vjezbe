#define Analyzer_cxx
#include "Analyzer.h"

Analyzer::Analyzer()
{
    mH_min = 10.;
    mH_max = 690.;
    mH_brBinova = 136; // sirina bina = 5
    zeta = 100.;
    sirinaProzora = 20;
    tStat_max = 30.;
    t_brBinova = 300;

    h_tstat  = new TH1F("t_statistic", "t statistic;t;g(t, H_{0})", t_brBinova, 0., tStat_max);
    h_pdf    = new TH1F("pdf", "pdf for photon mass;m_{#gamma#gamma};PDF(m_{#gamma#gamma})", mH_brBinova, mH_min, mH_max);
    f_pdf_SM = new TF1("f_pdf_SM", "[0]*exp(-x/[1])", mH_min, mH_max);
    f_pdf_SM->FixParameter(1, zeta);
    f_pdf_SM->SetParameter(0, 1.);
    f_pdf_SM->SetParNames("N_{SM}", "#zeta_{SM}");
    //f_pdf_SM->SetParError(0, 5); //mozda je ovo taj step size?
}

void Analyzer::GenerateTstatistic()
{
    const int Nevents = 1.0e5, Mexperiments = 1000;
    int Nprozora = (mH_max-mH_min)/sirinaProzora;
    Double_t masaFotona, xmin, xmax, chi2;

    TCanvas *c = new TCanvas("c", "pdf", 0,0,1000,800);
    TRandom3 *rand_gen = new TRandom3();

    for(int j = 0; j < Mexperiments; j++){

        h_pdf->Reset(); //isprazni h_pdf PUBLIC
        for(int i = 0; i < Nevents; i++){
            masaFotona = rand_gen->Exp(zeta);
            if(j==0 && i%1000==0) std::cout << "masa fotona = " << masaFotona << "\n";
            h_pdf->Fill(masaFotona);
        }
        h_pdf->Scale( 1.0/h_pdf->Integral() );
        
        // I sad nakon svakog eksperimenta fitat po prozorima sirine 20 GeV-a
        for(int k = 0; k < Nprozora; k++){
            xmin = mH_min + k*sirinaProzora;
            xmax = xmin + sirinaProzora;

            h_pdf->Fit(f_pdf_SM, "Q", "", xmin, xmax); // Q=minimum printing, ,fitting range

            chi2 = f_pdf_SM->GetChisquare();
            h_tstat->Fill(chi2);
            if(j%100==0 && k%10==0) std::cout << "j=" << j << ", fit od " << xmin << " do " << xmax << ", chi2 =" << chi2 << "\n";
        }
    }
    h_tstat->Scale( 1.0/h_tstat->Integral() ); // PUBLIC HISTOGRAM

    gStyle->SetOptStat();
    gStyle->SetOptFit();
    gPad->SetLeftMargin(0.15);

    h_pdf->Draw("hist");
    c->SaveAs("zad1_pdf_photons_noHiggs.png");

    c->Clear();
    h_tstat->Draw("hist");
    c->SaveAs("t_stat_chi2.png");

}

void Analyzer::PvalueScan()
{
    const int Nevents = 1.0e4, mH_step = 5;
    int Mexperiments = (int)(mH_max-mH_min)/mH_step;
    Double_t masaFotona, masaHiggsa, xmin, xmax, chi2, t_exp, z_score;
    Double_t higgsProbability;

    TCanvas *c         = new TCanvas("c", "pdf", 0,0,1000,800);
    TGraph *g_pvalue   = new TGraph();
    TRandom3 *rand_gen = new TRandom3();

    int n = 0; // broji koliko se higgsa stvorilo

    for(int j = 0; j < Mexperiments; j++){
        masaHiggsa = mH_min + j*mH_step;
        std::cout << "m_H = " << masaHiggsa << "\n";

        //higgsProbability = -1.*(masaHiggsa-190.)*(masaHiggsa-190.) + 0.02; // ovo je neki veliki negativni broj!!!
        if(masaHiggsa <= 190) higgsProbability = 0.1*masaHiggsa/190.;
        else higgsProbability = -1./6250. * (masaHiggsa-190.) + 0.1;

        h_pdf->Reset(); //isprazni h_pdf

        for(int i = 0; i < Nevents; i++){
            if(rand_gen->Rndm() < higgsProbability){ //stvori higgsa po gausu - MASA 2 FOTONA NASTALA IZ HIGGSA
                masaFotona = rand_gen->Gaus(masaHiggsa, masaHiggsa*0.0236);
                n += 1;
            }
            else { //MASA 2 FOTONA BEZ HIGGSA
                masaFotona = rand_gen->Exp(zeta);
            }

            h_pdf->Fill(masaFotona);
        }
        h_pdf->Scale( 1.0/h_pdf->Integral() );
        
        // Nakon svakog eksperimenta izracunaj "t observed" i p value
        h_pdf->Fit(f_pdf_SM, "Q", "", masaFotona-sirinaProzora/2., masaFotona+sirinaProzora/2.); //treba napravit fit u istom prozoru kao kod racunanja u zad 1
        t_exp = f_pdf_SM->GetChisquare(); // Sta mi je sad t observed?? A isto chi2 - triba fitat sad na cilu funkciju i dobit jedan broj
        std::cout << "t calculated = " << t_exp << "\n";

        pValue = h_tstat->Integral( h_tstat->FindBin(t_exp), t_brBinova );
        if(pValue > 0.5) pValue = 1. - pValue;

        std::cout << "p value = " << pValue << "\n";
        g_pvalue->AddPoint(masaHiggsa, pValue);

        z_score = TMath::Sqrt(2)*TMath::ErfcInverse(2*pValue);
        if (z_score >= 3.)
            std::cout << "\n    ***** significance greater than 3 sigma:  " << z_score << " *****\n\n";
    }
 
    gStyle->SetOptStat();
    gStyle->SetOptFit();
    gPad->SetLeftMargin(0.15);

    h_pdf->Draw("hist");
    c->SaveAs("zad2_pdf_photons_withHiggs.png");
    std::cout << "broj generiranih Higgsovih bozona: " << n << "\n";

    c->Clear();
    gPad->SetLogy();
    g_pvalue->SetLineColor(kAzure);
    g_pvalue->SetMarkerStyle(kCircle);
    g_pvalue->SetMarkerColor(kAzure);
    g_pvalue->SetTitle("P value scan");
    g_pvalue->GetXaxis()->SetTitle("m_{#gamma#gamma}");
    g_pvalue->GetYaxis()->SetTitle("p value");
    g_pvalue->Draw("ALP");
    c->SaveAs("pValueScan.png");

}



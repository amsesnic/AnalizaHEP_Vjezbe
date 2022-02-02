#define Analyzer_cxx
#include "Analyzer.h"

Analyzer::Analyzer()
{
    //prazan
}

Double_t Analyzer::Binomial(Int_t r, Double_t p, Int_t N)
{
    return TMath::Factorial(N)/(TMath::Factorial(r)*TMath::Factorial(N-r)) * TMath::Power(p,r) * TMath::Power(1.-p,N-r);

}

Double_t* Analyzer::ClopperPearson(Int_t m, Int_t N, Double_t C)
{
    static Double_t pBoundaries[2] = {0., 1.};
    Double_t p = 0., step = 0.001, suma0 = 0., suma1 = 0.;
    Bool_t nasliGranicu[2] = {0, 0};

    while(p <= 1.0){
        suma0 = 0.;
        suma1 = 0.;
        if(nasliGranicu[0] == false){ 
            for(int r = 0; r<m; r++){
                suma0 += Binomial(r,p,N);
            }
            if( suma0 <= 1.-(1.-C)/2. ){
                pBoundaries[0] = p;
                nasliGranicu[0] = true;
            }
        }
        if(nasliGranicu[1] == false){
            for(int r = m+1; r<=N; r++){
                suma1 += Binomial(r,p,N);
            }
            if( suma1 >= 1.-(1.-C)/2. ){
                pBoundaries[1] = p;
                nasliGranicu[1] = true;
                if(nasliGranicu[0]) break;
            }
        }

        p += step;
        
    }

    return pBoundaries;
}

void Analyzer::PojasPouzdanosti(Int_t rOdabrani)
{
    TH1F *h_dole = new TH1F("h_dole", "Neyman confidence belt;r;p", 11, -0.5, 10.5); // upper limit EXCLUDED!
    TH1F *h_gore = new TH1F("h_gore", "Neyman confidence belt;r;p", 11, -0.5, 10.5);
    Double_t *pInterval;

    for(int i=0; i<=10; i++){
        pInterval = this->ClopperPearson(i, 10, 0.6827); // povoljni, ukupno, C
        h_dole->SetBinContent(h_dole->FindBin(i), pInterval[0]);
        h_gore->SetBinContent(h_gore->FindBin(i), pInterval[1]);
        std::cout << i << ",  " << h_dole->FindBin(i) << ",  " << pInterval[0] << ",  " << pInterval[1] << "\n";
    }

    TCanvas *c = new TCanvas("c","c", 0,0,800,800);
    gStyle->SetOptStat(0);
    gPad->SetLeftMargin(0.1);

    Int_t ci = TColor::GetFreeColorIndex();
    TColor *bijela = new TColor(ci, 1., 1., 1.); //bijela

    h_dole->SetLineColor(kViolet);
    h_dole->SetLineWidth(2);
    h_dole->SetFillColor(ci); //bijela
    h_gore->SetLineColor(kViolet);
    h_gore->SetLineWidth(2);
    h_gore->SetFillColorAlpha(kViolet, 0.3); // prozirnost

    h_gore->SetMinimum(0.0);
    h_gore->SetMaximum(1.0);
    h_gore->Draw();
    h_dole->Draw("same");

    TLine *l1 = new TLine(rOdabrani, 0., rOdabrani, h_gore->GetBinContent( h_gore->FindBin(rOdabrani) ) );
    TLine *l2 = new TLine(-0.5, h_dole->GetBinContent(h_dole->FindBin(rOdabrani)), rOdabrani, h_dole->GetBinContent(h_dole->FindBin(rOdabrani)) );
    TLine *l3 = new TLine(-0.5, h_gore->GetBinContent(h_gore->FindBin(rOdabrani)), rOdabrani, h_gore->GetBinContent(h_gore->FindBin(rOdabrani)) );

    l1->SetLineColor(kViolet+3);
    l2->SetLineColor(kViolet+3);
    l3->SetLineColor(kViolet+3);
    l1->SetLineWidth(3);
    l2->SetLineWidth(3);
    l3->SetLineWidth(3);
    l1->SetLineStyle(kDashed);
    l2->SetLineStyle(kDashed);
    l3->SetLineStyle(kDashed);
    l1->Draw("same");
    l2->Draw("same");
    l3->Draw("same");

    c->SaveAs("NeymanBelt.png");

}




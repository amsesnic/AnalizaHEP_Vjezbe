#include <TROOT.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TGraphErrors.h>
#include <TF1.h>

int main(){

    TCanvas *c = new TCanvas("c", "masa", 0, 0, 1000, 800);
    //TCanvas *c1 = new TCanvas("c1", "chi2", 0, 0, 1000, 800);

    const Int_t n     = 5;
    Double_t a[n]     = {9.8, 21.2, 34.5, 39.9, 48.5};
    Double_t F[n]     = {1.0, 2.0,  3.0,  4.0,  5.0};
    Double_t err_a[n] = {1.0, 1.9,  3.1,  3.9,  5.1};
    Double_t err_F[n] = {0.0, 0.0,  0.0,  0.0,  0.0};

    TGraphErrors *gr = new TGraphErrors(n, F, a, err_F, err_a);
    gr->SetTitle("Masa; F; a");
    gr->SetMarkerColor(kMagenta);
    gr->SetMarkerStyle(kFullCircle);
    gr->Draw("AP");

    TF1 *fja = new TF1("fja", "1.0/[0]*x", 0., 6.);
    fja->SetParName(0, "m");
    fja->SetParameter(0, 1.);
    gr->Fit(fja);

    gStyle->SetOptFit();


    c->SaveAs("masa.png");

    TF1 *chi2 = new TF1("chi2", "(9.8-x*1.0)^2/1.0^2 + (21.2-x*2.0)^2/1.9^2 + (34.5-x*3.0)^2/3.1^2 + (39.9-x*4.0)^2/3.9^2 + (48.5-x*5.0)^2/5.1^2", 0., 20.);
    chi2->SetLineColor(kBlue);
    chi2->SetTitle("#chi^{2}(#theta)");
    chi2->Draw();

    c->SaveAs("chi2.png");

    return 0;
}

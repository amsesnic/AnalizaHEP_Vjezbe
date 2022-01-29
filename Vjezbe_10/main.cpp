#include <TROOT.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TGraphErrors.h>
#include <TF1.h>
#include <TMath.h>
#include <TLine.h>
#include <iostream>

int main(){

    TCanvas *c = new TCanvas("c", "masa", 0, 0, 1000, 800);
    //TCanvas *c1 = new TCanvas("c1", "chi2", 0, 0, 1000, 800);

    const Int_t n     = 5;
    Double_t a[n]     = {9.8, 21.2, 34.5, 39.9, 48.5};
    Double_t F[n]     = {1.0, 2.0,  3.0,  4.0,  5.0};
    Double_t err_a[n] = {1.0, 1.9,  3.1,  3.9,  5.1};
    Double_t err_F[n] = {0.0, 0.0,  0.0,  0.0,  0.0};

    // zadatak 1: fitanje podataka
    TGraphErrors *gr = new TGraphErrors(n, F, a, err_F, err_a);
    gr->SetTitle("Veza sile i akceleracije; F; a");
    gr->SetMarkerColor(kMagenta);
    gr->SetMarkerStyle(kFullCircle);
    gr->Draw("AP");

    TF1 *fja = new TF1("fja", "1.0/[0]*x", 0., 6.);
    fja->SetParName(0, "m");
    fja->SetParameter(0, 1.);
    gr->Fit(fja);

    gStyle->SetOptFit();

    c->SaveAs("zad1-masa.png");

    // zadatak 2: analiticki racun za procjenu parametra theta->m
    Double_t theta, brojnik = 0., nazivnik = 0., sigma_t, sigma_m;
    for(int i = 0; i < n; i++){
        brojnik += F[i]*a[i]/(err_a[i]*err_a[i]);
        nazivnik += F[i]*F[i]/(err_a[i]*err_a[i]);
    }
    theta = brojnik/nazivnik;
    sigma_t = 1./TMath::Sqrt(nazivnik);
    sigma_m = sigma_t/(theta*theta);
    std::cout << "\nZADATAK 2:\n   theta analiticki = " << theta << " +- " << sigma_t << "\n";
    std::cout << "   masa analiticki = " << 1./theta << " +- " << sigma_m << "\n\n";

    // zadatak 3: crtanje funkcije chi^2
    TF1 *chi2 = new TF1("chi2", "(9.8-x*1.0)^2/1.0^2 + (21.2-x*2.0)^2/1.9^2 + (34.5-x*3.0)^2/3.1^2 + (39.9-x*4.0)^2/3.9^2 + (48.5-x*5.0)^2/5.1^2", 8., 12.);
    chi2->SetLineColor(kBlue);
    chi2->SetTitle("#chi^{2}(#theta); #theta; #chi^{2}");
    chi2->Draw();


    Double_t theta_min = chi2->GetMinimumX();
    Double_t err_min_left = theta_min - chi2->GetX(chi2->GetMinimum()+1., 8.5, theta_min); //ogranicih domenu potrage
    Double_t err_min_right = chi2->GetX(chi2->GetMinimum()+1., theta_min, 11.5) - theta_min;
    Double_t masa_min = 1./theta_min;
    Double_t err_masa_left = err_min_left/TMath::Power(theta,2);
    Double_t err_masa_right = err_min_right/TMath::Power(theta,2);

    std::cout << "\nZADATAK 3:\n   theta minimum od chi^2 (graf) = " << theta_min << " + " << err_min_right << " - " << err_min_left << "\n";
    std::cout << "   masa po minimumu od chi^2 (graf) = " << masa_min << " + " << err_masa_right << " - " << err_masa_left << "\n";

    // zadatak 4: linije na grafu od chi^2
    TLine *l_middle = new TLine(theta_min, 0.9, theta_min, chi2->Eval(theta_min));
    TLine *l_left   = new TLine(theta_min - err_min_left, 0.9, theta_min - err_min_left, chi2->Eval(theta_min - err_min_left));
    TLine *l_right  = new TLine(theta_min + err_min_right, 0.9, theta_min + err_min_right, chi2->Eval(theta_min + err_min_right));

    l_middle->SetLineStyle(kDashed);
    l_left->SetLineStyle(kDashed);
    l_right->SetLineStyle(kDashed);

    l_middle->SetLineColor(kRed);
    l_left->SetLineColor(kRed);
    l_right->SetLineColor(kRed);

    l_middle->SetLineWidth(3);
    l_left->SetLineWidth(3);
    l_right->SetLineWidth(3);

    l_middle->Draw();
    l_left->Draw();
    l_right->Draw();
    c->SaveAs("zad3-chi2.png");

    return 0;
}

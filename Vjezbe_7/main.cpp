#include <Analyzer.h>

int main(){

    Analyzer *a = new Analyzer();
    TCanvas *c1 = new TCanvas("c1", "higgs i pozadina",0,0, 800, 600);
    THStack *hstack = new THStack("hstack", "Four lepton mass");
    TLegend *leg = new TLegend(0.7, 0.8, 0.9, 0.9); //koordinate dvaju vrhova

    a->PlotHistogram("ggH125");
    a->PlotHistogram("qqZZ"); //sad sam napunila oba histograma za masu 4l    
    
    hstack->Add(a->h_m4l_pozadina); //prvo dodaj pozadinu
    hstack->Add(a->h_m4l_higgs);    //onda dodaj higgsa da se zbroji s pozadinom

    hstack->Draw("histo");   
    hstack->GetXaxis()->SetTitle("m_{4l} (GeV)");      //OVO NAKON Draw()!!!
    hstack->GetYaxis()->SetTitle("Number of events / 2 GeV");
    
    leg->AddEntry(a->h_m4l_higgs, "gg->H", "fl");
    leg->AddEntry(a->h_m4l_pozadina, "qq->ZZ", "fl");
    leg->Draw();

    c1->SaveAs("4l-masa-higg+pozadina.png");
    delete c1;
    delete a;
    delete hstack;
    delete leg;    
    return 0;
}

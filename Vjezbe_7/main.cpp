#include <Analyzer.h>

int main(){

    Analyzer *a = new Analyzer();
    TCanvas *c1 = new TCanvas("c1", "higgs i pozadina",0,0, 800, 600);
    THStack *hstack = new THStack("hstack", "");

    a->PlotHistogram("ggH125");
    a->PlotHistogram("qqZZ"); //sad sam napunila oba histograma za masu 4l    
    
    hstack->Add(a->h_m4l_higgs);
    hstack->Add(a->h_m4l_pozadina);
    hstack->Draw();
    
    c1->SaveAs("4l-masa-higg+pozadina.png");
    delete c1;
    delete a;
    delete hstack;
    
    return 0;
}

#include <Analyzer.h>

int main(){

    Analyzer *a = new Analyzer();

    a->PlotHistogram("ggH125");
    a->PlotHistogram("qqZZ"); //sad sam napunila oba histograma za masu 4l    
    //a->PlotPublicHistograms(); //ZADATAK 1
    a->Model_70_170GeV();    //ZADATAK 2 - pokreni nakon sto promijenis granice za histograme na 70-170

    delete a;
 
    return 0;
}

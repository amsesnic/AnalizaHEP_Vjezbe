#include <Analyzer.h>

int main(){

    Analyzer *a = new Analyzer();

    a->PlotHistogram("ggH125");
    a->PlotHistogram("qqZZ"); //sad sam napunila oba histograma za masu 4l    
    //a->PlotPublicHistograms(); 
    a->Model_70_170GeV();

    delete a;
 
    return 0;
}

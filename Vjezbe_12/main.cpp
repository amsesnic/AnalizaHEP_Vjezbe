#include <Analyzer.h>

int main(){

    Analyzer *a = new Analyzer();

    //a->Loop();
    //a->MVATraining();
    a->MVAPlotResults();

    delete a;
 
    return 0;
}

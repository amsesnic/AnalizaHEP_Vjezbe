#include <Analyzer.h>

int main(){

    Analyzer *a = new Analyzer();

    a->PlotHistogram();

    delete a;
 
    return 0;
}

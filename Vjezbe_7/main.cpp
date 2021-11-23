#include <Analyzer.h>

int main(){

    Analyzer *a = new Analyzer();
    a->PlotHistogram("ggH125");
    a->PlotHistogram("qqZZ");
    return 0;
}

#include <Analyzer.h>

int main(){

    Analyzer *a = new Analyzer();

    TString dir_name = "qqZZ";

    a->PlotHistogram(dir_name);

    return 0;
}

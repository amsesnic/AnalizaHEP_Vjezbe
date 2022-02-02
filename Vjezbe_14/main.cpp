#include <Analyzer.h>

int main(){

    Analyzer *a = new Analyzer();

    a->GenerateTstatistic();
    a->PvalueScan();

    delete a;
 
    return 0;
}

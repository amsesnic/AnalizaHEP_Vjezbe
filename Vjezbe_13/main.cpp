#include <Analyzer.h>

int main(){

    Analyzer *a = new Analyzer();

    a->Loop(); //prvo izracunaj t observed
    a->GenerateTstatistic();

    delete a;
 
    return 0;
}

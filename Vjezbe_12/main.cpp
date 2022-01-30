#include <Analyzer.h>

int main(){

    Analyzer *a = new Analyzer();

    a->Loop();
    //a->MVATraining();

    delete a;
 
    return 0;
}

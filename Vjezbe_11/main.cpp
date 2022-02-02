#include <Analyzer.h>

int main(){

    Analyzer *a = new Analyzer();

    Int_t r = 10, N[10] = {50, 100, 120, 130, 140, 150, 160, 170, 173, 175};
    Double_t p = 0.32, prob;

    for(int i=0; i<10; i++){
        prob = a->Binomial(r, p, N[i]);
        std::cout << "B(r; p, N) = B(" << r << "; " << p << ", " << N[i] << ") = " << prob << "\n";
    }

    delete a; 
    return 0;
}

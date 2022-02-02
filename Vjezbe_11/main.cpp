#include <Analyzer.h>

int main(){

    Analyzer *a = new Analyzer();

    Int_t r = 10, N[10] = {50, 100, 120, 130, 140, 150, 160, 170, 173, 175};
    Double_t p = 0.32, prob;

/*    for(int i=0; i<10; i++){
        prob = a->Binomial(r, p, N[i]);
        std::cout << "B(r; p, N) = B(" << r << "; " << p << ", " << N[i] << ") = " << prob << "\n";
    }
*/

    Double_t *pInterval;
    Int_t ukupno = 10;
    for(int i=0; i<=ukupno; i++){
        pInterval = a->ClopperPearson(i, ukupno, 0.6827); // povoljni, ukupno, C
        std::cout << "C-P interval for " << i << "/" << ukupno << " successful outcomes: [" << pInterval[0] << ", " << pInterval[1] << "]\n";
    }

    a->PojasPouzdanosti(5);

    a->Kocka(10,0.6827); // 1 sigma
    a->Kocka(10,0.954);  // 2 sigma

    delete a; 
    return 0;
}

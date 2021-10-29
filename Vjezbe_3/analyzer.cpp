#include <iostream>
#include <fstream>
#include <string>
#include "ElementaryParticle.h"
#include "ran1.h"

#define N_HIGGS 10000
#define P_MIN -100.
#define P_MAX  100.

#define IME_DAT "Analysis.txt"

using namespace std;

int main(){
	ElementaryParticle* higgs[N_HIGGS];
	ElementaryParticle* decayParticle_1[N_HIGGS];
	ElementaryParticle* decayParticle_2[N_HIGGS];
	double p_komp[3], deltaP;
	long idum = (-503); //seed za ran1 je negativni cijeli broj
	int i, j;

        /* KREIRAJ I OTVORI DATOTEKU */
	fstream fout; //stvori objekt, moze klasa ofstream za output i ifstream za input
	fout.open(IME_DAT, ios::out); //pozovi metodu klase fstream, app=pisi na kraj
	fout << "#        IME           MASA BOZON?              E             PX             PY             PZ         transP\n";

	deltaP = P_MAX-P_MIN; //pomocna varijabla za sirinu intervala
                          //mogucih vrijednosti komponenti zaleta

	for(i=0; i<N_HIGGS; i++){
        higgs[i] = new ElementaryParticle("Higgsov_bozon", 125., true);//dinamicka alokacija memorije

        for(j=0; j<3; j++){                   //nasumicne komponente zaleta
            p_komp[j] = ran1(&idum)*deltaP + P_MIN; //u intervalu [P_MIN,P_MAX]
        }
        higgs[i]->postaviMoment(p_komp[0], p_komp[1], p_komp[2]);
        if(i%500==0){
            higgs[i]->printInfo();
            cout << "\n";
        }

        decayParticle_1[i] = new ElementaryParticle();
        decayParticle_2[i] = new ElementaryParticle();

        higgs[i]->bosonDecay(decayParticle_1[i], decayParticle_2[i], &idum);
        decayParticle_1[i]->printInfo(fout);
        decayParticle_2[i]->printInfo(fout);
        fout << "\n";
	}


	for(i=0; i<N_HIGGS; i++){
        delete higgs[i];
        delete decayParticle_1[i];
        delete decayParticle_2[i];
    }
    fout.close();
	return 0;
}

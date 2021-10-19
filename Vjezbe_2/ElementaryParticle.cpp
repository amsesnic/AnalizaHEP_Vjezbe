/* DEFINICIJA METODA IZ KLASE ElementaryParticle*/
#include <iostream>
#include <string>
#include "ElementaryParticle.h"

using namespace std;

void ElementaryParticle::printInfo(){
	cout << "Ime: " << ime << "\n";
	cout << "Masa: " << masa << " GeV\n";
	cout << "Je li " << ime << " bozon? " << bozon << "\n";
	cout << "Hej, opet novost!"; 
}

ElementaryParticle::ElementaryParticle(){
	//ne radi nista, ovo je trivijalni konstruktor
}

ElementaryParticle::ElementaryParticle(string i, double m, bool b){
			ime = i;
			masa = m;
			bozon = 0;
}


#include <iostream>
#include <string>
#include "ElementaryParticle.h"

using namespace std;

int main(){
	ElementaryParticle *higgs, *p1, *p2;
	double px, py, pz;
	
	higgs = new ElementaryParticle("Higgsov bozon", 125, true); //dinamicka alokacija memorije
	p1 = new ElementaryParticle();
	p2 = new ElementaryParticle();
	
	higgs->printInfo();
	
	px = 10.;
	py = 5.;
	pz = 4.;
	higgs->postaviMoment(px, py, pz);

	higgs->ispisiTransP();

	higgs->bosonDecay(p1, p2);

	delete higgs;
	delete p1;
	delete p2;
	return 0;
}

#include <iostream>
#include <string>
#include "ElementaryParticle.h"

using namespace std;

int main(){
	ElementaryParticle higgs, top;
	ElementaryParticle* Z; //pokazivac na objekt klase
	
	Z = new ElementaryParticle("Z bozon", 91, true); //dinamicka alokacija memorije - pokazivaci
	
	higgs.ime = "Higgsov bozon";
	higgs.masa = 125;
	higgs.bozon = true;
	top.ime = "top kvark";
	top.masa = 173;
	top.bozon = false;
	
	higgs.printInfo();
	top.printInfo();
	/*
	Z->ime = "Z bozon";
	Z->masa = 91;
	Z->bozon = true;
	*/
	Z->printInfo();

	delete Z;
	return 0;
}

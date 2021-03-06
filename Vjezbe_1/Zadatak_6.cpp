#include <iostream>
#include <string>

using namespace std;

class ElementaryParticle {
	public:
		string ime;
		double masa;
		bool bozon;
		void printInfo(){
			cout << "Ime: " << ime << "\n";
			cout << "Masa: " << masa << " GeV\n";
			cout << "Je li " << ime << " bozon? " << bozon << "\n"; 
		}
		ElementaryParticle(){} //overload konstruktora
		ElementaryParticle(string i, double m, bool b){
			ime = i;
			masa = m;
			bozon = b;
		}
		
};

int main(){
	ElementaryParticle higgs, top;// zboz;
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

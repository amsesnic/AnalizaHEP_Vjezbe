/* DEKLARACIJA KLASE, ATRIBUTA I METODA */
#include <iostream>
#include <string>
//using namespace std;

class ElementaryParticle {
	public:
		std::string ime;
		double masa;
		bool bozon;
		double moment[4];

		void printInfo();
		void postaviMoment(double px, double py, double pz);
		void ispisiTransP();
		void bosonDecay(ElementaryParticle* p1, ElementaryParticle* p2);

		ElementaryParticle(); //overload konstruktora
		ElementaryParticle(std::string i, double m, bool b);
};

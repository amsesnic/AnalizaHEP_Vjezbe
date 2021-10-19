/* DEKLARACIJA KLASE, ATRIBUTA I METODA */
#include <iostream>
#include <string>
//using namespace std;

class ElementaryParticle {
	public:
		std::string ime;
		double masa;
		bool bozon;

		void printInfo();
		ElementaryParticle(); //overload konstruktora
		ElementaryParticle(std::string i, double m, bool b);
};


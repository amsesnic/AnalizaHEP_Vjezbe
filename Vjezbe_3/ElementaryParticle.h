/* DEKLARACIJA KLASE, ATRIBUTA I METODA */
#include <iostream>
#include <fstream>
#include <string>
//using namespace std;

class ElementaryParticle {
	public:
		std::string ime;
		double masa;
		bool bozon;
		double moment[4];

		void printInfo();
		void printInfo(std::fstream& output_file);

		void postaviMoment(double px, double py, double pz);

		void ispisiTransP();
		void ispisiTransP(std::fstream& output_file);

		void bosonDecay(ElementaryParticle* p1, ElementaryParticle* p2, long* idum_ptr);

		ElementaryParticle(); //overload konstruktora
		ElementaryParticle(std::string i, double m, bool b);
};

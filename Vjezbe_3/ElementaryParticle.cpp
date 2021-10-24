/* DEFINICIJA METODA IZ KLASE ElementaryParticle*/
#include <iostream> //svugdje ukljucujem ove biblioteke - PROVJERIT!
#include <fstream>
#include <iomanip> //number formatting
#include <string>
#include <cmath>

#include "ElementaryParticle.h"
#include "ran1.h"


void ElementaryParticle::printInfo()
{ //Na zaslon ispisuje ime, masu, je li bozon i 4-vektor.
	std::cout << "Ime: " << this->ime << "\n";
	std::cout << "Masa: " << this->masa << " GeV\n";
	std::cout << "Je li " << this->ime << " bozon? " << this->bozon << "\n";
	std::cout << "4-vektor momenta: ( E, px, py, pz ) = ( ";
	for(int i=0; i<=3; i++){
        std::cout << this->moment[i];
        if(i!=3) std::cout << ", ";
    }
    std::cout << " )\n";
}

void ElementaryParticle::printInfo(std::fstream& output_file)
{ //U datoteku ispisuje ime, masu, je li bozon i 4-vektor.
        /* SPREMI TRENUTNE POSTAVKE */
    std::ios::fmtflags old_settings = output_file.flags(); //save previous format flags
    int old_precision = output_file.precision();      //save previous precision setting

    // Don't need to save width setting, because it automatically resets
    // to default value after each numeric output item.

    output_file << std::fixed << std::setprecision(6);
        // using manipulators
        // kad stavim "fixed", onda "precision" znaci broj decimalnih mjesta
        // namijestam "width" s manipulatorom setw() za ukupnu duljinu ispisa

    output_file << std::setw(12) << this->ime;
    output_file << std::setw(15) << this->masa;
    output_file << std::setw(7) << this->bozon;
    for(int i=0; i<=3; i++){
        output_file << std::setw(15) << this->moment[i];
    }
    output_file << "\n";


    //vracanje na stare postavke
    output_file.flags(old_settings);
    output_file.precision(old_precision);

}

void ElementaryParticle::postaviMoment(double px, double py, double pz)
{ //Postavlja komponente zaleta na dane vrijednosti i racuna energiju
	this->moment[1] = px;
	this->moment[2] = py;
	this->moment[3] = pz;
	this->moment[0] = sqrt(px*px + py*py + pz*pz + (this->masa)*(this->masa) );
}

void ElementaryParticle::ispisiTransP()
{ //Ispisuje iznos transverzalnog zaleta
	double pT;
	pT = sqrt(this->moment[1]*this->moment[1] + this->moment[2]*this->moment[2]);
	std::cout << "Transverzalni zalet iznosi p_T = " << pT << "\n";
}

void ElementaryParticle::bosonDecay(ElementaryParticle* p1, ElementaryParticle* p2, long* idum_ptr)
{ //Raspad bozona na dvije cestice
	double r1;
	int i;

	//std::cout << "Usla sam u bosonDecay()\n";

	if(this->bozon == false) std::cout << "Raspad nije moguc!\n";
    else { //ODREDUJE SVOJSTVA I 4-VEKTOR PRODUKATA

        r1 = ran1(idum_ptr); //radom generator daje broj u intervalu [0,1]
        //std::cout << "random: " << r1 << "\n";

        if(r1 <= 0.214) {
            //std::cout << "raspad na W bozone\n";
            p1->ime = "W bozon";
            p1->masa = 80.3;
            p1->bozon = true;
            p2->ime = "W bozon";
            p2->masa = 80.3;
            p2->bozon = true;
        }
        else if(r1 <= 0.278) {
            //std::cout << "raspad na tau leptone\n";
            p1->ime = "tau lepton";
            p1->masa = 1776.;
            p1->bozon = false;
            p2->ime = "tau lepton";
            p2->masa = 1776.;
            p2->bozon = false;
        }
        else if(r1 <= 0.304) {
            //std::cout << "raspad na Z bozone\n";
            p1->ime = "Z bozon";
            p1->masa = 91.18;
            p1->bozon = true;
            p2->ime = "Z bozon";
            p2->masa = 91.18;
            p2->bozon = true;
        }
        else {
            //std::cout << "raspad na b kvarkove";
            p1->ime = "b kvark";
            p1->masa = 4.1;
            p1->bozon = false;
            p2->ime = "b kvark";
            p2->masa = 4.1;
            p2->bozon = false;
        }

            /* NASUMICNO RASPODJELI KOMPONENTE ZALETA */
        for(i=1; i<=3; i++){
            r1 = ran1(idum_ptr); //mogu iskoristit istu varijablu za novi slucajni broj
            p1->moment[i] = (this->moment[i]) * r1;
            p2->moment[i] = (this->moment[i]) * (1.0-r1); //zakon ocuvanja zaleta

            p1->moment[0] += (p1->moment[i])*(p1->moment[i]); //konstruktor je postavio moment[0]=0.
            p2->moment[0] += (p2->moment[i])*(p2->moment[i]);
        }
            /* IZRACUNAJ ENERGIJU */
        p1->moment[0] += (p1->masa)*(p1->masa);
        p1->moment[0] = sqrt(p1->moment[0]);

        p2->moment[0] += (p2->masa)*(p2->masa);
        p2->moment[0] = sqrt(p2->moment[0]);
	}
}


/** KONSTRUKTORI **/
ElementaryParticle::ElementaryParticle()
{ //Postavlja sve atribute objekta na nulu.
	this->ime = " ";
	this->masa = 0.;
	this->bozon = 0;
	for(int i=0; i<=3; i++)
        this->moment[i] = 0.;
}

ElementaryParticle::ElementaryParticle(std::string i, double m, bool b){
	this->ime = i;
	this->masa = m;
	this->bozon = b;
}

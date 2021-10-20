/* DEFINICIJA METODA IZ KLASE ElementaryParticle*/
#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <time.h>
#include "ElementaryParticle.h"

using namespace std;



void ElementaryParticle::printInfo(){
	cout << "Ime: " << this->ime << "\n";
	cout << "Masa: " << this->masa << " GeV\n";
	cout << "Je li " << this->ime << " bozon? " << this->bozon << "\n";
}

void ElementaryParticle::postaviMoment(double px, double py, double pz){
	this->moment[1] = px;
	this->moment[2] = py;
	this->moment[3] = pz;
	this->moment[0] = sqrt(px*px + py*py + pz*pz + masa*masa);
}

void ElementaryParticle::ispisiTransP(){
	double pT;
	pT = sqrt(this->moment[1]*this->moment[1] + this->moment[2]*this->moment[2]);
	cout << "Transverzalni zalet iznosi p_T = " << pT << "\n";
}

void ElementaryParticle::bosonDecay(ElementaryParticle* p1, ElementaryParticle* p2){
	if(this->bozon == false)
		cout << "Raspad nije moguc!\n";
	cout << "Usla sam u bosonDecay()\n";
	
	srand(time(NULL)); //inicijalizacija random seed-a
	double r1 = rand()/RAND_MAX;
	if(r1 <= 0.214) {/* rapad na W bozone*/}
	else if(r1 <= 0.278) {/*raspad na tau leptone*/}
	else if(r1 <= 0.304) {/*raspad na Z bozone*/}
	else {/*raspad na b kvarkove*/}
	cout << "random: " << r1;
}

ElementaryParticle::ElementaryParticle(){
	this->ime = " ";
	this->masa = 0.;
	this->bozon = 0;
}

ElementaryParticle::ElementaryParticle(string i, double m, bool b){
	this->ime = i;
	this->masa = m;
	this->bozon = 0;
}


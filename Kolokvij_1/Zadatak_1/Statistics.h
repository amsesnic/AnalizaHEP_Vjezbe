#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

class Statistics {
    public:
        Statistics(); //konstruktor
        void CalculatePi(int N_events, long* idum_ptr);
        void NormalDistribution(double x, double mi, double s);

};

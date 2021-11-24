#include <Statistics.h>
#include <ran1.h> //Ovo je generator slucajnih brojeva sa kolegija Stohasticke simulacije

Statistics::Statistics()
{
    cout << "Objekt uspjesno kreiran.\n";
}

void Statistics::CalculatePi(int N_events, long* idum_ptr)
{
    double x, y, r;
    double pi=0;
    int i;
    
    //cout << "Random broj od 0 do 1: " << ran1(idum_ptr) << endl;
    
    for(i=0; i<=N_events; i++){
        x = ran1(idum_ptr); // fja ran1 prilikom svakog poziva promijeni seed
        y = ran1(idum_ptr);
        r = sqrt(x*x + y*y);

        if(r<=1.) pi += 1.0;
    }
    pi = 4.*pi/N_events;
    cout << "pi = " << pi << endl;
}



void Statistics::NormalDistribution(double x, double mi, double s)
{
    double P;
    double pi = 3.14159265358979323846;
    P = 1.0/(s*sqrt(2*pi)) * exp(-1.0 * (x-mi)*(x-mi) / (2.0*s*s) );
    cout << "P(" << x << ", " << mi << ", " << s << ") = " << P << endl;

}

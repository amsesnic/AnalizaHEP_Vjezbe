#include <Statistics.h>


int main(){
  
    Statistics *s = new Statistics();

    s->NormalDistribution(185., 178.2, 6.4);
    s->NormalDistribution(205., 178.2, 6.4);
    s->NormalDistribution(185., 160.2, 7.2);

    long idum = (-6789); // seed za ran1 je negativni cijeli broj
    s->CalculatePi(10000000, &idum);

    return 0;

}

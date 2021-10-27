#include "Analyzer.h"

#define N_HIGGS 10000
#define P_MIN -100.
#define P_MAX  100.

#define IME_DAT "Analysis.txt"

using namespace std;

int main(){
	Analyzer* a;
	a = new Analyzer();

	a->ReadFile("Analysis.txt");	

	delete a;
	return 0;
}

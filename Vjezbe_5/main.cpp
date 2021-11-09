#include <Analyzer.h>

using namespace std;

int main(){
	
	Analyzer *a = new Analyzer();
	
	//a->Loop(); //ovdje ispisuje varijable na ekran
	a->PlotHistogram();
	return 0;
}

#include "Analyzer.h"

#define IME_DAT "Analysis.txt"

using namespace std;

int main(){
	Analyzer* a;
	a = new Analyzer();

	a->ConvertTxtToRootFile(IME_DAT);	

	delete a;
	return 0;
}

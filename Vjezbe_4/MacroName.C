#include <cmath>
void MacroName(){
	double x[4] = {0,1,10,20};
	for(int i=0; i<4; i++){
		std::cout << exp(-x[i]*x[i]*0.2)-TMath::Gaus(x[i]) << std::endl;
	}
}

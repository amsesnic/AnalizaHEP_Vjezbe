#include <iostream>
using namespace std;

double my_cube(double x){
	return x*x*x;
}

int main(){
	double x, x3;
	cout << "Upisi realan broj: x = ";
	cin >> x;
	
	//x3=x*x*x;
	x3 = my_cube(x);
	cout << "x^3 = " << x3 << endl;
	return 0;
}



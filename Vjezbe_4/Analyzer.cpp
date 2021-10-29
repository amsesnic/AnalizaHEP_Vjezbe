#include "Analyzer.h"

void Analyzer::ReadFile(string input_file)
{
	ifstream fin;
	fin.open(input_file.c_str());
	
	string line;
	_skipFirstLine = true;
	
	if(fin.is_open()){
		while(getline(fin, line)){
			stringstream linestream(line); //linestream je moje ime za objekt klase 'stringstream' a konstruktoru sam predala string 'line'
						       //podijeli mi redak s obzirom na razmake
			
			if(_skipFirstLine){
				_skipFirstLine=false;
				continue;	
			}
		
			linestream >> particleName >> mass >> ifBoson >> momentum[0] >> momentum[1] >> momentum[2] >> momentum[3] >> transP;
			cout << particleName << " " << mass << endl;
		}
	}	
	
	fin.close();


}

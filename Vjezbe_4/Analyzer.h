#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>

using namespace std; 

class Analyzer{
	public:
		string particleName;
		double mass;
		bool ifBoson;
		double momentum[4], transP;
		bool _skipFirstLine;

		void ReadFile(string input_file);
		//defaultni konstruktor

};

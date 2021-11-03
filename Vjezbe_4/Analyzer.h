#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TApplication.h>

using namespace std; 

class Analyzer{
	public:
		string particleName;
		double mass;
		bool ifBoson;
		double momentum[4], transP;
		bool _skipFirstLine;

		void ReadFile_FillTree(string input_file, TTree* tree);
		void ConvertTxtToRootFile(string txt_file);
		//defaultni konstruktor

};

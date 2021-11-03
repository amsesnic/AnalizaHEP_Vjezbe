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
		string particleName1, particleName2;
		double mass1, mass2;
		bool ifBoson1, ifBoson2;
		double momentum1[4], momentum2[4], transP1, transP2;
		bool _skipFirstLine;

		void ReadFile_FillTree(string input_file, TTree* tree);
		void ConvertTxtToRootFile(string txt_file);
		//defaultni konstruktor

};

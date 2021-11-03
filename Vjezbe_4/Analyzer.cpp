#include "Analyzer.h"

void Analyzer::ReadFile_FillTree(string input_file, TTree* tree)
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
			tree->Fill();
		}
	}	
	
	fin.close();


}

void Analyzer::ConvertTxtToRootFile(string txt_file)
{ //konvertiraj .txt -> .root

	TFile* root_file;
	TTree* tree;
	
	root_file = TFile::Open("Analysis.root", "RECREATE");
	tree = new TTree("tree","Boson Decay Vjezbe 4");

	//Branch(name, address, string describing the leaf list); leaf: name/type
	tree->Branch("Particle_name", &particleName, "name/S");	
	tree->Branch("Mass", &mass, "mass/D");
	tree->Branch("Is_it_a_boson", &ifBoson, "ifBoson/B");
	tree->Branch("Energy", &momentum[0], "Energy/D");
	tree->Branch("Px", &momentum[1], "Px/D");
	tree->Branch("Py", &momentum[2], "Py/D");
	tree->Branch("Pz", &momentum[3], "Pz/D");
	tree->Branch("TransP", &transP, "transP/D");		
	
	this->ReadFile_FillTree(txt_file, tree);	
	
	tree->Print();
	tree->Write();//provjeri!

	delete tree;
	delete root_file;
	
}

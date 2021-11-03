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
			linestream >> particleName1 >> mass1 >> ifBoson1 >> momentum1[0] >> momentum1[1] >> momentum1[2] >> momentum1[3] >> transP1 >> particleName2 >> mass2 >> ifBoson2 >> momentum2[0] >> momentum2[1] >> momentum2[2] >> momentum2[3] >> transP2;
			
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
	tree->Branch("Particle_name_1", &particleName1, "name/S");	
	tree->Branch("Mass_1", &mass1, "mass/D");
	tree->Branch("Is_it_a_boson_1", &ifBoson1, "ifBoson/B");
	tree->Branch("Energy_1", &momentum1[0], "Energy/D");
	tree->Branch("Px_1", &momentum1[1], "Px/D");
	tree->Branch("Py_1", &momentum1[2], "Py/D");
	tree->Branch("Pz_1", &momentum1[3], "Pz/D");
	tree->Branch("TransP_1", &transP1, "transP/D");

	tree->Branch("Particle_name_2", &particleName2, "name/S");	
	tree->Branch("Mass_2", &mass2, "mass/D");
	tree->Branch("Is_it_a_boson_2", &ifBoson2, "ifBoson/B");
	tree->Branch("Energy_2", &momentum2[0], "Energy/D");
	tree->Branch("Px_2", &momentum2[1], "Px/D");
	tree->Branch("Py_2", &momentum2[2], "Py/D");
	tree->Branch("Pz_2", &momentum2[3], "Pz/D");
	tree->Branch("TransP_2", &transP2, "transP/D");		
	
	this->ReadFile_FillTree(txt_file, tree);	
	
	tree->Print();
	tree->Write();//provjeri!

	delete tree;
	delete root_file;
	
}

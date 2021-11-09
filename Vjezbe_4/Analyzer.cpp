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
	tree->Branch("Particle_name_1", &particleName1);	
	tree->Branch("Mass_1",          &mass1,         "mass1/D");
	tree->Branch("Is_it_a_boson_1", &ifBoson1,      "ifBoson1/O");
	tree->Branch("Energy_1",        &momentum1[0],  "energy1/D");
	tree->Branch("Px_1",            &momentum1[1],  "px_1/D");
	tree->Branch("Py_1",            &momentum1[2],  "py_1/D");
	tree->Branch("Pz_1",            &momentum1[3],  "pz_1/D");
	tree->Branch("TransP_1",        &transP1,       "pt_1/D");

	tree->Branch("Particle_name_2", &particleName2);	
	tree->Branch("Mass_2",          &mass2);
	tree->Branch("Is_it_a_boson_2", &ifBoson2);
	tree->Branch("Energy_2",        &momentum2[0]);
	tree->Branch("Px_2",            &momentum2[1]);
	tree->Branch("Py_2",            &momentum2[2]);
	tree->Branch("Pz_2",            &momentum2[3]);
	tree->Branch("TransP_2",        &transP2);		
	
	this->ReadFile_FillTree(txt_file, tree);	
	
	tree->Print(); // see the summary of the tree structure
	tree->Write(); // write the tree header into a ROOT file

	delete tree;
	delete root_file;
	
}

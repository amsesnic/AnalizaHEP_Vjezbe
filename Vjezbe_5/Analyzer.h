//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sat Nov  6 22:03:23 2021 by ROOT version 6.24/04
// from TTree tree/Boson Decay Vjezbe 4
// found on file: Analysis.root
//////////////////////////////////////////////////////////

#ifndef Analyzer_h
#define Analyzer_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH2.h>

// Header file for the classes stored in the TTree if any.
#include "string"

class Analyzer {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   std::string         *Particle_name_1;
   //TString         Particle_name_1;
   Double_t        Mass_1;
   Bool_t          Is_it_a_boson_1;
   Double_t        Energy_1;
   Double_t        Px_1;
   Double_t        Py_1;
   Double_t        Pz_1;
   Double_t        TransP_1;
   std::string         *Particle_name_2;
   //TString         Particle_name_2;
   Double_t        Mass_2;
   Bool_t          Is_it_a_boson_2;
   Double_t        Energy_2;
   Double_t        Px_2;
   Double_t        Py_2;
   Double_t        Pz_2;
   Double_t        TransP_2;

   // List of branches
   TBranch        *b_Particle_name_1;   //!
   TBranch        *b_Mass_1;   //!
   TBranch        *b_Is_it_a_boson_1;   //!
   TBranch        *b_Energy_1;   //!
   TBranch        *b_Px_1;   //!
   TBranch        *b_Py_1;   //!
   TBranch        *b_Pz_1;   //!
   TBranch        *b_TransP_1;   //!
   TBranch        *b_Particle_name_2;   //!
   TBranch        *b_Mass_2;   //!
   TBranch        *b_Is_it_a_boson_2;   //!
   TBranch        *b_Energy_2;   //!
   TBranch        *b_Px_2;   //!
   TBranch        *b_Py_2;   //!
   TBranch        *b_Pz_2;   //!
   TBranch        *b_TransP_2;   //!

   Analyzer(TTree *tree=0);
   virtual ~Analyzer();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual void     Loop(TH1F *h1, TH1F *h2, TH1F *hH);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
           void     PlotHistogram();
};

#endif

#ifdef Analyzer_cxx
Analyzer::Analyzer(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("Analysis.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("Analysis.root");
      }
      f->GetObject("tree",tree);

   }
   Init(tree);
}

Analyzer::~Analyzer()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Analyzer::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Analyzer::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void Analyzer::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   Particle_name_1 = 0;
   Particle_name_2 = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("Particle_name_1", &Particle_name_1, &b_Particle_name_1);
   fChain->SetBranchAddress("Mass_1", &Mass_1, &b_Mass_1);
   fChain->SetBranchAddress("Is_it_a_boson_1", &Is_it_a_boson_1, &b_Is_it_a_boson_1);
   fChain->SetBranchAddress("Energy_1", &Energy_1, &b_Energy_1);
   fChain->SetBranchAddress("Px_1", &Px_1, &b_Px_1);
   fChain->SetBranchAddress("Py_1", &Py_1, &b_Py_1);
   fChain->SetBranchAddress("Pz_1", &Pz_1, &b_Pz_1);
   fChain->SetBranchAddress("TransP_1", &TransP_1, &b_TransP_1);
   fChain->SetBranchAddress("Particle_name_2", &Particle_name_2, &b_Particle_name_2);
   fChain->SetBranchAddress("Mass_2", &Mass_2, &b_Mass_2);
   fChain->SetBranchAddress("Is_it_a_boson_2", &Is_it_a_boson_2, &b_Is_it_a_boson_2);
   fChain->SetBranchAddress("Energy_2", &Energy_2, &b_Energy_2);
   fChain->SetBranchAddress("Px_2", &Px_2, &b_Px_2);
   fChain->SetBranchAddress("Py_2", &Py_2, &b_Py_2);
   fChain->SetBranchAddress("Pz_2", &Pz_2, &b_Pz_2);
   fChain->SetBranchAddress("TransP_2", &TransP_2, &b_TransP_2);
   Notify();
}

Bool_t Analyzer::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Analyzer::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Analyzer::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef Analyzer_cxx

#define Analyzer_cxx
#include <Analyzer.h>

void Analyzer::PlotHistogram(TString dir_name)
{
    //stvori file i ucitaj stablo iz mape koju ti dam
    TTree *tree = new TTree();
    TFile *f = TFile::Open("/home/public/data/" + dir_name + "/ZZ4lAnalysis.root");
    TDirectory * dir = (TDirectory*)f->Get("/home/public/data/" + dir_name + "/ZZ4lAnalysis.root:/ZZTree");
    dir->GetObject("candTree",tree);
    this->Init(tree);

    TCanvas *c   = new TCanvas("c", "Histogrami", 0, 0, 1000, 800);
    TCanvas *c_H = new TCanvas("c_H", "Histogram_H", 0, 0, 800, 600);
   
    //TH1F *h_Higgs    = new TH1F("h_Higgs", "h_Higgs", 25, 90., 140.);
    TH1F *h_LepPt[4];
    TH1F *h_LepEta[4];
    TH1F *h_LepPhi[4];
    TH1F *h_LepBDT[4];
    int i;
    std::string naslov;
    for(i=0; i<4; i++){
        naslov = "h_LepPt"+std::to_string(i);
        h_LepPt[i]  = new TH1F(naslov.c_str(),  naslov.c_str(),  50, 0., 100.);

        naslov = "h_LepEta"+std::to_string(i);
        h_LepEta[i] = new TH1F(naslov.c_str(),  naslov.c_str(), 40, -4., 4.);

        naslov = "h_LepPhi"+std::to_string(i);
        h_LepPhi[i] = new TH1F(naslov.c_str(),  naslov.c_str(), 50, -5., 5.);

        naslov = "h_LepBDT"+std::to_string(i);
        h_LepBDT[i] = new TH1F(naslov.c_str(),  naslov.c_str(), 48, -2., 10.);
    }


    
    /*******   NAPUNI HISTOGRAME U Loop   ********************/
    //Kod kopiran iz Loop() metode
    if (fChain == 0) return;

    TLorentzVector p_Leptons[4];
    TLorentzVector p_Z1, p_Z2, p_H4L;

    // Weighted distributions
    double  w, sum_w, L=137.;
    sum_w = ReadHistogramFromFile(dir_name);
    if(sum_w==0) cout << "sum_w=0!" << endl;
    else {
        cout << "sum_w = " << sum_w << "\n";
        w = (L*xsec*1000.*overallEventWeight)/sum_w; //faktor 1000 zbog jedinica
        cout << "w = " << w << endl;
        cout << "L = " << L << " " << "xsec = " << xsec << " " << "w_event = " << overallEventWeight << endl;
        //nema smisla gledat xsec i overall... ako nismo u petlji po dogadajima
        //te varijable su "leafs"
    }
   
    // Kinematic discriminant
    double Dkin, constant = 70.;

    Long64_t nentries = fChain->GetEntriesFast();

    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry=0; jentry<nentries;jentry++) {
       Long64_t ientry = LoadTree(jentry);
       if (ientry < 0) break;
       nb = fChain->GetEntry(jentry);   nbytes += nb;
       // if (Cut(ientry) < 0) continue;
       
       //calculate weight for current event
       w = (L * xsec * 1000. * overallEventWeight)/sum_w;
       for(i=0; i<4; i++){
           h_LepPt[i] ->Fill(LepPt->at(i), w); //ovako se pristupa elementu vectora s pokazivacem na taj vector
           h_LepEta[i]->Fill(LepEta->at(i), w);
           h_LepPhi[i]->Fill(LepPhi->at(i), w);
           h_LepBDT[i]->Fill(LepBDT->at(i), w );
       }

       //4-momentum calculation
       for(i=0; i<4; i++)
           p_Leptons[i].SetPtEtaPhiM( LepPt->at(i), LepEta->at(i), LepPhi->at(i), 0.); //masa=0
      
       p_Z1 = p_Leptons[0] + p_Leptons[1];
       p_Z2 = p_Leptons[2] + p_Leptons[3];
       p_H4L = p_Z1 + p_Z2;
      
       //Kinematic discriminant for current event
       Dkin = 1.0 + constant * p_QQB_BKG_MCFM / p_GG_SIG_ghg2_1_ghz1_1_JHUGen;
       Dkin = 1.0/Dkin;

       //Fill public histos
       if(dir_name == "ggH125"){    
           h_m4l_higgs->Fill( p_H4L.M(), w);
           h_Dkin_sig->Fill(Dkin, w);
           h_2d_sig->Fill(p_H4L.M(), Dkin, w);
       }
       else if(dir_name == "qqZZ"){
           h_m4l_pozadina->Fill( p_H4L.M(), w);
           h_Dkin_bkg->Fill(Dkin, w);
           h_2d_bkg->Fill(p_H4L.M(), Dkin, w);  
       }
       else {cout << "Krivo ime direktorija" << dir_name << "\n"; return;}

    }
    /*****************************************/


    c->Divide(2,2);
    gStyle->SetOptStat(0);

    /******* PANEL 1 (gore lijevo): LepPt *******/
    c->cd(1);
    gPad->SetLeftMargin(0.15);

    h_LepPt[2]->GetXaxis()->SetTitle("P_{t} (GeV/c)");
    h_LepPt[2]->GetYaxis()->SetTitle("Number of events");
    h_LepPt[2]->SetLineColor(kAzure+1);
    h_LepPt[2]->SetTitle("Lepton transverse momentum");
    h_LepPt[2]->Draw("hist");

    h_LepPt[3]->SetLineColor(kMagenta+1);
    h_LepPt[3]->SetTitle("");
    h_LepPt[3]->Draw("hist same");

    h_LepPt[0]->SetLineColor(kRed+1);
    h_LepPt[0]->SetTitle("");
    h_LepPt[0]->Draw("hist same");
    
    h_LepPt[1]->SetLineColor(kGreen+2);
    h_LepPt[1]->SetTitle("");
    h_LepPt[1]->Draw("hist same");

    //legenda
    TLegend *leg_Pt = new TLegend(0.65,0.75,0.9,0.9);
    std::string opis;
    for(i=0; i<4; i++){
        opis = "lepton " + std::to_string(i+1);
        leg_Pt->AddEntry(h_LepPt[i], opis.c_str(), "l");
    }
    leg_Pt->Draw();

    /******* PANEL 2 (gore desno): LepEta *******/
    c->cd(2);
    gPad->SetLeftMargin(0.15);

    h_LepEta[2]->GetXaxis()->SetTitle("#eta");
    h_LepEta[2]->GetYaxis()->SetTitle("Number of events");
    h_LepEta[2]->SetLineColor(kAzure+1);
    h_LepEta[2]->SetTitle("Pseudorapidity");
    h_LepEta[2]->Draw("hist");

    h_LepEta[3]->SetLineColor(kMagenta+1);
    h_LepEta[3]->SetTitle("");
    h_LepEta[3]->Draw("hist same");

    h_LepEta[0]->SetLineColor(kRed+1);
    h_LepEta[0]->SetTitle("");
    h_LepEta[0]->Draw("hist same");
    
    h_LepEta[1]->SetLineColor(kGreen+2);
    h_LepEta[1]->SetTitle("");
    h_LepEta[1]->Draw("hist same");

    //legenda
    TLegend *leg_Eta = new TLegend(0.65,0.75,0.9,0.9);
    for(i=0; i<4; i++){
        opis = "lepton " + std::to_string(i+1);
        leg_Eta->AddEntry(h_LepEta[i], opis.c_str(), "l");
    }
    leg_Eta->Draw();

    /******* PANEL 3 (dolje lijevo): LepPhi *******/
    c->cd(3);
    gPad->SetLeftMargin(0.15);

    h_LepPhi[2]->GetXaxis()->SetTitle("#phi");
    h_LepPhi[2]->GetYaxis()->SetTitle("Number of events");
    h_LepPhi[2]->SetLineColor(kAzure+1);
    h_LepPhi[2]->SetTitle("Azimuthal angle");
    h_LepPhi[2]->Draw("hist");

    h_LepPhi[3]->SetLineColor(kMagenta+1);
    h_LepPhi[3]->SetTitle("");
    h_LepPhi[3]->Draw("hist same");

    h_LepPhi[0]->SetLineColor(kRed+1);
    h_LepPhi[0]->SetTitle("");
    h_LepPhi[0]->Draw("hist same");
    
    h_LepPhi[1]->SetLineColor(kGreen+2);
    h_LepPhi[1]->SetTitle("");
    h_LepPhi[1]->Draw("hist same");

    //legenda
    TLegend *leg_Phi = new TLegend(0.65,0.2,0.9,0.35);
    for(i=0; i<4; i++){
        opis = "lepton " + std::to_string(i+1);
        leg_Phi->AddEntry(h_LepPhi[i], opis.c_str(), "l");
    }
    leg_Phi->Draw();

    /******* PANEL 4 (dolje desno): LepBDT *******/
    c->cd(4);
    gPad->SetLeftMargin(0.15);

    h_LepBDT[0]->GetXaxis()->SetTitle("BDT");
    h_LepBDT[0]->GetYaxis()->SetTitle("Number of events");
    h_LepBDT[0]->SetLineColor(kRed+1);
    h_LepBDT[0]->SetTitle("BDT");
    h_LepBDT[0]->Draw("hist");

    h_LepBDT[2]->SetLineColor(kAzure+1);
    h_LepBDT[2]->SetTitle("");
    h_LepBDT[2]->Draw("hist same");

    h_LepBDT[3]->SetLineColor(kMagenta+1);
    h_LepBDT[3]->SetTitle("");
    h_LepBDT[3]->Draw("hist same");

    h_LepBDT[1]->SetLineColor(kGreen+2);
    h_LepBDT[1]->SetTitle("");
    h_LepBDT[1]->Draw("hist same");  

    //legenda
    TLegend *leg_BDT = new TLegend(0.65,0.75,0.9,0.9);
    for(i=0; i<4; i++){
        opis = "lepton " + std::to_string(i+1);
        leg_BDT->AddEntry(h_LepBDT[i], opis.c_str(), "l");
    }
    leg_BDT->Draw();

    
    c->Print("4l-distribucije-"+dir_name+".png");


    /****** CRTANJE MASE 4 LEPTONA = HIGGS ******/    
    c_H->cd();
    gPad->SetLeftMargin(0.15);

    if(dir_name == "ggH125"){
        h_m4l_higgs->SetTitle("4 leptons mass");
        h_m4l_higgs->GetXaxis()->SetTitle("m_{4l} (GeV)");
        h_m4l_higgs->GetYaxis()->SetTitle("Number of events");
        h_m4l_higgs->SetLineColor(kPink-6);
        h_m4l_higgs->SetFillColor(kPink+2);
        h_m4l_higgs->Draw("hist");
        c_H->Print("4l-masa-"+dir_name+".png");
    }
    else if(dir_name == "qqZZ"){
        h_m4l_pozadina->SetTitle("4 leptons mass");
        h_m4l_pozadina->GetXaxis()->SetTitle("m_{4l} (GeV)");
        h_m4l_pozadina->GetYaxis()->SetTitle("Number of events");
        h_m4l_pozadina->SetLineColor(kBlue+2);
        h_m4l_pozadina->SetFillColor(kAzure-4);
        h_m4l_pozadina->Draw("hist");
        c_H->Print("4l-masa-"+dir_name+".png");
    }
    else {cout << "Krivo ime direktorija" << dir_name << endl; return;}


    for(i=0; i<4; i++){
        delete h_LepPt[i];
        delete h_LepEta[i];
        delete h_LepPhi[i];
        delete h_LepBDT[i];
    }
    //delete h_Higgs;
    delete c;
    delete c_H;
}

void Analyzer::Loop()
{
//   In a ROOT session, you can do:
//      root> .L Analyzer.C
//      root> Analyzer t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

   }
}

Double_t Analyzer::ReadHistogramFromFile(TString dir_name)
{
    TFile *f = TFile::Open("/home/public/data/"+dir_name+"/ZZ4lAnalysis.root");
    TDirectory * dir = (TDirectory*)f->Get("/home/public/data/"+dir_name+"/ZZ4lAnalysis.root:/ZZTree");
    TH1F *h = new TH1F();
    dir->GetObject("Counters", h);
    return h->GetBinContent(40);
}

void Analyzer::PlotPublicHistograms()
{
    /********* Masa 4 leptona: Higg + pozadina *********************/

    TCanvas *c1 = new TCanvas("c1", "higgs i pozadina",0,0, 800, 600);
    THStack *hstack = new THStack("hstack", "Four lepton mass");
    TLegend *leg  = new TLegend(0.7, 0.8, 0.9, 0.9); //koordinate dvaju vrhova

    hstack->Add(this->h_m4l_pozadina); //prvo dodaj pozadinu
    hstack->Add(this->h_m4l_higgs);    //onda dodaj higgsa da se zbroji s pozad$

    hstack->Draw("hist");
    hstack->GetXaxis()->SetTitle("m_{4l} (GeV)");      //OVO NAKON Draw()!!!
    hstack->GetYaxis()->SetTitle("Number of events / 2 GeV");

    leg->AddEntry(h_m4l_higgs, "gg->H", "fl");
    leg->AddEntry(h_m4l_pozadina, "qq->ZZ", "fl");
    leg->Draw();

    c1->SaveAs("4l-masa-higg+pozadina.png");




    /********* Kinematicka diskriminatna **************************/

    TCanvas *c2 = new TCanvas("c2", "kinematicka diskriminanta",0,0, 800, 600);
    TLegend *leg2 = new TLegend(0.7, 0.8, 0.9, 0.9);

    Double_t scale_factor;

    scale_factor = 1.0/( h_Dkin_bkg->Integral() );
    h_Dkin_bkg->Scale(scale_factor);
    h_Dkin_bkg->SetTitle("Kinematic discriminant");
    h_Dkin_bkg->GetXaxis()->SetTitle("D^{kin}_{bkg}");
    h_Dkin_bkg->GetYaxis()->SetTitle("Probability");
    h_Dkin_bkg->SetLineColor(kRed+2);
    h_Dkin_bkg->SetLineWidth(2);
    h_Dkin_bkg->Draw("hist");

    scale_factor = 1.0/( h_Dkin_sig->Integral() );
    h_Dkin_sig->Scale(scale_factor);
    h_Dkin_sig->SetLineColor(kBlue-3);
    h_Dkin_sig->SetLineWidth(2);
    h_Dkin_sig->Draw("hist same");

    leg2->AddEntry(h_Dkin_sig, "signal", "l");
    leg2->AddEntry(h_Dkin_bkg, "background", "l");
    leg2->Draw();

    c2->SaveAs("KinDiscriminants.png");



    /***************** 2D HISTOGRAMI *********************/

    TCanvas *c3 = new TCanvas("c3", "2D histos", 0, 0, 1000, 800);

    c3->Divide(2,2);
    gStyle->SetOptStat(0);

    c3->cd(1);                   // diskriminanta
    gPad->SetLeftMargin(0.15);
    h_Dkin_bkg->Draw("hist");
    h_Dkin_sig->Draw("hist same");
    leg2->Draw();



    c3->cd(2);                   // Zad4: ROC



    c3->cd(3);                   // background
    gPad->SetLeftMargin(0.15);

    h_2d_bkg->SetTitle("background");
    h_2d_bkg->GetXaxis()->SetTitle("m_{4l}");
    h_2d_bkg->GetYaxis()->SetTitle("D^{kin}");
    h_2d_bkg->Draw("col");
    

    c3->cd(4);                   // signal
    gPad->SetLeftMargin(0.15);

    h_2d_sig->SetTitle("signal");
    h_2d_sig->GetXaxis()->SetTitle("m_{4l}");
    h_2d_sig->GetYaxis()->SetTitle("D^{kin}");
    h_2d_sig->Draw("col");


    c3->SaveAs("2Dhistos.png");

    delete c1;
    delete c2;
    delete c3;
    delete hstack;
    delete leg;
    delete leg2;    
}

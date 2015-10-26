#include <fstream>

void computeDataEff(TTree* tree, const int nbins, const double ptmin, const double ptmax, const double etamin, const double etamax, const TString lepton, const TString region, const TString trig, const TString outtrig, TH1D*& effhist, const int bin);

void trigDataEff(){

  //////////////////////////
  // Input TnP Data Trees //
  //////////////////////////

  TString run = "2015D";

  // muons 
  TFile * mufile = TFile::Open(Form("../input/%s/singleMu/tnptree-copy.root",run.Data()));
  TTree * mutree = (TTree*)mufile->Get("muontnptree/fitter_tree") ;

  // electrons
  TFile * elfile = TFile::Open(Form("../input/%s/singleEl/tnptree-copy.root",run.Data()));
  TTree * eltree = (TTree*)elfile->Get("electrontnptree/fitter_tree") ;

  //////////////////
  // Choose bins  //
  //////////////////

  int nbins           = 100;
  double muptbins[]   = {10, 15, 17.5, 20, 20.025, 20.05, 20.1, 20.15, 20.2, 20.3, 20.5, 20.75, 21, 22, 23, 24, 25, 27.5, 30, 35, 40, 45, 50, 60, 70, 85, 100, 1000}; //27
  double elptbins23[] = {10, 15, 20, 22, 22.5, 22.75, 23, 23.25, 23.5, 24, 24.5, 25, 26, 27, 28, 30, 35, 40, 45, 50, 60, 70, 85, 100, 1000}; //24
  double elptbins27[] = {10, 20, 25, 26, 26.5, 26.75, 27, 27.25, 27.5, 28, 28.5, 29, 30, 31, 32, 33, 35, 40, 45, 50, 60, 70, 85, 100, 1000}; //24

  ////////////////////////////
  // Make total Data eff hist //
  ////////////////////////////

  // Muon plots
  TH1D *  trigeff_mubar1 = new TH1D("trigeff_mubar1","HLT_IsoMu20 Trigger Effiency (Data Barrel)",   27, muptbins);
  TH1D *  trigeff_mubar2 = new TH1D("trigeff_mubar2","HLT_IsoTkMu20 Trigger Effiency (Data Barrel)", 27, muptbins);

  TH1D *  trigeff_muend1 = new TH1D("trigeff_muend1","HLT_IsoMu20 Trigger Effiency (Data Endcap)",   27, muptbins);
  TH1D *  trigeff_muend2 = new TH1D("trigeff_muend2","HLT_IsoTkMu20 Trigger Effiency (Data Endcap)", 27, muptbins);

  // Electron plots
  TH1D *  trigeff_elbar1 = new TH1D("trigeff_elbar1","HLT_Ele23_WPLoose_Gsf Trigger Effiency (Data Barrel)", 24, elptbins23);
  TH1D *  trigeff_elbar2 = new TH1D("trigeff_elbar2","HLT_Ele27_WPLoose_Gsf Trigger Effiency (Data Barrel)", 24, elptbins27);

  TH1D *  trigeff_elend1 = new TH1D("trigeff_elend1","HLT_Ele23_WPLoose_Gsf Trigger Effiency (Data Endcap)", 24, elptbins23);
  TH1D *  trigeff_elend2 = new TH1D("trigeff_elend2","HLT_Ele27_WPLoose_Gsf Trigger Effiency (Data Endcap)", 24, elptbins27);

  for (int i = 0; i < 27; i++){ // Muons first
    // Muon Barrel 
    computeDataEff(mutree, nbins, muptbins[i], muptbins[i+1], 0.0, 1.2, "muon", "barrel", "hltmu20",   "hltmu20",   trigeff_mubar1, i);
    computeDataEff(mutree, nbins, muptbins[i], muptbins[i+1], 0.0, 1.2, "muon", "barrel", "hlttkmu20", "hlttkmu20", trigeff_mubar2, i);

    // Muon Endcap
    computeDataEff(mutree, nbins, muptbins[i], muptbins[i+1], 1.2, 2.5, "muon", "endcap", "hltmu20",   "hltmu20",   trigeff_muend1, i);
    computeDataEff(mutree, nbins, muptbins[i], muptbins[i+1], 1.2, 2.5, "muon", "endcap", "hlttkmu20", "hlttkmu20", trigeff_muend2, i);
  }

  for (int i = 0; i < 24; i++){ // Electrons second
    // Electron Barrel 
    computeDataEff(eltree, nbins, elptbins23[i], elptbins23[i+1], 0.0, 1.4442, "electron", "barrel", "hltdata23", "hltel23", trigeff_elbar1, i);
    computeDataEff(eltree, nbins, elptbins27[i], elptbins27[i+1], 0.0, 1.4442, "electron", "barrel", "hltdata27", "hltel27", trigeff_elbar2, i);

    // Electron Endcap
    computeDataEff(eltree, nbins, elptbins23[i], elptbins23[i+1], 1.566,  2.5, "electron", "endcap", "hltdata23", "hltel23", trigeff_elend1, i);
    computeDataEff(eltree, nbins, elptbins27[i], elptbins27[i+1], 1.566,  2.5, "electron", "endcap", "hltdata27", "hltel27", trigeff_elend2, i);
  }

  TFile * muoutfile = new TFile("output_trig/muon/Data/triggereffs.root","RECREATE"); 
  muoutfile->cd();
  trigeff_mubar1->Write();
  trigeff_mubar2->Write();
  trigeff_muend1->Write();
  trigeff_muend2->Write();

  TFile * eloutfile = new TFile("output_trig/electron/Data/triggereffs.root","RECREATE"); 
  eloutfile->cd();
  trigeff_elbar1->Write();
  trigeff_elbar2->Write();
  trigeff_elend1->Write();
  trigeff_elend2->Write();
  
}

void computeDataEff(TTree* tree, const int nbins, const double ptmin, const double ptmax, const double etamin, const double etamax, const TString lepton, const TString region, const TString trig, const TString outtrig, TH1D*& effhist, const int bin){

  double xmin = 60.0;
  double xmax = 120.0;

  TH1F hpass("hpass", "", nbins, xmin, xmax);
  TH1F hfail("hfail", "", nbins, xmin, xmax);
  TH1F hall("hall",   "", nbins, xmin, xmax);
  TH1F hp("hp" , "", 1, xmin, xmax);
  TH1F ha("ha" , "", 1, xmin, xmax);
  TH1F hr("hr" , "", 1, xmin, xmax);

  hpass.Sumw2();
  hfail.Sumw2();
  hall.Sumw2();
  hp.Sumw2();
  ha.Sumw2();

  TBranch  *bmass       = tree->GetBranch("mass");
  TBranch  *bpt         = tree->GetBranch("pt");
  TBranch  *babseta     = tree->GetBranch("abseta");
  TBranch  *bid         = tree->GetBranch("tightid");
  TBranch  *bhlt        = tree->GetBranch(trig.Data());

  Float_t  mass         = 0.0;
  Float_t  pt           = 0.0;
  Float_t  abseta       = 0.0;
  Int_t    id           = 0;
  Int_t    hlt          = 0;

  bmass  ->SetAddress(&mass);
  bpt    ->SetAddress(&pt);
  babseta->SetAddress(&abseta);
  bid    ->SetAddress(&id);
  bhlt   ->SetAddress(&hlt);

  for (Long64_t i = 0; i < tree->GetEntries(); i++) {
    bmass  ->GetEvent(i);
    bpt    ->GetEvent(i);
    babseta->GetEvent(i);
    bid    ->GetEvent(i);
    bhlt   ->GetEvent(i);

    if (pt > ptmin && pt <= ptmax && abseta > etamin && abseta <= etamax && id > 0) {
      if (hlt == 0) {hfail.Fill(mass);}
      else if (hlt >  0) {
	hp.Fill(   mass);
	hpass.Fill(mass);
      }
      ha.Fill(  mass);
      hall.Fill(mass);
    }
  }

  hr.Divide(&hp, &ha, 1.0, 1.0, "B");

  TFile dataout(Form("output_trig/%s/Data/%s/%s/dataefficiency%d.root",lepton.Data(),region.Data(),outtrig.Data(),bin),"RECREATE");
  dataout.cd();
  hpass.Write();
  hfail.Write();
  hall.Write();
  hr.Write();

  TCanvas * canv = new TCanvas();
  canv->cd();
  hpass.Draw();
  canv->SaveAs(Form("output_trig/%s/Data/%s/%s/hpass%d.png",lepton.Data(),region.Data(),outtrig.Data(),bin));
  hfail.Draw();
  canv->SaveAs(Form("output_trig/%s/Data/%s/%s/hfail%d.png",lepton.Data(),region.Data(),outtrig.Data(),bin));
  delete canv;

  //upload bin pt
  effhist->SetBinContent(bin+1,hr.GetBinContent(1));
  effhist->SetBinError(bin+1,hr.GetBinError(1));
  
  std::cout << "Efficiency -- pT [" << ptmin << ", " << ptmax << "], eta [" << etamin << ", " << etamax << "]  :  " << hr.GetBinContent(1) << " +/- " << hr.GetBinError(1) << std::endl; 
}

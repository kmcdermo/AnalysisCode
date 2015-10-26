#include <fstream>

void computeEff(TTree* tree, TH1F*& puhist, const int nbins, const double ptmin, const double ptmax, const double etamin, const double etamax, const double wgtsum, const double lumi, const TString lepton, const TString region, const TString id, std::ofstream & effyield, TH1D*& effhist, const int bin);

void mcLeptonIDEff(TString lepton, TString region, TString id) {

  ///////////////////////
  // Input TnP MC Tree //
  ///////////////////////

  TString run = "2015D";
  double lumi = 0.55267;

  TFile * file = new TFile(Form("../input/%s/mcDYLL/tnptree.root",run.Data()));
  TTree * tree;
  TFile * pufile;
  double  wgtsum = -1;

  bool isMu;
  if      (lepton.Contains("muon",TString::kExact))     {isMu = true;}
  else if (lepton.Contains("electron",TString::kExact)) {isMu = false;}

  bool isBarrel;
  if      (region.Contains("barrel",TString::kExact)) {isBarrel = true;}
  else if (region.Contains("endcap",TString::kExact)) {isBarrel = false;}
  
  /////////////////////////////
  // Select Mu/El PU weights //
  /////////////////////////////
  if (isMu) {
    tree = (TTree*)file->Get("muontnptree/fitter_tree");  
    pufile = new TFile(Form("../input/%s/mcDYLL/PURW_zmumu.root",run.Data()));
    wgtsum = 8.40635e+10; //4.52712e11; // 25ns //1.12779e+11;//from 50ns //3.129e+11; from adish
  }
  else {
    tree = (TTree*)file->Get("electrontnptree/fitter_tree");  
    pufile = new TFile(Form("../input/%s/mcDYLL/PURW_zelel.root",run.Data()));
    wgtsum = 3.67205e+10; //4.52712e11; // 25ns //1.12779e+11;//from 50ns //3.129e+11; from adish
  }

  TH1F * puhist = (TH1F*)pufile->Get("nvtx_dataOverMC"); // pu weight histo
  
  /////////////////////
  // Choose bins, id //
  /////////////////////

  int nbins     = 100;
  double etamin = -1; 
  double etamax = -1; 

  if (isMu) {
    if (isBarrel) {
      etamin = 0;
      etamax = 1.2;
    }
    else {
      etamin = 1.2;
      etamax = 2.5;
    }
  }
  else { // ecal
    if (isBarrel) {
      etamin = 0;
      etamax = 1.4442;
    }
    else {
      etamin = 1.566;
      etamax = 2.5;
    }
  }
  
  //////////////////////////
  // Store numbers in csv //
  //////////////////////////

  ofstream effyield(Form("output/%s/MC/%s/%s/mcefficiency.csv", lepton.Data(), region.Data(), id.Data()),std::ofstream::app);
  effyield << "ID,"     << id.Data()     << std::endl;
  effyield << "lepton," << lepton.Data() << std::endl;
  effyield << "region," << region.Data() << std::endl;
  effyield << std::endl;

  ////////////////////////////
  // Make total MC eff hist //
  ////////////////////////////
  
  double ptbins[] = {10,20,30,40,50,70,100,1000};

  TH1D *  effhist = new TH1D("effhist",Form("%s MC Efficiency [%s - %s ID]",lepton.Data(),region.Data(),id.Data()), 7, ptbins);
  
  /// run it

  for (int i = 0; i < 7; i++){
    computeEff(tree, puhist, nbins, ptbins[i], ptbins[i+1], etamin, etamax, wgtsum, lumi, lepton, region, id, effyield, effhist, i);
  }

  TFile * outfile = new TFile( Form("output/%s/MC/%s/%s/mc-efficiency.root",lepton.Data(),region.Data(),id.Data()),"RECREATE"); 
  outfile->cd();
  effhist->Write();
  
  delete effhist;
  delete outfile;

  effyield.close();

}

void computeEff(TTree* tree, TH1F*& puhist, const int nbins, const double ptmin, const double ptmax, const double etamin, const double etamax, const double wgtsum, const double lumi, const TString lepton, const TString region, const TString sid, std::ofstream & effyield, TH1D*& effhist, const int bin){

  double xmin = 60.0;
  double xmax = 120.0;

  TH1F hpass("hpass", "", nbins, xmin, xmax);
  TH1F hfail("hfail", "", nbins, xmin, xmax);
  TH1F hall("hall", "", nbins, xmin, xmax);
  TH1F hp("hp" , "", 1, xmin, xmax);
  TH1F ha("ha" , "", 1, xmin, xmax);
  TH1F hr("hr" , "", 1, xmin, xmax);

  hp.Sumw2();
  ha.Sumw2();
  hpass.Sumw2();
  hfail.Sumw2();
  hall.Sumw2();

  TBranch  *bmass       = tree->GetBranch("mass");
  TBranch  *bpt         = tree->GetBranch("pt");
  TBranch  *babseta     = tree->GetBranch("abseta");
  TBranch  *bmc         = tree->GetBranch("mcTrue");
  TBranch  *bid         = tree->GetBranch(Form("%sid",sid.Data()));
  TBranch  *bnvtx       = tree->GetBranch("nvtx");
  TBranch  *bwgt        = tree->GetBranch("wgt");

  Float_t  mass         = 0.0;
  Float_t  pt           = 0.0;
  Float_t  abseta       = 0.0;
  Float_t  nvtx         = 0.0;
  Float_t  wgt          = 0.0;
  Int_t    mc           = 0; 
  Int_t    id           = 0;

  bmass  ->SetAddress(&mass);
  bpt    ->SetAddress(&pt);
  babseta->SetAddress(&abseta);
  bmc    ->SetAddress(&mc);
  bid    ->SetAddress(&id);
  bnvtx  ->SetAddress(&nvtx);
  bwgt   ->SetAddress(&wgt);

  for (Long64_t i = 0; i < tree->GetEntries(); i++) {
    bmass  ->GetEvent(i);
    bpt    ->GetEvent(i);
    babseta->GetEvent(i);
    bmc    ->GetEvent(i);
    bid    ->GetEvent(i);
    bnvtx  ->GetEvent(i);
    bwgt   ->GetEvent(i);

    if (pt > ptmin && pt <= ptmax && abseta > etamin && abseta <= etamax && mc > 0) {
      Float_t puwgt = puhist->GetBinContent(nvtx);
      if (id == 0) {hfail.Fill(mass, puwgt*wgt/wgtsum);}
      else if (id >  0) {
	hp.Fill(mass, puwgt*wgt/wgtsum);
	hpass.Fill(mass, puwgt*wgt/wgtsum);
      }
      ha.Fill(mass, puwgt*wgt/wgtsum);
      hall.Fill(mass, puwgt*wgt/wgtsum);
    }
  }

  for (int j = 1; j <= nbins; j++) {
    if (hpass.GetBinContent(j) < 0.) hpass.SetBinContent(j, 0.0);
    if (hfail.GetBinContent(j) < 0.) hfail.SetBinContent(j, 0.0);
    if (hall.GetBinContent(j)  < 0.) hall.SetBinContent(j, 0.0);
  }

  hpass.Scale(6025200*lumi);
  hfail.Scale(6025200*lumi);
  hr.Divide(&hp, &ha, 1.0, 1.0, "B");

  TFile mcout(Form("output/%s/MC/%s/%s/mcefficiency%d.root",lepton.Data(),region.Data(),sid.Data(),bin),"RECREATE");
  mcout.cd();
  hpass.Write();
  hfail.Write();
  hall.Write();
  hr.Write();

  hpass.Smooth();
  hfail.Smooth();

  RooRealVar m("mass", "", xmin, xmax);
  RooDataHist dhpass("dhpass", "", RooArgList(m), RooFit::Import(hpass), 0);
  RooDataHist dhfail("dhfail", "", RooArgList(m), RooFit::Import(hfail), 0);
  RooHistPdf signalPassMC("signalPassMC", "", RooArgSet(m), dhpass);
  RooHistPdf signalFailMC("signalFailMC", "", RooArgSet(m), dhfail);

  RooWorkspace w("w", "");
  w.import(signalPassMC);
  w.import(signalFailMC);

  TFile outfile(Form("output/%s/Data/%s/%s/templates%d.root",lepton.Data(),region.Data(),sid.Data(),bin),"RECREATE");
  outfile.cd();
  hpass.Write();
  hfail.Write();
  w.Write();
  
  TCanvas * canv = new TCanvas();
  canv->cd();
  hpass.Draw();
  canv->SaveAs(Form("output/%s/Data/%s/%s/hpass%d.png",lepton.Data(),region.Data(),sid.Data(),bin));
  hfail.Draw();
  canv->SaveAs(Form("output/%s/Data/%s/%s/hfail%d.png",lepton.Data(),region.Data(),sid.Data(),bin));
  delete canv;

  //upload bin pt
  effhist->SetBinContent(bin+1,hr.GetBinContent(1));
  effhist->SetBinError(bin+1,hr.GetBinError(1));
  
  std::cout << "Efficiency -- pT [" << ptmin << ", " << ptmax << "], eta [" << etamin << ", " << etamax << "]  :  " << hr.GetBinContent(1) << " +/- " << hr.GetBinError(1) << std::endl; 
  effyield << "eta [" << etamin << "-" << etamax << "]," << "pT [" << ptmin << "-" << ptmax << "],"  << hr.GetBinContent(1) << " +/- " << hr.GetBinError(1) << std::endl; 
}

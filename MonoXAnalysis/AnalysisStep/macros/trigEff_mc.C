#include <fstream>

void computeMCEff(TTree* tree, TH1F*& puhist, const int nbins, const double ptmin, const double ptmax, const double etamin, const double etamax, const double wgtsum, const double lumi, const TString lepton, const TString region, const TString trig, const TString outtrig, TH1D*& effhist, const int bin);

void trigEff_mc(){

  ////////////////////////
  // Input TnP MC Trees //
  ////////////////////////

  TString run = "2015D";
  TFile * mcfile   = TFile::Open(Form("../input/%s/mcDYLL/tnptree-copy.root",run.Data()));
  double lumi  = 1.2638;

  // muons 
  TTree * mumctree = (TTree*)mcfile->Get("muontnptree/fitter_tree") ;
  TFile * mupufile = TFile::Open(Form("../input/%s/mcDYLL/PURW_zmumu.root",run.Data()));
  TH1F  * mupuhist = (TH1F*)mupufile->Get("nvtx_dataOverMC"); // pu weight histo
  double  muwgtsum = 8.40635e+10;

  // electrons
  TTree * elmctree = (TTree*)mcfile->Get("electrontnptree/fitter_tree") ;
  TFile * elpufile = TFile::Open(Form("../input/%s/mcDYLL/PURW_zelel.root",run.Data()));
  TH1F  * elpuhist = (TH1F*)elpufile->Get("nvtx_dataOverMC"); // pu weight histo
  double  elwgtsum = 3.67205e+10;

  //////////////////
  // Choose bins  //
  //////////////////

  int nbins           = 100;
  double muptbins[]   = {10, 15, 17.5, 20, 20.025, 20.05, 20.1, 20.15, 20.2, 20.3, 20.5, 20.75, 21, 22, 23, 24, 25, 27.5, 30, 35, 40, 45, 50, 60, 70, 85, 100, 1000}; //27
  double elptbins23[] = {10, 15, 20, 22, 22.5, 22.75, 23, 23.25, 23.5, 24, 24.5, 25, 26, 27, 28, 30, 35, 40, 45, 50, 60, 70, 85, 100, 1000}; //24
  double elptbins27[] = {10, 20, 25, 26, 26.5, 26.75, 27, 27.25, 27.5, 28, 28.5, 29, 30, 31, 32, 33, 35, 40, 45, 50, 60, 70, 85, 100, 1000}; //24

  ////////////////////////////
  // Make total MC eff hist //
  ////////////////////////////

  // Muon plots
  TH1D *  trigeff_mcmubar1 = new TH1D("trigeff_mcmubar1","HLT_IsoMu20 Trigger Effiency (MC Barrel)",   27, muptbins);
  TH1D *  trigeff_mcmubar2 = new TH1D("trigeff_mcmubar2","HLT_IsoTkMu20 Trigger Effiency (MC Barrel)", 27, muptbins);
  
  TH1D *  trigeff_mcmuend1 = new TH1D("trigeff_mcmuend1","HLT_IsoMu20 Trigger Effiency (MC Endcap)",   27, muptbins);
  TH1D *  trigeff_mcmuend2 = new TH1D("trigeff_mcmuend2","HLT_IsoTkMu20 Trigger Effiency (MC Endcap)", 27, muptbins);

  // Electron plots
  TH1D *  trigeff_mcelbar1 = new TH1D("trigeff_mcelbar1","HLT_Ele23_CaloIdL_TrackIdL_IsoVL Trigger Effiency (MC Barrel)", 24, elptbins23);
  TH1D *  trigeff_mcelbar2 = new TH1D("trigeff_mcelbar2","HLT_Ele27_WP85_Gsf Trigger Effiency (MC Barrel)",               24, elptbins27);

  TH1D *  trigeff_mcelend1 = new TH1D("trigeff_mcelend1","HLT_Ele23_CaloIdL_TrackIdL_IsoVL Trigger Effiency (MC Endcap)", 24, elptbins23);
  TH1D *  trigeff_mcelend2 = new TH1D("trigeff_mcelend2","HLT_Ele27_WP85_Gsf Trigger Effiency (MC Endcap)",               24, elptbins27);

  for (int i = 0; i < 27; i++){ // Muons first
    // Muon Barrel 
    computeMCEff(mumctree, mupuhist, nbins, muptbins[i], muptbins[i+1], 0.0, 1.2, muwgtsum, lumi, "muon", "barrel", "hltmu20",   "hltmu20",   trigeff_mcmubar1, i);
    computeMCEff(mumctree, mupuhist, nbins, muptbins[i], muptbins[i+1], 0.0, 1.2, muwgtsum, lumi, "muon", "barrel", "hlttkmu20", "hlttkmu20", trigeff_mcmubar2, i);

    // Muon Endcap
    computeMCEff(mumctree, mupuhist, nbins, muptbins[i], muptbins[i+1], 1.2, 2.5, muwgtsum, lumi, "muon", "endcap", "hltmu20",   "hltmu20",   trigeff_mcmuend1, i);
    computeMCEff(mumctree, mupuhist, nbins, muptbins[i], muptbins[i+1], 1.2, 2.5, muwgtsum, lumi, "muon", "endcap", "hlttkmu20", "hlttkmu20", trigeff_mcmuend2, i);
  }

  for (int i = 0; i < 24; i++){ // Electrons second
    // Electron Barrel 
    computeMCEff(elmctree, elpuhist, nbins, elptbins23[i], elptbins23[i+1], 0.0, 1.4442, elwgtsum, lumi, "electron", "barrel", "hltmc23", "hltel23", trigeff_mcelbar1, i);
    computeMCEff(elmctree, elpuhist, nbins, elptbins27[i], elptbins27[i+1], 0.0, 1.4442, elwgtsum, lumi, "electron", "barrel", "hltmc27", "hltel27", trigeff_mcelbar2, i);

    // Electron Endcap
    computeMCEff(elmctree, elpuhist, nbins, elptbins23[i], elptbins23[i+1], 1.566,  2.5, elwgtsum, lumi, "electron", "endcap", "hltmc23", "hltel23", trigeff_mcelend1, i);
    computeMCEff(elmctree, elpuhist, nbins, elptbins27[i], elptbins27[i+1], 1.566,  2.5, elwgtsum, lumi, "electron", "endcap", "hltmc27", "hltel27", trigeff_mcelend2, i);
  }

  TFile * muoutfile = new TFile("output_trig/muon/MC/triggereffs.root","RECREATE"); 
  muoutfile->cd();
  trigeff_mcmubar1->Write();
  trigeff_mcmubar2->Write();
  trigeff_mcmuend1->Write();
  trigeff_mcmuend2->Write();

  delete muoutfile;

  TFile * eloutfile = new TFile("output_trig/electron/MC/triggereffs.root","RECREATE"); 
  eloutfile->cd();
  trigeff_mcelbar1->Write();
  trigeff_mcelbar2->Write();
  trigeff_mcelend1->Write();
  trigeff_mcelend2->Write();

  delete eloutfile;
}

void computeMCEff(TTree* tree, TH1F*& puhist, const int nbins, const double ptmin, const double ptmax, const double etamin, const double etamax, const double wgtsum, const double lumi, const TString lepton, const TString region, const TString trig, const TString outtrig, TH1D*& effhist, const int bin){

  double xmin = 60.0;
  double xmax = 120.0;

  TH1F hpass("hpass",  "", nbins, xmin, xmax);
  TH1F hfail("hfail",  "", nbins, xmin, xmax);
  TH1F hall("hall",    "", nbins, xmin, xmax);
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
  TBranch  *bmc         = tree->GetBranch("mcTrue");
  TBranch  *bid         = tree->GetBranch("tightid");
  TBranch  *bnvtx       = tree->GetBranch("nvtx");
  TBranch  *bwgt        = tree->GetBranch("wgt");
  TBranch  *bhlt        = tree->GetBranch(trig.Data());

  Float_t  mass         = 0.0;
  Float_t  pt           = 0.0;
  Float_t  abseta       = 0.0;
  Int_t    mc           = 0; 
  Int_t    id           = 0;
  Float_t  nvtx         = 0.0;
  Float_t  wgt          = 0.0;
  Int_t    hlt          = 0;

  bmass  ->SetAddress(&mass);
  bpt    ->SetAddress(&pt);
  babseta->SetAddress(&abseta);
  bmc    ->SetAddress(&mc);
  bid    ->SetAddress(&id);
  bnvtx  ->SetAddress(&nvtx);
  bwgt   ->SetAddress(&wgt);
  bhlt   ->SetAddress(&hlt);

  for (Long64_t i = 0; i < tree->GetEntries(); i++) {
    bmass  ->GetEvent(i);
    bpt    ->GetEvent(i);
    babseta->GetEvent(i);
    bmc    ->GetEvent(i);
    bid    ->GetEvent(i);
    bnvtx  ->GetEvent(i);
    bwgt   ->GetEvent(i);
    bhlt   ->GetEvent(i);

    if (pt > ptmin && pt <= ptmax && abseta > etamin && abseta <= etamax && mc > 0 && id > 0) {
      Float_t puwgt = puhist->GetBinContent(nvtx);
      if (hlt == 0) {hfail.Fill(mass, puwgt*wgt/wgtsum);}
      else if (hlt >  0) {
	hp.Fill(   mass, puwgt*wgt/wgtsum);
	hpass.Fill(mass, puwgt*wgt/wgtsum);
      }
      ha.Fill(  mass, puwgt*wgt/wgtsum);
      hall.Fill(mass, puwgt*wgt/wgtsum);
    }
  }

  for (int j = 1; j <= nbins; j++) {
    if (hpass.GetBinContent(j) < 0.) hpass.SetBinContent(j, 0.0);
    if (hfail.GetBinContent(j) < 0.) hfail.SetBinContent(j, 0.0);
    if (hp.GetBinContent(j) < 0.) hpass.SetBinContent(j, 0.0);
    if (ha.GetBinContent(j) < 0.) hfail.SetBinContent(j, 0.0);
    if (hall.GetBinContent(j)  < 0.) hall.SetBinContent(j, 0.0);
  }

  hpass.Scale(6025200*lumi);
  hfail.Scale(6025200*lumi);
  hr.Divide(&hp, &ha, 1.0, 1.0, "B");

  TFile mcout(Form("output_trig/%s/MC/%s/%s/mcefficiency%d.root",lepton.Data(),region.Data(),outtrig.Data(),bin),"RECREATE");
  mcout.cd();
  hpass.Write();
  hfail.Write();
  hall.Write();
  hr.Write();

  TCanvas * canv = new TCanvas();
  canv->cd();
  hpass.Draw();
  canv->SaveAs(Form("output_trig/%s/MC/%s/%s/hpass%d.png",lepton.Data(),region.Data(),outtrig.Data(),bin));
  hfail.Draw();
  canv->SaveAs(Form("output_trig/%s/MC/%s/%s/hfail%d.png",lepton.Data(),region.Data(),outtrig.Data(),bin));
  delete canv;

  //upload bin pt
  effhist->SetBinContent(bin+1,hr.GetBinContent(1));
  effhist->SetBinError(bin+1,hr.GetBinError(1));
  
  std::cout << "Efficiency -- pT [" << ptmin << ", " << ptmax << "], eta [" << etamin << ", " << etamax << "]  :  " << hr.GetBinContent(1) << " +/- " << hr.GetBinError(1) << std::endl; 
}

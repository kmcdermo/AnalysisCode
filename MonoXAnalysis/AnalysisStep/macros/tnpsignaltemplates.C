void maketemplate(TTree* tree, TH1F*& puhist, const int nbins, const double ptmin, const double ptmax, const double etamin, const double etamax, const char* outfilename, const double wgtsum, const TString sid);

void tnpsignaltemplates() {

  TString run = "25ns";

  TFile* file = new TFile(Form("../input/%s/mcDYLL/tnptree.root",run.Data()));
  TTree* tree;
  TFile * pufile;
  double wgtsum = -1;

  const bool isMu = true;
  if (isMu) {
    tree = (TTree*)file->Get("muontnptree/fitter_tree");  
    pufile = new TFile(Form("../input/%s/mcDYLL/PURW_zmumu.root",run.Data()));
    wgtsum = 4.52712e11; //1.12779e+11;//from 50ns //3.129e+11; from adish
  }
  else {
    tree = (TTree*)file->Get("electrontnptree/fitter_tree");  
    pufile = new TFile(Form("../input/%s/mcDYLL/PURW_zelel.root",run.Data()));
  }

  TH1F * puhist = (TH1F*)pufile->Get("nvtx_dataOverMC");
  
  int nbins     = 100;
  TString sid   = "looseid"; //"looseid";
  double etamin = 0.0;
  double etamax = 1.2;
  
  maketemplate(tree, puhist, nbins,  10.,   20., etamin, etamax, "templates0.root", wgtsum, sid);    
  maketemplate(tree, puhist, nbins,  20.,   30., etamin, etamax, "templates1.root", wgtsum, sid);    
  maketemplate(tree, puhist, nbins,  30.,   40., etamin, etamax, "templates2.root", wgtsum, sid);    
  maketemplate(tree, puhist, nbins,  40.,   50., etamin, etamax, "templates3.root", wgtsum, sid);    
  maketemplate(tree, puhist, nbins,  50.,   70., etamin, etamax, "templates4.root", wgtsum, sid);    
  maketemplate(tree, puhist, nbins,  70.,  100., etamin, etamax, "templates5.root", wgtsum, sid);  
  maketemplate(tree, puhist, nbins, 100., 1000., etamin, etamax, "templates6.root", wgtsum, sid);    // formally template_highpT.root


  /*
  maketemplate(tree, puhist, nbins, 100.,  200., etamin, etamax, "templates6.root", wgtsum, sid);  
  maketemplate(tree, puhist, nbins, 200.,  500., etamin, etamax, "templates7.root", wgtsum, sid); 
  maketemplate(tree, puhist, nbins, 500., 1000., etamin, etamax, "templates8.root", wgtsum, sid); */

}

void maketemplate(TTree* tree, TH1F*& puhist, const int nbins, const double ptmin, const double ptmax, const double etamin, const double etamax, const char* outfilename, const double wgtsum, const TString sid){

  double xmin = 65.0;
  double xmax = 115.0;

  TH1F hpass("hpass", "", nbins, xmin, xmax);
  TH1F hfail("hfail", "", nbins, xmin, xmax);
  TH1F hp("hp" , "", 1, xmin, xmax);
  TH1F ha("ha" , "", 1, xmin, xmax);
  TH1F hr("hr" , "", 1, xmin, xmax);

  hp.Sumw2();
  ha.Sumw2();

  TBranch  *bmass       = tree->GetBranch("mass");
  TBranch  *bpt         = tree->GetBranch("pt");
  TBranch  *babseta     = tree->GetBranch("abseta");
  TBranch  *bmc         = tree->GetBranch("mcTrue");
  TBranch  *bid         = tree->GetBranch(sid.Data());
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
      if (id >  0) {hpass.Fill(mass, puwgt*wgt/wgtsum);}
      if (id >  0) {hp.Fill(mass, puwgt*wgt/wgtsum);}
      ha.Fill(mass, puwgt*wgt/wgtsum);
    }
  }

  for (int j = 1; j <= nbins; j++) {
    if (hpass.GetBinContent(j) < 0.) hpass.SetBinContent(j, 0.0);
    if (hfail.GetBinContent(j) < 0.) hfail.SetBinContent(j, 0.0);
  }

  hr.Divide(&hp, &ha, 1.0, 1.0, "B");

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
        
  TFile outfile(outfilename, "RECREATE");
  w.Write();
  hpass.Write();
  hfail.Write();

  std::cout << "Efficiency -- pT [" << ptmin << ", " << ptmax << "], eta [" << etamin << ", " << etamax << "]   :   " << hr.GetBinContent(1) << " +/- " << hr.GetBinError(1) << std::endl;
}

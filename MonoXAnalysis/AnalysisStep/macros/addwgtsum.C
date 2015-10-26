void addwgtsum(){

  TFile * tfile = TFile::Open("../crab/mcDYLL/tnptree.root");
  TTree * ttree = (TTree*)tfile->Get("muontnptree/fitter_tree");
  
  TBranch  *bwgt        = ttree->GetBranch("wgt");
  Float_t  wgt          = 0.0;
  bwgt   ->SetAddress(&wgt);

  Float_t wgtsum = 0.;

  for (Long64_t i = 0; i < ttree->GetEntries(); i++) {
    bwgt   ->GetEvent(i);
    wgtsum += wgt;
  }
  
  std::cout << wgtsum << std::endl;
}

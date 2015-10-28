void combineIDEffSF(){

  // just do this by hand

  // Muons first

  TFile * infile1 = TFile::Open( "output/muon/scalefactor/barrel/loose/scalefactors.root" );
  TH1D  * sfhist1 = (TH1D*)infile1->Get("effhist");
  sfhist1->SetName("muon_barrel_loose_sf");

  TFile * infile2 = TFile::Open( "output/muon/scalefactor/barrel/tight/scalefactors.root" );
  TH1D  * sfhist2 = (TH1D*)infile2->Get("effhist");
  sfhist2->SetName("muon_barrel_tight_sf");

  TFile * infile3 = TFile::Open( "output/muon/scalefactor/endcap/loose/scalefactors.root" );
  TH1D  * sfhist3 = (TH1D*)infile3->Get("effhist");
  sfhist3->SetName("muon_endcap_loose_sf");

  TFile * infile4 = TFile::Open( "output/muon/scalefactor/endcap/tight/scalefactors.root" );
  TH1D  * sfhist4 = (TH1D*)infile4->Get("effhist");
  sfhist4->SetName("muon_endcap_tight_sf");

  // Electrons second

  TFile * infile5 = TFile::Open( "output/electron/scalefactor/barrel/veto/scalefactors.root" );
  TH1D  * sfhist5 = (TH1D*)infile5->Get("effhist");
  sfhist5->SetName("electron_barrel_veto_sf");

  TFile * infile6 = TFile::Open( "output/electron/scalefactor/barrel/tight/scalefactors.root" );
  TH1D  * sfhist6 = (TH1D*)infile6->Get("effhist");
  sfhist6->SetName("electron_barrel_tight_sf");

  TFile * infile7 = TFile::Open( "output/electron/scalefactor/endcap/veto/scalefactors.root" );
  TH1D  * sfhist7 = (TH1D*)infile7->Get("effhist");
  sfhist7->SetName("electron_endcap_veto_sf");

  TFile * infile8 = TFile::Open( "output/electron/scalefactor/endcap/tight/scalefactors.root" );
  TH1D  * sfhist8 = (TH1D*)infile8->Get("effhist");
  sfhist8->SetName("electron_endcap_tight_sf");

  //////////////////////////////////////

  // make 2D histograms -- not ideal at the moment with the by hand but whatever
  
  double ptbins[] = {10.,20.,30.,40.,50.,70.,100.,1000.};
  double muetabins[] = {0.,1.2,2.5};
  double eletabins[] = {0.,1.4442,1.556,2.5};

  TH2D * muloose = new TH2D("muon_loose_SF","Moun Loose ID Scale Factors",7,ptbins,2,muetabins);
  for (int i = 1; i <= muloose->GetNbinsX(); i++) {
    //barrel
    muloose->SetBinContent(i,1,sfhist1->GetBinContent(i));
    muloose->SetBinError(i,1,sfhist1->GetBinError(i));

    //endcap
    muloose->SetBinContent(i,2,sfhist3->GetBinContent(i));
    muloose->SetBinError(i,2,sfhist3->GetBinError(i));
  }

  TH2D * mutight = new TH2D("muon_tight_SF","Moun Tight ID Scale Factors",7,ptbins,2,muetabins);
  for (int i = 1; i <= mutight->GetNbinsX(); i++) {
    //barrel
    mutight->SetBinContent(i,1,sfhist2->GetBinContent(i));
    mutight->SetBinError(i,1,sfhist2->GetBinError(i));

    //endcap
    mutight->SetBinContent(i,2,sfhist4->GetBinContent(i));
    mutight->SetBinError(i,2,sfhist4->GetBinError(i));
  }

  TH2D * elveto = new TH2D("electron_veto_SF","Electron Veto ID Scale Factors",7,ptbins,3,eletabins);
  for (int i = 1; i <= elveto->GetNbinsX(); i++) {
    //barrel
    elveto->SetBinContent(i,1,sfhist5->GetBinContent(i));
    elveto->SetBinError(i,1,sfhist5->GetBinError(i));

    //endcap
    elveto->SetBinContent(i,3,sfhist7->GetBinContent(i));
    elveto->SetBinError(i,3,sfhist7->GetBinError(i));
  }

  TH2D * eltight = new TH2D("electron_tight_SF","Electron Tight ID Scale Factors",7,ptbins,3,eletabins);
  for (int i = 1; i <= eltight->GetNbinsX(); i++) {
    //barrel

    eltight->SetBinContent(i,1,sfhist6->GetBinContent(i));
    eltight->SetBinError(i,1,sfhist6->GetBinError(i));

    //endcap
    eltight->SetBinContent(i,3,sfhist8->GetBinContent(i));
    eltight->SetBinError(i,3,sfhist8->GetBinError(i));
  }

  /////////////////////////////////////

  TFile * outfile  = new TFile("output/leptonIDsfs.root","RECREATE");
  outfile->cd();
  sfhist1->Write();
  sfhist2->Write();
  sfhist3->Write();
  sfhist4->Write();
  sfhist5->Write();
  sfhist6->Write();
  sfhist7->Write();
  sfhist8->Write();

  muloose->Write();
  mutight->Write();
  elveto ->Write();
  eltight->Write();

  outfile->Close();
}

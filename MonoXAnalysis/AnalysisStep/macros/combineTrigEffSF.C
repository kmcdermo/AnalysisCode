void combineTrigEffSF(){

  // just do this by hand

  // Muons first

  TFile * infile1 = TFile::Open( "output_trig/muon/scalefactor/barrel/hltmu20/scalefactors.root" );
  TH1D  * sfhist1 = (TH1D*)infile1->Get("effhist");
  sfhist1->SetName("muon_barrel_hltmu20_sf");

  TFile * infile2 = TFile::Open( "output_trig/muon/scalefactor/barrel/hlttkmu20/scalefactors.root" );
  TH1D  * sfhist2 = (TH1D*)infile2->Get("effhist");
  sfhist2->SetName("muon_barrel_hlttkmu20_sf");

  TFile * infile3 = TFile::Open( "output_trig/muon/scalefactor/endcap/hltmu20/scalefactors.root" );
  TH1D  * sfhist3 = (TH1D*)infile3->Get("effhist");
  sfhist3->SetName("muon_endcap_hltmu20_sf");

  TFile * infile4 = TFile::Open( "output_trig/muon/scalefactor/endcap/hlttkmu20/scalefactors.root" );
  TH1D  * sfhist4 = (TH1D*)infile4->Get("effhist");
  sfhist4->SetName("muon_endcap_hlttkmu20_sf");

  // Electrons second

  TFile * infile5 = TFile::Open( "output_trig/electron/scalefactor/barrel/hltel23/scalefactors.root" );
  TH1D  * sfhist5 = (TH1D*)infile5->Get("effhist");
  sfhist5->SetName("electron_barrel_hltel23_sf");

  TFile * infile6 = TFile::Open( "output_trig/electron/scalefactor/barrel/hltel27/scalefactors.root" );
  TH1D  * sfhist6 = (TH1D*)infile6->Get("effhist");
  sfhist6->SetName("electron_barrel_hltel27_sf");

  TFile * infile7 = TFile::Open( "output_trig/electron/scalefactor/endcap/hltel23/scalefactors.root" );
  TH1D  * sfhist7 = (TH1D*)infile7->Get("effhist");
  sfhist7->SetName("electron_endcap_hltel23_sf");

  TFile * infile8 = TFile::Open( "output_trig/electron/scalefactor/endcap/hltel27/scalefactors.root" );
  TH1D  * sfhist8 = (TH1D*)infile8->Get("effhist");
  sfhist8->SetName("electron_endcap_hltel27_sf");

  //////////////////////////////////////

  double muptbins[]   = {10, 15, 17.5, 20, 20.025, 20.05, 20.1, 20.15, 20.2, 20.3, 20.5, 20.75, 21, 22, 23, 24, 25, 27.5, 30, 35, 40, 45, 50, 60, 70, 85, 100, 1000}; //27
  double elptbins23[] = {10, 15, 20, 22, 22.5, 22.75, 23, 23.25, 23.5, 24, 24.5, 25, 26, 27, 28, 30, 35, 40, 45, 50, 60, 70, 85, 100, 1000}; //24
  double elptbins27[] = {10, 20, 25, 26, 26.5, 26.75, 27, 27.25, 27.5, 28, 28.5, 29, 30, 31, 32, 33, 35, 40, 45, 50, 60, 70, 85, 100, 1000}; //24
  double muetabins[]  = {0.,1.2,2.5};
  double eletabins[]  = {0.,1.4442,1.556,2.5};

  TH2D * hltmu20 = new TH2D("hltmu20_SF","HLT_IsoMu20_v* Scale Factors",27,muptbins,2,muetabins);
  for (int i = 1; i <= hltmu20->GetNbinsX(); i++) {
    //barrel
    hltmu20->SetBinContent(i,1,sfhist1->GetBinContent(i));
    hltmu20->SetBinError(i,1,sfhist1->GetBinError(i));

    //endcap
    hltmu20->SetBinContent(i,2,sfhist3->GetBinContent(i));
    hltmu20->SetBinError(i,2,sfhist3->GetBinError(i));
  }

  TH2D * hlttkmu20 = new TH2D("hlttkmu20_SF","HLT_IsoTkMu20_v* Scale Factors",27,muptbins,2,muetabins);
  for (int i = 1; i <= hlttkmu20->GetNbinsX(); i++) {
    //barrel
    hlttkmu20->SetBinContent(i,1,sfhist2->GetBinContent(i));
    hlttkmu20->SetBinError(i,1,sfhist2->GetBinError(i));

    //endcap
    hlttkmu20->SetBinContent(i,2,sfhist4->GetBinContent(i));
    hlttkmu20->SetBinError(i,2,sfhist4->GetBinError(i));
  }

  TH2D * hltel23 = new TH2D("hltel23_SF","HLT_Ele23_WPLoose_Gsf_v* / HLT_Ele23_CaloIdL_TrackIdL_IsoVL_v*",24,elptbins23,3,eletabins);
  for (int i = 1; i <= hltel23->GetNbinsX(); i++) {
    //barrel
    hltel23->SetBinContent(i,1,sfhist5->GetBinContent(i));
    hltel23->SetBinError(i,1,sfhist5->GetBinError(i));

    //endcap
    hltel23->SetBinContent(i,3,sfhist7->GetBinContent(i));
    hltel23->SetBinError(i,3,sfhist7->GetBinError(i));
  }

  TH2D * hltel27 = new TH2D("hltel27_SF","HLT_Ele27_WPLoose_Gsf_v* / HLT_Ele27_WP85_Gsf_v*",24,elptbins27,3,eletabins);
  for (int i = 1; i <= hltel27->GetNbinsX(); i++) {
    //barrel

    hltel27->SetBinContent(i,1,sfhist6->GetBinContent(i));
    hltel27->SetBinError(i,1,sfhist6->GetBinError(i));

    //endcap
    hltel27->SetBinContent(i,3,sfhist8->GetBinContent(i));
    hltel27->SetBinError(i,3,sfhist8->GetBinError(i));
  }

  TFile * outfile  = new TFile("output_trig/leptonTrigsfs.root","RECREATE");
  outfile->cd();
  sfhist1->Write();
  sfhist2->Write();
  sfhist3->Write();
  sfhist4->Write();
  sfhist5->Write();
  sfhist6->Write();
  sfhist7->Write();
  sfhist8->Write();

  hltmu20  ->Write();
  hlttkmu20->Write();
  hltel23  ->Write();
  hltel27  ->Write();

  outfile->Close();
}

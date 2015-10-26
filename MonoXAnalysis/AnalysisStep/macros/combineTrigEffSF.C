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

  outfile->Close();
}

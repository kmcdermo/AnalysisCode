void setOneEffBin(){

  TFile * file = TFile::Open("output/electron/Data/barrel/tight/data-efficiency.root","UPDATE");
  TH1D * hist = (TH1D *)file->Get("effhist");
  
  hist->SetBinContent(4,0.724706);
  hist->SetBinError  (4,0.00109563);

  hist->Write();


}

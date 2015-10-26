void inspect(){

  TFile * test = TFile::Open("test.root");
  TCanvas * canv = (TCanvas*)test->Get("electrontnptree/Id/abseta_bin0__pt_bin0__pdfSignalPlusBackgroundb0/fit_canvas");
  canv->Draw();
    
  
}

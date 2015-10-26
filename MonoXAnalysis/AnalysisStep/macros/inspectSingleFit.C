void inspectSingleFit(){
  TFile * test = TFile::Open("testfit.root");
  TCanvas * canv = (TCanvas*)test->Get("electrontnptree/Id/abseta_bin0__pt_bin0__pdfSignalPlusBackgroundb0/fit_canvas");
  //  TCanvas * canv = (TCanvas*)test->Get("muontnptree/Id/abseta_bin0__pt_bin0__pdfSignalPlusBackgroundb0/fit_canvas");
  canv->Draw();
}

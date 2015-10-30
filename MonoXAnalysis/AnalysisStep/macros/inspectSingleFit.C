void inspectSingleFit(){
  TFile * test = TFile::Open("testfit.root");

  TCanvas * canv = (TCanvas*)test->Get("electrontnptree/Id/abseta_bin0__pt_bin0__pdfSignalPlusBackgroundb0/fit_canvas");
  canv->Draw();

  TCanvas * canv1 = (TCanvas*)test->Get("electrontnptree/Id/fit_eff_plots/abseta_pt_PLOT");
  canv1->Draw();

  
}

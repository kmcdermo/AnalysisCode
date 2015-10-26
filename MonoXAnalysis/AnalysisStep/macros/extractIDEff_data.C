void printout(TFile *& file, TString plot, TString lepton, TString region, TString id, TString outdir, TString shape){
  TCanvas * canv = (TCanvas*)file->Get( Form("%stnptree/Id/%s",lepton.Data(), plot.Data()) );

  TObject * obj  = 0; 
  TString   name = "";

  TIter next(canv->GetListOfPrimitives());
  while ((obj=next())) {
    if (obj->InheritsFrom("TH2")) {
      name = obj->GetName();
    }
  }

  TH2F * hist = (TH2F*)canv->GetPrimitive(name.Data());
  for (int i = 1; i <= hist->GetNbinsX() ; i++){
    for (int j = 1; j <= hist->GetNbinsY() ; j++){
      std::cout << hist->GetBinContent(i,j) << " +/- " << hist->GetBinError(i,j) << std::endl;
    }
  }
  std::cout << std::endl; 

  TH1D * proj = hist->ProjectionX("effhist",1,7);
  proj->SetTitle( Form("%s Data Efficiency [%s - %s ID]", lepton.Data(), region.Data(), id.Data()) );
  TCanvas * pcanv = new TCanvas();
  pcanv->cd();
  proj->Draw();
  pcanv->SetLogy();
  pcanv->SetLogx();
  pcanv->SaveAs( Form("%s/dataefficiency%s.png", outdir.Data(), shape.Data()) );

  TFile * outfile = new TFile( Form("%s/data-efficiency%s.root", outdir.Data(), shape.Data() ),"RECREATE"); 
  outfile->cd();
  proj->Write();
  delete outfile;

  delete pcanv;
  delete proj;

  delete hist;
  delete obj;
  delete canv;
}

void savecanv(TFile *& file, TString treedir, TString plot, TString outdir, TString outstring, TString shape){
  file->cd();

  TCanvas * canv = (TCanvas*)file->Get(Form("%s/%s", treedir.Data(), plot.Data()));
  if (plot.Contains("abseta_pt_PLOT",TString::kExact)) {
    canv->SetLogy();
  }
  canv->SaveAs( Form("%s/%s%s%s.png", outdir.Data(), plot.Data(), outstring.Data(), shape.Data()) );

  delete canv;
}

void extractIDEff_data(TString lepton, TString region, TString id, TString shape){

  TString outdir  = Form("output/%s/Data/%s/%s", lepton.Data(), region.Data(), id.Data());

  TFile * file  = TFile::Open( Form("%s/efficiency-data%s.root", outdir.Data(), shape.Data()) );

  printout(file, "fit_eff_plots/pt_abseta_PLOT", lepton.Data(), region, id, outdir, shape );
  //  printout(file, "cnt_eff_plots/pt_abseta_PLOT", lepton.Data() );

  savecanv(file, Form("%stnptree/Id/fit_eff_plots", lepton.Data()), "abseta_pt_PLOT", outdir, "", shape);

  for (int i = 0; i <= 6; i++){
    savecanv(file, Form("%stnptree/Id/abseta_bin0__pt_bin%d__pdfSignalPlusBackgroundb%d", lepton.Data(), i, i), "fit_canvas", outdir, Form("_%d",i) , shape);
  }
}

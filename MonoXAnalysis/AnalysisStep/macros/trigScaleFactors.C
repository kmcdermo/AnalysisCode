#incldue <fstream>

void SetTDRStyle(TStyle *& style);
void CMSLumi(TCanvas *& canv, const Int_t iPosX);

void makecanvas(TH1D*& mchist, TH1D*& datahist, const TString lepton, const TString region, const TString trig);

void trigScaleFactors(){

  ///////////////
  TStyle * tdrStyle = new TStyle("tdrStyle","Style for P-TDR");
  SetTDRStyle(tdrStyle);
  gROOT->ForceStyle();
  ///////////////

  ///////////////////////////
  // Input MC File + Hists //
  ///////////////////////////

  TFile * mumcinfile = TFile::Open("output_trig/muon/MC/triggereffs.root");
  mumcinfile->cd();

  TH1D * trigeff_mcmubar1 = (TH1D*)mumcinfile->Get("trigeff_mcmubar1"); // HLT_IsoMu20 -- Barrel MC
  TH1D * trigeff_mcmubar2 = (TH1D*)mumcinfile->Get("trigeff_mcmubar2"); // HLT_IsoTkMu20 -- Barrel MC
  TH1D * trigeff_mcmuend1 = (TH1D*)mumcinfile->Get("trigeff_mcmuend1"); // HLT_IsoMu20 -- Endcap MC
  TH1D * trigeff_mcmuend2 = (TH1D*)mumcinfile->Get("trigeff_mcmuend2"); // HLT_IsoTkMu20 -- Endcap MC

  TFile * elmcinfile = TFile::Open("output_trig/electron/MC/triggereffs.root");
  elmcinfile->cd();

  TH1D * trigeff_mcelbar1 = (TH1D*)elmcinfile->Get("trigeff_mcelbar1"); // HLT_Ele23_CaloIdL_TrackIdL_IsoVL -- Barrel MC
  TH1D * trigeff_mcelbar2 = (TH1D*)elmcinfile->Get("trigeff_mcelbar2"); // HLT_Ele27_WP85_Gsf -- Barrel MC
  TH1D * trigeff_mcelend1 = (TH1D*)elmcinfile->Get("trigeff_mcelend1"); // HLT_Ele23_CaloIdL_TrackIdL_IsoVL -- Endcap MC
  TH1D * trigeff_mcelend2 = (TH1D*)elmcinfile->Get("trigeff_mcelend2"); // HLT_Ele27_WP85_Gsf -- Endcap MC

  /////////////////////////////
  // Input Data File + Hists //
  /////////////////////////////

  TFile * muinfile = TFile::Open("output_trig/muon/Data/triggereffs.root");
  muinfile->cd();

  TH1D * trigeff_mubar1 = (TH1D*)muinfile->Get("trigeff_mubar1"); // HLT_IsoMu20 -- Barrel Data
  TH1D * trigeff_mubar2 = (TH1D*)muinfile->Get("trigeff_mubar2"); // HLT_IsoTkMu20 -- Barrel Data
  TH1D * trigeff_muend1 = (TH1D*)muinfile->Get("trigeff_muend1"); // HLT_IsoMu20 -- Endcap Data
  TH1D * trigeff_muend2 = (TH1D*)muinfile->Get("trigeff_muend2"); // HLT_IsoTkMu20 -- Endcap Data 

  TFile * elinfile = TFile::Open("output_trig/electron/Data/triggereffs.root");
  elinfile->cd();

  TH1D * trigeff_elbar1 = (TH1D*)elinfile->Get("trigeff_elbar1"); // HLT_Ele23_CaloIdL_TrackIdL_IsoVL -- Barrel Data
  TH1D * trigeff_elbar2 = (TH1D*)elinfile->Get("trigeff_elbar2"); // HLT_Ele27_WP85_Gsf -- Barrel Data 
  TH1D * trigeff_elend1 = (TH1D*)elinfile->Get("trigeff_elend1"); // HLT_Ele23_CaloIdL_TrackIdL_IsoVL -- Endcap Data 
  TH1D * trigeff_elend2 = (TH1D*)elinfile->Get("trigeff_elend2"); // HLT_Ele27_WP85_Gsf -- Endcap Data

  makecanvas(trigeff_mcmubar1,trigeff_mubar1,"muon","barrel","hltmu20");
  makecanvas(trigeff_mcmubar2,trigeff_mubar2,"muon","barrel","hlttkmu20");
  makecanvas(trigeff_mcmuend1,trigeff_muend1,"muon","endcap","hltmu20");
  makecanvas(trigeff_mcmuend2,trigeff_muend2,"muon","endcap","hlttkmu20");

  makecanvas(trigeff_mcelbar1,trigeff_elbar1,"electron","barrel","hltel23");
  makecanvas(trigeff_mcelbar2,trigeff_elbar2,"electron","barrel","hltel27");
  makecanvas(trigeff_mcelend1,trigeff_elend1,"electron","endcap","hltel23");
  makecanvas(trigeff_mcelend2,trigeff_elend2,"electron","endcap","hltel27");

}

void makecanvas(TH1D*& mchist, TH1D*& datahist, const TString lepton, const TString region, const TString trig){
  TCanvas * canvas = new TCanvas();
  canvas->cd();
  
  TPad * stackpad  = new TPad("stackpad","", 0, 0.3, 1.0, 0.98);
  stackpad->SetBottomMargin(0.02); // Upper and lower plot are joined  

  TLegend * leg = new TLegend(0.6,0.2,0.825,0.36);
  leg->SetBorderSize(4);
  leg->SetLineColor(kBlack);
  stackpad->Draw();
  stackpad->cd();
  //  stackpad->SetLogy();
  stackpad->SetLogx();
  stackpad->SetGridy();
  stackpad->SetGridx();

  TString hltname = datahist->GetTitle();

  //  datahist->SetTitle("");
  datahist->SetMaximum(1.01);
  datahist->SetTitle(Form("%s Trigger Efficiency (%s %s)",trig.Data(), lepton.Data(), region.Data()));
  datahist->GetYaxis()->SetTitle("Efficiency");
  datahist->SetLineColor(kRed);
  datahist->SetMarkerColor(kRed);
  leg->AddEntry(datahist,Form("Single %s Data",lepton.Data()),"ep1");
  datahist->Draw("EP");

  mchist->SetLineColor(kBlack);
  leg->AddEntry(mchist,"DY #rightarrow l^{+} l^{-}","ep1");
  mchist->Draw("PSAME");

  TH1D* mchistc = (TH1D*)mchist->Clone();

  mchistc->SetMarkerSize(0);
  mchistc->SetFillStyle(3254);
  mchistc->SetFillColor(kGray+3);
  mchistc->Draw("E2SAME");

  leg->Draw("SAME");

  canvas->cd();

  TPad * ratiopad = new TPad("ratiopad", "", 0, 0.05, 1.0, 0.3);
  ratiopad->Draw();
  ratiopad->cd();
  ratiopad->SetLogx();
  ratiopad->SetGridx();
  ratiopad->SetTopMargin(0.1);
  ratiopad->SetBottomMargin(0.2);

  TH1D* datahistc = (TH1D*)datahist->Clone();
  datahistc->SetName("effhist");
  datahistc->SetMaximum(1.1);
  datahistc->SetMinimum(0.9);

  datahistc->Divide(mchist);
  datahistc->GetYaxis()->SetTitle("Data/MC");
  datahistc->GetXaxis()->SetTitle("Probe p_{T} (GeV/c)");
  datahistc->GetYaxis()->SetNdivisions(505);
  datahistc->GetXaxis()->SetLabelSize(0.11);
  datahistc->GetXaxis()->SetTitleSize(0.09);
  datahistc->GetXaxis()->SetTickSize(0.11);
  datahistc->GetYaxis()->SetLabelSize(0.11);
  datahistc->GetYaxis()->SetTitleSize(0.15);
  datahistc->GetYaxis()->SetTitleOffset(0.4); 

  datahistc->Draw("EP");  

  canvas->cd();
  CMSLumi(canvas, 0);

  TString outdir = Form("output_trig/%s/scalefactor/%s/%s", lepton.Data(), region.Data(), trig.Data());
  canvas->SaveAs( Form("%s/overplot.png", outdir.Data()) );

  // for output
  TFile * outfile = new TFile( Form("%s/scalefactors.root", outdir.Data()) , "RECREATE");
  datahistc->Write();

  TString dummy = " Trigger Efficiency";
  Ssiz_t effpos = hltname.Index(dummy.Data());
  Ssiz_t hltlen = hltname.Length();
  hltname.Replace(effpos,hltlen-effpos,"");

  // more for output 
  ofstream outtext(Form("%s/trigresults.txt",outdir.Data()));
  outtext << hltname.Data() <<  " Results [" << region.Data() << "]" << std::endl;
  outtext << "-----------------------------------------" << std::endl << std::endl;

  ////////////// record results in text file /////////////

  outtext << "Data Trigger Efficiencies" << std::endl;
  for (int i = 1; i <= datahist->GetNbinsX(); i++) {
    outtext << "pT bin: " << datahist->GetXaxis()->GetBinLowEdge(i) << " - " << datahist->GetXaxis()->GetBinUpEdge(i) << " : " << datahist->GetBinContent(i) << " +/- " << datahist->GetBinError(i) << std::endl;
  }
  outtext << "-----------------------------------------" << std::endl << std::endl;

  outtext << "MC Trigger Efficiencies" << std::endl;
  for (int i = 1; i <= mchist->GetNbinsX(); i++) {
    outtext << "pT bin: " << mchist->GetXaxis()->GetBinLowEdge(i) << " - " << mchist->GetXaxis()->GetBinUpEdge(i) << " : " << mchist->GetBinContent(i) << " +/- " << mchist->GetBinError(i) << std::endl;
  }
  outtext << "-----------------------------------------" << std::endl << std::endl;

  outtext << "Scale Factors" << std::endl;
  for (int i = 1; i <= datahistc->GetNbinsX(); i++) {
    outtext << "pT bin: " << datahistc->GetXaxis()->GetBinLowEdge(i) << " - "   << datahistc->GetXaxis()->GetBinUpEdge(i) << " : " << datahistc->GetBinContent(i) << " +/- " << datahistc->GetBinError(i) << std::endl;
  }
  outtext.close();
  /////////////////////////////////////////////////////////

  //////////// record results in TeX table friendly manner //////////////////////

  TString etaregion = "";
  if (lepton.Contains("muon",TString::kExact)){
    if (region.Contains("barrel",TString::kExact)){
      etaregion = "$|\\eta| < 1.2$";
    }
    else if (region.Contains("endcap",TString::kExact)){
      etaregion = "$1.2 < |\\eta| < 2.5$";
    }
  }
  else if (lepton.Contains("electron",TString::kExact)){
    if (region.Contains("barrel",TString::kExact)){
      etaregion = "$|\\eta| < 1.4442$";
    }
    else if (region.Contains("endcap",TString::kExact)){
      etaregion = "$1.566 < |\\eta| < 2.5$";
    }
  }

  RooRealVar *mcvar = new RooRealVar("mcvar","mcvar",0.);
  RooRealVar *datavar = new RooRealVar("datavar","datavar",0.);
  RooRealVar *sfvar = new RooRealVar("sfvar","sfvar",0.);

  // make output for TeX tables
  ofstream table(Form("%s/table.txt",outdir.Data()));
  table << "\\begin{table}[h!]" << std::endl;
  table << "\\begin{center}"    << std::endl;
  table << "{\\small"           << std::endl;
  table << "\\begin{tabular}{|l|c|c|c|} \\hline" << std::endl;
  table << "$\\pt$ bin & MC Efficiency & Data Efficiency & Scale Factor \\\\ \\hline " << std::endl;
  for (int i = 1; i <= datahistc->GetNbinsX(); i++) {
    // set values in roofit
    mcvar->setVal(mchist->GetBinContent(i));
    mcvar->setError(mchist->GetBinError(i));
    datavar->setVal(datahist->GetBinContent(i));
    datavar->setError(datahist->GetBinError(i));
    sfvar->setVal(datahistc->GetBinContent(i));
    sfvar->setError(datahistc->GetBinError(i));

    table << datahistc->GetXaxis()->GetBinLowEdge(i) << "-" << datahistc->GetXaxis()->GetBinUpEdge(i) << "\\GeV &" 
	  << *(mcvar->format(2,"EXPF")) << " & " 
	  << *(datavar->format(2,"EXPF")) << " & " 
	  << *(sfvar->format(2,"EXPF")) << " & "  << "\\\\ \\hline"
	  << std::endl;
  }
  table << "\\end{tabular}" << std::endl;
  table << "}" << std::endl;
  table << "\\label{tab:" << lepton.Data() << trig.Data() << region.Data() << "}" << std::endl;
  table << "\\caption{" << hltname.Data() << " Trigger Efficiency Results (" << etaregion.Data() << ")}" << std::endl;
  table << "\\end{center}" << std::endl;
  table << "\\end{table}"  << std::endl;
  table.close();
  //////////////////////////////////////////////////////////////////////////////////////

  delete outfile;
  delete datahistc;
  delete ratiopad;
  delete mchistc;
  delete leg;
  delete stackpad;
  delete canvas;
}

void CMSLumi(TCanvas *& canv, const Int_t iPosX) { // borrowed from margaret
  TString cmsText      = "CMS";// Preliminary";
  Double_t cmsTextFont = 61;  // default is helvetic-bold
  
  Bool_t writeExtraText  = true;
  TString extraText      = "Preliminary";
  Double_t extraTextFont = 52;  // default is helvetica-italics

  double fLumi = 1.264;
  
  TString lumiText = Form("#sqrt{s} = 13 TeV, L = %1.3f fb^{-1}", fLumi);
  
  // text sizes and text offsets with respect to the top frame
  // in unit of the top margin size
  Double_t lumiTextSize     = 0.6;
  Double_t lumiTextOffset   = 0.2;
  Double_t cmsTextSize      = 0.75;
  Double_t cmsTextOffset    = 0.1;  // only used in outOfFrame version

  Double_t relPosX    = 0.045;
  Double_t relPosY    = 0.035;
  Double_t relExtraDY = 1.2;
 
  // ratio of "CMS" and extra text size
  Double_t extraOverCmsTextSize  = 0.76;
 
  Bool_t outOfFrame    = false;
  if ( iPosX/10 == 0 ) {
    outOfFrame = true;
  }

  Int_t alignY_=3;
  Int_t alignX_=2;
  if (iPosX/10 == 0) {alignX_ = 1;}
  if (iPosX == 0)    {alignY_ = 1;}
  if (iPosX/10 == 1) {alignX_ = 1;}
  if (iPosX/10 == 2) {alignX_ = 2;}
  if (iPosX/10 == 3) {alignX_ = 3;}
  Int_t align_ = 10*alignX_ + alignY_;

  Double_t H = canv->GetWh();
  Double_t W = canv->GetWw();
  Double_t l = canv->GetLeftMargin();
  Double_t t = canv->GetTopMargin();
  Double_t r = canv->GetRightMargin();
  Double_t b = canv->GetBottomMargin();
  Double_t e = 0.025;

  TLatex latex;
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);    

  Double_t extraTextSize = extraOverCmsTextSize*cmsTextSize;

  latex.SetTextFont(42);
  latex.SetTextAlign(31); 
  latex.SetTextSize(lumiTextSize*t);    
  latex.DrawLatex(1-r,1-t+lumiTextOffset*t,lumiText);

  if (outOfFrame) {
    latex.SetTextFont(cmsTextFont);
    latex.SetTextAlign(11); 
    latex.SetTextSize(cmsTextSize*t);    
    latex.DrawLatex(l,1-t+cmsTextOffset*t,cmsText);
  }
  
  Double_t posX_;
  if (iPosX%10 <= 1) {
    posX_ =   l + relPosX*(1-l-r);
  }
  else if (iPosX%10 == 2) {
    posX_ =  l + 0.5*(1-l-r);
  }
  else if (iPosX%10 == 3) {
    posX_ =  1-r - relPosX*(1-l-r);
  }

  Double_t posY_ = 1-t - relPosY*(1-t-b);

  if (!outOfFrame) {
    latex.SetTextFont(cmsTextFont);
    latex.SetTextSize(cmsTextSize*t);
    latex.SetTextAlign(align_);
    latex.DrawLatex(posX_, posY_, cmsText);
    
    if (writeExtraText) {
      latex.SetTextFont(extraTextFont);
      latex.SetTextAlign(align_);
      latex.SetTextSize(extraTextSize*t);
      latex.DrawLatex(posX_, posY_- relExtraDY*cmsTextSize*t , extraText);
    }
  }
  
  else if (outOfFrame && writeExtraText){
    if (iPosX == 0) {
      posX_ = l +  relPosX*(1-l-r)+0.05;
      posY_ = 1-t+lumiTextOffset*t;
    }
    latex.SetTextFont(extraTextFont);
    latex.SetTextSize(extraTextSize*t);
    latex.SetTextAlign(align_);
    latex.DrawLatex(posX_, posY_, extraText);      
  }
}

void SetTDRStyle(TStyle *& tdrStyle){  
  // For the canvas:
  tdrStyle->SetCanvasBorderMode(0);
  tdrStyle->SetCanvasColor(kWhite);
  tdrStyle->SetCanvasDefH(600); //Height of canvas
  tdrStyle->SetCanvasDefW(700); //Width of canvas
  tdrStyle->SetCanvasDefX(0);   //Position on screen
  tdrStyle->SetCanvasDefY(0);

  // For the Pad:
  tdrStyle->SetPadBorderMode(0);
  // tdrStyle->SetPadBorderSize(Width_t size = 1);
  tdrStyle->SetPadColor(kWhite);
  tdrStyle->SetPadGridX(false);
  tdrStyle->SetPadGridY(false);
  tdrStyle->SetGridColor(0);
  tdrStyle->SetGridStyle(3);
  tdrStyle->SetGridWidth(1);

  // For the frame:
  tdrStyle->SetFrameBorderMode(0);
  tdrStyle->SetFrameBorderSize(1);
  tdrStyle->SetFrameFillColor(0);
  tdrStyle->SetFrameFillStyle(0);
  tdrStyle->SetFrameLineColor(1);
  tdrStyle->SetFrameLineStyle(1);
  tdrStyle->SetFrameLineWidth(1);

  // For the histo:
  tdrStyle->SetHistLineColor(1);
  tdrStyle->SetHistLineStyle(0);
  tdrStyle->SetHistLineWidth(1);
  tdrStyle->SetEndErrorSize(2);
  tdrStyle->SetErrorX(0.5);
  tdrStyle->SetMarkerStyle(20);
  tdrStyle->SetMarkerSize(0.6);

  //For the fit/function:
  tdrStyle->SetOptFit(1);
  tdrStyle->SetFitFormat("5.4g");
  tdrStyle->SetFuncColor(2);
  tdrStyle->SetFuncStyle(1);
  tdrStyle->SetFuncWidth(1);

  //For the date:
  tdrStyle->SetOptDate(0);
  // tdrStyle->SetDateX(Float_t x = 0.01);
  // tdrStyle->SetDateY(Float_t y = 0.01);

  // For the statistics box:
  tdrStyle->SetOptFile(0);
  tdrStyle->SetOptStat(0); // To display the mean and RMS:   SetOptStat("mr");
  tdrStyle->SetStatColor(kWhite);
  tdrStyle->SetStatFont(42);
  tdrStyle->SetStatFontSize(0.025);
  tdrStyle->SetStatTextColor(1);
  tdrStyle->SetStatFormat("6.4g");
  tdrStyle->SetStatBorderSize(1);
  tdrStyle->SetStatH(0.1);
  tdrStyle->SetStatW(0.15);
  
  // Margins:
  tdrStyle->SetPadTopMargin(0.05);
  tdrStyle->SetPadBottomMargin(0.14);
  tdrStyle->SetPadLeftMargin(0.18);
  tdrStyle->SetPadRightMargin(0.15); 

  // For the Global title:

  tdrStyle->SetOptTitle(0);
  tdrStyle->SetTitleFont(42);
  tdrStyle->SetTitleColor(1);
  tdrStyle->SetTitleTextColor(1);
  tdrStyle->SetTitleFillColor(10);
  tdrStyle->SetTitleFontSize(0.05);
  // tdrStyle->SetTitleH(0); // Set the height of the title box
  // tdrStyle->SetTitleW(0); // Set the width of the title box
  // tdrStyle->SetTitleX(0); // Set the position of the title box
  // tdrStyle->SetTitleY(0.985); // Set the position of the title box
  // tdrStyle->SetTitleStyle(Style_t style = 1001);
  // tdrStyle->SetTitleBorderSize(2);

  // For the axis titles:

  tdrStyle->SetTitleColor(1, "XYZ");
  tdrStyle->SetTitleFont(42, "XYZ");
  tdrStyle->SetTitleSize(0.06, "XYZ");
  tdrStyle->SetTitleXOffset(0.9);
  tdrStyle->SetTitleYOffset(1.0);

  // For the axis labels:

  tdrStyle->SetLabelColor(1, "XYZ");
  tdrStyle->SetLabelFont(42, "XYZ");
  tdrStyle->SetLabelOffset(0.007, "XYZ");
  tdrStyle->SetLabelSize(0.05, "XYZ");

  // For the axis:

  tdrStyle->SetAxisColor(1, "XYZ");
  tdrStyle->SetStripDecimals(kTRUE);
  tdrStyle->SetTickLength(0.03, "XYZ");
  //  tdrStyle->SetNdivisions(510, "XYZ");
  tdrStyle->SetNdivisions(505, "X");
  tdrStyle->SetPadTickX(1);  // To get tick marks on the opposite side of the frame
  tdrStyle->SetPadTickY(1);

  // Change for log plots:
  tdrStyle->SetOptLogx(0);
  tdrStyle->SetOptLogy(0);
  tdrStyle->SetOptLogz(0);

  // Postscript options:
  // tdrStyle->SetPaperSize(15.,15.);
  // tdrStyle->SetLineScalePS(Float_t scale = 3);
  // tdrStyle->SetLineStyleString(Int_t i, const char* text);
  // tdrStyle->SetHeaderPS(const char* header);
  // tdrStyle->SetTitlePS(const char* pstitle);

  // tdrStyle->SetBarOffset(Float_t baroff = 0.5);
  // tdrStyle->SetBarWidth(Float_t barwidth = 0.5);
  // tdrStyle->SetPaintTextFormat(const char* format = "g");
  // tdrStyle->SetPalette(Int_t ncolors = 0, Int_t* colors = 0);
  // tdrStyle->SetTimeOffset(Double_t toffset);
  // tdrStyle->SetHistMinimumZero(kTRUE);
  
  ///////// pretty palette ///////////
  const Int_t NRGBs = 5;
  const Int_t NCont = 255;
  
  Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
  Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
  Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
  Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
  TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
  tdrStyle->SetNumberContours(NCont);
  /////////////////////////////////////
  
  tdrStyle->cd();
}

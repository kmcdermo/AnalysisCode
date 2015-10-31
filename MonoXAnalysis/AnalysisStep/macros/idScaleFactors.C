#include <fstream>
#include "RooRealVar.h"

using namespace RooFit;

void SetTDRStyle(TStyle *& style);
void CMSLumi(TCanvas *& canv, const Int_t iPosX);

void idScaleFactors(TString lepton, TString region, TString id, TString shape1, TString shape2){
  
  /////////////////////////////////////////////////////////////
  TStyle * tdrStyle = new TStyle("tdrStyle","Style for P-TDR");
  SetTDRStyle(tdrStyle);
  gROOT->ForceStyle();
  ////////////////////////////////////////////////////////////

  TString outdir = Form("output/%s/scalefactor/%s/%s", lepton.Data(), region.Data(), id.Data());
  ofstream outtext(Form("%s/idresults.txt",outdir.Data()));
  outtext << lepton.Data() << " " << id.Data() <<  " ID Results [" << region.Data() << "]" << std::endl;
  outtext << "-----------------------------------------" << std::endl << std::endl;
    
  TFile * datafile1 = TFile::Open( Form("output/%s/Data/%s/%s/data-efficiency%s.root", lepton.Data(), region.Data(), id.Data(), shape1.Data()) );
  TH1D  * datahist1 = (TH1D*)datafile1->Get("effhist");
  datahist1->SetTitle(Form("%s Efficiency [%s - %s ID] vs %s p_{T}", lepton.Data(), region.Data(), id.Data(), lepton.Data() ));
  datahist1->GetYaxis()->SetTitle("Efficiency");
  datahist1->SetStats(0);

  TFile * datafile2 = TFile::Open( Form("output/%s/Data/%s/%s/data-efficiency%s.root", lepton.Data(), region.Data(), id.Data(), shape2.Data()) );
  TH1D  * datahist2 = (TH1D*)datafile2->Get("effhist");
  datahist2->SetTitle("");
  datahist2->SetStats(0);

  TFile * mcfile   = TFile::Open( Form("output/%s/MC/%s/%s/mc-efficiency.root",     lepton.Data(), region.Data(), id.Data()) );
  TH1D  * mchist   = (TH1D*)mcfile->Get("effhist");
  mchist->SetTitle("");
  mchist->SetStats(0);

  ////////////// record results in text file /////////////

  outtext << "ID Efficiencies" << std::endl;
  for (int i = 1; i <= datahist1->GetNbinsX(); i++) {
    outtext << "pT bin: " << datahist1->GetXaxis()->GetBinLowEdge(i) << " - "   << datahist1->GetXaxis()->GetBinUpEdge(i) << std::endl;

    outtext << "MC Cut-n-Count:     " << mchist->GetBinContent(i)    << " +/- " << mchist->GetBinError(i)    << std::endl;
    outtext << "Nomimal Data Model: " << datahist1->GetBinContent(i) << " +/- " << datahist1->GetBinError(i) << std::endl;
    outtext << " Second Data Model: " << datahist2->GetBinContent(i) << " +/- " << datahist2->GetBinError(i) << std::endl << std::endl;
  }
  outtext << "-----------------------------------------" << std::endl << std::endl;

  TCanvas * canvas = new TCanvas();
  canvas->cd();

  // Draw main stacks
  
  TPad * stackpad  = new TPad("stackpad","", 0, 0.3, 1.0, 0.98);
  stackpad->SetBottomMargin(0.015); // Upper and lower plot are joined  

  TLegend * leg = new TLegend(0.482,0.2,0.825,0.42);
  leg->SetBorderSize(4);
  leg->SetLineColor(kBlack);
  stackpad->Draw();
  stackpad->cd();
  //  stackpad->SetLogy();
  stackpad->SetLogx();
  stackpad->SetGridy();
  stackpad->SetGridx();

  datahist1->SetMaximum(1.01);

  datahist1->SetLineColor(kRed);
  datahist1->SetMarkerColor(kRed);
  leg->AddEntry(datahist1,"Data - Sig: MC Template, Bg: RooCMS","ep1");
  datahist1->Draw("EP");

  datahist2->SetLineColor(kBlue);
  datahist2->SetMarkerColor(kBlue);
  leg->AddEntry(datahist2,"Data - Sig: MC Template, Bg: Exp","ep1");
  datahist2->Draw("EP SAME");

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

  // draw data/mc

  TPad * ratiopad = new TPad("ratiopad", "", 0, 0.18, 1.0, 0.3);
  ratiopad->Draw();
  ratiopad->cd();
  ratiopad->SetLogx();
  ratiopad->SetGridx();
  ratiopad->SetTopMargin(0.05);
  ratiopad->SetBottomMargin(0.1);

  TH1D* datahist1c = (TH1D*)datahist1->Clone();
  datahist1c->SetMaximum(1.1);
  datahist1c->SetMinimum(0.9);

  datahist1c->Divide(mchist);
  datahist1c->GetYaxis()->SetTitle("SF");
  datahist1c->GetYaxis()->SetNdivisions(304);
  datahist1c->GetXaxis()->SetLabelSize(0.);
  datahist1c->GetXaxis()->SetTitleSize(0.);
  datahist1c->GetXaxis()->SetTickSize(0.11);
  datahist1c->GetYaxis()->SetLabelSize(0.22);
  datahist1c->GetYaxis()->SetTitleSize(0.33);
  datahist1c->GetYaxis()->SetTitleOffset(0.16); 

  datahist1c->Draw("EP");  

  TH1D* datahist2c = (TH1D*)datahist2->Clone();
  datahist2c->Divide(mchist);
  datahist2c->Draw("EP SAME");  

  // save sfs

  outtext << "Scale Factors" << std::endl;
  for (int i = 1; i <= datahist1c->GetNbinsX(); i++) {
    outtext << "pT bin: " << datahist1c->GetXaxis()->GetBinLowEdge(i) << " - "   << datahist1c->GetXaxis()->GetBinUpEdge(i) << std::endl;

    outtext << "Nomimal Data Model: " << datahist1c->GetBinContent(i) << " +/- " << datahist1c->GetBinError(i) << std::endl;
    outtext << " Second Data Model: " << datahist2c->GetBinContent(i) << " +/- " << datahist2c->GetBinError(i) << std::endl;
  }
  outtext << "-----------------------------------------" << std::endl << std::endl;

  // draw systematics
  // for output, only care about one SF + systematics
  
  canvas->cd();

  TPad * systmpad = new TPad("systmpad", "", 0, 0.02, 1.0, 0.18);
  systmpad->Draw();
  systmpad->cd();
  systmpad->SetLogx();
  systmpad->SetGridx();
  systmpad->SetTopMargin(0);
  systmpad->SetBottomMargin(0.3);

  TH1D * systematics     = (TH1D*)datahist1->Clone();
  TH1D * systematics_sub = (TH1D*)datahist2->Clone();
  
  systematics->Add(systematics_sub,-1.);

  systematics->Divide(mchist);
  systematics->GetYaxis()->SetTitle("Sys Unc");
  systematics->GetYaxis()->SetNdivisions(304);
  systematics->GetXaxis()->SetLabelSize(0.2);
  systematics->GetXaxis()->SetTitleSize(0.2);
  systematics->GetXaxis()->SetTickSize(0.11);
  systematics->GetYaxis()->SetLabelSize(0.18);
  systematics->GetYaxis()->SetTitleSize(0.23);
  systematics->GetYaxis()->SetTitleOffset(0.22); 

  systematics->Draw("EP");

  outtext << "Systematic Uncertainty" << std::endl;
  for (int i = 1; i <= datahist1c->GetNbinsX(); i++) {
    outtext << "pT bin: " << datahist1c->GetXaxis()->GetBinLowEdge(i) << " - " << datahist1c->GetXaxis()->GetBinUpEdge(i) << " : "  << systematics->GetBinContent(i) << " +/- " << systematics->GetBinError(i) << std::endl;
  }
  outtext.close();

  canvas->cd();
  CMSLumi(canvas, 0);
  canvas->SaveAs(Form("%s/overplot.png",outdir.Data()));
  canvas->SaveAs(Form("%s/overplot.pdf",outdir.Data()));

  // now just save the SF plot with errors from systematics included
  
  TFile * outfile = new TFile(Form("%s/scalefactors.root",outdir.Data()), "RECREATE");
  
  // now set bin erros on datahist1c (i.e. data/MC for model template) to be stat + sys in quad
  
  for (int i = 1; i <= datahist1c->GetNbinsX(); i++){
    float stat = datahist1c->GetBinError(i);
    float sys  = std::abs(systematics->GetBinContent(i));

    datahist1c->SetBinError(i,std::sqrt(stat*stat + sys*sys));
  }

  datahist1c->SetTitle("SF vs Lepton p_{T}");
  outfile->cd();
  datahist1c->Write();

  outfile->Close();

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
  RooRealVar *datavar1 = new RooRealVar("data1var","data1var",0.);
  RooRealVar *datavar2 = new RooRealVar("data2var","data2var",0.);
  RooRealVar *sfvar = new RooRealVar("sfvar","sfvar",0.);

  // make output for TeX tables
  ofstream table(Form("%s/table.txt",outdir.Data()));
  table << "\\begin{table}[h!]" << std::endl;
  table << "\\begin{center}"    << std::endl;
  table << "{\\small"           << std::endl;
  table << "\\begin{tabular}{|l|c|c|c|c|} \\hline" << std::endl;
  table << "$\\pt$ bin & MC Efficiency & Data Model 1 Efficiency & Data Model 2 Efficiency & Scale Factor \\\\ \\hline " << std::endl;
  for (int i = 1; i <= datahist1c->GetNbinsX(); i++) {

    // set values in roofit
    mcvar->setVal(mchist->GetBinContent(i));
    mcvar->setError(mchist->GetBinError(i));
    datavar1->setVal(datahist1->GetBinContent(i));
    datavar1->setError(datahist1->GetBinError(i));
    datavar2->setVal(datahist2->GetBinContent(i));
    datavar2->setError(datahist2->GetBinError(i));
    sfvar->setVal(datahist1c->GetBinContent(i));
    sfvar->setError(datahist1c->GetBinError(i));

    // now print them out
    table << datahist1c->GetXaxis()->GetBinLowEdge(i) << "-" << datahist1c->GetXaxis()->GetBinUpEdge(i) << "\\GeV &" 
	  << *(mcvar->format(2,"EXPF")) << " & " 
	  << *(datavar1->format(2,"EXPF")) << " & " 
	  << *(datavar2->format(2,"EXPF")) << " & " 
	  << *(sfvar->format(2,"EXPF")) << "\\\\ \\hline"
	  << std::endl;
  }
  table << "\\end{tabular}" << std::endl;
  table << "}" << std::endl;
  table << "\\caption{" << lepton.Data() << " " << id.Data() << " ID Results (" << etaregion.Data() << ")}" << std::endl;
  table << "\\label{tab:" << lepton.Data() << id.Data() << region.Data() << "}" << std::endl;
  table << "\\end{center}" << std::endl;
  table << "\\end{table}"  << std::endl;
  table.close();
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

#ifndef MAKEHIST4_H
#define MAKEHIST4_H

#include <vector>
#include <fstream>
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TTreeReader.h"
#include "TTreeReaderArray.h"
#include "TLorentzVector.h"
#include "TString.h"

using namespace std;

// define binnings for the different observables
vector<float> bins_monoV_met        = {250.,300.,350.,400.,500.,600.,1000.};
vector<float> bins_substructure_met = {250.,300.,350.,400.,500.,600.,1000.};
vector<float> bins_monoJ_met        = {200.,230.,260,290,320,350,390,430,470,510,550,590,640,690,740,790,840,900,960,1020,1090,1160,1250};

vector<float> bins_monoV_mT        = {50.,100.,150.,200.,250.,300.,350.,400.,500.,600.,1000.};
vector<float> bins_substructure_mT = {50.,100.,150.,200.,250.,300.,350.,400.,500.,600.,1000.};
vector<float> bins_monoJ_mT        = {50.,80.,110.,140.,170,200.,230.,260,290,320,350,390,430,470,510,550,590,640,690,740,790,840,900,960,1020,1090,1160,1250};

vector<float> bins_monoV_mpr        = {65.,67.5,70.,72.5,75.,77.5,80.,82.5,85.,87.5,90.,92.5,95.,97.5,100.,102.5,105.};
vector<float> bins_monoJ_mpr        = {0.,3.,6.,9.,12.,15.,18.,21.,24.,27.,30.,33.,36.,39.,42.,45.,48.,51.,54.,57.,60.,64.,68.,72.,76.,80.,84.,88.,92.,96.,100.};
vector<float> bins_substructure_mpr = {0.,5.,10.,15,20.,25.,30.,35.,40.,45.,50.,55.,60.,65.,70.,75.,80.,85.,90.,95.,100.,105.,110.,115.,120.,125.,130.,135.,140.,145.,150.,155.,160.,165};

vector<float> bins_monoV_njet        = {0.,1.,2.,3.,4.,5.,6.,7.,8.};
vector<float> bins_monoJ_njet        = {0.,1.,2.,3.,4.,5.,6.,7.,8.};
vector<float> bins_substructure_njet = {0.,1.,2.,3.,4.,5.,6.,7.,8.};

vector<float> bins_monoV_HT = {0,50.,100.,150.,200.,250.,300.,350.,400.,450.500,550,600.,650,700.,750,850,950,1050,1250,1450,1650,1850,2100};
vector<float> bins_monoJ_HT = {0,50.,100.,150.,200.,250.,300.,350.,400.,450.500,550,600.,650,700.,750,850,950,1050,1250,1450,1650,1850,2100};
vector<float> bins_substructure_HT = {0,50.,100.,150.,200.,250.,300.,350.,400.,450.500,550,600.,650,700.,750,850,950,1050,1250,1450,1650,1850,2100};

vector<float> bins_monoV_jetPt = {200.,225.,250.,300.,350.,400.,500.,600.,1000.};
vector<float> bins_monoJ_jetPt = {100.,120.,140.,160.,180.,200.,230.,260,290,320,350,390,430,470,510,550,590,640,690,740,790,840,900,960,1020,1090,1160,1250};
vector<float> bins_substructure_jetPt = {100.,120.,140.,160.,180.,200.,230.,260,290,320,350,390,430,470,510,550,590,640,690,740,790,840,900,960,1020,1090,1160,1250};

vector<float> bins_monoV_bosonPt = {50.,70.,90.,120.,150.,180.,210.,230.,250.,300.,350.,400.,500.,600.,1000.};
vector<float> bins_monoJ_bosonPt = {50.,70.,90.,120.,150.,180.,210.,230.,260,290,320,350,390,430,470,510,550,590,640,690,740,790,840,900,960,1020,1090,1160,1250.};
vector<float> bins_substructure_bosonPt = {50.,70.,90.,120.,150.,180.,210.,230.,260,290,320,350,390,430,470,510,550,590,640,690,740,790,840,900,960,1020,1090,1160,1250.};

vector<float> bins_monoV_QGL = {0.,0.04,0.08,0.12,0.16,0.24,0.32,0.40,0.48,0.60,0.68,0.76,0.84,0.88,0.92,0.96,1.};
vector<float> bins_monoJ_QGL = {0.,0.04,0.08,0.12,0.16,0.24,0.32,0.40,0.48,0.60,0.68,0.76,0.84,0.88,0.92,0.96,1.};
vector<float> bins_substructure_QGL = {0.,0.04,0.08,0.12,0.16,0.24,0.32,0.40,0.48,0.60,0.68,0.76,0.84,0.88,0.92,0.96,1.};

vector<float> bins_monoV_tau2tau1 = {0.,0.08,0.16,0.24,0.32,0.40,0.48,0.56,0.64,0.72,0.80,0.90,1.};
vector<float> bins_monoJ_tau2tau1 = {0.,0.04,0.08,0.12,0.16,0.20,0.24,0.28,0.32,0.36,0.40,0.44,0.48,0.52,0.56,0.60,0.64,0.68,0.72,0.76,0.80,0.84,0.90,1.};
vector<float> bins_substructure_tau2tau1 = {0.,0.08,0.16,0.24,0.32,0.40,0.48,0.56,0.64,0.72,0.80,0.90,1.};

vector<float> bins_monoV_nvtx = {0.,2.,4.,6.,8.,10.,12.,14.,16,18,20,22,24,26,28,30,32};
vector<float> bins_monoJ_nvtx = {0.,2.,4.,6.,8.,10.,12.,14.,16,18,20,22,24,26,28,30,32};
vector<float> bins_substructure_nvtx = {0.,2.,4.,6.,8.,10.,12.,14.,16,18,20,22,24,26,28,30,32};

vector<float> bins_monoV_chfrac = {0.,0.04,0.08,0.12,0.16,0.20,0.24,0.28,0.32,0.36,0.40,0.44,0.48,0.52,0.56,0.60,0.64,0.68,0.72,0.76,0.80,0.84,0.88,0.92,0.96,1.};
vector<float> bins_monoJ_chfrac = {0.,0.04,0.08,0.12,0.16,0.20,0.24,0.28,0.32,0.36,0.40,0.44,0.48,0.52,0.56,0.60,0.64,0.68,0.72,0.76,0.80,0.84,0.88,0.92,0.96,1.};
vector<float> bins_substructure_chfrac = {0.,0.04,0.08,0.12,0.16,0.20,0.24,0.28,0.32,0.36,0.40,0.44,0.48,0.52,0.56,0.60,0.64,0.68,0.72,0.76,0.80,0.84,0.88,0.92,0.96,1.};

vector<float> bins_monoV_nhfrac = {0.,0.04,0.08,0.12,0.16,0.20,0.24,0.28,0.32,0.36,0.40,0.44,0.48,0.52,0.56,0.60,0.64,0.68,0.72,0.76,0.80,0.84,0.88,0.92,0.96,1.};
vector<float> bins_monoJ_nhfrac = {0.,0.04,0.08,0.12,0.16,0.20,0.24,0.28,0.32,0.36,0.40,0.44,0.48,0.52,0.56,0.60,0.64,0.68,0.72,0.76,0.80,0.84,0.88,0.92,0.96,1.};
vector<float> bins_substructure_nhfrac = {0.,0.04,0.08,0.12,0.16,0.20,0.24,0.28,0.32,0.36,0.40,0.44,0.48,0.52,0.56,0.60,0.64,0.68,0.72,0.76,0.80,0.84,0.88,0.92,0.96,1.};

// binning selections
vector<float> selectBinning (string observable, int category){
  
  if(observable == "met" and category <= 1)
    return bins_monoJ_met;
  else if(observable == "met" and category > 1 and category <=3)
    return bins_monoV_met;
  else if(observable == "met" and category > 3)
    return bins_substructure_met;

  if(observable == "mT" and category <= 1)
    return bins_monoJ_mT;
  else if(observable == "mT" and category > 1 and category <=3)
    return bins_monoV_mT;
  else if(observable == "mT" and category > 3)
    return bins_substructure_mT;

  else if(observable == "mpruned" and category <=1)
    return bins_monoJ_mpr;
  else if(observable == "mpruned" and category > 1 and category <=3)
    return bins_monoV_mpr;
  else if(observable == "mpruned" and category > 3)
    return bins_substructure_mpr;

  else if(observable == "tau2tau1" and category <= 1)
    return bins_monoJ_tau2tau1;
  else if(observable == "tau2tau1" and category > 1 and category <=3)
    return bins_monoV_tau2tau1;
  else if(observable == "tau2tau1" and category > 1)
    return bins_substructure_tau2tau1;

  else if(observable == "njet" and category <= 1)
    return bins_monoJ_njet;
  else if(observable == "njet" and category > 1 and category <= 3)
    return bins_monoV_njet;
  else if(observable == "njet" and category > 3)
    return bins_substructure_njet;

  else if(observable == "nbjet" and category <= 1)
    return bins_monoJ_njet;
  else if(observable == "nbjet" and category > 1 and category <= 3)
    return bins_monoV_njet;
  else if(observable == "nbjet" and category > 3)
    return bins_substructure_njet;

  else if(observable == "ht" and category <= 1)
    return bins_monoJ_HT;
  else if(observable == "ht" and category > 1 and category <= 3)
    return bins_monoV_HT;
  else if(observable == "ht" and category > 3)
    return bins_substructure_HT;
  
  else if(observable == "nvtx" and category <= 1)
    return bins_monoJ_nvtx;
  else if(observable == "nvtx" and category > 1 and category <= 3)
    return bins_monoV_nvtx;
  else if(observable == "nvtx" and category > 3)
    return bins_substructure_nvtx;

  else if(observable == "chfrac" and category <= 1)
    return bins_monoJ_chfrac;
  else if(observable == "chfrac" and category > 1 and category <= 3)
    return bins_monoV_chfrac;
  else if(observable == "chfrac" and category > 3)
    return bins_substructure_chfrac;

  else if(observable == "nhfrac" and category <= 1)
    return bins_monoJ_nhfrac;
  else if(observable == "nhfrac" and category > 1 and category <= 3)
    return bins_monoV_nhfrac;
  else if(observable == "nhfrac" and category > 3)
    return bins_substructure_nhfrac;

  else if(observable == "bosonPt" and category <= 1)
    return bins_monoJ_bosonPt;
  else if(observable == "bosonPt" and category > 1 and category <= 3)
    return bins_monoV_bosonPt;
  else if(observable == "bosonPt" and category > 3)
    return bins_substructure_bosonPt;

  else if((observable == "jetPt" or observable == "boostedJetPt") and category <= 1)
    return bins_monoJ_jetPt;
  else if((observable == "jetPt" or observable == "boostedJetPt") and category > 1 and category <= 3)
    return bins_monoV_jetPt;
  else if((observable == "jetPt" or observable == "boostedJetPt") and category > 3)
    return bins_substructure_jetPt;

  else if(TString(observable).Contains("QGL") and category <= 1)
    return bins_monoJ_QGL;
  else if(TString(observable).Contains("QGL") and category > 1 and category <= 3)
    return bins_monoV_QGL;
  else if(TString(observable).Contains("QGL") and category > 3)
    return bins_monoV_QGL;

  vector<float> dummy;
  return dummy;
  
}


// some basic cut values
const float tau2tau1      = 0.6;
const float prunedMassMin = 65.;
const float ptJetMinAK8   = 250.;

void makehist4(TTree* tree, /*input tree*/ 
	       vector<TH1*> hist1D, /* set of 1D histogram */ 
	       vector<TH2*> hist2D, /* set of 2D histogram */ 
	       bool   isMC, 
	       int    sample, 
	       int    category,
	       bool   isWJet,
	       double scale,
	       double lumi,	       
	       int    QGLweight,
	       vector<TH1*> khists, 
	       string sysName,	       
	       bool   reweightNVTX = true,
	       TH1* rhist = NULL) {

  if(not tree){
    cout<<" empty tree --> skip process "<<endl;
    return;
  }

  // in case you want to weight the NVTX distribution
  TFile* pufile;
  TH1*   puhist = NULL;
  if(reweightNVTX){
    pufile = TFile::Open("$CMSSW_BASE/src/AnalysisCode/MonoXAnalysis/data/npvWeight/purwt.root");
    puhist = (TH1*) pufile->Get("puhist");
  }
    
  // Lepton ID scale factor from tag and probe: muons, electrons 
  TFile* sffile  = TFile::Open("$CMSSW_BASE/src/AnalysisCode/MonoXAnalysis/data/leptonSF/leptonIDsfs.root");
  
  TH2*  msflhist = (TH2*)sffile->Get("muon_loose_SF");
  TH2*  msfthist = (TH2*)sffile->Get("muon_tight_SF");
  
  TH2*  esflhist = (TH2*)sffile->Get("electron_veto_SF");
  TH2*  esfthist = (TH2*)sffile->Get("electron_tight_SF");
  
  // Photon ID scale factor from tag and probe
  TFile* psffile = TFile::Open("$CMSSW_BASE/src/AnalysisCode/MonoXAnalysis/data/photonSF/PhotonSFandEffandPurity_Lumi2p1fb_0202.root");
  TH2*  psfhist  = (TH2*)psffile->Get("PhotonSF");  
  TH2*  purhist  = (TH2*)psffile->Get("PhotonPurity");
  
  // trigger efficiency correction for single electron trigger
  TFile* trefile = TFile::Open("$CMSSW_BASE/src/AnalysisCode/MonoXAnalysis/data/triggerSF/leptonTrigsfs.root");
  TH2*   trehist = (TH2*)trefile->Get("hltel27_SF");
  
  // trigger efficiency for met trigger
  TFile* trmfile = TFile::Open("$CMSSW_BASE/src/AnalysisCode/MonoXAnalysis/data/triggerSF/mettrigSF.root");
  TH1*   trmhist = (TH1*)trefile->Get("mettrigSF");

  // QGL rewight
  TFile* QGLReweight = TFile::Open("$CMSSW_BASE/src/AnalysisCode/MonoXAnalysis/data/QGLWeight/QGLWeight.root ");
  TH2* QGLWeightHist = NULL;

  if(QGLweight == 1 and sysName != "QGLup" and sysName != "QGLdw") // zmumu
    QGLWeightHist = (TH2*) QGLReweight->Get("QGL_weight_Z");
  else if(QGLweight == 1 and sysName == "QGLup")
    QGLWeightHist = (TH2*) QGLReweight->Get("QGL_weight_Z_up");
  else if(QGLweight == 1 and sysName == "QGLdw")
    QGLWeightHist = (TH2*) QGLReweight->Get("QGL_weight_Z_dw");

  if(QGLweight == 2 and sysName != "QGLup" and sysName != "QGLdw") // zmumu
    QGLWeightHist = (TH2*) QGLReweight->Get("QGL_weight_W");
  else if(QGLweight == 3 and sysName == "QGLup")
    QGLWeightHist = (TH2*) QGLReweight->Get("QGL_weight_W_up");
  else if(QGLweight == 3 and sysName == "QGLdw")
    QGLWeightHist = (TH2*) QGLReweight->Get("QGL_weight_W_dw");
  
  if(QGLweight == 3 and sysName != "QGLup" and sysName != "QGLdw") // zmumu
    QGLWeightHist = (TH2*) QGLReweight->Get("QGL_weight_G");
  else if(QGLweight == 3 and sysName == "QGLup")
    QGLWeightHist = (TH2*) QGLReweight->Get("QGL_weight_G_up");
  else if(QGLweight == 3 and sysName == "QGLdw")
    QGLWeightHist = (TH2*) QGLReweight->Get("QGL_weight_G_dw");

  if(QGLweight == 4 and sysName != "QGLup" and sysName != "QGLdw") // zmumu
    QGLWeightHist = (TH2*) QGLReweight->Get("QGL_weight_T");
  else if(QGLweight == 4 and sysName == "QGLup")
    QGLWeightHist = (TH2*) QGLReweight->Get("QGL_weight_T_up");
  else if(QGLweight == 4 and sysName == "QGLdw")
    QGLWeightHist = (TH2*) QGLReweight->Get("QGL_weight_T_dw");

  // histogram to be filled
  for(size_t ihist  = 0 ; ihist < hist1D.size(); ihist++)
    hist1D.at(ihist)->Sumw2();
  for(size_t ihist  = 0 ; ihist < hist2D.size(); ihist++)
    hist2D.at(ihist)->Sumw2();
  
  // define branches
  TTreeReader myReader(tree);

  // general info
  TTreeReaderValue<unsigned int> run    (myReader,"run");
  TTreeReaderValue<unsigned int> event    (myReader,"event");
  TTreeReaderValue<unsigned int> nvtx   (myReader,"nvtx");
  TTreeReaderValue<double> xsec      (myReader,"xsec");
  TTreeReaderValue<double> wgt       (myReader,"wgt");

  // take some wgt for MC events
  string wgtname;
  string wgtpileupname;
  string btagname;
  if(isMC){
    wgtname = "wgtsum";
    wgtpileupname = "wgtpileup";
    if(sysName == "btagUp")
      btagname = "wgtbtagUp";
    else if(sysName == "btagDown")
      btagname = "wgtbtagDown";
    else
      btagname = "wgtbtag";
  }
  else{
    wgtname  = "wgt";
    btagname = "wgt";
    wgtpileupname = "wgt";
  }

  TTreeReaderValue<double> wgtsum    (myReader,wgtname.c_str());
  TTreeReaderValue<double> wgtpileup (myReader,wgtpileupname.c_str());
  TTreeReaderValue<double> wgtbtag   (myReader,btagname.c_str());
  
  // trigger
  TTreeReaderValue<UChar_t> hltm (myReader,"hltmet90");
  TTreeReaderValue<UChar_t> hlte (myReader,"hltsingleel");
  TTreeReaderValue<UChar_t> hltp (myReader,"hltphoton165");
  TTreeReaderValue<UChar_t> hltp2 (myReader,"hltphoton175");
  TTreeReaderValue<UChar_t> fhbhe (myReader,"flaghbheloose");
  TTreeReaderValue<UChar_t> fhbiso (myReader,"flaghbheiso");
  
  // MET filters
  string cscname;
  string feebname;
  string fmutrkname;
  string fbtrkname;

  if(isMC){
    cscname  = "flagcsctight";
    feebname = "flageebadsc";
    fmutrkname = "flagcsctight";
    fbtrkname  = "flagcsctight";
  }
  else{
    cscname    = "flagcscnew";
    feebname   = "flageescnew";
    fmutrkname = "flagmuontrack";
    fbtrkname  = "flagbadtrack";
  }
  
  TTreeReaderValue<UChar_t> fcsc (myReader,cscname.c_str());
  TTreeReaderValue<UChar_t> feeb (myReader,feebname.c_str());

  TTreeReaderValue<UChar_t> fmutrk (myReader,fmutrkname.c_str());
  TTreeReaderValue<UChar_t> fbtrk (myReader,fbtrkname.c_str());

  TTreeReaderValue<unsigned int>    njets  (myReader,"njets");
  TTreeReaderValue<unsigned int>    nbjets (myReader,"nbjetslowpt");
  TTreeReaderValue<double> j1pt   (myReader,"leadingjetpt");
  TTreeReaderValue<double> ht     (myReader,"ht");
  
  TTreeReaderValue<vector<double> > jetpt  (myReader,"centraljetpt");
  TTreeReaderValue<vector<double> > jetQGL (myReader,"centraljetQGL");
  TTreeReaderValue<vector<double> > jeteta (myReader,"centraljeteta");
  TTreeReaderValue<vector<double> > jetphi (myReader,"centraljetphi");
  TTreeReaderValue<vector<double> > jetbtag (myReader,"centraljetbtag");
  TTreeReaderValue<vector<double> > jetm   (myReader,"centraljetm");
  TTreeReaderValue<vector<double> > chfrac (myReader,"centraljetCHfrac");
  TTreeReaderValue<vector<double> > nhfrac (myReader,"centraljetNHfrac");
  TTreeReaderValue<vector<double> > emfrac (myReader,"centraljetEMfrac");

  // AK8 jet
  TTreeReaderValue<vector<double> > boostedJetpt    (myReader,"boostedJetpt");
  TTreeReaderValue<vector<double> > boostedJetQGL   (myReader,"boostedJetQGL");
  TTreeReaderValue<vector<double> > boostedJeteta   (myReader,"boostedJeteta");
  TTreeReaderValue<vector<double> > boostedJetphi   (myReader,"boostedJetphi");
  TTreeReaderValue<vector<double> > boostedJetm     (myReader,"boostedJetm");
  TTreeReaderValue<vector<double> > prunedJetm      (myReader,"prunedJetm");
  TTreeReaderValue<vector<double> > boostedJettau2  (myReader,"boostedJettau2");
  TTreeReaderValue<vector<double> > boostedJettau1  (myReader,"boostedJettau1");
  TTreeReaderValue<vector<double> > boostedJetBosoneta  (myReader,"boostedJetBosoneta");
  TTreeReaderValue<vector<double> > boostedJetBosonphi  (myReader,"boostedJetBosonphi");

  // met
  string metSuffix = "";
  if(sysName == "muUp")
    metSuffix = "MuEnUp";
  else if(sysName == "muDown")
    metSuffix = "MuEnDown";
  else if(sysName == "elUp")
    metSuffix = "ElEnUp";
  else if(sysName == "elDown")
    metSuffix = "ElEnDown";
  else if(sysName == "phoUp")
    metSuffix = "PhoEnUp";
  else if(sysName == "phoDown")
    metSuffix = "PhoEnDown";
  else if(sysName == "tauUp")
    metSuffix = "TauEnUp";
  else if(sysName == "tauDown")
    metSuffix = "TauEnDown";
 else if(sysName == "jesUp")
    metSuffix = "JetEnUp";
  else if(sysName == "jesDown")
    metSuffix = "JetEnDown";
 else if(sysName == "jerUp")
    metSuffix = "JeeResUp";
  else if(sysName == "jerDown")
    metSuffix = "JetResDown";
 else if(sysName == "uncUp")
    metSuffix = "UncEnUp";
  else if(sysName == "uncDown")
    metSuffix = "UncEnDown";
  

  TTreeReaderValue<double> met (myReader,("t1pfmet"+metSuffix).c_str());
  TTreeReaderValue<double> metphi (myReader,"t1pfmetphi");
  TTreeReaderValue<double> mmet (myReader,"t1mumet");
  TTreeReaderValue<double> mmetphi (myReader,"t1mumetphi");
  
  TTreeReaderValue<double> emet (myReader,"t1elmet");
  TTreeReaderValue<double> emetphi (myReader,"t1elmetphi");
  
  TTreeReaderValue<double> pmet (myReader,"t1phmet");
  TTreeReaderValue<double> pmetphi (myReader,"t1phmetphi");
  
  // dphi
  TTreeReaderValue<double> jmmdphi (myReader,"incjetmumetdphimin4");
  TTreeReaderValue<double> jemdphi (myReader,"incjetelmetdphimin4");
  TTreeReaderValue<double> jpmdphi (myReader,"incjetphmetdphimin4");

  TTreeReaderValue<int> mu1pid (myReader,"mu1pid");
  TTreeReaderValue<int> mu2pid (myReader,"mu2pid");
  TTreeReaderValue<int> mu1id (myReader,"mu1id");
  TTreeReaderValue<int> mu2id (myReader,"mu2id");
  TTreeReaderValue<double> mu1pt (myReader,"mu1pt");
  TTreeReaderValue<double> mu2pt (myReader,"mu2pt");
  TTreeReaderValue<double> mu1eta (myReader,"mu1eta");
  TTreeReaderValue<double> mu2eta (myReader,"mu2eta");
  TTreeReaderValue<double> mu1phi (myReader,"mu1phi");
  TTreeReaderValue<double> mu2phi (myReader,"mu2phi");

  TTreeReaderValue<int> el1pid (myReader,"el1pid");
  TTreeReaderValue<int> el2pid (myReader,"el2pid");
  TTreeReaderValue<int> el1id (myReader,"el1id");
  TTreeReaderValue<int> el2id (myReader,"el2id");
  TTreeReaderValue<double> el1pt (myReader,"el1pt");
  TTreeReaderValue<double> el2pt (myReader,"el2pt");
  TTreeReaderValue<double> el1eta (myReader,"el1eta");
  TTreeReaderValue<double> el2eta (myReader,"el2eta");
  TTreeReaderValue<double> el1phi (myReader,"el1phi");
  TTreeReaderValue<double> el2phi (myReader,"el2phi");
  
  TTreeReaderValue<int> phidm (myReader,"phidm");
  TTreeReaderValue<double> phpt (myReader,"phpt");
  TTreeReaderValue<double> pheta (myReader,"pheta");
  TTreeReaderValue<double> phphi (myReader,"phphi");
  
  TTreeReaderValue<double> wzpt (myReader,"wzpt");
  TTreeReaderValue<double> wzeta (myReader,"wzeta");
  TTreeReaderValue<double> zmass (myReader,"zmass");
  TTreeReaderValue<double> zmmpt (myReader,"zpt");
  TTreeReaderArray<double> zeept (myReader,"zeept.zeeept");
  TTreeReaderValue<double> zeeeta (myReader,"zeeeta");
  TTreeReaderValue<double> zmmeta (myReader,"zeta");

  // loop on events
  while(myReader.Next()){
    // check trigger depending on the sample
    Double_t hlt = 0.0;
    if (sample == 0 || sample == 1 || sample == 2 || sample == 7)  hlt = *hltm;
    else if (sample == 3 || sample == 4 || sample == 8) {
      hlt = *hlte;
      if(*hlte == 0) hlt =  *hltp;
    }
    else if (sample == 5 || sample == 6) hlt = *hltp;

    // check both photon triggers
    if ((sample == 5 || sample == 6) && *hltp2 > 0)  hlt = *hltp2;
    
    // check dphi jet-met
    Double_t jmdphi = 0.0;
    
    if (sample == 0 || sample == 1 || sample == 2 || sample == 7) jmdphi = fabs(*jmmdphi);
    else if (sample == 3 || sample == 4 || sample == 8)           jmdphi = fabs(*jemdphi);
    else if (sample == 5 || sample == 6)           jmdphi = fabs(*jpmdphi);

    //set met
    Double_t pfmet = 0.0;
    Double_t pfmetphi = 0.0;
    if (sample == 0 || sample == 1 || sample == 2 || sample == 7){ pfmet = *mmet; pfmetphi = *mmetphi;}
    else if (sample == 3 || sample == 4 || sample == 8)          { pfmet = *emet; pfmetphi = *emetphi;}
    else if (sample == 5 || sample == 6)          { pfmet = *pmet; pfmetphi = *pmetphi;}
    else if (sample == 7 and (*hlte or *hltp))    { pfmet = *emet; pfmetphi = *emetphi;}
    else if (sample == 7 and not *hlte)           { pfmet = *mmet; pfmetphi = *mmetphi;}

    // set lepton info
    Int_t    id1   = 0;
    Int_t    id2   = 0;
    Double_t pt1   = 0.0;
    Double_t pt2   = 0.0;
    Double_t eta1  = 0.0;
    Double_t eta2  = 0.0;
    Double_t phi1  = 0.0;
    Double_t phi2  = 0.0;
    int pid1  = 0;
    int pid2  = 0;

    if (sample == 1 || sample == 2 || sample == 7) {
      id1  = *mu1id;
      id2  = *mu2id;
      pt1  = *mu1pt;
      pt2  = *mu2pt;
      pid1 = *mu1pid;
      pid2 = *mu2pid;
      eta1 = fabs(*mu1eta);
      eta2 = fabs(*mu2eta);
      phi1 = fabs(*el1phi);
      phi2 = fabs(*el2phi);
    }
    else if (sample == 3 || sample == 4 || sample == 8) {
      id1  = *el1id;
      id2  = *el2id;
      pt1  = *el1pt;
      pt2  = *el2pt;
      eta1 = fabs(*el1eta);
      eta2 = fabs(*el2eta);
      phi1 = fabs(*el1phi);
      phi2 = fabs(*el2phi);
      pid1 = *el1pid;
      pid2 = *el2pid;
    }
    else if (sample == 5 || sample == 6) {
      id1  = 1.0;
      id2  = 1.0;
      pt1  = *phpt;
      eta1 = fabs(*pheta);
    }
    
    if (pt1 >= 1000.) 
      pt1 = 999.0;
    if (pt2 >= 1000.) 
      pt2 = 999.0;


    // set zpt in case of Zsamples
    Double_t bosonPt = 0.0;
    if (sample == 1)      bosonPt = *zmmpt; // di-muon CR
    else if (sample == 3) bosonPt = zeept[0]; // di-electron CR
    else if (sample == 5) bosonPt = *phpt; // gamma+jets
    else if (sample == 2 or sample == 4){ // single muon or single ele
      TLorentzVector lep4V, met4V;
      lep4V.SetPtEtaPhiM(pt1,eta1,phi1,0.);
      met4V.SetPtEtaPhiM(*met,0.,*metphi,0.);
      bosonPt = (lep4V+met4V).Pt();
    }

    // scale factor for leptons
    TH2* sflhist = NULL;
    TH2* sfthist = NULL;
    
    if (sample == 1 || sample == 2 || sample == 7) {
	sflhist = msflhist;
	sfthist = msfthist;
    }
    if (sample == 3 || sample == 4 || sample == 8) {
	sflhist = esflhist;
	sfthist = esfthist;
    }
    
    Double_t sfwgt = 1.0;
    if (isMC && sflhist && sfthist) {
      if (pt1 > 0.) {
	if (id1 == 1) sfwgt *= sfthist->GetBinContent(sfthist->FindBin(pt1, eta1)); 
	else          sfwgt *= sflhist->GetBinContent(sflhist->FindBin(pt1, eta1)); 
      }
      if (pt2 > 0.) {
	if (id2 == 1) sfwgt *= sfthist->GetBinContent(sfthist->FindBin(pt2, eta2)); 
	else          sfwgt *= sflhist->GetBinContent(sflhist->FindBin(pt2, eta2)); 
      }
    }
    
    // trigger scale factor
    if (isMC && trehist && ( sample == 4 || sample == 8)) {
      if (pt1 > 0. && id1 == 1) {
	sfwgt *= trehist->GetBinContent(trehist->FindBin(pt1, eta1));
      }
    }

    // photon id scale factor
    if (isMC && psfhist && (sample == 5 || sample == 6)) {
      if (pt1 > 0. && id1 == 1) {
	sfwgt *= psfhist->GetBinContent(psfhist->FindBin(pt1, eta1));
      }
    }

    // photon purity
    if (!isMC && purhist && sample == 6) {
      if (pt1 > 175. && id1 == 1) {
	sfwgt *= (1.0 - purhist->GetBinContent(purhist->FindBin(pt1, eta1)));
	}
    }

    // met trigger scale factor
    if (isMC && trmhist && (sample == 0 || sample == 1 || sample == 2 || sample == 7)) {
      sfwgt *= trmhist->GetBinContent(trmhist->FindBin(pfmet));
    }

    // QGL weight    
    if(isMC and QGLWeightHist and QGLweight != 0){
      if(jetQGL->size() > 0)
	sfwgt *= QGLWeightHist->GetBinContent(QGLWeightHist->FindBin(jetpt->at(0),jetQGL->at(0)));
      else
	sfwgt *= 1.;
    }
    
    //V-tagging scale factor --> only for mono-V
    if(isMC && category == 2 && isWJet){
      if(tau2tau1 == 0.45){
	if(sysName == "VtagUp")
	  sfwgt *= (0.692+0.144);
	else if(sysName == "VtagDown")
	  sfwgt *= (0.692-0.144);
	else
	  sfwgt *= 0.692;
      }
      else if(tau2tau1 == 0.6){
	if(sysName == "VtagUp")
	  sfwgt *= (1.031+0.129);
	else if(sysName == "VtagDown")
	  sfwgt *= (1.031-0.129);
	else
	  sfwgt *= 1.031;
      }
    }
    else if(isMC && category == 3 && isWJet){
      if(tau2tau1 == 0.45){
	if(sysName == "VtagUp")
	  sfwgt *= (1.458+0.381);
	else if(sysName == "VtagDown")
	  sfwgt *= (1.458-0.381);
	else
	  sfwgt *= 1.458;
      }
      else if(tau2tau1 == 0.6){
	if(sysName == "VtagUp")
	  sfwgt *= (0.881+0.490);
	else if(sysName == "VtagDown")
	  sfwgt *= (0.881-0.490);
	else
	  sfwgt *= 0.881;
      }
    }
      
    // Gen level info --> NLO re-weight
    Double_t kvar = *wzpt;
    if (*wzpt < 100. ) 
      *wzpt = 100.;
    if (*wzpt > 1000.) 
      *wzpt = 999.;
    
    Double_t rwgt = 1.0;
    if (rhist) 
      rwgt = rhist->GetBinContent(rhist->FindBin(*wzpt));
    
    Double_t kwgt = 1.0;
    for (unsigned i = 0; i < khists.size(); i++) {
      if (isMC && khists[i]) kwgt *= khists[i]->GetBinContent(khists[i]->FindBin(*wzpt));
    }
    
    // Trigger Selection
    if (hlt  == 0) continue; // trigger
    // MET Filters
    if (*fhbhe == 0 || *fhbiso == 0 || *fcsc == 0 || *feeb == 0) continue;
    // Additional met filters
    if (not isMC){
      if(*fmutrk == 0 || *fbtrk == 0) continue; // met filters
    }
    // N-jets
    if (*njets  < 1) continue; 
    // B-veto, not for top control sample
    if (*nbjets > 0 and sample != 7 and sample != 8) continue; 
    // control regions with two leptons --> opposite charge
    if (sample == 1 && *mu1pid == *mu2pid) continue;
    if (sample == 3 && *el1pid == *el2pid) continue;
    // control regions with two leptons --> one should be tight
    if ((sample == 1 || sample == 3)){
	if(sample == 1 and id1 == 1){
	  if(pt1 < 20) continue;
	}
	else if(sample == 1 and id2 == 1){
	  if(pt2 < 20) continue;
	}

	if(sample == 3 and id1 == 1){
	  if(pt1 < 40) continue;
	}
	else if(sample == 3 and id2 == 1){
	  if(pt2 < 40) continue;
	}	
    }
    // control regions wit one lepton --> tight requirement 
    if ((sample == 2 || sample == 4) && id1 != 1) continue;
    // photon control sample
    if ((sample == 5 || sample == 6) && *phpt < 175.) continue;
    if ((sample == 5 || sample == 6) && fabs(*pheta) > 1.4442) continue;
    // Wenu kill QCD
    if (sample == 4 && *met < 50.) continue;
    // n-bjets cut for unboosted categories
    if ((sample == 7 || sample == 8) && (category !=2 and category !=3)  && *nbjets < 1) continue;
    if ( sample == 7 || sample == 8){ // select only events with one lepton
      // at least one lepton in the plateau region
      if(pt1 <=0 or id1 != 1) continue;
      if(abs(pid1) == 13 && pt1 < 20. ) continue;
      if(abs(pid1) == 11 && pt1 < 40. ) continue;
      // met cut
      if(sample == 8 && *met < 50.) continue;
      // veto di-lepton events
      if(pt2 > 0) continue;
    }
    
    // met selection
    if(category <= 1){
      if (pfmet < 200.) continue;
    }
    else{
      if(pfmet < 250.) continue;
    }

    // inclusive mono-jet analysis 
    if(category == 0){ 
      if (chfrac->size() == 0 || nhfrac->size() == 0 or jetpt->size() == 0) continue; // at least one leading jet
      if (chfrac->at(0) < 0.1) continue;   // jet id
      if (nhfrac->at(0) > 0.8) continue;   // jet id
      if (jetpt->at(0)  < 100.) continue;  // jet1 > 100 GeV
      if (jetpt->at(0)  < *j1pt) continue; 
      if (jmdphi < 0.5) continue; // deltaPhi cut
    }
    else{

      
      // boosted category and monojet
      // So far MonoJet = jet pt < 200 + jetPt > 200 && pruned mass < 40
      bool goodMonoJet = false;
      bool goodMonoV   = false;

      if(category == 1){ // mono jet + V-jet veto

	if (chfrac->size() == 0 || nhfrac->size() == 0 or jetpt->size() == 0) continue; // at least one leading jet                                                         
	if (chfrac->at(0) < 0.1) continue;   // jet id                                                                                                                       
	if (nhfrac->at(0) > 0.8) continue;   // jet id                                                                                                                        
	if (jetpt->at(0)  < 100.) continue;  // jet1 > 100 GeV                                                                                                             
	if (jetpt->at(0)  < *j1pt) continue;
	if (jmdphi < 0.5) continue; // deltaPhi cut                                                                                                          
	
	if(boostedJetpt->size()  == 0) // no boosted jets (AK8 pT > 200 GeV)
	  goodMonoJet = true;

	if(boostedJetpt->size() > 0){ // in case one boosted jet

	  if(boostedJetpt->at(0) < ptJetMinAK8) // check pT
	    goodMonoJet = true;
	  else{ // if high pT check pruned mass

	    TLorentzVector jetak4, jetak8;
	    jetak4.SetPtEtaPhiM(jetpt->at(0),jeteta->at(0),jetphi->at(0),jetm->at(0));
	    jetak8.SetPtEtaPhiM(boostedJetpt->at(0),boostedJeteta->at(0),boostedJetphi->at(0),boostedJetm->at(0));

	    if(jetak4.DeltaR(jetak8) > 0.8) continue;
	    	    
	    // jet met dphi     
	    float deltaPhi = 0.;	    
	    if(fabs(pfmetphi-jetak8.Phi()) > TMath::Pi())
	      deltaPhi = fabs(2*TMath::Pi() - fabs(pfmetphi-jetak8.Phi()));
	    else
	      deltaPhi = fabs(pfmetphi-jetak8.Phi());
		
	    if (deltaPhi < 0.5) continue; // deltaPhi cut                                                                                                           	    

	    // pruned mass selection
	    if(prunedJetm->at(0)   < prunedMassMin)
	      goodMonoJet= true;

	    // tau2tau1 selection
	    if(boostedJettau2->at(0)/boostedJettau1->at(0) > tau2tau1)
	      goodMonoJet= true;
	  }
	}
      	
	if(not goodMonoJet) continue;
      }
      
      else if(category >= 2){
	
	if(chfrac->size() == 0 || nhfrac->size() == 0 or jetpt->size() == 0) continue; 	
	if(boostedJetpt->size() == 0) continue;
	if(boostedJetpt->at(0) < ptJetMinAK8) continue;
	if(fabs(boostedJeteta->at(0)) > 2.4) continue;

	TLorentzVector jetak4, jetak8;
	jetak4.SetPtEtaPhiM(jetpt->at(0),jeteta->at(0),jetphi->at(0),jetm->at(0));
	jetak8.SetPtEtaPhiM(boostedJetpt->at(0),boostedJeteta->at(0),boostedJetphi->at(0),boostedJetm->at(0));
	
	// match leading ak4 and leading ak8 within 0.8 cone
	if(jetak4.DeltaR(jetak8) > 0.8) continue;
	
	//after match apply jetid on leading ak4
	if (chfrac->at(0) < 0.1) continue;   // jet id                                                                                                                       
	if (nhfrac->at(0) > 0.8) continue;   // jet id                                                                                                                        
	if (jetpt->at(0)  < 100.) continue;  // jet1 > 100 GeV                                                                                                             
	if (jetpt->at(0)  < *j1pt) continue;
	if (jmdphi < 0.5) continue; // deltaPhi cut                                                                                                                        

	// jet met dphi     
	float deltaPhi = 0.;	    
	if(fabs(pfmetphi-jetak8.Phi()) > TMath::Pi())
	  deltaPhi = fabs(2*TMath::Pi() - fabs(pfmetphi-jetak8.Phi()));
	else
	  deltaPhi = fabs(pfmetphi-jetak8.Phi());
	
	if (deltaPhi < 0.5) continue; // deltaPhi cut                                                                                                           	    
	

	// no overlap between b-jet and v-jet
	if (sample == 7 || sample == 8){ 
	  int nbjets = 0;
	  for(size_t ijet = 0 ; ijet < jetbtag->size(); ijet++){
	    jetak4.SetPtEtaPhiM(jetpt->at(ijet),jeteta->at(ijet),jetphi->at(ijet),jetm->at(ijet));
	    if(jetak4.DeltaR(jetak8) < 0.8) continue;
	    if(jetbtag->at(ijet) > 0.89){
	      nbjets++;
	    }
	  }
	  if(nbjets < 1) continue;
	}

	// category 2 means HP mono-V
	if(category == 2 and (prunedJetm->at(0) > 65 and prunedJetm->at(0) < 105) and boostedJettau2->at(0)/boostedJettau1->at(0) < tau2tau1)
	  goodMonoV   = true;
	// category 3 means LP mono-V
	else if(category == 3 and (prunedJetm->at(0) > 65 and prunedJetm->at(0) < 105) and 
		(boostedJettau2->at(0)/boostedJettau1->at(0) > tau2tau1 and boostedJettau2->at(0)/boostedJettau1->at(0) < 0.75))
	  goodMonoV   = true;
	// apply only pruned mass cut in a loose region --> useful for ttbar
	else if(category == 4 and (prunedJetm->at(0) > 40 and prunedJetm->at(0) < 200))
	  goodMonoV   = true;
	// apply only n-subjettiness
	else if(category == 5 and boostedJettau2->at(0)/boostedJettau1->at(0) < tau2tau1)
	  goodMonoV   = true;
	// apply only inverted n-subjettiness
	else if(category == 6 and boostedJettau2->at(0)/boostedJettau1->at(0) > tau2tau1)
	  goodMonoV   = true;
	  	
	if(not goodMonoV) continue;	
      }
    }
               
    // fill 1D histogram
    double fillvar = 0;
    
    // b-tag weight
    double btagw = *wgtbtag;
    if(*wgtbtag > 2 || *wgtbtag < 0)
      btagw = 1;

    // fill the histograms
    for(auto hist : hist1D){

      TString name(hist->GetName());      
      if(name.Contains("met"))
	fillvar = pfmet;      
      if(name.Contains("nvtx"))
	fillvar = *nvtx;
      if(name.Contains("chfrac"))
	fillvar = chfrac->at(0);
      if(name.Contains("nhfrac"))
	fillvar = nhfrac->at(0);
      else if(name.Contains("jetPt"))
	fillvar = jetpt->at(0);
      else if(name.Contains("boostedJetPt")){
	if(boostedJetpt->size() > 0)
	  fillvar = boostedJetpt->at(0);
	else
	  fillvar = 0.;
      }      
      else if(name.Contains("mT")){
	float deltaPhi = fabs(jetphi->at(0)-pfmetphi);
	if(deltaPhi > TMath::Pi())
	  deltaPhi = fabs(2*TMath::Pi() - deltaPhi);
	fillvar = sqrt(2*jetpt->at(0)*pfmet*(1-cos(deltaPhi)));
      }    
      else if(name.Contains("njet"))
	  fillvar = *njets;      
      else if(name.Contains("nbjet"))
	  fillvar = *nbjets;
      else if(name.Contains("bosonPt"))
	fillvar = bosonPt;
      else if(name.Contains("QGL_1")){
	if(jetpt->at(0) < 175.)
	  fillvar = jetQGL->at(0);
	else
	  fillvar = -1.;
      }
      else if(name.Contains("QGL_2")){
	if(jetpt->at(0) > 175. and jetpt->at(0) < ptJetMinAK8)
	  fillvar = jetQGL->at(0);
	else
	  fillvar = -1.;
      }
      else if(name.Contains("QGL_3")){
	if(jetpt->at(0) > ptJetMinAK8)
	  fillvar = jetQGL->at(0);
	else
	  fillvar = -1.;
      }
      else if(name.Contains("QGL")){
	fillvar = jetQGL->at(0);
      }
      else if(name.Contains("QGL_AK8")){
	if(boostedJetpt->size() > 0)
	  fillvar = boostedJetQGL->at(0);
	else
	  fillvar = -1.;
      }

      else if(name.Contains("mpruned")){
	if( prunedJetm->size() > 0 and boostedJetpt->at(0) > ptJetMinAK8 )
	  fillvar = prunedJetm->at(0);	
	else fillvar = 0.;
      }
      else if(name.Contains("ht"))
	fillvar = *ht;      
      else if(name.Contains("tau2tau1")){
	if( boostedJettau1->size() > 0 and boostedJettau2->size() > 0 and boostedJetpt->at(0) > ptJetMinAK8 )
	  fillvar = boostedJettau2->at(0)/boostedJettau1->at(0);	
	else fillvar = 0.;
      }

      // overflow bin
      if (fillvar >= hist->GetBinLowEdge(hist->GetNbinsX())+hist->GetBinWidth(hist->GetNbinsX())) 
	fillvar = hist->GetXaxis()->GetBinCenter(hist->GetNbinsX());
      
      // total event weight
      double evtwgt  = 1.0;
      Double_t puwgt = 0.;
      if (isMC and not reweightNVTX) 
	evtwgt = (*xsec)*(scale)*(lumi)*(*wgt)*(*wgtpileup)*(btagw)*sfwgt*rwgt*kwgt/(*wgtsum); //(xsec, scale, lumi, wgt, pileup, sf, rw, kw, wgtsum)
      else if (isMC and reweightNVTX){
	if (*nvtx <= 35) 
	  puwgt = puhist->GetBinContent(*nvtx);
	evtwgt = (*xsec)*(scale)*(lumi)*(*wgt)*(puwgt)*(btagw)*sfwgt*rwgt*kwgt/(*wgtsum);
      }
      if (!isMC && sample == 6) 
	evtwgt = sfwgt;

      hist->Fill(fillvar, evtwgt);
    }

    //fill 2D histo
    double fillvarX = 0;
    double fillvarY = 0;

    for(auto hist: hist2D){
      TString name(hist->GetName());

      if(name.Contains("met_jetPt")){ 
	fillvarX = pfmet;
	fillvarY = jetpt->at(0);
      }
      else if(name.Contains("met_bosonPt")){
	fillvarX = pfmet;
	fillvarY = bosonPt;
      }
      else if(name.Contains("met_mT")){	
	fillvarX = pfmet;
	float deltaPhi = fabs(jetphi->at(0)-pfmetphi);
	if(deltaPhi > TMath::Pi())
	  deltaPhi = 2*TMath::Pi() - deltaPhi;
	fillvarY = sqrt(2*jetpt->at(0)*pfmet*(1-cos(deltaPhi)));
      }    
      // overflow bin
      if (fillvarX >= hist->GetXaxis()->GetBinLowEdge(hist->GetNbinsX())+hist->GetXaxis()->GetBinWidth(hist->GetNbinsX())) 
	fillvarX = hist->GetXaxis()->GetBinCenter(hist->GetNbinsX());
      if (fillvarY >= hist->GetYaxis()->GetBinLowEdge(hist->GetNbinsY())+hist->GetYaxis()->GetBinWidth(hist->GetNbinsY())) 
	fillvarY = hist->GetYaxis()->GetBinCenter(hist->GetNbinsY());

      // total event weight
      double evtwgt  = 1.0;
      Double_t puwgt = 0.;

      if (isMC and not reweightNVTX)
	evtwgt = (*xsec)*(scale)*(lumi)*(*wgt)*(*wgtpileup)*(btagw)*sfwgt*rwgt*kwgt/(*wgtsum); //(xsec, scale, lumi, wgt, pileup, sf, rw, kw, wgtsum)      
      else if (isMC and reweightNVTX){
	if (*nvtx <= 35) 
	  puwgt = puhist->GetBinContent(*nvtx);
	evtwgt = (*xsec)*(scale)*(lumi)*(*wgt)*(puwgt)*(btagw)*sfwgt*rwgt*kwgt/(*wgtsum);
      }
      if (!isMC && sample == 6) 
	evtwgt = sfwgt;
      
      hist->Fill(fillvarX,fillvarY,evtwgt);      
      
    }
  }

  sffile  ->Close();
  psffile ->Close();
  trefile ->Close();
}
#endif

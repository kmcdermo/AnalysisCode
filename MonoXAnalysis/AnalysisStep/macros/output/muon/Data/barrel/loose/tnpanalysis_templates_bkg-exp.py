import FWCore.ParameterSet.Config as cms

process = cms.Process("TagProbe")
process.source = cms.Source("EmptySource")
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.destinations = ['cout', 'cerr']
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

isMC     = False
isMu     = True
isBarrel = True
idtype   = "loose"

TemplateDir = ""

if isMu :
    if isMC :
        InputFileName = "../input/2015D/mcDYLL/tnptree.root" 
        InputDirName  = "muontnptree"
    else :
        InputFileName = "../input/2015D/singleMu/tnptree.root"
        InputDirName  = "muontnptree"
        if isBarrel :
            TemplateDir = "output/muon/Data/barrel/"+idtype+"/"
        else :
            TemplateDir = "output/muon/Data/endcap/"+idtype+"/"
else :
    if isMC :
        InputFileName = "../input/2015D/mcDYLL/tnptree.root"
        InputDirName  = "electrontnptree"
    else : 
        InputFileName = "../input/2015D/singleEl/tnptree.root"
        InputDirName  = "electrontnptree"
        if isBarrel :
            TemplateDir = "output/electron/Data/barrel/"+idtype+"/"
        else :
            TemplateDir = "output/electron/Data/endcap/"+idtype+"/"

if isMC : 
    OutputFilePrefix = "efficiency-mc"
else :
    OutputFilePrefix = "efficiency-data_bkg-exp"

PDFName = "pdfSignalPlusBackground"

EfficiencyBins = cms.PSet(
    pt = cms.vdouble( 10., 20., 30., 40., 50., 70., 100., 1000. ),
    abseta = cms.vdouble( 0.0, 1.2 ),
)

EfficiencyBinningSpecification = cms.PSet(
    UnbinnedVariables = cms.vstring("mass"),
    BinnedVariables = cms.PSet(
        EfficiencyBins,
    ),
    BinToPDFmap = cms.vstring([
        "pdfSignalPlusBackground", 
        "*pt_bin0*", "pdfSignalPlusBackgroundb0",
        "*pt_bin1*", "pdfSignalPlusBackgroundb1",
        "*pt_bin2*", "pdfSignalPlusBackgroundb2",
        "*pt_bin3*", "pdfSignalPlusBackgroundb3",
        "*pt_bin4*", "pdfSignalPlusBackgroundb4",
        "*pt_bin5*", "pdfSignalPlusBackgroundb5",
        "*pt_bin6*", "pdfSignalPlusBackgroundb6",
    ])  
)

IDModule = cms.PSet(
    Id = cms.PSet(
        EfficiencyBinningSpecification,
        EfficiencyCategoryAndState = cms.vstring(idtype+"id","pass"), 
    )
)

process.leptonIdTnP = cms.EDAnalyzer("TagProbeFitTreeAnalyzer",
    InputFileNames = cms.vstring(InputFileName),
    InputDirectoryName = cms.string(InputDirName),
    InputTreeName = cms.string("fitter_tree"),
    OutputFileName = cms.string(TemplateDir+OutputFilePrefix+".root"),
    NumCPU = cms.uint32(1),
    SaveWorkspace = cms.bool(True),
    floatShapeParameters = cms.bool(True),
    binsForMassPlots = cms.uint32(25),
    Variables = cms.PSet(
        mass = cms.vstring("Tag-Probe Mass", "60.0", "120.0", "GeV/c^{2}"),
        pt = cms.vstring("Probe p_{T}", "0", "1000", "GeV/c"), 
        abseta = cms.vstring("Probe #eta", "-2.5", "2.5", ""),  
    ),

    Categories = cms.PSet(
        mcTrue = cms.vstring("MC Truth", "dummy[true=1,false=0]"),
        looseid  = cms.vstring("Loose ID", "dummy[pass=1,fail=0]"), 
    ),
    PDFs = cms.PSet( 
        pdfSignalPlusBackground = cms.vstring(
            "BreitWigner::signalPass(mass, mP[91, 89, 93], sP[0.01, 0.0, 0.05])",
            "BreitWigner::signalFail(mass, mF[91, 89, 93], sF[0.01, 0.0, 0.05])", 
            "Exponential::backgroundPass(mass, cP[0.0, -1.0, 0.0])",
            "Exponential::backgroundFail(mass, cF[0.0, -1.0, 0.0])",
            "efficiency[0.8,0,1]",
         ),
         pdfSignalPlusBackgroundb0 = cms.vstring(
             "#import "+TemplateDir+"templates0.root:w:signalPassMC",
             "#import "+TemplateDir+"templates0.root:w:signalFailMC",
             "Gaussian::signalPassSmear(mass, mP[0.15, 0.0, 1.0], sp[0.1, 0.0, 1.0])",
             "Gaussian::signalFailSmear(mass, mF[0.15, 0.0, 1.0], sF[0.1, 0.0, 1.0])",
             "FCONV::signalPass(mass, signalPassMC, signalPassSmear)",
             "FCONV::signalFail(mass, signalFailMC, signalFailSmear)",
             "Exponential::backgroundPass(mass, cP[-0.05, -2.0, 2.0])",
             "Exponential::backgroundFail(mass, cF[-0.05, -2.0, 2.0])",
             "efficiency[0.8,0,1]"
          ),
         pdfSignalPlusBackgroundb1 = cms.vstring(
             "#import "+TemplateDir+"templates1.root:w:signalPassMC",
             "#import "+TemplateDir+"templates1.root:w:signalFailMC",
             "Gaussian::signalPassSmear(mass, mP[0.15, 0.0, 0.5], sp[0.1, 0.0, 1.0])",
             "Gaussian::signalFailSmear(mass, mF[0.15, 0.0, 0.5], sF[0.1, 0.0, 1.0])",
             "FCONV::signalPass(mass, signalPassMC, signalPassSmear)",
             "FCONV::signalFail(mass, signalFailMC, signalFailSmear)",
             "Exponential::backgroundPass(mass, cP[-1.0, -2.0, 2.0])",
             "Exponential::backgroundFail(mass, cF[-1.0, -2.0, 2.0])",
             "efficiency[0.8,0,1]"
          ),
         pdfSignalPlusBackgroundb2 = cms.vstring(
             "#import "+TemplateDir+"templates2.root:w:signalPassMC",
             "#import "+TemplateDir+"templates2.root:w:signalFailMC",
             "Gaussian::signalPassSmear(mass, mP[0.15, 0.0, 0.5], sp[0.5, 0.0, 1.5])",
             "Gaussian::signalFailSmear(mass, mF[0.15, 0.0, 0.5], sF[0.5, 0.0, 1.5])",
             "FCONV::signalPass(mass, signalPassMC, signalPassSmear)",
             "FCONV::signalFail(mass, signalFailMC, signalFailSmear)",
             "Exponential::backgroundPass(mass, cP[-1.0, -2.0, 2.0])",
             "Exponential::backgroundFail(mass, cF[-1.0, -2.0, 2.0])",
             "efficiency[0.8,0,1]"
          ),
         pdfSignalPlusBackgroundb3 = cms.vstring(
             "#import "+TemplateDir+"templates3.root:w:signalPassMC",
             "#import "+TemplateDir+"templates3.root:w:signalFailMC",
             "Gaussian::signalPassSmear(mass, mP[0.18, 0., 1.], sp[0.5, 0.0, 1.5])",
             "Gaussian::signalFailSmear(mass, mF[0.15, 0., 1.], sF[0.5, 0.0, 1.5])",
             "FCONV::signalPass(mass, signalPassMC, signalPassSmear)",
             "FCONV::signalFail(mass, signalFailMC, signalFailSmear)",
             "Exponential::backgroundPass(mass, cP[ .01, -1.0, 1.0])",
             "Exponential::backgroundFail(mass, cF[-.01, -1.0, 1.0])",
             "efficiency[0.8,0,1]"
          ),
         pdfSignalPlusBackgroundb4 = cms.vstring(
             "#import "+TemplateDir+"templates4.root:w:signalPassMC",
             "#import "+TemplateDir+"templates4.root:w:signalFailMC",
             "Gaussian::signalPassSmear(mass, mP[0.15, 0.0, 0.5], sp[1.0, 0.0, 2.0])",
             "Gaussian::signalFailSmear(mass, mF[0.15, 0.0, 0.5], sF[1.0, 0.0, 2.0])",
             "FCONV::signalPass(mass, signalPassMC, signalPassSmear)",
             "FCONV::signalFail(mass, signalFailMC, signalFailSmear)",
             "Exponential::backgroundPass(mass, cP[0.1, -1.0, 1.0])",
             "Exponential::backgroundFail(mass, cF[0.1, -1.0, 1.0])",
             "efficiency[0.8,0,1]"
          ),
         pdfSignalPlusBackgroundb5 = cms.vstring(
             "#import "+TemplateDir+"templates5.root:w:signalPassMC",
             "#import "+TemplateDir+"templates5.root:w:signalFailMC",
             "Gaussian::signalPassSmear(mass, mP[0.15, 0.0, 0.5], sp[1.0, 0.0, 3.0])",
             "Gaussian::signalFailSmear(mass, mF[1.0, 0.0, 2.0], sF[1.5, 0.0, 3.0])",
             "FCONV::signalPass(mass, signalPassMC, signalPassSmear)",
             "FCONV::signalFail(mass, signalFailMC, signalFailSmear)",
             "Exponential::backgroundPass(mass, cP[.015, -2.0, 2.0])",
             "Exponential::backgroundFail(mass, cF[.015, -2.0, 2.0])",
             "efficiency[0.8,0,1]"
          ),
         pdfSignalPlusBackgroundb6 = cms.vstring(
             "#import "+TemplateDir+"templates5.root:w:signalPassMC",
             "#import "+TemplateDir+"templates5.root:w:signalFailMC",
             "Gaussian::signalPassSmear(mass, mP[0.15, 0.0, 0.5], sp[1.0, 0.0, 3.0])",
             "Gaussian::signalFailSmear(mass, mF[1.0, 0.0, 2.0], sF[2.0, 0.0, 3.0])",
             "FCONV::signalPass(mass, signalPassMC, signalPassSmear)",
             "FCONV::signalFail(mass, signalFailMC, signalFailSmear)",
             "Exponential::backgroundPass(mass, cP[.015, -2.0, 2.0])",
             "Exponential::backgroundFail(mass, cF[.015, -2.0, 2.0])",
             "efficiency[0.8,0,1]"
          ),
        ),

     Efficiencies = cms.PSet(
        IDModule
   )
)

process.fit = cms.Path(process.leptonIdTnP)

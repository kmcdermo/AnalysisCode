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
    OutputFilePrefix = "efficiency-data"

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
            "RooCMSShape::backgroundPass(mass, alphaPass[80.,60.,100.], betaPass[0.105, 0.,1.0], gammaPass[0.033, 0, 0.1], peakPass[91.2, 90, 92])",
            "RooCMSShape::backgroundFail(mass, alphaFail[80.,60.,100.], betaFail[0.105, 0.,1.0], gammaFail[0.033, 0, 0.1], peakFail[91.2, 90, 92])",
#             "Exponential::backgroundPass(mass, cP[0.0, -1.0, 0.0])",
#             "Exponential::backgroundFail(mass, cF[0.0, -1.0, 0.0])",
            "efficiency[0.8,0,1]",
         ),
         pdfSignalPlusBackgroundb0 = cms.vstring(
             "#import "+TemplateDir+"templates0.root:w:signalPassMC",
             "#import "+TemplateDir+"templates0.root:w:signalFailMC",
             "Gaussian::signalPassSmear(mass, mP[0.17, -0.5, 0.5], sp[0.45, 0.0, 1.0])",
             "Gaussian::signalFailSmear(mass, mF[0.17, -0.5, 0.5], sF[0.45, 0.0, 1.0])",
             "FCONV::signalPass(mass, signalPassMC, signalPassSmear)",
             "FCONV::signalFail(mass, signalFailMC, signalFailSmear)",
             "RooCMSShape::backgroundPass(mass, alphaPass[102.,100.,110.], betaPass[-0.005, -0.05, 0.05], gammaPass[0.05, 0, 0.1], peakPass[91.2, 90, 92])",
             "RooCMSShape::backgroundFail(mass, alphaFail[128.,122.,132.], betaFail[-0.033, -0.08, 0.08], gammaFail[0.05, 0, 0.1], peakFail[91.2, 90, 92])",
             "efficiency[0.8,0,1]"
        ),
          pdfSignalPlusBackgroundb1 = cms.vstring(
             "#import "+TemplateDir+"templates1.root:w:signalPassMC",
             "#import "+TemplateDir+"templates1.root:w:signalFailMC",
             "Gaussian::signalPassSmear(mass, mP[0.17, 0, 0.5], sp[0.5, 0.0, 2.0])",
             "Gaussian::signalFailSmear(mass, mF[0.17, 0, 0.5], sF[0.5, 0.0, 2.0])",
             "FCONV::signalPass(mass, signalPassMC, signalPassSmear)",
             "FCONV::signalFail(mass, signalFailMC, signalFailSmear)",
             "RooCMSShape::backgroundPass(mass, alphaPass[110.,100.,150.], betaPass[0.01, -0.5, 0.1], gammaPass[0.090, 0, 0.1], peakPass[91.2, 90, 92])",
             "RooCMSShape::backgroundFail(mass, alphaFail[120.,100.,150.], betaFail[-0.08, -0.5, 1.0], gammaFail[0.03, 0, 0.1], peakFail[91.2, 90, 92])",
             "efficiency[0.8,0,1]"
        ),
         pdfSignalPlusBackgroundb2 = cms.vstring(
             "#import "+TemplateDir+"templates2.root:w:signalPassMC",
             "#import "+TemplateDir+"templates2.root:w:signalFailMC",
             "Gaussian::signalPassSmear(mass, mP[0., -2, 2.], sp[0.5, 0.0, 2.0])",
             "Gaussian::signalFailSmear(mass, mF[0., -2, 2.], sF[0.5, 0.0, 2.0])",
             "FCONV::signalPass(mass, signalPassMC, signalPassSmear)",
             "FCONV::signalFail(mass, signalFailMC, signalFailSmear)",
             "RooCMSShape::backgroundPass(mass, alphaPass[90., 80., 100.], betaPass[-0.01, -1.0, 1.0], gammaPass[0.064, -0.1, 0.1], peakPass[91.2, 90, 92])",
             "RooCMSShape::backgroundFail(mass, alphaFail[112.,100.,120.], betaFail[-0.03, -0.5, 0.5], gammaFail[-0.06, -0.1, 0.1], peakFail[91.2, 90, 92])",
             "efficiency[0.8,0,1]"
        ),
         pdfSignalPlusBackgroundb3 = cms.vstring(
             "#import "+TemplateDir+"templates3.root:w:signalPassMC",
             "#import "+TemplateDir+"templates3.root:w:signalFailMC",
             "Gaussian::signalPassSmear(mass, mP[0.15, -1, 1.], sp[0.5, 0.0, 1.0])",
             "Gaussian::signalFailSmear(mass, mF[0.15, -1, 1.], sF[0.5, 0.0, 1.0])",
             "FCONV::signalPass(mass, signalPassMC, signalPassSmear)",
             "FCONV::signalFail(mass, signalFailMC, signalFailSmear)",
             "RooCMSShape::backgroundPass(mass, alphaPass[100.,80.,120.], betaPass[0.03, -0.1, 1.0], gammaPass[0.02, 0, 0.1], peakPass[91.2, 90, 92])",
             "RooCMSShape::backgroundFail(mass, alphaFail[100.,80.,120.], betaFail[0.03, -0.1, 1.0], gammaFail[0.02, 0, 0.1], peakFail[91.2, 90, 92])",
             "efficiency[0.8,0,1]"
         ),
         pdfSignalPlusBackgroundb4 = cms.vstring(
             "#import "+TemplateDir+"templates4.root:w:signalPassMC",
             "#import "+TemplateDir+"templates4.root:w:signalFailMC",
             "Gaussian::signalPassSmear(mass, mP[0.15, -1, 1.], sp[0.5, 0.0, 1.0])",
             "Gaussian::signalFailSmear(mass, mF[0.15, -1, 1.], sF[0.5, 0.0, 1.0])",
             "FCONV::signalPass(mass, signalPassMC, signalPassSmear)",
             "FCONV::signalFail(mass, signalFailMC, signalFailSmear)",
             "RooCMSShape::backgroundPass(mass, alphaPass[110.,100.,120.], betaPass[0.032, 0.0, 0.05], gammaPass[0.023,  0, 0.1], peakPass[91.2, 90, 92])",
             "RooCMSShape::backgroundFail(mass, alphaFail[100.,90., 120.], betaFail[0.024, 0.0, 0.05], gammaFail[0.033,  0, 0.1], peakFail[91.2, 90, 92])",
             "efficiency[0.8,0,1]"
        ),
         pdfSignalPlusBackgroundb5 = cms.vstring(
             "#import "+TemplateDir+"templates5.root:w:signalPassMC",
             "#import "+TemplateDir+"templates5.root:w:signalFailMC",
             "Gaussian::signalPassSmear(mass, mP[0.15, -1, 1.], sp[0.5, 0.0, 1.0])",
             "Gaussian::signalFailSmear(mass, mF[0.15, -1, 1.], sF[2.0, 0.0, 4.0])",
             "FCONV::signalPass(mass, signalPassMC, signalPassSmear)",
             "FCONV::signalFail(mass, signalFailMC, signalFailSmear)",
             "RooCMSShape::backgroundPass(mass, alphaPass[100.,80.,150.], betaPass[0.01, -1.0, 1.0], gammaPass[0.1, 0, 0.3], peakPass[91.2, 90, 92])",
             "RooCMSShape::backgroundFail(mass, alphaFail[100, 50., 150.], betaFail[0.01, -1.0, 1.0], gammaFail[0.01, 0, 0.1], peakFail[91.2, 90, 92])",
             "efficiency[0.8,0,1]"
        ),
         pdfSignalPlusBackgroundb6 = cms.vstring(
             "#import "+TemplateDir+"templates5.root:w:signalPassMC",
             "#import "+TemplateDir+"templates5.root:w:signalFailMC",
             "Gaussian::signalPassSmear(mass, mP[0.15, -1, 1.], sp[0.5, 0.0, 1.0])",
             "Gaussian::signalFailSmear(mass, mF[0.15, -1, 1.], sF[2.0, 0.0, 4.0])",
             "FCONV::signalPass(mass, signalPassMC, signalPassSmear)",
             "FCONV::signalFail(mass, signalFailMC, signalFailSmear)",
             "RooCMSShape::backgroundPass(mass, alphaPass[100.,80.,150.], betaPass[0.01, -1.0, 1.0], gammaPass[0.1, 0, 0.3], peakPass[91.2, 90, 92])",
             "RooCMSShape::backgroundFail(mass, alphaFail[100, 50., 150.], betaFail[0.01, -1.0, 1.0], gammaFail[0.01, 0, 0.1], peakFail[91.2, 90, 92])",
             "efficiency[0.8,0,1]"
        ),







        ),

     Efficiencies = cms.PSet(
        IDModule
   )
)

process.fit = cms.Path(process.leptonIdTnP)

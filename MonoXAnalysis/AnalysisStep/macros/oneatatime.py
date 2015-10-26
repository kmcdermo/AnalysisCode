import FWCore.ParameterSet.Config as cms

process = cms.Process("TagProbe")
process.source = cms.Source("EmptySource")
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.destinations = ['cout', 'cerr']
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

isMC     = True
isMu     = False
isBarrel = True
idtype   = "veto"

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


OutputFilePrefix = "test"

PDFName = "pdfSignalPlusBackground"

EfficiencyBins = cms.PSet(
    pt = cms.vdouble( 50. , 70. ),
    abseta = cms.vdouble( 0.0, 1.4442 )
#    abseta = cms.vdouble( 1.566, 2.5 )
)
EfficiencyBinningSpecification = cms.PSet(
    UnbinnedVariables = cms.vstring("mass"),
    BinnedVariables = cms.PSet(
        EfficiencyBins,
    ),
    BinToPDFmap = cms.vstring([
        "pdfSignalPlusBackground", 
        "*pt_bin0*", "pdfSignalPlusBackgroundb0",
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
    OutputFileName = cms.string(OutputFilePrefix+".root"),
    NumCPU = cms.uint32(1),
    SaveWorkspace = cms.bool(True),
    floatShapeParameters = cms.bool(True),
 
    binnedFit  = cms.bool(True),
    binsForFit = cms.uint32(100),

#    binsForMassPlots = cms.uint32(25),
    Variables = cms.PSet(
        mass = cms.vstring("Tag-Probe Mass", "60.0", "120.0", "GeV/c^{2}"),
        pt = cms.vstring("Probe p_{T}", "0", "1000", "GeV/c"), 
        abseta = cms.vstring("Probe #eta", "-2.5", "2.5", ""),  
    ),

    Categories = cms.PSet(
        mcTrue = cms.vstring("MC Truth", "dummy[true=1,false=0]"),
        vetoid  = cms.vstring("Veto ID", "dummy[pass=1,fail=0]"), 
#        tightid  = cms.vstring("Tight ID", "dummy[pass=1,fail=0]"), 
    ),
    PDFs = cms.PSet( 
        pdfSignalPlusBackground = cms.vstring(
            "RooCBShape::signalPass(mass,mP[90.0,85.000,95.000],sigmaP[0.956,0.00,5.000],alphaP[0.999, 0.0,20.0],nP[1.405,0.000,50.00])",
            "RooCBShape::signalFail(mass,meanF[90.0,85.000,95.000],sigmaF[3.331,0.00,5.000],alphaF[1.586, 0.0,20.0],nF[0.464,0.000,20.00])",
            "Exponential::backgroundPass(mass, cP[0.0, -1.0, 1.0])",
            "Exponential::backgroundFail(mass, cF[0.0, -1.0, 1.0])",

#            "Chebychev::backgroundPass(mass, {c1P[0.0])",
#            "Chebychev::backgroundFail(mass, {c1F[0.0])",
            "efficiency[0.8,0,1]"
         ),
         pdfSignalPlusBackgroundb0 = cms.vstring(
#            "RooCBExGaussShape::signalPass(mass,meanP[91,90,92],sigmaP[0.956,0.00,5.000],alphaP[0.999, 0.0,50.0],nP[1.405,0.000,50.000],sigmaP_2[1.000,0.500,15.00])",
#            "RooCBExGaussShape::signalFail(mass,meanF[91,90,92],sigmaF[3.331,0.00,5.000],alphaF[1.586, 0.0,50.0],nF[0.464,0.000,20.00],sigmaF_2[1.675,0.500,2.000])",
            "RooCBShape::signalPass(mass,mP[91.0,90.000,92.000],sigmaP[0.956,0.00,5.000],alphaP[0.999, -20.0,20.0],nP[1.405,-50.000,50.00])",
            "RooCBShape::signalFail(mass,meanF[91.0,90.000,92.000],sigmaF[3.331,0.00,5.000],alphaF[1.586, -20.0,20.0],nF[0.464,-50.000,20.00])",
            "Exponential::backgroundPass(mass, cP[-10e6])",
            "Exponential::backgroundFail(mass, cF[-10e6])",
#            "Chebychev::backgroundPass(mass, {c1P[0.0]})",
#            "Chebychev::backgroundFail(mass, {c1F[0.0]})",
            "efficiency[0.8,0,1]"
         ),

),
     Efficiencies = cms.PSet(
        IDModule
   )
)

process.fit = cms.Path(process.leptonIdTnP)

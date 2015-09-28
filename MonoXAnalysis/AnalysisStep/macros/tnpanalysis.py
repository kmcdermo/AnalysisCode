import FWCore.ParameterSet.Config as cms

process = cms.Process("TNP")
process.source = cms.Source("EmptySource")
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.destinations = ['cout', 'cerr']
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

isMC = False
isMu = True

if isMu :
    if isMC :
        InputFileName = "../input/mcDYLL/tnptree.root" 
        InputDirName  = "muontnptree"
    else :
        InputFileName = "../input/25ns/singleMu/tnptree.root"
        InputDirName  = "muontnptree"
else :
    if isMC :
        InputFileName = "../input/mcDYLL/tnptree.root"
        InputDirName  = "electrontnptree"
    else : 
        InputFileName = "../input/singleEl/tnptree.root"
        InputDirName  = "electrontnptree"

if isMC : 
    OutputFilePrefix = "efficiency-mc"
else :
    OutputFilePrefix = "efficiency-data"

PDFName = "pdfSignalPlusBackground"

EfficiencyBins = cms.PSet(
#    pt = cms.vdouble( 10., 20., 30., 40., 50., 70., 100., 200., 500., 1000.),
    pt = cms.vdouble( 10., 20., 30., 40., 50., 70., 100., 1000. ),
#    pt = cms.vdouble( 100., 1000. ),
    abseta = cms.vdouble( 0.0, 1.2 )
#    abseta = cms.vdouble( 1.2, 2.4 )
)
EfficiencyBinningSpecification = cms.PSet(
    UnbinnedVariables = cms.vstring("mass"),
    BinnedVariables = cms.PSet(
        EfficiencyBins,
    ),
    BinToPDFmap = cms.vstring([
        "pdfSignalPlusBackground", 
        #"*pt_bin_highpT*", "pdfSignalPlusBackground_highpT",
        "*pt_bin0*", "pdfSignalPlusBackgroundb0",
        "*pt_bin1*", "pdfSignalPlusBackgroundb1",
        "*pt_bin2*", "pdfSignalPlusBackgroundb2",
        "*pt_bin3*", "pdfSignalPlusBackgroundb3",
        "*pt_bin4*", "pdfSignalPlusBackgroundb4",
        "*pt_bin5*", "pdfSignalPlusBackgroundb5",
        "*pt_bin6*", "pdfSignalPlusBackgroundb6",
#        "*pt_bin7*", "pdfSignalPlusBackgroundb7",
#        "*pt_bin8*", "pdfSignalPlusBackgroundb8",
    ])  
)

IDModule = cms.PSet(
    Id = cms.PSet(
        EfficiencyBinningSpecification,
        EfficiencyCategoryAndState = cms.vstring("looseid","pass"),
#        EfficiencyCategoryAndState = cms.vstring("mediumid","pass"),
#        EfficiencyCategoryAndState = cms.vstring("tightid","pass"),
#        EfficiencyCategoryAndState = cms.vstring("pfid","pass"),
#        EfficiencyCategoryAndState = cms.vstring("vetoid","pass"),
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
    binsForMassPlots = cms.uint32(25),
    Variables = cms.PSet(
        mass = cms.vstring("Tag-Probe Mass", "65.0", "115.0", "GeV/c^{2}"),
        pt = cms.vstring("Probe p_{T}", "0", "1000", "GeV/c"), 
        abseta = cms.vstring("Probe #eta", "-2.4", "2.4", ""),  
    ),

    Categories = cms.PSet(
        mcTrue = cms.vstring("MC Truth", "dummy[true=1,false=0]"),
        looseid  = cms.vstring("Loose ID", "dummy[pass=1,fail=0]"), 
#        mediumid = cms.vstring("Medium ID", "dummy[pass=1,fail=0]"), 
#        tightid  = cms.vstring("Tight ID", "dummy[pass=1,fail=0]"), 
#        vetoid   = cms.vstring("Veto ID", "dummy[pass=1,fail=0]"), 
#        pfid = cms.vstring("PF ID", "dummy[pass=1,fail=0]"), 
    ),
    PDFs = cms.PSet(
        pdfSignalPlusBackground = cms.vstring(
            "BreitWigner::signalPass(mass, mP[91, 89, 93], sP[3.0, 0.0, 7.0])",
            "BreitWigner::signalFail(mass, mF[91, 89, 93], sF[3.0, 0.0, 7.0])",
            "Exponential::backgroundPass(mass, cP[0.0, -1.0, 0.0])",
            "Exponential::backgroundFail(mass, cF[0.0, -1.0, 0.0])",
            "efficiency[0.8,0,1]"
        ),
        # pdfSignalPlusBackground_highpT = cms.vstring(
        #     "#import templates_highpT.root:w:signalPassMC",
        #     "#import templates_highpT.root:w:signalFailMC",
        #     "Gaussian::signalPassSmear(mass, mP[0., -1, 1.], sP[0.01, 0.0, 0.5])",
        #     "Gaussian::signalFailSmear(mass, mF[0., -1, 1.], sF[0.01, 0.0, 0.5])",
        #     "FCONV::signalPass(mass, signalPassMC, signalPassSmear)",
        #     "FCONV::signalFail(mass, signalFailMC, signalFailSmear)",
        #     "Exponential::backgroundPass(mass, cP[0.0, -1.0, 0.0])",
        #     "Exponential::backgroundFail(mass, cF[0.0, -1.0, 0.0])",
        #     "efficiency[0.8,0,1]"
        # ),
        pdfSignalPlusBackgroundb0 = cms.vstring(
            "#import templates0.root:w:signalPassMC",
            "#import templates0.root:w:signalFailMC",
            "Gaussian::signalPassSmear(mass, mP[0., -1, 1.], sP[0.01, 0.0, 0.5])",
            "Gaussian::signalFailSmear(mass, mF[0., -1, 1.], sF[0.01, 0.0, 0.5])",
            "FCONV::signalPass(mass, signalPassMC, signalPassSmear)",
            "FCONV::signalFail(mass, signalFailMC, signalFailSmear)",
            "Exponential::backgroundPass(mass, cP[0.0, -1.0, 0.0])",
            "Exponential::backgroundFail(mass, cF[0.0, -1.0, 0.0])",
            "efficiency[0.8,0,1]"
        ),
        pdfSignalPlusBackgroundb1 = cms.vstring(
            "#import templates1.root:w:signalPassMC",
            "#import templates1.root:w:signalFailMC",
            "Gaussian::signalPassSmear(mass, mP[0., -1, 1.], sP[0.01, 0.0, 0.5])",
            "Gaussian::signalFailSmear(mass, mF[0., -1, 1.], sF[0.01, 0.0, 0.5])",
            "FCONV::signalPass(mass, signalPassMC, signalPassSmear)",
            "FCONV::signalFail(mass, signalFailMC, signalFailSmear)",
            "Exponential::backgroundPass(mass, cP[0.0, -1.0, 0.0])",
            "Exponential::backgroundFail(mass, cF[0.0, -1.0, 0.0])",
            "efficiency[0.8,0,1]"
        ),
        pdfSignalPlusBackgroundb2 = cms.vstring(
            "#import templates2.root:w:signalPassMC",
            "#import templates2.root:w:signalFailMC",
            "Gaussian::signalPassSmear(mass, mP[0., -1, 1.], sP[0.01, 0.0, 0.5])",
            "Gaussian::signalFailSmear(mass, mF[0., -1, 1.], sF[0.01, 0.0, 0.5])",
            "FCONV::signalPass(mass, signalPassMC, signalPassSmear)",
            "FCONV::signalFail(mass, signalFailMC, signalFailSmear)",
            "Exponential::backgroundPass(mass, cP[0.0, -1.0, 0.0])",
            "Exponential::backgroundFail(mass, cF[0.0, -1.0, 0.0])",
            "efficiency[0.8,0,1]"
        ),
        pdfSignalPlusBackgroundb3 = cms.vstring(
            "#import templates3.root:w:signalPassMC",
            "#import templates3.root:w:signalFailMC",
            "Gaussian::signalPassSmear(mass, mP[0., -1, 1.], sP[0.01, 0.0, 0.5])",
            "Gaussian::signalFailSmear(mass, mF[0., -1, 1.], sF[0.01, 0.0, 0.5])",
            "FCONV::signalPass(mass, signalPassMC, signalPassSmear)",
            "FCONV::signalFail(mass, signalFailMC, signalFailSmear)",
            "Exponential::backgroundPass(mass, cP[0.0, -1.0, 0.0])",
            "Exponential::backgroundFail(mass, cF[0.0, -1.0, 0.0])",
            "efficiency[0.8,0,1]"
        ),
        pdfSignalPlusBackgroundb4 = cms.vstring(
            "#import templates4.root:w:signalPassMC",
            "#import templates4.root:w:signalFailMC",
            "Gaussian::signalPassSmear(mass, mP[0., -1, 1.], sP[0.01, 0.0, 0.5])",
            "Gaussian::signalFailSmear(mass, mF[0., -1, 1.], sF[0.01, 0.0, 0.5])",
            "FCONV::signalPass(mass, signalPassMC, signalPassSmear)",
            "FCONV::signalFail(mass, signalFailMC, signalFailSmear)",
            "Exponential::backgroundPass(mass, cP[0.0, -1.0, 0.0])",
            "Exponential::backgroundFail(mass, cF[0.0, -1.0, 0.0])",
            "efficiency[0.8,0,1]"
        ),
        pdfSignalPlusBackgroundb5 = cms.vstring(
            "#import templates5.root:w:signalPassMC",
            "#import templates5.root:w:signalFailMC",
            "Gaussian::signalPassSmear(mass, mP[0., -1, 1.], sP[0.01, 0.0, 0.5])",
            "Gaussian::signalFailSmear(mass, mF[0., -1, 1.], sF[0.01, 0.0, 0.5])",
            "FCONV::signalPass(mass, signalPassMC, signalPassSmear)",
            "FCONV::signalFail(mass, signalFailMC, signalFailSmear)",
            "Exponential::backgroundPass(mass, cP[0.0, -1.0, 0.0])",
            "Exponential::backgroundFail(mass, cF[0.0, -1.0, 0.0])",
            "efficiency[0.8,0,1]"
        ),
        pdfSignalPlusBackgroundb6 = cms.vstring(
            "#import templates6.root:w:signalPassMC",
            "#import templates6.root:w:signalFailMC",
            "Gaussian::signalPassSmear(mass, mP[0., -1, 1.], sP[0.01, 0.0, 0.5])",
            "Gaussian::signalFailSmear(mass, mF[0., -1, 1.], sF[0.01, 0.0, 0.5])",
            "FCONV::signalPass(mass, signalPassMC, signalPassSmear)",
            "FCONV::signalFail(mass, signalFailMC, signalFailSmear)",
            "Exponential::backgroundPass(mass, cP[0.0, -1.0, 0.0])",
            "Exponential::backgroundFail(mass, cF[0.0, -1.0, 0.0])",
            "efficiency[0.8,0,1]"
        ),
        # pdfSignalPlusBackgroundb7 = cms.vstring(
        #     "#import templates7.root:w:signalPassMC",
        #     "#import templates7.root:w:signalFailMC",
        #     "Gaussian::signalPassSmear(mass, mP[0., -1, 1.], sP[0.01, 0.0, 0.5])",
        #     "Gaussian::signalFailSmear(mass, mF[0., -1, 1.], sF[0.01, 0.0, 0.5])",
        #     "FCONV::signalPass(mass, signalPassMC, signalPassSmear)",
        #     "FCONV::signalFail(mass, signalFailMC, signalFailSmear)",
        #     "Exponential::backgroundPass(mass, cP[0.0, -1.0, 0.0])",
        #     "Exponential::backgroundFail(mass, cF[0.0, -1.0, 0.0])",
        #     "efficiency[0.8,0,1]"
        # ),
        # pdfSignalPlusBackgroundb8 = cms.vstring(
        #     "#import templates8.root:w:signalPassMC",
        #     "#import templates8.root:w:signalFailMC",
        #     "Gaussian::signalPassSmear(mass, mP[0., -1, 1.], sP[0.01, 0.0, 0.5])",
        #     "Gaussian::signalFailSmear(mass, mF[0., -1, 1.], sF[0.01, 0.0, 0.5])",
        #     "FCONV::signalPass(mass, signalPassMC, signalPassSmear)",
        #     "FCONV::signalFail(mass, signalFailMC, signalFailSmear)",
        #     "Exponential::backgroundPass(mass, cP[0.0, -1.0, 0.0])",
        #     "Exponential::backgroundFail(mass, cF[0.0, -1.0, 0.0])",
        #     "efficiency[0.8,0,1]"
        # ),
        ),

    Efficiencies = cms.PSet(
        IDModule
    )
)

process.fit = cms.Path(process.leptonIdTnP)

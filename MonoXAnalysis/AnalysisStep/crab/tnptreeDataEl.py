import FWCore.ParameterSet.Config as cms

# Define the CMSSW process
process = cms.Process("TNP")

# Load the standard set of configuration modules
process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.StandardSequences.GeometryDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

# Message Logger settings
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.destinations = ['cout', 'cerr']
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

# Set the process options -- Display summary at the end, enable unscheduled execution
process.options = cms.untracked.PSet( 
    allowUnscheduled = cms.untracked.bool(True),
    wantSummary = cms.untracked.bool(True) 
#    SkipEvent = cms.untracked.vstring('ProductNotFound')
)

# How many events to process
process.maxEvents = cms.untracked.PSet( 
    input = cms.untracked.int32(-1)
)

# Is this a simulation or real data
isMCFlag = False

# Define the input source
process.source = cms.Source("PoolSource", 
    fileNames = cms.untracked.vstring([
            '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/675/00000/D8CD44FA-9C5F-E511-8B24-02163E0134DD.root',
            #            '/store/data/Run2015C/SingleMuon/MINIAOD/PromptReco-v1/000/253/888/00000/DA473838-0941-E511-9644-02163E014405.root',
    ])
)

# Setup the service to make a ROOT TTree
process.TFileService = cms.Service("TFileService", fileName = cms.string("tnptree.root"))

# Set the global tag depending on the sample type
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
if isMCFlag:
    process.GlobalTag.globaltag = 'MCRUN2_74_V9A::All'   # for Simulation
else:
    #    process.GlobalTag.globaltag = 'GR_P_V56::All'        # for Data 50ns
    process.GlobalTag.globaltag = '74X_dataRun2_Prompt_v2'        # for Data 25ns - 2015D

# Select good primary vertices
process.goodVertices = cms.EDFilter("VertexSelector",
  src = cms.InputTag("offlineSlimmedPrimaryVertices"),
  cut = cms.string("!isFake && ndof > 4 && abs(z) <= 24 && position.Rho <= 2"),
  filter = cms.bool(True)
)

# Electron and Photon ValueMaps for identification
from PhysicsTools.SelectorUtils.tools.vid_id_tools import *
dataFormat = DataFormat.MiniAOD
switchOnVIDElectronIdProducer(process, dataFormat)

ele_id_modules = ['RecoEgamma.ElectronIdentification.Identification.cutBasedElectronID_Spring15_25ns_V1_cff']
for idmod in ele_id_modules:
    setupAllVIDIdsInModule(process,idmod,setupVIDElectronSelection)
process.egmGsfElectronIDs.physicsObjectSrc = "probeelectrons"

# Probe muons
process.probemuons = cms.EDFilter("PATMuonSelector",
    src = cms.InputTag("slimmedMuons"),
    cut = cms.string("pt > 10 && abs(eta) < 2.4 && (isTrackerMuon || isStandAloneMuon)"),
    filter = cms.bool(True)  
)

# Probe electrons
process.probeelectrons = cms.EDFilter("PATElectronSelector",
    src = cms.InputTag("slimmedElectrons"),
    cut = cms.string("pt > 10 && abs(eta) < 2.5"),
    filter = cms.bool(True)  
)

# Make the ValueMap for muon tight ID -- cannot pass it through a string selection due to the vertex argument
process.probeinfo = cms.EDProducer("LeptonTnPInfoProducer",
    muons = cms.InputTag("probemuons"),
    electrons = cms.InputTag("probeelectrons"),
    geninfo = cms.InputTag("generator"),
    vertices = cms.InputTag("goodVertices"),
    triggerobjects = cms.InputTag("selectedPatTrigger"),
    triggerResults = cms.InputTag("TriggerResults", "", "HLT"),
    loosemuisocut = cms.double(0.20),
    tightmuisocut = cms.double(0.12),
    tagmuonptcut = cms.double(30.0),
    tagmuonetacut = cms.double(2.1),
    tagmuontrigmatchdR = cms.double(0.3),
    requiremuonhlt = cms.bool(True),
    tagmuontriggers = cms.vstring([
        "HLT_IsoMu20_eta2p1_v*", 
        "HLT_IsoMu24_eta2p1_v*", 
        "HLT_IsoTkMu20_eta2p1_v*", 
        "HLT_IsoTkMu24_eta2p1_v*"
    ]),
    tagelectronptcut = cms.double(40.0),
    tagelectronetacut = cms.double(2.1),
    tagelectrontrigmatchdR = cms.double(0.3),
    requireelectronhlt = cms.bool(False),
    tagelectrontriggers = cms.vstring([
        "HLT_Ele27_eta2p1_WPLoose_Gsf_v*",
        "HLT_Ele27_eta2p1_WPTight_Gsf_v*",
        "HLT_Ele32_eta2p1_WPLoose_Gsf_v*",
        "HLT_Ele32_eta2p1_WPTight_Gsf_v*"
    ]),
    electronvetoid = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Spring15-25ns-V1-standalone-veto"),
    electronlooseid = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Spring15-25ns-V1-standalone-loose"),
    electronmediumid = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Spring15-25ns-V1-standalone-medium"),
    electrontightid = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Spring15-25ns-V1-standalone-tight"),
)

# Tag muons
process.tagmuons = cms.EDFilter("PATMuonSelector", 
    src = cms.InputTag("probeinfo", "tightmuons"),
    cut = cms.string(""),
    filter = cms.bool(True) 
)

# Tag electrons
process.tagelectrons = cms.EDFilter("PATElectronSelector",
    src = cms.InputTag("probeinfo", "tightelectrons"),
    cut = cms.string(""),
    filter = cms.bool(True)
)

# Tag and Probe pairs
process.muontnp = cms.EDProducer("CandViewShallowCloneCombiner",
    decay = cms.string("tagmuons@+ probemuons@-"),
    cut   = cms.string("60 < mass < 120"),
)

process.electrontnp = cms.EDProducer("CandViewShallowCloneCombiner",
    decay = cms.string("tagelectrons@+ probeelectrons@-"),
    cut   = cms.string("60 < mass < 120"),
)

# Make the TnP tree 
process.muontnptree = cms.EDAnalyzer("TagProbeFitTreeProducer",
    tagProbePairs = cms.InputTag("muontnp"),
    arbitration = cms.string("BestMass"),
    massForArbitration = cms.double(91.186),
    variables = cms.PSet(
        pt  = cms.string("pt()"),
        eta = cms.string("eta()"),
        abseta = cms.string("abs(eta())"),
        phi = cms.string("phi()"),
        nvtx = cms.InputTag("probeinfo", "munvtxmap"),
        wgt = cms.InputTag("probeinfo", "muwgtmap")
    ),
    flags = cms.PSet(
        pfid = cms.string("isPFMuon"),
        looseid = cms.InputTag("probeinfo", "loosemuonrefs"),
        tightid = cms.InputTag("probeinfo", "tightmuonrefs"),
    ),
    isMC = cms.bool(isMCFlag)
)

process.electrontnptree = cms.EDAnalyzer("TagProbeFitTreeProducer",
    tagProbePairs = cms.InputTag("electrontnp"),
    arbitration = cms.string("BestMass"),
    massForArbitration = cms.double(91.186),
    variables = cms.PSet(
        pt  = cms.string("pt()"),
        eta = cms.string("superCluster().eta()"),
        abseta = cms.string("abs(superCluster().eta())"),
        phi = cms.string("phi()"),
        nvtx = cms.InputTag("probeinfo", "elnvtxmap"),
        wgt = cms.InputTag("probeinfo", "elwgtmap")
    ),
    flags = cms.PSet(
        vetoid   = cms.InputTag("probeinfo", "vetoelectronrefs"),
        looseid  = cms.InputTag("probeinfo", "looseelectronrefs"),
        mediumid = cms.InputTag("probeinfo", "mediumelectronrefs"),
        tightid  = cms.InputTag("probeinfo", "tightelectronrefs"),
    ),
    isMC = cms.bool(isMCFlag)
)

# MC Truth Matching
if isMCFlag : 
    process.mcmutagmatch = cms.EDProducer("MCTruthDeltaRMatcherNew",
        matchPDGId = cms.vint32(13),
        src = cms.InputTag("tagmuons"),
        distMin = cms.double(0.1),
        matched = cms.InputTag("prunedGenParticles"),
        checkCharge = cms.bool(True)
    )

    process.mcmuprobematch = cms.EDProducer("MCTruthDeltaRMatcherNew",
        matchPDGId = cms.vint32(13),
        src = cms.InputTag("probemuons"),
        distMin = cms.double(0.1),
        matched = cms.InputTag("prunedGenParticles"),
        checkCharge = cms.bool(True)
    )

    process.mceltagmatch = cms.EDProducer("MCTruthDeltaRMatcherNew",
        matchPDGId = cms.vint32(11),
        src = cms.InputTag("tagelectrons"),
        distMin = cms.double(0.1),
        matched = cms.InputTag("prunedGenParticles"),
        checkCharge = cms.bool(True)
    )

    process.mcelprobematch = cms.EDProducer("MCTruthDeltaRMatcherNew",
        matchPDGId = cms.vint32(11),
        src = cms.InputTag("probeelectrons"),
        distMin = cms.double(0.1),
        matched = cms.InputTag("prunedGenParticles"),
        checkCharge = cms.bool(True)
    )

    process.muontnptree.tagMatches = cms.InputTag("mcmutagmatch")
    process.muontnptree.probeMatches = cms.InputTag("mcmuprobematch")
    process.muontnptree.motherPdgId = cms.int32(23)
    process.muontnptree.makeMCUnbiasTree = cms.bool(True)
    process.muontnptree.checkMotherInUnbiasEff = cms.bool(True)
    process.muontnptree.allProbes = cms.InputTag("probemuons")
    
    process.electrontnptree.tagMatches = cms.InputTag("mceltagmatch")
    process.electrontnptree.probeMatches = cms.InputTag("mcelprobematch")
    process.electrontnptree.motherPdgId = cms.int32(23)
    process.electrontnptree.makeMCUnbiasTree = cms.bool(True)
    process.electrontnptree.checkMotherInUnbiasEff = cms.bool(True)
    process.electrontnptree.allProbes = cms.InputTag("probeelectrons")

process.mutreePath = cms.Path(process.muontnptree)
process.eltreePath = cms.Path(process.electrontnptree)

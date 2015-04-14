import FWCore.ParameterSet.Config as cms

# Define the CMSSW process
process = cms.Process("TREE")

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
)

# How many events to process
process.maxEvents = cms.untracked.PSet( 
    input = cms.untracked.int32(-1)
)

# Is this a simulation or real data
isMC = True

# Filter on high MET events
filterHighMETEvents = False

# Define the global tag depending on the sample type
if isMC:
    process.GlobalTag.globaltag = 'PHYS14_25_V1::All'   # for Simulation
else:
    process.GlobalTag.globaltag = 'PHYS14_25_V1::All'   # for Data (for now set to the MC tag)

# Define the input source
process.source = cms.Source("PoolSource", 
    fileNames = cms.untracked.vstring('/store/mc/Phys14DR/ZJetsToNuNu_HT-100to200_Tune4C_13TeV-madgraph-tauola/MINIAODSIM/PU20bx25_PHYS14_25_V1-v1/00000/0E9FF9A1-D073-E411-B441-20CF305B04DA.root')
)

# Select good primary vertices
process.goodVertices = cms.EDFilter("VertexSelector",
  src = cms.InputTag("offlineSlimmedPrimaryVertices"),
  cut = cms.string("!isFake && ndof > 4 && abs(z) <= 24 && position.Rho <= 2"),
  filter = cms.bool(True),
)

# Electron and Photon ValueMaps for identification and isolation
process.load("RecoEgamma.PhotonIdentification.PhotonIDValueMapProducer_cfi")

from PhysicsTools.SelectorUtils.tools.vid_id_tools import *
process.load("RecoEgamma.ElectronIdentification.egmGsfElectronIDs_cfi")
process.egmGsfElectronIDs.physicsObjectSrc = cms.InputTag('slimmedElectrons')
from PhysicsTools.SelectorUtils.centralIDRegistry import central_id_registry
process.egmGsfElectronIDSequence = cms.Sequence(process.egmGsfElectronIDs)
my_id_modules = ['RecoEgamma.ElectronIdentification.Identification.cutBasedElectronID_PHYS14_PU20bx25_V1_miniAOD_cff']
for idmod in my_id_modules:
     setupAllVIDIdsInModule(process,idmod,setupVIDElectronSelection)

process.selectedObjects = cms.EDProducer("PFCleaner",
    vertices = cms.InputTag("goodVertices"),
    rho = cms.InputTag("fixedGridRhoFastjetAll"),
    muons = cms.InputTag("slimmedMuons"),
    electrons = cms.InputTag("slimmedElectrons"),
    photons = cms.InputTag("slimmedPhotons"),
    electronidveto = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-PHYS14-PU20bx25-V1-miniAOD-standalone-veto"),
    electronidmedium = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-PHYS14-PU20bx25-V1-miniAOD-standalone-medium"),
    photonsigmaietaieta = cms.InputTag("photonIDValueMapProducer:phoFull5x5SigmaIEtaIEta"),
    photonchargediso = cms.InputTag("photonIDValueMapProducer:phoChargedIsolation"),
    photonneutraliso = cms.InputTag("photonIDValueMapProducer:phoNeutralHadronIsolation"),
    photongammaiso = cms.InputTag("photonIDValueMapProducer:phoPhotonIsolation")
)

# Define all the METs corrected for lepton/photon momenta
process.mumet = cms.EDProducer("MuonCorrectedMETProducer",
    met = cms.InputTag("pfMet"),
    muons = cms.InputTag("selectedObjects", "muons")
)
process.pfmupt = cms.EDProducer("MuonCorrectedMETProducer",
    met = cms.InputTag("pfMet"),
    muons = cms.InputTag("selectedObjects", "muons"),
    muptonly = cms.bool(True)
)
process.phmet = cms.EDProducer("CandCorrectedMETProducer",
    met = cms.InputTag("pfMet"),
    cands = cms.VInputTag(cms.InputTag("selectedObjects", "photons")) 
)
process.t1mumet = cms.EDProducer("MuonCorrectedMETProducer",
    met = cms.InputTag("slimmedMETs"),
    muons = cms.InputTag("selectedObjects", "muons")
)
process.t1phmet = cms.EDProducer("CandCorrectedMETProducer",
    met = cms.InputTag("slimmedMETs"),
    cands = cms.VInputTag(cms.InputTag("selectedObjects", "photons")) 
)

from RecoMET.METProducers.PFMET_cfi import pfMet

process.pfMet = pfMet.clone(src = "packedPFCandidates")
process.pfMet.calculateSignificance = False

from RecoJets.JetProducers.ak4PFJets_cfi import ak4PFJets

process.ak4PFJets = ak4PFJets.clone(src = "packedPFCandidates")

process.load("JetMETCorrections.Type1MET.correctionTermsPfMetType1Type2_cff")
from JetMETCorrections.Type1MET.correctedMet_cff import pfMetT1
process.pfType1CorrectedMet = pfMetT1.clone()

# Remove MC matching when running on data
if not isMC:
    runOnData(process)

process.TFileService = cms.Service("TFileService", fileName = cms.string("tree.root"))

process.load("JetMETCorrections.Configuration.JetCorrectionServices_cff")
if isMC : 
    process.ak4PFCHSCorr = process.ak4PFCHSL1FastL2L3.clone()
else :
    process.ak4PFCHSCorr = process.ak4PFCHSL1FastL2L3Residual.clone()

process.tree = cms.EDAnalyzer("MonoJetTreeMaker",
    pileup = cms.InputTag("addPileupInfo"),
    vertices = cms.InputTag("goodVertices"),
    gens = cms.InputTag("prunedGenParticles"),
    pfcands = cms.InputTag("packedPFCandidates"),
    muons = cms.InputTag("selectedObjects", "muons"),
    electrons = cms.InputTag("selectedObjects", "electrons"),
    photons = cms.InputTag("selectedObjects", "photons"),
    tightmuons = cms.InputTag("selectedObjects", "tightmuons"),
    tightelectrons = cms.InputTag("selectedObjects", "tightelectrons"),
    tightphotons = cms.InputTag("selectedObjects", "tightphotons"),
    taus = cms.InputTag("slimmedTaus"),
    jets = cms.InputTag("slimmedJets"),
    fatjets = cms.InputTag("slimmedJetsAK8"),
    pfmet = cms.InputTag("pfMet"),
    t1pfmet = cms.InputTag("slimmedMETs"),
    pfmupt = cms.InputTag("pfmupt"),
    mumet = cms.InputTag("mumet"),
    phmet = cms.InputTag("phmet"),
    t1mumet = cms.InputTag("t1mumet"),
    t1phmet = cms.InputTag("t1phmet"),
    triggerResults = cms.InputTag("TriggerResults", "", "HLT"),
    jes = cms.string("ak4PFCHSCorr"),
    weight = cms.double(1000.0*831.76/25446993.0),
    isWorZMCSample = cms.bool(False),
    isSignalSample = cms.bool(False),
    cleanPhotonJet = cms.bool(True)
)

process.metfilter = cms.EDFilter("CandViewSelector",
    src = cms.InputTag("mumet"),
    cut = cms.string("et > 200"),
    filter = cms.bool(True)
)


if filterHighMETEvents: 
    process.treePath = cms.Path(process.goodVertices + process.metfilter + process.tree)
else :
    process.treePath = cms.Path(process.goodVertices + process.tree)


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
process.MessageLogger.cerr.FwkReport.reportEvery = 10

# Set the process options -- Display summary at the end, enable unscheduled execution
process.options = cms.untracked.PSet( 
    allowUnscheduled = cms.untracked.bool(True),
    wantSummary = cms.untracked.bool(False) 
)

# How many events to process
process.maxEvents = cms.untracked.PSet( 
    input = cms.untracked.int32(-1)
)

# Test code
myTest = False

# Is this a simulation or real data
isMC = False

# Filter on high MET events
filterHighMETEvents = True

# Filter on triggered events
filterOnHLT = False

# Use private JECs since the GTs are not updated
usePrivateSQlite = True

# Apply L2L3 residual corrections -- under development 
applyL2L3Residuals = True

# Define the input source
process.source = cms.Source(
    "PoolSource", 
    fileNames = cms.untracked.vstring([
            'file:/user/ndaci/Data/XMET/Run2015C/SingleElectron/MINIAOD_0T/A2A0552B-CE45-E511-BE5D-02163E013865.root'
            #'file:/user/ndaci/Data/XMET/Run2015C/SingleMuon/MINIAOD_0T/2E16F335-D945-E511-A469-02163E013865.root'
            #'/store/data/Run2015C/SingleMuon/MINIAOD/PromptReco-v1/000/254/226/00000/905BFE5A-2446-E511-9815-02163E014184.root'
            #'file:/store/data/Run2015C/SingleMuon/MINIAOD/PromptReco-v1/000/254/293/00000/2E16F335-D945-E511-A469-02163E013865.root',
            #'file:/store/data/Run2015C/SingleMuon/MINIAOD/PromptReco-v1/000/254/293/00000/301BB738-D945-E511-A3F7-02163E014462.root',
            #'file:/store/data/Run2015C/SingleMuon/MINIAOD/PromptReco-v1/000/254/293/00000/565E5A3B-D945-E511-995A-02163E011E04.root',
            #'file:/store/data/Run2015C/SingleMuon/MINIAOD/PromptReco-v1/000/254/293/00000/60E06B39-D945-E511-848D-02163E01358E.root',
            #'file:/store/data/Run2015C/SingleMuon/MINIAOD/PromptReco-v1/000/254/293/00000/7098D336-D945-E511-83FF-02163E011DF7.root',
            #'file:/store/data/Run2015C/SingleMuon/MINIAOD/PromptReco-v1/000/254/293/00000/86FAB239-D945-E511-8331-02163E0141E8.root',
            #'file:/store/data/Run2015C/SingleMuon/MINIAOD/PromptReco-v1/000/254/293/00000/BEC4B232-D945-E511-B4C7-02163E011F9D.root'
    ])
)

# Setup the service to make a ROOT TTree
process.TFileService = cms.Service("TFileService", fileName = cms.string("tree.root"))

# Set the global tag depending on the sample type
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
if isMC:
    process.GlobalTag.globaltag = 'MCRUN2_74_V9::All'    # for Simulation
else:
    process.GlobalTag.globaltag = 'GR_P_V56::All'        # for Data

# Setup the private SQLite -- Ripped from PhysicsTools/PatAlgos/test/corMETFromMiniAOD.py
if usePrivateSQlite:
    from CondCore.DBCommon.CondDBSetup_cfi import *
    import os
    era = "Summer15_50nsV4"
    if isMC : 
        era += "_MC"
    else :
        era += "_DATA"
    dBFile = os.path.expandvars(era+".db")
    process.jec = cms.ESSource("PoolDBESSource",
        CondDBSetup,
        connect = cms.string("sqlite_file:"+dBFile),
        toGet =  cms.VPSet(
            cms.PSet(
                record = cms.string("JetCorrectionsRecord"),
                tag = cms.string("JetCorrectorParametersCollection_"+era+"_AK4PF"),
                label= cms.untracked.string("AK4PF")
            ),
            cms.PSet(
                record = cms.string("JetCorrectionsRecord"),
                tag = cms.string("JetCorrectorParametersCollection_"+era+"_AK4PFchs"),
                label= cms.untracked.string("AK4PFchs")
            ),
        )
    )
    process.es_prefer_jec = cms.ESPrefer("PoolDBESSource",'jec')


# Set the process for reading MET filter flags from TriggerResults
if isMC:
    metFilterProcess = "PAT"
else :
    metFilterProcess = "RECO"

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
switchOnVIDPhotonIdProducer(process, dataFormat)

ele_id_modules = ['RecoEgamma.ElectronIdentification.Identification.cutBasedElectronID_PHYS14_PU20bx25_V2_cff']
ph_id_modules  = ['RecoEgamma.PhotonIdentification.Identification.cutBasedPhotonID_PHYS14_PU20bx25_V2_cff']
for idmod in ele_id_modules:
    setupAllVIDIdsInModule(process,idmod,setupVIDElectronSelection)
for idmod in ph_id_modules:
    setupAllVIDIdsInModule(process,idmod,setupVIDPhotonSelection)

# Rerun Jet/MET with updated corrections and recommendations 
if isMC:
    JECLevels = ['L1FastJet', 'L2Relative', 'L3Absolute']
else :
    if not applyL2L3Residuals : 
        JECLevels = ['L1FastJet', 'L2Relative', 'L3Absolute']
    else : 
        JECLevels = ['L1FastJet', 'L2Relative', 'L3Absolute', 'L2L3Residual']


from PhysicsTools.PatUtils.tools.runMETCorrectionsAndUncertainties import runMetCorAndUncFromMiniAOD

runMetCorAndUncFromMiniAOD(process,
    isData = (not isMC),
)
runMetCorAndUncFromMiniAOD(process,
    isData = (not isMC),
    pfCandColl = cms.InputTag("noHFCands"),
    postfix = "NoHF"
)

if not applyL2L3Residuals : 
    process.patPFMetT1T2Corr.jetCorrLabelRes = cms.InputTag("L3Absolute")
    process.patPFMetT1T2SmearCorr.jetCorrLabelRes = cms.InputTag("L3Absolute")
    process.patPFMetT2Corr.jetCorrLabelRes = cms.InputTag("L3Absolute")
    process.patPFMetT2SmearCorr.jetCorrLabelRes = cms.InputTag("L3Absolute")
    process.shiftedPatJetEnDown.jetCorrLabelUpToL3Res = cms.InputTag("ak4PFCHSL1FastL2L3Corrector")
    process.shiftedPatJetEnUp.jetCorrLabelUpToL3Res = cms.InputTag("ak4PFCHSL1FastL2L3Corrector")
    
    process.patPFMetT1T2CorrNoHF.jetCorrLabelRes = cms.InputTag("L3Absolute")
    process.patPFMetT1T2SmearCorrNoHF.jetCorrLabelRes = cms.InputTag("L3Absolute")
    process.patPFMetT2CorrNoHF.jetCorrLabelRes = cms.InputTag("L3Absolute")
    process.patPFMetT2SmearCorrNoHF.jetCorrLabelRes = cms.InputTag("L3Absolute")
    process.shiftedPatJetEnDownNoHF.jetCorrLabelUpToL3Res = cms.InputTag("ak4PFCHSL1FastL2L3Corrector")
    process.shiftedPatJetEnUpNoHF.jetCorrLabelUpToL3Res = cms.InputTag("ak4PFCHSL1FastL2L3Corrector")

from PhysicsTools.PatAlgos.producersLayer1.jetUpdater_cff import patJetCorrFactorsUpdated
process.patJetCorrFactorsReapplyJEC = patJetCorrFactorsUpdated.clone(
    src = cms.InputTag("slimmedJets"),
    levels = JECLevels,
    payload = 'AK4PFchs' 
)

from PhysicsTools.PatAlgos.producersLayer1.jetUpdater_cff import patJetsUpdated
process.slimmedJetsRecorrected = patJetsUpdated.clone(
    jetSource = cms.InputTag("slimmedJets"),
    jetCorrFactorsSource = cms.VInputTag(cms.InputTag("patJetCorrFactorsReapplyJEC"))
)

# Create a set of objects to read from
process.selectedObjects = cms.EDProducer("PFCleaner",
    vertices = cms.InputTag("goodVertices"),
    pfcands = cms.InputTag("packedPFCandidates"),
    muons = cms.InputTag("slimmedMuons"),
    electrons = cms.InputTag("slimmedElectrons"),
    photons = cms.InputTag("slimmedPhotons"),
    jets = cms.InputTag("slimmedJetsRecorrected"),
    electronidveto = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-PHYS14-PU20bx25-V2-standalone-veto"),
    electronidmedium = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-PHYS14-PU20bx25-V2-standalone-medium"),
    photonidloose = cms.InputTag("egmPhotonIDs:cutBasedPhotonID-PHYS14-PU20bx25-V2-standalone-loose")
)

# Define all the METs corrected for lepton/photon momenta
process.partMet = cms.EDProducer("METBreakDownProducer",
    pfcands = cms.InputTag("packedPFCandidates") 
)

process.noHFCands = cms.EDFilter("CandPtrSelector",
    src=cms.InputTag("packedPFCandidates"),
    cut=cms.string("abs(pdgId)!=1 && abs(pdgId)!=2 && abs(eta)<3.0")
)

process.mumet = cms.EDProducer("MuonCorrectedMETProducer",
    met = cms.InputTag("slimmedMETs"),
    muons = cms.InputTag("selectedObjects", "muons"),
)
process.pfmupt = cms.EDProducer("MuonCorrectedMETProducer",
    met = cms.InputTag("slimmedMETs"),
    muons = cms.InputTag("selectedObjects", "muons"),
    muptonly = cms.bool(True)
)
process.t1mumet = cms.EDProducer("MuonCorrectedMETProducer",
    met = cms.InputTag("slimmedMETs"),
    muons = cms.InputTag("selectedObjects", "muons")
)

# Quark-Gluon Discriminant
process.load("RecoJets.JetProducers.QGTagger_cfi")
process.QGTagger.srcJets = "slimmedJetsRecorrected"
process.QGTagger.srcVertexCollection = "goodVertices"

# Make the tree 
process.tree = cms.EDAnalyzer("MonoJetTreeMaker",
    pileup = cms.InputTag("addPileupInfo"),
    genevt = cms.InputTag("generator"),
    vertices = cms.InputTag("goodVertices"),
    gens = cms.InputTag("prunedGenParticles"),
    muons = cms.InputTag("selectedObjects", "muons"),
    electrons = cms.InputTag("selectedObjects", "electrons"),
    photons = cms.InputTag("selectedObjects", "photons"),
    tightmuons = cms.InputTag("selectedObjects", "tightmuons"),
    tightelectrons = cms.InputTag("selectedObjects", "tightelectrons"),
    tightphotons = cms.InputTag("selectedObjects", "tightphotons"),
    photonMediumId = cms.InputTag("egmPhotonIDs:cutBasedPhotonID-PHYS14-PU20bx25-V2-standalone-medium"),
    photonTightId = cms.InputTag("egmPhotonIDs:cutBasedPhotonID-PHYS14-PU20bx25-V2-standalone-tight"),
    loosephotons = cms.InputTag("selectedObjects", "loosephotons"),
    rndgammaiso = cms.InputTag("selectedObjects", "rndgammaiso"),
    rndchhadiso = cms.InputTag("selectedObjects", "rndchhadiso"),
    photonsieie = cms.InputTag("photonIDValueMapProducer", "phoFull5x5SigmaIEtaIEta"),
    taus = cms.InputTag("slimmedTaus"),
    jets = cms.InputTag("slimmedJetsRecorrected"),
    fatjets = cms.InputTag("slimmedJetsAK8"),
    qgl = cms.InputTag("QGTagger", "qgLikelihood"),
    qgs2 = cms.InputTag("QGTagger", "axis2"),
    qgmult = cms.InputTag("QGTagger", "mult"),
    qgptd = cms.InputTag("QGTagger", "ptD"),
    partmet = cms.InputTag("partMet"),
    t1pfmet = cms.InputTag("slimmedMETs"),
    t1metnohf = cms.InputTag("slimmedMETsNoHF"),
    pfmupt = cms.InputTag("pfmupt"),
    mumet = cms.InputTag("mumet"),
    t1mumet = cms.InputTag("t1mumet"),
    triggerResults = cms.InputTag("TriggerResults", "", "HLT"),
    objects        = cms.InputTag("selectedPatTrigger"),
    filterResults = cms.InputTag("TriggerResults", "", metFilterProcess),
    hcalnoise = cms.InputTag("hcalnoise"),
    xsec = cms.double(9235.0),
    cleanMuonJet = cms.bool(True),
    cleanElectronJet = cms.bool(True),
    cleanPhotonJet = cms.bool(True),
    applyHLTFilter = cms.bool(filterOnHLT),
    uselheweights = cms.bool(False),
    isWorZMCSample = cms.bool(False),
    verbose        = cms.int32(1)
)

# Tree for the generator weights
process.gentree = cms.EDAnalyzer("LHEWeightsTreeMaker",
    lheinfo = cms.InputTag("externalLHEProducer"),
    geninfo = cms.InputTag("generator"),
    uselheweights = cms.bool(True),
    addqcdpdfweights = cms.bool(True)
)

# MET filter
process.metfilter = cms.EDFilter("CandViewSelector",
    src = cms.InputTag("t1mumet"),
    cut = cms.string("et > 30"),
    filter = cms.bool(True)
)

# Set up the path
if myTest:
    process.treePath = cms.Path(process.tree)

elif filterHighMETEvents: 
    if (isMC):
        process.treePath = cms.Path(process.gentree + process.goodVertices + process.metfilter + process.tree)
    else :
        process.treePath = cms.Path(                  process.goodVertices + process.metfilter + process.tree)
else :
    if (isMC):
        process.treePath = cms.Path(process.gentree + process.goodVertices                     + process.tree)
    else :
        process.treePath = cms.Path(                  process.goodVertices                     + process.tree)
        #process.treePath = cms.Path(process.tree)

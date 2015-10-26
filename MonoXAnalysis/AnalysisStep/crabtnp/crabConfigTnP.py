from CRABClient.UserUtilities import config
config = config()

config.General.requestName = 'mAv2-TNP_DYLLJets'

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'tnptree.py'

#config.Data.ignoreLocality = True
#config.Data.inputDataset = '/SingleMuon/Run2015D-05Oct2015-v1/MINIAOD'
#config.Data.inputDataset = '/SingleMuon/Run2015D-PromptReco-v4/MINIAOD'
config.Data.inputDataset = '/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/MINIAODSIM'
config.Data.splitting = 'EventAwareLumiBased' #'LumiBased' 
config.Data.unitsPerJob = 50000 #50000

#config.Data.lumiMask = 'Cert_256630-258750_13TeV_PromptReco_Collisions15_25ns_JSON.txt'

config.Data.publication = False
config.Site.storageSite = 'T2_CH_CERN'


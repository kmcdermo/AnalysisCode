from CRABClient.UserUtilities import config
config = config()

config.General.requestName = 'PRv4_monoX-SingleEl_resubmit'

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'tree.py'

config.Data.inputDataset = '/SingleElectron/Run2015D-PromptReco-v4/MINIAOD'
#'/DoubleEG/Run2015D-05Oct2015-v1/MINIAOD'
#'/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/MINIAODSIM'
#/MET/Run2015D-PromptReco-v4/MINIAOD' #'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 15
#50000 for EALB in MC, 40 for LB in Data # 20 for single el/mu/double eg

config.Data.lumiMask = 'Cert_256630-258750_13TeV_PromptReco_Collisions15_25ns_JSON.txt'
config.Site.storageSite = 'T2_CH_CERN'

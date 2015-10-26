from WMCore.Configuration import Configuration
config = Configuration()

config.section_("General")
config.General.requestName = 'SingleMu_2015C_TnP'

config.section_("JobType")
config.JobType.allowUndistributedCMSSW = True
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'tnptreeData.py'

config.section_("Data")
config.Data.inputDataset = '/SingleMuon/Run2015C-PromptReco-v1/MINIAOD'
config.Data.inputDBS = 'global'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 40

config.Data.lumiMask = 'Cert_246908-255031_13TeV_PromptReco_Collisions15_25ns_JSON_v2.txt'
config.Data.publication = False
config.Data.outLFNDirBase = '/store/user/kmcdermo/'
config.Data.publishDBS = 'phys03'
config.Data.publishDataName = 'SingleMu_2015C_TnP'
config.section_('User')
config.section_("Site")
config.Site.storageSite = 'T2_CH_CERN'


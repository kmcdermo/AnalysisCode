from WMCore.Configuration import Configuration
config = Configuration()

config.section_("General")
config.General.requestName = 'SingleEl_2015B_TnP'

config.section_("JobType")
config.JobType.allowUndistributedCMSSW = True
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'tnptree.py'

config.section_("Data")
config.Data.inputDataset = '/SingleElectron/Run2015B-PromptReco-v1/MINIAOD'
config.Data.inputDBS = 'global'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 40

config.Data.lumiMask = 'Cert_246908-254349_13TeV_PromptReco_Collisions15_JSON_v2.txt'
config.Data.publication = False
config.Data.outLFNDirBase = '/store/user/kmcdermo/'
config.Data.publishDBS = 'phys03'
config.Data.publishDataName = 'SingleEl_2015B_TnP'
config.section_('User')
config.section_("Site")
config.Site.storageSite = 'T2_CH_CERN'


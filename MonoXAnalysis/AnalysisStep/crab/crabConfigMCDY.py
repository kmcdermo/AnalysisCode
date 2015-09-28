from WMCore.Configuration import Configuration
config = Configuration()

config.section_("General")
config.General.requestName = 'DYLL_TnP_25ns'

config.section_("JobType")
config.JobType.allowUndistributedCMSSW = True
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'tnptreeMC.py'

config.section_("Data")
config.Data.inputDataset = '/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v3/MINIAODSIM'
config.Data.inputDBS = 'global'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 40

#config.Data.lumiMask = 'https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions15/13TeV/DCSOnly/json_DCSONLY_Run2015B.txt'
config.Data.publication = False
config.Data.outLFNDirBase = '/store/user/kmcdermo/'
config.Data.publishDBS = 'phys03'
config.Data.publishDataName = 'DYLL_TnP_25ns'
config.section_('User')
config.section_("Site")
config.Site.storageSite = 'T2_CH_CERN'

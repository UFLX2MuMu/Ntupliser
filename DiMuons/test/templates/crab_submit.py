from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.requestName = 'ggToHToMuMu_PU40bx50_try2'
config.General.workArea = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs = True

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'UFDiMuonAnalyzer.py'
#config.JobType.outputFiles = ['outputfile.root']

config.Data.inputDataset = '/GluGluToHToMuMu_M-125_13TeV-powheg-pythia6/Spring14miniaod-141029_PU40bx50_PLS170_V6AN2-v1/MINIAODSIM'
config.Data.inputDBS = 'global'
config.Data.splitting = 'FileBased'
#config.Data.splitting = 'LumiBased' # Must use this with JSON file
#config.Data.lumiMask = '/path/to/JSON_file.txt'
config.Data.unitsPerJob = 1
config.Data.outLFNDirBase = '/store/user/acarnes/'
config.Data.publication = False
config.Data.outputDatasetTag = 'ggToHToMuMu_PU40bx50'

config.Site.storageSite = 'T2_US_Florida'

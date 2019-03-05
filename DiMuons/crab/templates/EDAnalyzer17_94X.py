# =============================================================#
#                      UFDiMuonsAnalyzer                       #
#                                                              #
# Stripped down, no updateJetCollection, apparently not needed #
# egmGsfElectronID necessary for electron ID - AWB 23.10.2018  #
# =============================================================#


# /////////////////////////////////////////////////////////////
# Load some things
# /////////////////////////////////////////////////////////////

import FWCore.ParameterSet.Config as cms

process = cms.Process('dimuons')

process.load('FWCore.MessageService.MessageLogger_cfi')

process.load('Configuration.EventContent.EventContent_cff')
process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')


# /////////////////////////////////////////////////////////////
# Get a sample from our collection of samples
# /////////////////////////////////////////////////////////////

if samp.isData:
    print '\nRunning over data sample %s' % samp.name
else:
    print '\nRunning over MC sample %s' % samp.name
print '  * From DAS: %s' % samp.DAS


# /////////////////////////////////////////////////////////////
# Global tag, automatically retrieved from the imported sample
# /////////////////////////////////////////////////////////////

print '\nLoading Global Tag: ' + samp.GT
process.GlobalTag.globaltag = samp.GT


# /////////////////////////////////////////////////////////////
# ------------ PoolSource -------------
# /////////////////////////////////////////////////////////////
readFiles = cms.untracked.vstring();
# Get list of files from the sample we loaded
readFiles.extend(samp.files);


process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.MessageLogger.cerr.FwkReport.reportEvery = 1000
process.source = cms.Source('PoolSource',fileNames = readFiles)
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(False) )
process.source.lumisToProcess = cms.untracked.VLuminosityBlockRange()

# # use a JSON file when locally executing cmsRun
# if samp.isData:
#     import FWCore.PythonUtilities.LumiList as LumiList
#     process.source.lumisToProcess = LumiList.LumiList(filename = samp.JSON).getVLuminosityBlockRange()
#     # process.source.lumisToProcess = LumiList.LumiList(filename = 'data/JSON/bad_evt.txt').getVLuminosityBlockRange()


# /////////////////////////////////////////////////////////////
# Save output with TFileService
# /////////////////////////////////////////////////////////////

process.TFileService = cms.Service('TFileService', fileName = cms.string('tuple.root') )


# /////////////////////////////////////////////////////////////
# Load electron IDs
# /////////////////////////////////////////////////////////////

## Following https://twiki.cern.ch/twiki/bin/view/CMS/EgammaPostRecoRecipes#Running_on_2017_MiniAOD_V2
## More complete recipe documentation: https://twiki.cern.ch/twiki/bin/view/CMS/MultivariateElectronIdentificationRun2
##               - In particular here: https://twiki.cern.ch/twiki/bin/view/CMS/MultivariateElectronIdentificationRun2#VID_based_recipe_provides_pass_f
from RecoEgamma.EgammaTools.EgammaPostRecoTools import setupEgammaPostRecoSeq
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')

setupEgammaPostRecoSeq( process,
                        runVID = True ,  ## Needed for 2017 V2 IDs
                        era    = '2017-Nov17ReReco' )
                        # eleIDModules = [ 'RecoEgamma.ElectronIdentification.Identification.cutBasedElectronID_Fall17_94X_V2_cff',
                        #                  'RecoEgamma.ElectronIdentification.Identification.mvaElectronID_Fall17_noIso_V1_cff' ] )


# /////////////////////////////////////////////////////////////
# Load UFDiMuonsAnalyzer
# /////////////////////////////////////////////////////////////

if samp.isData:
  process.load('Ntupliser.DiMuons.Analyzer_2017_94X_cff')
else:
  process.load('Ntupliser.DiMuons.Analyzer_2017_94X_MC_cff')


# # /////////////////////////////////////////////////////////////
# # Save output tree
# # /////////////////////////////////////////////////////////////

# outCommands = cms.untracked.vstring('keep *')

# process.treeOut = cms.OutputModule('PoolOutputModule',
#                                    fileName = cms.untracked.string('tree.root'),
#                                    outputCommands = outCommands
#                                    )

# process.treeOut_step = cms.EndPath(process.treeOut) ## Keep output tree


# /////////////////////////////////////////////////////////////
# Set the order of operations
# /////////////////////////////////////////////////////////////
    
print 'About to run the process path'

## Unscheduled running Recommended at least by JetMET, but apparently 'default' and not necessary in CMSSW >= 9_1_0
## https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideUnscheduledExecution

## Following struture seen in:
## https://github.com/pfs/TopLJets2015/blob/master/TopAnalysis/test/runMiniAnalyzer_cfg.py#L169
## https://github.com/pfs/TopLJets2015/blob/master/TopAnalysis/python/customizeJetTools_cff.py#L47
## https://github.com/pfs/TopLJets2015/blob/master/TopAnalysis/python/customizeEGM_cff.py#L67

process.egamma_step = cms.Path( process.egammaPostRecoSeq )  ## See setupEgammaPostRecoSeq above
process.ntuple_step = cms.Path( process.dimuons )

process.schedule = cms.Schedule( process.egamma_step, process.ntuple_step )  ## , process.treeOut_step )

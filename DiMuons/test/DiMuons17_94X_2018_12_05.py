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

# from python.Samples_2017_94X_v2 import SingleMu_2017C as samp
# from python.Samples_2017_94X_v2 import H2Mu_gg_125_NLO as samp
from python.Samples_2017_94X_v2 import H2Mu_ttH_125 as samp

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


process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000) )
process.MessageLogger.cerr.FwkReport.reportEvery = 100
process.source = cms.Source('PoolSource',fileNames = readFiles)
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(False) )
process.source.lumisToProcess = cms.untracked.VLuminosityBlockRange()

# use a JSON file when locally executing cmsRun
if samp.isData:
    import FWCore.PythonUtilities.LumiList as LumiList
    process.source.lumisToProcess = LumiList.LumiList(filename = samp.JSON).getVLuminosityBlockRange()
    # process.source.lumisToProcess = LumiList.LumiList(filename = 'data/JSON/bad_evt.txt').getVLuminosityBlockRange()


# /////////////////////////////////////////////////////////////
# Save output with TFileService
# /////////////////////////////////////////////////////////////

# process.TFileService = cms.Service('TFileService', fileName = cms.string('SingleMu_2016C_1k.root') )
# process.TFileService = cms.Service('TFileService', fileName = cms.string('GluGlu_HToMuMu_M125_NLO.root') )
process.TFileService = cms.Service('TFileService', fileName = cms.string('ttH_HToMuMu_M125_1k_mod.root') )
# process.TFileService = cms.Service('TFileService', fileName = cms.string('ZJets_AMC.root') )
# process.TFileService = cms.Service('TFileService', fileName = cms.string('ZJets_MG_HT_2500_inf.root') )


# /////////////////////////////////////////////////////////////
# Load electron IDs
# /////////////////////////////////////////////////////////////

from RecoEgamma.EgammaTools.EgammaPostRecoTools import setupEgammaPostRecoSeq
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')

setupEgammaPostRecoSeq( process,
                        runVID       = True,  ## Needed to get V2 electron IDs
                        era          = '2017-Nov17ReReco' )
                        # eleIDModules = [ 'RecoEgamma.ElectronIdentification.Identification.cutBasedElectronID_Fall17_94X_V2_cff',
                        #                  'RecoEgamma.ElectronIdentification.Identification.mvaElectronID_Fall17_noIso_V1_cff' ] )

# setupEgammaPostRecoSeq( process,
#                         applyEnergyCorrections    = False,  ## Default
#                         applyVIDOnCorrectedEgamma = False,  ## Default
#                         isMiniAOD                 = True,   ## Default
#                         era                       = "2017-Nov17ReReco",
#                         eleIDModules              = [ ## egmGsfElectronIDs:cutBasedElectronID-Fall17-94X-V2
#                                                       'RecoEgamma.ElectronIdentification.Identification.cutBasedElectronID_Fall17_94X_V2_cff',
#                                                       ## electronMVAValueMapProducer:ElectronMVAEstimatorRun2Fall17NoIsoV1Values
#                                                       'RecoEgamma.ElectronIdentification.Identification.mvaElectronID_Fall17_noIso_V1_cff' ],
#                         phoIDModules              = [],     ## Photons not used
#                         runVID                    = False,  ## Default for 2017 MiniAOD v2
#                         runEnergyCorrections      = True,   ## Default
#                         applyEPCombBug            = False,  ## Default
#                         autoAdjustParams          = True )  ## Default

# ## Modeled after https://github.com/GhentAnalysis/heavyNeutrino/blob/master/multilep/python/egmSequence_cff.py
# ## Have to merge V2 electron IDs using this recipe: https://twiki.cern.ch/twiki/bin/viewauth/CMS/CutBasedElectronIdentificationRun2#Recipe_for_regular_users_formats
# from PhysicsTools.SelectorUtils.tools.vid_id_tools import *
# process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
# switchOnVIDElectronIdProducer(process, DataFormat.MiniAOD)
# eleIDs = [ 'RecoEgamma.ElectronIdentification.Identification.cutBasedElectronID_Fall17_94X_V2_cff',
#            'RecoEgamma.ElectronIdentification.Identification.mvaElectronID_Fall17_noIso_V1_cff' ]

# for eleID in eleIDs: setupAllVIDIdsInModule(process, eleID, setupVIDElectronSelection)

# /////////////////////////////////////////////////////////////
# Load UFDiMuonsAnalyzer
# /////////////////////////////////////////////////////////////

if samp.isData:
  process.load('Ntupliser.DiMuons.Analyzer_2017_94X_cff')
else:
  process.load('Ntupliser.DiMuons.Analyzer_2017_94X_MC_cff')

# process.dimuons.isVerbose  = cms.untracked.bool(False)
# process.dimuons.doSys      = cms.bool(True)
# process.dimuons.doSys_KaMu = cms.bool(False)
# process.dimuons.doSys_Roch = cms.bool(True)
# process.dimuons.slimOut    = cms.bool(True)

# process.dimuons.jetsTag    = cms.InputTag('slimmedJets')


# /////////////////////////////////////////////////////////////
# Save output tree
# /////////////////////////////////////////////////////////////

outCommands = cms.untracked.vstring('keep *')

process.treeOut = cms.OutputModule('PoolOutputModule',
                                   fileName = cms.untracked.string('tree.root'),
                                   outputCommands = outCommands
                                   )

process.treeOut_step = cms.EndPath(process.treeOut) ## Keep output tree


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

process.egamma_step   = cms.Path( process.egammaPostRecoSeq )
# process.egammaID_step = cms.Path( process.egmGsfElectronIDSequence )  ## See eleIDs above
process.ntuple_step   = cms.Path( process.dimuons )

process.schedule = cms.Schedule( process.egamma_step, process.ntuple_step, process.treeOut_step )

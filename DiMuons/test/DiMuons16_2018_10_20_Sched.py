# =============================================================#
#                      UFDiMuonsAnalyzer                       #
#                                                              #
# Scheduled, no longer recommended - much slower               #
# Also complicates updateJetCollection                         #
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

# from python.Samples_2016_94X_v2 import SingleMu_2016C as samp
# from python.Samples_2016_94X_v2 import H2Mu_gg as samp
from python.Samples_2016_94X_v2 import ZJets_AMC as samp
# from python.Samples_2016_94X_v2 import ZJets_MG_HT_2500_inf as samp

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

# readFiles.extend(['file:dy_jetsToLL.root']);

# readFiles.extend(['root://cms-xrd-global.cern.ch//store/mc/RunIISpring16MiniAODv2/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/50000/000FF6AC-9F2A-E611-A063-0CC47A4C8EB0.root']);

# ## From /GluGlu_HToMuMu_M125_13TeV_powheg_pythia8/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM
# readFiles.extend(['/store/user/abrinke1/HiggsToMuMu/samples/GluGlu_HToMuMu_M125_13TeV_powheg_pythia8/PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/12B931FE-CD3A-E611-9844-0025905C3D98.root'])

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10000) )
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

# process.TFileService = cms.Service('TFileService', fileName = cms.string('SingleMu_2016C_Sched_slimmedJets_noJEC.root') )
# process.TFileService = cms.Service('TFileService', fileName = cms.string('GluGlu_HToMuMu_M125_GEN_Sched.root') )
process.TFileService = cms.Service('TFileService', fileName = cms.string('ZJets_AMC_Sched_slimmedJets_noJEC.root') )
# process.TFileService = cms.Service('TFileService', fileName = cms.string('ZJets_AMC_Sched_updatedPatJetsUpdatedJEC.root') )
# process.TFileService = cms.Service('TFileService', fileName = cms.string('ZJets_AMC_Sched_updatedPatJetsTransientCorrectedUpdatedJEC.root') )
# process.TFileService = cms.Service('TFileService', fileName = cms.string('ZJets_MG_HT_2500_inf_Sched.root') )


# /////////////////////////////////////////////////////////////
# Load electron IDs
# /////////////////////////////////////////////////////////////

## Modeled after https://github.com/GhentAnalysis/heavyNeutrino/blob/master/multilep/python/egmSequence_cff.py
from PhysicsTools.SelectorUtils.tools.vid_id_tools import *
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
switchOnVIDElectronIdProducer(process, DataFormat.MiniAOD)
eleIDs = [ 'RecoEgamma.ElectronIdentification.Identification.cutBasedElectronID_Summer16_80X_V1_cff',
           'RecoEgamma.ElectronIdentification.Identification.mvaElectronID_Spring16_GeneralPurpose_V1_cff' ]
for eleID in eleIDs: setupAllVIDIdsInModule(process, eleID, setupVIDElectronSelection)


# # /////////////////////////////////////////////////////////////
# # Update jet energy corrections
# # /////////////////////////////////////////////////////////////

# ## Following https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookJetEnergyCorrections#CorrPatJets
# ## See also https://github.com/cms-sw/cmssw/blob/CMSSW_7_6_X/PhysicsTools/PatAlgos/test/patTuple_updateJets_fromMiniAOD_cfg.py
# ## Some details based on https://github.com/GhentAnalysis/heavyNeutrino/blob/master/multilep/python/jetSequence_cff.py
# from PhysicsTools.PatAlgos.tools.jetTools import updateJetCollection
# process.load('Configuration.StandardSequences.MagneticField_cff') # needed for pfImpactParameterTagInfos

# updateJetCollection(
#     process,
#     jetSource = cms.InputTag('slimmedJets'),
#     labelName = 'UpdatedJEC',
#     jetCorrections = ('AK4PFchs', cms.vstring(['L1FastJet', 'L2Relative', 'L3Absolute', 'L2L3Residual']), 'None'),
#     ## Update: Safe to always add 'L2L3Residual' as MC contains dummy L2L3Residual corrections (always set to 1)
#     btagDiscriminators = [ 'pfCombinedInclusiveSecondaryVertexV2BJetTags',
#                            'pfDeepCSVJetTags:probb',
#                            'pfDeepCSVJetTags:probbb' ]
#     ## Requires switch to 'updatedPatJetsTransientCorrectedUpdatedJEC' as jetsTag input source
#     ## https://github.com/cms-sw/cmssw/blob/master/PhysicsTools/PatAlgos/python/tools/jetTools.py#L1660
#     )

# process.jetSequence = cms.Sequence(process.patAlgosToolsTask)


# /////////////////////////////////////////////////////////////
# Load UFDiMuonsAnalyzer
# /////////////////////////////////////////////////////////////

if samp.isData:
  process.load('Ntupliser.DiMuons.UFDiMuonsAnalyzer_cff')
else:
  process.load('Ntupliser.DiMuons.UFDiMuonsAnalyzer_MC_cff')

process.dimuons.isVerbose  = cms.untracked.bool(False)
process.dimuons.doSys      = cms.bool(True)
process.dimuons.doSys_KaMu = cms.bool(False)
process.dimuons.doSys_Roch = cms.bool(True)
process.dimuons.slimOut    = cms.bool(True)

## No warning, deepCSV and jecFactor apparently filled
## Exactly identical nJets and jets pt, eta, jecFactor, CSV, and deepCSV to Unscheduled
## Also exactly identical eles mvaID and lepMVA, and muons lepMVA
process.dimuons.jetsTag = cms.InputTag('slimmedJets')

# # ## Gives following fatal exception: This JEC level L1FastJet does not exist.
# process.dimuons.jetsTag = cms.InputTag('updatedPatJetsUpdatedJEC')

# ## Gives following warning:
# ## %MSG-w L3Absolute not found:  PATJetUpdater:updatedPatJetsUpdatedJEC
# ## L2L3Residual and L3Absolute are not part of the jetCorrFactors
# ## of module patJetCorrFactorsUpdatedJEC. Jets will remain uncorrected.
# ## Exactly identical nJets and jets pt, eta, and jecFactor to Unscheduled
# ## *VERY* slightly different CSV and deepCSV, also lepMVA
# process.dimuons.jetsTag = cms.InputTag('updatedPatJetsTransientCorrectedUpdatedJEC')


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

process.p = cms.Path( # process.BadPFMuonFilter *
                      process.egmGsfElectronIDSequence *  ## See eleIDs above
                      # process.jetSequence *  ## See updateJetCollection above
                      process.dimuons )

# ## https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideUnscheduledExecution
# from FWCore.ParameterSet.Utilities import convertToUnscheduled
# convertToUnscheduled(process)

# process.schedule = cms.Schedule(process.p, process.treeOut_step)

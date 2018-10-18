# =============================================================#
# DiMuons                                            #
# =============================================================#
# Makes stage 1 trees.                                         #
# Originally Made by Justin Hugon. Edited by Andrew Carnes and #
# Andrew Brinkerhoff.                                          #
################################################################

# /////////////////////////////////////////////////////////////
# Load some things
# /////////////////////////////////////////////////////////////

import FWCore.ParameterSet.Config as cms

process = cms.Process("DiMuons")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.load('Configuration.EventContent.EventContent_cff')
process.load('Configuration.StandardSequences.Services_cff')
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")

## Geometry and Detector Conditions (needed for a few patTuple production steps)

## Correct geometry to use?  What about GeometryExtended2016_cff or GeometryExtended2016Reco_cff? - AWB 16.01.17
## https://github.com/cms-sw/cmssw/tree/CMSSW_8_0_X/Configuration/Geometry/python
process.load("Configuration.Geometry.GeometryIdeal_cff")  

# ## Geometry according to Tim Cox, used by Jia Fu Low
# ##   https://indico.cern.ch/event/588469/contributions/2372672/subcontributions/211968/attachments/1371248/2079893/
# ##   2016-11-14_coordinate_conversion_v1.pdf
# from Configuration.AlCa.autoCond import autoCond
# process.load('Configuration.StandardSequences.GeometryDB_cff')
# process.load("Alignment.CommonAlignmentProducer.FakeAlignmentSource_cfi")
# process.preferFakeAlign = cms.ESPrefer("FakeAlignmentSource")


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

# # /////////////////////////////////
# # Additional jet energy corrections
# # /////////////////////////////////

# ## See https://twiki.cern.ch/twiki/bin/view/CMS/JECDataMC
# ## and https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookJetEnergyCorrections

# from CondCore.DBCommon.CondDBSetup_cfi import CondDBSetup
# process.jec = cms.ESSource('PoolDBESSource',
#     CondDBSetup,
#     connect = cms.string('sqlite:data/JEC/Spring16_23Sep2016V2_MC.db'),
#     toGet = cms.VPSet(
#         # cms.PSet(
#         #     record = cms.string('JetCorrectionsRecord'),
#         #     tag    = cms.string('JetCorrectorParametersCollection_Fall15_V2_DATA_AK4PFchs'),
#         #     label  = cms.untracked.string('AK4PFchs')
#         # ),
#         cms.PSet(
#             record = cms.string('JetCorrectionsRecord'),
#             # record = cms.string('JetCorrectorParametersCollection'),  ## Produces run-time error
#             tag    = cms.string('JetCorrectorParametersCollection_Spring16_23Sep2016V2_MC_AK4PFchs'),
#             # label  = cms.untracked.string('AK4PFchs')
#             label  = cms.untracked.string('slimmedJets')
#         ),
#         # ...and so on for all jet types you need
#     )
# )

# ## Add an ESPrefer to override JEC that might be available from the global tag
# process.es_prefer_jec = cms.ESPrefer('PoolDBESSource', 'jec')


# /////////////////////////////////////////////////////////////
# ------------ PoolSource -------------
# /////////////////////////////////////////////////////////////
readFiles = cms.untracked.vstring();
## Get list of local files from the sample we loaded (not used in crab)
readFiles.extend(samp.files);

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.MessageLogger.cerr.FwkReport.reportEvery = 10000
process.source = cms.Source("PoolSource", fileNames = readFiles)
process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(False) )
process.source.lumisToProcess = cms.untracked.VLuminosityBlockRange()

## Use a JSON file for local running (not used in crab)
if samp.isData:
    import FWCore.PythonUtilities.LumiList as LumiList
    process.source.lumisToProcess = LumiList.LumiList(filename = samp.JSON).getVLuminosityBlockRange()


# /////////////////////////////////////////////////////////////
# Save output with TFileService
# /////////////////////////////////////////////////////////////

process.TFileService = cms.Service("TFileService", fileName = cms.string("tuple.root") )

# /////////////////////////////////////////////////////////////
# Load DiMuons
# /////////////////////////////////////////////////////////////

if samp.isData:
  process.load("Ntupliser.DiMuons.UFDiMuonsAnalyzer_cff")
else:
  process.load("Ntupliser.DiMuons.UFDiMuonsAnalyzer_MC_cff")

process.dimuons = process.DiMuons.clone()


# /////////////////////////////////////////////////////////////
# Electron Cut Based IDs
# /////////////////////////////////////////////////////////////

from PhysicsTools.SelectorUtils.tools.vid_id_tools import *

dataFormat = DataFormat.MiniAOD
switchOnVIDElectronIdProducer(process, dataFormat)

## First need to run: git cms-merge-topic ikrav:egm_id_80X_v1
## https://twiki.cern.ch/twiki/bin/view/CMS/CutBasedElectronIdentificationRun2#Recipe_for_regular_users_for_8_0
my_id_modules = ['RecoEgamma.ElectronIdentification.Identification.cutBasedElectronID_Summer16_80X_V1_cff']
for idmod in my_id_modules:
    setupAllVIDIdsInModule(process,idmod,setupVIDElectronSelection)


# /////////////////////////////////////////////////////////////
# Updated Jet Energy Scale corrections
# /////////////////////////////////////////////////////////////

## Following https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookJetEnergyCorrections#CorrPatJets
##   - Last check that procedure was up-to-date: March 10, 2017 (AWB)
from PhysicsTools.PatAlgos.tools.jetTools import updateJetCollection

if samp.isData:
    JEC_to_apply = cms.vstring(['L1FastJet', 'L2Relative', 'L3Absolute', 'L2L3Residual'])
else:
    JEC_to_apply = cms.vstring(['L1FastJet', 'L2Relative', 'L3Absolute'])
    
updateJetCollection(
    process,
    jetSource = cms.InputTag('slimmedJets'),
    labelName = 'UpdatedJEC',
    jetCorrections = ('AK4PFchs', JEC_to_apply, 'None')
    )

process.jecSequence = cms.Sequence(process.patJetCorrFactorsUpdatedJEC * process.updatedPatJetsUpdatedJEC)


# /////////////////////////////////////////////////////////////
# Corrected MET (and jets?)
# /////////////////////////////////////////////////////////////

## Following https://twiki.cern.ch/twiki/bin/view/CMS/MissingETUncertaintyPrescription
##   - Last check that procedure was up-to-date: March 10, 2017 (AWB)

## First need to run: git cms-merge-topic cms-met:METRecipe_8020 -u
from PhysicsTools.PatUtils.tools.runMETCorrectionsAndUncertainties import runMetCorAndUncFromMiniAOD

## If you only want to re-correct and get the proper uncertainties
runMetCorAndUncFromMiniAOD(process, isData=samp.isData)

# /////////////////////////////////////////////////////////////
# Set the order of operations
# /////////////////////////////////////////////////////////////
    
process.p = cms.Path( # process.BadPFMuonFilter *
                      process.egmGsfElectronIDSequence *
                      process.jecSequence *
                      process.fullPatMetSequence *
                      process.dimuons )


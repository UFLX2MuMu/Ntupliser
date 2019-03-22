import FWCore.ParameterSet.Config as cms

process = cms.Process("UFDiMuonsAnalyzer")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.load('Configuration.EventContent.EventContent_cff')
process.load('Configuration.StandardSequences.Services_cff')
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")


# /////////////////////////////////////////////////////////////
# Get a sample from our collection of samples
# /////////////////////////////////////////////////////////////

if samp.isData:
    print '\nRunning over data sample %s' % samp.name
else:
    print '\nRunning over MC sample %s' % samp.name
print '  * From DAS: %s' % samp.DAS

# /////////////////////////////////////////////////////////////
# global tag, automatically retrieved from the imported sample
# /////////////////////////////////////////////////////////////

print '\nLoading Global Tag: ' + samp.GT
process.GlobalTag.globaltag = samp.GT

# # /////////////////////////////////
# # Additional jet energy corrections
# # /////////////////////////////////

# ## The recommended way of accessing JEC is via a global tag.
# ## However, in case the JEC are available as a sqlite file and not in the global tag yet we can use this section.
# ## More info in:
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

# # Add an ESPrefer to override JEC that might be available from the global tag
# process.es_prefer_jec = cms.ESPrefer('PoolDBESSource', 'jec')


# /////////////////////////////////////////////////////////////
# ------------ PoolSource -------------
# /////////////////////////////////////////////////////////////
readFiles = cms.untracked.vstring();
## Get list of local files from the sample we loaded (not used in crab)
readFiles.extend(samp.files);

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.MessageLogger.cerr.FwkReport.reportEvery = 10000
process.source = cms.Source("PoolSource",fileNames = readFiles)
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(False) )
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
# Load UFDiMuonsAnalyzer
# /////////////////////////////////////////////////////////////

if samp.isData:
  process.load("Ntupliser.DiMuons.Analyzer_data_cff")
else:
  process.load("Ntupliser.DiMuons.Analyzer_MC_cff")

# Overwrite the settings in the Ntupliser/DiMuons/python/Analyzers*cff analyzers
# Parameters that in a crab production should usually be equal for data and MC
process.dimuons.isVerbose  = cms.untracked.bool(False)
process.dimuons.doSys      = cms.bool(True)
process.dimuons.doSys_KaMu = cms.bool(False)
process.dimuons.doSys_Roch = cms.bool(True)
process.dimuons.slimOut    = cms.bool(False) #reducing the number of branches. This should be the same in data and MC to avoid confusion.
process.dimuons.skim_nMuons = cms.int32(2)

# /////////////////////////////////////////////////////////////
# Electron IDs
# /////////////////////////////////////////////////////////////

## Following https://twiki.cern.ch/twiki/bin/view/CMS/EgammaPostRecoRecipes#Running_on_2017_MiniAOD_V2
## More complete recipe documentation: https://twiki.cern.ch/twiki/bin/view/CMS/MultivariateElectronIdentificationRun2
##               - In particular here: https://twiki.cern.ch/twiki/bin/view/CMS/MultivariateElectronIdentificationRun2#VID_based_recipe_provides_pass_f

from RecoEgamma.EgammaTools.EgammaPostRecoTools import setupEgammaPostRecoSeq
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')

setupEgammaPostRecoSeq( process,
                        era    = '2018-Prompt' )
 
# /////////////////////////////////////////////////////////////
# Updated Jet Energy Scale corrections
# /////////////////////////////////////////////////////////////

## Following https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookJetEnergyCorrections#CorrPatJets
##   - Last check that procedure was up-to-date: March 10, 2017 (AWB)
##   - checked again 21.06.2018 (PB)
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

## Following https://twiki.cern.ch/twiki/bin/view/CMS/MissingETUncertaintyPrescription - AWB 01.03.17
##   - Last check that procedure was up-to-date: March 10, 2017 (AWB). Reviewd 31.05.2018 (PB)

## Only if you want to recluster MET or JET: first need to run: git cms-merge-topic cms-met:METRecipe_94X -u
## Temporary fix for 2017 data and 17Nov2017 re-reco. Excluding low pt jets in |eta|=[2.650-3.139] region from the calculation of Type1 MET correction. Will be integrated in 10_1_X cycle git cms-merge-topic cms-met:METRecipe94xEEnoisePatch -u (PB)
from PhysicsTools.PatUtils.tools.runMETCorrectionsAndUncertainties import runMetCorAndUncFromMiniAOD

## If you only want to re-correct and get the proper uncertainties
runMetCorAndUncFromMiniAOD(process, isData=samp.isData)

# /////////////////////////////////////////////////////////////
# Set the order of operations
# /////////////////////////////////////////////////////////////

process.p = cms.Path( 
                      process.egammaPostRecoSeq *
                      process.jecSequence *
                      process.fullPatMetSequence *
                      process.dimuons )


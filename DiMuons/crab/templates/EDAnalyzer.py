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
# Global tag, automatically retrieved from the imported sample
# /////////////////////////////////////////////////////////////

print '\nLoading Global Tag: ' + samp.GT
process.GlobalTag.globaltag = samp.GT

# /////////////////////////////////
# Additional jet energy corrections
# /////////////////////////////////

## See https://twiki.cern.ch/twiki/bin/view/CMS/JECDataMC
## and https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookJetEnergyCorrections

from CondCore.DBCommon.CondDBSetup_cfi import CondDBSetup
if samp.isData:
  jec_db_file = 'sqlite_fip:Ntupliser/DiMuons/data/JEC/Autumn18_RunABCD_V8_DATA.db'
  jec_tag = 'JetCorrectorParametersCollection_Autumn18_RunABCD_V8_DATA_AK4PFchs'
else: 
  jec_db_file = 'sqlite_fip:Ntupliser/DiMuons/data/JEC/Autumn18_V8_MC.db'
  jec_tag = 'JetCorrectorParametersCollection_Autumn18_V8_MC_AK4PFchs'

process.jec = cms.ESSource('PoolDBESSource',
    CondDBSetup,
    connect = cms.string(jec_db_file),
    toGet = cms.VPSet(
       cms.PSet(
            record = cms.string('JetCorrectionsRecord'),
            tag    = cms.string(jec_tag),
            label  = cms.untracked.string('slimmedJets')
        ),
        # ...and so on for all jet types you need
    )
)

## Add an ESPrefer to override JEC that might be available from the global tag
process.es_prefer_jec = cms.ESPrefer('PoolDBESSource', 'jec')


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

## Following https://twiki.cern.ch/twiki/bin/view/CMS/MissingETUncertaintyPrescription
##   - Last check that procedure was up-to-date: March 10, 2017 (AWB)

## First need to run: git cms-merge-topic cms-met:METRecipe_8020 -u
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


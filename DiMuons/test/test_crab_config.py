# =============================================================#
# X2MuMuAnalyzer configuration file                            #
# =============================================================#

import FWCore.ParameterSet.Config as cms

process = cms.Process("dimuons")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.load('Configuration.EventContent.EventContent_cff')
process.load('Configuration.StandardSequences.Services_cff')
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")

# /////////////////////////////////////////////////////////////
# Get a sample from our collection of samples
# /////////////////////////////////////////////////////////////

from python.Samples_2017_94X_v2 import H2Mu_gg_125_NLO as samp

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
## Get list of local files from the sample we loaded (not used in crab)
readFiles.extend(samp.files);

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000) )
process.MessageLogger.cerr.FwkReport.reportEvery = 100
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
# Load electron IDs
# /////////////////////////////////////////////////////////////

## Following https://twiki.cern.ch/twiki/bin/view/CMS/EgammaPostRecoRecipes#Running_on_2017_MiniAOD_V2
## More complete recipe documentation: https://twiki.cern.ch/twiki/bin/view/CMS/MultivariateElectronIdentificationRun2
##               - In particular here: https://twiki.cern.ch/twiki/bin/view/CMS/MultivariateElectronIdentificationRun2#VID_based_recipe_provides_pass_f
from RecoEgamma.EgammaTools.EgammaPostRecoTools import setupEgammaPostRecoSeq
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')

setupEgammaPostRecoSeq( 
  process,
  runVID = True ,  ## Needed for 2017 V2 IDs
  era    = '2017-Nov17ReReco' 
  )

# /////////////////////////////////////////////////////////////
# Correct MET from EE noise
# /////////////////////////////////////////////////////////////
# More info on https://indico.cern.ch/event/759372/contributions/3149378/attachments/1721436/2802416/metreport.pdf

from PhysicsTools.PatUtils.tools.runMETCorrectionsAndUncertainties import runMetCorAndUncFromMiniAOD

runMetCorAndUncFromMiniAOD (
  process,
  isData = samp.isData,
  fixEE2017 = True,
  fixEE2017Params = {'userawPt':True,'ptThreshold':50.0,'minEtaThreshold':2.65,'maxEtaThreshold':3.139},
  postfix = "ModifiedMET"
  )

# /////////////////////////////////////////////////////////////
# Load Analyzer
# /////////////////////////////////////////////////////////////

if samp.isData:
  process.load("Ntupliser.DiMuons.Analyzer_cff")
else:
  process.load("Ntupliser.DiMuons.Analyzer_MC_cff")

# /////////////////////////////////////////////////////////////
# Electron Cut Based IDs
# /////////////////////////////////////////////////////////////

## Following https://twiki.cern.ch/twiki/bin/view/CMS/EgammaPostRecoRecipes#Running_on_2017_MiniAOD_V2
## More complete recipe documentation: https://twiki.cern.ch/twiki/bin/view/CMS/MultivariateElectronIdentificationRun2
##               - In particular here: https://twiki.cern.ch/twiki/bin/view/CMS/MultivariateElectronIdentificationRun2#VID_based_recipe_provides_pass_f

from RecoEgamma.EgammaTools.EgammaPostRecoTools import setupEgammaPostRecoSeq
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')

setupEgammaPostRecoSeq( process,
                        runVID = True ,  ## Needed for 2017 V2 IDs
                        era    = '2017-Nov17ReReco' )
 
# /////////////////////////////////////////////////////////////
# Set the order of operations
# /////////////////////////////////////////////////////////////
    
process.p = cms.Path( 
  process.egammaPostRecoSeq *
  process.fullPatMetSequenceModifiedMET *
  process.dimuons )


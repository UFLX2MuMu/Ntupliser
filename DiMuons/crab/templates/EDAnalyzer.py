# =============================================================#
# X2MuMuAnalyzer configuration file                            #
# =============================================================#

import FWCore.ParameterSet.Config as cms

process = cms.Process("dimuons")

process.load('FWCore.MessageService.MessageLogger_cfi')

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

# /////////////////////////////////////////////////////////////
# ------------ PoolSource -------------
# /////////////////////////////////////////////////////////////

readFiles = cms.untracked.vstring();
# Get list of files from the sample we loaded
readFiles.extend(samp.files);

# readFiles.extend(['file:dy_jetsToLL.root']);

# readFiles.extend(['root://cms-xrd-global.cern.ch//store/mc/RunIISpring16MiniAODv2/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/50000/000FF6AC-9F2A-E611-A063-0CC47A4C8EB0.root']);

# /////////////////////////////////////////////////////////////
# Save output with TFileService
# /////////////////////////////////////////////////////////////


# /////////////////////////////////////////////////////////////
# L1 Prefiring maps
# from https://twiki.cern.ch/twiki/bin/viewauth/CMS/L1ECALPrefiringWeightRecipe
# /////////////////////////////////////////////////////////////

from PhysicsTools.PatUtils.l1ECALPrefiringWeightProducer_cfi import l1ECALPrefiringWeightProducer
process.prefiringweight = l1ECALPrefiringWeightProducer.clone(
    DataEra = cms.string("2016BtoH"),
    UseJetEMPt = cms.bool(False),
    PrefiringRateSystematicUncty = cms.double(0.2),
    SkipWarnings = False)

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
  process.prefiringweight *
  process.egammaPostRecoSeq *
  process.fullPatMetSequenceModifiedMET *
  process.dimuons )


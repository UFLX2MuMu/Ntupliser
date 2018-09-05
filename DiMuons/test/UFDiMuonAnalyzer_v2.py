# =============================================================#
# UFDiMuonsAnalyzer                                             #
# =============================================================#
# Makes stage1 trees.                                          #
# Adds a cleaner vector of jets to each event.                 #
# Originally Made by Justin Hugon. Edited by Andrew Carnes.    #
#                                                              #
################################################################ 

# /////////////////////////////////////////////////////////////
# Load some things
# /////////////////////////////////////////////////////////////

#Add new comment to test push

import FWCore.ParameterSet.Config as cms

process = cms.Process("UFDiMuonsAnalyzer")

process.load("Configuration.StandardSequences.MagneticField_38T_cff")
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 100
##process.MessageLogger.destinations.append("detailedInfo")
##process.MessageLogger.detailedInfo = cms.untracked.PSet(
##    threshold = cms.untracked.string("INFO"),
##    categories = cms.untracked.vstring("UFHLTTests")
##)


## Geometry and Detector Conditions (needed for a few patTuple production steps)
process.load("Configuration.Geometry.GeometryIdeal_cff")
process.load('Configuration.EventContent.EventContent_cff')
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")

# /////////////////////////////////////////////////////////////
# Get a sample from our collection of samples
# /////////////////////////////////////////////////////////////

#from Samples_v2 import doubleMuon_RunB_MINIAOD as s
from Samples_v3 import dy_jetsToLL as s

thisIsData = s.isData

print ""
print ""
if thisIsData:
    print 'Running over data sample'
else:
    print 'Running over MC sample'

print "Sample Name:    " +  s.name
print "Sample DAS DIR: " +  s.dir
print ""
print ""

# /////////////////////////////////////////////////////////////
# global tag, automatically retrieved from the imported sample
# /////////////////////////////////////////////////////////////

globalTag = s.globaltag

#process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff")

print 'Loading Global Tag: ' + globalTag
process.GlobalTag.globaltag = globalTag

# /////////////////////////////////////////////////////////////
# ------------ PoolSource -------------
# /////////////////////////////////////////////////////////////
readFiles = cms.untracked.vstring();
# Get list of files from the sample we loaded
#readFiles.extend(s.files);

# readFiles.extend(['file:dy_jetsToLL.root']);

# readFiles.extend(['root://cms-xrd-global.cern.ch//store/mc/RunIISpring16MiniAODv2/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/50000/000FF6AC-9F2A-E611-A063-0CC47A4C8EB0.root']);

## From /GluGlu_HToMuMu_M125_13TeV_powheg_pythia8/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM
readFiles.extend(['/store/user/abrinke1/HiggsToMuMu/samples/GluGlu_HToMuMu_M125_13TeV_powheg_pythia8/PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/12B931FE-CD3A-E611-9844-0025905C3D98.root'])

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10000) )
process.source = cms.Source("PoolSource",fileNames = readFiles)
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(False) )
process.source.lumisToProcess = cms.untracked.VLuminosityBlockRange()

# use a JSON file when locally executing cmsRun
if thisIsData:
    import FWCore.PythonUtilities.LumiList as LumiList
    process.source.lumisToProcess = LumiList.LumiList(filename = s.jsonfiles[0]).getVLuminosityBlockRange()


# /////////////////////////////////////////////////////////////
# -------- Add a cleaner vector jets to each event -----------
# /////////////////////////////////////////////////////////////

## Clean the Jets from good muons, apply loose jet Id
#ccMuPreSel = "pt > 10. && isGlobalMuon "
#ccMuPreSel += " && globalTrack().normalizedChi2 < 10 "
#ccMuPreSel += " && isPFMuon "
#ccMuPreSel += " && innerTrack().hitPattern().trackerLayersWithMeasurement > 5 "
#ccMuPreSel += " && innerTrack().hitPattern().numberOfValidPixelHits > 0 "
#ccMuPreSel += " && globalTrack().hitPattern().numberOfValidMuonHits > 0 "
#ccMuPreSel += " && numberOfMatchedStations > 1 && dB < 0.2 && abs(eta) < 2.4 "
#ccMuPreSel += " && ( chargedHadronIso + max(0.,neutralHadronIso + photonIso - 0.5*puChargedHadronIso) ) < 0.12 * pt"
#
#jetSelection = 'neutralEmEnergy/energy < 0.99 '
#jetSelection += ' && neutralHadronEnergy/energy < 0.99 '
#jetSelection += ' && (chargedMultiplicity + neutralMultiplicity) > 1 '
#jetSelection += ' && ((abs(eta)>2.4) || (chargedMultiplicity > 0 '
#jetSelection += ' && chargedHadronEnergy/energy > 0.0'
#jetSelection += ' && chargedEmEnergy/energy < 0.99))'
#
#process.cleanJets = cms.EDProducer("PATJetCleaner",
#          src = cms.InputTag("slimmedJets"),
#          preselection = cms.string(jetSelection),
#          checkOverlaps = cms.PSet(
#             muons = cms.PSet(
#               src       = cms.InputTag("slimmedMuons"),
#               algorithm = cms.string("byDeltaR"),
#               preselection        = cms.string(ccMuPreSel),
#               deltaR              = cms.double(0.3),
#               checkRecoComponents = cms.bool(False),
#               pairCut             = cms.string(""),
#               requireNoOverlaps   = cms.bool(True),
#             ),
#             #electrons = cms.PSet(
#             #  src       = cms.InputTag("slimmedElectrons"),
#             #  algorithm = cms.string("byDeltaR"),
#             #  preselection        = cms.string(ccElePreSel),
#             #  deltaR              = cms.double(0.5),
#             #  checkRecoComponents = cms.bool(False),
#             #  pairCut             = cms.string(""),
#             #  requireNoOverlaps   = cms.bool(True),
#             #),
#         ),
#         finalCut = cms.string('')
#)

# /////////////////////////////////////////////////////////////
# Save output with TFileService
# /////////////////////////////////////////////////////////////

# process.TFileService = cms.Service("TFileService", fileName = cms.string("stage_1_"+s.name+"_edit_vec_10k.root") )
process.TFileService = cms.Service("TFileService", fileName = cms.string("GluGlu_HToMuMu_M125_vec_test.root") )

# /////////////////////////////////////////////////////////////
# Load UFDiMuonsAnalyzer
# /////////////////////////////////////////////////////////////

if thisIsData:
  process.load("UfHMuMuCode.UFDiMuonsAnalyzer.UFDiMuonsAnalyzer_cff")
else:
  process.load("UfHMuMuCode.UFDiMuonsAnalyzer.UFDiMuonsAnalyzer_MC_cff")

process.dimuons = process.DiMuons.clone()
# process.dimuons.jetsTag   = cms.InputTag("cleanJets")
process.dimuons.isVerbose = cms.untracked.bool(False)

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
    
## Kill electrons for now - AWB 10.11.16

# /////////////////////////////////////////////////////////////
# Set the order of operations
# /////////////////////////////////////////////////////////////
    
process.p = cms.Path(process.egmGsfElectronIDSequence*process.dimuons)

# ## Kill electrons for now - AWB 10.11.16
# process.p = cms.Path(process.dimuons)

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

import FWCore.ParameterSet.Config as cms

process = cms.Process("UFDiMuonsAnalyzer")

process.load("Configuration.StandardSequences.MagneticField_38T_cff")
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000
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

thisIsData = s.isData

print ""
print ""
if thisIsData:
    print 'Running over data sample'
else:
    print 'Running over MC sample'

print "Sample Name:    " +  s.name
print "Sample DAS DIR: " +  s.dir
if thisIsData:
    print "Sample JSON:    " +  s.jsonfiles[1]
print ""

# /////////////////////////////////////////////////////////////
# global tag, automatically retrieved from the imported sample
# /////////////////////////////////////////////////////////////

globalTag = s.globaltag

# The updated FrontierConditions_GlobalTag load needed for 2015 13TeV data does not like the ::All at the end of the tag
#if not thisIsData:
#    process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
#    globalTag+="::All"
#else:
#    process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff") 

# Newer MC global tags are consistent with data so we don't need the separate conditions
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff")

print 'Loading Global Tag: ' + globalTag
process.GlobalTag.globaltag = globalTag

# /////////////////////////////////////////////////////////////
# ------------ PoolSource -------------
# /////////////////////////////////////////////////////////////
readFiles = cms.untracked.vstring();

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.source = cms.Source("PoolSource",fileNames = readFiles)
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(False) )
process.source.lumisToProcess = cms.untracked.VLuminosityBlockRange()

# use a JSON file when locally executing cmsRun
if thisIsData:
    import FWCore.PythonUtilities.LumiList as LumiList
    process.source.lumisToProcess = LumiList.LumiList(filename = s.jsonfiles[1]).getVLuminosityBlockRange()

# /////////////////////////////////////////////////////////////
# Save output with TFileService
# /////////////////////////////////////////////////////////////

process.TFileService = cms.Service("TFileService", fileName = cms.string("stage_1_"+s.name+".root") )

# /////////////////////////////////////////////////////////////
# Load UFDiMuonAnalyzer
# /////////////////////////////////////////////////////////////

if thisIsData:
  process.load("UfHMuMuCode.UFDiMuonsAnalyzer.UFDiMuonsAnalyzer_cff")
else:
  process.load("UfHMuMuCode.UFDiMuonsAnalyzer.UFDiMuonsAnalyzer_MC_cff")

process.dimuons = process.DiMuons.clone()

# /////////////////////////////////////////////////////////////
# Electron Cut Based IDs
# /////////////////////////////////////////////////////////////

from PhysicsTools.SelectorUtils.tools.vid_id_tools import *

dataFormat = DataFormat.MiniAOD
switchOnVIDElectronIdProducer(process, dataFormat)

my_id_modules = ['RecoEgamma.ElectronIdentification.Identification.cutBasedElectronID_Summer16_80X_V1_cff'
                ]

for idmod in my_id_modules:
    setupAllVIDIdsInModule(process,idmod,setupVIDElectronSelection)

# /////////////////////////////////////////////////////////////
# Set the order of operations
# /////////////////////////////////////////////////////////////

process.p = cms.Path(process.egmGsfElectronIDSequence*process.dimuons)

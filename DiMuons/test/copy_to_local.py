# Standard import for CMSSW files
import FWCore.ParameterSet.Config as cms

# Import VarParsing
from FWCore.ParameterSet.VarParsing import VarParsing

# implement input from the shell
options = VarParsing ('analysis')
options.parseArguments()

# Must define a CMSSW process named process
process = cms.Process("ReadDatasets");
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(options.maxEvents) )

# The files to read in
readFiles = cms.untracked.vstring()


from Samples_v3 import dy_jetsToLL as s

print ""
print "Copying from " + s.name + ", " + s.dir
print ""

readFiles.extend(s.files);

print "=== Files in the sample ==="
print readFiles
print ""

# Which files to get
process.source = cms.Source ("PoolSource", fileNames = readFiles)

# Save the events to a file
process.Out = cms.OutputModule("PoolOutputModule",
#         outputCommands = cms.untracked.vstring("drop *", "keep recoTracks_*_*_*"),
         fileName = cms.untracked.string (s.name+".root")
)

# make sure everything is hooked up
process.end = cms.EndPath(process.Out)

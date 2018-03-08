import FWCore.ParameterSet.Config as cms

process = cms.Process('NoSplit')

#process.source = cms.Source("PoolSource", fileNames = cms.untracked.vstring())
process.source = cms.Source("PoolSource", fileNames = cms.untracked.vstring())

## DY
#process.source.fileNames.extend([
#  "root://cms-xrd-global.cern.ch//store/mc/Spring14miniaod/DYJetsToLL_M-50_13TeV-madgraph-pythia8-tauola_v2/MINIAODSIM/PU20bx25_POSTLS170_V5-v1/00000/00245653-EC23-E411-B9BF-02163E006C73.root",
#  "root://cms-xrd-global.cern.ch//store/mc/Spring14miniaod/DYJetsToLL_M-50_13TeV-madgraph-pythia8-tauola_v2/MINIAODSIM/PU20bx25_POSTLS170_V5-v1/00000/00826DC0-FF23-E411-ACA6-02163E00A2BC.root",
#  "root://cms-xrd-global.cern.ch//store/mc/Spring14miniaod/DYJetsToLL_M-50_13TeV-madgraph-pythia8-tauola_v2/MINIAODSIM/PU20bx25_POSTLS170_V5-v1/00000/00B40818-EF23-E411-B00D-02163E00A091.root",
#  "root://cms-xrd-global.cern.ch//store/mc/Spring14miniaod/DYJetsToLL_M-50_13TeV-madgraph-pythia8-tauola_v2/MINIAODSIM/PU20bx25_POSTLS170_V5-v1/00000/00B5C280-EE23-E411-B05F-02163E00A2BC.root",
#  "root://cms-xrd-global.cern.ch//store/mc/Spring14miniaod/DYJetsToLL_M-50_13TeV-madgraph-pythia8-tauola_v2/MINIAODSIM/PU20bx25_POSTLS170_V5-v1/00000/0219770E-0024-E411-8C7B-02163E00A091.root",
#])

### TTbar
#process.source.fileNames.extend([
#  "root://cms-xrd-global.cern.ch//store/mc/Spring14miniaod/TTJets_MSDecaysCKM_central_Tune4C_13TeV-madgraph-tauola/MINIAODSIM/PU20bx25_POSTLS170_V5-v2/00000/004C6DA7-FB03-E411-96BD-0025905A497A.root /store/mc/Spring14miniaod/TTJets_MSDecaysCKM_central_Tune4C_13TeV-madgraph-tauola/MINIAODSIM/PU20bx25_POSTLS170_V5-v2/00000/004C6DA7-FB03-E411-96BD-0025905A497A.root",
#  "root://cms-xrd-global.cern.ch//store/mc/Spring14miniaod/TTJets_MSDecaysCKM_central_Tune4C_13TeV-madgraph-tauola/MINIAODSIM/PU20bx25_POSTLS170_V5-v2/00000/00566B8C-FA03-E411-B790-0025905A60CE.root /store/mc/Spring14miniaod/TTJets_MSDecaysCKM_central_Tune4C_13TeV-madgraph-tauola/MINIAODSIM/PU20bx25_POSTLS170_V5-v2/00000/00566B8C-FA03-E411-B790-0025905A60CE.root",
#  "root://cms-xrd-global.cern.ch//store/mc/Spring14miniaod/TTJets_MSDecaysCKM_central_Tune4C_13TeV-madgraph-tauola/MINIAODSIM/PU20bx25_POSTLS170_V5-v2/00000/00600DE1-F903-E411-98B8-0025905A608C.root /store/mc/Spring14miniaod/TTJets_MSDecaysCKM_central_Tune4C_13TeV-madgraph-tauola/MINIAODSIM/PU20bx25_POSTLS170_V5-v2/00000/00600DE1-F903-E411-98B8-0025905A608C.root",
#  "root://cms-xrd-global.cern.ch//store/mc/Spring14miniaod/TTJets_MSDecaysCKM_central_Tune4C_13TeV-madgraph-tauola/MINIAODSIM/PU20bx25_POSTLS170_V5-v2/00000/006F31B7-FA03-E411-A101-0025905A60D2.root /store/mc/Spring14miniaod/TTJets_MSDecaysCKM_central_Tune4C_13TeV-madgraph-tauola/MINIAODSIM/PU20bx25_POSTLS170_V5-v2/00000/006F31B7-FA03-E411-A101-0025905A60D2.root",
#  "root://cms-xrd-global.cern.ch//store/mc/Spring14miniaod/TTJets_MSDecaysCKM_central_Tune4C_13TeV-madgraph-tauola/MINIAODSIM/PU20bx25_POSTLS170_V5-v2/00000/0088CFB8-FB03-E411-8995-002618943869.root /store/mc/Spring14miniaod/TTJets_MSDecaysCKM_central_Tune4C_13TeV-madgraph-tauola/MINIAODSIM/PU20bx25_POSTLS170_V5-v2/00000/0088CFB8-FB03-E411-8995-002618943869.root",
#  "root://cms-xrd-global.cern.ch//store/mc/Spring14miniaod/TTJets_MSDecaysCKM_central_Tune4C_13TeV-madgraph-tauola/MINIAODSIM/PU20bx25_POSTLS170_V5-v2/00000/00E3BD46-F703-E411-AEBD-0025905A60D6.root /store/mc/Spring14miniaod/TTJets_MSDecaysCKM_central_Tune4C_13TeV-madgraph-tauola/MINIAODSIM/PU20bx25_POSTLS170_V5-v2/00000/00E3BD46-F703-E411-AEBD-0025905A60D6.root",
#  "root://cms-xrd-global.cern.ch//store/mc/Spring14miniaod/TTJets_MSDecaysCKM_central_Tune4C_13TeV-madgraph-tauola/MINIAODSIM/PU20bx25_POSTLS170_V5-v2/00000/021A04AA-F603-E411-AA4D-0025905A6056.root /store/mc/Spring14miniaod/TTJets_MSDecaysCKM_central_Tune4C_13TeV-madgraph-tauola/MINIAODSIM/PU20bx25_POSTLS170_V5-v2/00000/021A04AA-F603-E411-AA4D-0025905A6056.root",
#  "root://cms-xrd-global.cern.ch//store/mc/Spring14miniaod/TTJets_MSDecaysCKM_central_Tune4C_13TeV-madgraph-tauola/MINIAODSIM/PU20bx25_POSTLS170_V5-v2/00000/0236A717-F703-E411-942A-002354EF3BE4.root /store/mc/Spring14miniaod/TTJets_MSDecaysCKM_central_Tune4C_13TeV-madgraph-tauola/MINIAODSIM/PU20bx25_POSTLS170_V5-v2/00000/0236A717-F703-E411-942A-002354EF3BE4.root",
#  "root://cms-xrd-global.cern.ch//store/mc/Spring14miniaod/TTJets_MSDecaysCKM_central_Tune4C_13TeV-madgraph-tauola/MINIAODSIM/PU20bx25_POSTLS170_V5-v2/00000/02574403-F803-E411-8BBF-0025905A60C6.root /store/mc/Spring14miniaod/TTJets_MSDecaysCKM_central_Tune4C_13TeV-madgraph-tauola/MINIAODSIM/PU20bx25_POSTLS170_V5-v2/00000/02574403-F803-E411-8BBF-0025905A60C6.root",
#  "root://cms-xrd-global.cern.ch//store/mc/Spring14miniaod/TTJets_MSDecaysCKM_central_Tune4C_13TeV-madgraph-tauola/MINIAODSIM/PU20bx25_POSTLS170_V5-v2/00000/0263877E-F603-E411-A1D0-0025905B8562.root /store/mc/Spring14miniaod/TTJets_MSDecaysCKM_central_Tune4C_13TeV-madgraph-tauola/MINIAODSIM/PU20bx25_POSTLS170_V5-v2/00000/0263877E-F603-E411-A1D0-0025905B8562.root",
#  "root://cms-xrd-global.cern.ch//store/mc/Spring14miniaod/TTJets_MSDecaysCKM_central_Tune4C_13TeV-madgraph-tauola/MINIAODSIM/PU20bx25_POSTLS170_V5-v2/00000/02711447-F703-E411-AA3C-0025905A6136.root /store/mc/Spring14miniaod/TTJets_MSDecaysCKM_central_Tune4C_13TeV-madgraph-tauola/MINIAODSIM/PU20bx25_POSTLS170_V5-v2/00000/02711447-F703-E411-AA3C-0025905A6136.root",
#  "root://cms-xrd-global.cern.ch//store/mc/Spring14miniaod/TTJets_MSDecaysCKM_central_Tune4C_13TeV-madgraph-tauola/MINIAODSIM/PU20bx25_POSTLS170_V5-v2/00000/02937394-F603-E411-BDA2-0025905AA9CC.root /store/mc/Spring14miniaod/TTJets_MSDecaysCKM_central_Tune4C_13TeV-madgraph-tauola/MINIAODSIM/PU20bx25_POSTLS170_V5-v2/00000/02937394-F603-E411-BDA2-0025905AA9CC.root",
#])

### gg->H->mumu
#process.source.fileNames.extend([
#"/store/mc/Spring14miniaod/GluGluToHToMuMu_M-125_13TeV-powheg-pythia6/MINIAODSIM/PU20bx25_POSTLS170_V5-v1/30000/78D10A0D-DC18-E411-A4ED-001E67248688.root",
#"/store/mc/Spring14miniaod/GluGluToHToMuMu_M-125_13TeV-powheg-pythia6/MINIAODSIM/PU20bx25_POSTLS170_V5-v1/30000/9E87F3BB-DB18-E411-B812-001E67248688.root",
#"/store/mc/Spring14miniaod/GluGluToHToMuMu_M-125_13TeV-powheg-pythia6/MINIAODSIM/PU20bx25_POSTLS170_V5-v1/30000/ECD0F207-DB18-E411-AAF2-001E67248688.root",
#])

### VBF H->mumu
#process.source.fileNames.extend([
#"root://cms-xrd-global.cern.ch//store/mc/Spring14miniaod/VBF_HToMuMu_M-125_13TeV-powheg-pythia6/MINIAODSIM/PU20bx25_POSTLS170_V5-v1/30000/28AE675C-DA18-E411-9043-00259048AC98.root",
#"root://cms-xrd-global.cern.ch//store/mc/Spring14miniaod/VBF_HToMuMu_M-125_13TeV-powheg-pythia6/MINIAODSIM/PU20bx25_POSTLS170_V5-v1/30000/568DCA64-DA18-E411-B85A-00259048A862.root",
#"root://cms-xrd-global.cern.ch//store/mc/Spring14miniaod/VBF_HToMuMu_M-125_13TeV-powheg-pythia6/MINIAODSIM/PU20bx25_POSTLS170_V5-v1/30000/B87E2E49-DA18-E411-BCD3-00259029E888.root",
#])

## WH,ZH->mumu
process.source.fileNames.extend([
"root://cms-xrd-global.cern.ch//store/mc/Spring14miniaod/WH_ZH_HToMuMu_M-125_13TeV_pythia6/MINIAODSIM/PU20bx25_POSTLS170_V5-v1/00000/0873FD03-FF07-E411-B320-001E673968A6.root",
"root://cms-xrd-global.cern.ch//store/mc/Spring14miniaod/WH_ZH_HToMuMu_M-125_13TeV_pythia6/MINIAODSIM/PU20bx25_POSTLS170_V5-v1/00000/2C2768CB-FE07-E411-B0BE-002590A3C96E.root",
"root://cms-xrd-global.cern.ch//store/mc/Spring14miniaod/WH_ZH_HToMuMu_M-125_13TeV_pythia6/MINIAODSIM/PU20bx25_POSTLS170_V5-v1/00000/C68BF09E-FE07-E411-AE36-001E67396F9A.root",
])


process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(2000))
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))
process.output = cms.OutputModule("PoolOutputModule",
    #outputCommands = cms.untracked.vstring("drop *", "keep recoTracks_*_*_*"),
    #fileName = cms.untracked.string('output.root'),
    #fileName = cms.untracked.string('DYJetsToLL_M-50_13TeV-madgraph-pythia8-tauola_v2-Spring14miniaod-PU20bx25_POSTLS170_V5-v1.root'),
    #fileName = cms.untracked.string('TTJets_MSDecaysCKM_central_Tune4C_13TeV-madgraph-tauola-Spring14miniaod-PU20bx25_POSTLS170_V5-v2.root'),
    #fileName = cms.untracked.string('GluGluToHToMuMu_M-125_13TeV-powheg-pythia6-Spring14miniaod-PU20bx25_POSTLS170_V5-v1.root'),
    #fileName = cms.untracked.string('VBF_HToMuMu_M-125_13TeV-powheg-pythia6-Spring14miniaod-PU20bx25_POSTLS170_V5-v1.root'),
    fileName = cms.untracked.string('WH_ZH_HToMuMu_M-125_13TeV_pythia6-Spring14miniaod-PU20bx25_POSTLS170_V5-v1.root'),
)
process.out = cms.EndPath(process.output)

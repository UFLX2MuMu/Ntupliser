# some good idea and code snippets from https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookMiniAOD2014#Trigger

import ROOT
ROOT.gROOT.SetBatch(1)

# load FWLite C++ libraries
ROOT.gSystem.Load("libFWCoreFWLite.so");
ROOT.gSystem.Load("libDataFormatsFWLite.so");
ROOT.FWLiteEnabler.enable()
ROOT.AutoLibraryLoader.enable()

# load FWlite python libraries
from DataFormats.FWLite import Handle, Events

#filein=["/eos/cms//store/data/Run2017B/SingleMuon/MINIAOD/17Nov2017-v1/70000/E4FB2B00-82D8-E711-9BEB-02163E014410.root"]
#filein=["/eos/cms/store/mc/RunIIFall17MiniAODv2/WZTo3LNu_3Jets_MLL-50_TuneCP5_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/00000/369C3391-F858-E811-9895-FA163EA77A9B.root"]
filein=['/eos/cms//store/user/bortigno/mc_genproduction/darkphoton/LHE-MINIAODSIM/ZD_UpTo2j_MZD125_Eps2e-2_v0/ZD_UpTo2j_MZD125_Eps2e-2/RunIISummer17PrePremix-MC_v2_94X_mc2017_realistic_v11LHE-MINIAODSIM/180525_114650/0000/darkphoton_miniaodsim_299.root']

events=Events(filein, maxEvents=1)

handleTrigRes = Handle("edm::TriggerResults")

#labels=["RECO","SIM","PAT","HLT"]
labels=["RECO","HLT"]
for label in labels:
  events.getByLabel(("TriggerResults","",label), handleTrigRes)
  print("======= "+label+" =======")

  for ev in events:
    trNames=ev.object().triggerNames(handleTrigRes.product())
    for i in range(0,handleTrigRes.product().size()):
      print(trNames.triggerName(i))


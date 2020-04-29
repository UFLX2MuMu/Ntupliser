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

filein=["/eos/cms//store/data/Run2017F/SingleMuon/MINIAOD/31Mar2018-v1/00003/002E160D-7437-E811-A5A4-0025904886E6.root"]


#filein=["/eos/cms/store/mc/RunIIFall17MiniAOD/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PU2017_94X_mc2017_realistic_v11_ext1-v1/00000/1C18929B-FF90-E811-976C-02163E014BB0.root"]
#filein=['/eos/cms//store/user/bortigno/mc_genproduction/darkphoton/LHE-MINIAODSIM/ZD_UpTo2j_MZD125_Eps2e-2_v0/ZD_UpTo2j_MZD125_Eps2e-2/RunIISummer17PrePremix-MC_v2_94X_mc2017_realistic_v11LHE-MINIAODSIM/180525_114650/0000/darkphoton_miniaodsim_299.root']

events=Events(filein, maxEvents=1)

handleEvFlags = Handle("edm::TriggerResults")

#labels=["RECO","SIM","PAT"]
labels=["RECO"] # flags are in RECO for data and the ZD private production, while they are in PAT for Fall17 MC production - remove HLT as there are only triggers there.
for label in labels:
  events.getByLabel(("TriggerResults","",label), handleEvFlags)
  print("======= "+label+" =======")

  for ev in events:
    flagNames=ev.object().triggerNames(handleEvFlags.product())
    for i in range(0,handleEvFlags.product().size()):
      print(flagNames.triggerName(i)) 
      #print(flagNames.triggerName(i) + " ; accept = " + str(handleEvFlags.product().accept(i)))


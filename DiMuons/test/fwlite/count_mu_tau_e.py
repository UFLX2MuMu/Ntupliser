#!/usr/bin/env python
# import ROOT in batch mode
import sys
import ROOT

oldargv = sys.argv[:]
sys.argv = [ '-b-' ]

ROOT.gROOT.SetBatch(True)
sys.argv = oldargv

# load FWLite C++ libraries
ROOT.gSystem.Load("libFWCoreFWLite.so");
ROOT.gSystem.Load("libDataFormatsFWLite.so");
ROOT.FWLiteEnabler.enable()

# load FWlite python libraries
from DataFormats.FWLite import Handle, Events

def isAncestor(a,p) :
        if a == p : 
                return True
        for i in xrange(0,p.numberOfMothers()) :
                if isAncestor(a,p.mother(i)) :
                         return True
        return False

def hasMotherWithId(p, id):
    #print "hasMotherWithId ", id
    for i in xrange(0,p.numberOfMothers()):
            part = p.mother(i)
            if abs(part.pdgId()) == id:
                print "****mother: pdg %5d, status: %3d, pt %4.1f, eta %+5.2f,  phi %+4.2f, mass %+5.2f," % (
                    part.pdgId(), part.status(), part.pt(), part.eta(), part.phi(), part.mass())
                return True
    return False

def printMothers(p):
    for i in xrange(0,p.numberOfMothers()):
            part = p.mother(i)
            print "    mother: pdg %5d, status: %3d, pt %4.1f, eta %+5.2f,  phi %+4.2f, mass %+5.2f," % (
                part.pdgId(), part.status(), part.pt(), part.eta(), part.phi(), part.mass())

def isGammaFromMuFromZ(p):
    for i in xrange(0, p.numberOfMothers()):
        part = p.mother(i)
        if abs(part.pdgId()) == 13:
            print "****mother: pdg %5d, status: %3d, pt %4.1f, eta %+5.2f,  phi %+4.2f, mass %+5.2f," % (
                part.pdgId(), part.status(), part.pt(), part.eta(), part.phi(), part.mass())
            return hasMotherWithId(part, 23)
    return False
    
muons, muonLabel = Handle("std::vector<pat::Muon>"), "slimmedMuons"
electrons, electronLabel = Handle("std::vector<pat::Electron>"), "slimmedElectrons"
photons, photonLabel = Handle("std::vector<pat::Photon>"), "slimmedPhotons"
taus, tauLabel = Handle("std::vector<pat::Tau>"), "slimmedTaus"
jets, jetLabel = Handle("std::vector<pat::Jet>"), "slimmedJets"
fatjets, fatjetLabel = Handle("std::vector<pat::Jet>"), "slimmedJetsAK8"
mets, metLabel = Handle("std::vector<pat::MET>"), "slimmedMETs"
vertices, vertexLabel = Handle("std::vector<reco::Vertex>"), "offlineSlimmedPrimaryVertices"
packedGenParts, packedGenPartLabel = Handle("std::vector<pat::PackedGenParticle>"), "packedGenParticles"
prunedGenParts, prunedGenPartLabel = Handle("std::vector<reco::GenParticle>"), "prunedGenParticles"

# open file (you can use 'edmFileUtil -d /store/whatever.root' to get the physical file name)
#events = Events("root://eoscms//eos/cms/store/cmst3/user/gpetrucc/miniAOD/v1/TT_Tune4C_13TeV-pythia8-tauola_PU_S14_PAT.root")
events = Events('../dy_jetsToLL.root')

numZ = 0;
numTauFromZ = 0;
numElectronFromZ = 0;
numMuFromZ = 0;

for iev,event in enumerate(events):

    if iev >= 2000: break
    event.getByLabel(packedGenPartLabel,packedGenParts)
    event.getByLabel(prunedGenPartLabel,prunedGenParts)

    print "\nEvent %d: run %6d, lumi %4d, event %12d" % (iev,event.eventAuxiliary().run(), event.eventAuxiliary().luminosityBlock(),event.eventAuxiliary().event())


    for i,part in enumerate(prunedGenParts.product()):
        if(abs(part.pdgId()) == 11 or abs(part.pdgId()) == 13 or abs(part.pdgId()) == 15 or abs(part.pdgId() == 23)):
            print "prunedPart %3d: pdg %5d, status: %3d, pt %4.1f, eta %+5.2f,  phi %+4.2f, mass %+5.2f," % (
                i, part.pdgId(), part.status(), part.pt(), part.eta(), part.phi(), part.mass())
            printMothers(part)

            if part.pdgId() == 23 and part.status() == 62:
                numZ+=1

            if hasMotherWithId(part, 23) and abs(part.pdgId()) == 15:
                numTauFromZ+=1

            if hasMotherWithId(part, 23) and abs(part.pdgId()) == 11:
                numElectronFromZ+=1

            if hasMotherWithId(part, 23) and abs(part.pdgId()) == 13:
                numMuFromZ+=1

    for i,part in enumerate(packedGenParts.product()):
        if(abs(part.pdgId()) == 11 or abs(part.pdgId()) == 13 or abs(part.pdgId()) == 15 or abs(part.pdgId() == 23)):
            print "packedPart %3d: pdg %5d, status: %3d, pt %4.1f, eta %+5.2f,  phi %+4.2f, mass %+5.2f," % (
                i, part.pdgId(), part.status(), part.pt(), part.eta(), part.phi(), part.mass())
            printMothers(part)

print ""
print "num Z               :", numZ
print "num muons from Z    :", numMuFromZ
print "num tau from Z      :", numTauFromZ
print "num electrons from Z:", numElectronFromZ
print ""

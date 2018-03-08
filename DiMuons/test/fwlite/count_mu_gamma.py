#!/usr/bin/env python

# import ROOT in batch mode
import sys
oldargv = sys.argv[:]
sys.argv = [ '-b-' ]
import ROOT
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

numZ22 = 0
numZ62 = 0
numZ = 0

numMu = 0
numMu23 = 0
numMu1 = 0

numGamma = 0
numGamma22 = 0
numGamma62 = 0
numGamma23 = 0

numGammaFromMu = 0
numMuFromZ = 0
numMuFromMu = 0
numGammaFromMuFromZ = 0
numGammaFromZ = 0

Z = []

for iev,event in enumerate(events):

    if iev >= 2000: break
    event.getByLabel(packedGenPartLabel,packedGenParts)
    event.getByLabel(prunedGenPartLabel,prunedGenParts)

    print "\nEvent %d: run %6d, lumi %4d, event %12d" % (iev,event.eventAuxiliary().run(), event.eventAuxiliary().luminosityBlock(),event.eventAuxiliary().event())

    for i,part in enumerate(prunedGenParts.product()): 
        if(abs(part.pdgId()) == 13 or abs(part.pdgId()) == 23):
            print "prunedPart %3d: pdg %5d, status: %3d, pt %4.1f, eta %+5.2f,  phi %+4.2f, mass %+5.2f," % (
                i, part.pdgId(), part.status(), part.pt(), part.eta(), part.phi(), part.mass())

        if(abs(part.pdgId()) == 23):
            if(part.status() == 22):
                numZ22+=1
                numZ+=1
            if(part.status() == 62):
                numZ62+=1
                numZ+=1
                Z.append(part)
                printMothers(part)
        
        if(abs(part.pdgId()) == 13):
            if(part.status() == 23):
                printMothers(part)
                numMu23+=1
                numMu+=1
                if hasMotherWithId(part, 23):
                    numMuFromZ+=1

        if(abs(part.pdgId()) == 22):
            if part.status() != 1:
                print "!! photon status = ", part.status()
            if(part.status() == 22):
                numGamma22+=1
                numGamma+=1
            if(part.status() == 62):
                numGamma62+=1
                numGamma+=1
            if(part.status() == 23):
                numGamma23+=1
                numGamma+=1


    for i,part in enumerate(packedGenParts.product()): 
        if(abs(part.pdgId()) == 13 or abs(part.pdgId()) == 23):
            print "packedPart %3d: pdg %5d, status: %3d, pt %4.1f, eta %+5.2f,  phi %+4.2f, mass %+5.2f," % (
                i, part.pdgId(), part.status(), part.pt(), part.eta(), part.phi(), part.mass())

        if(abs(part.pdgId()) == 13):
            if(part.status() == 1):
                printMothers(part)
                numMu1+=1
                numMu+=1
                if hasMotherWithId(part, 23):
                    numMuFromZ+=1
                if hasMotherWithId(part, 13):
                    numMuFromMu+=1

        if(abs(part.pdgId()) == 22):
            print "packedPart %3d: pdg %5d, status: %3d, pt %4.1f, eta %+5.2f,  phi %+4.2f, mass %+5.2f," % (
                i, part.pdgId(), part.status(), part.pt(), part.eta(), part.phi(), part.mass())
            printMothers(part)
            if part.status() != 1:
                print "!! photon status = ", part.status()
            else:
                numGamma+=1
            if isGammaFromMuFromZ(part):
                numGammaFromMuFromZ+=1
            if hasMotherWithId(part, 23):
                numGammaFromZ+=1

print " "
print "numZ:   ", numZ
print "numZ62: ", numZ62
print "numZ22: ", numZ22
print " "
print "numMu:   ", numMu
print "numMu1:  ", numMu1
print "numMu23: ", numMu23
print " "
print "numGamma: ", numGamma
print "numGamma62: ", numGamma62
print "numGamma22: ", numGamma22
print "numGamma23: ", numGamma23
print " "

print "numMuFromZ:  ", numMuFromZ
print "numGammaFromMuFromZ: ", numGammaFromMuFromZ
print "numGammaFromZ: ", numGammaFromZ
print " "

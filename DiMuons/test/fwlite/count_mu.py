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


def isParticleFromMuFromZ(p):
    for i in xrange(0, p.numberOfMothers()):
        part = p.mother(i)
        if abs(part.pdgId()) == 13:
            print "****mother: pdg %5d, status: %3d, pt %4.1f, eta %+5.2f,  phi %+4.2f, mass %+5.2f," % (
                part.pdgId(), part.status(), part.pt(), part.eta(), part.phi(), part.mass())
            return hasMotherWithId(part, 23)
    return False
    
def printDaughters(p):
    for i in xrange(0,p.numberOfDaughters()):
            part = p.daughter(i)
            print "    daughter: pdg %5d, status: %3d, pt %4.1f, eta %+5.2f,  phi %+4.2f, mass %+5.2f," % (
                part.pdgId(), part.status(), part.pt(), part.eta(), part.phi(), part.mass())

def hasStableDaughterWithId(p, id):
    #print "hasMotherWithId ", id
    for i in xrange(0,p.numberOfDaughters()):
            part = p.daughter(i)
            if abs(part.pdgId()) == id and part.status() == 1:
                print "****daughter: pdg %5d, status: %3d, pt %4.1f, eta %+5.2f,  phi %+4.2f, mass %+5.2f," % (
                    part.pdgId(), part.status(), part.pt(), part.eta(), part.phi(), part.mass())
                return True
    return False

def hasDaughterWithId(p, id):
    #print "hasMotherWithId ", id
    for i in xrange(0,p.numberOfDaughters()):
            part = p.daughter(i)
            if abs(part.pdgId()) == id:
                print "****daughter: pdg %5d, status: %3d, pt %4.1f, eta %+5.2f,  phi %+4.2f, mass %+5.2f," % (
                    part.pdgId(), part.status(), part.pt(), part.eta(), part.phi(), part.mass())
                return True
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
numMuFromZother = 0
numMu1 = 0

numMuFromZ = 0
numMuFromMu = 0

numNotPostFSR = 0
numPostFSR = 0

numNotPreFSR = 0
numPreFSR = 0

numPreAndPost = 0
numTotal = 0

numPre = 0

numNotZMuon = 0

mucount = [0,0,0,0,0,0,0,0,0,0,0]
numPairs = 0

for iev,event in enumerate(events):

    if iev >= 2000: break
    event.getByLabel(muonLabel, muons)
    event.getByLabel(packedGenPartLabel,packedGenParts)
    event.getByLabel(prunedGenPartLabel,prunedGenParts)

    print "\nEvent %d: run %6d, lumi %4d, event %12d" % (iev,event.eventAuxiliary().run(), event.eventAuxiliary().luminosityBlock(),event.eventAuxiliary().event())

    evNumMuPlus = 0;
    evNumMuMinus = 0;

    evNumMuons = 0
    evNumPreFSR = 0
    evNumPostFSR = 0
    evNumNotZMuon = 0
    foundZ = False

    # Muons
    for i,mu in enumerate(muons.product()): 
        #if mu.pt() >= 5 and mu.isLooseMuon(): evNumMuons+=1
        if mu.pt() >= 10 and abs(mu.eta()) < 2.4 and mu.isTrackerMuon(): 
            evNumMuons+=1
            if mu.charge() > 0: evNumMuPlus+=1
            if mu.charge() < 0: evNumMuMinus+=1
        #print "recomu %3d: pdg %5d, status: %3d, pt %4.1f, eta %+5.2f,  phi %+4.2f, mass %+5.2f," % (
        #    i, mu.pdgId(), mu.status(), mu.pt(), mu.eta(), mu.phi(), mu.mass())

    if evNumMuons >= 3:  
        for i,mu in enumerate(muons.product()): 
            if mu.pt() >= 10 and abs(mu.eta()) < 2.4 and mu.isTrackerMuon():
                print "recomu %3d: pdg %5d, status: %3d, pt %4.1f, eta %+5.2f,  phi %+4.2f, mass %+5.2f," % (
                    i, mu.pdgId(), mu.status(), mu.pt(), mu.eta(), mu.phi(), mu.mass())
        
#        genMuon = mu.genParticle()
#        if genMuon != None:
#            print "      Associated GenParticle pt: %4.2f eta: %4.2f phi: %4.2f deltaR: %10.8f" % (genMuon.pt(),genMuon.eta(),genMuon.phi(),((genMuon.eta()-mu.eta())**2+(genMuon.phi()-mu.phi())**2)**0.5)
#
#
#    hasMu23 = False
#    hasMu1 = False
#
#    for i,part in enumerate(prunedGenParts.product()): 
#        if(abs(part.pdgId()) == 13 or abs(part.pdgId()) == 23):
#            print "prunedPart %3d: pdg %5d, status: %3d, pt %4.1f, eta %+5.2f,  phi %+4.2f, mass %+5.2f," % (
#                i, part.pdgId(), part.status(), part.pt(), part.eta(), part.phi(), part.mass())
#
#        if(abs(part.pdgId()) == 23):
#            if(part.status() == 22):
#                numZ22+=1
#            if(part.status() == 62):
#                foundZ = True
#                numZ62+=1
#                numZ+=1
#                printDaughters(part)
#        
#        if(abs(part.pdgId()) == 13):
#            if(part.status() == 1):
#                if hasMotherWithId(part, 23):
#                    numMuFromZother+=1
#            if(part.status() == 23):
#                printMothers(part)
#                printDaughters(part)
#                numMu23+=1
#                numMu+=1
#                evNumPreFSR+=1
#                if hasMotherWithId(part, 23):
#                    numMuFromZ+=1
#                if hasStableDaughterWithId(part, part.pdgId()) and hasMotherWithId(part, 23):
#                    numMuFromZother+=1
#
#
#    for i,part in enumerate(packedGenParts.product()): 
##        if(abs(part.pdgId()) == 13 or abs(part.pdgId()) == 23):
##            print "packedPart %3d: pdg %5d, status: %3d, pt %4.1f, eta %+5.2f,  phi %+4.2f, mass %+5.2f," % (
##                i, part.pdgId(), part.status(), part.pt(), part.eta(), part.phi(), part.mass())
#
#        if(abs(part.pdgId()) == 13):
#            if(part.status() == 1):
#                numMu1+=1
#                numMu+=1
#                evNumPostFSR+=1
#                if isParticleFromMuFromZ(part):
#                    numMuFromMu+=1
#                if hasMotherWithId(part, 23):
#                    numMuFromZ+=1
#
#                if ((not hasMotherWithId(part, 23)) and (not isParticleFromMuFromZ(part))):
#                    evNumNotZMuon+=1
#                    print "Added bad muon..."
#                    print "packedPart %3d: pdg %5d, status: %3d, pt %4.1f, eta %+5.2f,  phi %+4.2f, mass %+5.2f," % (
#                        i, part.pdgId(), part.status(), part.pt(), part.eta(), part.phi(), part.mass())
#                    printMothers(part)
#
#    if( evNumPreFSR == 2 and evNumPostFSR >=2): numPreAndPost +=1
#    if( evNumPreFSR == 2): numPre += 1
#
#    if( foundZ and evNumMuons >=2 and evNumPreFSR==2 ): numPreFSR +=1
#
#    if( foundZ and evNumMuons >= 2 and evNumPostFSR==2): numPostFSR +=1
#    if( foundZ and evNumMuons >= 2 and evNumPostFSR==2 and evNumNotZMuon>=1): numNotZMuon +=1
#    if( foundZ and evNumMuons >=2): numTotal+=1

    mucount[evNumMuPlus*evNumMuMinus]+=1
    numPairs+=evNumMuPlus*evNumMuMinus

#print " "
#print "numZ:   ", numZ
#print "numZ62: ", numZ62
#print "numZ22: ", numZ22
#print " "
#print "numMu:   ", numMu
#print "numMu1:  ", numMu1
#print "numMu23: ", numMu23
#print "numMuFromZother: ", numMuFromZother
#
#print "numMuFromZ:  ", numMuFromZ
#print " "
#print "pre and post / pre", (0.0 + numPreAndPost)/numPre
#print "numPreFSR-Z-2Mu / numTotal", (0.0 + numPreFSR)/numTotal
#print "numPostFSR-Z-2Mu / numTotal", (0.0 + numPostFSR)/numTotal
#print "numNotZMuon/numPostFSR", (0.0 + numNotZMuon)/numPostFSR
print ""
print "numPairs:", numPairs
print "mucount :"
print mucount

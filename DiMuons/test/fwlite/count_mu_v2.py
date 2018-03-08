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
ROOT.gSystem.Load("libDataFormatsPatCandidates.so");
ROOT.FWLiteEnabler.enable()
#ROOT.AutoLibraryLoader.enable()

# load FWlite python libraries
from DataFormats.FWLite import Handle, Events

def isAncestor(a,p) :
        if a == p : 
                return True
        for i in xrange(0,p.numberOfMothers()) :
                if isAncestor(a,p.mother(i)) :
                         return True
        return False

def hasMotherWithIdFull(p, id, abso=True):
    #print "hasMotherWithId ", id
    if abso and abs(part.pdgId()) == id:
        return True
    if not abso and part.pdgId() == id:
        return True

    for i in xrange(0,p.numberOfMothers()):
        hasMotherWithIdFull(p.mother(i), id, abso=abso)

    return False

def hasMotherWithId(p, id, abso=True):
    #print "hasMotherWithId ", id
    for i in xrange(0,p.numberOfMothers()):
            part = p.mother(i)
            if abso and abs(part.pdgId()) == id:
                return True
            if not abso and part.pdgId() == id:
                return True
    return False

def printMothers(p):
    for i in xrange(0,p.numberOfMothers()):
            part = p.mother(i)
            print "    mother: pdg %5d, status: %3d, pt %4.1f, eta %+5.2f,  phi %+4.2f, mass %+5.2f," % (
                part.pdgId(), part.status(), part.pt(), part.eta(), part.phi(), part.mass())


def isParticleFromMuFromZ(p, abso=True):
    for i in xrange(0, p.numberOfMothers()):
        part = p.mother(i)
        if abso and abs(part.pdgId()) == 13:
            return hasMotherWithId(part, 23, abso=abso)
        if not abso and part.pdgId() == 13:
            return hasMotherWithId(part, 23, abso=abso)
    return False
    
def printDaughters(p):
    for i in xrange(0,p.numberOfDaughters()):
            part = p.daughter(i)
            print "    daughter: pdg %5d, status: %3d, pt %4.1f, eta %+5.2f,  phi %+4.2f, mass %+5.2f," % (
                part.pdgId(), part.status(), part.pt(), part.eta(), part.phi(), part.mass())

def hasStableDaughterWithId(p, id, abso=True):
    #print "hasMotherWithId ", id
    for i in xrange(0,p.numberOfDaughters()):
            part = p.daughter(i)
            if abso and abs(part.pdgId()) == id and part.status() == 1:
                return True
            if not abso and part.pdgId() == id and part.status() == 1:
                return True
    return False

def hasDaughterWithId(p, id, abso=True):
    #print "hasMotherWithId ", id
    for i in xrange(0,p.numberOfDaughters()):
            part = p.daughter(i)
            if abso and abs(part.pdgId()) == id:
                return True
            if not abso and part.pdgId() == id:
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
genjets, genjetLabel = Handle("reco::GenJetCollection"), "slimmedGenJets"

# open file (you can use 'edmFileUtil -d /store/whatever.root' to get the physical file name)
#events = Events("root://eoscms//eos/cms/store/cmst3/user/gpetrucc/miniAOD/v1/TT_Tune4C_13TeV-pythia8-tauola_PU_S14_PAT.root")
events = Events('../dy_jetsToLL.root')

numZ = 0
not_z_ll_count = 0
not_z_count = 0

numZtau = 0
numZmu = 0
numZe = 0

numElectronFromZ = 0
numMuFromZ = 0
numTauFromZ = 0

numElectronFromZpack = 0
numMuFromZpack = 0
numTauFromZpack = 0

valid_z_mumu_count = 0
gamma_ll = 0
status1_z_no_prunedZ = 0

numMuHardProcess = 0
numMuHardProcessFinalState = 0
numMuPrompt = 0

for iev,event in enumerate(events):

    if iev >= 2000: break
    event.getByLabel(muonLabel, muons)
    event.getByLabel(electronLabel, electrons)
    event.getByLabel(tauLabel, taus)
    event.getByLabel(jetLabel, jets)
    event.getByLabel(genjetLabel, genjets)
    event.getByLabel(packedGenPartLabel,packedGenParts)
    event.getByLabel(prunedGenPartLabel,prunedGenParts)

    valid_z_mu = False
    valid_z_antimu = False

    z_ll = False
    foundZ = False

    print "\nEvent %d: run %6d, lumi %4d, event %12d" % (iev,event.eventAuxiliary().run(), event.eventAuxiliary().luminosityBlock(),event.eventAuxiliary().event())

    for i,part in enumerate(prunedGenParts.product()): 
        #if(abs(part.pdgId()) == 23):
        #    print "prunedPart %3d: pdg %5d, status: %3d, pt %4.1f, eta %+5.2f,  phi %+4.2f, mass %+5.2f," % (
        #        i, part.pdgId(), part.status(), part.pt(), part.eta(), part.phi(), part.mass())

        if(abs(part.pdgId()) == 23):
            if(part.status() == 62):
                foundZ = True;
                numZ+=1
                #printDaughters(part)
                if(hasDaughterWithId(part, 11)):
                    numZe+=1
                    z_ll = True
                if(hasDaughterWithId(part, 13)):
                    numZmu+=1
                    z_ll = True
                if(hasDaughterWithId(part, 15)):
                    numZtau+=1
                    z_ll = True
        
        if(abs(part.pdgId()) == 22):
            if hasDaughterWithId(part, 11, abso=False) and hasDaughterWithId(part, -11, abso=False):
                gamma_ll+=1
            if hasDaughterWithId(part, 13, abso=False) and hasDaughterWithId(part, -13, abso=False):
                gamma_ll+=1
            if hasDaughterWithId(part, 15, abso=False) and hasDaughterWithId(part, -15, abso=False):
                gamma_ll+=1
        
        if(abs(part.pdgId()) == 11 and hasMotherWithId(part, 23)):
            numElectronFromZ+=1;

        if(abs(part.pdgId()) == 13 and hasMotherWithId(part, 23)):
            numMuFromZ+=1
            if part.pdgId() == 13 and part.pt() > 10 and abs(part.eta()) < 2.4: 
                valid_z_mu = True
            if part.pdgId() == -13 and part.pt() > 10 and abs(part.eta()) < 2.4: 
                valid_z_antimu = True
            #print "prunedPart %3d: pdg %5d, status: %3d, pt %4.1f, eta %+5.2f,  phi %+4.2f, mass %+5.2f," % (\
            #    i, part.pdgId(), part.status(), part.pt(), part.eta(), part.phi(), part.mass())
            #printDaughters(part)

        if(abs(part.pdgId()) == 15 and hasMotherWithId(part, 23)):
            numTauFromZ+=1;


    for i,part in enumerate(packedGenParts.product()): 
        #if(abs(part.pdgId()) == 13 or abs(part.pdgId()) == 23):
        #    print "packedPart %3d: pdg %5d, status: %3d, pt %4.1f, eta %+5.2f,  phi %+4.2f, mass %+5.2f," % (
        #        i, part.pdgId(), part.status(), part.pt(), part.eta(), part.phi(), part.mass())

        if(abs(part.pdgId()) == 11 and hasMotherWithId(part, 23)):
            numElectronFromZpack+=1;
            if not z_ll:
                status1_z_no_prunedZ+=1
                
        if(abs(part.pdgId()) == 13 and hasMotherWithId(part, 23)):
            numMuFromZpack+=1;
            #print "prunedPart %3d: pdg %5d, status: %3d, pt %4.1f, eta %+5.2f,  phi %+4.2f, mass %+5.2f," % (\
            #    i, part.pdgId(), part.status(), part.pt(), part.eta(), part.phi(), part.mass())
            #printDaughters(part)
            if not z_ll:
                status1_z_no_prunedZ+=1
            #if part.isHardProcess():
            #    numMuHardProcess+=1
            #if part.fromHardProcessFinalState():
            #    numMuHardProcessFinalState+=1
            #if part.isPrompt():
            #    numMuPrompt+=1
        if(abs(part.pdgId()) == 15 and hasMotherWithId(part, 23)):
            numTauFromZpack+=1;
            if not z_ll:
                status1_z_no_prunedZ+=1

    if not z_ll or not foundZ:
        if not z_ll: 
            not_z_ll_count+=1
            print ""
            print "!!! No z_ll in this event."
        if not foundZ: 
            not_z_count+=1
            print "+++ No Z at all in this event."
            print "... prunedGenParticles.size() = ", prunedGenParts.product().size()
            print "... packedGenParticles.size() = ", packedGenParts.product().size()
            print "..."
        for i,part in enumerate(prunedGenParts.product()): 
            if hasDaughterWithId(part, 11, abso=False) and hasDaughterWithId(part, -11, abso=False) and part.status() ==21:
                print "prunedPart %3d: pdg %5d, status: %3d, pt %4.1f, eta %+5.2f,  phi %+4.2f, mass %+5.2f," % (
                    i, part.pdgId(), part.status(), part.pt(), part.eta(), part.phi(), part.mass())
                printDaughters(part)
            if hasDaughterWithId(part, 13, abso=False) and hasDaughterWithId(part, -13, abso=False) and part.status() == 21:
                print "prunedPart %3d: pdg %5d, status: %3d, pt %4.1f, eta %+5.2f,  phi %+4.2f, mass %+5.2f," % (
                    i, part.pdgId(), part.status(), part.pt(), part.eta(), part.phi(), part.mass())
                printDaughters(part)
            if hasDaughterWithId(part, 15, abso=False) and hasDaughterWithId(part, -15, abso=False) and part.status() == 21:
                print "prunedPart %3d: pdg %5d, status: %3d, pt %4.1f, eta %+5.2f,  phi %+4.2f, mass %+5.2f," % (
                    i, part.pdgId(), part.status(), part.pt(), part.eta(), part.phi(), part.mass())
                printDaughters(part)

    if z_ll or foundZ:
        if z_ll: 
            print ""
            print "!!! Found z_ll in this event."
        if foundZ: 
            print "+++ Found Z in this event."
            print "... prunedGenParticles.size() = ", prunedGenParts.product().size()
            print "... packedGenParticles.size() = ", packedGenParts.product().size()
            print "..."
        for i,part in enumerate(prunedGenParts.product()): 
            if hasDaughterWithId(part, 11, abso=False) and hasDaughterWithId(part, -11, abso=False) and part.status() ==21:
                print "prunedPart %3d: pdg %5d, status: %3d, pt %4.1f, eta %+5.2f,  phi %+4.2f, mass %+5.2f," % (
                    i, part.pdgId(), part.status(), part.pt(), part.eta(), part.phi(), part.mass())
                printDaughters(part)
            if hasDaughterWithId(part, 13, abso=False) and hasDaughterWithId(part, -13, abso=False) and part.status() == 21:
                print "prunedPart %3d: pdg %5d, status: %3d, pt %4.1f, eta %+5.2f,  phi %+4.2f, mass %+5.2f," % (
                    i, part.pdgId(), part.status(), part.pt(), part.eta(), part.phi(), part.mass())
                printDaughters(part)
            if hasDaughterWithId(part, 15, abso=False) and hasDaughterWithId(part, -15, abso=False) and part.status() == 21:
                print "prunedPart %3d: pdg %5d, status: %3d, pt %4.1f, eta %+5.2f,  phi %+4.2f, mass %+5.2f," % (
                    i, part.pdgId(), part.status(), part.pt(), part.eta(), part.phi(), part.mass())
                printDaughters(part)

        #for i,part in enumerate(packedGenParts.product()): 
        #    print "packedPart %3d: pdg %5d, status: %3d, pt %4.1f, eta %+5.2f,  phi %+4.2f, mass %+5.2f," % (
        #        i, part.pdgId(), part.status(), part.pt(), part.eta(), part.phi(), part.mass())

        #for i,part in enumerate(electrons.product()): 
        #    if(abs(part.pdgId()) == 23):
        #        print "electronss %3d: pdg %5d, status: %3d, pt %4.1f, eta %+5.2f,  phi %+4.2f, mass %+5.2f," % (
        #            i, part.pdgId(), part.status(), part.pt(), part.eta(), part.phi(), part.mass())

        #for i,part in enumerate(muons.product()): 
        #    if(abs(part.pdgId()) == 23):
        #        print "muons %3d: pdg %5d, status: %3d, pt %4.1f, eta %+5.2f,  phi %+4.2f, mass %+5.2f," % (
        #            i, part.pdgId(), part.status(), part.pt(), part.eta(), part.phi(), part.mass())

        #for i,part in enumerate(taus.product()): 
        #    if(abs(part.pdgId()) == 23):
        #        print "taus %3d: pdg %5d, status: %3d, pt %4.1f, eta %+5.2f,  phi %+4.2f, mass %+5.2f," % (
        #            i, part.pdgId(), part.status(), part.pt(), part.eta(), part.phi(), part.mass())

        #for i,part in enumerate(jets.product()): 
        #    if(abs(part.pdgId()) == 23):
        #        print "jets %3d: pdg %5d, status: %3d, pt %4.1f, eta %+5.2f,  phi %+4.2f, mass %+5.2f," % (
        #            i, part.pdgId(), part.status(), part.pt(), part.eta(), part.phi(), part.mass())

        #for i,part in enumerate(genjets.product()): 
        #    if(abs(part.pdgId()) == 23):
        #        print "genjets %3d: pdg %5d, status: %3d, pt %4.1f, eta %+5.2f,  phi %+4.2f, mass %+5.2f," % (
        #            i, part.pdgId(), part.status(), part.pt(), part.eta(), part.phi(), part.mass())



    
    if valid_z_mu and valid_z_antimu:
        valid_z_mumu_count+=1

print "numZ            : ", numZ
print "not_z_ll_count  :", not_z_ll_count
print "not_z_count     :", not_z_count
print ""
print ""
print "numZe           :", numZe
print "numZmu          :", numZmu
print "numZtau         :", numZtau
print ""
print "numElectronFromZ:", numElectronFromZ/2
print "numMuFromZ      :", numMuFromZ/2
print "numTauFromZ     :", numTauFromZ/2
print ""
print "validZmumu      :", valid_z_mumu_count
print "gammaLL         :", gamma_ll
print "nums1ZnoPruneZ  :", status1_z_no_prunedZ
print ""
print "numMuHardProcess            :", numMuHardProcess 
print "numMuHardProcessFinalState  :", numMuHardProcessFinalState
print "numMuPrompt                 :", numMuPrompt
print ""
print "numElectronFromZpack:", numElectronFromZpack/2
print "numMuFromZpack      :", numMuFromZpack/2
print "numTauFromZpack     :", numTauFromZpack/2
print ""

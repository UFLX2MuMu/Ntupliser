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
ROOT.AutoLibraryLoader.enable()

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
events = Events(['dy_jetsToLL_asympt50.root'])

numGammaFromMuFromZ = 0
numPatGamma = 0
avgPatGammaPt = 0
avgGammaFromMuFromZPt = 0
matches = 0

for iev,event in enumerate(events):
    if iev >= 2000: break
    event.getByLabel(muonLabel, muons)
    event.getByLabel(electronLabel, electrons)
    event.getByLabel(photonLabel, photons)
    event.getByLabel(tauLabel, taus)
    event.getByLabel(jetLabel, jets)
    event.getByLabel(fatjetLabel, fatjets)
    event.getByLabel(metLabel, mets)
    event.getByLabel(vertexLabel, vertices)
    event.getByLabel(packedGenPartLabel,packedGenParts)
    event.getByLabel(prunedGenPartLabel,prunedGenParts)

#    print "\nEvent %d: run %6d, lumi %4d, event %12d" % (iev,event.eventAuxiliary().run(), event.eventAuxiliary().luminosityBlock(),event.eventAuxiliary().event())

#    # Muons
#    for i,mu in enumerate(muons.product()): 
#        if mu.pt() < 5 or not mu.isLooseMuon(): continue
#        print "muon %2d: pt %4.1f, eta %4.1f, dz(PV) %+5.3f, POG loose id %d, tight id %d." % (
#            i, mu.pt(), mu.eta(), mu.muonBestTrack().dz(PV.position()), mu.isLooseMuon(), mu.isTightMuon(PV))
#        #print "      Iso: CH: %4.1f NH: %4.1f NEM: %4.1f PUCH: %4.1f" % (
#        #    mu.chargedHadronIso(), mu.neutralHadronIso(), mu.photonIso(), mu.puChargedHadronIso())
#        pfRelIso = (mu.chargedHadronIso() +max(0,mu.neutralHadronIso()+mu.photonIso()-0.5*mu.puChargedHadronIso()))/mu.pt()
#        print "      PFRelIso: CH: %4.2f  TrkRelIso: %4.2f" % (pfRelIso,mu.trackIso()/mu.pt())
#        genMuon = mu.genParticle()
#        print "      Associated GenParticle pt: %4.2f eta: %4.2f phi: %4.2f deltaR: %10.8f" % (genMuon.pt(),genMuon.eta(),genMuon.phi(),((genMuon.eta()-mu.eta())**2+(genMuon.phi()-mu.phi())**2)**0.5)

#    # Electrons
#    for i,el in enumerate(electrons.product()):
#        if el.pt() < 5: continue
#        print "elec %2d: pt %4.1f, eta %4.1f, supercluster eta %+5.3f, sigmaIetaIeta %.3f (%.3f with full5x5 shower shapes), lost hits %d, pass conv veto %d" % (
#                    i, el.pt(), el.eta(), el.superCluster().eta(), el.sigmaIetaIeta(), el.full5x5_sigmaIetaIeta(), el.gsfTrack().trackerExpectedHitsInner().numberOfLostHits(), el.passConversionVeto())

    # Photon
    for i,pho in enumerate(photons.product()):
        numPatGamma+=1
        avgPatGammaPt+=pho.pt()
        genPho = pho.genPhoton()
        if genPho != None:
            if isGammaFromMuFromZ(genPho):
                print "\nEvent %d: run %6d, lumi %4d, event %12d" % (iev,event.eventAuxiliary().run(), event.eventAuxiliary().luminosityBlock(),event.eventAuxiliary().event())
                print "phot %2d: pt %4.1f, eta %4.1f, supercluster eta %+5.3f, sigmaIetaIeta %.3f (%.3f with full5x5 shower shapes)" % (
                    i, pho.pt(), pho.eta(), pho.superCluster().eta(), pho.sigmaIetaIeta(), pho.full5x5_sigmaIetaIeta())
                print "    Associated GenParticle pt: %4.2f eta: %4.2f phi: %4.2f deltaR: %10.8f" % (genPho.pt(),genPho.eta(),genPho.phi(),((genPho.eta()-pho.eta())**2+(genPho.phi()-pho.phi())**2)**0.5)
                matches+=1
#    # Tau
#    for i,tau in enumerate(taus.product()):
#        if tau.pt() < 20: continue
#        print "tau  %2d: pt %4.1f, eta %4.1f, dxy signif %.1f, ID(byMediumCombinedIsolationDeltaBetaCorr3Hits) %.1f, lead candidate pt %.1f, pdgId %d " % (
#                    i, tau.pt(), tau.eta(), tau.dxy_Sig(), tau.tauID("byMediumCombinedIsolationDeltaBetaCorr3Hits"), tau.leadCand().pt(), tau.leadCand().pdgId()) 
#
#
#    # Jets (standard AK4)
#    for i,j in enumerate(jets.product()):
#        if j.pt() < 20: continue
#        print "jet %3d: pt %5.1f (raw pt %5.1f), eta %+4.2f, btag CSV %.3f, CISV %.3f, pileup mva disc %+.2f" % (
#            i, j.pt(), j.pt()*j.jecFactor('Uncorrected'), j.eta(), max(0,j.bDiscriminator("combinedSecondaryVertexBJetTags")), max(0,j.bDiscriminator("combinedInclusiveSecondaryVertexBJetTags")), j.userFloat("pileupJetId:fullDiscriminant"))
#        if i == 0: # for the first jet, let's print the leading constituents
#            constituents = [ j.daughter(i2) for i2 in xrange(j.numberOfDaughters()) ]
#            constituents.sort(key = lambda c:c.pt(), reverse=True)
#            for i2, cand in enumerate(constituents):
#                print "         constituent %3d: pt %6.2f, dz(pv) %+.3f, pdgId %+3d" % (i2,cand.pt(),cand.dz(PV.position()),cand.pdgId()) 
#                if i2 > 3: break
#            #outStr= "User float names:"
#            #for ufn in  j.userFloatNames():
#            #   outStr += " "+ufn+" "
#            #print outStr
#
#    # Fat AK8 Jets
#    for i,j in enumerate(fatjets.product()):
#        print "jet %3d: pt %5.1f (raw pt %5.1f), eta %+4.2f, mass %5.1f ungroomed, %5.1f pruned, %5.1f trimmed, %5.1f filtered. CMS TopTagger %.1f" % (
#            i, j.pt(), j.pt()*j.jecFactor('Uncorrected'), j.eta(), j.mass(), j.userFloat('ak8PFJetsCHSPrunedLinks'), j.userFloat('ak8PFJetsCHSTrimmedLinks'), j.userFloat('ak8PFJetsCHSFilteredLinks'), j.userFloat("cmsTopTagPFJetsCHSLinksAK8"))
#
#    # MET:
#    met = mets.product().front()
#    print "MET: pt %5.1f, phi %+4.2f, sumEt (%.1f). rawMET: %.1f, genMET %.1f. MET with JES up/down: %.1f/%.1f" % (
#        met.pt(), met.phi(), met.sumEt(),
#        met.uncorrectedPt(), #<<?-- seems to return the same as pt(): help needed from JetMET experts!
#        met.genMET().pt(),
#        met.shiftedPt(ROOT.pat.MET.JetEnUp), met.shiftedPt(ROOT.pat.MET.JetEnDown));



#    for i,part in enumerate(prunedGenParts.product()): 
#        print "prunedPart %3d: pdg %5d, status: %3d, pt %4.1f, eta %+5.2f,  phi %+4.2f, mass %+5.2f," % (
#            i, part.pdgId(), part.status(), part.pt(), part.eta(), part.phi(), part.mass())

    for i,part in enumerate(packedGenParts.product()): 
        if(abs(part.pdgId()) == 22):
#            if part.status() != 1:
#                print "!! photon status = ", part.status()
            if isGammaFromMuFromZ(part):
                numGammaFromMuFromZ+=1
                avgGammaFromMuFromZPt+=part.pt()
#                print "packedPart %3d: pdg %5d, status: %3d, pt %5.3e, eta %+5.2f,  phi %+4.2f, mass %+5.2f," % (
#                    i, part.pdgId(), part.status(), part.pt(), part.eta(), part.phi(), part.mass())

avgPatGammaPt = avgPatGammaPt/numPatGamma
avgGammaFromMuFromZPt = avgGammaFromMuFromZPt/numGammaFromMuFromZ

print ""
print "numPatGamma: ", numPatGamma
print "numGammaFromMuFromZ: ", numGammaFromMuFromZ
print ""
print "avgPatGammaPt: ", avgPatGammaPt
print "avgGammaFromMuFromZPt: ", avgGammaFromMuFromZPt
print ""
print "numMatchedPhotons", matches
print ""


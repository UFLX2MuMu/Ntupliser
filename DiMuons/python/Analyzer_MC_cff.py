import FWCore.ParameterSet.Config as cms

## Assumes you are looking at miniAOD
dimuons = cms.EDAnalyzer('UFDiMuonsAnalyzer',
                         
                         isVerbose    = cms.untracked.bool(False),
                         isMonteCarlo = cms.bool(True),
                         doSys        = cms.bool(False),
                         slimOut      = cms.bool(True),

                         ## Event selection cuts
                         skim_nMuons   = cms.int32(1),
                         skim_nLeptons = cms.int32(2),
                         skim_trig     = cms.bool(True),
                         
                         processName  = cms.string("HLT"),
                         ## Triggers which were unprescaled in 2016, 2017, or 2018
                         ## 2016 : https://cmswbm.web.cern.ch/cmswbm/cmsdb/servlet/TriggerMode?KEY=l1_hlt_collisions2016/v450
                         ## 2017 : https://cmswbm.cern.ch/cmsdb/servlet/TriggerMode?KEY=l1_hlt_collisions2017/v320
                         trigNames = cms.vstring("HLT_IsoMu22_eta2p1", "HLT_IsoTkMu22_eta2p1",
                                                 "HLT_IsoMu24", "HLT_IsoTkMu24",
                                                 "HLT_IsoMu27", "HLT_IsoTkMu27",
                                                 "HLT_Mu50", "HLT_TkMu50", "HLT_TkMu100"),
                         trigResults = cms.InputTag("TriggerResults","","HLT"),
                         trigObjs    = cms.InputTag("slimmedPatTrigger"),

                         ## Event flags
                         evtFlags = cms.InputTag("TriggerResults","","RECO"),

                         ## Vertex and Beam Spot
                         primaryVertexTag = cms.InputTag("offlineSlimmedPrimaryVertices"),
                         beamSpotTag      = cms.InputTag("offlineBeamSpot"),

                         ## Muons
                         muonColl   = cms.InputTag("slimmedMuons"),
                         doSys_KaMu = cms.bool(False),
                         doSys_Roch = cms.bool(False),
                         muEffArea  = cms.FileInPath('Ntupliser/DiMuons/data/EffArea/effAreas_cone03_Muons_Fall17.txt'),

                         ## Electrons
                         eleColl     = cms.InputTag("slimmedElectrons"),
                         eleIdVeto   = cms.string("cutBasedElectronID-Fall17-94X-V2-veto"),
                         eleIdLoose  = cms.string("cutBasedElectronID-Fall17-94X-V2-loose"),
                         eleIdMedium = cms.string("cutBasedElectronID-Fall17-94X-V2-medium"),
                         eleIdTight  = cms.string("cutBasedElectronID-Fall17-94X-V2-tight"),
                         eleIdMva    = cms.string("ElectronMVAEstimatorRun2Fall17NoIsoV1Values"),
                         ## https://github.com/GhentAnalysis/heavyNeutrino/blob/master/multilep/test/multilep.py#L107
                         eleEffArea  = cms.FileInPath('RecoEgamma/ElectronIdentification/data/Fall17/effAreaElectrons_cone03_pfNeuHadronsAndPhotons_92X.txt'),

                         ## Jets
                         ## Not clear which jet tag below should be used - AWB 21.10.2018
                         jetsTag  = cms.InputTag('slimmedJets'),
                         # jetsTag  = cms.InputTag('updatedPatJetsUpdatedJEC'),
                         # jetsTag  = cms.InputTag('updatedPatJetsTransientCorrectedUpdatedJEC'),
                         jetType  = cms.string("AK4PFchs"),
                         btagName = cms.string("pfCombinedInclusiveSecondaryVertexV2BJetTags"),
                         # btagName = cms.string("pfDeepCSVJetTags"),
                         rhoTag   = cms.InputTag("fixedGridRhoFastjetAll"), ## No idea if this is right, matches TOP-18-008 - AWB 15.10.2018
                         ## https://github.com/GhentAnalysis/heavyNeutrino/blob/master/multilep/test/multilep.py#L144

                         ## PF cands
                         pfCandsTag = cms.InputTag("packedPFCandidates"),

                         ## MET
                         metTag = cms.InputTag("slimmedMETs"),

                         ## GEN particle collections
                         genJetsTag           = cms.InputTag("slimmedGenJets"),
                         prunedGenParticleTag = cms.InputTag("prunedGenParticles"),
                         packedGenParticleTag = cms.InputTag("packedGenParticles"),
                         
                         ## Object selection
                         vertex_ndof_min = cms.double( 4.0),
                         vertex_rho_max  = cms.double( 2.0),
                         vertex_z_max    = cms.double(24.0),

                         muon_ID        = cms.string("loose"),
                         muon_pT_min    = cms.double(10.0),
                         muon_eta_max   = cms.double( 2.4),
                         muon_trig_dR   = cms.double( 0.1),
                         muon_use_pfIso = cms.bool  (True),
                         muon_iso_dR    = cms.double( 0.4),
                         muon_iso_max   = cms.double( 0.4),

                         muon_id_sf_wp_num = cms.string("MediumID"),
                         muon_id_sf_wp_den = cms.string("TrackerMuons"),
                         muon_iso_sf_wp_num = cms.string("LooseRelIso"),
                         muon_iso_sf_wp_den = cms.string("MediumID"),

                         ele_ID      = cms.string("loose"),
                         ele_pT_min  = cms.double(10.),
                         ele_eta_max = cms.double(2.5),

                         jet_ID      = cms.string("tight"),
                         jet_pT_min  = cms.double(20.0),
                         jet_eta_max = cms.double(5.0),

                         ## Event weights and efficiencies
                         PU_wgt_file      = cms.string("PU_wgt_2018_Autumn18_v0.root"),
                         Trig_eff_3_file  = cms.string("MuonReferenceEfficiencies/EfficienciesStudies/2018_trigger/EfficienciesAndSF_2018Data_AfterMuonHLTUpdate.root"),
                         MuID_eff_3_file  = cms.string("MuonReferenceEfficiencies/EfficienciesStudies/2018/jsonfiles/RunABCD_SF_ID.json"),
                         MuIso_eff_3_file = cms.string("MuonReferenceEfficiencies/EfficienciesStudies/2018/jsonfiles/RunABCD_SF_ISO.json"),

                         # ## Taus
                         # tauColl    = cms.InputTag("slimmedTaus"),
                         # tauIDNames = cms.vstring(["decayModeFinding",
                         #                           "byLooseCombinedIsolationDeltaBetaCorr3Hits",
                         #                           "byMediumCombinedIsolationDeltaBetaCorr3Hits",
                         #                           "byTightCombinedIsolationDeltaBetaCorr3Hits",
                         #                           "byVLooseIsolationMVArun2v1DBoldDMwLT",
                         #                           "byLooseIsolationMVArun2v1DBoldDMwLT",
                         #                           "byMediumIsolationMVArun2v1DBoldDMwLT",
                         #                           "byTightIsolationMVArun2v1DBoldDMwLT",
                         #                           "byVTightIsolationMVArun2v1DBoldDMwLT",
                         #                           "againstMuonLoose3",
                         #                           "againstMuonTight3",
                         #                           "againstElectronVLooseMVA6",
                         #                           "againstElectronLooseMVA6",
                         #                           "againstElectronMediumMVA6",
                         #                           "againstElectronTightMVA6",
                         #                           "againstElectronVTightMVA6"]),
                         # tau_pT_min  = cms.double(10.),
                         # tau_eta_max = cms.double(2.5),
                         

                         )


class sample:
    def __init__(self, name='', DAS='', nEvt=0, files=[], GT='80X_mcRun2_asymptotic_2016_TrancheIV_v8', 
                 JEC='Summer16_23Sep2016V4_MC', runs=[], JSON=[], isData=False):
        self.name   = name   ## User-assigned dataset name
        self.DAS    = DAS    ## DAS directory
        self.nEvt   = nEvt   ## Number of events in dataset
        self.files  = files  ## Local files for testing
        self.GT     = GT     ## Global tag
        self.JEC    = JEC    ## Jet energy corrections global tag
        self.runs   = runs   ## Run range
        self.JSON   = JSON   ## JSON file
        self.isData = isData ## Is data

# =======================================================================================================
# ------------------------------- DATA ------------------------------------------------------------------
# =======================================================================================================

# The JSON file details the valid lumi sections
## ReReco:     https://twiki.cern.ch/twiki/bin/view/CMS/PdmV2016Analysis#Re_reco_datasets
## PromptReco: https://twiki.cern.ch/twiki/bin/view/CMS/PdmV2016Analysis#DATA
## JSON files: https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions16/13TeV/ReReco/Final/
##             https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions16/13TeV/Final/
JSON_2016 = ['data/JSON/Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt', ## 36.814 fb-1
             'data/JSON/Cert_271036-284044_13TeV_PromptReco_Collisions16_JSON.txt']      ## 36.773 fb-1

AWB_dir = '/store/user/abrinke1/HiggsToMuMu/samples/'

#####################################
###  Global tag and dataset info  ###
#####################################

## RE-miniAOD info: https://twiki.cern.ch/twiki/bin/view/CMSPublic/ReMiniAOD03Feb2017Notes

## Up-to-date GT info: https://twiki.cern.ch/twiki/bin/view/CMS/PdmV2016Analysis
##   * MC:         https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideFrontierConditions#Global_Tags_for_PdmVMCcampaignRu
##     - Last check that GT 80X_mcRun2_asymptotic_2016_TrancheIV_v8 was up-to-date: March 10, 2017 (AWB)
##   * ReReco:     https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideFrontierConditions#Global_Tags_for_2016_data_re_rec
##     - Last check that GT 80X_dataRun2_2016SeptRepro_v7 was up-to-date: March 10, 2017 (AWB)
##   * PromptReco: https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideFrontierConditions#Prompt_reconstruction_Global_AN1
##     - Last check that GT 80X_dataRun2_Prompt_v16 was up-to-date: March 10, 2017 (AWB)

## Jet energy correction info
## https://twiki.cern.ch/twiki/bin/view/CMS/JECDataMC
##  - Last check that data GT Summer16_23Sep2016*V4_DATA was up-to-date: March 10, 2017 (AWB)  
##  - Last check that MC   GT Summer16_23Sep2016V4_MC    was up-to-date: March 10, 2017 (AWB)  
## https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookJetEnergyCorrections

SingleMu_2016C_dir = 'SingleMuon_Run2016C/03Feb2017-v1/'

SingleMu_2016B = sample( name   = 'SingleMu_2016B',
                         DAS    = '/SingleMuon/Run2016B-03Feb2017_ver2-v2/MINIAOD',
                         ## No runs from Run2016B-23Sep2016-v1 in the 23Sep2016ReReco JSON
                         GT     = '80X_dataRun2_2016SeptRepro_v7',
                         JEC    = 'Summer16_23Sep2016BCDV4_DATA',
                         JSON   = JSON_2016[0],
                         isData = True)

SingleMu_2016C = sample( name   = 'SingleMu_2016C',
                         DAS    = '/SingleMuon/Run2016C-03Feb2017-v1/MINIAOD',
                         files = [ AWB_dir+SingleMu_2016C_dir+'004A1ACA-D5EA-E611-885F-B499BAA6776E.root' ],
                         GT     = '80X_dataRun2_2016SeptRepro_v7',
                         JEC    = 'Summer16_23Sep2016BCDV4_DATA',
                         JSON   = JSON_2016[0],
                         isData = True)

SingleMu_2016D = sample( name   = 'SingleMu_2016D',
                         DAS    = '/SingleMuon/Run2016D-03Feb2017-v1/MINIAOD',
                         GT     = '80X_dataRun2_2016SeptRepro_v7',
                         JEC    = 'Summer16_23Sep2016BCDV4_DATA',
                         JSON   = JSON_2016[0],
                         isData = True)

SingleMu_2016E = sample( name   = 'SingleMu_2016E',
                         DAS    = '/SingleMuon/Run2016E-03Feb2017-v1/MINIAOD',
                         GT     = '80X_dataRun2_2016SeptRepro_v7',
                         JEC    = 'Summer16_23Sep2016EFV4_DATA',
                         JSON   = JSON_2016[0],
                         isData = True)

SingleMu_2016F_1 = sample( name   = 'SingleMu_2016F_1',
                           DAS    = '/SingleMuon/Run2016F-03Feb2017-v1/MINIAOD',
                           GT     = '80X_dataRun2_2016SeptRepro_v7',
                           JEC    = 'Summer16_23Sep2016EFV4_DATA',
                           runs   = [0, 278801],
                           JSON   = JSON_2016[0],
                         isData = True)

SingleMu_2016F_2 = sample( name   = 'SingleMu_2016F_2',
                           DAS    = '/SingleMuon/Run2016F-03Feb2017-v1/MINIAOD',
                           GT     = '80X_dataRun2_2016SeptRepro_v7',
                           JEC    = 'Summer16_23Sep2016GV4_DATA',
                           runs   = [278802, 999999],
                           JSON   = JSON_2016[0],
                           isData = True)

SingleMu_2016G = sample( name   = 'SingleMu_2016G',
                         DAS    = '/SingleMuon/Run2016G-03Feb2017-v1/MINIAOD',
                         GT     = '80X_dataRun2_2016SeptRepro_v7',
                         JEC    = 'Summer16_23Sep2016GV4_DATA',
                         JSON   = JSON_2016[0],
                         isData = True)

SingleMu_2016H_1 = sample( name   = 'SingleMu_2016H_1',
                           DAS    = '/SingleMuon/Run2016H-03Feb2017_ver2-v1/MINIAOD',
                           ## No runs from Run2016H-PromptReco-v1 in 23Sep2016ReReco or PromptReco JSON
                           GT     = '80X_dataRun2_Prompt_v16',
                           JEC    = 'Summer16_23Sep2016HV4_DATA',
                           JSON   = JSON_2016[0],
                           isData = True)

SingleMu_2016H_2 = sample( name   = 'SingleMu_2016H_2',
                           DAS    = '/SingleMuon/Run2016H-03Feb2017_ver3-v1/MINIAOD',
                           GT     = '80X_dataRun2_Prompt_v16',
                           JEC    = 'Summer16_23Sep2016HV4_DATA',
                           JSON   = JSON_2016[0],
                           isData = True)

SingleMu = []  ## All SingleMuon datasets

SingleMu.append(SingleMu_2016B)
SingleMu.append(SingleMu_2016C)
SingleMu.append(SingleMu_2016D)
SingleMu.append(SingleMu_2016E)
SingleMu.append(SingleMu_2016F_1)
SingleMu.append(SingleMu_2016F_2)
SingleMu.append(SingleMu_2016G)
SingleMu.append(SingleMu_2016H_1)
SingleMu.append(SingleMu_2016H_2)

# =======================================================================================================
# ------------------------------- SIGNAL ----------------------------------------------------------------
# =======================================================================================================

## DAS location: dataset=/*HToMuMu_M125_13TeV*/*Moriond*/MINIAODSIM
DAS_era_sig = 'RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
H2Mu_gg_dir = 'GluGlu_HToMuMu_M125_13TeV_powheg_pythia8/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/'

## Gluon-gluon fusion
H2Mu_gg = sample( name  = 'H2Mu_gg',
                  DAS   = '/GluGlu_HToMuMu_M125_13TeV_powheg_pythia8/'+DAS_era_sig,
                  nEvt  = 250000, ## 250 k
                  files = [ AWB_dir+H2Mu_gg_dir+'C0801715-85C0-E611-97A8-001E67396A18.root' ] )

H2Mu_gg_120 = sample( name  = 'H2Mu_gg_120',
                      DAS   = '/GluGlu_HToMuMu_M120_13TeV_powheg_pythia8/'+DAS_era_sig,
                      nEvt  = 250000, ## 250 k
                      files = [ AWB_dir+H2Mu_gg_dir+'C0801715-85C0-E611-97A8-001E67396A18.root' ] )

H2Mu_gg_130 = sample( name  = 'H2Mu_gg_130',
                      DAS   = '/GluGlu_HToMuMu_M130_13TeV_powheg_pythia8/'+DAS_era_sig,
                      nEvt  = 250000, ## 250 k
                      files = [ AWB_dir+H2Mu_gg_dir+'C0801715-85C0-E611-97A8-001E67396A18.root' ] )

## Vector boson fusion
H2Mu_VBF = sample( name = 'H2Mu_VBF',
                   DAS  = '/VBF_HToMuMu_M125_13TeV_powheg_pythia8/'+DAS_era_sig,
                   nEvt = 249200 ) ## 250 k

H2Mu_VBF_120 = sample( name = 'H2Mu_VBF_120',
                       DAS  = '/VBF_HToMuMu_M120_13TeV_powheg_pythia8/'+DAS_era_sig,
                       nEvt = 249200 ) ## 250 k

H2Mu_VBF_130 = sample( name = 'H2Mu_VBF_130',
                       DAS  = '/VBF_HToMuMu_M130_13TeV_powheg_pythia8/'+DAS_era_sig,
                       nEvt = 249200 ) ## 250 k

## WH (+)
H2Mu_WH_pos = sample( name = 'H2Mu_WH_pos',
                      DAS  = '/WPlusH_HToMuMu_M125_13TeV_powheg_pythia8/'+DAS_era_sig,
                      nEvt = 124547 ) ## 125 k

H2Mu_WH_pos_120 = sample( name = 'H2Mu_WH_pos_120',
                          DAS  = '/WPlusH_HToMuMu_M120_13TeV_powheg_pythia8/'+DAS_era_sig,
                          nEvt = 124547 ) ## 125 k

H2Mu_WH_pos_130 = sample( name = 'H2Mu_WH_pos_130',
                          DAS  = '/WPlusH_HToMuMu_M130_13TeV_powheg_pythia8/'+DAS_era_sig,
                          nEvt = 124547 ) ## 125 k

## WH (-)
H2Mu_WH_neg = sample( name = 'H2Mu_WH_neg',
                      DAS  = '/WMinusH_HToMuMu_M125_13TeV_powheg_pythia8/'+DAS_era_sig,
                      nEvt = 125000 ) ## 125 k

H2Mu_WH_neg_120 = sample( name = 'H2Mu_WH_neg_120',
                          DAS  = '/WMinusH_HToMuMu_M120_13TeV_powheg_pythia8/'+DAS_era_sig,
                          nEvt = 125000 ) ## 125 k

H2Mu_WH_neg_130 = sample( name = 'H2Mu_WH_neg_130',
                          DAS  = '/WMinusH_HToMuMu_M130_13TeV_powheg_pythia8/'+DAS_era_sig,
                          nEvt = 125000 ) ## 125 k

## ZH
H2Mu_ZH = sample( name = 'H2Mu_ZH',
                  DAS  = '/ZH_HToMuMu_M125_13TeV_powheg_pythia8/'+DAS_era_sig,
                  nEvt = 249748 ) ## 250 k

H2Mu_ZH_120 = sample( name = 'H2Mu_ZH_120',
                  DAS  = '/ZH_HToMuMu_M120_13TeV_powheg_pythia8/'+DAS_era_sig,
                  nEvt = 249748 ) ## 250 k

H2Mu_ZH_130 = sample( name = 'H2Mu_ZH_130',
                      DAS  = '/ZH_HToMuMu_M130_13TeV_powheg_pythia8/'+DAS_era_sig,
                      nEvt = 249748 ) ## 250 k

# ## ttH
# H2Mu_ttH = sample( name = 'H2Mu_ttH',
#                    DAS  = '',
#                    nEvt = )

Signal = []  ## All H2Mu signal samples
Signal.append(H2Mu_gg)
Signal.append(H2Mu_VBF)
Signal.append(H2Mu_WH_pos)
Signal.append(H2Mu_WH_neg)
Signal.append(H2Mu_ZH)
# Signal.append(H2Mu_ttH)

Signal.append(H2Mu_gg_120)
Signal.append(H2Mu_VBF_120)
Signal.append(H2Mu_WH_pos_120)
Signal.append(H2Mu_WH_neg_120)
Signal.append(H2Mu_ZH_120)

Signal.append(H2Mu_gg_130)
Signal.append(H2Mu_VBF_130)
Signal.append(H2Mu_WH_pos_130)
Signal.append(H2Mu_WH_neg_130)
Signal.append(H2Mu_ZH_130)



# =======================================================================================================
# ------------------------------- BACKGROUND ------------------------------------------------------------
# =======================================================================================================

Background = []  ## All H2Mu background samples

DAS_era_bkg_1 = 'RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6'
DAS_era_bkg_2 = 'RunIISummer16MiniAODv2-PUMoriond17_backup_80X_mcRun2_asymptotic_2016_TrancheIV_v6'
DAS_AMC       = 'TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring16MiniAODv'

###################
###  Drell-Yan  ###
###################
ZJets_AMC_dir = 'DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/PUMoriond17_HCALDebug_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/'
ZJets_MG_HT_2500_inf_dir = 'DYJetsToLL_M-50_HT-2500toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/'

ZJets_MG = sample( name = 'ZJets_MG',
                   DAS  = '/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v2/MINIAODSIM',
                   nEvt = 49144274 ) ## 49 million 

ZJets_MG_HER = sample( name = 'ZJets_MG_HER',
                       DAS  = '/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-herwigpp_30M/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM',
                       nEvt =  29813625 ) ## 30 million

ZJets_AMC = sample( name = 'ZJets_AMC',
                    DAS  = '/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_HCALDebug_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM',
                    nEvt = 28968252,  ## 29 million
                    files = [ AWB_dir+ZJets_AMC_dir+'00312D7A-FEBD-E611-A713-002590DB923E.root' ] )

ZJets_hiM = sample( name = 'ZJets_hiM',
                    DAS  = '/DYJetsToLL_M-100to200_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM',
                    nEvt = 1083606 ) ## 1.1 million
                    ## GT   = 'Spring16_23Sep2016V2_MC' ) ## Need a different global tag? - AWB 19.01.17

ZJets_MG_HT_70_100 = sample( name = 'ZJets_MG_HT_70_100',
                             DAS  = '/DYJetsToLL_M-50_HT-70to100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM',
                             nEvt = 999 )

ZJets_MG_HT_100_200_A = sample( name = 'ZJets_MG_HT_100_200_A',
                                DAS  = '/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM',
                                nEvt = 999 )

ZJets_MG_HT_100_200_B = sample( name = 'ZJets_MG_HT_100_200_B',
                                DAS  = '/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM',
                                nEvt = 999 )

ZJets_MG_HT_200_400_A = sample( name = 'ZJets_MG_HT_200_400_A',
                                DAS  = '/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM',
                                nEvt = 999 )

ZJets_MG_HT_200_400_B = sample( name = 'ZJets_MG_HT_200_400_B',
                                DAS  = '/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM',
                                nEvt = 999 )

ZJets_MG_HT_400_600_A = sample( name = 'ZJets_MG_HT_400_600_A',
                                DAS  = '/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM',
                                nEvt = 999 )

ZJets_MG_HT_400_600_B = sample( name = 'ZJets_MG_HT_400_600_B',
                                DAS  = '/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM',
                                nEvt = 999 )

ZJets_MG_HT_600_800 = sample( name = 'ZJets_MG_HT_600_800',
                              DAS  = '/DYJetsToLL_M-50_HT-600to800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM',
                              nEvt = 999 )

ZJets_MG_HT_800_1200 = sample( name = 'ZJets_MG_HT_800_1200',
                               DAS  = '/DYJetsToLL_M-50_HT-800to1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM',
                               nEvt = 999 )

ZJets_MG_HT_1200_2500 = sample( name = 'ZJets_MG_HT_1200_2500',
                                DAS  = '/DYJetsToLL_M-50_HT-1200to2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM',
                                nEvt = 999 )

ZJets_MG_HT_2500_inf = sample( name = 'ZJets_MG_HT_2500_inf',
                               DAS  = '/DYJetsToLL_M-50_HT-2500toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM',
                               nEvt = 999,
                               files = [ AWB_dir+ZJets_MG_HT_2500_inf_dir+'308C289B-B8C0-E611-A7C6-0025905A606A.root' ],
                               )

Background.append(ZJets_MG)
# Background.append(ZJets_MG_HER)
Background.append(ZJets_AMC)
Background.append(ZJets_hiM)
Background.append(ZJets_MG_HT_70_100)
Background.append(ZJets_MG_HT_100_200_A)
Background.append(ZJets_MG_HT_100_200_B)
Background.append(ZJets_MG_HT_200_400_A)
Background.append(ZJets_MG_HT_200_400_B)
Background.append(ZJets_MG_HT_400_600_A)
Background.append(ZJets_MG_HT_400_600_B)
Background.append(ZJets_MG_HT_600_800)
Background.append(ZJets_MG_HT_800_1200)
Background.append(ZJets_MG_HT_1200_2500)
Background.append(ZJets_MG_HT_2500_inf)

####################
###  Single top  ###
####################

tW_pos_1 = sample( name = 'tW_pos_1',
                   DAS  = '/ST_tW_top_5f_NoFullyHadronicDecays_13TeV-powheg_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM',
                   nEvt = 5372991 ) ## 5 million

tW_pos_2 = sample( name = 'tW_pos_2',
                   DAS  = '/ST_tW_top_5f_NoFullyHadronicDecays_13TeV-powheg_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM',
                   nEvt = 3256650 ) ## 3 million

tW_neg_1 = sample( name = 'tW_neg_1',
                   DAS  = '/ST_tW_antitop_5f_NoFullyHadronicDecays_13TeV-powheg_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM',
                   nEvt = 5425134 ) ## 5 million

tW_neg_2 = sample( name = 'tW_neg_2',
                   DAS  = '/ST_tW_antitop_5f_NoFullyHadronicDecays_13TeV-powheg_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM',
                   nEvt = 3256407 ) ## 3 million

Background.append(tW_pos_1)
Background.append(tW_pos_2)
Background.append(tW_neg_1)
Background.append(tW_neg_2)

###############
###  ttbar  ###
###############

tt = sample( name = 'tt',
             DAS  = '/TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_backup_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM',
             nEvt = 43561608 ) ## 43 million

tt_ll_MG_1 = sample( name = 'tt_ll_MG_1',
                     DAS  = '/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM',
                     nEvt = 6094476 ) ## 6 million

tt_ll_MG_2 = sample( name = 'tt_ll_MG_2',
                     DAS  = '/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM',
                     nEvt = 24350202 ) ## 24 million

tt_ll_AMC = sample( name = 'tt_ll_AMC',
                    DAS  = '/TTJets_Dilept_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM',
                    nEvt = 14529280 ) ## 14 million

# Background.append(tt)
Background.append(tt_ll_MG_1)
Background.append(tt_ll_MG_2)
Background.append(tt_ll_AMC)

#################
###  Diboson  ###
#################

WW = sample( name = 'WW',
             DAS  = '/WWTo2L2Nu_13TeV-powheg/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM',
             nEvt = 1999000 ) ## 2 million

WW_HER = sample( name = 'WW_HER',
                 DAS  = '/WWTo2L2Nu_13TeV-powheg-herwigpp/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM',
                 nEvt = 1982372 ) ## 2 million

WW_up = sample( name = 'WW_up',
                DAS  = '/WWTo2L2Nu_13TeV-powheg-CUETP8M1Up/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM',
                nEvt =  1984000 ) ## 2 million

WW_down = sample( name = 'WW_down',
                  DAS  = '/WWTo2L2Nu_13TeV-powheg-CUETP8M1Down/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM',
                  nEvt = 1988000 ) ## 2 million

WZ_2l = sample( name = 'WZ_2l',
                DAS  = '/WZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM',
                nEvt =  26517272 ) ## 27 million

WZ_3l_AMC = sample( name = 'WZ_3l_AMC',
                    DAS  = '/WZTo3LNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM',
                    nEvt = 11887464 ) ## 12 million 

WZ_3l_POW = sample( name = 'WZ_3l_POW',
                    DAS  = '/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM',
                    nEvt =  1993200 ) ## 2 million

ZZ_2l_2v = sample( name = 'ZZ_2l_2v',
                   DAS  = '/ZZTo2L2Nu_13TeV_powheg_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM',
                   nEvt = 8842475 ) ## 9 million

ZZ_2l_2q = sample( name = 'ZZ_2l_2q',
                   DAS  = '/ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM',
                   nEvt = 15345572 ) ## 15 million

ZZ_4l_AMC = sample( name = 'ZZ_4l_AMC',
                    DAS  = '/ZZTo4L_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM',
                    nEvt = 10709784 ) ## 11 million

ZZ_4l_POW = sample( name = 'ZZ_4l_POW',
                    DAS  = '/ZZTo4L_13TeV_powheg_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM',
                    nEvt = 6669988 ) ## 7 million

Background.append(WW)
# Background.append(WW_HER)
# Background.append(WW_up)
# Background.append(WW_down)
Background.append(WZ_2l)
Background.append(WZ_3l_AMC)
# Background.append(WZ_3l_POW)
Background.append(ZZ_2l_2v)
Background.append(ZZ_2l_2q)
Background.append(ZZ_4l_AMC)
# Background.append(ZZ_4l_POW)

#################
###  Triboson  ##
#################

WWW = sample( name = 'WWW',
              DAS  = '/WWW_4F_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM',
              nEvt = 240000 ) ## 240 k

WWZ = sample( name = 'WWZ',
              DAS  = '/WWZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM',
              nEvt = 250000 ) ## 250 k

WZZ = sample( name = 'WZZ',
              DAS  = '/WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM',
              nEvt = 246800 ) ## 250 k

ZZZ = sample( name = 'ZZZ',
              DAS  = '/ZZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM',
              nEvt = 249237 ) ## 250 k

Background.append(WWW)
Background.append(WWZ)
Background.append(WZZ)
Background.append(ZZZ)

#####################
###  Single top+X  ##
#####################

tZq = sample( name = 'tZq',
              DAS  = '/tZq_ll_4f_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM',
              nEvt = 14509520 ) ## 15 million

tZq_HER = sample( name = 'tZq_HER',
                  DAS  = '/tZq_ll_4f_13TeV-amcatnlo-herwigpp/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM',
                  nEvt = 9999044 ) ## 10 million

tZW = sample( name = 'tZW',
              DAS  = '/ST_tWll_5f_LO_13TeV-MadGraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM',
              nEvt = 50000 ) ## 50 k

Background.append(tZq)
# Background.append(tZq_HER)
Background.append(tZW)

################
###  ttbar+X  ##
################

ttW_1 = sample( name = 'ttW_1',
                DAS  = '/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v3/MINIAODSIM',
                nEvt = 2160168 ) ## 2 million

ttW_2 = sample( name = 'ttW_2',
                DAS  = '/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/MINIAODSIM',
                nEvt = 3120397 ) ## 3 million

ttZ = sample( name = 'ttZ',
              DAS  = '/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM',
              nEvt = 1992438 ) ## 2 million

ttH = sample( name = 'ttH',
              DAS  = '/ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM',
              nEvt = 3981250 ) ## 4 million

Background.append(ttW_1)
Background.append(ttW_2)
Background.append(ttZ)
Background.append(ttH)


DataAndMC = []
DataAndMC.extend(SingleMu)
DataAndMC.extend(Signal)
DataAndMC.extend(Background)

MC = []
MC.extend(Signal)
MC.extend(Background)

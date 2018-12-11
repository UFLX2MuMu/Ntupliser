
class sample:
    def __init__(self, name='', DAS='', nEvt=0, files=[], GT='94X_mc2017_realistic_v14',
                 JEC='Fall17_17Nov2017_V32_94X_MC', runs=[], JSON=[], isData=False):
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
## ReReco:     https://twiki.cern.ch/twiki/bin/view/CMS/PdmV2017Analysis#Re_reco_datasets
## JSON files: https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions17/13TeV/Final/
JSON_2017 = 'data/JSON/2017/Cert_294927-306462_13TeV_PromptReco_Collisions17_JSON.txt'  ## 41.53 fb-1

AWB_dir = '/store/user/abrinke1/HiggsToMuMu/samples/'

#####################################
###  Global tag and dataset info  ###
#####################################

## 94x v2 miniAOD info: https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookMiniAOD#2017_MC_re_miniAOD_12Apr2018_94X
##   * Last check that MC   GT 94X_mc2017_realistic_v14 was up-to-date: 05.12.2018 (AWB) - TO BE UPDATED SOON!!!
##   * Last check that data GT 94X_dataRun2_v6          was up-to-date: 05.12.2018 (AWB) - TO BE UPDATED SOON!!!

## GT info here may or may not be up-to-date: https://twiki.cern.ch/twiki/bin/view/CMS/PdmV2017Analysis
## Likewise in Frontier Conditions, latest info is for 80X "legacy" reprocessing
##   * https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideFrontierConditions#Global_Tags_for_2017_Nov_re_reco

## Jet energy correction info
## https://twiki.cern.ch/twiki/bin/view/CMS/JECDataMC
##  - Last check that data Fall17_17Nov2017_V32_94X_DATA   was up-to-date: 05.12.2018 (AWB)  
##  - Last check that MC   JEC Fall17_17Nov2017_V32_94X_MC was up-to-date: 05.12.2018 (AWB)  
## https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookJetEnergyCorrections


SingleMu_2017B = sample( name   = 'SingleMu_2017B',
                         DAS    = '/SingleMuon/Run2017B-31Mar2018-v1/MINIAOD',
                         GT     = '94X_dataRun2_v10',
                         JEC    = 'Fall17_17Nov2017_V32_94X_DATA',
                         JSON   = JSON_2017,
                         isData = True)

SingleMu_2017C = sample( name   = 'SingleMu_2017C',
                         DAS    = '/SingleMuon/Run2017C-31Mar2018-v1/MINIAOD',
                         # xrdcp root://cms-xrd-global.cern.ch//store/data/SingleMuon/MINIAOD/31Mar2018-v1/90000/DCBC78A8-A637-E811-8861-20CF3027A5BB.root /eos/cms/store/user/abrinke1/HiggsToMuMu/samples/SingleMuon_Run2017D/31Mar2018-v1/
                         # files = [ AWB_dir+'SingleMuon_Run2017C/31Mar2018-v1/D6E4B6C8-1C9B-E811-8C98-90E2BAD5729C.root' ],
                         GT     = '94X_dataRun2_v10',
                         JEC    = 'Fall17_17Nov2017_V32_94X_DATA',
                         JSON   = JSON_2017,
                         isData = True)

SingleMu_2017D = sample( name   = 'SingleMu_2017D',
                         DAS    = '/SingleMuon/Run2017D-31Mar2018-v1/MINIAOD',
                         GT     = '94X_dataRun2_v10',
                         JEC    = 'Fall17_17Nov2017_V32_94X_DATA',
                         JSON   = JSON_2017,
                         isData = True)

SingleMu_2017E = sample( name   = 'SingleMu_2017E',
                         DAS    = '/SingleMuon/Run2017E-31Mar2018-v1/MINIAOD',
                         GT     = '94X_dataRun2_v10',
                         JEC    = 'Fall17_17Nov2017_V32_94X_DATA',
                         JSON   = JSON_2017,
                         isData = True)

SingleMu_2017F = sample( name   = 'SingleMu_2017F',
                         DAS    = '/SingleMuon/Run2017F-31Mar2018-v1/MINIAOD',
                         GT     = '94X_dataRun2_v10',
                         JEC    = 'Fall17_17Nov2017_V32_94X_DATA',
                         JSON   = JSON_2017,
                         isData = True)

SingleMu = []  ## All SingleMuon datasets

SingleMu.append(SingleMu_2017B)
SingleMu.append(SingleMu_2017C)
SingleMu.append(SingleMu_2017D)
SingleMu.append(SingleMu_2017E)
SingleMu.append(SingleMu_2017F)


DoubleMu_2017B = sample( name   = 'DoubleMu_2017B',
                         DAS    = '/DoubleMuon/Run2017B-31Mar2018-v1/MINIAOD',
                         GT     = '94X_dataRun2_v10',
                         JEC    = 'Fall17_17Nov2017_V32_94X_DATA',
                         JSON   = JSON_2017,
                         isData = True)

DoubleMu_2017C = sample( name   = 'DoubleMu_2017C',
                         DAS    = '/DoubleMuon/Run2017C-31Mar2018-v1/MINIAOD',
                         GT     = '94X_dataRun2_v10',
                         JEC    = 'Fall17_17Nov2017_V32_94X_DATA',
                         JSON   = JSON_2017,
                         isData = True)

DoubleMu_2017D = sample( name   = 'DoubleMu_2017D',
                         DAS    = '/DoubleMuon/Run2017D-31Mar2018-v1/MINIAOD',
                         GT     = '94X_dataRun2_v10',
                         JEC    = 'Fall17_17Nov2017_V32_94X_DATA',
                         JSON   = JSON_2017,
                         isData = True)

DoubleMu_2017E = sample( name   = 'DoubleMu_2017E',
                         DAS    = '/DoubleMuon/Run2017E-31Mar2018-v1/MINIAOD',
                         GT     = '94X_dataRun2_v10',
                         JEC    = 'Fall17_17Nov2017_V32_94X_DATA',
                         JSON   = JSON_2017,
                         isData = True)

DoubleMu_2017F = sample( name   = 'DoubleMu_2017F',
                         DAS    = '/DoubleMuon/Run2017F-31Mar2018-v1/MINIAOD',
                         GT     = '94X_dataRun2_v10',
                         JEC    = 'Fall17_17Nov2017_V32_94X_DATA',
                         JSON   = JSON_2017,
                         isData = True)


DoubleMu = []  ## All DoubleMuon datasets

# DoubleMu.append(DoubleMu_2017B)
# DoubleMu.append(DoubleMu_2017C)
# DoubleMu.append(DoubleMu_2017D)
# DoubleMu.append(DoubleMu_2017E)
# DoubleMu.append(DoubleMu_2017F)


## MC spreadsheet: https://docs.google.com/spreadsheets/d/192q__wqy9o-1J1Twv1AkqmLYu2Vijg62nGBaF3vGyEk
## MC DAS location: dataset=/*/RunIIFall17MiniAODv2*/MINIAODSIM
DAS_era_MC_a = 'RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14'
DAS_era_MC_b = 'RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14'
DAS_era_MC_c = 'RunIIFall17MiniAODv2-PU2017RECOSIMstep_12Apr2018_94X_mc2017_realistic_v14'

# =======================================================================================================
# ------------------------------- SIGNAL ----------------------------------------------------------------
# =======================================================================================================

## DAS location: dataset=/*HToMuMu*125*/RunIIFall17MiniAODv2*/MINIAODSIM
H2Mu_gg_dir  = 'GluGluHToMuMu_M125_13TeV_amcatnloFXFX_pythia8/PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/'
H2Mu_ttH_dir = 'ttHToMuMu_M125_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v3/'

## Gluon-gluon fusion, amc@NLO
H2Mu_gg_125_NLO = sample( name  = 'H2Mu_gg',
                          DAS   = '/GluGluHToMuMu_M125_13TeV_amcatnloFXFX_pythia8/'+DAS_era_MC_a+'-v1/MINIAODSIM',
                          nEvt  = 2000000, ## 2.0 million
                          files = [ AWB_dir+H2Mu_gg_dir+'226E7A92-6D42-E811-B5E3-44A8423D7E31.root' ] )

H2Mu_gg_120_NLO = sample( name  = 'H2Mu_gg_120',
                          DAS   = '/GluGluHToMuMu_M120_13TeV_amcatnloFXFX_pythia8/'+DAS_era_MC_a+'-v1/MINIAODSIM',
                          nEvt  = 1900000 ) ## 1.9 million

H2Mu_gg_130_NLO = sample( name  = 'H2Mu_gg_130',
                          DAS   = '/GluGluHToMuMu_M130_13TeV_amcatnloFXFX_pythia8/'+DAS_era_MC_a+'-v1/MINIAODSIM',
                          nEvt  = 1700000 ) ## 1.7 million

# ## Vector boson fusion
# H2Mu_VBF = sample( name = 'H2Mu_VBF',
#                    DAS  = '/VBF_HToMuMu_M125_13TeV_powheg_pythia8/'+DAS_era_MC_a+'-v1/MINIAODSIM',
#                    nEvt = 249200 ) ## 250 k

# H2Mu_VBF_120 = sample( name = 'H2Mu_VBF_120',
#                        DAS  = '/VBF_HToMuMu_M120_13TeV_powheg_pythia8/'+DAS_era_MC_a+'-v1/MINIAODSIM',
#                        nEvt = 249200 ) ## 250 k

# H2Mu_VBF_130 = sample( name = 'H2Mu_VBF_130',
#                        DAS  = '/VBF_HToMuMu_M130_13TeV_powheg_pythia8/'+DAS_era_MC_a+'-v1/MINIAODSIM',
#                        nEvt = 249200 ) ## 250 k

# ## WH (+)
# H2Mu_WH_pos = sample( name = 'H2Mu_WH_pos',
#                       DAS  = '/WPlusH_HToMuMu_M125_13TeV_powheg_pythia8/'+DAS_era_MC_a+'-v1/MINIAODSIM',
#                       nEvt = 124547 ) ## 125 k

# H2Mu_WH_pos_120 = sample( name = 'H2Mu_WH_pos_120',
#                           DAS  = '/WPlusH_HToMuMu_M120_13TeV_powheg_pythia8/'+DAS_era_MC_a+'-v1/MINIAODSIM',
#                           nEvt = 124547 ) ## 125 k

# H2Mu_WH_pos_130 = sample( name = 'H2Mu_WH_pos_130',
#                           DAS  = '/WPlusH_HToMuMu_M130_13TeV_powheg_pythia8/'+DAS_era_MC_a+'-v1/MINIAODSIM',
#                           nEvt = 124547 ) ## 125 k

# ## WH (-)
# H2Mu_WH_neg = sample( name = 'H2Mu_WH_neg',
#                       DAS  = '/WMinusH_HToMuMu_M125_13TeV_powheg_pythia8/'+DAS_era_MC_a+'-v1/MINIAODSIM',
#                       nEvt = 125000 ) ## 125 k

# H2Mu_WH_neg_120 = sample( name = 'H2Mu_WH_neg_120',
#                           DAS  = '/WMinusH_HToMuMu_M120_13TeV_powheg_pythia8/'+DAS_era_MC_a+'-v1/MINIAODSIM',
#                           nEvt = 125000 ) ## 125 k

# H2Mu_WH_neg_130 = sample( name = 'H2Mu_WH_neg_130',
#                           DAS  = '/WMinusH_HToMuMu_M130_13TeV_powheg_pythia8/'+DAS_era_MC_a+'-v1/MINIAODSIM',
#                           nEvt = 125000 ) ## 125 k

# ## ZH
# H2Mu_ZH = sample( name = 'H2Mu_ZH',
#                   DAS  = '/ZH_HToMuMu_M125_13TeV_powheg_pythia8/'+DAS_era_MC_a+'-v1/MINIAODSIM',
#                   nEvt = 249748 ) ## 250 k

# H2Mu_ZH_120 = sample( name = 'H2Mu_ZH_120',
#                   DAS  = '/ZH_HToMuMu_M120_13TeV_powheg_pythia8/'+DAS_era_MC_a+'-v1/MINIAODSIM',
#                   nEvt = 249748 ) ## 250 k

# H2Mu_ZH_130 = sample( name = 'H2Mu_ZH_130',
#                       DAS  = '/ZH_HToMuMu_M130_13TeV_powheg_pythia8/'+DAS_era_MC_a+'-v1/MINIAODSIM',
#                       nEvt = 249748 ) ## 250 k

## ttH
H2Mu_ttH_120 = sample( name = 'H2Mu_ttH_120',
                       DAS  = '/ttHToMuMu_M120_TuneCP5_13TeV-powheg-pythia8/'+DAS_era_MC_a+'-v1/MINIAODSIM',
                       nEvt = 300000 ) ## 300 k

H2Mu_ttH_125 = sample( name = 'H2Mu_ttH_125',
                       DAS  = '/ttHToMuMu_M125_TuneCP5_13TeV-powheg-pythia8/'+DAS_era_MC_a+'-v3/MINIAODSIM',
                       nEvt = 294000, ## 300 k
                       files = [ AWB_dir+H2Mu_ttH_dir+'C8B266CB-3551-E811-8C8A-3417EBE6458E.root' ] )

H2Mu_ttH_130 = sample( name = 'H2Mu_ttH_130',
                       DAS  = '/ttHToMuMu_M130_TuneCP5_13TeV-powheg-pythia8/'+DAS_era_MC_a+'-v1/MINIAODSIM',
                       nEvt = 290172 ) ## 300 k


Signal = []  ## All H2Mu signal samples
Signal.append(H2Mu_gg_125_NLO)
# Signal.append(H2Mu_VBF)
# Signal.append(H2Mu_WH_pos)
# Signal.append(H2Mu_WH_neg)
# Signal.append(H2Mu_ZH)
Signal.append(H2Mu_ttH_125)

# Signal.append(H2Mu_gg_120)
# Signal.append(H2Mu_VBF_120)
# Signal.append(H2Mu_WH_pos_120)
# Signal.append(H2Mu_WH_neg_120)
# Signal.append(H2Mu_ZH_120)

# Signal.append(H2Mu_gg_130)
# Signal.append(H2Mu_VBF_130)
# Signal.append(H2Mu_WH_pos_130)
# Signal.append(H2Mu_WH_neg_130)
# Signal.append(H2Mu_ZH_130)



# # =======================================================================================================
# # ------------------------------- BACKGROUND ------------------------------------------------------------
# # =======================================================================================================

# Background = []  ## All H2Mu background samples

# DAS_era_bkg_2 = 'RunIISummer16MiniAODv3-PUMoriond17_backup_80X_mcRun2_asymptotic_2016_TrancheIV_v6'
# DAS_AMC       = 'TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring16MiniAODv'

# ###################
# ###  Drell-Yan  ###
# ###################
# ZJets_AMC_dir            = 'DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/94X_mcRun2_asymptotic_v3/'
# ZJets_MG_HT_2500_inf_dir = 'DYJetsToLL_M-50_HT-2500toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/'

# ZJets_AMC = sample( name = 'ZJets_AMC',
#                     DAS  = '/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/'+DAS_era_MC+'_ext2-v1/MINIAODSIM',
#                     nEvt = 120777245,  ## 121 million
#                     files = [ AWB_dir+ZJets_AMC_dir+'2ECA84BD-B0CA-E811-9449-1866DA890B94.root' ] )

# ZJets_AMC_0j_A = sample( name = 'ZJets_AMC_0j_A',
#                          DAS  = '/DYToLL_0J_13TeV-amcatnloFXFX-pythia8/'+DAS_era_MC+'_ext1-v1/MINIAODSIM',
#                          nEvt = 49538540 )  ## 50 million

# # ZJets_AMC_0j_B = sample( name = 'ZJets_AMC_0j_B',
# #                          DAS  = '/DYToLL_0J_13TeV-amcatnloFXFX-pythia8/'+DAS_era_bkg_2+'-v1/MINIAODSIM',
# #                          nEvt = 44253240 )  ## 44 million

# ZJets_AMC_1j_A = sample( name = 'ZJets_AMC_1j_A',
#                          DAS  = '/DYToLL_1J_13TeV-amcatnloFXFX-pythia8/'+DAS_era_MC+'_ext1-v1/MINIAODSIM',
#                          nEvt = 50121080 )  ## 50 million

# # ZJets_AMC_1j_B = sample( name = 'ZJets_AMC_1j_B',
# #                          DAS  = '/DYToLL_1J_13TeV-amcatnloFXFX-pythia8/'+DAS_era_bkg_2+'-v1/MINIAODSIM',
# #                          nEvt = 41597712 )  ## 42 million

# # ZJets_AMC_2j_A = sample( name = 'ZJets_AMC_2j_A',
# #                          DAS  = '/DYToLL_2J_13TeV-amcatnloFXFX-pythia8/'+DAS_era_MC+'_ext1-v1/MINIAODSIM',
# #                          nEvt = 47974554 )  ## 48 million

# # ZJets_AMC_2j_B = sample( name = 'ZJets_AMC_2j_B',
# #                          DAS  = '/DYToLL_2J_13TeV-amcatnloFXFX-pythia8/'+DAS_era_MC+'-v2/MINIAODSIM',
# #                          nEvt = 42324802 )  ## 42 million

# # ZJets_hiM = sample( name = 'ZJets_hiM',
# #                     DAS  = '/DYJetsToLL_M-100to200_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/'+DAS_era_MC+'_ext1-v1/MINIAODSIM',
# #                     nEvt = 1083606 ) ## 1.1 million
# #                     ## GT   = 'Spring16_23Sep2016V2_MC' ) ## Need a different global tag? - AWB 19.01.17

# # ZJets_MG = sample( name = 'ZJets_MG',
# #                    DAS  = '/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/'+DAS_era_MC+'_ext1-v2/MINIAODSIM',
# #                    nEvt = 49144274 ) ## 49 million 

# ZJets_MG_HER = sample( name = 'ZJets_MG_HER',
#                        DAS  = '/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-herwigpp_30M/'+DAS_era_MC+'-v1/MINIAODSIM',
#                        nEvt =  29883521 ) ## 30 million

# # ZJets_MG_HT_70_100 = sample( name = 'ZJets_MG_HT_70_100',
# #                              DAS  = '/DYJetsToLL_M-50_HT-70to100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/'+DAS_era_MC+'-v1/MINIAODSIM',
# #                              nEvt = 999 )

# # ZJets_MG_HT_100_200_A = sample( name = 'ZJets_MG_HT_100_200_A',
# #                                 DAS  = '/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/'+DAS_era_MC+'-v1/MINIAODSIM',
# #                                 nEvt = 999 )

# # ZJets_MG_HT_100_200_B = sample( name = 'ZJets_MG_HT_100_200_B',
# #                                 DAS  = '/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/'+DAS_era_MC+'_ext1-v1/MINIAODSIM',
# #                                 nEvt = 999 )

# # ZJets_MG_HT_200_400_A = sample( name = 'ZJets_MG_HT_200_400_A',
# #                                 DAS  = '/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/'+DAS_era_MC+'-v1/MINIAODSIM',
# #                                 nEvt = 999 )

# # ZJets_MG_HT_200_400_B = sample( name = 'ZJets_MG_HT_200_400_B',
# #                                 DAS  = '/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/'+DAS_era_MC+'_ext1-v1/MINIAODSIM',
# #                                 nEvt = 999 )

# # ZJets_MG_HT_400_600_A = sample( name = 'ZJets_MG_HT_400_600_A',
# #                                 DAS  = '/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/'+DAS_era_MC+'-v1/MINIAODSIM',
# #                                 nEvt = 999 )

# # ZJets_MG_HT_400_600_B = sample( name = 'ZJets_MG_HT_400_600_B',
# #                                 DAS  = '/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/'+DAS_era_MC+'_ext1-v1/MINIAODSIM',
# #                                 nEvt = 999 )

# # ZJets_MG_HT_600_800 = sample( name = 'ZJets_MG_HT_600_800',
# #                               DAS  = '/DYJetsToLL_M-50_HT-600to800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/'+DAS_era_MC+'-v2/MINIAODSIM',
# #                               nEvt = 999 )

# # ZJets_MG_HT_800_1200 = sample( name = 'ZJets_MG_HT_800_1200',
# #                                DAS  = '/DYJetsToLL_M-50_HT-800to1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/'+DAS_era_MC+'-v1/MINIAODSIM',
# #                                nEvt = 999 )

# # ZJets_MG_HT_1200_2500 = sample( name = 'ZJets_MG_HT_1200_2500',
# #                                 DAS  = '/DYJetsToLL_M-50_HT-1200to2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/'+DAS_era_MC+'-v1/MINIAODSIM',
# #                                 nEvt = 999 )

# # ZJets_MG_HT_2500_inf = sample( name = 'ZJets_MG_HT_2500_inf',
# #                                DAS  = '/DYJetsToLL_M-50_HT-2500toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/'+DAS_era_MC+'-v1/MINIAODSIM',
# #                                nEvt = 999,
# #                                files = [ AWB_dir+ZJets_MG_HT_2500_inf_dir+'308C289B-B8C0-E611-A7C6-0025905A606A.root' ],
# #                                )

# Background.append(ZJets_AMC)
# Background.append(ZJets_AMC_0j_A)
# # Background.append(ZJets_AMC_0j_B)
# Background.append(ZJets_AMC_1j_A)
# # Background.append(ZJets_AMC_1j_B)
# # Background.append(ZJets_AMC_2j_A)
# # Background.append(ZJets_AMC_2j_B)
# # Background.append(ZJets_hiM)
# # Background.append(ZJets_MG)
# Background.append(ZJets_MG_HER)
# # Background.append(ZJets_MG_HT_70_100)
# # Background.append(ZJets_MG_HT_100_200_A)
# # Background.append(ZJets_MG_HT_100_200_B)
# # Background.append(ZJets_MG_HT_200_400_A)
# # Background.append(ZJets_MG_HT_200_400_B)
# # Background.append(ZJets_MG_HT_400_600_A)
# # Background.append(ZJets_MG_HT_400_600_B)
# # Background.append(ZJets_MG_HT_600_800)
# # Background.append(ZJets_MG_HT_800_1200)
# # Background.append(ZJets_MG_HT_1200_2500)
# # Background.append(ZJets_MG_HT_2500_inf)

# # ####################
# # ###  Single top  ###
# # ####################

# # tW_pos_1 = sample( name = 'tW_pos_1',
# #                    DAS  = '/ST_tW_top_5f_NoFullyHadronicDecays_13TeV-powheg_TuneCUETP8M1/'+DAS_era_MC+'-v1/MINIAODSIM',
# #                    nEvt = 5372991 ) ## 5 million

# # tW_pos_2 = sample( name = 'tW_pos_2',
# #                    DAS  = '/ST_tW_top_5f_NoFullyHadronicDecays_13TeV-powheg_TuneCUETP8M1/'+DAS_era_MC+'_ext1-v1/MINIAODSIM',
# #                    nEvt = 3256650 ) ## 3 million

# # tW_neg_1 = sample( name = 'tW_neg_1',
# #                    DAS  = '/ST_tW_antitop_5f_NoFullyHadronicDecays_13TeV-powheg_TuneCUETP8M1/'+DAS_era_MC+'-v1/MINIAODSIM',
# #                    nEvt = 5425134 ) ## 5 million

# # tW_neg_2 = sample( name = 'tW_neg_2',
# #                    DAS  = '/ST_tW_antitop_5f_NoFullyHadronicDecays_13TeV-powheg_TuneCUETP8M1/'+DAS_era_MC+'_ext1-v1/MINIAODSIM',
# #                    nEvt = 3256407 ) ## 3 million

# # Background.append(tW_pos_1)
# # Background.append(tW_pos_2)
# # Background.append(tW_neg_1)
# # Background.append(tW_neg_2)

# ###############
# ###  ttbar  ###
# ###############

# # tt = sample( name = 'tt',
# #              DAS  = '/TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8/'+DAS_era_bkg_2+'-v1/MINIAODSIM',
# #              nEvt = 43561608 ) ## 43 million

# # tt_ll_MG_1 = sample( name = 'tt_ll_MG_1',
# #                      DAS  = '/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/'+DAS_era_MC+'-v1/MINIAODSIM',
# #                      nEvt = 6094476 ) ## 6 million

# # tt_ll_MG_2 = sample( name = 'tt_ll_MG_2',
# #                      DAS  = '/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/'+DAS_era_MC+'_ext1-v1/MINIAODSIM',
# #                      nEvt = 24350202 ) ## 24 million

# tt_ll_AMC = sample( name = 'tt_ll_AMC',
#                     DAS  = '/TTJets_Dilept_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8/'+DAS_era_MC+'-v1/MINIAODSIM',
#                     nEvt = 14529280 ) ## 14.5 million

# # Background.append(tt)
# # Background.append(tt_ll_MG_1)
# # Background.append(tt_ll_MG_2)
# Background.append(tt_ll_AMC)

# # #################
# # ###  Diboson  ###
# # #################

# # WW = sample( name = 'WW',
# #              DAS  = '/WWTo2L2Nu_13TeV-powheg/'+DAS_era_MC+'-v1/MINIAODSIM',
# #              nEvt = 1999000 ) ## 2 million

# # WW_HER = sample( name = 'WW_HER',
# #                  DAS  = '/WWTo2L2Nu_13TeV-powheg-herwigpp/'+DAS_era_MC+'-v1/MINIAODSIM',
# #                  nEvt = 1982372 ) ## 2 million

# # WW_up = sample( name = 'WW_up',
# #                 DAS  = '/WWTo2L2Nu_13TeV-powheg-CUETP8M1Up/'+DAS_era_MC+'-v1/MINIAODSIM',
# #                 nEvt =  1984000 ) ## 2 million

# # WW_down = sample( name = 'WW_down',
# #                   DAS  = '/WWTo2L2Nu_13TeV-powheg-CUETP8M1Down/'+DAS_era_MC+'-v1/MINIAODSIM',
# #                   nEvt = 1988000 ) ## 2 million

# # WZ_2l = sample( name = 'WZ_2l',
# #                 DAS  = '/WZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/'+DAS_era_MC+'-v1/MINIAODSIM',
# #                 nEvt =  26517272 ) ## 27 million

# # WZ_3l_AMC = sample( name = 'WZ_3l_AMC',
# #                     DAS  = '/WZTo3LNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/'+DAS_era_MC+'-v1/MINIAODSIM',
# #                     nEvt = 11887464 ) ## 12 million

# # WZ_3l_POW = sample( name = 'WZ_3l_POW',
# #                     DAS  = '/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8/'+DAS_era_MC+'-v1/MINIAODSIM',
# #                     nEvt =  1993200 ) ## 2 million

# # ZZ_2l_2v = sample( name = 'ZZ_2l_2v',
# #                    DAS  = '/ZZTo2L2Nu_13TeV_powheg_pythia8/'+DAS_era_MC+'-v1/MINIAODSIM',
# #                    nEvt = 8842475 ) ## 9 million

# # ZZ_2l_2q = sample( name = 'ZZ_2l_2q',
# #                    DAS  = '/ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/'+DAS_era_MC+'-v1/MINIAODSIM',
# #                    nEvt = 15345572 ) ## 15 million

# # ZZ_4l_AMC = sample( name = 'ZZ_4l_AMC',
# #                     DAS  = '/ZZTo4L_13TeV-amcatnloFXFX-pythia8/'+DAS_era_MC+'_ext1-v1/MINIAODSIM',
# #                     nEvt = 10709784 ) ## 11 million

# ZZ_4l_POW = sample( name = 'ZZ_4l_POW',
#                     DAS  = '/ZZTo4L_13TeV_powheg_pythia8/'+DAS_era_MC+'-v1/MINIAODSIM',
#                     nEvt = 6669988 ) ## 7 million

# # Background.append(WW)
# # # Background.append(WW_HER)
# # # Background.append(WW_up)
# # # Background.append(WW_down)
# # Background.append(WZ_2l)
# # Background.append(WZ_3l_AMC)
# # # Background.append(WZ_3l_POW)
# # Background.append(ZZ_2l_2v)
# # Background.append(ZZ_2l_2q)
# # Background.append(ZZ_4l_AMC)
# Background.append(ZZ_4l_POW)

# # #################
# # ###  Triboson  ##
# # #################

# # WWW = sample( name = 'WWW',
# #               DAS  = '/WWW_4F_TuneCUETP8M1_13TeV-amcatnlo-pythia8/'+DAS_era_MC+'-v1/MINIAODSIM',
# #               nEvt = 240000 ) ## 240 k

# # WWZ = sample( name = 'WWZ',
# #               DAS  = '/WWZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/'+DAS_era_MC+'-v1/MINIAODSIM',
# #               nEvt = 250000 ) ## 250 k

# # WZZ = sample( name = 'WZZ',
# #               DAS  = '/WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/'+DAS_era_MC+'-v1/MINIAODSIM',
# #               nEvt = 246800 ) ## 250 k

# # ZZZ = sample( name = 'ZZZ',
# #               DAS  = '/ZZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/'+DAS_era_MC+'-v1/MINIAODSIM',
# #               nEvt = 249237 ) ## 250 k

# # Background.append(WWW)
# # Background.append(WWZ)
# # Background.append(WZZ)
# # Background.append(ZZZ)

# #####################
# ###  Single top+X  ##
# #####################

# # tZq = sample( name = 'tZq',
# #               DAS  = '/tZq_ll_4f_13TeV-amcatnlo-pythia8/'+DAS_era_MC+'_ext1-v1/MINIAODSIM',
# #               nEvt = 14509520 ) ## 15 million

# tZq_HER = sample( name = 'tZq_HER',
#                   DAS  = '/tZq_ll_4f_13TeV-amcatnlo-herwigpp/'+DAS_era_MC+'-v1/MINIAODSIM',
#                   nEvt = 9999044 ) ## 10 million

# # tZW = sample( name = 'tZW',
# #               DAS  = '/ST_tWll_5f_LO_13TeV-MadGraph-pythia8/'+DAS_era_MC+'-v1/MINIAODSIM',
# #               nEvt = 50000 ) ## 50 k

# # Background.append(tZq)
# Background.append(tZq_HER)
# # Background.append(tZW)

# ################
# ###  ttbar+X  ##
# ################

# ttW_1 = sample( name = 'ttW_1',
#                 DAS  = '/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/'+DAS_era_MC+'_ext1-v3/MINIAODSIM',
#                 nEvt = 2160168 ) ## 2 million

# ttW_2 = sample( name = 'ttW_2',
#                 DAS  = '/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/'+DAS_era_MC+'_ext2-v1/MINIAODSIM',
#                 nEvt = 3120397 ) ## 3 million

# ttZ = sample( name = 'ttZ',
#               DAS  = '/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/'+DAS_era_MC+'_ext1-v1/MINIAODSIM',
#               nEvt = 1992438 ) ## 2 million

# ttH = sample( name = 'ttH',
#               DAS  = '/ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/'+DAS_era_MC+'-v1/MINIAODSIM',
#               nEvt = 3981250 ) ## 4 million

# Background.append(ttW_1)
# Background.append(ttW_2)
# Background.append(ttZ)
# Background.append(ttH)


# DataAndMC = []
# DataAndMC.extend(SingleMu)
# DataAndMC.extend(Signal)
# DataAndMC.extend(Background)

# MC = []
# MC.extend(Signal)
# MC.extend(Background)

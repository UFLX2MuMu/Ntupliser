
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
                         files = [ AWB_dir+'SingleMuon_Run2017C/31Mar2018-v1/ECB43DA6-3B37-E811-AE28-02163E013A0A.root' ],
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
H2Mu_gg_120_NLO = sample( name = 'H2Mu_gg_120',
                          DAS  = '/GluGluHToMuMu_M120_13TeV_amcatnloFXFX_pythia8/'+DAS_era_MC_a+'-v1/MINIAODSIM',
                          nEvt = 1900000 ) ## 1.9 million

H2Mu_gg_125_NLO = sample( name  = 'H2Mu_gg',
                          DAS   = '/GluGluHToMuMu_M125_13TeV_amcatnloFXFX_pythia8/'+DAS_era_MC_a+'-v1/MINIAODSIM',
                          nEvt  = 2000000, ## 2.0 million
                          files = [ AWB_dir+H2Mu_gg_dir+'226E7A92-6D42-E811-B5E3-44A8423D7E31.root' ] )

H2Mu_gg_130_NLO = sample( name = 'H2Mu_gg_130',
                          DAS  = '/GluGluHToMuMu_M130_13TeV_amcatnloFXFX_pythia8/'+DAS_era_MC_a+'-v1/MINIAODSIM',
                          nEvt = 1700000 ) ## 1.7 million

## Vector boson fusion
H2Mu_VBF_120_NLO = sample( name = 'H2Mu_VBF_120',
                           DAS  = '/VBFHToMuMu_M120_13TeV_amcatnloFXFX_pythia8/'+DAS_era_MC_a+'-v1/MINIAODSIM',
                           nEvt = 1000000 ) ## 1.0 million

H2Mu_VBF_125_NLO = sample( name = 'H2Mu_VBF',
                           DAS  = '/VBFHToMuMu_M125_13TeV_amcatnloFXFX_pythia8/'+DAS_era_MC_a+'-v1/MINIAODSIM',
                           nEvt = 1000000 ) ## 1.0 million

H2Mu_VBF_130_NLO = sample( name = 'H2Mu_VBF_130',
                           DAS  = '/VBFHToMuMu_M130_13TeV_amcatnloFXFX_pythia8/'+DAS_era_MC_a+'-v1/MINIAODSIM',
                           nEvt = 965810 ) ## 1.0 million

## WH (+)
H2Mu_WH_pos_120 = sample( name = 'H2Mu_WH_pos_120',
                          DAS  = '/WplusH_HToMuMu_WToAll_M120_13TeV_powheg_pythia8/'+DAS_era_MC_a+'-v1/MINIAODSIM',
                          nEvt = 300000 ) ## 300 k

H2Mu_WH_pos_125 = sample( name = 'H2Mu_WH_pos_125',
                          DAS  = '/WplusH_HToMuMu_WToAll_M125_13TeV_powheg_pythia8/'+DAS_era_MC_a+'-v3/MINIAODSIM',
                          nEvt = 300000 ) ## 300 k

H2Mu_WH_pos_130 = sample( name = 'H2Mu_WH_pos_130',
                          DAS  = '/WplusH_HToMuMu_WToAll_M130_13TeV_powheg_pythia8/'+DAS_era_MC_a+'-v2/MINIAODSIM',
                          nEvt = 288600 ) ## 300 k

## WH (-)
# H2Mu_WH_neg_120 = sample( name = 'H2Mu_WH_neg_120',
#                           DAS  = '/WMinusH_HToMuMu_M120_13TeV_powheg_pythia8/'+DAS_era_MC_a+'-v1/MINIAODSIM',
#                           nEvt = 125000 ) ## 125 k

H2Mu_WH_neg_125 = sample( name = 'H2Mu_WH_neg_125',
                          DAS  = '/WminusH_HToMuMu_WToAll_M125_13TeV_powheg_pythia8/'+DAS_era_MC_a+'-v1/MINIAODSIM',
                          nEvt = 300000 ) ## 300 k

H2Mu_WH_neg_130 = sample( name = 'H2Mu_WH_neg_130',
                          DAS  = '/WminusH_HToMuMu_WToAll_M130_13TeV_powheg_pythia8/'+DAS_era_MC_a+'-v1/MINIAODSIM',
                          nEvt = 287460 ) ## 300 k

## ZH
H2Mu_ZH_120 = sample( name = 'H2Mu_ZH_120',
                      DAS  = '/ZH_HToMuMu_ZToAll_M120_13TeV_powheg_pythia8/'+DAS_era_MC_a+'-v2/MINIAODSIM',
                      nEvt = 285500 ) ## 300 k

H2Mu_ZH_125 = sample( name = 'H2Mu_ZH_125',
                      DAS  = '/ZH_HToMuMu_ZToAll_M125_13TeV_powheg_pythia8/'+DAS_era_MC_a+'-v1/MINIAODSIM',
                      nEvt = 296904 ) ## 300 k

H2Mu_ZH_130 = sample( name = 'H2Mu_ZH_130',
                      DAS  = '/ZH_HToMuMu_ZToAll_M130_13TeV_powheg_pythia8/'+DAS_era_MC_a+'-v1/MINIAODSIM',
                      nEvt = 297102 ) ## 300 k

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
Signal.append(H2Mu_VBF_125_NLO)
Signal.append(H2Mu_WH_pos_125)
Signal.append(H2Mu_WH_neg_125)
Signal.append(H2Mu_ZH_125)
Signal.append(H2Mu_ttH_125)

Signal.append(H2Mu_gg_120_NLO)
Signal.append(H2Mu_VBF_120_NLO)
Signal.append(H2Mu_WH_pos_120)
# Signal.append(H2Mu_WH_neg_120)
Signal.append(H2Mu_ZH_120)

Signal.append(H2Mu_gg_130_NLO)
Signal.append(H2Mu_VBF_130_NLO)
Signal.append(H2Mu_WH_pos_130)
Signal.append(H2Mu_WH_neg_130)
Signal.append(H2Mu_ZH_130)



# # =======================================================================================================
# # ------------------------------- BACKGROUND ------------------------------------------------------------
# # =======================================================================================================

Background = []  ## All H2Mu background samples

# DAS_era_bkg_2 = 'RunIISummer16MiniAODv3-PUMoriond17_backup_80X_mcRun2_asymptotic_2016_TrancheIV_v6'
# DAS_AMC       = 'TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring16MiniAODv'

###################
###  Drell-Yan  ###
###################

ZJets_AMC = sample( name = 'ZJets_AMC',
                    DAS  = '/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/'+DAS_era_MC_b+'_ext1-v1/MINIAODSIM',
                    nEvt = 182217609)  ## 182 million

ZJets_MG_1 = sample( name = 'ZJets_MG_1',
                     DAS  = '/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/'+DAS_era_MC_c+'-v1/MINIAODSIM',
                     nEvt = 48675378 ) ## 49 million

ZJets_MG_2 = sample( name = 'ZJets_MG_2',
                     DAS  = '/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/'+DAS_era_MC_c+'_ext1-v1/MINIAODSIM',
                     nEvt = 49125561 ) ## 49 million

# ZJets_hiM_AMC = sample( name = 'ZJets_hiM_AMC',
#                         DAS  = '/DYJetsToLL_M-105To160_TuneCP5_PSweights_13TeV-amcatnloFXFX-pythia8/RunIIFall17MiniAODv2*/MINIAODSIM',
#                         nEvt =  )  ## 60 million

# ZJets_hiM_MG = sample( name = 'ZJets_hiM_MG',
#                        DAS  = '/DYJetsToLL_M-105To160_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2*/MINIAODSIM',
#                        nEvt =  )  ## ? million


Background.append(ZJets_AMC)
Background.append(ZJets_MG_1)
Background.append(ZJets_MG_2)
# Background.append(ZJets_hiM_AMC)
# Background.append(ZJets_hiM_MG)

###############
###  ttbar  ###
###############

tt_ll_MG = sample( name = 'tt_ll_MG',
                   DAS  = '/TTJets_DiLept_TuneCP5_13TeV-madgraphMLM-pythia8/'+DAS_era_MC_a+'-v1/MINIAODSIM',
                   nEvt = 28380110 ) ## 28 million

tt_ll_POW = sample( name = 'tt_ll_POW',
                    DAS  = '/TTTo2L2Nu_TuneCP5_PSweights_13TeV-powheg-pythia8/'+DAS_era_MC_b+'-v2/MINIAODSIM',
                    nEvt = 69155808 ) ## 69 million

tt_ljj_POW_1 = sample ( name = 'tt_ljj_POW_1',
                        DAS  = '/TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8/'+DAS_era_MC_a+'-v1/MINIAODSIM',
                        nEvt = 111325048 ) ## 111 million

tt_ljj_POW_2 = sample ( name = 'tt_ljj_POW_2',
                        DAS  = '/TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8/'+DAS_era_MC_a+'-v2/MINIAODSIM',
                        nEvt = 110085096 ) ## 110 million

Background.append(tt_ll_MG)
Background.append(tt_ll_POW)
Background.append(tt_ljj_POW_1)
Background.append(tt_ljj_POW_2)

####################
###  Single top  ###
####################

tW_pos = sample( name = 'tW_pos',
                 DAS  = '/ST_tW_top_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8/'+DAS_era_MC_b+'-v1/MINIAODSIM',
                 nEvt = 4955102 ) ## 5 million

tW_neg = sample( name = 'tW_neg',
                 DAS  = '/ST_tW_antitop_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8/'+DAS_era_MC_b+'-v1/MINIAODSIM',
                 nEvt = 5635539 ) ## 5 million

Background.append(tW_pos)
Background.append(tW_neg)

#################
###  Diboson  ###
#################

WW_2l_1 = sample( name = 'WW_2l_1',
             DAS  = '/WWTo2L2Nu_NNPDF31_TuneCP5_13TeV-powheg-pythia8/'+DAS_era_MC_a+'-v1/MINIAODSIM',
             nEvt = 2000000 ) ## 2 million

WW_2l_2 = sample( name = 'WW_2l_2',
               DAS = '/WWTo2L2Nu_NNPDF31_TuneCP5_PSweights_13TeV-powheg-pythia8/'+DAS_era_MC_a+'_ext1-v1/MINIAODSIM',
             nEvt = 2000000 ) ## 2 million

WZ_2l = sample( name = 'WZ_2l',
                DAS  = '/WZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/'+DAS_era_MC_a+'-v1/MINIAODSIM',
                nEvt =  27582164 ) ## 28 million

WZ_3l = sample( name = 'WZ_3l',
                DAS  = '/WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8/'+DAS_era_MC_b+'-v1/MINIAODSIM',
                nEvt = 10987679 ) ## 11 million

ZZ_2l_2q = sample( name = 'ZZ_2l_2q',
                   DAS  = '//ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/'+DAS_era_MC_a+'-v1/MINIAODSIM/',
                   nEvt = 27840918 ) ## 28 million

ZZ_4l = sample( name = 'ZZ_4l',
                DAS  = '/ZZTo4L_13TeV_powheg_pythia8/'+DAS_era_MC_a+'_ext1-v1/MINIAODSIM',
                nEvt = 98091559 ) ## 98 million

Background.append(WW_2l_1)
Background.append(WW_2l_2)
Background.append(WZ_2l)
Background.append(WZ_3l)
Background.append(ZZ_2l_2q)
Background.append(ZZ_4l)

################
###  ttbar+X  ##
################

ttW = sample( name = 'ttW',
              DAS  = '/TTWJetsToLNu_TuneCP5_PSweights_13TeV-amcatnloFXFX-madspin-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1/MINIAODSIM',
              nEvt = 4908905 ) ## 4.9 million


ttZ = sample( name = 'ttZ',
              DAS  = '/TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM',
              nEvt = 7563490 ) ## 7.5 million

ttZ_lowM = sample( name = 'ttZ_lowM',
                   DAS  = '/TTZToLL_M-1to10_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM',
                   nEvt = 250000 ) ## 250 k
ttH = sample( name = 'ttH',
              DAS  = '/ttHJetToNonbb_M125_TuneCP5_13TeV_amcatnloFXFX_madspin_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1/MINIAODSIM',
              nEvt = 9779592 ) ## 10 million

ttWW = sample( name = 'ttWW',
               DAS  = '/TTWW_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM',
               nEvt = 200000 ) ## 200 k

Background.append(ttW)
Background.append(ttZ)
Background.append(ttZ_lowM)
Background.append(ttH)
Background.append(ttWW)

# #####################
# ###  Single top+X  ##
# #####################

tZq = sample( name = 'tZq',
              DAS  = '/tZq_ll_4f_ckm_NLO_TuneCP5_PSweights_13TeV-amcatnlo-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v2/MINIAODSIM',
              nEvt = 13276146 ) ## 13 million

# tZW = sample( name = 'tZW',
#               DAS  = '/ST_tWll_5f_LO_TuneCP5_PSweights_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2*/MINIAODSIM',
#               nEvt =  ) ## 

tHq = sample( name = 'tHq',
              DAS  = '/THQ_4f_Hincl_13TeV_madgraph_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM',
              nEvt = 3381548 ) ## 3 million

tHW = sample( name = 'tHW',
              DAS  = '/THW_5f_Hincl_13TeV_madgraph_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM',
              nEvt = 1439996 ) ## 1 million

Background.append(tZq)
# Background.append(tZW)
Background.append(tHq)
Background.append(tHW)

#################
###  Triboson  ##
#################

WWW = sample( name = 'WWW',
              DAS  = '/WWW_4F_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM',
              nEvt = 232300 ) ## 230 k

WWZ = sample( name = 'WWZ',
              DAS  = '/WWZ_4F_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM',
              nEvt = 250000 ) ## 250 k

WZZ = sample( name = 'WZZ',
              DAS  = '/WZZ_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM',
              nEvt = 250000 ) ## 250 k

ZZZ = sample( name = 'ZZZ',
              DAS  = '/ZZZ_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM',
              nEvt = 250000 ) ## 250 k

Background.append(WWW)
Background.append(WWZ)
Background.append(WZZ)
Background.append(ZZZ)


DataAndMC = []
DataAndMC.extend(SingleMu)
# DataAndMC.extend(DoubleMu)
DataAndMC.extend(Signal)
DataAndMC.extend(Background)

MC = []
MC.extend(Signal)
MC.extend(Background)

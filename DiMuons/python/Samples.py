
class sample:
    def __init__(self, name='', DAS='', inputDBS='global', nEvt=-1, files=[], 
                 GT='94X_mc2017_realistic_v17', JEC='94X_mc2017_realistic_v17', 
                 runs=[], JSON=[], isData=False):
        self.name   = name   ## User-assigned dataset name
        self.DAS    = DAS    ## DAS directory
        self.inputDBS = inputDBS  # to be used in crab in case of private production. config.Data.inputDBS = 'global' or 'phys03'
        self.nEvt   = nEvt   ## Number of events in dataset
        self.files  = files  ## Local files for testing
        self.GT     = GT     ## Global tag
        self.JEC    = JEC    ## Jet energy corrections global tag # https://twiki.cern.ch/twiki/bin/view/CMS/JECDataMC#Recommended_for_MC
        self.runs   = runs   ## Run range
        self.JSON   = JSON   ## JSON file
        self.isData = isData ## Is data

# =======================================================================================================
# ------------------------------- DATA ------------------------------------------------------------------
# =======================================================================================================

# The JSON file details the valid lumi sections
## JSON files: https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions17/13TeV/Final/Cert_294927-306462_13TeV_PromptReco_Collisions17_JSON.txt
JSON_2017 = ['data/JSON/2017/Cert_294927-306462_13TeV_PromptReco_Collisions17_JSON.txt']  ## 41.86 /fb

#####################################
###  Global tag and dataset info  ###
#####################################

# 2017 Data analysis recommendation
# More info at https://twiki.cern.ch/twiki/bin/view/CMS/PdmV2017Analysis
# Suggested GT (see frontier conditions twiki for more info)
# JEC recommendation from https://twiki.cern.ch/twiki/bin/view/CMS/JECDataMC#Recommended_for_MC

# ReReco MINIAOD 31March2018
# GT for data : 94X_dataRun2_v11
# JEC for data : 94X_dataRun2_v11

SingleMu_2017B = sample ( name   = 'SingleMu_2017B',
                          DAS    = '/SingleMuon/Run2017B-31Mar2018-v1/MINIAOD',
                          GT     = '94X_dataRun2_v11',
                          JEC    = '94X_dataRun2_v11',
                          files = ['/store/data/Run2017B/SingleMuon/MINIAOD/31Mar2018-v1/80000/0E555487-7241-E811-9209-002481CFC92C.root'],
                          JSON   = JSON_2017[0],
                          isData = True )

SingleMu_2017C = sample ( name   = 'SingleMu_2017C',
                          DAS    = '/SingleMuon/Run2017C-31Mar2018-v1/MINIAOD',
                          GT     = '94X_dataRun2_v11',
                          JEC    = '94X_dataRun2_v11',
                          JSON   = JSON_2017[0],
                          isData = True )


SingleMu_2017D = sample ( name   = 'SingleMu_2017D',
                          DAS    = '/SingleMuon/Run2017D-31Mar2018-v1/MINIAOD',
                          GT     = '94X_dataRun2_v11',
                          JEC    = '94X_dataRun2_v11',
                          JSON   = JSON_2017[0],
                          isData = True )


SingleMu_2017E = sample ( name   = 'SingleMu_2017E',
                          DAS    = '/SingleMuon/Run2017E-31Mar2018-v1/MINIAOD',
                          GT     = '94X_dataRun2_v11',
                          JEC    = '94X_dataRun2_v11',
                          JSON   = JSON_2017[0],
                          isData = True )


SingleMu_2017F = sample ( name   = 'SingleMu_2017F',
                          DAS    = '/SingleMuon/Run2017F-31Mar2018-v1/MINIAOD',
                          GT     = '94X_dataRun2_v11',
                          JEC    = '94X_dataRun2_v11',
                          JSON   = JSON_2017[0],
                          isData = True )


## Up-to-date GT info: https://twiki.cern.ch/twiki/bin/view/CMS/PdmV2017Analysis

## Jet energy correction info
## https://twiki.cern.ch/twiki/bin/view/CMS/JECDataMC
## https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookJetEnergyCorrections

SingleMu = []  ## All SingleMuon datasets

SingleMu.append(SingleMu_2017B)
SingleMu.append(SingleMu_2017C)
SingleMu.append(SingleMu_2017D)
SingleMu.append(SingleMu_2017E)
SingleMu.append(SingleMu_2017F)

###################
## DOUBLE MUON ####
###################

DoubleMu_2017B = sample( name   = 'DoubleMu_2017B',
                         DAS    = '/DoubleMuon/Run2017B-31Mar2018-v1/MINIAOD',
                         GT     = '94X_dataRun2_v11',
                         JEC    = '94X_dataRun2_v11',
                         JSON   = JSON_2017,
                         isData = True)

DoubleMu_2017C = sample( name   = 'DoubleMu_2017C',
                         DAS    = '/DoubleMuon/Run2017C-31Mar2018-v1/MINIAOD',
                         GT     = '94X_dataRun2_v11',
                         JEC    = '94X_dataRun2_v11',
                         JSON   = JSON_2017,
                         isData = True)

DoubleMu_2017D = sample( name   = 'DoubleMu_2017D',
                         DAS    = '/DoubleMuon/Run2017D-31Mar2018-v1/MINIAOD',
                         GT     = '94X_dataRun2_v11',
                         JEC    = '94X_dataRun2_v11',
                         JSON   = JSON_2017,
                         isData = True)

DoubleMu_2017E = sample( name   = 'DoubleMu_2017E',
                         DAS    = '/DoubleMuon/Run2017E-31Mar2018-v1/MINIAOD',
                         GT     = '94X_dataRun2_v11',
                         JEC    = '94X_dataRun2_v11',
                         JSON   = JSON_2017,
                         isData = True)

DoubleMu_2017F = sample( name   = 'DoubleMu_2017F',
                         DAS    = '/DoubleMuon/Run2017F-31Mar2018-v1/MINIAOD',
                         GT     = '94X_dataRun2_v11',
                         JEC    = '94X_dataRun2_v11',
                         JSON   = JSON_2017,
                         isData = True)


DoubleMu = []  ## All DoubleMuon datasets

DoubleMu.append(DoubleMu_2017B)
DoubleMu.append(DoubleMu_2017C)
DoubleMu.append(DoubleMu_2017D)
DoubleMu.append(DoubleMu_2017E)
DoubleMu.append(DoubleMu_2017F)



# =======================================================================================================
# ------------------------------- SIGNAL ----------------------------------------------------------------
# =======================================================================================================

## GT suggested by JETMET POG for MC for new JEC
## 94X_mc2017_realistic_v13

## MC spreadsheet: https://docs.google.com/spreadsheets/d/192q__wqy9o-1J1Twv1AkqmLYu2Vijg62nGBaF3vGyEk
## MC DAS location: dataset=/*/RunIIFall17MiniAODv2*/MINIAODSIM
DAS_era_MC_a = 'RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14'
DAS_era_MC_b = 'RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14'
DAS_era_MC_c = 'RunIIFall17MiniAODv2-PU2017RECOSIMstep_12Apr2018_94X_mc2017_realistic_v14'


## Gluon-gluon fusion

H2Mu_gg_120_NLO = sample( name = 'H2Mu_gg_120_NLO',
                          DAS  = '/GluGluHToMuMu_M120_13TeV_amcatnloFXFX_pythia8/'+DAS_era_MC_a+'-v1/MINIAODSIM',
                          nEvt = -1 ) ## 1.9 million


H2Mu_gg_125_NLO = sample( name  = 'H2Mu_gg_125_NLO',
                  DAS   = '/GluGluHToMuMu_M125_13TeV_amcatnloFXFX_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM',
                  files  = ['/store/mc/RunIIFall17MiniAODv2/GluGluHToMuMu_M125_13TeV_amcatnloFXFX_pythia8/MINIAODSIM/PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/20000/5AC9148F-9842-E811-892B-3417EBE535DA.root'],
                  nEvt  = -1
                )

H2Mu_gg_130_NLO = sample( name = 'H2Mu_gg_130_NLO',
                          DAS  = '/GluGluHToMuMu_M130_13TeV_amcatnloFXFX_pythia8/'+DAS_era_MC_a+'-v1/MINIAODSIM',
                          nEvt = -1 ) ## 1.7 million


## Vector boson fusion
H2Mu_VBF_120_NLO_1 = sample( name = 'H2Mu_VBF_120_NLO_1',
                              DAS  = '/VBFHToMuMu_M120_TuneCP5_PSweights_13TeV_amcatnlo_pythia8/'+DAS_era_MC_a+'-v1/MINIAODSIM',
                              nEvt = -1 ) ## In production - AWB 04.04.2019

H2Mu_VBF_120_NLO_2 = sample( name = 'H2Mu_VBF_120_NLO_2',
                             DAS  = '/VBFHToMuMu_M120_TuneCP5_PSweights_13TeV_amcatnlo_pythia8/'+DAS_era_MC_a+'-v2/MINIAODSIM',
                             nEvt = -1 ) ## 1.0 million

H2Mu_VBF_125_NLO_1 = sample( name  = 'H2Mu_VBF_125_NLO_1',
                             DAS   = '/VBFHToMuMu_M125_TuneCP5_PSweights_13TeV_amcatnlo_pythia8/'+DAS_era_MC_a+'-v1/MINIAODSIM',
                             nEvt  = -1, ## 500 k
                             files = [ '/store/mc/RunIIFall17MiniAODv2/VBFHToMuMu_M125_TuneCP5_PSweights_13TeV_amcatnlo_pythia8/MINIAODSIM/PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/60000/F43846F1-7945-E911-973C-0CC47AFF02FC.root' ] )

H2Mu_VBF_125_NLO_2 = sample( name = 'H2Mu_VBF_125_NLO_2',
                             DAS  = '/VBFHToMuMu_M125_TuneCP5_PSweights_13TeV_amcatnlo_pythia8/'+DAS_era_MC_a+'_ext1-v1/MINIAODSIM',
                             nEvt = -1 ) ## 475 k

H2Mu_VBF_130_NLO_1 = sample( name = 'H2Mu_VBF_130_NLO_1',
                              DAS  = '/VBFHToMuMu_M130_TuneCP5_PSweights_13TeV_amcatnlo_pythia8/'+DAS_era_MC_a+'-v1/MINIAODSIM',
                              nEvt = -1 ) ## In production - AWB 04.04.2019

H2Mu_VBF_130_NLO_2 = sample( name = 'H2Mu_VBF_130_NLO_2',
                             DAS  = '/VBFHToMuMu_M130_TuneCP5_PSweights_13TeV_amcatnlo_pythia8/'+DAS_era_MC_a+'-v1/MINIAODSIM',
                             nEvt = -1 ) ## 1.0 million

## WH (+)
H2Mu_WH_pos_120 = sample( name = 'H2Mu_WH_pos_120',
                          DAS  = '/WplusH_HToMuMu_WToAll_M120_13TeV_powheg_pythia8/'+DAS_era_MC_a+'-v1/MINIAODSIM',
                          nEvt = -1 ) ## 300 k

H2Mu_WH_pos_125 = sample( name = 'H2Mu_WH_pos_125',
                          DAS  = '/WplusH_HToMuMu_WToAll_M125_13TeV_powheg_pythia8/'+DAS_era_MC_a+'-v3/MINIAODSIM',
                          nEvt = -1 ) ## 300 k

H2Mu_WH_pos_130 = sample( name = 'H2Mu_WH_pos_130',
                          DAS  = '/WplusH_HToMuMu_WToAll_M130_13TeV_powheg_pythia8/'+DAS_era_MC_a+'-v2/MINIAODSIM',
                          nEvt = -1 ) ## 300 k

## WH (-)
H2Mu_WH_neg_120 = sample( name = 'H2Mu_WH_neg_120',
                          DAS  = '/WminusH_HToMuMu_WToAll_M120_13TeV_powheg_pythia8/'+DAS_era_MC_a+'-v1/MINIAODSIM',
                          nEvt = -1 ) ## 300 k

H2Mu_WH_neg_125 = sample( name = 'H2Mu_WH_neg_125',
                          DAS  = '/WminusH_HToMuMu_WToAll_M125_13TeV_powheg_pythia8/'+DAS_era_MC_a+'-v1/MINIAODSIM',
                          nEvt = -1 ) ## 300 k

H2Mu_WH_neg_130 = sample( name = 'H2Mu_WH_neg_130',
                          DAS  = '/WminusH_HToMuMu_WToAll_M130_13TeV_powheg_pythia8/'+DAS_era_MC_a+'-v1/MINIAODSIM',
                          nEvt = -1 ) ## 300 k

## ZH
H2Mu_ZH_120 = sample( name = 'H2Mu_ZH_120',
                      DAS  = '/ZH_HToMuMu_ZToAll_M120_13TeV_powheg_pythia8/'+DAS_era_MC_a+'-v2/MINIAODSIM',
                      nEvt = -1 ) ## 300 k

H2Mu_ZH_125 = sample( name = 'H2Mu_ZH_125',
                      DAS  = '/ZH_HToMuMu_ZToAll_M125_13TeV_powheg_pythia8/'+DAS_era_MC_a+'-v1/MINIAODSIM',
                      nEvt = -1 ) ## 300 k

H2Mu_ZH_130 = sample( name = 'H2Mu_ZH_130',
                      DAS  = '/ZH_HToMuMu_ZToAll_M130_13TeV_powheg_pythia8/'+DAS_era_MC_a+'-v1/MINIAODSIM',
                      nEvt = -1 ) ## 300 k

## ttH
H2Mu_ttH_120 = sample( name = 'H2Mu_ttH_120',
                       DAS  = '/ttHToMuMu_M120_TuneCP5_13TeV-powheg-pythia8/'+DAS_era_MC_a+'-v1/MINIAODSIM',
                       nEvt = -1 ) ## 300 k

H2Mu_ttH_125 = sample( name = 'H2Mu_ttH_125',
                       DAS  = '/ttHToMuMu_M125_TuneCP5_13TeV-powheg-pythia8/'+DAS_era_MC_a+'-v3/MINIAODSIM',
                       nEvt = -1 ) ## 300 k
                    

H2Mu_ttH_130 = sample( name = 'H2Mu_ttH_130',
                       DAS  = '/ttHToMuMu_M130_TuneCP5_13TeV-powheg-pythia8/'+DAS_era_MC_a+'-v1/MINIAODSIM',
                       nEvt = -1 ) ## 300 k

## pre-approval requests
H2Mu_THW_125 = sample( name = 'H2Mu_THW_125',
                       DAS  = '/THW_HToMuMu_TuneCP5_13TeV-madgraph-pythia/rgerosa-RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-MINIAODSIM-092dbe4ee9b874883e19626ddbf3d288/USER',
                       inputDBS = 'phys03',
                       nEvt = -1 ) ## 300 k

H2Mu_THQ_125 = sample( name = 'H2Mu_THQ_125',
                       DAS  = '/THQ_HToMuMu_TuneCP5_13TeV-madgraph-pythia/rgerosa-RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-MINIAODSIM-092dbe4ee9b874883e19626ddbf3d288/USER',
                       inputDBS = 'phys03',
                       nEvt = -1,
                       files= ['/store/user/rgerosa/PrivateMC/THQ_HToMuMu_TuneCP5_13TeV-madgraph-pythia/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-MINIAODSIM/200430_162419/0000/miniAOD_step_256.root'] ) ## 300 k

H2Mu_ggZH_125 = sample( name = 'H2Mu_ggZH_125',
                       DAS  = '/ggZH_HToMuMu_ZToLL_M125_13TeV_powheg_pythia8/rgerosa-RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-MINIAODSIM-092dbe4ee9b874883e19626ddbf3d288/USER',
                       inputDBS = 'phys03',
                       nEvt = -1 ) ## 300 k

H2Mu_bbH_125 = sample( name = 'H2Mu_bbH_125',
                       DAS  = '/bbHToMuMu_M-125_4FS_yb2_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM',
                       nEvt = -1 ) ## 300 k


Signal = []  ## All H2Mu signal samples
Signal.append(H2Mu_gg_125_NLO)
Signal.append(H2Mu_VBF_125_NLO_1)
Signal.append(H2Mu_VBF_125_NLO_2)
Signal.append(H2Mu_WH_pos_125)
Signal.append(H2Mu_WH_neg_125)
Signal.append(H2Mu_ZH_125)
Signal.append(H2Mu_ttH_125)

Signal.append(H2Mu_gg_120_NLO)
Signal.append(H2Mu_VBF_120_NLO_1)
Signal.append(H2Mu_VBF_120_NLO_2)
Signal.append(H2Mu_WH_pos_120)
Signal.append(H2Mu_WH_neg_120)
Signal.append(H2Mu_ZH_120)

Signal.append(H2Mu_gg_130_NLO)
Signal.append(H2Mu_VBF_130_NLO_1)
Signal.append(H2Mu_VBF_130_NLO_2)
Signal.append(H2Mu_WH_pos_130)
Signal.append(H2Mu_WH_neg_130)
Signal.append(H2Mu_ZH_130)
Signal.append(H2Mu_ttH_130)

Signal.append(H2Mu_ggZH_125)
Signal.append(H2Mu_THQ_125)
Signal.append(H2Mu_THW_125)
Signal.append(H2Mu_bbH_125)


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
                    nEvt = -1 )  ## 182 million

ZJets_MG_1 = sample( name = 'ZJets_MG_1',
                     DAS  = '/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/'+DAS_era_MC_c+'-v1/MINIAODSIM',
                     nEvt = -1 ) ## 49 million

ZJets_MG_2 = sample( name = 'ZJets_MG_2',
                     DAS  = '/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/'+DAS_era_MC_c+'_ext1-v1/MINIAODSIM',
                     nEvt = -1 ) ## 49 million

ZJets_hiM_AMC = sample( name = 'ZJets_hiM_AMC',
                        DAS  = '/DYJetsToLL_M-105To160_TuneCP5_PSweights_13TeV-amcatnloFXFX-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM',
                        nEvt = -1 )  ## 53 million

ZJets_hiM_MG = sample( name = 'ZJets_hiM_MG',
                       DAS  = '/DYJetsToLL_M-105To160_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM',
                       nEvt = -1 )  ## 58 million -- SO FAR!!! AWB 02.04.2019

Background.append(ZJets_AMC)
Background.append(ZJets_MG_1)
Background.append(ZJets_MG_2)
Background.append(ZJets_hiM_AMC)
Background.append(ZJets_hiM_MG)

###############
###  ttbar  ###
###############

tt_ll_MG = sample( name = 'tt_ll_MG',
                   DAS  = '/TTJets_DiLept_TuneCP5_13TeV-madgraphMLM-pythia8/'+DAS_era_MC_a+'-v1/MINIAODSIM',
                   nEvt = -1 ) ## 28 million

tt_ll_POW = sample( name = 'tt_ll_POW',
                    DAS  = '/TTTo2L2Nu_TuneCP5_PSweights_13TeV-powheg-pythia8/'+DAS_era_MC_b+'-v2/MINIAODSIM',
                    nEvt = -1 ) ## 69 million

tt_ljj_POW = sample ( name = 'tt_ljj_POW',
                      DAS  = '/TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8/'+DAS_era_MC_a+'-v2/MINIAODSIM',
                      nEvt = -1 ) ## 110 million

Background.append(tt_ll_MG)
Background.append(tt_ll_POW)
Background.append(tt_ljj_POW)

####################
###  Single top  ###
####################

tW_pos = sample( name = 'tW_pos',
                 DAS  = '/ST_tW_top_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8/'+DAS_era_MC_b+'-v1/MINIAODSIM',
                 nEvt = -1 ) ## 5 million

tW_neg = sample( name = 'tW_neg',
                 DAS  = '/ST_tW_antitop_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8/'+DAS_era_MC_b+'-v1/MINIAODSIM',
                 nEvt = -1 ) ## 5 million

Background.append(tW_pos)
Background.append(tW_neg)

#################
###  Diboson  ###
#################

WW_2l_1 = sample( name = 'WW_2l_1',
             DAS  = '/WWTo2L2Nu_NNPDF31_TuneCP5_13TeV-powheg-pythia8/'+DAS_era_MC_a+'-v1/MINIAODSIM',
             nEvt = -1 ) ## 2 million

WW_2l_2 = sample( name = 'WW_2l_2',
               DAS = '/WWTo2L2Nu_NNPDF31_TuneCP5_PSweights_13TeV-powheg-pythia8/'+DAS_era_MC_a+'_ext1-v1/MINIAODSIM',
             nEvt = -1 ) ## 2 million

WZ_2l = sample( name = 'WZ_2l',
                DAS  = '/WZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/'+DAS_era_MC_a+'-v1/MINIAODSIM',
                nEvt = -1 ) ## 28 million

WZ_3l = sample( name = 'WZ_3l',
                DAS  = '/WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8/'+DAS_era_MC_b+'-v1/MINIAODSIM',
                nEvt = -1 ) ## 11 million

ZZ_2l_2q = sample( name = 'ZZ_2l_2q',
                   DAS  = '/ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/'+DAS_era_MC_a+'-v1/MINIAODSIM',
                   nEvt = -1 ) ## 28 million

ZZ_4l = sample( name = 'ZZ_4l',
                DAS  = '/ZZTo4L_13TeV_powheg_pythia8/'+DAS_era_MC_a+'_ext1-v1/MINIAODSIM',
                nEvt = -1 ) ## 98 million

ZZ_4l_gg_2e2mu = sample( name = 'ZZ_4l_gg_2e2mu',
                         DAS  = '/GluGluToContinToZZTo2e2mu_13TeV_MCFM701_pythia8/'+DAS_era_MC_a+'-v1/MINIAODSIM',
                         nEvt = -1 ) ## 1.5 million

ZZ_4l_gg_4mu = sample( name = 'ZZ_4l_gg_4mu',
                       DAS  = '/GluGluToContinToZZTo4mu_13TeV_MCFM701_pythia8/'+DAS_era_MC_a+'-v1/MINIAODSIM',
                       nEvt = -1 ) ## 924 k

Background.append(WW_2l_1)
Background.append(WW_2l_2)
Background.append(WZ_2l)
Background.append(WZ_3l)
Background.append(ZZ_2l_2q)
Background.append(ZZ_4l)
Background.append(ZZ_4l_gg_2e2mu)
Background.append(ZZ_4l_gg_4mu)

################
###  ttbar+X  ##
################

ttW = sample( name = 'ttW',
              DAS  = '/TTWJetsToLNu_TuneCP5_PSweights_13TeV-amcatnloFXFX-madspin-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1/MINIAODSIM',
              nEvt = -1 ) ## 4.9 million


ttZ = sample( name = 'ttZ',
              DAS  = '/TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM',
              nEvt = -1 ) ## 7.5 million

ttZ_lowM = sample( name = 'ttZ_lowM',
                   DAS  = '/TTZToLL_M-1to10_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM',
                   nEvt = -1 ) ## 250 k
ttH = sample( name = 'ttH',
              DAS  = '/ttHJetToNonbb_M125_TuneCP5_13TeV_amcatnloFXFX_madspin_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1/MINIAODSIM',
              nEvt = -1 ) ## 10 million

ttWW = sample( name = 'ttWW',
               DAS  = '/TTWW_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM',
               nEvt = -1 ) ## 200 k

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
              nEvt = -1 ) ## 13 million

tZW = sample( name = 'tZW',
              DAS  = '/ST_tWll_5f_LO_TuneCP5_PSweights_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM',
              nEvt = -1 ) ## 1 million

tHq = sample( name = 'tHq',
              DAS  = '/THQ_4f_Hincl_13TeV_madgraph_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM',
              nEvt = -1 ) ## 3 million

tHW = sample( name = 'tHW',
              DAS  = '/THW_5f_Hincl_13TeV_madgraph_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM',
              nEvt = -1 ) ## 1 million

Background.append(tZq)
# Background.append(tZW)
Background.append(tHq)
Background.append(tHW)

#################
###  Triboson  ##
#################

WWW = sample( name = 'WWW',
              DAS  = '/WWW_4F_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM',
              nEvt = -1 ) ## 230 k

WWZ = sample( name = 'WWZ',
              DAS  = '/WWZ_4F_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM',
              nEvt = -1 ) ## 250 k

WZZ = sample( name = 'WZZ',
              DAS  = '/WZZ_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM',
              nEvt = -1 ) ## 250 k

ZZZ = sample( name = 'ZZZ',
              DAS  = '/ZZZ_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM',
              nEvt = -1 ) ## 250 k

Background.append(WWW)
Background.append(WWZ)
Background.append(WZZ)
Background.append(ZZZ)


####################
### Combinations ###
####################

DataAndMC = []
DataAndMC.extend(SingleMu)
# DataAndMC.extend(DoubleMu)
DataAndMC.extend(Signal)
DataAndMC.extend(Background)

MC = []
MC.extend(Signal)
MC.extend(Background)

#create dictionary
samples_dictionary = {sample.name:sample for sample in DataAndMC}



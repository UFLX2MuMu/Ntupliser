
class sample:
    def __init__(self, name='', DAS='', inputDBS='global', nEvt=0, files=[], GT='94X_mcRun2_asymptotic_v3', 
                 JEC='Summer16_23Sep2016V4MC', runs=[], JSON=[], isData=False):
        self.name   = name   ## User-assigned dataset name
        self.DAS    = DAS    ## DAS directory
        self.inputDBS = inputDBS  # to be used in crab in case of private production. config.Data.inputDBS = 'global' or 'phys03'
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
## JSON files: https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions17/13TeV/ReReco/
golden_23Sep2016ReReco = 'data/JSON/2016/Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt'


processed_dataset = ['RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1', #0 
                     'RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2', #1
                     'RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext2-v1', #2
                     'RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2', #3
                     'RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext2-v2', #4
                     'RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v3', #5
                     'RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1', #6
                     'RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext2-v1', #7
                     'RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext3-v1' #8
                     ]


data_tier = ['MINIAOD',
             'MINIAODSIM']

all_samples = []

#####################################
###  Global tag and dataset info  ###
#####################################

## 94x v2 miniAOD info: https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookMiniAOD#2016_Data_legacy_re_miniAOD_17Ju
##   * Last check that MC   GT 94X_mcRun2_asymptotic_v3 was up-to-date: 19.10.2018 (AWB)
##   * Last check that data GT 94X_dataRun2_v10         was up-to-date: 19.10.2018 (AWB)

## GT info does not appear to be up-to-date: https://twiki.cern.ch/twiki/bin/view/CMS/PdmV2016Analysis
## Likewise in Frontier Conditions, latest info is for 80X "legacy" reprocessing
##   * https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideFrontierConditions#Global_Tags_for_2016_legacy_data

## Jet energy correction info
## https://twiki.cern.ch/twiki/bin/view/CMS/JECDataMC
##  - Last check that data JEC Summer16_07Aug2017All_V11_DATA was up-to-date: 19.10.2018 (AWB)  
##  - Last check that MC   JEC Summer16_07Aug2017_V11_MC      was up-to-date: 19.10.2018 (AWB)  
## https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookJetEnergyCorrections


SingleMu_2016B = sample( name   = 'SingleMu_2016B',
                         DAS    = '/SingleMuon/Run2016B-17Jul2018_ver2-v1/MINIAOD',
                         GT     = '94X_dataRun2_v10',
                         JEC    = 'Summer16_07Aug2017All_V11_DATA',
                         JSON   = golden_23Sep2016ReReco,
                         isData = True)

SingleMu_2016C = sample( name   = 'SingleMu_2016C',
                         DAS    = '/SingleMuon/Run2016C-17Jul2018-v1/MINIAOD',
                         files = ['/store/user/abrinke1/HiggsToMuMu/samples/SingleMuon_Run2016C/17Jul2018-v1/D6E4B6C8-1C9B-E811-8C98-90E2BAD5729C.root' ],
                         GT     = '94X_dataRun2_v10',
                         JEC    = 'Summer16_07Aug2017All_V11_DATA',
                         JSON   = golden_23Sep2016ReReco,
                         isData = True)

SingleMu_2016D = sample( name   = 'SingleMu_2016D',
                         DAS    = '/SingleMuon/Run2016D-17Jul2018-v1/MINIAOD',
                         GT     = '94X_dataRun2_v10',
                         JEC    = 'Summer16_07Aug2017All_V11_DATA',
                         JSON   = golden_23Sep2016ReReco,
                         isData = True)

SingleMu_2016E = sample( name   = 'SingleMu_2016E',
                         DAS    = '/SingleMuon/Run2016E-17Jul2018-v1/MINIAOD',
                         GT     = '94X_dataRun2_v10',
                         JEC    = 'Summer16_07Aug2017All_V11_DATA',
                         JSON   = golden_23Sep2016ReReco,
                         isData = True)

SingleMu_2016F = sample( name   = 'SingleMu_2016F',
                         DAS    = '/SingleMuon/Run2016F-17Jul2018-v1/MINIAOD',
                         GT     = '94X_dataRun2_v10',
                         JEC    = 'Summer16_07Aug2017All_V11_DATA',
                         JSON   = golden_23Sep2016ReReco,
                         isData = True)

SingleMu_2016G = sample( name   = 'SingleMu_2016G',
                         DAS    = '/SingleMuon/Run2016G-17Jul2018-v1/MINIAOD',
                         GT     = '94X_dataRun2_v10',
                         JEC    = 'Summer16_07Aug2017All_V11_DATA',
                         JSON   = golden_23Sep2016ReReco,
                         isData = True)

SingleMu_2016H = sample( name   = 'SingleMu_2016H',
                         DAS    = '/SingleMuon/Run2016H-17Jul2018-v1/MINIAOD',
                         GT     = '94X_dataRun2_v10',
                         JEC    = 'Summer16_07Aug2017All_V11_DATA',
                         JSON   = golden_23Sep2016ReReco,
                         isData = True)

SingleMu = []  ## All SingleMuon datasets

SingleMu.append(SingleMu_2016B)
SingleMu.append(SingleMu_2016C)
SingleMu.append(SingleMu_2016D)
SingleMu.append(SingleMu_2016E)
SingleMu.append(SingleMu_2016F)
SingleMu.append(SingleMu_2016G)
SingleMu.append(SingleMu_2016H)


DoubleMu_2016B = sample( name   = 'DoubleMu_2016B',
                         DAS    = '/DoubleMuon/Run2016B-17Jul2018_ver2-v1/MINIAOD',
                         GT     = '94X_dataRun2_v10',
                         JEC    = 'Summer16_07Aug2017All_V11_DATA',
                         JSON   = golden_23Sep2016ReReco,
                         isData = True)

DoubleMu_2016C = sample( name   = 'DoubleMu_2016C',
                         DAS    = '/DoubleMuon/Run2016C-17Jul2018-v1/MINIAOD',
                         GT     = '94X_dataRun2_v10',
                         JEC    = 'Summer16_07Aug2017All_V11_DATA',
                         JSON   = golden_23Sep2016ReReco,
                         isData = True)

DoubleMu_2016D = sample( name   = 'DoubleMu_2016D',
                         DAS    = '/DoubleMuon/Run2016D-17Jul2018-v1/MINIAOD',
                         GT     = '94X_dataRun2_v10',
                         JEC    = 'Summer16_07Aug2017All_V11_DATA',
                         JSON   = golden_23Sep2016ReReco,
                         isData = True)

DoubleMu_2016E = sample( name   = 'DoubleMu_2016E',
                         DAS    = '/DoubleMuon/Run2016E-17Jul2018-v1/MINIAOD',
                         GT     = '94X_dataRun2_v10',
                         JEC    = 'Summer16_07Aug2017All_V11_DATA',
                         JSON   = golden_23Sep2016ReReco,
                         isData = True)

DoubleMu_2016F = sample( name   = 'DoubleMu_2016F',
                         DAS    = '/DoubleMuon/Run2016F-17Jul2018-v1/MINIAOD',
                         GT     = '94X_dataRun2_v10',
                         JEC    = 'Summer16_07Aug2017All_V11_DATA',
                         JSON   = golden_23Sep2016ReReco,
                         isData = True)

DoubleMu_2016G = sample( name   = 'DoubleMu_2016G',
                         DAS    = '/DoubleMuon/Run2016G-17Jul2018-v1/MINIAOD',
                         GT     = '94X_dataRun2_v10',
                         JEC    = 'Summer16_07Aug2017All_V11_DATA',
                         JSON   = golden_23Sep2016ReReco,
                         isData = True)

DoubleMu_2016H = sample( name   = 'DoubleMu_2016H',
                         DAS    = '/DoubleMuon/Run2016H-17Jul2018-v1/MINIAOD',
                         GT     = '94X_dataRun2_v10',
                         JEC    = 'Summer16_07Aug2017All_V11_DATA',
                         JSON   = golden_23Sep2016ReReco,
                         isData = True)

DoubleMu = []  ## All DoubleMuon datasets

# DoubleMu.append(DoubleMu_2016B)
# DoubleMu.append(DoubleMu_2016C)
# DoubleMu.append(DoubleMu_2016D)
# DoubleMu.append(DoubleMu_2016E)
# DoubleMu.append(DoubleMu_2016F)
# DoubleMu.append(DoubleMu_2016G)
# DoubleMu.append(DoubleMu_2016H)

# =======================================================================================================
# ------------------------------- SIGNAL ----------------------------------------------------------------
# =======================================================================================================

## GT suggested by JETMET POG for MC for new JEC
## 94X_mc2017_realistic_v13

# =======================================================================================================
# ------------------------------- SIGNAL ----------------------------------------------------------------
# =======================================================================================================

## Gluon-gluon fusion, amc@NLO
H2Mu_gg_120_NLO = sample( name = 'H2Mu_gg_120',
                          DAS  = '/GluGluHToMuMu_M120_TuneCP5_PSweights_13TeV_amcatnloFXFX_pythia8/{0}/{1}'.format(processed_dataset[0],data_tier[1]),
                          nEvt = -1 ) ## 1.9 million

H2Mu_gg_125_NLO = sample( name  = 'H2Mu_gg',
                          DAS   = '/GluGluHToMuMu_M125_TuneCP5_PSweights_13TeV_amcatnloFXFX_pythia8/{0}/{1}'.format(processed_dataset[0],data_tier[1]),
                          nEvt  = -1, ## 2.0 million
                          files = [ '/store/mc/RunIIAutumn18MiniAOD/GluGluHToMuMu_M125_TuneCP5_PSweights_13TeV_amcatnloFXFX_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v2/80000/F348840D-094B-ED48-B2A1-5ABD7D9C2B57.root' ] )

H2Mu_gg_130_NLO = sample( name = 'H2Mu_gg_130',
                          DAS  = '/GluGluHToMuMu_M130_TuneCP5_PSweights_13TeV_amcatnloFXFX_pythia8/{0}/{1}'.format(processed_dataset[0],data_tier[1]),
                          nEvt = -1 ) ## 1.7 million

## Vector boson fusion
H2Mu_VBF_120_NLO = sample( name = 'H2Mu_VBF_120',
                           DAS  = '/VBFHToMuMu_M120_TuneCP5_PSweights_13TeV_amcatnlo_pythia8/{0}/{1}'.format(processed_dataset[0],data_tier[1]),
                           nEvt = -1 ) ## 1.0 million

H2Mu_VBF_125_NLO = sample( name = 'H2Mu_VBF',
                           DAS  = '/VBFHToMuMu_M125_TuneCP5_PSweights_13TeV_amcatnlo_pythia8/{0}/{1}'.format(processed_dataset[0],data_tier[1]),
                           nEvt = -1 ) ## 1.0 million

H2Mu_VBF_130_NLO = sample( name = 'H2Mu_VBF_130',
                           DAS  = '/VBFHToMuMu_M130_TuneCP5_PSweights_13TeV_amcatnlo_pythia8/{0}/{1}'.format(processed_dataset[0],data_tier[1]),
                           nEvt = -1 ) ## 1.0 million

## WH (+)
H2Mu_WH_pos_120 = sample( name = 'H2Mu_WH_pos_120',
                          DAS  = '/WplusH_HToMuMu_WToAll_M120_TuneCP5_PSweights_13TeV_powheg_pythia8/{0}/{1}'.format(processed_dataset[0],data_tier[1]),
                          nEvt = -1 ) ## 300 k

H2Mu_WH_pos_125 = sample( name = 'H2Mu_WH_pos_125',
                          DAS  = '/WplusH_HToMuMu_WToAll_M125_TuneCP5_PSweights_13TeV_powheg_pythia8/{0}/{1}'.format(processed_dataset[0],data_tier[1]),
                          nEvt = -1 ) ## 300 k

H2Mu_WH_pos_130 = sample( name = 'H2Mu_WH_pos_130',
                          DAS  = '/WplusH_HToMuMu_WToAll_M130_TuneCP5_PSweights_13TeV_powheg_pythia8/{0}/{1}'.format(processed_dataset[0],data_tier[1]),
                          nEvt = -1 ) ## 300 k

## WH (-)
H2Mu_WH_neg_120 = sample( name = 'H2Mu_WH_neg_120',
                           DAS  = '/WminusH_HToMuMu_WToAll_M120_TuneCP5_PSweights_13TeV_powheg_pythia8/{0}/{1}'.format(processed_dataset[0],data_tier[1]),
                           nEvt = -1 ) ## 125 k

H2Mu_WH_neg_125 = sample( name = 'H2Mu_WH_neg_125',
                          DAS  = '/WminusH_HToMuMu_WToAll_M125_TuneCP5_PSweights_13TeV_powheg_pythia8/{0}/{1}'.format(processed_dataset[0],data_tier[1]),
                          nEvt = -1 ) ## 300 k

H2Mu_WH_neg_130 = sample( name = 'H2Mu_WH_neg_130',
                          DAS  = '/WminusH_HToMuMu_WToAll_M130_TuneCP5_PSweights_13TeV_powheg_pythia8/{0}/{1}'.format(processed_dataset[0],data_tier[1]),
                          nEvt = -1 ) ## 300 k

## ZH
H2Mu_ZH_120 = sample( name = 'H2Mu_ZH_120',
                      DAS  = '/ZH_HToMuMu_ZToAll_M120_TuneCP5_PSweights_13TeV_powheg_pythia8/{0}/{1}'.format(processed_dataset[0],data_tier[1]),
                      nEvt = -1 ) ## 300 k

H2Mu_ZH_125 = sample( name = 'H2Mu_ZH_125',
                      DAS  = '/ZH_HToMuMu_ZToAll_M125_TuneCP5_PSweights_13TeV_powheg_pythia8/{0}/{1}'.format(processed_dataset[0],data_tier[1]),
                      nEvt = -1 ) ## 300 k

H2Mu_ZH_130 = sample( name = 'H2Mu_ZH_130',
                      DAS  = '/ZH_HToMuMu_ZToAll_M130_TuneCP5_PSweights_13TeV_powheg_pythia8/{0}/{1}'.format(processed_dataset[0],data_tier[1]),
                      nEvt = -1 ) ## 300 k

## ttH
H2Mu_ttH_120 = sample( name = 'H2Mu_ttH_120',
                       DAS  = '/ttHToMuMu_M120_TuneCP5_PSweights_13TeV-powheg-pythia8/{0}/{1}'.format(processed_dataset[0],data_tier[1]),
                       nEvt = -1 ) ## 300 k

H2Mu_ttH_125 = sample( name = 'H2Mu_ttH_125',
                       DAS  = '/ttHToMuMu_M125_TuneCP5_PSweights_13TeV-powheg-pythia8/{0}/{1}'.format(processed_dataset[0],data_tier[1]),
                       nEvt = -1 ) ## 300 k

H2Mu_ttH_130 = sample( name = 'H2Mu_ttH_130',
                       DAS  = '/ttHToMuMu_M130_TuneCP5_PSweights_13TeV-powheg-pythia8/{0}/{1}'.format(processed_dataset[0],data_tier[1]),
                       nEvt = -1 ) ## 300 k


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
Signal.append(H2Mu_WH_neg_120)
Signal.append(H2Mu_ZH_120)
Signal.append(H2Mu_ttH_120)

Signal.append(H2Mu_gg_130_NLO)
Signal.append(H2Mu_VBF_130_NLO)
Signal.append(H2Mu_WH_pos_130)
Signal.append(H2Mu_WH_neg_130)
Signal.append(H2Mu_ZH_130)
Signal.append(H2Mu_ttH_130)

# # =======================================================================================================
# # ------------------------------- BACKGROUND ------------------------------------------------------------
# # =======================================================================================================

Background = []  ## All H2Mu background samples

###################
###  Drell-Yan  ###
###################

ZJets_AMC = sample( name = 'ZJets_AMC',
                    DAS  = '/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/{0}/{1}'.format(processed_dataset[2],data_tier[1]),
                    nEvt = -1)  ## 1 million

ZJets_MG = sample( name = 'ZJets_MG_1',
                     DAS  = '/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/{0}/{1}'.format(processed_dataset[4],data_tier[1]),
                     nEvt = -1 ) ## 100 million

ZJets_MG_2 = sample( name = 'ZJets_MG_2',
                     DAS  = '/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/{0}/{1}'.format(processed_dataset[3],data_tier[1]),
                     nEvt = -1 ) ## 60 million

ZJets_hiM_AMC = sample( name = 'ZJets_hiM_AMC',
                        DAS  = '/DYJetsToLL_M-105To160_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/{0}/{1}'.format(processed_dataset[6],data_tier[1]),
                        nEvt = -1 )  ## 60 million

ZJets_hiM_MG = sample( name = 'ZJets_hiM_MG',
                       DAS  = '/DYJetsToLL_M-105To160_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/{0}/{1}'.format(processed_dataset[0],data_tier[1]),
                       nEvt = -1 )  ## 60 million


Background.append(ZJets_AMC)
Background.append(ZJets_MG)
Background.append(ZJets_MG_2)
Background.append(ZJets_hiM_AMC)
Background.append(ZJets_hiM_MG)

###############
###  ttbar  ###
###############

#tt_ll_AMC = sample( name = 'tt_ll_AMC',
#                    DAS  = '/TT_DiLept_TuneCP5_13TeV-amcatnlo-pythia8/{0}/{1}'.format(processed_dataset[0],data_tier[1]),
#                    nEvt = -1 ) ## 4 million

tt_ll_MG = sample( name = 'tt_ll_MG',
                   DAS  = '/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/{0}/{1}'.format(processed_dataset[3],data_tier[1]),
                   nEvt = -1 ) ## 60 million

tt_ll_POW = sample( name = 'tt_ll_POW', #
                    DAS  = '/TTTo2L2Nu_TuneCP5_PSweights_13TeV-powheg-pythia8/{0}/{1}'.format(processed_dataset[0],data_tier[1]),
                    nEvt = -1 ) ## 71 million

tt_ljj_POW_1 = sample ( name = 'tt_ljj_POW_1',
                        DAS  = '/TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8/{0}/{1}'.format(processed_dataset[0],data_tier[1]),
                        nEvt = -1 ) ## 111 million

#Background.append(tt_ll_AMC)
Background.append(tt_ll_MG)
Background.append(tt_ll_POW)
Background.append(tt_ljj_POW_1)

####################
###  Single top  ###
####################

tW_pos = sample( name = 'tW_pos',
                 DAS  = '/ST_tW_top_5f_inclusiveDecays_TuneCP5_PSweights_13TeV-powheg-pythia8/{0}/{1}'.format(processed_dataset[0],data_tier[1]),
                 nEvt = -1 ) ## 5 million

tW_neg = sample( name = 'tW_neg',
                 DAS  = '/ST_tW_antitop_5f_inclusiveDecays_TuneCP5_PSweights_13TeV-powheg-pythia8/{0}/{1}'.format(processed_dataset[0],data_tier[1]),
                 nEvt = -1 ) ## 5 million

Background.append(tW_pos)
Background.append(tW_neg)

#################
###  Diboson  ###
#################

WW_2l_1 = sample( name = 'WW_2l_1',
             DAS  = '/WWTo2L2Nu_13TeV-powheg/{0}/{1}'.format(processed_dataset[1],data_tier[1]),
             nEvt = -1 ) ## 2 million

WW_2l_2 = sample( name = 'WW_2l_2',
             DAS  = '/WWTo2L2Nu_13TeV-powheg-herwigpp/{0}/{1}'.format(processed_dataset[1],data_tier[1]),
             nEvt = -1 ) ## 2 million


WZ_2l = sample( name = 'WZ_2l',
                DAS  = '/WZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/{0}/{1}'.format(processed_dataset[1],data_tier[1]),
                nEvt =  -1 ) ## 28 million

WZ_3l = sample( name = 'WZ_3l',
                DAS  = '/WZTo3LNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/{0}/{1}'.format(processed_dataset[1],data_tier[1]),
                nEvt = -1 ) ## 11 million

ZZ_2l_2q = sample( name = 'ZZ_2l_2q',
                   DAS  = '/ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/{0}/{1}'.format(processed_dataset[0],data_tier[1]),
                   nEvt = -1 ) ## 28 million

ZZ_4l = sample( name = 'ZZ_4l',
                DAS  = '/ZZTo4L_13TeV_powheg_pythia8_ext1/{0}/{1}'.format(processed_dataset[1],data_tier[1]),
                nEvt = -1 ) ## 98 million

ZZ_4l_amc = sample( name = 'ZZ_4l_amc',
                DAS  = '/ZZTo4L_13TeV-amcatnloFXFX-pythia8/{0}/{1}'.format(processed_dataset[3],data_tier[1]),
                nEvt = -1 ) ## 10 million

ggZZ_4mu = sample ( name = 'ggZZ_4mu',
                    DAS  = '/GluGluToContinToZZTo4mu_13TeV_MCFM701_pythia8/{0}/{1}'.format(processed_dataset[1],data_tier[1]),
                    files = ["/store/mc/RunIISummer16MiniAODv3/GluGluToContinToZZTo4mu_13TeV_MCFM701_pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3-v2/120000/4E25DF26-2EEB-E811-BEBE-0CC47AF9B2E2.root",
                             "/store/mc/RunIISummer16MiniAODv3/GluGluToContinToZZTo4mu_13TeV_MCFM701_pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3-v2/120000/B84A75C9-2EEB-E811-8D48-0025905D1D50.root",
                             "/store/mc/RunIISummer16MiniAODv3/GluGluToContinToZZTo4mu_13TeV_MCFM701_pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3-v2/120000/38AE8C6F-2EEB-E811-BD40-0025905C42F4.root",
                             "/store/mc/RunIISummer16MiniAODv3/GluGluToContinToZZTo4mu_13TeV_MCFM701_pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3-v2/120000/B451A6F9-2EEB-E811-8A83-0025905D1CAC.root"],
                    nEvt = -1 )

ggZZ_2e2mu = sample ( name = 'ggZZ_2e2mu',
                      DAS  = '/GluGluToContinToZZTo2e2mu_13TeV_MCFM701_pythia8/{0}/{1}'.format(processed_dataset[1],data_tier[1]),
                      nEvt = -1 )

ggZZ_2mu2tau = sample ( name = 'ggZZ_2mu2tau',
                        DAS  = '/GluGluToContinToZZTo2mu2tau_13TeV_MCFM701_pythia8/{0}/{1}'.format(processed_dataset[1],data_tier[1]),
                        nEvt = -1 )

ggZZ_2e2tau  = sample  ( name = 'ggZZ_2e2tau',
                        DAS  = '/GluGluToContinToZZTo2e2tau_13TeV_MCFM701_pythia8/{0}/{1}'.format(processed_dataset[1],data_tier[1]),
                        nEvt = -1 )

ggZZ_2mu2nu = sample  ( name = 'ggZZ_2mu2nu',
                        DAS  = '/GluGluToContinToZZTo2mu2nu_13TeV_MCFM701_pythia8/{0}/{1}'.format(processed_dataset[1],data_tier[1]),
                        nEvt = -1 )

ggZZ_4tau = sample ( name = 'ggZZ_4tau',
                    DAS  = '/GluGluToContinToZZTo4tau_13TeV_MCFM701_pythia8/{0}/{1}'.format(processed_dataset[1],data_tier[1]),
                    nEvt = -1 )

Background.append(WW_2l_1)
Background.append(WZ_2l)
Background.append(WZ_3l)
Background.append(ZZ_2l_2q)
Background.append(ZZ_4l)
Background.append(ZZ_4l_amc)
Background.append(ggZZ_4mu)
Background.append(ggZZ_2e2mu)
Background.append(ggZZ_2mu2tau)
Background.append(ggZZ_2e2tau)
Background.append(ggZZ_2mu2nu)
Background.append(ggZZ_4tau)

################
###  ttbar+X  ##
################

ttW = sample( name = 'ttW',
              DAS  = '/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/{0}/{1}'.format(processed_dataset[3],data_tier[1]),
              nEvt = -1 ) ## 4.9 million

ttZ = sample( name = 'ttZ',
              DAS  = '/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/{0}/{1}'.format(processed_dataset[3],data_tier[1]),
              nEvt = -1 ) ## 2 million

ttZ_1 = sample( name = 'ttZ_1',
              DAS  = '/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/{0}/{1}'.format(processed_dataset[7],data_tier[1]),
              nEvt = -1 ) ## 5 million

ttZ_2 = sample( name = 'ttZ_2',
              DAS  = '/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/{0}/{1}'.format(processed_dataset[8],data_tier[1]),
              nEvt = -1 ) ## 5 million

#not present in MINIAODv3 2016
#ttZ_lowM = sample( name = 'ttZ_lowM',
#                   DAS  = '/TTZToLL_M-1to10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/{0}/{1}'.format(processed_dataset[0],data_tier[1]),
#                   nEvt = -1 ) ## 250 k

ttH = sample( name = 'ttH',
              DAS  = '/ttHToNonbb_M125_TuneCP5_13TeV-powheg-pythia8/{0}/{1}'.format(processed_dataset[0],data_tier[1]),
              nEvt = -1 ) ## 10 million

ttWW = sample( name = 'ttWW',
               DAS  = '/TTWW_TuneCUETP8M2T4_13TeV-madgraph-pythia8/{0}/{1}'.format(processed_dataset[6],data_tier[1]),
               nEvt = -1 ) ## 200 k

Background.append(ttW)
Background.append(ttZ)
Background.append(ttZ_1)
Background.append(ttZ_2)
#Background.append(ttZ_lowM)
Background.append(ttH)
Background.append(ttWW)

# #####################
# ###  Single top+X  ##
# #####################

tZq = sample( name = 'tZq',
              DAS  = '/tZq_ll_4f_13TeV-amcatnlo-pythia8/{0}/{1}'.format(processed_dataset[6],data_tier[1]),
              nEvt = -1 ) ## 13 million

tZq_herwig = sample( name = 'tZq+herwig',
              DAS  = '/tZq_ll_4f_13TeV-amcatnlo-herwigpp/{0}/{1}'.format(processed_dataset[0],data_tier[1]),
              nEvt = -1 ) ## 13 million


# tZW = sample( name = 'tZW',
#               DAS  = '/ST_tWll_5f_LO_TuneCUETP8M1_PSweights_13TeV-madgraph-pythia8/{0}/{1}'.format(processed_dataset[0],data_tier[1])*/MINIAODSIM',
#               nEvt = -1) ## 

tHq = sample( name = 'tHq',
              DAS  = '/THQ_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1/{0}/{1}'.format(processed_dataset[1],data_tier[1]),
              nEvt = -1 ) ## 3 million

tHW = sample( name = 'tHW',
              DAS  = '/THW_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1/{0}/{1}'.format(processed_dataset[1],data_tier[1]),
              nEvt = -1 ) ## 1 million

Background.append(tZq)
Background.append(tZq_herwig)
# Background.append(tZW)
Background.append(tHq)
Background.append(tHW)

#################
###  Triboson  ##
#################

WWW = sample( name = 'WWW',
              DAS  = '/WWW_4F_TuneCUETP8M1_13TeV-amcatnlo-pythia8/{0}/{1}'.format(processed_dataset[1],data_tier[1]),
              nEvt = -1 ) ## 230 k

WWW_lep = sample( name = 'WWW_lep',
              DAS  = '/WWW_4F_DiLeptonFilter_TuneCUETP8M1_13TeV-amcatnlo-pythia8/{0}/{1}'.format(processed_dataset[5],data_tier[1]),
              nEvt = -1 ) 

WWZ = sample( name = 'WWZ',
              DAS  = '/WWZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/{0}/{1}'.format(processed_dataset[1],data_tier[1]),
              nEvt = -1 ) ## 250 k

#WWZ_4f = sample( name = 'WWZ_4f',
#              DAS  = '/WWZJetsTo4L2Nu_4f_TuneCUETP8M1_13TeV_amcatnloFXFX_pythia8/{0}/{1}'.format(processed_dataset[0],data_tier[1]),
#              nEvt = -1 )

WZZ = sample( name = 'WZZ',
              DAS  = '/WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/{0}/{1}'.format(processed_dataset[1],data_tier[1]),
              nEvt = -1 ) ## 250 k

ZZZ = sample( name = 'ZZZ',
              DAS  = '/ZZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/{0}/{1}'.format(processed_dataset[1],data_tier[1]),
              nEvt = -1 ) ## 250 k

Background.append(WWW)
Background.append(WWW_lep)
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

#create dictionary
samples_dictionary = {sample.name:sample for sample in DataAndMC}



# root://xrootd-cms.infn.it/

# This is my current collection of datasets for H->MuMu.

class sample:
    def __init__(self, name="", dir="", files=[], numevents=0, globaltag="", jsonfiles=[], isData=False):
        self.name = name
        self.dir = dir     # DAS directory
        self.numevents = numevents
        self.files = files
        self.globaltag = globaltag
        self.jsonfiles = jsonfiles
        self.isData = isData

# =======================================================================================================
# ------------------------------- DATA ------------------------------------------------------------------
# =======================================================================================================

# 25 ns
# The jsonfiles details the valid lumi sections
jsonlist2016 = ['sample_file_lists/data/json/Cert_271036-280385_13TeV_PromptReco_Collisions16_JSON_NoL1T_v2.txt', #27.217/fb
                'sample_file_lists/data/json/Cert_271036-283685_13TeV_PromptReco_Collisions16_JSON_NoL1T.txt']    #33.598/fb 

#//////////////////////////// Single Muon /////////////////////////////////////////////////////////////////////////////////////////////

singleMuon = []

# 25 ns

singleMuon_Run2016B_MINIAOD = sample(name="singleMuon_Run2016B_MINIAOD",
                                 dir="/SingleMuon/Run2016B-PromptReco-v2/MINIAOD",
                                 files = open('sample_file_lists/data/singleMuon_Run2016B_MINIAOD.files').read().splitlines(),
                                 numevents=158188719,
                                 globaltag = '80X_dataRun2_Prompt_v9',
                                 jsonfiles = jsonlist2016[:],
                                 isData = True)

singleMuon_Run2016C_MINIAOD = sample(name="singleMuon_Run2016C_MINIAOD",
                                 dir="/SingleMuon/Run2016C-PromptReco-v2/MINIAOD",
                                 files = open('sample_file_lists/data/singleMuon_Run2016C_MINIAOD.files').read().splitlines(),
                                 numevents=68492270,
                                 globaltag = '80X_dataRun2_Prompt_v9',
                                 jsonfiles = jsonlist2016[:],
                                 isData = True)

singleMuon_Run2016D_MINIAOD = sample(name="singleMuon_Run2016D_MINIAOD",
                                 dir="/SingleMuon/Run2016D-PromptReco-v2/MINIAOD",
                                 files = open('sample_file_lists/data/singleMuon_Run2016D_MINIAOD.files').read().splitlines(),
                                 numevents=98175265,
                                 globaltag = '80X_dataRun2_Prompt_v10',
                                 jsonfiles = jsonlist2016[:],
                                 isData = True)

singleMuon_Run2016E_MINIAOD = sample(name="singleMuon_Run2016E_MINIAOD",
                                 dir="/SingleMuon/Run2016E-PromptReco-v2/MINIAOD",
                                 files = open('sample_file_lists/data/singleMuon_Run2016E_MINIAOD.files').read().splitlines(),
                                 numevents=90986344,
                                 globaltag = '80X_dataRun2_Prompt_v10',
                                 jsonfiles = jsonlist2016[:],
                                 isData = True)

singleMuon_Run2016F_MINIAOD = sample(name="singleMuon_Run2016F_MINIAOD",
                                 dir="/SingleMuon/Run2016F-PromptReco-v1/MINIAOD",
                                 files = open('sample_file_lists/data/singleMuon_Run2016F_MINIAOD.files').read().splitlines(),
                                 numevents=65235075,
                                 globaltag = '80X_dataRun2_Prompt_v10',
                                 jsonfiles = jsonlist2016[:],
                                 isData = True)

singleMuon_Run2016G_MINIAOD = sample(name="singleMuon_Run2016G_MINIAOD",
                                 dir="/SingleMuon/Run2016G-PromptReco-v1/MINIAOD",
                                 files = open('sample_file_lists/data/singleMuon_Run2016G_MINIAOD.files').read().splitlines(),
                                 numevents=152881545,
                                 globaltag = '80X_dataRun2_Prompt_v11',
                                 jsonfiles = jsonlist2016[:],
                                 isData = True)

singleMuon_Run2016H_MINIAOD = sample(name="singleMuon_Run2016H_MINIAOD",
                                 dir="/SingleMuon/Run2016H-PromptReco-v2/MINIAOD",
                                 files = open('sample_file_lists/data/singleMuon_Run2016H_MINIAOD.files').read().splitlines(),
                                 numevents=49346125,
                                 globaltag = '80X_dataRun2_Prompt_v14',
                                 jsonfiles = jsonlist2016[:],
                                 isData = True)

singleMuon.append(singleMuon_Run2016B_MINIAOD)
singleMuon.append(singleMuon_Run2016C_MINIAOD)
singleMuon.append(singleMuon_Run2016D_MINIAOD)
singleMuon.append(singleMuon_Run2016E_MINIAOD)
singleMuon.append(singleMuon_Run2016F_MINIAOD)
singleMuon.append(singleMuon_Run2016G_MINIAOD)
singleMuon.append(singleMuon_Run2016H_MINIAOD)

# =======================================================================================================
# ------------------------------- SIGNAL ----------------------------------------------------------------
# =======================================================================================================

# ///////////////////////////////////////////////////////////////////////////////////////////////////////
#---- Gluon Gluon Fusion --------------------------------------------------------------------------------
# ///////////////////////////////////////////////////////////////////////////////////////////////////////

signal = []

#gg_HToMuMu1 = sample( name="gg_HToMuMu1", 
#                     dir="/GluGlu_HToMuMu_M125_13TeV_powheg_pythia8/RunIISpring16MiniAODv1-PUSpring16RAWAODSIM_80X_mcRun2_asymptotic_2016_v3-v1/MINIAODSIM", 
#                     files = open('sample_file_lists/signal/gg_HToMuMu1.files').read().splitlines(),
#                     numevents=250000,
#                     globaltag = '80X_mcRun2_asymptotic_2016_v3')

gg_HToMuMu2 = sample( name="gg_HToMuMu2", 
                     dir="/GluGlu_HToMuMu_M125_13TeV_powheg_pythia8/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v2/MINIAODSIM", 
                     files = open('sample_file_lists/signal/gg_HToMuMu2.files').read().splitlines(),
                     numevents=250000,
                     globaltag = '80X_mcRun2_asymptotic_2016_miniAODv2_v0')

#signal.append(gg_HToMuMu1)
signal.append(gg_HToMuMu2)

# ///////////////////////////////////////////////////////////////////////////////////////////////////////
#---- Vector Boson Fusion --------------------------------------------------------------------------------
# ///////////////////////////////////////////////////////////////////////////////////////////////////////


vbf_HToMuMu = sample(name="vbf_HToMuMu", 
                     dir="/VBF_HToMuMu_M125_13TeV_powheg_pythia8/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v2/MINIAODSIM",
                     files = open('sample_file_lists/signal/vbf_HToMuMu.files').read().splitlines(),
                     numevents=227820,
                     globaltag = '80X_mcRun2_asymptotic_2016_miniAODv2_v0')

signal.append(vbf_HToMuMu)

# ///////////////////////////////////////////////////////////////////////////////////////////////////////
#---- W/Z to Higgs --------------------------------------------------------------------------------------
# ///////////////////////////////////////////////////////////////////////////////////////////////////////

# No 2015 production sample yet

# Old samples
wh_zh_HToMuMu_PU40bx50 = sample(name="wh_zh_HToMuMu_PU40bx50", 
                                dir="/WH_ZH_HToMuMu_M-125_13TeV_pythia6/Spring14miniaod-141029_PU40bx50_PLS170_V6AN2-v1/MINIAODSIM",
                                #files = open('sample_file_lists/signal/vbf_HToMuMu_PU20bx25.files').read().splitlines(),
                                numevents=100000,
                                globaltag = 'PLS170_V6AN2')

wh_zh_HToMuMu_PU20bx25 = sample(name="wh_zh_HToMuMu_PU20bx25", 
                                dir="/WH_ZH_HToMuMu_M-125_13TeV_pythia6/Spring14miniaod-PU20bx25_POSTLS170_V5-v1/MINIAODSIM",
                                #files = open('sample_file_lists/signal/vbf_HToMuMu_PU20bx25.files').read().splitlines(),
                                numevents=100000,
                                globaltag = 'POSTLS170_V5')

# =======================================================================================================
# ------------------------------- BACKGROUND ------------------------------------------------------------
# =======================================================================================================

# ///////////////////////////////////////////////////////////////////////////////////////////////////////
# ---- DRELL YANN ---------------------------------------------------------------------------------------
# ///////////////////////////////////////////////////////////////////////////////////////////////////////
background = []

dy_jetsToLL = sample(name="dy_jetsToLL", 
                     dir="/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM",
                     #files = open('sample_file_lists/bg/dy_jetsToLL.files').read().splitlines(),
                     files = [],
                     numevents=28696958,
                     globaltag = '80X_mcRun2_asymptotic_2016_miniAODv2_v0');

#background.append(dy_ZToMuMu_asympt25)
background.append(dy_jetsToLL)

# ///////////////////////////////////////////////////////////////////////////////////////////////////////
#---- TTBAR --------------------------------------------------------------------------------------------
# ///////////////////////////////////////////////////////////////////////////////////////////////////////

#ttJets1 = sample(name="ttJets1", 
#                dir="/TTJets_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring16MiniAODv1-PUSpring16_80X_mcRun2_asymptotic_2016_v3-v3/MINIAODSIM",
#                files = open('sample_file_lists/bg/ttJets1.files').read().splitlines(),
#                numevents=28088535,
#                globaltag = '80X_mcRun2_asymptotic_2016_v3')

ttJets2 = sample(name="ttJets2", 
                dir="/TTJets_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM",
                files = open('sample_file_lists/bg/ttJets2.files').read().splitlines(),
                numevents=37459078,
                globaltag = '80X_mcRun2_asymptotic_2016_miniAODv2_v0')

ttZToLLNuNu = sample(name="ttZToLLNuNu", 
                     dir="/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v2/MINIAODSIM",
                     files = open('sample_file_lists/bg/ttZToLLNuNu.files').read().splitlines(),
                     numevents=398000,
                     globaltag = '74X_mcRun2_asymptotic_v2')

#background.append(ttJets1)
background.append(ttJets2)
#background.append(ttZToLLNuNu)

# ///////////////////////////////////////////////////////////////////////////////////////////////////////
#---- Diboson -------------------------------------------------------------------------------------------
# ///////////////////////////////////////////////////////////////////////////////////////////////////////

# Haven't added all of the Diboson backgrounds. There are a ton of samples.
# 12.178 pb
WWTo2L2Nu = sample(name="WWTo2L2Nu", 
                   dir="/WWTo2L2Nu_13TeV-powheg/RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/MINIAODSIM",
                   files = open('sample_file_lists/bg/WWTo2L2Nu.files').read().splitlines(),
                   numevents=1965200,
                   globaltag = '74X_mcRun2_asymptotic_v2')

# 5.595 pb
WZTo2L2Q = sample(name="WZTo2L2Q", 
                   dir="/WZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/MINIAODSIM",
                   files = open('sample_file_lists/bg/WZTo2L2Q.files').read().splitlines(),
                   numevents=31477411,
                   globaltag = '74X_mcRun2_asymptotic_v2')

# 4.42965 pb
WZTo3LNu = sample(name="WZTo3LNu", 
                   dir="/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/MINIAODSIM",
                   files = open('sample_file_lists/bg/WZTo3LNu.files').read().splitlines(),
                   numevents=1980800,
                   globaltag = '74X_mcRun2_asymptotic_v2')
# 3.22 pb
ZZTo2L2Q = sample(name="ZZTo2L2Q", 
                   dir="/ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/MINIAODSIM",
                   files = open('sample_file_lists/bg/ZZTo2L2Q.files').read().splitlines(),
                   numevents=18790122,
                   globaltag = '74X_mcRun2_asymptotic_v2')

#background.append(WWTo2L2Nu)
#background.append(WZTo2L2Q)
#background.append(WZTo3LNu)
#background.append(ZZTo2L2Q)

# 1.256 pb
ZZTo4L = sample(name="ZZTo4L", 
                   dir="/ZZTo4L_13TeV_powheg_pythia8/RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v2/MINIAODSIM",
                   files = open('sample_file_lists/bg/ZZTo4L.files').read().splitlines(),
                   numevents=6665004,
                   globaltag = '74X_mcRun2_asymptotic_v2')
# 0.564 pb
ZZTo2L2Nu = sample(name="ZZTo2L2Nu", 
                   dir="/ZZTo2L2Nu_13TeV_powheg_pythia8/RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v2/MINIAODSIM",
                   files = open('sample_file_lists/bg/ZZTo2L2Nu.files').read().splitlines(),
                   numevents=8719200,
                   globaltag = '74X_mcRun2_asymptotic_v2')

#background.append(ZZTo4L)
#background.append(ZZTo2L2Nu)

# 0.003194 pb
GluGluToZZTo2mu2tau = sample(name="GluGluToZZTo2mu2tau", 
                   dir="/GluGluToZZTo2mu2tau_BackgroundOnly_13TeV_MCFM/RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/MINIAODSIM",
                   files = open('sample_file_lists/bg/GluGluToZZTo2mu2tau.files').read().splitlines(),
                   numevents=650000,
                   globaltag = '74X_mcRun2_asymptotic_v2')

# 0.003194 pb
GluGluToZZTo2e2mu = sample(name="GluGluToZZTo2e2mu", 
                   dir="/GluGluToZZTo2e2mu_BackgroundOnly_13TeV_MCFM/RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/MINIAODSIM",
                   files = open('sample_file_lists/bg/GluGluToZZTo2e2mu.files').read().splitlines(),
                   numevents= 648800,
                   globaltag = '74X_mcRun2_asymptotic_v2')

# 0.001586 pb
GluGluToZZTo4mu = sample(name="GluGluToZZTo4mu", 
                   dir="/GluGluToZZTo4mu_BackgroundOnly_13TeV_MCFM/RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/MINIAODSIM",
                   files = open('sample_file_lists/bg/GluGluToZZTo4mu.files').read().splitlines(),
                   numevents= 339600,
                   globaltag = '74X_mcRun2_asymptotic_v2')

#background.append(GluGluToZZTo2mu2tau)
#background.append(GluGluToZZTo2e2mu)
#background.append(GluGluToZZTo4mu)

singleAndMC = []
singleAndMC.extend(singleMuon)
singleAndMC.extend(signal)
singleAndMC.extend(background)

MC = []
MC.extend(signal)
MC.extend(background)

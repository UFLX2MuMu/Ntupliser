PPD Analysis Guidelines
https://docs.google.com/presentation/d/1F1ZsQqljdR4IqIJ5za2TAIVFF0eqHquopzN_jgVTdKE/edit#slide=id.g43837f3ea1_0_46


## Ntupliser
X2MuMu Ntupliser

## Instructions for checking out code to run master_2017_94X

setenv SCRAM_ARCH slc6_amd64_gcc630
cmsrel CMSSW_9_4_10  ## Need a release >= 9_4_10 to merge cms-egamma code (below)
cd CMSSW_9_4_10/src
cmsenv
git cms-init
git remote add cms-sw git@github.com:cms-sw/cmssw.git
git fetch cms-sw

git remote add your_username git@github.com:your_username/cmssw.git
git remote add Ntupliser git@github.com:UFLX2MuMu/Ntupliser.git

git clone https://github.com/UFLX2MuMu/Ntupliser.git

## Twiki not updated recently (as of 18.10.2018)
## https://twiki.cern.ch/twiki/bin/view/CMS/MuonScaleResolKalman
git clone https://github.com/bachtis/Analysis.git -b KaMuCa_V4 KaMuCa

## Add following lines to the beginning of KaMuCa/Calibration/interface/KalmanMuonCalibrator.h
#ifndef KalmanMuonCalibrator_h
#define KalmanMuonCalibrator_h
## and the following line to the end:
#endif // #define KalmanMuonCalibrator_h

## Get most recent electron IDs, following:
## https://twiki.cern.ch/twiki/bin/viewauth/CMS/CutBasedElectronIdentificationRun2#Recipe_for_regular_users_formats
## https://twiki.cern.ch/twiki/bin/view/CMS/EgammaMiniAODV2#2017_MiniAOD_V2
## https://twiki.cern.ch/twiki/bin/view/CMS/EgammaPostRecoRecipes#Running_on_2017_MiniAOD_V1
git cms-merge-topic cms-egamma:EgammaID_949             # If you want the V2 IDs, otherwise skip
git cms-merge-topic cms-egamma:EgammaPostRecoTools_940  # Just adds an extra file for an easier setup function

scram b -j 6

cd Ntupliser
git checkout master_2017_94X
scram b -j 6

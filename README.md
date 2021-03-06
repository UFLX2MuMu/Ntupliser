# X2MuMu Ntupliser 

Ntupler producer for analyses working with at least two muons. 
It works with 2016 and 2017 data and MC. 
Compatibility with 2018 data and MC is under development.
Each year has its own master branch:
- master_2016_94X
- master_2017_94X
- master_2018_102X

CMSSW releases, global tags, samples, and json files are in line with the PPD analysis guidelines.

This readme includes instructions on how to checkout and run this code. 
Nevertheless common ntuples production are regularly ran.
Contact us before running your nutples: we might have just produced it, or about to do so.


## 2017

### CMSSW_9_4_13

Instruction for checking out code to run on master_2017_94X in CMSSW_9_4_13
```
scram project -n x2mm17_9413 CMSSW_9_4_13
cd x2mm17_9413/src
cmsenv
git cms-init
git cms-merge-topic cms-egamma:EgammaPostRecoTools # cms-egamma:EgammaID_949 is already merged in 9_4_13
scram b -j 9
git clone git@github.com:UFLX2MuMu/Ntupliser.git Ntupliser
git clone -o Analysis https://github.com/bachtis/analysis.git -b KaMuCa_V4 KaMuCa # these corrections are only for 2016
```

Add the following lines to KaMuCa/Calibration/interface/KalmanMuonCalibrator.h

```
#ifndef KalmanMuonCalibration_h
#define KalmanMuonCalibration_h
...
#endif
```

and finally checkout the *master_2017_94X* branch, recompile and test.

```
cd Ntupliser
git checkout master_2017_94X
scram b -j 6
cd DiMuons
cmsRun test/test_ntupliser_mc.py
```

#### Crab submission

Assuming a valid crab certificate.

Check production parameters in:

```
DiMuons/crab/templates/EDAnalyzer.py # analyzers parameters
DiMuons/crab/templates/crab_config.py # output directory name, storage site
```

Producing a tag for bookeeping:

```
git commit -m "<your message>"
git tag -m "<message> <tag-name>"
```

The <tag-name> is used to create a folder for the crab production. If no tag is provided, the hash of the last commit is used to name the crab folder.

Prepare and launch the production:

```
crab/make_crab_script.py -s <sample name>
./crab/submit_all
```


### CMSSW_9_4_10


```
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

```

Add following lines to the beginning of KaMuCa/Calibration/interface/KalmanMuonCalibrator.h
```
#ifndef KalmanMuonCalibrator_h
#define KalmanMuonCalibrator_h
## and the following line to the end:
#endif // #define KalmanMuonCalibrator_h
```

Checkout a more recent electron ID compared to the release and recompile:
```
git cms-merge-topic cms-egamma:EgammaID_949             # If you want the V2 IDs, otherwise skip
git cms-merge-topic cms-egamma:EgammaPostRecoTools_940  # Just adds an extra file for an easier setup function
cd Ntupliser
git checkout master_2017_94X
scram b -j 6
```

## Misc

### PPD Analysis Guidelines
https://docs.google.com/presentation/d/1F1ZsQqljdR4IqIJ5za2TAIVFF0eqHquopzN_jgVTdKE/edit#slide=id.g43837f3ea1_0_46

### Electron ID
Get most recent electron IDs, following:
- https://twiki.cern.ch/twiki/bin/viewauth/CMS/CutBasedElectronIdentificationRun2#Recipe_for_regular_users_formats
- https://twiki.cern.ch/twiki/bin/view/CMS/EgammaMiniAODV2#2017_MiniAOD_V2
- https://twiki.cern.ch/twiki/bin/view/CMS/EgammaPostRecoRecipes#Running_on_2017_MiniAOD_V1

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


## 2018

### CMSSW_10_2_11_patch1

Instruction for checking out code to run on master_2018_102X in CMSSW_10_2_11_patch1
```
scram project -n x2mm18_10211p1 CMSSW CMSSW_10_2_11_patch1
cd x2mmm18_10211p1/src
cmsenv
git cms-init
git cms-merge-topic cms-egamma:EgammaPostRecoTools 
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

and finally checkout the *master_2018_102X* branch, recompile and test.

```
cd Ntupliser
git checkout master_2018_102X
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


## Misc

### PPD Analysis Guidelines
https://docs.google.com/presentation/d/1F1ZsQqljdR4IqIJ5za2TAIVFF0eqHquopzN_jgVTdKE/edit#slide=id.g43837f3ea1_0_46

### Electron ID
Get most recent electron IDs, following:
- https://twiki.cern.ch/twiki/bin/viewauth/CMS/CutBasedElectronIdentificationRun2#Recipe_for_regular_users_formats
- https://twiki.cern.ch/twiki/bin/view/CMS/EgammaMiniAODV2#2017_MiniAOD_V2
- https://twiki.cern.ch/twiki/bin/view/CMS/EgammaPostRecoRecipes#Running_on_2017_MiniAOD_V1

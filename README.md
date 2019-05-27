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
scram project -n x2mm16_9413 CMSSW CMSSW_9_4_13 
cd x2mmm_9413/src
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
git checkout master_2016_94X
scram b -j 6
cd DiMuons
cmsRun test/UFDiMuonAnalyzer_2018_02_07.py
```



#! /usr/bin/env python 

from python.Samples_Moriond17 import *
import time  ## For timestamp on crab jobs
import os  ## For executable permissions on scripts

samps = []

## Get the samples you want to make a crab config file for 
test_run = False
test_str = '_hiM'
# samps.extend(SingleMu)
# samps.extend(Signal)
# samps.extend(Background)
samps.extend(DataAndMC)

# test_run = True
# test_str = '_v1'
# samps.append(SingleMu_2016C)
# samps.append(H2Mu_gg)
# samps.append(ZJets_MG_HT_2500_inf)

for samp in samps:
    print '\nCreating analyzer and crab config for %s' % samp.name
    ## Open a file for writing
    out_file = open('analyzers/'+samp.name+'.py', 'w')
    
    ## Open the analyzer template to change
    in_file = open('templates/EDAnalyzer.py', 'r')
    
    ## Read in the template and replace the parameters to
    ## make a python file which we will submit using crab
    for line in in_file:
        line = line.replace('samp.isData', str(samp.isData))
        line = line.replace('samp.name', "'%s'" % samp.name)
        line = line.replace('samp.DAS', "'%s'" % samp.DAS)
        line = line.replace('samp.GT', "'%s'" % samp.GT)
        line = line.replace('samp.files', str(samp.files))
        line = line.replace('samp.JSON', "'%s'" % samp.JSON)
        # line = line.replace('samp.inputDBS','%s' %samp.inputDBS)

        out_file.write(line)
    
    ## Close the file
    print '  * Wrote %s' % out_file.name
    out_file.close()
    in_file.close()
    
    ## Open the crab submission template to change
    in_file = open('templates/crab_config.py', 'r')
    out_file = open('configs/'+samp.name+'.py', 'w')
    
    # Read in the template and replace the parameters to make a
    # crab submission file that uses the above CMSSW analyzer
    for line in in_file:
        if 'requestName' in line:
            line = line.replace("= 'STR'", "= '%s_%s%s'" % (samp.name, time.strftime('%Y_%m_%d'), test_str) )

        if 'psetName' in line: 
            line = line.replace("= 'STR'", "= 'analyzers/%s.py'" % samp.name)

        if 'inputDataset' in line:
            line = line.replace("= 'STR'", "= '%s'" % samp.DAS)

        if samp.isData and 'lumiMask' in line: 
            line = line.replace('# config.Data.lumiMask', 'config.Data.lumiMask')
            line = line.replace("= 'STR'", "= '%s'" % samp.JSON)

        if 'splitting' in line:
            if samp.isData:
                line = line.replace("= 'STR'", "= 'LumiBased'")
            else:
                line = line.replace("= 'STR'", "= 'FileBased'")

        if 'unitsPerJob' in line:
            if test_run:
                line = line.replace('= NUM', '= 1')
            elif samp.isData:
                line = line.replace('= NUM', '= 100')
            # elif samp.name == 'ZJets_MG' or ('ZJets_MG' in samp.name and '_B' in samp.name) or samp.name == 'ZZ_4l_AMC':
            #     line = line.replace('= NUM', '= 3')  ## 10-file jobs fail with too much RAM
            else:
                line = line.replace('= NUM', '= 5')

        # if 'inputDBS' in line:
        #     line = line.replace("= 'DBS'", "= '%s'"  % samp.inputDBS)

        if 'outputDatasetTag' in line:
            line = line.replace("= 'STR'", "= '%s'" % samp.name)

        out_file.write(line)
    
    print '  * Wrote %s' % out_file.name
    out_file.close()
    in_file.close()


print '\nCreating submit_all.sh and check_all.sh scripts'

out_file = open('submit_all.sh', 'w')
out_file.write('#!/bin/bash\n')
out_file.write('\n')
#out_file.write('source /cvmfs/cms.cern.ch/crab3/crab.csh\n')
out_file.write('voms-proxy-init --voms cms --valid 168:00\n')
out_file.write('\n')
for samp in samps:
    out_file.write('crab submit -c configs/%s.py\n' % samp.name)
out_file.close()
os.chmod('submit_all.sh', 0o744)

out_file = open('check_all.sh', 'w')
out_file.write('#!/bin/bash\n')
out_file.write('\n')
# out_file.write('source /cvmfs/cms.cern.ch/crab3/crab.csh\n')
# out_file.write('voms-proxy-init --voms cms --valid 168:00\n')
out_file.write('\n')
for samp in samps:
    out_file.write('crab status -d logs/crab_%s_%s\n' % (samp.name, time.strftime('%Y_%m_%d')))
out_file.close()
os.chmod('check_all.sh', 0o744)

import Samples_v3

samples = []

# get the samples you want to make a crab config file for 
#samples.extend(Samples_v3.MC);
#samples.extend(Samples_v3.background);
#samples.extend(Samples_v3.signal);
#samples.extend(Samples_v3.singleMuon);
samples.extend(Samples_v3.singleAndMC);
#samples.extend(Samples_v3.singleMuon);

json_number = 1

for s in samples:
    # open a file for writing
    cfgname = 'dimu_'
    cfgname += s.name
    if s.isData: cfgname += str(json_number)
    cfgname += '_for_crab.py'
    
    outfile = open(cfgname, 'w')
    
    # open the template to change
    file = open('templates/dimuanalyzer_template.py', 'r')
    
    # read in the template and replace the parameters to make a
    # python file which we will submit using crab
    
    for line in file:
        if 's.isData' in line: 
            line = line.replace('s.isData', str(s.isData))
        if 's.name' in line: 
            line = line.replace('s.name', '\"' + s.name + '\"')
        if 's.dir' in line: 
            line = line.replace('s.dir', '\"' + s.dir + '\"')
        if 's.globaltag' in line: 
            line = line.replace('s.globaltag', '\"' + s.globaltag + '\"')
        if 's.jsonfiles[1]' in line and s.isData: 
            line = line.replace('s.jsonfiles[1]', '\"' + s.jsonfiles[json_number] + '\"')
    
        outfile.write(line)
    
    # close the file
    outfile.close()
    file.close()
    
    file = open('templates/crab_template.py', 'r')

    if s.isData: 
        outfile = open('crab_auto_submit_'+s.name+'_JSON'+str(json_number)+'.py', 'w')

    else:
        outfile = open('crab_auto_submit_'+s.name+'.py', 'w')
    
    # read in the template and replace the parameters to make a
    # crab submission file that uses the above cmssw script
    for line in file:
        if 'psetName' in line: 
            line = line.replace('cfgname', cfgname)
        if s.isData and 'FileBased' in line: 
            line = line.replace('FileBased', 'LumiBased')
        if s.isData and 'config.Data.lumiMask' in line: 
            line = line.replace('#', '')
            line = line.replace('s.jsonfiles[1]', s.jsonfiles[json_number])
        if 's.name' in line: 
            name = s.name
            if s.isData: name+="_JSON"+str(json_number)
            line = line.replace('s.name', name)
        if 's.dir' in line: 
            line = line.replace('s.dir', s.dir)
    
        outfile.write(line)
    
    outfile.close()
    file.close()

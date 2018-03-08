#!/bin/bash

job_tag=$1

eos_cmd="/afs/cern.ch/project/eos/installation/0.3.84-aquamarine/bin/eos.select"
hadd_cmd="/cvmfs/cms.cern.ch/slc6_amd64_gcc530/cms/cmssw/CMSSW_8_0_25/external/slc6_amd64_gcc530/bin/hadd"

eos_pre="root://eoscms.cern.ch/"
eos_dir="/store/group/phys_higgs/HiggsExo/H2Mu/UF/ntuples/Moriond17/"
max_add=10

if ! [ -e "file_lists/$job_tag" ]; then
    `mkdir file_lists/$job_tag`
fi
if ! [ -e "file_lists/$job_tag/hadd" ]; then
    `mkdir file_lists/$job_tag/hadd`
fi

for dir1 in `$eos_cmd ls $eos_dir$job_tag`; do
    for dir2 in `$eos_cmd ls $eos_dir$job_tag/$dir1`; do
	if [ -e "file_lists/$job_tag/$dir2.txt" ]; then
	    `rm file_lists/$job_tag/$dir2.txt`
	fi
	if [ -e "file_lists/$job_tag/hadd/$dir2.txt" ]; then
	    `rm file_lists/$job_tag/hadd/$dir2.txt`
	fi
	echo >> "file_lists/$job_tag/$dir2.txt"
	echo >> "file_lists/$job_tag/hadd/$dir2.txt"
	for dir3 in `$eos_cmd ls $eos_dir$job_tag/$dir1/$dir2`; do
	    
	    # ## Only look at SingleMu, but not SingleMu_2016G
	    # if test "${dir2#*SingleMu}" == "$dir2"; then
	    # 	continue
	    # fi
	    # if test "${dir2#*SingleMu_2016G}" != "$dir2"; then
	    # 	continue
	    # fi

	    ## Make list of hadded root files
	    if test "${dir3#*root}" != "$dir3"; then
		echo "$eos_pre$eos_dir$job_tag/$dir1/$dir2/$dir3" >> "file_lists/$job_tag/hadd/$dir2.txt"
		continue
	    fi

	    ## Find most recent crab subission
	    last_ver=$dir3
	    for dir3a in `$eos_cmd ls $eos_dir$job_tag/$dir1/$dir2`; do
		if test "${dir3a#*root}" == "$dir3a"; then
		    last_ver=$dir3a
		fi
	    done
	    
	    ## Assume only the most recent submission is the only valid one
	    if test "${dir3#*$last_ver}" == "$dir3"; then
		continue
	    fi


	    for dir4 in `$eos_cmd ls $eos_dir$job_tag/$dir1/$dir2/$dir3`; do

		for fName in `$eos_cmd ls $eos_dir$job_tag/$dir1/$dir2/$dir3/$dir4`; do
		    if test "${fName#*.root}" != "$fName"; then
			echo "$eos_pre$eos_dir$job_tag/$dir1/$dir2/$dir3/$dir4/$fName" >> "file_lists/$job_tag/$dir2.txt"
		    fi
		done  ## Closes while loop over all files
	    done  ## Closes for loop over dir4 ("0000")

	done  ## Closes for loop over dir3 (crab timestamp)
    done ## Closes for loop over dir2 (sample name)
done  ## Closes for loop over dir1 (DAS name)

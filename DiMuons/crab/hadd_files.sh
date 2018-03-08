#!/bin/bash

job_tag=$1

eos_cmd="/afs/cern.ch/project/eos/installation/0.3.84-aquamarine/bin/eos.select"
hadd_cmd="/cvmfs/cms.cern.ch/slc6_amd64_gcc530/cms/cmssw/CMSSW_8_0_25/external/slc6_amd64_gcc530/bin/hadd"

eos_pre="root://eoscms.cern.ch/"
eos_dir="/store/group/phys_higgs/HiggsExo/H2Mu/UF/ntuples/Moriond17/"
tmp_dir="/afs/cern.ch/work/a/abrinke1/tmp"
max_add=10

## Clean up tmp directory
`rm $tmp_dir/NTuple_*.root`
`rm $tmp_dir/tuple_*.root`

for dir1 in `$eos_cmd ls $eos_dir$job_tag`; do
    for dir2 in `$eos_cmd ls $eos_dir$job_tag/$dir1`; do

	## Remove existing hadded files
	for dir3 in `$eos_cmd ls $eos_dir$job_tag/$dir1/$dir2`; do
	    if test "${dir3#*root}" != "$dir3"; then
		echo "Removing existing $eos_dir$job_tag/$dir1/$dir2/$dir3"
		`$eos_cmd rm $eos_dir$job_tag/$dir1/$dir2/$dir3`
		continue
	    fi
	done

	## Create new hadded files
	for dir3 in `$eos_cmd ls $eos_dir$job_tag/$dir1/$dir2`; do

	    # ## Only look at SingleMu_2016B
	    # if test "${dir2#*SingleMu_2016B}" == "$dir2"; then
	    # 	continue
	    # fi

	    ## Find most recent crab subission
	    last_ver=$dir3
	    for dir3a in `$eos_cmd ls $eos_dir$job_tag/$dir1/$dir2`; do
		if test "${dir3a#*root}" == "$dir3a"; then
		    last_ver=$dir3a
		fi
	    done
	    
	    ## Assume only the most recent submission is the only valid one
	    if test "${dir3#*$last_ver}" == "$dir3"; then
		echo "#####################################################################################"
		echo "Skipping old submission: $eos_dir$job_tag/$dir1/$dir2/$dir3"
		echo "#####################################################################################"
		echo ""
		continue
	    fi
	    
	    for dir4 in `$eos_cmd ls $eos_dir$job_tag/$dir1/$dir2/$dir3`; do

		nFiles=0
		for fName in `$eos_cmd ls $eos_dir$job_tag/$dir1/$dir2/$dir3/$dir4`; do
		    if test "${fName#*.root}" != "$fName"; then
			let "nFiles += 1"
		    fi
		done
		echo "*************************************************************************************"
		echo "$dir1/$dir2/$dir3/$dir4 has $nFiles files"
		echo "*************************************************************************************"
		echo ""

		nTot=0
		nOut=0
		used_files=""
		while [ $nTot -lt $nFiles ]; do

		    hadd_str="$hadd_cmd $tmp_dir/NTuple_$nOut.root"
		    nAdded=0
		    for fName in `$eos_cmd ls $eos_dir$job_tag/$dir1/$dir2/$dir3/$dir4`; do
			if test "${used_files#*$fName}" != "$used_files"; then
			    continue
			fi
			if test "${fName#*.root}" != "$fName"; then
			    if [ "$nAdded" -lt $max_add ]; then
				`xrdcp $eos_pre$eos_dir$job_tag/$dir1/$dir2/$dir3/$dir4/$fName $tmp_dir`
				hadd_str="$hadd_str $tmp_dir/$fName"
				used_files="$used_files $fName"
				let "nAdded += 1"
				let "nTot += 1"
			    fi
			fi
		    done  ## Closes for loop over max_add files
		    `$hadd_str`
		    echo ""
		    echo "  * Wrote out $tmp_dir/NTuple_$nOut.root"
		    echo ""
		    `xrdcp $tmp_dir/NTuple_$nOut.root $eos_pre$eos_dir$job_tag/$dir1/$dir2`
		    `rm $tmp_dir/NTuple_$nOut.root`
		    `rm $tmp_dir/tuple_*.root`
		    let "nOut += 1"
		done  ## Closes while loop over all files
	    done  ## Closes for loop over dir4 ("0000")
	done  ## Closes for loop over dir3 (crab timestamp)
    done ## Closes for loop over dir2 (sample name)
done  ## Closes for loop over dir1 (DAS name)

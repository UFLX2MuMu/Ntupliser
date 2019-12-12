#!/bin/bash

prod_tag=$1

eos_dir="/eos/cms/store/user/eyigitba/h2mm/ntuples/2016/94X/"
tmp_dir="/afs/cern.ch/work/e/eyigitba/tmp"
max_add=5

for dir1 in `ls $eos_dir$prod_tag`; do
  
  ## Skip SingleMu
  # if test "${dir1#*SingleMu}" != "$dir1"; then
  #   echo "skipping $dir1"
  #   continue
  # fi

  for dir2 in `ls $eos_dir$prod_tag/$dir1`; do
    ## Create new hadded files for this MC sample
    for dir3 in `ls $eos_dir$prod_tag/$dir1/$dir2`; do

      ## Find most recent crab subission
      last_ver=$dir3
      for dir3a in `ls $eos_dir$prod_tag/$dir1/$dir2`; do
        if test "${dir3a#*root}" == "$dir3a"; then
            last_ver=$dir3a
        fi
      done        
      ## Assume only the most recent submission is the only valid one
      if test "${dir3#*$last_ver}" == "$dir3"; then
        echo "#####################################################################################"
        echo "Skipping old submission: $eos_dir$prod_tag/$dir1/$dir2/$dir3"
        echo "#####################################################################################"
        echo ""
        continue
      fi
      for dir4 in `ls $eos_dir$prod_tag/$dir1/$dir2/$dir3`; do
        ## Remove existing hadded files for this MC sample
        if test "${dir4#*root}" != "$dir4"; then
          echo "Removing existing $eos_dir$prod_tag/$dir1/$dir2/$dir3/$dir4"
          `rm $eos_dir$prod_tag/$dir1/$dir2/$dir3/$dir4`
          continue
        fi
      done
        
      for dir4 in `ls $eos_dir$prod_tag/$dir1/$dir2/$dir3`; do

        nFiles=0
        for fName in `ls $eos_dir$prod_tag/$dir1/$dir2/$dir3/$dir4`; do
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

          hadd_str="$eos_dir$prod_tag/$dir1/$dir2/$dir3/NTuple_$nOut.root"
          nAdded=0
          for fName in `ls $eos_dir$prod_tag/$dir1/$dir2/$dir3/$dir4`; do
            if test "${used_files#*$fName}" != "$used_files"; then
              continue
            fi
            if test "${fName#*.root}" != "$fName"; then
              if [ "$nAdded" -lt $max_add ]; then
                hadd_str="$hadd_str $eos_dir$prod_tag/$dir1/$dir2/$dir3/$dir4/$fName"
                used_files="$used_files $fName"
                let "nAdded += 1"
                let "nTot += 1"
              fi
            fi
          done  ## Closes for loop over max_add files
          echo "About to hadd $eos_dir$prod_tag/$dir1/$dir2"
          # echo "$hadd_str"
          hadd $hadd_str
          echo ""
          echo "  * Wrote out $eos_dir$prod_tag/$dir1/$dir2/$dir3/NTuple_$nOut.root ... "
          echo ""
          let "nOut += 1"
        done  ## Closes while loop over all files
      done  ## Closes for loop over dir4 ("0000")
    done  ## Closes for loop over dir3 (crab timestamp)
  done ## Closes for loop over dir2 (sample name)
done  ## Closes for loop over dir1 (DAS name)
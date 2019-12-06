How to launch crab jobs
-----------------------

Update your area
```
git pull
```

Check if there is a production branch open for the release. Should also be logged in the issues.
There should always be a production branch from master so it's easier to adap the code for the production or fix last minutes bugs without interfering with master.

If there isn't one already create one. For 2017 for example, for the release v17.<version>.X. Keep always the last value general using "X" otherwise it will interfere with the tags. For git tags and branches are the same thing.
 ```
 git checkout master_2017_94x
 git checkout -b prod-v17.<version>.X
 ```

Checkout the production branch, and recompile and test it - to be safe.

```
git checkout prod-v17.<version>.X
git pull
scram b clean
scram b -j 6
cmsRun test/test_ntupliser_mc.py
cmsRun test/test_ntupliser_data.py
```

If all is good prepare a tag. 
```
git tag -m "first test of v17.<version>.X" prod-v17.<version>.0
python crab/make_crab_script.py -s <samples names> 
```

This will create a directory <crab_dir> with date and tag - if you forgot to tag it will have the hash of your last commit. 
This is useful when you make a small technical modification to an already tagged version, indicating that these ntuples can be used together (though keeping track that something is different).

Then you can submit and check:

```
./<crab_dir>/submit_all.sh
./<crab_dir>/check_all.sh
```


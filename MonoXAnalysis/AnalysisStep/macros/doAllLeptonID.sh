#!/bin/sh

# do muons first
for region in barrel endcap
do 
    for id in loose tight
    do 
	./runIDEffChain.sh "muon" ${region} ${id}
    done
done

# Do electrons second
for region in barrel endcap
do 
    for id in veto tight
    do 
	./runIDEffChain.sh "electron" ${region} ${id}
    done
done

root -l -b -q combineIDEffSF.C

echo "DONE"
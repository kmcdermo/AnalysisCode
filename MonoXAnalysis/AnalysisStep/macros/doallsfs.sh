#!/bin/sh

# # do muons first
# for region in barrel endcap
# do 
#     for id in loose tight
#     do 
# 	./doall.sh "muon" ${region} ${id}
#     done
# done

# Do electrons second
for region in barrel endcap
do 
    for id in veto tight
    do 
	./doall.sh "electron" ${region} ${id}
    done
done

#root -l -b -q allinone.C

echo "DONE"
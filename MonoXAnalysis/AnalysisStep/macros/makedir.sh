#! /bin/sh

for lepton in electron #muon #electron
do

    for data in Data MC scalefactor
    do

	for region in barrel endcap
	do
	
	    for id in veto tight #veto loose medium tight pf
	    do

		mkdir -p output/${lepton}/${data}/${region}/${id}
		
	    done
	    
	done
	
    done

done
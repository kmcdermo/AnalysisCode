#! /bin/sh

for lepton in electron #muon #electron
do

    for data in Data MC scalefactor
    do

	for region in barrel endcap
	do
	
	    for trig in hltel23 hltel27 #hlttkmu20 hltmu20 #
	    do

		mkdir -p output_trig/${lepton}/${data}/${region}/${trig}
		
	    done
	    
	done
	
    done

done
#! /bin/sh

lepton=$1
region=$2
id=$3

# MC Template Building + Make MC Effiency File 
root -l -b -q "mcEfficiency.C("\"${lepton}\",\"${region}\",\"${id}\"")"

# Do Data Fit for templates
mainmodelstr=""
#mainmodelstr="sigtempl_bkgroocms"
#cmsRun output/${lepton}/Data/${region}/${id}/tnpanalysis_templates${mainmodelstr}.py

# Do Data Fit for exponential background
bkgmodel2str="_bkg-exp"
cmsRun output/${lepton}/Data/${region}/${id}/tnpanalysis_templates${bkgmodel2str}.py

# Extract projections from data fits to make overall data plot
root -l -b -q "extract.C("\"${lepton}\",\"${region}\",\"${id}\",\"${mainmodelstr}\"")"
root -l -b -q "extract.C("\"${lepton}\",\"${region}\",\"${id}\",\"${bkgmodel2str}\"")"

# Extract projections from data fits to make overall data plot
root -l -b -q "scaleFactors.C("\"${lepton}\",\"${region}\",\"${id}\",\"${mainmodelstr}\",\"${bkgmodel2str}\"")"


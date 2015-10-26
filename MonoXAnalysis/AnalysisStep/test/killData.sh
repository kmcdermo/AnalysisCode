#!/bin/sh

for sample in crab_05OctRR-monoX_DoubleEG  crab_05OctRR-monoX_MET       crab_05OctRR-monoX_SingleMu crab_05OctRR-monoX_DoubleMu  crab_05OctRR-monoX_SingleEl  crab_05OctRR-monoX_SinglePh

#crab_PRv4-monoX_DoubleEG  crab_PRv4-monoX_DoubleMu  crab_PRv4-monoX_SingleEl  crab_PRv4-monoX_SingleMu  crab_PRv4-monoX_SinglePh  crab_PRv4-monoX_met

do

crab kill -d ${sample}

done

#crab_Oct05Rereco-monoX           crab_Oct05Rereco-monoX_DoubleEG      crab_Oct05Rereco-monoX_met       crab_Oct05Rereco-monoX_SingleEl      crab_Oct05Rereco-monoX_singleMuon  crab_Oct05Rereco-monoX_doubleEG  crab_Oct05Rereco-monoX_DoubleEG-PAT  crab_Oct05Rereco-monoX_singleEl  crab_Oct05Rereco-monoX_SingleEl-PAT  crab_Oct05Rereco-monoX_singlePh
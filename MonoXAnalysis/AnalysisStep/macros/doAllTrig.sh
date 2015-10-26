#!/bin/sh

root -l -b -q trigEff_mc.C 
root -l -b -q trigEff_data.C
root -l -b -q trigScaleFactors.C
root -l -b -q combineTrigEffSF.C

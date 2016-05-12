============
AnalysisCode
============

Repository for analysis code

Recipe for 76X (temp fixes for pileup jet id):

       cmsrel CMSSW_7_6_4
       cd CMSSW_7_6_4/src
       cmsenv
       git cms-init
       #echo /CommonTools/PileupAlgos/ > .git/info/sparse-checkout
       #echo /CommonTools/Utils/ >> .git/info/sparse-checkout
       #echo /JetMETCorrections/Configuration/ >> .git/info/sparse-checkout
       #echo /JetMETCorrections/Modules/ >> .git/info/sparse-checkout
       #echo /JetMETCorrections/Type1MET/ >> .git/info/sparse-checkout
       #echo /PhysicsTools/PatAlgos/ >> .git/info/sparse-checkout
       #echo /PhysicsTools/PatUtils/ >> .git/info/sparse-checkout
       #echo /RecoMET/METAlgorithms/ >> .git/info/sparse-checkout
       #echo /RecoMET/METProducers/ >> .git/info/sparse-checkout
       git cms-merge-topic cms-met:metTool76X
       git cms-addpkg RecoJets/JetProducers
       git-cms-merge-topic jbrands:pileupJetId76X
       cd RecoJets/JetProducers/data/
       wget https://github.com/jbrands/RecoJets-JetProducers/raw/3dad903ed25d025f68be94d6f781ca957d6f86ac/pileupJetId_76x_Eta0to2p5_BDT.weights.xml.gz
       wget https://github.com/jbrands/RecoJets-JetProducers/raw/3dad903ed25d025f68be94d6f781ca957d6f86ac/pileupJetId_76x_Eta2p5to2p75_BDT.weights.xml.gz
       wget https://github.com/jbrands/RecoJets-JetProducers/raw/3dad903ed25d025f68be94d6f781ca957d6f86ac/pileupJetId_76x_Eta2p75to3_BDT.weights.xml.gz
       wget https://github.com/jbrands/RecoJets-JetProducers/raw/3dad903ed25d025f68be94d6f781ca957d6f86ac/pileupJetId_76x_Eta3to5_BDT.weights.xml.gz	   
       cd ../../..	
       git clone git@github.com:avartak/AnalysisCode.git -b Raffaele_76X
       git clone https://github.com/rfriese/RecoMET-METPUSubtraction data -b 74X-13TeV-Summer15-July2015
       rm -rf data/.git  
       rm JetMETCorrections/Modules/src/SealModule.cc
	   
How to Run the ntuple production (for analysis):

       cd CMSSW_7_6_4/src/AnalysisCode/MonoXAnalysis/test
       cmsRun tree.py <list of options>

Example:

	cmsRun tree.py isMC=True 	  


Options:   

	   isMC                : set to True when running on simulated events
	   isFastSIM           : set to True when running on fast sim miniAOD (still temp and relying on Emanuele miniAOD)
	   filterHighMETEvents : apply metCut GeV seletion on recoil/met (mumet or elmet or phmet or met)
	   metCut              : met threshold
	   filterOnHLT         : require the OR of all the trigger path definied in the MonoJetTreeMaker (beginRun)
	   usePrivateSQliteJEC : use a local db file for jet energy correction
	   usePrivateSQliteJER : use a local db file for jet energy smearings (by default true since no records in existing GT)
	   applyL2L3Residuals  : apply or not L2L3 residuals on data
	   addPileupJetID      : re-run the pileup-jet id on AK4PFchs jets (new tune for 76X)
	   addQGLikelihood     : add QGL value for AK4PFchs and AK4PFPuppi in case
	   addPuppiJets        : dump Puppi jet info in the MonoJetTreeMaker and add all the related modules in the process
	   addPuppiMET         : dump Puppi met info in the MonoJetTreeMaker and add all the related modules in the process
	   addMVAMet           : add the MVA met (still not working in 76X)
	   useMiniAODMet       : set to True when using miniAOD computed met and related systematics
	   addMETSystematics   : dump MET systematic variations in the tree and, when useMiniAODMet = False, re-evaluate thorugh METSystematicProducer (for PUPPI too)
	   useOfficialMETSystematics : use the official MET tool for systematics and not the private code
	   addSubstructureCHS  : compute all substructure info for PFCHS jets (different parameters can be changed directly in tree.py)
	   addSubstructurePuppi: compute all substructure info for PFPuppi jets 
	   processName         : name of the cms.Process
	   miniAODProcess      : name of the cms.Process used in miniAOD production --> useful for MET filters..etc
	   outputFileName      : name of the output root file from TFileService
	   globalTag           : GT to be used--> default for MC = 76X_mcRun2_asymptotic_RunIIFall15DR76_v1, default for DATA = 76X_dataRun2_16Dec2015_v0
	   JECEra              : JEC era string
	   useLHEWeights       : dump LHE weights and info (only for MC samples)
	   addQCDPDFWeights    : dump scalar and PDF variations (only for MC samples)
	   addGenParticles     : dump gen level info like W/Z boson and related decaying particles, gen photons, top and anti-top
	   isSignalSample      : dump gen level info for DM particles and mediator, as well as reading masses from the LHE header
	   crossSection        : fix the cross section branch in fb-1 from an external value
	   dropAnalyzerDumpEDM : to debug, avoid analyzers and dump edm collections produced in the event
	   nThreads            : number of threads
	   isCrab              : to be used to handle correctly local files with Crab

	   
Some useful information:

     Global Tag:
     	    https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideFrontierConditions

     Recipe for pileup-reweight:
     	    https://twiki.cern.ch/twiki/bin/view/CMS/PileupJSONFileforData#2015_Pileup_JSON_Files

	    Example:
	    pileupCalc.py -i Cert_246908-260627_13TeV_PromptReco_Collisions15_25ns_JSON_v2.txt --inputLumiJSON pileup_JSON_11-19-2015.txt  --calcMode true --minBiasXsec 69000 --maxPileupBin 50 --numPileupBins 50 Cert_246908-260627_13TeV_PromptReco_Collisions15_25ns_JSON_v2.root

     MiniAOD content:
     	    https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookMiniAOD2015

     Recipe for muon ID:
     	    https://twiki.cern.ch/twiki/bin/view/CMS/SWGuideMuonIdRun2

     Recipe for electron ID (cut based):
     	    https://twiki.cern.ch/twiki/bin/view/CMS/CutBasedElectronIdentificationRun2

     Recipe for photon ID (cut based):
     	    https://twiki.cern.ch/twiki/bin/view/CMS/CutBasedPhotonIdentificationRun2

     Recipe for jet ID:
     	    https://twiki.cern.ch/twiki/bin/view/CMS/JetID

     Recipe for pileup jet ID:
     	    https://twiki.cern.ch/twiki/bin/view/CMS/PileupJetID

     Recipe for Puppi and Puppi MET:
     	    https://twiki.cern.ch/twiki/bin/viewauth/CMS/PUPPI

     Recipe for Quark-Gluon likelihood ID:
     	    https://twiki.cern.ch/twiki/bin/view/CMS/QuarkGluonLikelihood

     Recipe for B-tagging and scale factor:
     	    https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation

     Recipe for V-tagging:
     	    https://twiki.cern.ch/twiki/bin/view/CMS/JetWtagging

     Recipe for DoubleB-tagging:
     	    https://twiki.cern.ch/twiki/bin/view/CMS/Hbbtagging

     Recipe for JEC variations:
     	    https://twiki.cern.ch/twiki/bin/view/CMS/JECDataMC

     Recipe for JER smearings:
     	    https://twiki.cern.ch/twiki/bin/view/CMS/JetResolution

     Recipe for MET filters:
     	    https://twiki.cern.ch/twiki/bin/view/CMS/MissingETOptionalFiltersRun2

     Recipe for MVA MET:
     	    https://twiki.cern.ch/twiki/bin/viewauth/CMS/MVAMet
	 
     Recipe for Recoil Correction:
     	    https://twiki.cern.ch/twiki/bin/view/CMS/MissingETRun2RecoilCorrection

==========================
Combine Package and ROOT 6
==========================

Please have a look to the following twiki: https://twiki.cern.ch/twiki/bin/view/CMS/SWGuideHiggsAnalysisCombinedLimit#ROOT6_SLC6_release_CMSSW_7_4_X

=================================
Run Crab Jobs for a given dataset
=================================

Python multicrab script can be used to submit on multiple dataset in one shot

       cd AnalysisCode/MonoXAnalysis/test/crab
       python <multicrab.py> <multicrab cfg> 

Examples on how to setup the python for data and MC are crab/multicrab_MC_76X.py crab/multicrab_DATA_76X.py:

	 pyCfgParams : list of all the parameters to be given to the cmsRun application when the job is executed on the grid
	 config.JobType.numCores : to allow multi-thread process .. the value should be the same of nThread
	 All the other parameters are the standard crab3 ones: https://twiki.cern.ch/twiki/bin/view/CMSPublic/CRAB3ConfigurationFile

The config file which defines the dataset and additional parmaters for the cmsRun application can be found in SampleList_DATA_76X and SampleList_MC_76X. 

    samples[<name of crab di>] = [<dataset name>, [<additional parameters>]]
    
Example: 

    samples['ZJetsToNuNu_HT-100To200']  = ['/ZJetsToNuNu_HT-100To200_13TeV-madgraph/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM',
    					   ['useLHEWeights=True','addQCDPDFWeights=True','isSignalSample=False','addGenParticles=True','crossSection=280.5']]

=================================
Run Filter step for a dataset
=================================

The filter step macro allows to reduce the event content of the trees produced by the MonoJetTreeMaker, according to a set of predifined selections.

To run the macro:

   cd AnalysisCode/MonoXAnalysis/;
   root -l ;
   .L fiters.C+
   sigfilter(...), zmmfilter(....), zeefilter(...), wmnfilter(...), wenfilter(...), gamfilter(...), topmufilter(...), topelfilter(...)

These function are used to select signal like events, Z->mm, Z->ee, W->mnu, W->enu, gamma+jets, semi-leptonic ttbar muon, semi-leptionc ttbar electron

Basic options:

      inputFileName : name of the input file or name of the crab directory in which different files are locate (TChain is used in this case)
      outputFileName : output file .. the code can take a list of files in input but will produce a single output
      isMC : flag to indicate data or MC
      applyBTagWeights : calculates b-tag scale factors and related uncertainties
      isInputDirectory : specify if the inputFileName is a single file or a directory
      isEOS : in case of a directoy this indicates if it is located in EOS or in a local directory
      xsType: 0 means use the xsec branch stored in the origin MonoJetTreeMaker tree, 1 valuate the xs as sumwgt/Nevents (useful for powheg+minlo mono-jet samples), 2 means take the xs from LHE header stored in the genTree.
      storeGenTree : save the whole gen tree in the output 
      isSinglePhoton: options available only for zeefilter, wenfilter and topelfilter allows to run on single photon dataset keeping events triggered by singlephoton but not by single electron triggers .. aim is to increase the statistics at high pt.

To run the filter step on a crab output:

   python scripts/runFilters.py -b <options>

Options:
	
	--inputDIR : input directory path
	--outputDIR : output directory path
	--filterName = "sigfilter",....... "all" => when you want to run all the filters (one filter = one job)
	--calculateXSfromSW : to calculate xs from sum of weights
	--calculateXSfromLHE : take xs from LHE header
	--isMC
	--applyBTagSF
	--storeGenTree
	--isSinglePhoton
	--isCrabDirectory : indicates if the directory has been created by crab (use a recursive find method to make the file list for the TChain)
	--isOnEOS
	--batchMode : means run the filter.C code on lxbatch
	--jobDIR : direcotry where all the jobs sh are created
	--queque <string>
	--submit : to submit while created

Example:

	python scripts/runFilters.py --inputDIR /store/group/upgrade/delphes/VBS_SS/Production-03-04-2016//WWToLNuQQ_13TeV-powheg --outputDIR /store/group/upgrade/delphes/VBS_SS/Production-03-04-2016/SkimmedProduction-12-05-2016/ --filterName all --jobDIR JOB --queque 1nd --batchMode --submit --isOnEOS --isMC --applyBTagSF --isCrabDirectory 


==========================================
Run Filter step for all the crab outputs
==========================================

If you want to run in one shot filters on a set of outputs produced by crab for different datasets you can use:

   python scripts/submitFilters.py <options>

Options:

	--inputDIR : mother crab directory, typically located on EOS
	--outputDIR : output directory .. typically located on EOS
	<many options in common with scripts/runFilters.py>
	--grepName <name 1>,<name 2> ..: to look only at specific subdir which name contains all the string in the list
	--skipName <name 1>,<name 2> ..: to skip the sub-dir which name contains one  of the string in the list

Example:

	python scripts/submitFilters.py --inputDIR /store/group/upgrade/delphes/VBS_SS/Production-03-04-2016/ --outputDIR /store/group/upgrade/delphes/VBS_SS/Production-03-04-2016/SkimmedProduction-12-05-2016/ --filterName all --isMC --applyBTagSF --skipName MET,SinglePhoton,SingleEle --jobDIR JOB --queque 1nd

=================================
Copy Files to a local laptop
=================================

Once all the filtered files are available in some directory (typically on EOS), a script can be used to copy all or some of them to a local machine, where the last stages of the analysis are done:

     python scripts/files/copyAllDirectoriesEOS.py  <options>

Options:

	--inputDIR : mother direcotry where all the filtered files are located
	--outputDIR : local folder on a local machine
	--toEOS: in case the copy is not from EOS to a local machine but from a local machine to EOS
	--grepName name1,name2... : copy only a set of sub-dirs
	--skipName name1.name2... : skip some sub-dirs

Example:

	python scripts/files/copyAllDirectoriesEOS.py --inputDIR /store/group/upgrade/delphes/VBS_SS/Production-03-04-2016/SkimmedProduction-12-05-2016/ --outputDIR /home/rgerosa/test/ --grepName Axial,1000


To copy only files belonging to a single directory each time, please use: scripts/files/copyFilesEOS.py

   python scripts/files/copyFilesEOS.py <options>     

=================================
Merge directories in a clever way
=================================

Once all the files are copied to a local machine, is a good thing to arrange them in common directories to run the last steps of the analysis. As example, if you have for Mono-jet Vector production 100 mass points, instead of keeping 100 directories, you can merge all the filter directories (sigfilter, zmmfilter..etc) into a common one. The output root file already reflects the name of the sample so there is no need of having indipendent directories (just the way in which crab is setup).

     python scripts/files/mergeDirectories.py <options>

Options:

	--inputDIR : mother directory that containes all the sub-directories that you wanna merge
	--outputDIR : name of the output common directory
	--grepName name1,name2... : merge only a	set of sub-dirs
	--skipName name1.name2... : skip some sub-dirs

Example:
	python scripts/files/mergeDirectories.py --inputDIR /home/rgerosa/test/ --outputDIR /home/rgerosa/test/DMV_Axial/ --grepName Axial


=================================
Merge ROOT files in a clever way
=================================

	python scripts/files/mergeFile.py <options>

Options:
	--inputDIR : directory that contains all the files to be merged
	--outputName : name of the single root file created

=======================================
Run Basic makeTemplate for the analysis
=======================================

After the filter step, once all the files are copied to a local machine and correctly organized in directories, these are the useful codes to run the analysis:

      cd AnalysisCode/MonoXAnalysis/macros

      macros/histoUtils.h : used to define the binning of each 1D observables as std::vector<float>. In addtion there are function usefult to smooth empty bins, make the average of two histograms, fix shape uncertainties, fix empty bins for combine and generate evenvelope given a set of input histograms

      macros/histoUtils2D.h: same thing for 2D histograms .. this time there are also function to perform rolling and un-rolling (useful for a 2D analysis)

      macros/makehist.h: function that makes the loop on the events, apply selections and weights. Some external files are useful here and located in the AnalysisCode/MonoXAnalysis/data directory. baseInputTreePath is a string which indicated the base directory where all the input root files are located.

      macros/makeCorrHistograms.C : set of functions used to create Transfer factors and variations for the different control regions (also top regions in case needed)
      
      macros/makeDataHistograms.C : set of functions used to select data and MC events belonging to Z->mm, Z->ee, W->mn, W->en, gamma+jets, SR, ttbar mu, ttbar e. Indipendent functions applied selections on signal samples: one function for Higgs invisible vs mH, one function for DM analysis

      macros/makeTemplates.C: main code to be run


To run:

   cd AnalysisCode/MonoXAnalysis/macros;
   root -l;
   .L makeTemplates.C+;
   makeTemplates.C(....options ...);

Options:
      
      doCorrectionHistograms : true when you want to prodce root files with Transfer Factors
      skipCorrectionHistograms : when true the codes tries to open root files with TFs and clone them in the template file used to create combine workspace
      category : it rules the analysis selection  0 means mono=jet inclusive, 1 means mono-jet exclusive, 2 means mono-V .. 3,4,5..etc are used to apply on some sub-structure cuts
      lumi : luminosity value in fb-1
      outDir: directory where TFs and template file will be created
      templateSuffix : suffix to be added to the template file name
      observables: different observebales to be considered when created templates {"met","jetPt","njet"} .. names are delcared in macros/histoUtils.h
      observables_2D: 2D combinations {"met_ht","met_njet"} ... names are declared in macros/histoUtils2D.h
      applyQGLReweight : if true re-weight QGL leading AK8 jet MC to data using pre-existing files in the data directory
      doShapeSystematics : if true evaluate MET systematics (JEC, JER, unclustered) and b-tagging SF effects for each MC based process
      makeResonantSelection : split ttbar in resonant and non resonant (substructure studies)
      typeOfDMSignal : run only on some signal production mechanism .. 0 means both mono-j and mono-V, 1 is mono-j, 2 is mono-V  
      runHiggsInvisible : run Higgs invisible analysis instead of DM one (when trye the value of typeOfDMSignal doesn't matter)
      runOnlySignal : when true apply selections only on signal MC in SR
      runOnlyBackground : generate templates for data and bkg processes in SR and CRs					 
      applyPostFitWeights : when true post-fit met binned weights are applied to the event
      addTop : to run selections also for the top enriched control samples
      ext : additional string

==========================
Create analysis Worksapce
==========================

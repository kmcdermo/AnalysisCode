  TBranch  *bmumcmass       = mumctree->GetBranch("mass");
  TBranch  *bmumcpt         = mumctree->GetBranch("pt");
  TBranch  *bmumcabseta     = mumctree->GetBranch("abseta");
  TBranch  *bmumcmc         = mumctree->GetBranch("mcTrue");
  TBranch  *bmumcid         = mumctree->GetBranch("tightid");
  TBranch  *bmumcnvtx       = mumctree->GetBranch("nvtx");
  TBranch  *bmumcwgt        = mumctree->GetBranch("wgt");
  TBranch  *bmumchlt20      = mumctree->GetBranch("hltmu20");
  TBranch  *bmumchlttk20    = mumctree->GetBranch("hlttkmu20");

  Float_t  mumcmass         = 0.0;
  Float_t  mumcpt           = 0.0;
  Float_t  mumcabseta       = 0.0;
  Float_t  mumcnvtx         = 0.0;
  Float_t  mumcwgt          = 0.0;
  Int_t    mumcmc           = 0; 
  Int_t    mumcid           = 0;
  Int_t    mumchlt20        = 0;
  Int_t    mumchlttk20      = 0;

  bmumcmass  ->SetAddress(&mumcmass);
  bmumcpt    ->SetAddress(&mumcpt);
  bmumcabseta->SetAddress(&mumcabseta);
  bmumcmc    ->SetAddress(&mumcmc);
  bmumcid    ->SetAddress(&mumcid);
  bmumcnvtx  ->SetAddress(&mumcnvtx);
  bmumcwgt   ->SetAddress(&mumcwgt);
  bmumchlt20 ->SetAddress(&mumchlt20);
  bmumchlttk20->SetAddress(&mumchlttk20);



  TBranch  *belmcmass       = elmctree->GetBranch("mass");
  TBranch  *belmcpt         = elmctree->GetBranch("pt");
  TBranch  *belmcabseta     = elmctree->GetBranch("abseta");
  TBranch  *belmcmc         = elmctree->GetBranch("mcTrue");
  TBranch  *belmcid         = elmctree->GetBranch("tightid");
  TBranch  *belmcnvtx       = elmctree->GetBranch("nvtx");
  TBranch  *belmcwgt        = elmctree->GetBranch("wgt");
  TBranch  *belmchlt23      = elmctree->GetBranch("hltmc23");
  TBranch  *belmchlt27      = elmctree->GetBranch("hltmc27");

  Float_t  elmcmass         = 0.0;
  Float_t  elmcpt           = 0.0;
  Float_t  elmcabseta       = 0.0;
  Float_t  elmcnvtx         = 0.0;
  Float_t  elmcwgt          = 0.0;
  Int_t    elmcmc           = 0; 
  Int_t    elmcid           = 0;
  Int_t    elmchlt23        = 0;
  Int_t    elmchlt27        = 0;

  belmcmass  ->SetAddress(&elmcmass);
  belmcpt    ->SetAddress(&elmcpt);
  belmcabseta->SetAddress(&elmcabseta);
  belmcmc    ->SetAddress(&elmcmc);
  belmcid    ->SetAddress(&elmcid);
  belmcnvtx  ->SetAddress(&elmcnvtx);
  belmcwgt   ->SetAddress(&elmcwgt);
  belmchlt23 ->SetAddress(&elmchlt23);
  belmchlt27 ->SetAddress(&elmchlt27);

  TBranch  *bmumass       = mutree->GetBranch("mass");
  TBranch  *bmupt         = mutree->GetBranch("pt");
  TBranch  *bmuabseta     = mutree->GetBranch("abseta");
  TBranch  *bmuid         = mutree->GetBranch("tightid");
  TBranch  *bmuhlt20      = mutree->GetBranch("hltmu20");
  TBranch  *bmuhlttk20    = mutree->GetBranch("hlttkmu20");

  Float_t  mumass         = 0.0;
  Float_t  mupt           = 0.0;
  Float_t  muabseta       = 0.0;
  Int_t    muid           = 0;
  Int_t    muhlt20        = 0;
  Int_t    muhlttk20      = 0;

  bmumass  ->SetAddress(&mumass);
  bmupt    ->SetAddress(&mupt);
  bmuabseta->SetAddress(&muabseta);
  bmuid    ->SetAddress(&muid);
  bmuhlt20 ->SetAddress(&muhlt20);
  bmuhlttk20->SetAddress(&muhlttk20);

  TBranch  *belmass       = eltree->GetBranch("mass");
  TBranch  *belpt         = eltree->GetBranch("pt");
  TBranch  *belabseta     = eltree->GetBranch("abseta");
  TBranch  *belid         = eltree->GetBranch("tightid");
  TBranch  *belhlt23      = eltree->GetBranch("hltdata23");
  TBranch  *belhlt27      = eltree->GetBranch("hltdata27");

  Float_t  elmass         = 0.0;
  Float_t  elpt           = 0.0;
  Float_t  elabseta       = 0.0;
  Int_t    elid           = 0;
  Int_t    elhlt23        = 0;
  Int_t    elhlt27        = 0;

  belmass  ->SetAddress(&elmass);
  belpt    ->SetAddress(&elpt);
  belabseta->SetAddress(&elabseta);
  belid    ->SetAddress(&elid);
  belhlt23 ->SetAddress(&elhlt23);
  belhlt27 ->SetAddress(&elhlt27);


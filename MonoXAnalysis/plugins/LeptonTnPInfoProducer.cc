#include <memory>
#include <vector>
#include <iostream>
#include <string>

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/stream/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/Common/interface/ValueMap.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/MuonReco/interface/MuonSelectors.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "FWCore/Common/interface/TriggerNames.h"

class LeptonTnPInfoProducer : public edm::stream::EDProducer<> {
    public:
        explicit LeptonTnPInfoProducer(const edm::ParameterSet&);
        ~LeptonTnPInfoProducer();
        
        static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
    
    private:
        virtual void beginJob() ;
        virtual void produce(edm::Event&, const edm::EventSetup&) ;
        virtual void endJob() ;
        
        virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
        virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
        virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
        virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;

        const edm::EDGetTokenT<GenEventInfoProduct> geninfoToken;
        const edm::EDGetTokenT<std::vector<reco::Vertex> > verticesToken;
        const edm::EDGetTokenT<std::vector<pat::Muon> > muonsToken;
        const edm::EDGetTokenT<std::vector<pat::Electron> > electronsToken;
        const edm::EDGetTokenT<pat::TriggerObjectStandAloneCollection> triggerObjectsToken;
        const edm::EDGetTokenT<edm::TriggerResults> triggerResultsToken;
        const edm::EDGetTokenT<edm::ValueMap<bool> > electronVetoIdMapToken;
        const edm::EDGetTokenT<edm::ValueMap<bool> > electronLooseIdMapToken;
        const edm::EDGetTokenT<edm::ValueMap<bool> > electronMediumIdMapToken;
        const edm::EDGetTokenT<edm::ValueMap<bool> > electronTightIdMapToken;

        const double loosemuisocut;
        const double tightmuisocut;
        const double tagmuonptcut;
        const double tagmuonetacut;
        const double tagmuontrigmatchdR;
        const bool   requiremuonhlt;
        const std::vector<std::string> tagmuontriggers;
        const double tagelectronptcut;
        const double tagelectronetacut;
        const double tagelectrontrigmatchdR;
        const bool   requireelectronhlt;
        const std::vector<std::string> tagelectrontriggers;
};

LeptonTnPInfoProducer::LeptonTnPInfoProducer(const edm::ParameterSet& iConfig): 
    geninfoToken(consumes<GenEventInfoProduct>(iConfig.getParameter<edm::InputTag>("geninfo"))),
    verticesToken(consumes<std::vector<reco::Vertex> >(iConfig.getParameter<edm::InputTag>("vertices"))),
    muonsToken(consumes<std::vector<pat::Muon> >(iConfig.getParameter<edm::InputTag>("muons"))),
    electronsToken(consumes<std::vector<pat::Electron> >(iConfig.getParameter<edm::InputTag>("electrons"))),
    triggerObjectsToken(consumes<pat::TriggerObjectStandAloneCollection>(iConfig.getParameter<edm::InputTag>("triggerobjects"))),
    triggerResultsToken(consumes<edm::TriggerResults>(iConfig.getParameter<edm::InputTag>("triggerResults"))),
    electronVetoIdMapToken(consumes<edm::ValueMap<bool> >(iConfig.getParameter<edm::InputTag>("electronvetoid"))),
    electronLooseIdMapToken(consumes<edm::ValueMap<bool> >(iConfig.getParameter<edm::InputTag>("electronlooseid"))),
    electronMediumIdMapToken(consumes<edm::ValueMap<bool> >(iConfig.getParameter<edm::InputTag>("electronmediumid"))),
    electronTightIdMapToken(consumes<edm::ValueMap<bool> >(iConfig.getParameter<edm::InputTag>("electrontightid"))),
    loosemuisocut(iConfig.getParameter<double>("loosemuisocut")),
    tightmuisocut(iConfig.getParameter<double>("tightmuisocut")),
    tagmuonptcut(iConfig.getParameter<double>("tagmuonptcut")),
    tagmuonetacut(iConfig.getParameter<double>("tagmuonetacut")),
    tagmuontrigmatchdR(iConfig.getParameter<double>("tagmuontrigmatchdR")),
    requiremuonhlt(iConfig.getParameter<bool>("requiremuonhlt")),
    tagmuontriggers(iConfig.getParameter<std::vector<std::string> >("tagmuontriggers")),
    tagelectronptcut(iConfig.getParameter<double>("tagelectronptcut")),
    tagelectronetacut(iConfig.getParameter<double>("tagelectronetacut")),
    tagelectrontrigmatchdR(iConfig.getParameter<double>("tagelectrontrigmatchdR")),
    requireelectronhlt(iConfig.getParameter<bool>("requireelectronhlt")),
    tagelectrontriggers(iConfig.getParameter<std::vector<std::string> >("tagelectrontriggers"))
{
    produces<edm::ValueMap<float> >("munvtxmap");
    produces<edm::ValueMap<float> >("muwgtmap");

    // Muon HLT Refs
    produces<pat::MuonRefVector>("hltmu20muonrefs");
    produces<pat::MuonRefVector>("hlttkmu20muonrefs");
    //    produces<pat::MuonRefVector>("hltmu24muonrefs");
    //    produces<pat::MuonRefVector>("hlttkmu24muonrefs");

    produces<pat::MuonRefVector>("loosemuonrefs");
    produces<pat::MuonRefVector>("tightmuonrefs");
    produces<pat::MuonCollection>("tightmuons");
    produces<edm::ValueMap<float> >("elnvtxmap");
    produces<edm::ValueMap<float> >("elwgtmap");

    // Electron HLT Refs
    produces<pat::ElectronRefVector>("hltel23calotrkisoelectronmcrefs");
    produces<pat::ElectronRefVector>("hltel27wp85electronmcrefs");
    produces<pat::ElectronRefVector>("hltel23wplooseelectrondatarefs");
    produces<pat::ElectronRefVector>("hltel27wplooseelectrondatarefs");

    produces<pat::ElectronRefVector>("vetoelectronrefs");
    produces<pat::ElectronRefVector>("looseelectronrefs");
    produces<pat::ElectronRefVector>("mediumelectronrefs");
    produces<pat::ElectronRefVector>("tightelectronrefs");
    produces<pat::ElectronCollection>("tightelectrons");
}


LeptonTnPInfoProducer::~LeptonTnPInfoProducer() {
}

void LeptonTnPInfoProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup) {
    using namespace edm;
    using namespace reco;
    using namespace std;

    Handle<GenEventInfoProduct> geninfoH;
    iEvent.getByToken(geninfoToken, geninfoH);

    Handle<std::vector<reco::Vertex> > verticesH;
    iEvent.getByToken(verticesToken, verticesH);

    Handle<std::vector<pat::Muon> > muonsH;
    iEvent.getByToken(muonsToken, muonsH);

    Handle<std::vector<pat::Electron> > electronsH;
    iEvent.getByToken(electronsToken, electronsH);

    Handle<pat::TriggerObjectStandAloneCollection> triggerObjectsH;
    iEvent.getByToken(triggerObjectsToken, triggerObjectsH);

    Handle<edm::TriggerResults> triggerResultsH;
    iEvent.getByToken(triggerResultsToken, triggerResultsH);

    Handle<edm::ValueMap<bool> > electronVetoIdH;
    iEvent.getByToken(electronVetoIdMapToken, electronVetoIdH);

    Handle<edm::ValueMap<bool> > electronLooseIdH;
    iEvent.getByToken(electronLooseIdMapToken, electronLooseIdH);

    Handle<edm::ValueMap<bool> > electronMediumIdH;
    iEvent.getByToken(electronMediumIdMapToken, electronMediumIdH);

    Handle<edm::ValueMap<bool> > electronTightIdH;
    iEvent.getByToken(electronTightIdMapToken, electronTightIdH);

    std::auto_ptr<edm::ValueMap<float> > outputmunvtxmap(new ValueMap<float>());
    std::auto_ptr<edm::ValueMap<float> > outputmuwgtmap(new ValueMap<float>());

    std::auto_ptr<pat::MuonRefVector> outputhltmu20muonrefs(new pat::MuonRefVector);
    std::auto_ptr<pat::MuonRefVector> outputhlttkmu20muonrefs(new pat::MuonRefVector);
    //    std::auto_ptr<pat::MuonRefVector> outputhltmu24muonrefs(new pat::MuonRefVector);
    //    std::auto_ptr<pat::MuonRefVector> outputhlttkmu24muonrefs(new pat::MuonRefVector);

    std::auto_ptr<pat::MuonRefVector> outputloosemuonrefs(new pat::MuonRefVector);
    std::auto_ptr<pat::MuonRefVector> outputtightmuonrefs(new pat::MuonRefVector);
    std::auto_ptr<pat::MuonCollection> outputtightmuons(new pat::MuonCollection);
    std::auto_ptr<edm::ValueMap<float> > outputelnvtxmap(new ValueMap<float>());
    std::auto_ptr<edm::ValueMap<float> > outputelwgtmap(new ValueMap<float>());
    std::auto_ptr<pat::ElectronRefVector> outputvetoelectronrefs(new pat::ElectronRefVector);
    std::auto_ptr<pat::ElectronRefVector> outputlooseelectronrefs(new pat::ElectronRefVector);
    std::auto_ptr<pat::ElectronRefVector> outputmediumelectronrefs(new pat::ElectronRefVector);
    std::auto_ptr<pat::ElectronRefVector> outputtightelectronrefs(new pat::ElectronRefVector);
    std::auto_ptr<pat::ElectronCollection> outputtightelectrons(new pat::ElectronCollection);

    std::auto_ptr<pat::ElectronRefVector> outputhltel23calotrkisoelectronmcrefs(new pat::ElectronRefVector);
    std::auto_ptr<pat::ElectronRefVector> outputhltel27wp85electronmcrefs(new pat::ElectronRefVector);
    std::auto_ptr<pat::ElectronRefVector> outputhltel23wplooseelectrondatarefs(new pat::ElectronRefVector);
    std::auto_ptr<pat::ElectronRefVector> outputhltel27wplooseelectrondatarefs(new pat::ElectronRefVector);

    float wgt = 1.0;
    if (geninfoH.isValid()) wgt = geninfoH->weight(); 

    const edm::TriggerNames& trigNames = iEvent.triggerNames(*triggerResultsH);

    vector<float> munvtxvector;
    vector<float> muwgtvector;
    for (vector<pat::Muon>::const_iterator muons_iter = muonsH->begin(); muons_iter != muonsH->end(); ++muons_iter) {
        float isoval = muons_iter->pfIsolationR04().sumNeutralHadronEt;
        isoval += muons_iter->pfIsolationR04().sumPhotonEt;
        isoval -= 0.5*muons_iter->pfIsolationR04().sumPUPt;
        if (isoval < 0.) isoval = 0.;
        isoval += muons_iter->pfIsolationR04().sumChargedHadronPt;
        isoval /= muons_iter->pt();

        bool triggermatched = false;
        bool hltisomu20matched = false;
        bool hltisotkmu20matched = false;
	//        bool hltisomu24matched = false;
	//        bool hltisotkmu24matched = false;
        for (pat::TriggerObjectStandAlone trgobj : *triggerObjectsH) {
            trgobj.unpackPathNames(trigNames);
            for (std::string trigpath : tagmuontriggers) {
                if (trgobj.hasPathName(trigpath, true, true) && deltaR(trgobj.eta(), trgobj.phi(), muons_iter->eta(), muons_iter->phi()) < tagmuontrigmatchdR) triggermatched = true;
            }
            if (trgobj.hasPathName("HLT_IsoMu20_v*"  , true, true) && deltaR(trgobj.eta(), trgobj.phi(), muons_iter->eta(), muons_iter->phi()) < tagmuontrigmatchdR) hltisomu20matched   = true;
            if (trgobj.hasPathName("HLT_IsoTkMu20_v*", true, true) && deltaR(trgobj.eta(), trgobj.phi(), muons_iter->eta(), muons_iter->phi()) < tagmuontrigmatchdR) hltisotkmu20matched = true;
	    //            if (trgobj.hasPathName("HLT_IsoMu24_v*"  , true, true) && deltaR(trgobj.eta(), trgobj.phi(), muons_iter->eta(), muons_iter->phi()) < tagmuontrigmatchdR) hltisomu24matched   = true;
	    //            if (trgobj.hasPathName("HLT_IsoTkMu24_v*", true, true) && deltaR(trgobj.eta(), trgobj.phi(), muons_iter->eta(), muons_iter->phi()) < tagmuontrigmatchdR) hltisotkmu24matched = true;
        }
        if (!requiremuonhlt) triggermatched = true;

        if (verticesH->size() != 0 && hltisomu20matched                                                               ) outputhltmu20muonrefs  ->push_back(pat::MuonRef(muonsH, muons_iter - muonsH->begin()));
        if (verticesH->size() != 0 && hltisotkmu20matched                                                             ) outputhlttkmu20muonrefs->push_back(pat::MuonRef(muonsH, muons_iter - muonsH->begin()));
	//        if (verticesH->size() != 0 && hltisomu24matched                                                               ) outputhltmu24muonrefs  ->push_back(pat::MuonRef(muonsH, muons_iter - muonsH->begin()));
	//        if (verticesH->size() != 0 && hltisotkmu24matched                                                             ) outputhlttkmu24muonrefs->push_back(pat::MuonRef(muonsH, muons_iter - muonsH->begin()));
        if (verticesH->size() != 0 && muon::isLooseMuon(*muons_iter)                        && isoval <= loosemuisocut) outputloosemuonrefs    ->push_back(pat::MuonRef(muonsH, muons_iter - muonsH->begin()));
        if (verticesH->size() != 0 && muon::isTightMuon(*muons_iter, *(verticesH->begin())) && isoval <= tightmuisocut) outputtightmuonrefs    ->push_back(pat::MuonRef(muonsH, muons_iter - muonsH->begin()));
        if (verticesH->size() != 0 && muon::isTightMuon(*muons_iter, *(verticesH->begin())) && isoval <= tightmuisocut) {
            if (triggermatched && muons_iter->pt() > tagmuonptcut && fabs(muons_iter->eta()) < tagmuonetacut) outputtightmuons->push_back(*muons_iter);
        }
        munvtxvector.push_back(float(verticesH->size()));
        muwgtvector.push_back(wgt);
    }

    vector<float> elnvtxvector;
    vector<float> elwgtvector;
    for (vector<pat::Electron>::const_iterator electrons_iter = electronsH->begin(); electrons_iter != electronsH->end(); ++electrons_iter) {
        const Ptr<pat::Electron> electronPtr(electronsH, electrons_iter - electronsH->begin());

        bool triggermatched = false;
        bool hltel23calotrkisomcmatched = false;
        bool hltel27wp85mcmatched = false;
        bool hltel23wploosedatamatched = false;
        bool hltel27wploosedatamatched = false;
        for (pat::TriggerObjectStandAlone trgobj : *triggerObjectsH) {
            trgobj.unpackPathNames(trigNames);
            for (std::string trigpath : tagelectrontriggers) {
                if (trgobj.hasPathName(trigpath, true, false) && deltaR(trgobj.eta(), trgobj.phi(), electrons_iter->eta(), electrons_iter->phi()) < tagelectrontrigmatchdR) triggermatched = true;
            }
            if (trgobj.hasPathName("HLT_Ele23_CaloIdL_TrackIdL_IsoVL_v*", true, true) && deltaR(trgobj.eta(), trgobj.phi(), electrons_iter->eta(), electrons_iter->phi()) < tagelectrontrigmatchdR) hltel23calotrkisomcmatched = true;
            if (trgobj.hasPathName("HLT_Ele27_WP85_Gsf_v*"              , true, true) && deltaR(trgobj.eta(), trgobj.phi(), electrons_iter->eta(), electrons_iter->phi()) < tagelectrontrigmatchdR) hltel27wp85mcmatched       = true;
            if (trgobj.hasPathName("HLT_Ele23_WPLoose_Gsf_v*"               , true, true) && deltaR(trgobj.eta(), trgobj.phi(), electrons_iter->eta(), electrons_iter->phi()) < tagelectrontrigmatchdR) hltel23wploosedatamatched  = true;
            if (trgobj.hasPathName("HLT_Ele27_WPLoose_Gsf_v*"               , true, true) && deltaR(trgobj.eta(), trgobj.phi(), electrons_iter->eta(), electrons_iter->phi()) < tagelectrontrigmatchdR) hltel27wploosedatamatched  = true;
        }
        if (!requireelectronhlt) triggermatched = true;

        if (verticesH->size() != 0 && hltel23calotrkisomcmatched       ) outputhltel23calotrkisoelectronmcrefs->push_back(pat::ElectronRef(electronsH, electrons_iter - electronsH->begin()));
        if (verticesH->size() != 0 && hltel27wp85mcmatched             ) outputhltel27wp85electronmcrefs      ->push_back(pat::ElectronRef(electronsH, electrons_iter - electronsH->begin()));
        if (verticesH->size() != 0 && hltel23wploosedatamatched        ) outputhltel23wplooseelectrondatarefs ->push_back(pat::ElectronRef(electronsH, electrons_iter - electronsH->begin()));
        if (verticesH->size() != 0 && hltel27wploosedatamatched        ) outputhltel27wplooseelectrondatarefs ->push_back(pat::ElectronRef(electronsH, electrons_iter - electronsH->begin()));
        if (verticesH->size() != 0 && (*electronVetoIdH)  [electronPtr]) outputvetoelectronrefs  ->push_back(pat::ElectronRef(electronsH, electrons_iter - electronsH->begin()));
        if (verticesH->size() != 0 && (*electronLooseIdH) [electronPtr]) outputlooseelectronrefs ->push_back(pat::ElectronRef(electronsH, electrons_iter - electronsH->begin()));
        if (verticesH->size() != 0 && (*electronMediumIdH)[electronPtr]) outputmediumelectronrefs->push_back(pat::ElectronRef(electronsH, electrons_iter - electronsH->begin()));
        if (verticesH->size() != 0 && (*electronTightIdH) [electronPtr]) outputtightelectronrefs ->push_back(pat::ElectronRef(electronsH, electrons_iter - electronsH->begin()));
        if (verticesH->size() != 0 && (*electronTightIdH) [electronPtr]) {
            if (triggermatched && electrons_iter->pt() > tagelectronptcut && fabs(electrons_iter->eta()) < tagelectronetacut) outputtightelectrons->push_back(*electrons_iter);
        }
        elnvtxvector.push_back(float(verticesH->size()));
        elwgtvector.push_back(wgt);
    }

    edm::ValueMap<float>::Filler munvtxfiller(*outputmunvtxmap);
    munvtxfiller.insert(muonsH, munvtxvector.begin(), munvtxvector.end());
    munvtxfiller.fill();

    edm::ValueMap<float>::Filler muwgtfiller(*outputmuwgtmap);
    muwgtfiller.insert(muonsH, muwgtvector.begin(), muwgtvector.end());
    muwgtfiller.fill();

    edm::ValueMap<float>::Filler elnvtxfiller(*outputelnvtxmap);
    elnvtxfiller.insert(electronsH, elnvtxvector.begin(), elnvtxvector.end());
    elnvtxfiller.fill();

    edm::ValueMap<float>::Filler elwgtfiller(*outputelwgtmap);
    elwgtfiller.insert(electronsH, elwgtvector.begin(), elwgtvector.end());
    elwgtfiller.fill();

    iEvent.put(outputmunvtxmap, "munvtxmap");
    iEvent.put(outputmuwgtmap, "muwgtmap");
    iEvent.put(outputhltmu20muonrefs, "hltmu20muonrefs");
    iEvent.put(outputhlttkmu20muonrefs, "hlttkmu20muonrefs");
    //    iEvent.put(outputhltmu24muonrefs, "hltmu24muonrefs");
    //    iEvent.put(outputhlttkmu24muonrefs, "hlttkmu24muonrefs");
    iEvent.put(outputloosemuonrefs, "loosemuonrefs");
    iEvent.put(outputtightmuonrefs, "tightmuonrefs");
    iEvent.put(outputtightmuons, "tightmuons");
    iEvent.put(outputelnvtxmap, "elnvtxmap");
    iEvent.put(outputelwgtmap, "elwgtmap");
    iEvent.put(outputvetoelectronrefs, "vetoelectronrefs");
    iEvent.put(outputlooseelectronrefs, "looseelectronrefs");
    iEvent.put(outputmediumelectronrefs, "mediumelectronrefs");
    iEvent.put(outputtightelectronrefs, "tightelectronrefs");
    iEvent.put(outputtightelectrons, "tightelectrons");
    iEvent.put(outputhltel23calotrkisoelectronmcrefs, "hltel23calotrkisoelectronmcrefs");
    iEvent.put(outputhltel27wp85electronmcrefs, "hltel27wp85electronmcrefs");
    iEvent.put(outputhltel23wplooseelectrondatarefs, "hltel23wplooseelectrondatarefs");
    iEvent.put(outputhltel27wplooseelectrondatarefs, "hltel27wplooseelectrondatarefs");
}

void LeptonTnPInfoProducer::beginJob() {
}

void LeptonTnPInfoProducer::endJob() {
}

void LeptonTnPInfoProducer::beginRun(edm::Run const&, edm::EventSetup const&) {
}

void LeptonTnPInfoProducer::endRun(edm::Run const&, edm::EventSetup const&) {
}

void LeptonTnPInfoProducer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) {
}

void LeptonTnPInfoProducer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) {
}

void LeptonTnPInfoProducer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
    edm::ParameterSetDescription desc;
    desc.setUnknown();
    descriptions.addDefault(desc);
}

DEFINE_FWK_MODULE(LeptonTnPInfoProducer);

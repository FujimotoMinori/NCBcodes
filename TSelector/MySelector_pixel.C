#define MySelector_pixel_cxx
// The class definition in MySelector_pixel.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.


// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// root> T->Process("MySelector_pixel.C")
// root> T->Process("MySelector_pixel.C","some options")
// root> T->Process("MySelector_pixel.C+")
//


#include "MySelector_pixel.h"
#include <TH1.h>
#include <TH2.h>
#include <TStyle.h>
#include <map>

void MySelector_pixel::Begin(TTree * /*tree*/)
{
	// The Begin() function is called at the start of the query.
	// When running with PROOF Begin() is only called on the client.
	// The tree argument is deprecated (on PROOF 0 is passed).

	TString option = GetOption();
}

void MySelector_pixel::SlaveBegin(TTree * /*tree*/)
{
	// The SlaveBegin() function is called after the Begin() function.
	// When running with PROOF SlaveBegin() is called on each slave server.
	// The tree argument is deprecated (on PROOF 0 is passed).

	TString option = GetOption();
	outputfile_ = "output.root";

        //TH1F
	h_events= new TH1F("events", "; Run Number; Events", 16340, 348150.5, 364490.5);
	h_events_AC= new TH1F("eventsAC", "; Run Number; Events", 16340, 348150.5, 364490.5);
	h_events_CA= new TH1F("eventsCA", "; Run Number; Events", 16340, 348150.5, 364490.5);
	h_events_ACwoPV= new TH1F("eventsACwoPV", "; Run Number; Events", 16340, 348150.5, 364490.5);
	h_events_CAwoPV= new TH1F("eventsCAwoPV", "; Run Number; Events", 16340, 348150.5, 364490.5);
        //for single pixel cluster
	h_all = new TH1F("all", "; Nhits; Events", 300, 0., 300.);
	h_woSmallHits = new TH1F("woSmallHits", "; Nhits; Events", 300, 0., 300.);
	h_wSmallHits = new TH1F("wSmallHits", "; Nhits; Events", 300, 0., 300.);
	h_wSmallHitsA = new TH1F("wSmallHitsA", "; Nhits; Events", 300, 0., 300.);
	h_noiseA = new TH1F("noiseA", "; Nhits; Events", 300, 0., 300.);
	h_noiseC = new TH1F("noiseC", "; Nhits; Events", 300, 0., 300.);
	h_ECA_beam1 = new TH1F("ECA_beam1", "; Nhits; Events", 300, 0., 300.);
	h_ratio_woSmallHits = new TH1F("ratio_woSmallHits", "; ratio; Events", 100, 0., 1.);
	h_ratio_wSmallHits = new TH1F("ratio_wSmallHits", "; ratio; Events", 100, 0., 1.);
	h_ratiocharge_woSmallHits = new TH1F("ratiocharge_woSmallHits", "; ratio; Events", 100, 0., 1.);
	h_ratiocharge_wSmallHits = new TH1F("ratiocharge_wSmallHits", "; ratio; Events", 100, 0., 1.);

	h_ratio_woSmallHits_charge = new TH1F("ratio_woSmallHits_charge", "; ratio; Events", 100, 0., 1.);
	h_ratio_wSmallHits_charge = new TH1F("ratio_wSmallHits_charge", "; ratio; Events", 100, 0., 1.);
	h_ratio_woSmallHits_cut = new TH1F("ratio_woSmallHits_cut", "; ratio; Events", 100, 0., 1.);
	h_ratio_wSmallHits_cut = new TH1F("ratio_wSmallHits_cut", "; ratio; Events", 100, 0., 1.);
	h_ratio= new TH1F("ratio", "; ratio; Events", 100, 0., 1.);

	h_nLB = new TH1F("nLB", "; LB; Events", 300, 0., 300.);

	//h_allnoise = new TH1F("allnoise", "; Run Number", 16340, 348150.5, 364490.5);
	//h_electricnoise = new TH1F("electricnoise", "; Run Number", 16340, 348150.5, 364490.5);
	//h_allnoisewSH = new TH1F("allnoisewSH", "; Run Number", 16340, 348150.5, 364490.5);
	//h_electricnoisewSH = new TH1F("electricnoisewSH", "; Run Number", 16340, 348150.5, 364490.5);
	h_noiserateall = new TH1F("noiserateall", "; Run Number", 16340, 348150.5, 364490.5);
	h_noiserate = new TH1F("noiserate", "; Run Number", 16340, 348150.5, 364490.5);

	//h_allnoiseA = new TH1F("allnoiseA", "; Run Number", 16340, 348150.5, 364490.5);
	//h_electricnoiseA = new TH1F("electricnoiseA", "; Run Number", 16340, 348150.5, 364490.5);
	//h_allnoisewSHA = new TH1F("allnoisewSHA", "; Run Number", 16340, 348150.5, 364490.5);
	//h_electricnoisewSHA = new TH1F("electricnoisewSHA", "; Run Number", 16340, 348150.5, 364490.5);
	h_noiserateallA = new TH1F("noiserateallA", "; Run Number", 16340, 348150.5, 364490.5);
	h_noiserateA = new TH1F("noiserateA", "; Run Number", 16340, 348150.5, 364490.5);

	//h_allnoisecluster = new TH1F("allnoisecluster", "; Run Number", 16340, 348150.5, 364490.5);
	//h_electricnoisecluster = new TH1F("electricnoisecluster", "; Run Number", 16340, 348150.5, 364490.5);
	h_allnoisewSHcluster = new TH1F("allnoisewSHcluster", "; Run Number", 16340, 348150.5, 364490.5);
	h_electricnoisewSHcluster = new TH1F("electricnoisewSHcluster", "; Run Number", 16340, 348150.5, 364490.5);
	h_noiserateallcluster = new TH1F("noiserateallcluster", "; Run Number", 16340, 348150.5, 364490.5);
	h_noiseratecluster = new TH1F("noiseratecluster", "; Run Number", 16340, 348150.5, 364490.5);

	//h_allnoiseAcluster = new TH1F("allnoiseAcluster", "; Run Number", 16340, 348150.5, 364490.5);
	//h_electricnoiseAcluster = new TH1F("electricnoiseAcluster", "; Run Number", 16340, 348150.5, 364490.5);
	h_allnoisewSHAcluster = new TH1F("allnoisewSHAcluster", "; Run Number", 16340, 348150.5, 364490.5);
	h_electricnoisewSHAcluster = new TH1F("electricnoisewSHAcluster", "; Run Number", 16340, 348150.5, 364490.5);
	h_noiserateallAcluster = new TH1F("noiserateallAcluster", "; Run Number", 16340, 348150.5, 364490.5);
	h_noiserateAcluster = new TH1F("noiserateAcluster", "; Run Number", 16340, 348150.5, 364490.5);

	h_allLB = new TH1F("allLB", "; Run Number", 16340, 348150.5, 364490.5);

	ListTH1F.push_back(h_events);
	ListTH1F.push_back(h_events_AC);
	ListTH1F.push_back(h_events_CA);
	ListTH1F.push_back(h_events_ACwoPV);
	ListTH1F.push_back(h_events_CAwoPV);
	//ListTH1F.push_back(h_bcid);
	//ListTH1F.push_back(h_bcid_AC);
	//ListTH1F.push_back(h_bcid_AC_woSH);
	//ListTH1F.push_back(h_bcid_AC_wSH);
	//ListTH1F.push_back(h_bcid_CA);
	//ListTH1F.push_back(h_bcid_CA_woSH);
	//ListTH1F.push_back(h_bcid_CA_wSH);
	ListTH1F.push_back(h_all);
	ListTH1F.push_back(h_woSmallHits);
	ListTH1F.push_back(h_wSmallHits);
	ListTH1F.push_back(h_wSmallHitsA);
	ListTH1F.push_back(h_noiseA);
	ListTH1F.push_back(h_noiseC);
	ListTH1F.push_back(h_ECA_beam1);
	ListTH1F.push_back(h_ratio_woSmallHits);
	ListTH1F.push_back(h_ratio_wSmallHits);
	ListTH1F.push_back(h_ratio_woSmallHits_charge);
	ListTH1F.push_back(h_ratio_wSmallHits_charge);
	ListTH1F.push_back(h_ratio_woSmallHits_cut);
	ListTH1F.push_back(h_ratio_wSmallHits_cut);
	ListTH1F.push_back(h_ratio);
	ListTH1F.push_back(h_ratiocharge_woSmallHits);
	ListTH1F.push_back(h_ratiocharge_wSmallHits);
	ListTH1F.push_back(h_nLB);

	//ListTH1F.push_back(h_allnoise);
	//ListTH1F.push_back(h_electricnoise);
	//ListTH1F.push_back(h_allnoisewSH);
	//ListTH1F.push_back(h_electricnoisewSH);
	ListTH1F.push_back(h_noiserateall);
	ListTH1F.push_back(h_noiserate);

	//ListTH1F.push_back(h_allnoiseA);
	//ListTH1F.push_back(h_electricnoiseA);
	//ListTH1F.push_back(h_allnoisewSHA);
	//ListTH1F.push_back(h_electricnoisewSHA);
	ListTH1F.push_back(h_noiserateallA);
	ListTH1F.push_back(h_noiserateA);

	//ListTH1F.push_back(h_allnoisecluster);
	//ListTH1F.push_back(h_electricnoisecluster);
	ListTH1F.push_back(h_allnoisewSHcluster);
	ListTH1F.push_back(h_electricnoisewSHcluster);
	ListTH1F.push_back(h_noiserateallcluster);
	ListTH1F.push_back(h_noiseratecluster);

	//ListTH1F.push_back(h_allnoiseAcluster);
	//ListTH1F.push_back(h_electricnoiseAcluster);
	ListTH1F.push_back(h_allnoisewSHAcluster);
	ListTH1F.push_back(h_electricnoisewSHAcluster);
	ListTH1F.push_back(h_noiserateallAcluster);
	ListTH1F.push_back(h_noiserateAcluster);

	ListTH1F.push_back(h_allLB);

        //TH2F
	//h_nHitsA_beam1 = new TH2F("nHitsA_beam1", "; Run Number; Events", 16340, 348150.5, 364490.5,5000,0,5000);
	//h_nHitsC_beam1 = new TH2F("nHitsC_beam1", "; Run Number; Events", 16340, 348150.5, 364490.5,5000,0,5000);
	//h_nHitsA_beam2 = new TH2F("nHitsA_beam2", "; Run Number; Events", 16340, 348150.5, 364490.5,5000,0,5000);
	//h_nHitsC_beam2 = new TH2F("nHitsC_beam2", "; Run Number; Events", 16340, 348150.5, 364490.5,5000,0,5000);
	//h_nHitsA_beam1_woSmallHits = new TH2F("nHitsA_beam1_woSmallHits", "; Run Number; Events", 16340, 348150.5, 364490.5,5000,0,5000);
	//h_nHitsC_beam1_woSmallHits = new TH2F("nHitsC_beam1_woSmallHits", "; Run Number; Events", 16340, 348150.5, 364490.5,5000,0,5000);
	//h_nHitsA_beam2_woSmallHits = new TH2F("nHitsA_beam2_woSmallHits", "; Run Number; Events", 16340, 348150.5, 364490.5,5000,0,5000);
	//h_nHitsC_beam2_woSmallHits = new TH2F("nHitsC_beam2_woSmallHits", "; Run Number; Events", 16340, 348150.5, 364490.5,5000,0,5000);
	//h_nHitsA_beam1_wSmallHits = new TH2F("nHitsA_beam1_wSmallHits", "; Run Number; Events", 16340, 348150.5, 364490.5,5000,0,5000);
	//h_nHitsC_beam1_wSmallHits = new TH2F("nHitsC_beam1_wSmallHits", "; Run Number; Events", 16340, 348150.5, 364490.5,5000,0,5000);
	//h_nHitsA_beam2_wSmallHits = new TH2F("nHitsA_beam2_wSmallHits", "; Run Number; Events", 16340, 348150.5, 364490.5,5000,0,5000);
	//h_nHitsC_beam2_wSmallHits = new TH2F("nHitsC_beam2_wSmallHits", "; Run Number; Events", 16340, 348150.5, 364490.5,5000,0,5000);
	//h_zasym_AC = new TH2F("zasym_AC", "; Run Number; Events", 16340, 348150.5, 364490.5,100,-1,1.1);
	//h_zasym_CA = new TH2F("zasym_CA", "; Run Number; Events", 16340, 348150.5, 364490.5,100,-1,1.1);
	//h_zasym_AC_woSmallHits = new TH2F("zasym_AC_woSmallHits", "; Run Number; Events", 16340, 348150.5, 364490.5,100,-1,1.1);
	//h_zasym_CA_woSmallHits = new TH2F("zasym_CA_woSmallHits", "; Run Number; Events", 16340, 348150.5, 364490.5,100,-1,1.1);
	//h_zasym_AC_wSmallHits = new TH2F("zasym_AC_wSmallHits", "; Run Number; Events", 16340, 348150.5, 364490.5,100,-1,1.1);
	//h_zasym_CA_wSmallHits = new TH2F("zasym_CA_wSmallHits", "; Run Number; Events", 16340, 348150.5, 364490.5,100,-1,1.1);
	h_noiseA2D = new TH2F("noiseA2D", "; Run Number; Events", 16340, 348150.5, 364490.5,300,0,300);
	h_noiseC2D = new TH2F("noiseC2D", "; Run Number; Events", 16340, 348150.5, 364490.5,300,0,300);
	h_noiseA2DRDO = new TH2F("noiseA2DRDO", "; Run Number; Events", 16340, 348150.5, 364490.5,300,0,300);
	h_noiseC2DRDO = new TH2F("noiseC2DRDO", "; Run Number; Events", 16340, 348150.5, 364490.5,300,0,300);

	//ListTH2F.push_back(h_nHitsA_beam1);
	//ListTH2F.push_back(h_nHitsC_beam1);
	//ListTH2F.push_back(h_nHitsA_beam2);
	//ListTH2F.push_back(h_nHitsC_beam2);
	//ListTH2F.push_back(h_nHitsA_beam1_woSmallHits);
	//ListTH2F.push_back(h_nHitsC_beam1_woSmallHits);
	//ListTH2F.push_back(h_nHitsA_beam2_woSmallHits);
	//ListTH2F.push_back(h_nHitsC_beam2_woSmallHits);
	//ListTH2F.push_back(h_nHitsA_beam1_wSmallHits);
	//ListTH2F.push_back(h_nHitsC_beam1_wSmallHits);
	//ListTH2F.push_back(h_nHitsA_beam2_wSmallHits);
	//ListTH2F.push_back(h_nHitsC_beam2_wSmallHits);
	//ListTH2F.push_back(h_zasym_AC);
	//ListTH2F.push_back(h_zasym_CA);
	//ListTH2F.push_back(h_zasym_AC_woSmallHits);
	//ListTH2F.push_back(h_zasym_CA_woSmallHits);
	//ListTH2F.push_back(h_zasym_AC_wSmallHits);
	//ListTH2F.push_back(h_zasym_CA_wSmallHits);
	ListTH2F.push_back(h_noiseA2D);
	ListTH2F.push_back(h_noiseC2D);
	ListTH2F.push_back(h_noiseA2DRDO);
	ListTH2F.push_back(h_noiseC2DRDO);

	//for output
	cout << "outputfile_:" << outputfile_ << endl;
	outputFile = new TFile(outputfile_.c_str(), "RECREATE");


}

Bool_t MySelector_pixel::Process(Long64_t entry)
{
	// The Process() function is called for each entry in the tree (or possibly
	// keyed object in the case of PROOF) to be processed. The entry argument
	// specifies which entry in the currently loaded tree is to be processed.
	// When processing keyed objects with PROOF, the object is already loaded
	// and is available via the fObject pointer.
	//
	// This function should contain the \"body\" of the analysis. It can contain
	// simple or elaborate selection criteria, run algorithms on the data
	// of the event and typically fill histograms.
	//
	// The processing can be stopped by calling Abort().
	//
	// Use fStatus to set the return value of TTree::Process().
	//
	// The return value is currently not used.

	fReader.SetEntry(entry);
	h_events->Fill(*fRunNumber);
	h_nLB->Fill(*fLBNumber);
	h_allLB->Fill(*fRunNumber,h_nLB->GetNbinsX());

	//std::string LB_number = std::to_string(*fLBNumber); // Lumi block number
	//char const *char_LB_number = LB_number.c_str();

	//// Get the number of good lumi blocks from rootrc file assigned in 'setting' to a variable 'char_run_number', 1 is the default value.
	//int NLB = settings->GetValue(char_run_number, 1);
	//double perSec = (double) NLB*60; // duration in seconds of the run
	//double weight = (double)1/perSec; // when normalize to the Lumi blocks; weight is a inverse of the duration to get the average event rate
	//double min = 60; // min = 60 seconds
	//double perLB = (double)1/min; // when normalize to 60 seconds

	double zasym = 1000;
        double pA = 1000;
        double pC = 1000;
        
        int bcid = *fbcid;
	//h_bcid->Fill(bcid);
        int hitA = 0;
        int hitC = 0;
        hitA = *fHitsPixelECA;
	hitC = *fHitsPixelECC;
	int hitsECA = 0; //pixelhits
	int hitsECC = 0; //pixelhits
	int hitscharge = 0;
	int hitschargeA = 0;
	int hitschargeC = 0;
	int noisechargeA = 0;
	int noisechargeC = 0;
	int clusterchargeA = 0;
	int clusterchargeC = 0;
        double ratio = 1000;
        double ratiocharge = 1000;

	if (*fwithPrimaryVertex == false) { //pass events with PV

		for(int i = 0;i<*fPixelHits;i++){ //pixel cluster loop
			if(abs(fpbecV[i]) == 2){
				if(fpbecV[i] == 2 ) { //ECA
					hitsECA += fpnRDOV[i];    
					if(fpchargeV[i] < 10000 && fpnRDOV[i] == 1) {
						hitschargeA += fpnRDOV[i]; //noise pixel
						clusterchargeA++; //noise cluster
						noisechargeA++; //electric noise cluster
					}
					if(fpchargeV[i] < 13000 && fpnRDOV[i] == 2) {
						hitschargeA += fpnRDOV[i];
						clusterchargeA++;
					}
				} //ECA
				if(fpbecV[i] == -2 ) { //ECC
					//for single pixel cluster
					hitsECC += fpnRDOV[i];    
					if(fpchargeV[i] < 10000 && fpnRDOV[i] == 1) {
						hitschargeC += fpnRDOV[i];
						clusterchargeC++;
						noisechargeC++;
					}
					if(fpchargeV[i] < 13000 && fpnRDOV[i] == 2) {
						hitschargeC += fpnRDOV[i];
						clusterchargeC++;
					}
				} //ECC
			}

			if(*fpassesACTrigger == true) { // BCMAC
				if(*fTriggerISO == true){ //ISO
					if(hitC <= 50) {
						if(fpbecV[i] == 2 ) { //ECA
							if(fpchargeV[i] < 10000 && fpnRDOV[i] == 1) { //electric noise? selection
								h_electricnoisewSHAclusterAC->Fill(*fRunNumber); 
							}
						}
						if(fpbecV[i] == -2 ) { //ECC
							if(fpchargeV[i] < 10000 && fpnRDOV[i] == 1) { //electric noise? selection
								h_electricnoisewSHcluster->Fill(*fRunNumber); 
								h_allnoisewSHcluster->Fill(*fRunNumber); 
							}
							if(fpchargeV[i] < 13000 && fpnRDOV[i] == 2) { //noise? selection
								h_allnoisewSHcluster->Fill(*fRunNumber); 
							}
						}
					}
				} //ISO
			} //BCMAC
			if(*fpassesCATrigger == true) { // BCMCA
				if(*fTriggerISO == true){ //ISO
					if(hitA <= 50) {
						if(fpbecV[i] == 2 ) { //ECA
							if(fpchargeV[i] < 10000 && fpnRDOV[i] == 1) {
								h_electricnoisewSHAcluster->Fill(*fRunNumber); 
								h_allnoisewSHAcluster->Fill(*fRunNumber); 
							}
							if(fpchargeV[i] < 13000 && fpnRDOV[i] == 2) {
								h_allnoisewSHAcluster->Fill(*fRunNumber); 
							}
						}
					}
				} //ISO
			} //BCMCA

		} //end of pixelcluster loop

		if ( hitA != 0) ratio = ((double)hitsECA)/((double)hitA);
		if(*fPixelHits !=0) ratiocharge = ((double)hitscharge)/((double)*fPixelHits);
		if ((hitA+hitC) != 0) zasym = (double)( hitA - hitC )/( hitA + hitC );
		if (hitC != 0) pA = (double) hitA/hitC;
		if (hitA != 0) pC = (double) hitC/hitA;

		// selection with trigger
		if(*fpassesACTrigger == true) { // BCMAC
			if(*fTriggerISO == true){ //ISO
				h_events_AC->Fill(*fRunNumber); //eventsAC
				//h_bcid_AC->Fill(*fbcid); //bcid
				//h_nHitsA_beam1->Fill(*fRunNumber,hitA);
				h_ECA_beam1->Fill(hitsECA); 
				h_all->Fill(hitA);
				//h_nHitsC_beam1->Fill(*fRunNumber,hitC);
				if(hitA > 50) {
					//h_nHitsA_beam1_woSmallHits->Fill(*fRunNumber,hitA);
					h_woSmallHits->Fill(hitA);
					h_ratio_woSmallHits->Fill(ratio);
					h_ratiocharge_woSmallHits->Fill(ratiocharge);
				}
				if(hitC > 50) {
					//h_nHitsC_beam1_woSmallHits->Fill(*fRunNumber,hitC);
				}
				anoiseall += hitsECC;
				enoiseall += hitschargeC; //electric noise pixel
				anoiseallcluster += hitC;
				enoiseallcluster += noisechargeC; //noise cluster
				if(hitA <= 50) {
					//h_nHitsA_beam1_wSmallHits->Fill(*fRunNumber,hitA);
					h_ratio_wSmallHits->Fill(ratio);
					h_ratiocharge_wSmallHits->Fill(ratiocharge);
				}
				if(hitC <= 50) {
					anoise += hitsECC;
					enoise += hitschargeC;
					anoisecluster += hitC;
					enoisecluster += noisechargeC;
					h_wSmallHits->Fill(hitsECC);
					//h_nHitsC_beam1_wSmallHits->Fill(*fRunNumber,hitC);
					h_noiseC->Fill(noisechargeC);
					h_noiseC2D->Fill(*fRunNumber,noisechargeC); //electric noise cluster
					h_noiseC2DRDO->Fill(*fRunNumber,clusterchargeC); //noise cluster
				}

				h_events_ACwoPV->Fill(*fRunNumber);
				//h_zasym_AC->Fill(*fRunNumber,zasym);

				if(hitA>50 && hitC>50) {
					//h_zasym_AC_woSmallHits->Fill(*fRunNumber,zasym);
				}
				if(hitA<=50 && hitC<=50) {
					//h_zasym_AC_wSmallHits->Fill(*fRunNumber,zasym);
				}
			}
		}

		if(*fpassesCATrigger == true) { // BCMCA
			if(*fTriggerISO == true){ //ISO
				h_events_CA->Fill(*fRunNumber);
				//h_bcid_CA->Fill(bcid);
				//h_nHitsA_beam2->Fill(*fRunNumber,hitA);
				//h_nHitsC_beam2->Fill(*fRunNumber,hitC);
				if(hitA > 50) {
					//h_nHitsA_beam2_woSmallHits->Fill(*fRunNumber,hitA);
				}
				if(hitC > 50) {
					//h_nHitsC_beam2_woSmallHits->Fill(*fRunNumber,hitC);
				}
				anoiseallA += hitsECA;
				enoiseallA += hitschargeA;
				anoiseallAcluster += hitA;
				enoiseallAcluster += noisechargeA;
				if(hitA <= 50) {
					anoiseA += hitsECA;
					enoiseA += hitschargeA;
					anoiseAcluster += hitA;
					enoiseAcluster += noisechargeA;
					h_wSmallHitsA->Fill(hitsECA);
					//h_nHitsA_beam2_wSmallHits->Fill(*fRunNumber,hitA);
					h_noiseA->Fill(noisechargeA); //electric noise cluster
					h_noiseA2D->Fill(*fRunNumber,noisechargeA); //electric noise cluster 
					h_noiseA2DRDO->Fill(*fRunNumber,clusterchargeA); //noise cluster
				}
				//if(hitC <= 50) h_nHitsC_beam2_wSmallHits->Fill(*fRunNumber,hitC);
				h_events_CAwoPV->Fill(*fRunNumber);
				//h_zasym_CA->Fill(*fRunNumber,zasym);
				if(hitA>50 && hitC>50) {
					//h_zasym_CA_woSmallHits->Fill(*fRunNumber,zasym);
				}
				if(hitA<=50 && hitC<=50) {
					//h_zasym_CA_wSmallHits->Fill(*fRunNumber,zasym);
				}
			}
		}
	}

	return kTRUE;
}

void MySelector_pixel::SlaveTerminate()
{
	// The SlaveTerminate() function is called after all entries or objects
	// have been processed. When running with PROOF SlaveTerminate() is called
	// on each slave server.

}

void MySelector_pixel::Terminate()
{
	// The Terminate() function is the last function to be called during
	// a query. It always runs on the client, it can be used to present
	// the results graphically or save the results to file.
	if (anoiseall != 0 ) h_noiserateall->Fill(*fRunNumber,double(enoiseall)/double(anoiseall));
	if (anoise != 0 ) h_noiserate->Fill(*fRunNumber,double(enoise)/double(anoise));
	if (anoiseallA != 0 ) h_noiserateallA->Fill(*fRunNumber,double(enoiseallA)/double(anoiseallA));
	if (anoiseA != 0 ) h_noiserateA->Fill(*fRunNumber,double(enoiseA)/double(anoiseA));

	if (anoiseallcluster != 0 ) h_noiserateallcluster->Fill(*fRunNumber,double(enoiseallcluster)/double(anoiseallcluster));
	if (anoisecluster != 0 ) h_noiseratecluster->Fill(*fRunNumber,double(enoisecluster)/double(anoisecluster));
	if (anoiseallAcluster != 0 ) h_noiserateallAcluster->Fill(*fRunNumber,double(enoiseallAcluster)/double(anoiseallAcluster));
	if (anoiseAcluster != 0 ) h_noiserateAcluster->Fill(*fRunNumber,double(enoiseAcluster)/double(anoiseAcluster));

	for ( TH1F* th1f : ListTH1F) th1f->Write();
	for ( TH2F* th2f : ListTH2F) th2f->Write();
	outputFile->Close();
}



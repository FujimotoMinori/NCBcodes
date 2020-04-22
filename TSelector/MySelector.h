//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Mar 23 13:46:05 2017 by ROOT version 6.04/16
// from TTree tree/tree
// found on file: sample.root
//////////////////////////////////////////////////////////

#ifndef MySelector_h
#define MySelector_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>

#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>

// Header file for the classes stored in the TTree if any.
#include "vector"

#include "TH2F.h"

#include "TSystem.h"
#include "TEnv.h"
#include <fstream>
class MySelector : public TSelector {
private:
   std::string outputfile_;

public :
   TFile *outputFile = 0;
   ofstream myfile;
   ofstream myfile2;
   ofstream fileACPrescale;
   ofstream fileCAPrescale;

   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
 
   // Setting up TEnvironment to get values corresponding to a run number.
   TEnv 	  *settings;
   TEnv		  *time_settings;
   TEnv		  *BIB_settings_AC;
   TEnv 	  *BIB_settings_CA;
   TEnv 	  *peaklumi_304337;
   TEnv		  *HLT_settings;
// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           EventNumber;
   Int_t           RunNumber;
   Int_t 	   timeStamp;
   Int_t           LBNumber;
   Int_t           bcid;
   Bool_t          passesACTrigger;
   Bool_t          passesCATrigger;
   vector<int>     *HitsOnDisks;
   Float_t	   BCMACprescale;
   Float_t	   BCMCAprescale;
   Bool_t	   passesHLT;
   Float_t 	   HLTprescale;
   
   Int_t 	  fNumberOfEvents; // Total number of events
   //Int_t	  fTotalDataSize; // Sum of data size (in bytes) of all events

   TTreeReader fReader;
   //TTreeReaderValue<Int_t> fCurrentEventSize; // Size of the current event


   // List of branches
   TBranch        *b_EventNumber;   //!
   TBranch        *b_RunNumber;   //!
   TBranch	  *b_timeStamp; //!
   TBranch        *b_LBNumber;   //!
   TBranch        *b_bcid;   //!
   TBranch        *b_passesACTrigger;   //!
   TBranch        *b_passesCATrigger;   //!
   TBranch        *b_HitsOnDisks;   //!
   TBranch	  *b_BCMACprescale; //!
   TBranch	  *b_BCMCAprescale; //!
   TBranch	  *b_passesHLT; //!
   TBranch	  *b_HLTprescale; //!

   // Readers to access the data: This is to read the variable in the private ntuple in MySelector.C file.
   TTreeReaderValue<Int_t> fEventNumber = {fReader, "EventNumber"};
   TTreeReaderValue<Int_t> fRunNumber = {fReader, "RunNumber"};
   TTreeReaderValue<Int_t> ftimeStamp = {fReader, "timeStamp"};
   TTreeReaderValue<Int_t> fLBNumber = {fReader, "LBNumber"};
   TTreeReaderValue<Int_t> fbcid = {fReader, "bcid"};
   TTreeReaderValue<Bool_t> fpassesACTrigger = {fReader, "passesACTrigger"};
   TTreeReaderValue<Bool_t> fpassesCATrigger = {fReader, "passesCATrigger"};
   TTreeReaderValue<std::vector<int>> fHitsOnDisks = {fReader, "HitsOnDisks"};
   TTreeReaderValue<std::vector<int>> fHitsOnModulesOfDisk6 = {fReader, "HitsOnModulesOfDisk6"};
   TTreeReaderValue<Float_t> fBCMACprescale = {fReader, "BCMACprescale"};
   TTreeReaderValue<Float_t> fBCMCAprescale = {fReader, "BCMCAprescale"};
   TTreeReaderValue<Bool_t> fpassesHLT = {fReader, "passesHLT"};
   TTreeReaderValue<Float_t> fHLTprescale = {fReader, "HLTprescale"};

   MySelector(TTree * /*tree*/ =0) : 
 	fNumberOfEvents(0),
	fChain(0) { }

   virtual ~MySelector() { }

   virtual Int_t   Version() const { return 2; }
   virtual void    Begin(TTree *tree);
   virtual void    SlaveBegin(TTree *tree);
   virtual void    Init(TTree *tree);
   virtual Bool_t  Notify();
   virtual Bool_t  Process(Long64_t entry);
   virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
   virtual void    SetOption(const char *option) { fOption = option; }
   virtual void    SetObject(TObject *obj) { fObject = obj; }
   virtual void    SetInputList(TList *input) { fInput = input; }
   virtual TList  *GetOutputList() const { return fOutput; }
   virtual void    SlaveTerminate();
   virtual void    Terminate();

   // Histograms
   std::vector<TH2F*> ListTH2F;
   std::vector<TH1F*> ListTH1F;

   TH2F * h_ACtrigger;
   TH2F * h_CAtrigger;
   TH2F * h_ECAHit78_beam2;
   TH2F * h_ECCHit78_beam2;
   TH2F * h_ECAHit78_beam1;
   TH2F * h_ECCHit78_beam1;
   TH2F * h_z_asym_beam1;
   TH2F * h_z_asym_beam2;
   TH2F * h_run_vs_timestamp;
   TH2F * h_pressure_bump_run_2;
  
   TH2F * h_z_asym_beam1_299147;
   TH2F * h_z_asym_beam2_299147;
   TH2F * h_z_asym_beam1_304337;
   TH2F * h_z_asym_beam2_304337;

   TH2F * h_ECCHit78_beam1_301918;
   TH2F * h_ECAHit78_beam2_301918;
   TH2F * h_ECCHit78_beam1_309314;
   TH2F * h_ECAHit78_beam2_309314;
 
   TH2F * h_ECCHit78_beam1_302737;
   TH2F * h_ECAHit78_beam2_302737;
   TH2F * h_ECCHit78_beam1_304494;
   TH2F * h_ECAHit78_beam2_304494;
   TH2F * h_ECCHit78_beam1_298771;
   TH2F * h_ECAHit78_beam2_298771;
   TH2F * h_ECCHit78_beam1_299147;
   TH2F * h_ECAHit78_beam2_299147;
   TH2F * h_ECCHit78_beam1_304337;
   TH2F * h_ECAHit78_beam2_304337;
   TH2F * h_ECCHit78_beam1_300687;
   TH2F * h_ECAHit78_beam2_300687;
   TH2F * h_BIB_ECAHit78_beam2;
   TH2F * h_BIB_ECCHit78_beam1;
   TH2F * h_BIB_ECAHit78_beam2_309314;
   TH2F * h_BIB_ECCHit78_beam1_309314;

   TH2F * h_ECCHit78_beam2_299147;
   TH2F * h_ECAHit78_beam1_299147;
   TH2F * h_ECCHit78_beam2_304337;
   TH2F * h_ECAHit78_beam1_304337;

   //upstream
   TH2F * h_ECCHit78_beam1_302829;
   TH2F * h_ECAHit78_beam2_302829;
   TH2F * h_ECCHit78_beam1_302831;
   TH2F * h_ECAHit78_beam2_302831;
   TH2F * h_ECCHit78_beam1_307195;
   TH2F * h_ECAHit78_beam2_307195;
   TH2F * h_ECCHit78_beam1_310738;
   TH2F * h_ECAHit78_beam2_310738;

   //downstream
   TH2F * h_ECCHit78_beam2_302829;
   TH2F * h_ECAHit78_beam1_302829;
   TH2F * h_ECCHit78_beam2_302831;
   TH2F * h_ECAHit78_beam1_302831;
   TH2F * h_ECAHit78_beam1_307195;
   TH2F * h_ECCHit78_beam2_307195;
   TH2F * h_ECAHit78_beam1_310738;
   TH2F * h_ECCHit78_beam2_310738;
  
   
   TH2F * h_bcid_vs_lb_AC_302737;
   TH2F * h_bcid_vs_lb_CA_302737;
   TH2F * h_bcid_vs_lb_HLTbeam1Like_302737;
   TH2F * h_bcid_vs_lb_HLTbeam2Like_302737;


   TH2F * h_ECCHit78_beam1_15min;
   TH2F * h_ECAHit78_beam1_15min;
   TH2F * h_ECCHit78_beam2_15min;
   TH2F * h_ECAHit78_beam2_15min;

   TH2F * h_lumi_ECCHit78_beam1_304337;
   TH2F * h_BIB_ECCHit78_beam1_304337;
   TH2F * h_ECAHit78_HLT_beam2Like;
   TH2F * h_ECCHit78_HLT_beam1Like;
   TH2F * h_ECAHit78_HLT_upstream;
   TH2F * h_ECCHit78_HLT_upstream;

   TH2F * outer_module_ECCdisk6_hit_vs_run;
   TH2F * outer_module_ECAdisk6_hit_vs_run;
   TH2F * middle_module_ECCdisk6_hit_vs_run;
   TH2F * middle_module_ECAdisk6_hit_vs_run;
   TH2F * inner_module_ECCdisk6_hit_vs_run;
   TH2F * inner_module_ECAdisk6_hit_vs_run;

   TH2F * outer_module_ECCdisk6_hit_vs_run_beam1;
   TH2F * outer_module_ECAdisk6_hit_vs_run_beam1;
   TH2F * middle_module_ECCdisk6_hit_vs_run_beam1;
   TH2F * middle_module_ECAdisk6_hit_vs_run_beam1;
   TH2F * inner_module_ECCdisk6_hit_vs_run_beam1;
   TH2F * inner_module_ECAdisk6_hit_vs_run_beam1;

   TH2F * outer_module_ECCdisk6_hit_vs_run_beam2;
   TH2F * outer_module_ECAdisk6_hit_vs_run_beam2;
   TH2F * middle_module_ECCdisk6_hit_vs_run_beam2;
   TH2F * middle_module_ECAdisk6_hit_vs_run_beam2;
   TH2F * inner_module_ECCdisk6_hit_vs_run_beam2;
   TH2F * inner_module_ECAdisk6_hit_vs_run_beam2;

   TH2F * outer_module_ECCdisk6_hit_vs_run_beam1Like;
   TH2F * outer_module_ECAdisk6_hit_vs_run_beam1Like;
   TH2F * middle_module_ECCdisk6_hit_vs_run_beam1Like;
   TH2F * middle_module_ECAdisk6_hit_vs_run_beam1Like;
   TH2F * inner_module_ECCdisk6_hit_vs_run_beam1Like;
   TH2F * inner_module_ECAdisk6_hit_vs_run_beam1Like;

   TH2F * outer_module_ECCdisk6_hit_vs_run_beam2Like;
   TH2F * outer_module_ECAdisk6_hit_vs_run_beam2Like;
   TH2F * middle_module_ECCdisk6_hit_vs_run_beam2Like;
   TH2F * middle_module_ECAdisk6_hit_vs_run_beam2Like;
   TH2F * inner_module_ECCdisk6_hit_vs_run_beam2Like;
   TH2F * inner_module_ECAdisk6_hit_vs_run_beam2Like;


   TH2F * h_ECAHit78_HLT;
   TH2F * h_ECCHit78_HLT;
   TH2F * h_HLTbeam1Like_z_asym_302737;
   TH2F * h_HLTbeam2Like_z_asym_302737;
   TH2F * h_HLT_z_asym_302737;
   TH2F * h_HLTbeam1Like_hit_302737;
   TH2F * h_HLTbeam2Like_hit_302737;
   TH2F * h_HLT_hit_302737;
   TH2F * h_BCMtrigger_z_asym_302737;
   TH2F * h_ACtrigger_z_asym_302737;
   TH2F * h_CAtrigger_z_asym_302737;  
   TH2F * h_HLT_z_asym_304337;
   TH2F * h_HLT_hit_304337;

   TH2F * h_HLT_z_asym;
   TH2F * h_bcid_vs_lb_HLT_302737;
   TH2F * h_hit_vs_disks;

   TH2F * h_HLT_z_asym_298771;
   TH2F * h_HLT_hit_298771;
   TH2F * h_bcid_vs_lb_HLT_298771;
   TH2F * h_bcid_vs_pv_HLT_307195;
   TH2F * h_bcid_vs_nv_HLT_307195;
   TH2F * h_lb_vs_HitECC78_beam1Like_307195;
   TH2F * h_lb_vs_HitECA78_beam2Like_307195;

   TH2F * h_bcid_vs_pv_HLT_309314;
   TH2F * h_bcid_vs_nv_HLT_309314;
   TH2F * h_lb_vs_HitECC78_beam1Like_309314;
   TH2F * h_lb_vs_HitECA78_beam2Like_309314;
  
   TH2F * h_bcid_vs_pv_HLT_302737;
   TH2F * h_bcid_vs_nv_HLT_302737;
   TH2F * h_bcid_vs_pv_HLT_302737_zlarger05;
   TH2F * h_bcid_vs_nv_HLT_302737_zlarger05;

   TH2F * h_bcid_vs_pv_HLT_302737_zsmaller05;
   TH2F * h_bcid_vs_nv_HLT_302737_zsmaller05;



   TH2F * h_bcid_vs_pv_HLT_302737_disk1;
   TH2F * h_bcid_vs_pv_HLT_302737_disk2;
   TH2F * h_bcid_vs_pv_HLT_302737_disk3;
   TH2F * h_bcid_vs_pv_HLT_302737_disk4;
   TH2F * h_bcid_vs_pv_HLT_302737_disk5;
   TH2F * h_bcid_vs_pv_HLT_302737_disk6;
   TH2F * h_bcid_vs_pv_HLT_302737_disk9;

	
   TH2F * h_bcid_vs_nv_HLT_302737_disk1;
   TH2F * h_bcid_vs_nv_HLT_302737_disk2;
   TH2F * h_bcid_vs_nv_HLT_302737_disk3;
   TH2F * h_bcid_vs_nv_HLT_302737_disk4;
   TH2F * h_bcid_vs_nv_HLT_302737_disk5;
   TH2F * h_bcid_vs_nv_HLT_302737_disk6;
   TH2F * h_bcid_vs_nv_HLT_302737_disk9;

   TH2F * h_bcid_pv_HLT_302737_disk1_largez;
   TH2F * h_bcid_pv_HLT_302737_disk2_largez;
   TH2F * h_bcid_pv_HLT_302737_disk3_largez;
   TH2F * h_bcid_pv_HLT_302737_disk4_largez;
   TH2F * h_bcid_pv_HLT_302737_disk5_largez;
   TH2F * h_bcid_pv_HLT_302737_disk6_largez;
   TH2F * h_bcid_pv_HLT_302737_disk9_largez;

   TH2F * h_bcid_nv_HLT_302737_disk1_largez;
   TH2F * h_bcid_nv_HLT_302737_disk2_largez;
   TH2F * h_bcid_nv_HLT_302737_disk3_largez;
   TH2F * h_bcid_nv_HLT_302737_disk4_largez;
   TH2F * h_bcid_nv_HLT_302737_disk5_largez;
   TH2F * h_bcid_nv_HLT_302737_disk6_largez;
   TH2F * h_bcid_nv_HLT_302737_disk9_largez;


   TH2F * h_bcid_vs_hit_HLT_302737;

   TH1F * h_all_events;
   TH1F * h_triggered_events;
   TH1F * h_ACtriggered_events;
   TH1F * h_CAtriggered_events;
   TH1F * h_ACtriggered_events_15min;
   TH1F * h_CAtriggered_events_15min;
   TH1F * h_ACselected_events_15min;
   TH1F * h_CAselected_events_15min;
   TH1F * h_BIB_CAselected_events_15min;
   TH1F * h_BIB_ACselected_events_15min;
   TH1F * h_ACselected_events;
   TH1F * h_CAselected_events;
   TH1F * h_ACselected_events_299147;
   TH1F * h_CAselected_events_299147;
   TH1F * h_ACselected_events_304337;
   TH1F * h_CAselected_events_304337; 

   TH1F * h_ACselected_events_12;
   TH1F * h_CAselected_events_12;
   TH1F * h_PVselected_events;
   TH1F * h_NVselected_events;
   TH1F * h_AC_seconds;
   TH1F * h_CA_seconds;
   TH1F * h_ACtriggered_events_301918;
   TH1F * h_CAtriggered_events_301918;
   TH1F * h_ACtriggered_events_309314;
   TH1F * h_CAtriggered_events_309314;
   
   TH1F * h_ACtriggered_events_302737;
   TH1F * h_CAtriggered_events_302737;
   TH1F * h_ACtriggered_events_304494;
   TH1F * h_CAtriggered_events_304494;
   TH1F * h_ACtriggered_events_298771;
   TH1F * h_CAtriggered_events_298771;
   TH1F * h_ACtriggered_events_304337;
   TH1F * h_CAtriggered_events_304337;
   TH1F * h_ACtriggered_events_299147;
   TH1F * h_CAtriggered_events_299147;
   TH1F * h_ACtriggered_events_300687;
   TH1F * h_CAtriggered_events_300687;
   TH1F * h_z_asym_only_pvs;
   TH1F * h_z_asym_wo_pvs;
   TH1F * h_z_asym_12;
   TH1F * h_z_asym_only_pvs_12;
   TH1F * h_BIB_ACselected_events;
   TH1F * h_BIB_CAselected_events;
   TH1F * h_BIB_ACselected_events_309314;
   TH1F * h_BIB_CAselected_events_309314;
 
   TH1F * h_HLT_events; 
   TH1F * h_HLT_beam1Like_events;
   TH1F * h_HLT_beam2Like_events;
   TH1F * h_HLT_beam1Like_events_15min;
   TH1F * h_HLT_beam2Like_events_15min;
 
   TH1F * h_HLT_and_AC;
   TH1F * h_HLT_and_CA;

   TH1F * h_HLTbeam1Like_triggered_events_302737;
   TH1F * h_HLTbeam2Like_triggered_events_302737;

   ClassDef(MySelector,0);
};

#endif

#ifdef MySelector_cxx
void MySelector::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

  // Associate the TTreeReader with the tree we want to read
   fReader.SetTree(tree);


   // Set object pointer
   HitsOnDisks = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("EventNumber", &EventNumber, &b_EventNumber);
   fChain->SetBranchAddress("RunNumber", &RunNumber, &b_RunNumber);
   fChain->SetBranchAddress("timeStamp", &timeStamp, &b_timeStamp);
   fChain->SetBranchAddress("LBNumber", &LBNumber, &b_LBNumber);
   fChain->SetBranchAddress("bcid", &bcid, &b_bcid);
   fChain->SetBranchAddress("passesACTrigger", &passesACTrigger, &b_passesACTrigger);
   fChain->SetBranchAddress("passesCATrigger", &passesCATrigger, &b_passesCATrigger);
   fChain->SetBranchAddress("HitsOnDisks", &HitsOnDisks, &b_HitsOnDisks);
   fChain->SetBranchAddress("BCMACprescale", &BCMACprescale, &b_BCMACprescale);
   fChain->SetBranchAddress("BCMCAprescale", &BCMCAprescale, &b_BCMCAprescale);
}

Bool_t MySelector::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

#endif // #ifdef MySelector_cxx

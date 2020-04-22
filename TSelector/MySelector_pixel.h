//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sat May 11 11:07:23 2019 by ROOT version 6.16/00
// from TTree tree/tree
// found on file: /eos/atlas/unpledged/group-tokyo/users/mfujimot/NCB/condorDir/output30run.root
//////////////////////////////////////////////////////////

#ifndef MySelector_pixel_h
#define MySelector_pixel_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>

// Headers needed by this particular selector
#include <vector>



class MySelector_pixel : public TSelector {
private:
   std::string outputfile_;
public :
   TFile *outputFile = 0;
   TTreeReader     fReader;  //!the tree reader
   TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain

   // Readers to access the data (delete the ones you do not need).
   TTreeReaderValue<Int_t> fEventNumber = {fReader, "EventNumber"};
   TTreeReaderValue<Int_t> fRunNumber = {fReader, "RunNumber"};
   TTreeReaderValue<Int_t> ftimeStamp = {fReader, "timeStamp"};
   TTreeReaderValue<Int_t> fLBNumber = {fReader, "LBNumber"};
   TTreeReaderValue<Int_t> fbcid = {fReader, "bcid"};
   TTreeReaderValue<Int_t> fpvs = {fReader, "pvs"};
   TTreeReaderValue<Bool_t> fpassesACTrigger = {fReader, "passesACTrigger"};
   TTreeReaderValue<Bool_t> fpassesCATrigger = {fReader, "passesCATrigger"};
   TTreeReaderArray<int> fHitsOnDisks = {fReader, "HitsOnDisks"};
   TTreeReaderArray<int> fsideDiskA = {fReader, "sideDiskA"};
   TTreeReaderArray<int> fsideDiskC = {fReader, "sideDiskC"};
   TTreeReaderValue<Float_t> fBCMprescale = {fReader, "BCMprescale"};
   TTreeReaderValue<Bool_t> fTriggerISO = {fReader, "TriggerISO"};
   TTreeReaderValue<Bool_t> fTriggerEmpty = {fReader, "TriggerEmpty"};
   TTreeReaderValue<Bool_t> fGoodLB = {fReader, "GoodLB"};
   TTreeReaderValue<Bool_t> fpassesHLT = {fReader, "passesHLT"};
   TTreeReaderValue<Float_t> fHLTprescale = {fReader, "HLTprescale"};
   TTreeReaderValue<Int_t> fPixelHits = {fReader, "PixelHits"};
   TTreeReaderValue<Int_t> fHitsPixelECA = {fReader, "HitsPixelECA"};
   TTreeReaderValue<Int_t> fHitsPixelECC = {fReader, "HitsPixelECC"};
   TTreeReaderValue<Int_t> fHitsTRTECA = {fReader, "HitsTRTECA"};
   TTreeReaderValue<Int_t> fHitsTRTECC = {fReader, "HitsTRTECC"};
   TTreeReaderValue<Float_t> fZAsymmetryTRT = {fReader, "ZAsymmetryTRT"};
   TTreeReaderValue<Bool_t> fwithPrimaryVertex = {fReader, "withPrimaryVertex"};
   TTreeReaderArray<int> fpbecV = {fReader, "pbecV"};
   TTreeReaderArray<int> fplayerV = {fReader, "playerV"};
   TTreeReaderArray<int> fpphiV = {fReader, "pphiV"};
   TTreeReaderArray<float> fpchargeV = {fReader, "pchargeV"};
   TTreeReaderArray<int> fpnRDOV = {fReader, "pnRDOV"};
   TTreeReaderValue<Float_t> fZAsymmetryPixel = {fReader, "ZAsymmetryPixel"};


   MySelector_pixel(TTree * /*tree*/ =0) { 
	   //fNumberOfEvents(0),
		   //fChain(0) { }

   }

   virtual ~MySelector_pixel() { }
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

   TH1F* h_events;
   TH1F* h_events_AC;
   TH1F* h_events_CA;
   TH1F* h_events_double;
   TH1F* h_events_ACwoPV;
   TH1F* h_events_CAwoPV;
   TH1F* h_ratioAC;
   TH1F* h_ratioCA;
   //TH1F* h_bcid;
   //TH1F* h_bcid_double;
   //TH1F* h_bcid_AC;
   //TH1F* h_bcid_AC_woSH;
   //TH1F* h_bcid_AC_wSH;
   //TH1F* h_bcid_CA;
   //TH1F* h_bcid_CA_woSH;
   //TH1F* h_bcid_CA_wSH;
   //for single pixel cluster
   TH1F* h_all;
   TH1F* h_woSmallHits;
   TH1F* h_wSmallHits;
   TH1F* h_wSmallHitsA;
   TH1F* h_noiseA;
   TH1F* h_noiseC;
   TH1F* h_cut;
   TH1F* h_ECA_beam1;
   TH1F* h_ratio_woSmallHits;
   TH1F* h_ratio_wSmallHits;
   TH1F* h_ratio_woSmallHits_charge;
   TH1F* h_ratio_wSmallHits_charge;
   TH1F* h_ratio_woSmallHits_cut;
   TH1F* h_ratio_wSmallHits_cut;
   TH1F* h_ratio;
   TH1F* h_ratiocharge_woSmallHits;
   TH1F* h_ratiocharge_wSmallHits;
   TH1F* h_nLB;

   //TH1F* h_allnoise;
   //TH1F* h_electricnoise;
   //TH1F* h_allnoisewSH;
   //TH1F* h_electricnoisewSH;
   TH1F* h_noiserateall;
   TH1F* h_noiserate;

   //TH1F* h_allnoiseA;
   //TH1F* h_electricnoiseA;
   //TH1F* h_allnoisewSHA;
   //TH1F* h_electricnoisewSHA;
   TH1F* h_noiserateallA;
   TH1F* h_noiserateA;

   //TH1F* h_allnoisecluster;
   //TH1F* h_electricnoisecluster;
   TH1F* h_allnoisewSHcluster;
   TH1F* h_electricnoisewSHcluster;
   TH1F* h_noiserateallcluster;
   TH1F* h_noiseratecluster;

   //TH1F* h_allnoiseAcluster;
   //TH1F* h_electricnoiseAcluster;
   TH1F* h_allnoisewSHAcluster;
   TH1F* h_electricnoisewSHAcluster;
   TH1F* h_noiserateallAcluster;
   TH1F* h_noiserateAcluster;

   TH1F* h_allLB;

   //TH2F* h_nHitsA_beam1;
   //TH2F* h_nHitsC_beam1;
   //TH2F* h_nHitsA_beam2;
   //TH2F* h_nHitsC_beam2;
   //TH2F* h_nHitsA_beam1_woSmallHits;
   //TH2F* h_nHitsC_beam1_woSmallHits;
   //TH2F* h_nHitsA_beam2_woSmallHits;
   //TH2F* h_nHitsC_beam2_woSmallHits;
   //TH2F* h_nHitsA_beam1_wSmallHits;
   //TH2F* h_nHitsC_beam1_wSmallHits;
   //TH2F* h_nHitsA_beam2_wSmallHits;
   //TH2F* h_nHitsC_beam2_wSmallHits;
   //TH2F* h_zasym_AC;
   //TH2F* h_zasym_CA;
   //TH2F* h_zasym_AC_woSmallHits;
   //TH2F* h_zasym_CA_woSmallHits;
   //TH2F* h_zasym_AC_wSmallHits;
   //TH2F* h_zasym_CA_wSmallHits;
   TH2F* h_noiseA2D;
   TH2F* h_noiseC2D;
   TH2F* h_noiseA2DRDO;
   TH2F* h_noiseC2DRDO;

   int enoise = 0;
   int anoise = 0;
   int enoiseall = 0;
   int anoiseall = 0;
   int enoiseA = 0;
   int anoiseA = 0;
   int enoiseallA = 0;
   int anoiseallA = 0;

   int enoisecluster = 0;
   int anoisecluster = 0;
   int enoiseallcluster = 0;
   int anoiseallcluster = 0;
   int enoiseAcluster = 0;
   int anoiseAcluster = 0;
   int enoiseallAcluster = 0;
   int anoiseallAcluster = 0;

   ClassDef(MySelector_pixel,0);

};

#endif

#ifdef MySelector_pixel_cxx
void MySelector_pixel::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the reader is initialized.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   fReader.SetTree(tree);
   // Set object pointer
   //HitsOnDisks = 0;
   // Set branch addresses and branch pointers
   //if (!tree) return;
   //fChain = tree;
   //fChain->SetMakeClass(1);

   //fChain->SetBranchAddress("EventNumber", &EventNumber, &b_EventNumber);
   //fChain->SetBranchAddress("RunNumber", &RunNumber, &b_RunNumber);
   //fChain->SetBranchAddress("timeStamp", &timeStamp, &b_timeStamp);
   //fChain->SetBranchAddress("LBNumber", &LBNumber, &b_LBNumber);
   //fChain->SetBranchAddress("bcid", &bcid, &b_bcid);
   //fChain->SetBranchAddress("passesACTrigger", &passesACTrigger, &b_passesACTrigger);
   //fChain->SetBranchAddress("passesCATrigger", &passesCATrigger, &b_passesCATrigger);
   //fChain->SetBranchAddress("HitsOnDisks", &HitsOnDisks, &b_HitsOnDisks);
   //fChain->SetBranchAddress("BCMACprescale", &BCMACprescale, &b_BCMACprescale);
   //fChain->SetBranchAddress("BCMCAprescale", &BCMCAprescale, &b_BCMCAprescale);
   //fChain->SetBranchAddress("withPrimaryVertex", &withPrimaryVertex, &b_withPrimaryVertex);
   //fChain->SetBranchAddress("PixelHitsOnDisksA", &PixelHitsOnDisksA, &b_PixelHitsOnDisksA);
   //fChain->SetBranchAddress("PixelHitsOnDisksC", &PixelHitsOnDisksC, &b_PixelHitsOnDisksC);

}

Bool_t MySelector_pixel::Notify()
{
	// The Notify() function is called when a new file is opened. This
	// can be either for a new TTree in a TChain or when when a new TTree
	// is started when using PROOF. It is normally not necessary to make changes
	// to the generated code, but the routine can be extended by the
	// user if needed. The return value is currently not used.

	return kTRUE;
}


#endif // #ifdef MySelector_pixel_cxx


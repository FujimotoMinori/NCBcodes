#define MySelector_cxx
// The class definition in MySelector.h has been generated automatically
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
// root> T->Process("MySelector.C")
// root> T->Process("MySelector.C","some options")
// root> T->Process("MySelector.C+")
//

#include "MySelector.h"
#include <TH2.h>
#include <TStyle.h>
#include "TGaxis.h"
#include "TGraph.h"
#include "/nfs/dust/atlas/user/jeongj/atlas_Style/AtlasStyle.C"
#include "/nfs/dust/atlas/user/jeongj/atlas_Style/AtlasLabels.C"
#include "/nfs/dust/atlas/user/jeongj/atlas_Style/AtlasUtils.C"

void MySelector::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();
//   fNumberOfEvents = 0;

   std::string config = "grl_NLB.rootrc";
   config = gSystem->ExpandPathName(config.c_str());
   settings = new TEnv(config.c_str());
   std::cout << "bcid config is setted up: " << settings->GetRcName() << std::endl;

   //std::string time_config = "extract_timestamp.rootrc";
   std::string time_config = "run_vs_timestamp_inclusive_BCM.rootrc";
   time_config = gSystem->ExpandPathName(time_config.c_str());
   time_settings = new TEnv(time_config.c_str());
   std::cout << "time config is setted up: " << time_settings->GetRcName() << std::endl;

   //std::string HLT_timestamp_config = "HLTtimeStamp.rootrc";
   std::string HLT_timestamp_config = "run_vs_timestamp_inclusive_HLT.rootrc";
   HLT_timestamp_config = gSystem->ExpandPathName(HLT_timestamp_config.c_str());
   HLT_settings = new TEnv(HLT_timestamp_config.c_str());
   std::cout << "HLT timestamp config is setted up: " << HLT_settings->GetRcName() << std::endl;

   //std::string BIB_config_AC = "run_vs_timestamp_endof2016_AC.rootrc";
   std::string BIB_config_AC = "run_vs_timestamp_endof2016_AC_working.rootrc";
   BIB_config_AC = gSystem->ExpandPathName(BIB_config_AC.c_str());
   BIB_settings_AC = new TEnv(BIB_config_AC.c_str());
   std::cout << "2016 AC config is setted up: " << BIB_settings_AC->GetRcName() << std::endl;

   //std::string BIB_config_CA = "run_vs_timestamp_endof2016_CA.rootrc";
   std::string BIB_config_CA = "run_vs_timestamp_endof2016_CA_working.rootrc";
   BIB_config_CA = gSystem->ExpandPathName(BIB_config_CA.c_str());
   BIB_settings_CA = new TEnv(BIB_config_CA.c_str());
   std::cout << "2016 CA config is setted up: " << BIB_settings_CA->GetRcName() << std::endl;

   std::string lumi_304337 = "peaklumiplb_run304337.rootrc";
   lumi_304337 = gSystem->ExpandPathName(lumi_304337.c_str());
   peaklumi_304337 = new TEnv(lumi_304337.c_str());
   std::cout << "lumi_304337 is setted up: " << peaklumi_304337->GetRcName() << std::endl;

   outputfile_ = "module_disk6_allruns.root";
   h_ACtrigger = new TH2F("h_ACtrigger", "; BCID ; Lumi block", 400, 0, 400, 500, 0, 500);
   h_CAtrigger = new TH2F("h_CAtrigger", "; BCID ; Lumi block", 400, 0, 400, 500, 0, 500);

   h_all_events = new TH1F("h_all_events", "; Run; Events" , 13563, 298000.5, 311563.5);
   h_triggered_events = new TH1F("h_triggered_events", "; Run; Events" , 13563, 298000.5, 311563.5);
   h_ACtriggered_events = new TH1F("h_ACtriggered_events", "; Run; Events", 13563, 298000.5, 311563.5);
   h_CAtriggered_events = new TH1F("h_CAtriggered_events", "; Run; Events", 13563, 298000.5, 311563.5);
   h_ACtriggered_events_15min = new TH1F("h_ACtriggered_events_15min", "; Time stamp; Hz", 17000000, 1461500000, 1478500000);
   h_CAtriggered_events_15min = new TH1F("h_CAtriggered_events_15min", "; Time stamp; Hz", 17000000, 1461500000, 1478500000);
   h_ACselected_events_15min = new TH1F("h_ACselected_events_15min", "; Time stamp; Hz", 17000000, 1461500000, 1478500000);
   h_CAselected_events_15min = new TH1F("h_CAselected_events_15min", "; Time stamp; Hz", 17000000, 1461500000, 1478500000);

   h_BIB_CAselected_events_15min = new TH1F("h_BIB_CAselected_events_15min", "; Time stamp; Hz", 17000000, 1461500000, 1478500000); 
   h_BIB_ACselected_events_15min = new TH1F("h_BIB_ACselected_events_15min", "; Time stamp; Hz", 17000000, 1461500000, 1478500000); 

   h_ACselected_events = new TH1F("h_ACselected_events", "; Run; Events", 13563, 298000.5, 311563.5);
   h_CAselected_events = new TH1F("h_CAselected_events", "; Run; Events", 13563, 298000.5, 311563.5);
   h_ACselected_events_299147 = new TH1F("h_ACselected_events_299147", "; Lumi block, Events", 335, 140, 475);
   h_CAselected_events_299147 = new TH1F("h_CAselected_events_299147", "; Lumi block, Events", 335, 140, 475);
   h_ACselected_events_304337 = new TH1F("h_ACselected_events_304337", "; Lumi block, Events", 1130, 70, 1200);
   h_CAselected_events_304337 = new TH1F("h_CAselected_events_304337", "; Lumi block, Events", 1130, 70, 1200);

   h_ACselected_events_12 = new TH1F("h_ACselected_events_12", "; Run; Events", 13563, 298000.5, 311563.5);
   h_CAselected_events_12 = new TH1F("h_CAselected_events_12", "; Run; Events", 13563, 298000.5, 311563.5);

   h_PVselected_events = new TH1F("h_PVselected_events", "; Run; Events", 13563, 298000.5, 311563.5);
   h_NVselected_events = new TH1F("h_NVselected_events", "; Run; Events", 13563, 298000.5, 311563.5);

   h_AC_seconds = new TH1F("h_AC_seconds", " ; Second; Hz", 17000000 , 1461500000, 1478500000);
   h_CA_seconds = new TH1F("h_CA_seconds", " ; Second; Hz", 17000000 , 1461500000, 1478500000);

   h_ACtriggered_events_301918 = new TH1F("h_ACtriggered_events_301918", " ; Lumi block; Hz" , 300, 0, 300);
   h_CAtriggered_events_301918 = new TH1F("h_CAtriggered_events_301918", " ; Lumi block; Hz" , 300, 0, 300);
   h_ACtriggered_events_309314 = new TH1F("h_ACtriggered_events_309314", " ; Lumi block; Hz" , 350, 90, 440);
   h_CAtriggered_events_309314 = new TH1F("h_CAtriggered_events_309314", " ; Lumi block; Hz" , 350, 90, 440);
  
   h_ACtriggered_events_302737 = new TH1F("h_ACtriggered_events_302737", " ; Lumi block; Hz" , 500, 0, 500);
   h_CAtriggered_events_302737 = new TH1F("h_CAtriggered_events_302737", " ; Lumi block; Hz" , 500, 0, 500);
   h_ACtriggered_events_304494 = new TH1F("h_ACtriggered_events_304494", " ; Lumi block; Hz" , 500, 0, 500);
   h_CAtriggered_events_304494 = new TH1F("h_CAtriggered_events_304494", " ; Lumi block; Hz" , 500, 0, 500);
   h_ACtriggered_events_298771 = new TH1F("h_ACtriggered_events_298771", " ; Lumi block; Hz" , 500, 0, 500);
   h_CAtriggered_events_298771 = new TH1F("h_CAtriggered_events_298771", " ; Lumi block; Hz" , 500, 0, 500);

   h_ACtriggered_events_299147 = new TH1F("h_ACtriggered_events_299147", " ; Lumi block; Hz" , 335, 140, 475);
   h_CAtriggered_events_299147 = new TH1F("h_CAtriggered_events_299147", " ; Lumi block; Hz" , 335, 140, 475);
   h_ACtriggered_events_304337 = new TH1F("h_ACtriggered_events_304337", "; Lumi block; Hz", 1130, 70, 1200);
   h_CAtriggered_events_304337 = new TH1F("h_CAtriggered_events_304337", "; Lumi block; Hz", 1130, 70, 1200);
   h_ACtriggered_events_300687 = new TH1F("h_ACtriggered_events_300687", "; Lumi block; Hz", 1130, 75, 1205);
   h_CAtriggered_events_300687 = new TH1F("h_CAtriggered_events_300687", "; Lumi block; Hz", 1130, 75, 1205);

   h_BIB_ACselected_events = new TH1F("h_BIB_ACselected_events", "; Run; Hz", 14000, 298000.5, 312000.5); // BIB refers to BIB selection based on SCT and trigger is not applied.
   h_BIB_CAselected_events = new TH1F("h_BIB_CAselected_events", "; Run; Hz", 14000, 298000.5, 312000.5);
   h_BIB_ACselected_events_309314 = new TH1F("h_BIB_ACselected_events_309314", "; Lumi block; Hz", 350, 90, 440);
   h_BIB_CAselected_events_309314 = new TH1F("h_BIB_CAselected_events_309314", "; Lumi block; Hz", 350, 90, 440);


   h_HLT_events = new TH1F("h_HLT_events", "; Run; Hz", 14000, 298000.5, 312000.5);
   h_HLT_beam1Like_events = new TH1F("h_HLT_beam1Like_events", "; Run; Hz", 14000, 298000.5, 312000.5);
   h_HLT_beam2Like_events = new TH1F("h_HLT_beam2Like_events", "; Run; Hz", 14000, 298000.5, 312000.5);
   h_HLT_beam1Like_events_15min = new TH1F("h_HLT_beam1Like_events_15min", "; Time stamp; Hz", 17000000, 1461500000, 1478500000);
   h_HLT_beam2Like_events_15min = new TH1F("h_HLT_beam2Like_events_15min", "; Time stamp; Hz", 17000000, 1461500000, 1478500000);

   h_HLT_and_AC = new TH1F("h_HLT_and_AC", "; Run; Hz", 14000, 298000.5, 312000.5);
   h_HLT_and_CA = new TH1F("h_HLT_and_CA", "; Run; Hz", 14000, 298000.5, 312000.5);
   h_HLTbeam1Like_triggered_events_302737 = new TH1F("h_HLTbeam1Like_triggered_events_302737", "; Lumi block; Events", 500, 0, 500);
   h_HLTbeam2Like_triggered_events_302737 = new TH1F("h_HLTbeam2Like_triggered_events_302737", "; Lumi block; Events", 500, 0, 500);

   h_ECAHit78_beam2_301918 = new TH2F("h_ECAHit78_beam2_301918", "; Lumi block; Hit occupancy", 200, 30, 230, 60, 0, 3000);
   h_ECCHit78_beam1_301918 = new TH2F("h_ECCHit78_beam1_301918", "; Lumi block; Hit occupancy", 200, 30, 230, 60, 0, 3000);
   h_ECAHit78_beam2_309314 = new TH2F("h_ECAHit78_beam2_309314", "; Lumi block; Hit occupancy", 350, 90, 440, 60, 0, 3000);
   h_ECCHit78_beam1_309314 = new TH2F("h_ECCHit78_beam1_309314", "; Lumi block; Hit occupancy", 350, 90, 440, 60, 0, 3000);
  
   h_ECAHit78_beam2_302737 = new TH2F("h_ECAHit78_beam2_302737", "; Lumi block; Hit occupancy", 260, 140, 400, 60, 0, 3000);
   h_ECCHit78_beam1_302737 = new TH2F("h_ECCHit78_beam1_302737", "; Lumi block; Hit occupancy", 260, 140, 400, 60, 0, 3000);
   h_ECAHit78_beam2_304494 = new TH2F("h_ECAHit78_beam2_304494", "; Lumi block; Hit occupancy", 180, 130, 310, 60, 0, 3000);
   h_ECCHit78_beam1_304494 = new TH2F("h_ECCHit78_beam1_304494", "; Lumi block; Hit occupancy", 180, 130, 310, 60, 0, 3000);
   h_ECAHit78_beam2_298771 = new TH2F("h_ECAHit78_beam2_298771", "; Lumi block; Hit occupancy", 220, 180, 400, 60, 0, 3000);
   h_ECCHit78_beam1_298771 = new TH2F("h_ECCHit78_beam1_298771", "; Lumi block; Hit occupancy", 220, 180, 400, 60, 0, 3000);
   h_ECAHit78_beam2_299147 = new TH2F("h_ECAHit78_beam2_299147", "; Lumi block; Hit occupancy", 335, 140, 475, 60, 0, 3000);
   h_ECCHit78_beam1_299147 = new TH2F("h_ECCHit78_beam1_299147", "; Lumi block; Hit occupancy", 335, 140, 475, 60, 0, 3000);
   h_ECAHit78_beam2_304337 = new TH2F("h_ECAHit78_beam2_304337", "; Lumi block; Hit occupancy", 1130, 70, 1200, 60, 0, 3000);  
   h_ECCHit78_beam1_304337 = new TH2F("h_ECCHit78_beam1_304337", "; Lumi block; Hit occupancy", 1130, 70, 1200, 60, 0, 3000);  
   h_ECAHit78_beam2_300687 = new TH2F("h_ECAHit78_beam2_300687", "; Lumi block; Hit occupancy", 1130, 75, 1205, 60, 0, 3000);
   h_ECCHit78_beam1_300687 = new TH2F("h_ECCHit78_beam1_300687", "; Lumi block; Hit occupancy", 1130, 75, 1205, 60, 0, 3000);  
   h_ECAHit78_beam2_307195 = new TH2F("h_ECAHit78_beam2_307195", "; Lumi block; Hit occupancy", 480, 260, 740, 60, 0, 3000);
   h_ECCHit78_beam1_307195 = new TH2F("h_ECCHit78_beam1_307195", "; Lumi block; Hit occupancy", 480, 260, 740, 60, 0, 3000);

   h_ECAHit78_beam2_310738 = new TH2F("h_ECAHit78_beam2_310738", "; Lumi block; Hit occupancy", 1200, 0, 1200, 60, 0, 3000);
   h_ECCHit78_beam1_310738 = new TH2F("h_ECCHit78_beam1_310738", "; Lumi block; Hit occupancy", 1200, 0, 1200, 60, 0, 3000);



   h_ECAHit78_beam1_299147 = new TH2F("h_ECAHit78_beam1_299147", "; Lumi block; Hit occupancy", 335, 140, 475, 20, 0, 1000);
   h_ECCHit78_beam2_299147 = new TH2F("h_ECCHit78_beam2_299147", "; Lumi block; Hit occupancy", 335, 140, 475, 20, 0, 1000);
   h_ECAHit78_beam1_304337 = new TH2F("h_ECAHit78_beam1_304337", "; Lumi block; Hit occupancy", 1130, 70, 1200, 20, 0, 1000);  
   h_ECCHit78_beam2_304337 = new TH2F("h_ECCHit78_beam2_304337", "; Lumi block; Hit occupancy", 1130, 70, 1200, 20, 0, 1000);  
   h_ECAHit78_beam1_307195 = new TH2F("h_ECAHit78_beam1_307195", "; Lumi block; Hit occupancy", 480, 260, 740, 20, 0, 1000);
   h_ECCHit78_beam2_307195 = new TH2F("h_ECCHit78_beam2_307195", "; Lumi block; Hit occupancy", 480, 260, 740, 20, 0, 1000);

   h_ECCHit78_beam2_310738 = new TH2F("h_ECCHit78_beam2_310738", "; Lumi block; Hit occupancy", 1200, 0, 1200, 60, 0, 3000);
   h_ECAHit78_beam1_310738 = new TH2F("h_ECAHit78_beam1_310738", "; Lumi block; Hit occupancy", 1200, 0, 1200, 60, 0, 3000);


   
   //upstream end cap
   h_ECAHit78_beam2_302829 = new TH2F("h_ECAHit78_beam2_302829", "; Lumi block; Hit occupancy", 1600, 300, 1900, 60, 0, 3000);
   h_ECCHit78_beam1_302829 = new TH2F("h_ECCHit78_beam1_302829", "; Lumi block; Hit occupancy", 1600, 300, 1900, 60, 0, 3000);
   h_ECAHit78_beam2_302831 = new TH2F("h_ECAHit78_beam2_302831", "; Lumi block; Hit occupancy", 125, 0, 125, 60, 0, 3000);  
   h_ECCHit78_beam1_302831 = new TH2F("h_ECCHit78_beam1_302831", "; Lumi block; Hit occupancy", 125, 0, 125, 60, 0, 3000);  
   //downstream end cap
   h_ECAHit78_beam1_302829 = new TH2F("h_ECAHit78_beam1_302829", "; Lumi block; Hit occupancy", 1600, 300, 1900, 20, 0, 1000);
   h_ECCHit78_beam2_302829 = new TH2F("h_ECCHit78_beam2_302829", "; Lumi block; Hit occupancy", 1600, 300, 1900, 20, 0, 1000);
   h_ECAHit78_beam1_302831 = new TH2F("h_ECAHit78_beam1_302831", "; Lumi block; Hit occupancy", 125, 0, 125, 20, 0, 1000);  
   h_ECCHit78_beam2_302831 = new TH2F("h_ECCHit78_beam2_302831", "; Lumi block; Hit occupancy", 125, 0, 125, 20, 0, 1000);  
 
   h_ECAHit78_beam2 = new TH2F("h_ECAHit78_beam2", "; Run; Hit occupancy", 13563, 298000.5, 311563.5, 60, 0, 3000);
   h_ECCHit78_beam2 = new TH2F("h_ECCHit78_beam2", "; Run; Hit occupancy", 13563, 298000.5, 311563.5, 20, 0, 1000);
   h_ECAHit78_beam1 = new TH2F("h_ECAHit78_beam1", "; Run; Hit occupancy", 13563, 298000.5, 311563.5, 20, 0, 1000);
   h_ECCHit78_beam1 = new TH2F("h_ECCHit78_beam1", "; Run; Hit occupancy", 13563, 298000.5, 311563.5, 60, 0, 3000);

   h_z_asym_beam1 = new TH2F("h_z_asym_beam1", "; Run; z-asymmetry", 13563, 298000.5, 311563.5, 50, -1, 1);
   h_z_asym_beam2 = new TH2F("h_z_asym_beam2", "; Run; z-asymmetry", 13563, 298000.5, 311563.5, 50, -1, 1);

   h_z_asym_only_pvs = new TH1F("h_z_asym_only_pvs", "; z asymmetry; Events", 50, -1, 1);
   h_z_asym_wo_pvs = new TH1F("h_z_asym_wo_pvs", "; z asymmetry; Events", 50, -1, 1);
   h_z_asym_12 = new TH1F("h_z_asym_12", "; z asymmetry; Events", 50, -1, 1);
   h_z_asym_only_pvs_12 = new TH1F("h_z_asym_only_pvs_12", "; z asymmetry; Events", 50, -1, 1);


   h_z_asym_beam1_299147 = new TH2F("h_z_asym_beam1_299147", "; Lumi block; z-asymmetry", 335, 140, 475, 50, -1, 1);
   h_z_asym_beam2_299147 = new TH2F("h_z_asym_beam2_299147", "; Lumi block; z-asymmetry", 335, 140, 475, 50, -1, 1);
   h_z_asym_beam1_304337 = new TH2F("h_z_asym_beam1_304337", "; Lumi block; z-asymmetry", 1130, 70, 1200, 50, -1, 1);
   h_z_asym_beam2_304337 = new TH2F("h_z_asym_beam2_304337", "; Lumi block; z-asymmetry", 1130, 70, 1200, 50, -1, 1);


   h_pressure_bump_run_2 = new TH2F("h_pressure_bump_run_2" , "; bcid; Lumi block", 400, 0, 400, 500, 0, 500);

   h_BIB_ECAHit78_beam2 = new TH2F("h_BIB_ECAHit78_beam2", "; Run; Hit occupancy", 14000, 298000.5, 312000.5, 60, 0, 3000);
   h_BIB_ECCHit78_beam1 = new TH2F("h_BIB_ECCHit78_beam1", "; Run; Hit occupancy", 14000, 298000.5, 312000.5, 60, 0, 3000);
   //h_BIB_ECAHit78_beam1 = new TH2F("h_BIB_ECAHit78_beam1", "; Run; Hit occupancy", 14000, 298000.5, 312000.5, 20, 0, 1000);
   //h_BIB_ECCHit78_beam2 = new TH2F("h_BIB_ECCHit78_beam2", "; Run; Hit occupancy", 14000, 298000.5, 312000.5, 20, 0, 1000);

   h_BIB_ECAHit78_beam2_309314 = new TH2F("h_BIB_ECAHit78_beam2_309314", "; Lumi block; Hit occupancy", 350, 90, 440, 60, 0, 3000);
   h_BIB_ECCHit78_beam1_309314 = new TH2F("h_BIB_ECCHit78_beam1_309314", "; Lumi block; Hit occupancy", 350, 90, 440, 60, 0, 3000);


   h_ECAHit78_beam1_15min = new TH2F("h_ECAHit78_beam1_15min", "; Run; Hit occupancy", 14000, 298000.5, 312000.5, 20, 0, 1000);
   h_ECCHit78_beam1_15min = new TH2F("h_ECCHit78_beam1_15min", "; Run; Hit occupancy", 14000, 298000.5, 312000.5, 60, 0, 3000);
   h_ECAHit78_beam2_15min = new TH2F("h_ECAHit78_beam2_15min", "; Run; Hit occupancy", 14000, 298000.5, 312000.5, 60, 0, 3000);
   h_ECCHit78_beam2_15min = new TH2F("h_ECCHit78_beam2_15min", "; Run; Hit occupancy", 14000, 298000.5, 312000.5, 20, 0, 1000);
   // Memory issue regarding TH2F with respect to Time stamp
   /*
   h_ECAHit78_beam2_15min = new TH2F("h_ECAHit78_beam2_15min", "; Time stamp; Hz", 17000000, 1461500000, 1478500000, 60, 0, 3000);
   h_ECCHit78_beam1_15min = new TH2F("h_ECCHit78_beam1_15min", "; Time stamp; Hz", 17000000, 1461500000, 1478500000, 60, 0, 3000);
   h_ECAHit78_beam1_15min = new TH2F("h_ECAHit78_beam1_15min", "; Time stamp; Hz", 17000000, 1461500000, 1478500000, 20, 0, 1000);
   h_ECCHit78_beam2_15min = new TH2F("h_ECCHit78_beam2_15min", "; Time stamp; Hz", 17000000, 1461500000, 1478500000, 20, 0, 1000);
   */

   h_lumi_ECCHit78_beam1_304337 = new TH2F("h_lumi_ECCHit78_beam1_304337", "; Delivered luminosity [#mub^{-1}/s]; SCT BIB [Hz]", 100, 4000, 12000, 60, 0, 3000);
   h_BIB_ECCHit78_beam1_304337 = new TH2F("h_BIB_ECCHit78_beam1_304337", "; Lumi block; SCT BIB [Hz]", 100, 70, 1200, 60, 0, 3000);


   h_bcid_vs_lb_AC_302737 = new TH2F("h_bcid_vs_lb_AC_302737", "; BCID; Lumi block", 3200, 0, 3200, 260, 140, 400); 
   h_bcid_vs_lb_CA_302737 = new TH2F("h_bcid_vs_lb_CA_302737", "; BCID; Lumi block", 3200, 0, 3200, 260, 140, 400); 

   h_bcid_vs_lb_HLTbeam1Like_302737 = new TH2F("h_bcid_vs_lb_HLTbeam1Like_302737", "; BCID; Lumi block", 3200, 0, 3200, 260, 140, 400); 
   h_bcid_vs_lb_HLTbeam2Like_302737 = new TH2F("h_bcid_vs_lb_HLTbeam2Like_302737", "; BCID; Lumi block", 3200, 0, 3200, 260, 140, 400); 
   h_ECCHit78_HLT_beam1Like = new TH2F("h_ECCHit78_HLT_beam1Like", "; Run; Hit occupancy", 14000, 298000.5, 312000.5, 60, 0, 3000);
   h_ECAHit78_HLT_beam2Like = new TH2F("h_ECAHit78_HLT_beam2Like", "; Run; Hit occupancy", 14000, 298000.5, 312000.5, 60, 0, 3000);
   h_ECAHit78_HLT_upstream = new TH2F("h_ECAHit78_HLT_upstream", "; Run; Hit occupancy", 14000, 298000.5, 312000.5, 60, 0, 3000);
   h_ECCHit78_HLT_upstream = new TH2F("h_ECCHit78_HLT_upstream", "; Run; Hit occupancy", 14000, 298000.5, 312000.5, 60, 0, 3000);


   outer_module_ECCdisk6_hit_vs_run = new TH2F("outer_module_ECCdisk6_hit_vs_run", "; Run; Hit occupancy", 14000, 298000.5, 312000.5, 200, 0, 1000);
   outer_module_ECAdisk6_hit_vs_run = new TH2F("outer_module_ECAdisk6_hit_vs_run", "; Run; Hit occupancy", 14000, 298000.5, 312000.5, 200, 0, 1000);
   middle_module_ECCdisk6_hit_vs_run = new TH2F("middle_module_ECCdisk6_hit_vs_run", "; Run; Hit occupancy", 14000, 298000.5, 312000.5, 100, 0, 500);
   middle_module_ECAdisk6_hit_vs_run = new TH2F("middle_module_ECAdisk6_hit_vs_run", "; Run; Hit occupancy", 14000, 298000.5, 312000.5, 100, 0, 500);
   inner_module_ECCdisk6_hit_vs_run = new TH2F("inner_module_ECCdisk6_hit_vs_run", "; Run; Hit occupancy", 14000, 298000.5, 312000.5, 20, 0, 100);
   inner_module_ECAdisk6_hit_vs_run = new TH2F("inner_module_ECAdisk6_hit_vs_run", "; Run; Hit occupancy", 14000, 298000.5, 312000.5, 20, 0, 100);

   outer_module_ECCdisk6_hit_vs_run_beam1Like = new TH2F("outer_module_ECCdisk6_hit_vs_run_beam1Like", "; Run; Hit occupancy", 14000, 298000.5, 312000.5, 200, 0, 1000);
   outer_module_ECAdisk6_hit_vs_run_beam1Like = new TH2F("outer_module_ECAdisk6_hit_vs_run_beam1Like", "; Run; Hit occupancy", 14000, 298000.5, 312000.5, 200, 0, 1000);
   middle_module_ECCdisk6_hit_vs_run_beam1Like = new TH2F("middle_module_ECCdisk6_hit_vs_run_beam1Like", "; Run; Hit occupancy", 14000, 298000.5, 312000.5, 100, 0, 500);
   middle_module_ECAdisk6_hit_vs_run_beam1Like = new TH2F("middle_module_ECAdisk6_hit_vs_run_beam1Like", "; Run; Hit occupancy", 14000, 298000.5, 312000.5, 100, 0, 500);
   inner_module_ECCdisk6_hit_vs_run_beam1Like = new TH2F("inner_module_ECCdisk6_hit_vs_run_beam1Like", "; Run; Hit occupancy", 14000, 298000.5, 312000.5, 20, 0, 100);
   inner_module_ECAdisk6_hit_vs_run_beam1Like = new TH2F("inner_module_ECAdisk6_hit_vs_run_beam1Like", "; Run; Hit occupancy", 14000, 298000.5, 312000.5, 20, 0, 100);

   outer_module_ECCdisk6_hit_vs_run_beam2Like = new TH2F("outer_module_ECCdisk6_hit_vs_run_beam2Like", "; Run; Hit occupancy", 14000, 298000.5, 312000.5, 200, 0, 1000);
   outer_module_ECAdisk6_hit_vs_run_beam2Like = new TH2F("outer_module_ECAdisk6_hit_vs_run_beam2Like", "; Run; Hit occupancy", 14000, 298000.5, 312000.5, 200, 0, 1000);
   middle_module_ECCdisk6_hit_vs_run_beam2Like = new TH2F("middle_module_ECCdisk6_hit_vs_run_beam2Like", "; Run; Hit occupancy", 14000, 298000.5, 312000.5, 100, 0, 500);
   middle_module_ECAdisk6_hit_vs_run_beam2Like = new TH2F("middle_module_ECAdisk6_hit_vs_run_beam2Like", "; Run; Hit occupancy", 14000, 298000.5, 312000.5, 100, 0, 500);
   inner_module_ECCdisk6_hit_vs_run_beam2Like = new TH2F("inner_module_ECCdisk6_hit_vs_run_beam2Like", "; Run; Hit occupancy", 14000, 298000.5, 312000.5, 20, 0, 100);
   inner_module_ECAdisk6_hit_vs_run_beam2Like = new TH2F("inner_module_ECAdisk6_hit_vs_run_beam2Like", "; Run; Hit occupancy", 14000, 298000.5, 312000.5, 20, 0, 100);





   outer_module_ECCdisk6_hit_vs_run_beam1 = new TH2F("outer_module_ECCdisk6_hit_vs_run_beam1", "; Run; Hit occupancy", 14000, 298000.5, 312000.5, 200, 0, 1000);
   outer_module_ECAdisk6_hit_vs_run_beam1 = new TH2F("outer_module_ECAdisk6_hit_vs_run_beam1", "; Run; Hit occupancy", 14000, 298000.5, 312000.5, 200, 0, 1000);
   middle_module_ECCdisk6_hit_vs_run_beam1 = new TH2F("middle_module_ECCdisk6_hit_vs_run_beam1", "; Run; Hit occupancy", 14000, 298000.5, 312000.5, 100, 0, 500);
   middle_module_ECAdisk6_hit_vs_run_beam1 = new TH2F("middle_module_ECAdisk6_hit_vs_run_beam1", "; Run; Hit occupancy", 14000, 298000.5, 312000.5, 100, 0, 500);
   inner_module_ECCdisk6_hit_vs_run_beam1 = new TH2F("inner_module_ECCdisk6_hit_vs_run_beam1", "; Run; Hit occupancy", 14000, 298000.5, 312000.5, 20, 0, 100);
   inner_module_ECAdisk6_hit_vs_run_beam1 = new TH2F("inner_module_ECAdisk6_hit_vs_run_beam1", "; Run; Hit occupancy", 14000, 298000.5, 312000.5, 20, 0, 100);

   outer_module_ECCdisk6_hit_vs_run_beam2 = new TH2F("outer_module_ECCdisk6_hit_vs_run_beam2", "; Run; Hit occupancy", 14000, 298000.5, 312000.5, 200, 0, 1000);
   outer_module_ECAdisk6_hit_vs_run_beam2 = new TH2F("outer_module_ECAdisk6_hit_vs_run_beam2", "; Run; Hit occupancy", 14000, 298000.5, 312000.5, 200, 0, 1000);
   middle_module_ECCdisk6_hit_vs_run_beam2 = new TH2F("middle_module_ECCdisk6_hit_vs_run_beam2", "; Run; Hit occupancy", 14000, 298000.5, 312000.5, 100, 0, 500);
   middle_module_ECAdisk6_hit_vs_run_beam2 = new TH2F("middle_module_ECAdisk6_hit_vs_run_beam2", "; Run; Hit occupancy", 14000, 298000.5, 312000.5, 100, 0, 500);
   inner_module_ECCdisk6_hit_vs_run_beam2 = new TH2F("inner_module_ECCdisk6_hit_vs_run_beam2", "; Run; Hit occupancy", 14000, 298000.5, 312000.5, 20, 0, 100);
   inner_module_ECAdisk6_hit_vs_run_beam2 = new TH2F("inner_module_ECAdisk6_hit_vs_run_beam2", "; Run; Hit occupancy", 14000, 298000.5, 312000.5, 20, 0, 100);






   h_ECCHit78_HLT = new TH2F("h_ECCHit78_HLT", "; Run; Hit occupancy", 14000, 298000.5, 312000.5, 60, 0, 3000);
   h_ECAHit78_HLT = new TH2F("h_ECAHit78_HLT", "; Run; Hit occupancy", 14000, 298000.5, 312000.5, 60, 0, 3000);

   h_HLTbeam1Like_z_asym_302737 = new TH2F("h_HLTbeam1Like_z_asym_302737", "; Lumi block; z-asymmetry", 260, 140, 400, 240, -1.2, 1.2);
   h_HLTbeam2Like_z_asym_302737 = new TH2F("h_HLTbeam2Like_z_asym_302737", "; Lumi block; z-asymmetry", 260, 140, 400, 240, -1.2, 1.2);
   h_HLT_z_asym_302737 = new TH2F("h_HLT_z_asym_302737", "; Lumi block; z-asymmetry", 260, 140, 400, 240, -1.2, 1.2);

   h_HLTbeam1Like_hit_302737 = new TH2F("h_HLTbeam1Like_hit_302737", "; Lumi block; Hit occupancy", 260, 140, 400, 60, 0, 3000);
   h_HLTbeam2Like_hit_302737 = new TH2F("h_HLTbeam2Like_hit_302737", "; Lumi block; Hit occupancy", 260, 140, 400, 60, 0, 3000);
   h_HLT_hit_302737 = new TH2F("h_HLT_hit_302737", "; Lumi block; Hit occupancy", 260, 140, 400, 60, 0, 3000);
   h_HLT_z_asym_304337 = new TH2F("h_HLT_z_asym_304337", "; Lumi block; z-asymmetry", 1130, 70, 1200, 240, -1.2, 1.2);
   h_HLT_hit_304337 = new TH2F("h_HLT_hit_304337", "; Lumi block; Hit occupancy", 1130, 70, 1200, 60, 0, 3000);

   h_BCMtrigger_z_asym_302737 = new TH2F("h_BCMtrigger_z_asym_302737", "; Lumi block; z-asymmetry", 260, 140, 400, 240, -1.2, 1.2);
   h_ACtrigger_z_asym_302737 = new TH2F("h_ACtrigger_z_asym_302737", "; Lumi block; z-asymmetry", 260, 140, 400, 240, -1.2, 1.2);
   h_CAtrigger_z_asym_302737 = new TH2F("h_CAtrigger_z_asym_302737", "; Lumi block; z-asymmetry", 260, 140, 400, 240, -1.2, 1.2);
  
   h_HLT_z_asym = new TH2F("h_HLT_z_asym", "; Run; z-asymmetry", 13563, 298000.5, 311563.5, 50, -1, 1);
   h_bcid_vs_lb_HLT_302737 = new TH2F("h_bcid_vs_lb_HLT_302737", "; BICD; Lumi block", 3200, 0, 3200, 260, 140, 400);

   h_hit_vs_disks = new TH2F("h_hit_vs_disks", "; End-cap disks; Hit occupancy", 17, -8.5, 8.5, 60, 0, 3000);

   h_HLT_z_asym_298771 = new TH2F("h_HLT_z_asym_298771", "; Lumi block; z-asymmetry", 220, 180, 400, 50, -1, 1);
   h_HLT_hit_298771 = new TH2F("h_HLT_hit_298771", "; Lumi block; Hit occupancy", 220, 180, 400, 60, 0, 3000);
   h_bcid_vs_lb_HLT_298771 = new TH2F("h_bcid_vs_lb_HLT_298771", "; BCID; Lumi block", 200, 200, 400, 220, 180, 400);
   //h_bcid_vs_pv_HLT_302737 = new TH2F("h_bcid_vs_pv_HLT_302737", "; BCID; Hit occupancy", 3200, 0, 3200, 60, 0, 3000);
   //h_bcid_vs_nv_HLT_302737 = new TH2F("h_bcid_vs_nv_HLT_302737", "; BCID; Hit occupancy", 3200, 0, 3200, 60, 0, 3000);
   
   h_bcid_vs_pv_HLT_302737 = new TH2F("h_bcid_vs_pv_HLT_302737", "; BCID; Hit occupancy", 200, 3000, 3200, 20, 0, 100);
   h_bcid_vs_nv_HLT_302737 = new TH2F("h_bcid_vs_nv_HLT_302737", "; BCID; Hit occupancy", 200, 3000, 3200, 20, 0, 100);

   h_bcid_vs_pv_HLT_307195 = new TH2F("h_bcid_vs_pv_HLT_307195", "; BCID; Hit occupancy", 30, 0, 30, 20, 0, 100);
   h_bcid_vs_nv_HLT_307195 = new TH2F("h_bcid_vs_nv_HLT_307195", "; BCID; Hit occupancy", 30, 0, 30, 20, 0, 100);
   h_lb_vs_HitECC78_beam1Like_307195 = new TH2F("h_lb_vs_HitECC78_beam1Like_307195", "; Lumi block; Hit occupancy", 480, 260, 740, 20, 0, 100);
   h_lb_vs_HitECA78_beam2Like_307195 = new TH2F("h_lb_vs_HitECA78_beam2Like_307195", "; Lumi block; Hit occupancy", 480, 260, 740, 20, 0, 100);

   h_bcid_vs_pv_HLT_309314 = new TH2F("h_bcid_vs_pv_HLT_309314", "; BCID; Hit occupancy", 60, 90, 150, 20, 0, 100);
   h_bcid_vs_nv_HLT_309314 = new TH2F("h_bcid_vs_nv_HLT_309314", "; BCID; Hit occupancy", 60, 90, 150, 20, 0, 100);
   h_lb_vs_HitECC78_beam1Like_309314 = new TH2F("h_lb_vs_HitECC78_beam1Like_309314", "; Lumi block; Hit occupancy", 350, 90, 440, 20, 0, 100);
   h_lb_vs_HitECA78_beam2Like_309314 = new TH2F("h_lb_vs_HitECA78_beam2Like_309314", "; Lumi block; Hit occupancy", 350, 90, 440, 20, 0, 100);

   h_bcid_vs_pv_HLT_302737_zlarger05 = new TH2F("h_bcid_vs_pv_HLT_302737_zlarger05", "; BCID; Hit occupancy", 200, 3000, 3200, 20, 0, 100);
   h_bcid_vs_nv_HLT_302737_zlarger05 = new TH2F("h_bcid_vs_nv_HLT_302737_zlarger05", "; BCID; Hit occupancy", 200, 3000, 3200, 20, 0, 100);
   h_bcid_vs_pv_HLT_302737_zsmaller05 = new TH2F("h_bcid_vs_pv_HLT_302737_zsmaller05", "; BCID; Hit occupancy", 200, 3000, 3200, 20, 0, 100);
   h_bcid_vs_nv_HLT_302737_zsmaller05 = new TH2F("h_bcid_vs_nv_HLT_302737_zsmaller05", "; BCID; Hit occupancy", 200, 3000, 3200, 20, 0, 100);
 
   h_bcid_vs_pv_HLT_302737_disk1 = new TH2F("h_bcid_vs_pv_HLT_302737_disk1", "; BCID; Hit occupancy", 200, 3000, 3200, 20, 0, 100);
   h_bcid_vs_pv_HLT_302737_disk2 = new TH2F("h_bcid_vs_pv_HLT_302737_disk2", "; BCID; Hit occupancy", 200, 3000, 3200, 20, 0, 100);
   h_bcid_vs_pv_HLT_302737_disk3 = new TH2F("h_bcid_vs_pv_HLT_302737_disk3", "; BCID; Hit occupancy", 200, 3000, 3200, 20, 0, 100);
   h_bcid_vs_pv_HLT_302737_disk4 = new TH2F("h_bcid_vs_pv_HLT_302737_disk4", "; BCID; Hit occupancy", 200, 3000, 3200, 20, 0, 100);
   h_bcid_vs_pv_HLT_302737_disk5 = new TH2F("h_bcid_vs_pv_HLT_302737_disk5", "; BCID; Hit occupancy", 200, 3000, 3200, 20, 0, 100);
   h_bcid_vs_pv_HLT_302737_disk6 = new TH2F("h_bcid_vs_pv_HLT_302737_disk6", "; BCID; Hit occupancy", 200, 3000, 3200, 20, 0, 100);
   h_bcid_vs_pv_HLT_302737_disk9 = new TH2F("h_bcid_vs_pv_HLT_302737_disk9", "; BCID; Hit occupancy", 200, 3000, 3200, 20, 0, 100);

   h_bcid_vs_nv_HLT_302737_disk1 = new TH2F("h_bcid_vs_nv_HLT_302737_disk1", "; BCID; Hit occupancy", 200, 3000, 3200, 20, 0, 100);
   h_bcid_vs_nv_HLT_302737_disk2 = new TH2F("h_bcid_vs_nv_HLT_302737_disk2", "; BCID; Hit occupancy", 200, 3000, 3200, 20, 0, 100);
   h_bcid_vs_nv_HLT_302737_disk3 = new TH2F("h_bcid_vs_nv_HLT_302737_disk3", "; BCID; Hit occupancy", 200, 3000, 3200, 20, 0, 100);
   h_bcid_vs_nv_HLT_302737_disk4 = new TH2F("h_bcid_vs_nv_HLT_302737_disk4", "; BCID; Hit occupancy", 200, 3000, 3200, 20, 0, 100);
   h_bcid_vs_nv_HLT_302737_disk5 = new TH2F("h_bcid_vs_nv_HLT_302737_disk5", "; BCID; Hit occupancy", 200, 3000, 3200, 20, 0, 100);
   h_bcid_vs_nv_HLT_302737_disk6 = new TH2F("h_bcid_vs_nv_HLT_302737_disk6", "; BCID; Hit occupancy", 200, 3000, 3200, 20, 0, 100);
   h_bcid_vs_nv_HLT_302737_disk9 = new TH2F("h_bcid_vs_nv_HLT_302737_disk9", "; BCID; Hit occupancy", 200, 3000, 3200, 20, 0, 100);

   h_bcid_pv_HLT_302737_disk1_largez = new TH2F("h_bcid_pv_HLT_302737_disk1_largez", "; BCID; Hit occupancy", 200, 3000, 3200, 20, 0, 100);
   h_bcid_pv_HLT_302737_disk2_largez = new TH2F("h_bcid_pv_HLT_302737_disk2_largez", "; BCID; Hit occupancy", 200, 3000, 3200, 20, 0, 100);
   h_bcid_pv_HLT_302737_disk3_largez = new TH2F("h_bcid_pv_HLT_302737_disk3_largez", "; BCID; Hit occupancy", 200, 3000, 3200, 20, 0, 100);
   h_bcid_pv_HLT_302737_disk4_largez = new TH2F("h_bcid_pv_HLT_302737_disk4_largez", "; BCID; Hit occupancy", 200, 3000, 3200, 20, 0, 100);
   h_bcid_pv_HLT_302737_disk5_largez = new TH2F("h_bcid_pv_HLT_302737_disk5_largez", "; BCID; Hit occupancy", 200, 3000, 3200, 20, 0, 100);
   h_bcid_pv_HLT_302737_disk6_largez = new TH2F("h_bcid_pv_HLT_302737_disk6_largez", "; BCID; Hit occupancy", 200, 3000, 3200, 20, 0, 100);
   h_bcid_pv_HLT_302737_disk9_largez = new TH2F("h_bcid_pv_HLT_302737_disk9_largez", "; BCID; Hit occupancy", 200, 3000, 3200, 20, 0, 100);

   h_bcid_nv_HLT_302737_disk1_largez = new TH2F("h_bcid_nv_HLT_302737_disk1_largez", "; BCID; Hit occupancy", 200, 3000, 3200, 20, 0, 100);
   h_bcid_nv_HLT_302737_disk2_largez = new TH2F("h_bcid_nv_HLT_302737_disk2_largez", "; BCID; Hit occupancy", 200, 3000, 3200, 20, 0, 100);
   h_bcid_nv_HLT_302737_disk3_largez = new TH2F("h_bcid_nv_HLT_302737_disk3_largez", "; BCID; Hit occupancy", 200, 3000, 3200, 20, 0, 100);
   h_bcid_nv_HLT_302737_disk4_largez = new TH2F("h_bcid_nv_HLT_302737_disk4_largez", "; BCID; Hit occupancy", 200, 3000, 3200, 20, 0, 100);
   h_bcid_nv_HLT_302737_disk5_largez = new TH2F("h_bcid_nv_HLT_302737_disk5_largez", "; BCID; Hit occupancy", 200, 3000, 3200, 20, 0, 100);
   h_bcid_nv_HLT_302737_disk6_largez = new TH2F("h_bcid_nv_HLT_302737_disk6_largez", "; BCID; Hit occupancy", 200, 3000, 3200, 20, 0, 100);
   h_bcid_nv_HLT_302737_disk9_largez = new TH2F("h_bcid_nv_HLT_302737_disk9_largez", "; BCID; Hit occupancy", 200, 3000, 3200, 20, 0, 100);

   h_bcid_vs_hit_HLT_302737 = new TH2F("h_bcid_vs_hit_HLT_302737", "; BCID; Hit occupancy", 3200, 0, 3200, 60, 0, 3000);

   ListTH2F.push_back(h_ACtrigger);
   ListTH2F.push_back(h_CAtrigger);
   ListTH2F.push_back(h_ECAHit78_beam2);
   ListTH2F.push_back(h_ECCHit78_beam2);
   ListTH2F.push_back(h_ECAHit78_beam1);
   ListTH2F.push_back(h_ECCHit78_beam1);
   ListTH2F.push_back(h_z_asym_beam1);
   ListTH2F.push_back(h_z_asym_beam2);

   ListTH2F.push_back(h_z_asym_beam1_299147);
   ListTH2F.push_back(h_z_asym_beam2_299147);

   ListTH2F.push_back(h_z_asym_beam1_304337);
   ListTH2F.push_back(h_z_asym_beam2_304337);


   ListTH2F.push_back(h_pressure_bump_run_2);
   
   ListTH2F.push_back(h_ECAHit78_beam2_301918);
   ListTH2F.push_back(h_ECCHit78_beam1_301918);
   ListTH2F.push_back(h_ECAHit78_beam2_309314);
   ListTH2F.push_back(h_ECCHit78_beam1_309314);
 
   ListTH2F.push_back(h_ECAHit78_beam2_302737);
   ListTH2F.push_back(h_ECCHit78_beam1_302737);
   ListTH2F.push_back(h_ECAHit78_beam2_304494);
   ListTH2F.push_back(h_ECCHit78_beam1_304494);
   ListTH2F.push_back(h_ECAHit78_beam2_298771);
   ListTH2F.push_back(h_ECCHit78_beam1_298771);
   ListTH2F.push_back(h_ECAHit78_beam2_299147);
   ListTH2F.push_back(h_ECCHit78_beam1_299147);
 
   ListTH2F.push_back(h_ECAHit78_beam2_304337);
   ListTH2F.push_back(h_ECCHit78_beam1_304337);
   ListTH2F.push_back(h_ECAHit78_beam2_300687);
   ListTH2F.push_back(h_ECCHit78_beam1_300687);
   ListTH2F.push_back(h_ECAHit78_beam2_307195);
   ListTH2F.push_back(h_ECCHit78_beam1_307195);
   ListTH2F.push_back(h_ECAHit78_beam1_307195);
   ListTH2F.push_back(h_ECCHit78_beam2_307195);

   ListTH2F.push_back(h_ECAHit78_beam2_310738);
   ListTH2F.push_back(h_ECCHit78_beam1_310738);
   ListTH2F.push_back(h_ECAHit78_beam1_310738);
   ListTH2F.push_back(h_ECCHit78_beam2_310738);



   ListTH2F.push_back(h_BIB_ECCHit78_beam1);
   ListTH2F.push_back(h_BIB_ECAHit78_beam2);
   //ListTH2F.push_back(h_BIB_ECAHit78_beam1);
   //ListTH2F.push_back(h_BIB_ECCHit78_beam2);
   ListTH2F.push_back(h_BIB_ECCHit78_beam1_309314);
   ListTH2F.push_back(h_BIB_ECAHit78_beam2_309314);

   ListTH2F.push_back(h_ECAHit78_beam1_299147);
   ListTH2F.push_back(h_ECCHit78_beam2_299147);
   ListTH2F.push_back(h_ECAHit78_beam1_304337);
   ListTH2F.push_back(h_ECCHit78_beam2_304337);
   
   // downstream  
   ListTH2F.push_back(h_ECAHit78_beam1_302829);
   ListTH2F.push_back(h_ECCHit78_beam2_302829);
   ListTH2F.push_back(h_ECAHit78_beam1_302831);
   ListTH2F.push_back(h_ECCHit78_beam2_302831);
   // upstream
   ListTH2F.push_back(h_ECAHit78_beam2_302829);
   ListTH2F.push_back(h_ECCHit78_beam1_302829);
   ListTH2F.push_back(h_ECAHit78_beam2_302831);
   ListTH2F.push_back(h_ECCHit78_beam1_302831);
 
   ListTH2F.push_back(h_ECAHit78_beam1_15min);
   ListTH2F.push_back(h_ECCHit78_beam1_15min);
   ListTH2F.push_back(h_ECCHit78_beam2_15min);
   ListTH2F.push_back(h_ECAHit78_beam2_15min);

   ListTH2F.push_back(h_lumi_ECCHit78_beam1_304337);
   ListTH2F.push_back(h_BIB_ECCHit78_beam1_304337);

   ListTH2F.push_back(h_bcid_vs_lb_AC_302737);
   ListTH2F.push_back(h_bcid_vs_lb_CA_302737);
   ListTH2F.push_back(h_bcid_vs_lb_HLTbeam1Like_302737);
   ListTH2F.push_back(h_bcid_vs_lb_HLTbeam2Like_302737);
   ListTH2F.push_back(h_ECCHit78_HLT_beam1Like);
   ListTH2F.push_back(h_ECAHit78_HLT_beam2Like);
   ListTH2F.push_back(h_ECAHit78_HLT_upstream);
   ListTH2F.push_back(h_ECCHit78_HLT_upstream);

   ListTH2F.push_back(outer_module_ECCdisk6_hit_vs_run);
   ListTH2F.push_back(outer_module_ECAdisk6_hit_vs_run);
   ListTH2F.push_back(middle_module_ECCdisk6_hit_vs_run);
   ListTH2F.push_back(middle_module_ECAdisk6_hit_vs_run);
   ListTH2F.push_back(inner_module_ECCdisk6_hit_vs_run);
   ListTH2F.push_back(inner_module_ECAdisk6_hit_vs_run);


   ListTH2F.push_back(outer_module_ECCdisk6_hit_vs_run_beam1Like);
   ListTH2F.push_back(outer_module_ECAdisk6_hit_vs_run_beam1Like);
   ListTH2F.push_back(middle_module_ECCdisk6_hit_vs_run_beam1Like);
   ListTH2F.push_back(middle_module_ECAdisk6_hit_vs_run_beam1Like);
   ListTH2F.push_back(inner_module_ECCdisk6_hit_vs_run_beam1Like);
   ListTH2F.push_back(inner_module_ECAdisk6_hit_vs_run_beam1Like);


   ListTH2F.push_back(outer_module_ECCdisk6_hit_vs_run_beam2Like);
   ListTH2F.push_back(outer_module_ECAdisk6_hit_vs_run_beam2Like);
   ListTH2F.push_back(middle_module_ECCdisk6_hit_vs_run_beam2Like);
   ListTH2F.push_back(middle_module_ECAdisk6_hit_vs_run_beam2Like);
   ListTH2F.push_back(inner_module_ECCdisk6_hit_vs_run_beam2Like);
   ListTH2F.push_back(inner_module_ECAdisk6_hit_vs_run_beam2Like);


   ListTH2F.push_back(outer_module_ECCdisk6_hit_vs_run_beam1);
   ListTH2F.push_back(outer_module_ECAdisk6_hit_vs_run_beam1);
   ListTH2F.push_back(middle_module_ECCdisk6_hit_vs_run_beam1);
   ListTH2F.push_back(middle_module_ECAdisk6_hit_vs_run_beam1);
   ListTH2F.push_back(inner_module_ECCdisk6_hit_vs_run_beam1);
   ListTH2F.push_back(inner_module_ECAdisk6_hit_vs_run_beam1);



   ListTH2F.push_back(outer_module_ECCdisk6_hit_vs_run_beam2);
   ListTH2F.push_back(outer_module_ECAdisk6_hit_vs_run_beam2);
   ListTH2F.push_back(middle_module_ECCdisk6_hit_vs_run_beam2);
   ListTH2F.push_back(middle_module_ECAdisk6_hit_vs_run_beam2);
   ListTH2F.push_back(inner_module_ECCdisk6_hit_vs_run_beam2);
   ListTH2F.push_back(inner_module_ECAdisk6_hit_vs_run_beam2);
 

 
  
   ListTH2F.push_back(h_ECCHit78_HLT);
   ListTH2F.push_back(h_ECAHit78_HLT);

   ListTH2F.push_back(h_HLTbeam1Like_z_asym_302737);
   ListTH2F.push_back(h_HLTbeam2Like_z_asym_302737);
   ListTH2F.push_back(h_HLT_z_asym_302737);

   ListTH2F.push_back(h_HLTbeam1Like_hit_302737);
   ListTH2F.push_back(h_HLTbeam2Like_hit_302737);
   ListTH2F.push_back(h_HLT_hit_302737);
   ListTH2F.push_back(h_BCMtrigger_z_asym_302737);
   ListTH2F.push_back(h_ACtrigger_z_asym_302737);
   ListTH2F.push_back(h_CAtrigger_z_asym_302737);

   ListTH2F.push_back(h_HLT_z_asym_304337);
   ListTH2F.push_back(h_HLT_hit_304337);
   ListTH2F.push_back(h_HLT_z_asym); 
   ListTH2F.push_back(h_bcid_vs_lb_HLT_302737);
   ListTH2F.push_back(h_hit_vs_disks);
   ListTH2F.push_back(h_HLT_z_asym_298771);
   ListTH2F.push_back(h_HLT_hit_298771);
   ListTH2F.push_back(h_bcid_vs_lb_HLT_298771);

   ListTH2F.push_back(h_bcid_vs_pv_HLT_307195);
   ListTH2F.push_back(h_bcid_vs_nv_HLT_307195);
   ListTH2F.push_back(h_lb_vs_HitECC78_beam1Like_307195);
   ListTH2F.push_back(h_lb_vs_HitECA78_beam2Like_307195);

   ListTH2F.push_back(h_bcid_vs_pv_HLT_309314);
   ListTH2F.push_back(h_bcid_vs_nv_HLT_309314);
   ListTH2F.push_back(h_lb_vs_HitECC78_beam1Like_309314);
   ListTH2F.push_back(h_lb_vs_HitECA78_beam2Like_309314);
 

   ListTH2F.push_back(h_bcid_vs_pv_HLT_302737);
   ListTH2F.push_back(h_bcid_vs_nv_HLT_302737);
   ListTH2F.push_back(h_bcid_vs_pv_HLT_302737_zlarger05);
   ListTH2F.push_back(h_bcid_vs_nv_HLT_302737_zlarger05);
   ListTH2F.push_back(h_bcid_vs_pv_HLT_302737_zsmaller05);
   ListTH2F.push_back(h_bcid_vs_nv_HLT_302737_zsmaller05);

   ListTH2F.push_back(h_bcid_vs_pv_HLT_302737_disk1);
   ListTH2F.push_back(h_bcid_vs_pv_HLT_302737_disk2);
   ListTH2F.push_back(h_bcid_vs_pv_HLT_302737_disk3);
   ListTH2F.push_back(h_bcid_vs_pv_HLT_302737_disk4);
   ListTH2F.push_back(h_bcid_vs_pv_HLT_302737_disk5);
   ListTH2F.push_back(h_bcid_vs_pv_HLT_302737_disk6);
   ListTH2F.push_back(h_bcid_vs_pv_HLT_302737_disk9);

   ListTH2F.push_back(h_bcid_vs_nv_HLT_302737_disk1);
   ListTH2F.push_back(h_bcid_vs_nv_HLT_302737_disk2);
   ListTH2F.push_back(h_bcid_vs_nv_HLT_302737_disk3);
   ListTH2F.push_back(h_bcid_vs_nv_HLT_302737_disk4);
   ListTH2F.push_back(h_bcid_vs_nv_HLT_302737_disk5);
   ListTH2F.push_back(h_bcid_vs_nv_HLT_302737_disk6);
   ListTH2F.push_back(h_bcid_vs_nv_HLT_302737_disk9);

   ListTH2F.push_back(h_bcid_pv_HLT_302737_disk1_largez);
   ListTH2F.push_back(h_bcid_pv_HLT_302737_disk2_largez);
   ListTH2F.push_back(h_bcid_pv_HLT_302737_disk3_largez);
   ListTH2F.push_back(h_bcid_pv_HLT_302737_disk4_largez);
   ListTH2F.push_back(h_bcid_pv_HLT_302737_disk5_largez);
   ListTH2F.push_back(h_bcid_pv_HLT_302737_disk6_largez);
   ListTH2F.push_back(h_bcid_pv_HLT_302737_disk9_largez);


   ListTH2F.push_back(h_bcid_nv_HLT_302737_disk1_largez);
   ListTH2F.push_back(h_bcid_nv_HLT_302737_disk2_largez);
   ListTH2F.push_back(h_bcid_nv_HLT_302737_disk3_largez);
   ListTH2F.push_back(h_bcid_nv_HLT_302737_disk4_largez);
   ListTH2F.push_back(h_bcid_nv_HLT_302737_disk5_largez);
   ListTH2F.push_back(h_bcid_nv_HLT_302737_disk6_largez);
   ListTH2F.push_back(h_bcid_nv_HLT_302737_disk9_largez);


   ListTH2F.push_back(h_bcid_vs_hit_HLT_302737);

   ListTH1F.push_back(h_all_events);
   ListTH1F.push_back(h_triggered_events);
   ListTH1F.push_back(h_ACtriggered_events);
   ListTH1F.push_back(h_CAtriggered_events);
   ListTH1F.push_back(h_ACselected_events);
   ListTH1F.push_back(h_CAselected_events);
   ListTH1F.push_back(h_ACselected_events_299147);
   ListTH1F.push_back(h_CAselected_events_299147);
   ListTH1F.push_back(h_ACselected_events_304337);
   ListTH1F.push_back(h_CAselected_events_304337);
 
   ListTH1F.push_back(h_ACselected_events_12);
   ListTH1F.push_back(h_CAselected_events_12);
   ListTH1F.push_back(h_PVselected_events);
   ListTH1F.push_back(h_NVselected_events);
   ListTH1F.push_back(h_AC_seconds);
   ListTH1F.push_back(h_CA_seconds);
   ListTH1F.push_back(h_ACtriggered_events_15min);
   ListTH1F.push_back(h_CAtriggered_events_15min);
   ListTH1F.push_back(h_BIB_CAselected_events_15min);
   ListTH1F.push_back(h_BIB_ACselected_events_15min);
   ListTH1F.push_back(h_ACselected_events_15min);
   ListTH1F.push_back(h_CAselected_events_15min);
   ListTH1F.push_back(h_ACtriggered_events_301918);
   ListTH1F.push_back(h_CAtriggered_events_301918);  
   ListTH1F.push_back(h_ACtriggered_events_309314);
   ListTH1F.push_back(h_CAtriggered_events_309314);  
 
   ListTH1F.push_back(h_ACtriggered_events_302737);
   ListTH1F.push_back(h_CAtriggered_events_302737);  
   ListTH1F.push_back(h_ACtriggered_events_304494);
   ListTH1F.push_back(h_CAtriggered_events_304494);  
   ListTH1F.push_back(h_ACtriggered_events_298771);
   ListTH1F.push_back(h_CAtriggered_events_298771);  

   ListTH1F.push_back(h_ACtriggered_events_299147);
   ListTH1F.push_back(h_CAtriggered_events_299147);  
   ListTH1F.push_back(h_ACtriggered_events_304337);
   ListTH1F.push_back(h_CAtriggered_events_304337);
   ListTH1F.push_back(h_ACtriggered_events_300687);
   ListTH1F.push_back(h_CAtriggered_events_300687);


   ListTH1F.push_back(h_z_asym_only_pvs);
   ListTH1F.push_back(h_z_asym_wo_pvs);
   ListTH1F.push_back(h_z_asym_12);
   ListTH1F.push_back(h_z_asym_only_pvs_12);
   ListTH1F.push_back(h_BIB_ACselected_events);
   ListTH1F.push_back(h_BIB_CAselected_events);
   ListTH1F.push_back(h_BIB_ACselected_events_309314);
   ListTH1F.push_back(h_BIB_CAselected_events_309314);


   ListTH1F.push_back(h_HLT_events);
   ListTH1F.push_back(h_HLT_beam1Like_events); 
   ListTH1F.push_back(h_HLT_beam2Like_events); 
   ListTH1F.push_back(h_HLT_beam1Like_events_15min); 
   ListTH1F.push_back(h_HLT_beam2Like_events_15min); 

   ListTH1F.push_back(h_HLT_and_AC);
   ListTH1F.push_back(h_HLT_and_CA);
   ListTH1F.push_back(h_HLTbeam1Like_triggered_events_302737);
   ListTH1F.push_back(h_HLTbeam2Like_triggered_events_302737);

   // define output tree
   cout << "outputfile_:" << outputfile_ << endl;
   outputFile = new TFile(outputfile_.c_str(), "RECREATE");

   // txt file for run vs timestamp
   //myfile.open("run_vs_timestamp_inclusive_BCM.txt");
   //fileACPrescale.open("run_vs_ACPrescale.txt");
   //fileCAPrescale.open("run_vs_CAPrescale.txt");
   //fileACPrescale.open("run_vs_ACLikeBIB.txt");
   //fileCAPrescale.open("run_vs_CALikeBIB.txt");
   //fileACPrescale.open("run_vs_ACLikeBIB_working.txt");
   //fileCAPrescale.open("run_vs_CALikeBIB_working.txt");
 
    //myfile.open("bugfixing_302737_beam1Like.txt");
    //myfile2.open("bugfixing_302737_beam2Like.txt");
    //myfile2.open("run_vs_timestamp_inclusive_HLT.txt");
    
    //myfile.open("HLTprescale_allruns.txt");
}

void MySelector::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

Bool_t MySelector::Process(Long64_t entry)
{
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // It can be passed to either MySelector::GetEntry() or TBranch::GetEntry()
   // to read either all or the required parts of the data. When processing
   // keyed objects with PROOF, the object is already loaded and is available
   // via the fObject pointer.
   //
   // This function should contain the "body" of the analysis. It can contain
   // simple or elaborate selection criteria, run algorithms on the data
   // of the event and typically fill histograms.
   //
   // The processing can be stopped by calling Abort().
   //
   // Use fStatus to set the return value of TTree::Process().
   //
   // The return value is currently not used.

   // print some information about the current entry
  
   //std::cout << "Processing Entry number" << entry << std::endl;
   // increase the total number of entries
  //  ++fNumberOfEvents;


   // Tell the TTreeReader to get the data for the entry number "entry" in the current tree:
   fReader.SetLocalEntry(entry);


  // compute the total size of all events; dereference the TTreeReaderValue using * to get the value it refers to, just like an iterator.

//   std::cout << "Event Number: " << *fEventNumber << std::endl;
//     std::cout << "Run Number: " << *fRunNumber << std::endl;
//     std::cout << "LB Number: " << *fLBNumber << std::endl;
//      std::cout << "bcid: " << *fbcid << std::endl;





   h_all_events->Fill(*fRunNumber);

   std::string run_number = std::to_string(*fRunNumber);
   char const *char_run_number = run_number.c_str(); 

   std::string LB_number = std::to_string(*fLBNumber); // Lumi block number
   char const *char_LB_number = LB_number.c_str();

   // Get the number of good lumi blocks from rootrc file assigned in 'setting' to a variable 'char_run_number', 1 is the default value.
   int NLB = settings->GetValue(char_run_number, 1);
   double perSec = (double) NLB*60; // duration in seconds of the run
   double weight = (double)1/perSec; // when normalize to the Lumi blocks; weight is a inverse of the duration to get the average event rate
   double min = 60; // min = 60 seconds
   double perLB = (double)1/min; // when normalize to 60 seconds

   double prescaled = 0;
   double ACprescale = 0;
   double CAprescale = 0;
   double per_each_LB = 0;

   
   int LBstartTime = time_settings->GetValue(char_run_number, 0); // LBstartTime is the earliest time since BCM UI triggered events it is written in the rootrc file linked to 'time_setting'.

   // The duration of 15 lumi blocks (15 minutes) since the beginning of the run
   int LB15min = LBstartTime + 900;
   // normalize to the 15 minutes, weight is the inverse of the lumi blocks.
   double norm_15min = (double)1/900; 


   int LBstartTime_AC = BIB_settings_AC->GetValue(char_run_number, 0); // LBstartTime_AC is the earliest time since BIB event selection with SCT. 
   int LB15min_AC = LBstartTime_AC + 900;
   double norm_15min_AC = (double)1/900; 

   int LBstartTime_CA = BIB_settings_CA->GetValue(char_run_number, 0); // LBstartTime_CA is the earliest time since BIB event selection with SCT. 
   int LB15min_CA = LBstartTime_CA + 900;
   double norm_15min_CA = (double)1/900; 

   int HLTstartTime = HLT_settings->GetValue(char_run_number, 0); // HLT_settings is the earliest time since HLT UI triggered events.
   int HLT15min = HLTstartTime + 900;
 
   int nv, pv; 
   nv = fHitsOnDisks->at(6) + fHitsOnDisks->at(7); // nv = End Cap C disk 7 + 8
   pv = fHitsOnDisks->at(14) + fHitsOnDisks->at(15); // pv = End Cap A disk 7 + 8

    
   // z asymmetry
   double z_asym = 1000;
   if (pv > 0 || nv > 0)
  	z_asym = (double)(pv-nv)/(pv+nv);


   // z asymmetry given by disk 1,2
   int nv_12, pv_12;
   nv_12 = fHitsOnDisks->at(0) + fHitsOnDisks->at(1); // nv_12 = End Cap C disk 1 + 2
   pv_12 = fHitsOnDisks->at(8) + fHitsOnDisks->at(9); // pv_12 = End Cap A disk 1 + 2

   double z_asym_12 = 1000;
   if(pv_12 > 0 || nv_12 > 0)
	z_asym_12 = (double)(pv_12-nv_12)/(pv_12+nv_12);

   // z asymmetry given by individual disks.
   double z_asym_1 = 1000; // disk 1
   if(fHitsOnDisks->at(8) > 0 || fHitsOnDisks->at(0) > 0)
 	z_asym_1 = (double)(fHitsOnDisks->at(8) - fHitsOnDisks->at(0))/(fHitsOnDisks->at(8) + fHitsOnDisks->at(0));

   double z_asym_2 = 1000; // disk 2
   if(fHitsOnDisks->at(9) > 0 || fHitsOnDisks->at(1) > 0)
 	z_asym_2 = (double)(fHitsOnDisks->at(9) - fHitsOnDisks->at(1))/(fHitsOnDisks->at(9) + fHitsOnDisks->at(1));

   double z_asym_3 = 1000; // disk 3
   if(fHitsOnDisks->at(10) > 0 || fHitsOnDisks->at(2) > 0)
 	z_asym_3 = (double)(fHitsOnDisks->at(10) - fHitsOnDisks->at(2))/(fHitsOnDisks->at(10) + fHitsOnDisks->at(2));

   double z_asym_4 = 1000; // disk 4
   if(fHitsOnDisks->at(11) > 0 || fHitsOnDisks->at(3) > 0)
 	z_asym_4 = (double)(fHitsOnDisks->at(11) - fHitsOnDisks->at(3))/(fHitsOnDisks->at(11) + fHitsOnDisks->at(3));

   double z_asym_5 = 1000; // disk 5
   if(fHitsOnDisks->at(12) > 0 || fHitsOnDisks->at(4) > 0)
 	z_asym_5 = (double)(fHitsOnDisks->at(12) - fHitsOnDisks->at(4))/(fHitsOnDisks->at(12) + fHitsOnDisks->at(4));

   double z_asym_6 = 1000; // disk 6
   if(fHitsOnDisks->at(13) > 0 || fHitsOnDisks->at(5) > 0)
 	z_asym_6 = (double)(fHitsOnDisks->at(13) - fHitsOnDisks->at(5))/(fHitsOnDisks->at(13) + fHitsOnDisks->at(5));
	
   double z_asym_9 = 1000; // disk 7
   if(fHitsOnDisks->at(16) > 0 || fHitsOnDisks->at(17) > 0) // index 16: ECA disk9, index 17: ECC disk 9
	z_asym_9 = (double)(fHitsOnDisks->at(16) - fHitsOnDisks->at(17))/(fHitsOnDisks->at(16) + fHitsOnDisks->at(17));




   if(*fRunNumber == 298771 && *fLBNumber == 264) {
  	h_z_asym_only_pvs->Fill(z_asym);
        h_z_asym_only_pvs_12->Fill(z_asym_12);
   }

   //fileACPrescale << *fRunNumber << ": " << *ftimeStamp << "\n";
   //fileCAPrescale << *fRunNumber << ": " << *ftimeStamp << "\n";


   // Recover BCM trigger rate with BIB event selection based on SCT
   if( pv >= 25 && z_asym >= 0.5) { // BIB event selection for beam 2 events
	if(z_asym == 1000) // error message
		std::cout << "BIB selection pv: z_asym == 1000" << std::endl;
	else {
		h_BIB_CAselected_events->Fill(*fRunNumber, weight);
		h_BIB_ECAHit78_beam2->Fill(*fRunNumber, pv, weight);
		//fileCAPrescale << *fRunNumber << ": " << *ftimeStamp << "\n";

		// Event rate is normalized to the first 15 lumi blocks.
		if(*ftimeStamp >= LBstartTime_CA && *ftimeStamp <= LB15min_CA)	
			h_BIB_CAselected_events_15min->Fill(LBstartTime_CA, norm_15min_CA);
	
		// for a specific run 309314, the histogram 'h_BIB_CAselected_events_309314' is plotted with respect to lumi block. The event rate is normalized to the duration of a unit lumi block, 60 seconds. 
		if(*fRunNumber == 309314) {
			h_BIB_CAselected_events_309314->Fill(*fLBNumber, perLB);
			h_BIB_ECAHit78_beam2_309314->Fill(*fLBNumber, pv, perLB);
		}
	}
    }
   if( nv >= 25 && z_asym <= -0.5) { // BIB event selection for beam 1 events
	if(z_asym == 1000)
		std::cout << "BIB selection nv: z_asym == 1000" << std::endl;
	else {
		h_BIB_ACselected_events->Fill(*fRunNumber, weight);
		h_BIB_ECCHit78_beam1->Fill(*fRunNumber, nv, weight);
		//fileACPrescale << *fRunNumber << ": " << *ftimeStamp << "\n";
		
		if(*ftimeStamp >= LBstartTime_AC && *ftimeStamp <= LB15min_AC)
			h_BIB_ACselected_events_15min->Fill(LBstartTime_AC, norm_15min_AC);

		if(*fRunNumber == 309314) {
			h_BIB_ACselected_events_309314->Fill(*fLBNumber, perLB);
			h_BIB_ECCHit78_beam1_309314->Fill(*fLBNumber, nv, perLB);
		}
	}
    }
 



if( *fpassesACTrigger == true || *fpassesCATrigger == true) { // if this event passes BCM AC or BCM CA UI trigger.
   if(*fRunNumber == 298771 && *fLBNumber == 264 ) {
   	h_z_asym_wo_pvs->Fill(z_asym);
    	h_z_asym_12->Fill(z_asym_12);
   }
   // set prescale
   if(*fpassesACTrigger == true) {
	ACprescale = *fBCMACprescale;
	prescaled = ACprescale*weight; // 'prescaled' is prescale + normalize over the total number of good lumi blocks.
        per_each_LB = ACprescale*perLB;
	//fileACPrescale << *fRunNumber << ": " << ACprescale << "\n";
   }
   if(*fpassesCATrigger == true) {
        CAprescale = *fBCMCAprescale;
	prescaled = CAprescale*weight;
	per_each_LB = CAprescale*perLB;
	//fileCAPrescale << *fRunNumber << ": " << CAprescale << "\n";
   }

   if(*ftimeStamp >= LBstartTime && *ftimeStamp <= LB15min) { // collecting events for 15 mins
	if(*fpassesACTrigger == true) {
		//h_ACtriggered_events_15min->Fill(LBstartTime, norm_15min);
		h_ACtriggered_events_15min->Fill(LBstartTime, norm_15min * ACprescale);
		if((nv >= 25) && (z_asym <= -0.5)) {
			h_ACselected_events_15min->Fill(LBstartTime, norm_15min * ACprescale);
			h_ECCHit78_beam1_15min->Fill(*fRunNumber, nv, norm_15min * ACprescale);
 			h_ECAHit78_beam1_15min->Fill(*fRunNumber, pv, norm_15min * ACprescale);
		}
	}
	
	if(*fpassesCATrigger == true) {
		h_CAtriggered_events_15min->Fill(LBstartTime, norm_15min * CAprescale);
		if((pv >= 25) && (z_asym >= 0.5)) {
			h_CAselected_events_15min->Fill(LBstartTime, norm_15min * CAprescale);
			h_ECCHit78_beam2_15min->Fill(*fRunNumber, nv, norm_15min * CAprescale);
			h_ECAHit78_beam2_15min->Fill(*fRunNumber, pv, norm_15min * CAprescale);
		}
	}
   }
   //myfile << *fRunNumber << ": " << *ftimeStamp << "\n";

   if(*fRunNumber == 301918) {
	h_pressure_bump_run_2->Fill(*fbcid, *fLBNumber);	
	if(*fpassesACTrigger == true) {
		h_ACtriggered_events_301918->Fill(*fLBNumber, per_each_LB);
		h_ECCHit78_beam1_301918->Fill(*fLBNumber, nv, per_each_LB);
	}
	if(*fpassesCATrigger == true) {
		h_CAtriggered_events_301918->Fill(*fLBNumber, per_each_LB);
		h_ECAHit78_beam2_301918->Fill(*fLBNumber, pv, per_each_LB);
	}
    }


   if(*fRunNumber == 309314) {
	if(*fpassesACTrigger == true) {
		h_ACtriggered_events_309314->Fill(*fLBNumber, per_each_LB);
		h_ECCHit78_beam1_309314->Fill(*fLBNumber, nv, per_each_LB);
	}
	if(*fpassesCATrigger == true) {
		h_CAtriggered_events_309314->Fill(*fLBNumber, per_each_LB);
		h_ECAHit78_beam2_309314->Fill(*fLBNumber, pv, per_each_LB);
	}
    }


    if(*fRunNumber == 302737) {
	if(*fpassesACTrigger == true || *fpassesCATrigger == true) {
		h_BCMtrigger_z_asym_302737->Fill(*fLBNumber, z_asym);

		if(*fpassesACTrigger == true) {
			h_ACtriggered_events_302737->Fill(*fLBNumber, per_each_LB);
			h_ECCHit78_beam1_302737->Fill(*fLBNumber, nv, per_each_LB);
			h_bcid_vs_lb_AC_302737->Fill(*fbcid, *fLBNumber, per_each_LB);
			h_ACtrigger_z_asym_302737->Fill(*fLBNumber, z_asym, per_each_LB);
		}
		if(*fpassesCATrigger == true) {
			h_CAtriggered_events_302737->Fill(*fLBNumber, per_each_LB);
			h_ECAHit78_beam2_302737->Fill(*fLBNumber, pv, per_each_LB);
			h_bcid_vs_lb_CA_302737->Fill(*fbcid, *fLBNumber, per_each_LB);
			h_CAtrigger_z_asym_302737->Fill(*fLBNumber, z_asym, per_each_LB);
		}
	}
	
    }


    if(*fRunNumber == 304494) {
	if(*fpassesACTrigger == true) {
		h_ACtriggered_events_304494->Fill(*fLBNumber, per_each_LB);
		h_ECCHit78_beam1_304494->Fill(*fLBNumber, nv, per_each_LB);
	}
	if(*fpassesCATrigger == true) {
		h_CAtriggered_events_304494->Fill(*fLBNumber, per_each_LB);
		h_ECAHit78_beam2_304494->Fill(*fLBNumber, pv, per_each_LB);
	}

    //if(*fRunNumber == 304337) {
    //	std::cout << *fLBNumber << ": " << peaklumi_304337->GetValue(char_LB_number, 1.0) << std::endl;
    //}


    }

    if(*fRunNumber == 304337) {
	double delivered_lumi = peaklumi_304337->GetValue(char_LB_number, 1.0);
	if(*fpassesACTrigger == true) {
		h_ACtriggered_events_304337->Fill(*fLBNumber, per_each_LB);
		h_ECCHit78_beam1_304337->Fill(*fLBNumber, nv, per_each_LB);
		h_ECAHit78_beam1_304337->Fill(*fLBNumber, pv, per_each_LB);
         	h_z_asym_beam1_304337->Fill(*fLBNumber, z_asym);
	
	 	if( nv >= 25 && z_asym <= -0.5) {
			h_ACselected_events_304337->Fill(*fLBNumber, per_each_LB);
			h_lumi_ECCHit78_beam1_304337->Fill(delivered_lumi, nv, per_each_LB);
			h_BIB_ECCHit78_beam1_304337->Fill(*fLBNumber, nv, per_each_LB);
		}
	}
	if(*fpassesCATrigger == true) {
		h_CAtriggered_events_304337->Fill(*fLBNumber, per_each_LB);
		h_ECAHit78_beam2_304337->Fill(*fLBNumber, pv, per_each_LB);
		h_ECCHit78_beam2_304337->Fill(*fLBNumber, nv, per_each_LB);
		h_z_asym_beam2_304337->Fill(*fLBNumber, z_asym);

	 	if( pv >= 25 && z_asym >= 0.5) {
			h_CAselected_events_304337->Fill(*fLBNumber, per_each_LB);
		}

	}
    }


    if(*fRunNumber == 307195) {
	if(*fpassesACTrigger == true) {
		h_ECCHit78_beam1_307195->Fill(*fLBNumber, nv, per_each_LB);
		h_ECAHit78_beam1_307195->Fill(*fLBNumber, pv, per_each_LB);
	
	}
	if(*fpassesCATrigger == true) {
		h_ECAHit78_beam2_307195->Fill(*fLBNumber, pv, per_each_LB);
		h_ECCHit78_beam2_307195->Fill(*fLBNumber, nv, per_each_LB);

	}
    }

    if(*fRunNumber == 310738) {
	if(*fpassesACTrigger == true) {
		h_ECCHit78_beam1_310738->Fill(*fLBNumber, nv, per_each_LB);
		h_ECAHit78_beam1_310738->Fill(*fLBNumber, pv, per_each_LB);
	
	}
	if(*fpassesCATrigger == true) {
		h_ECAHit78_beam2_310738->Fill(*fLBNumber, pv, per_each_LB);
		h_ECCHit78_beam2_310738->Fill(*fLBNumber, nv, per_each_LB);

	}
    }




   if(*fRunNumber == 298771) {
	if(*fpassesACTrigger == true) {
		h_ACtriggered_events_298771->Fill(*fLBNumber, per_each_LB);
		h_ECCHit78_beam1_298771->Fill(*fLBNumber, nv, per_each_LB);
	}
	if(*fpassesCATrigger == true) {
		h_CAtriggered_events_298771->Fill(*fLBNumber, per_each_LB);
		h_ECAHit78_beam2_298771->Fill(*fLBNumber, pv, per_each_LB);
	}
    }


    if(*fRunNumber == 299147) {
	if(*fpassesACTrigger == true) {
		h_ACtriggered_events_299147->Fill(*fLBNumber, per_each_LB);
		h_ECCHit78_beam1_299147->Fill(*fLBNumber, nv, per_each_LB);
		h_ECAHit78_beam1_299147->Fill(*fLBNumber, pv, per_each_LB);
		h_z_asym_beam1_299147->Fill(*fLBNumber, z_asym);

	 	if( nv >= 25 && z_asym <= -0.5) {
			h_ACselected_events_299147->Fill(*fLBNumber, per_each_LB);
		}
	}
	if(*fpassesCATrigger == true) {
		h_CAtriggered_events_299147->Fill(*fLBNumber, per_each_LB);
		h_ECAHit78_beam2_299147->Fill(*fLBNumber, pv, per_each_LB);
		h_ECCHit78_beam2_299147->Fill(*fLBNumber, nv, per_each_LB);
		h_z_asym_beam2_299147->Fill(*fLBNumber, z_asym);

	 	if( pv >= 25 && z_asym >= 0.5) {
			h_CAselected_events_299147->Fill(*fLBNumber, per_each_LB);
		}

	}
    }

   // Same Fill in different runs

   if(*fRunNumber == 302831) {
	if(*fpassesACTrigger == true) {
		h_ECCHit78_beam1_302831->Fill(*fLBNumber, nv, per_each_LB);
		h_ECAHit78_beam1_302831->Fill(*fLBNumber, pv, per_each_LB);
	}
	if(*fpassesCATrigger == true) {
		h_ECAHit78_beam2_302831->Fill(*fLBNumber, pv, per_each_LB);
		h_ECCHit78_beam2_302831->Fill(*fLBNumber, nv, per_each_LB);
	}
    }

    if(*fRunNumber == 302829) {
	if(*fpassesACTrigger == true) {
		h_ECCHit78_beam1_302829->Fill(*fLBNumber, nv, per_each_LB);
		h_ECAHit78_beam1_302829->Fill(*fLBNumber, pv, per_each_LB);
	}
	if(*fpassesCATrigger == true) {
		h_ECAHit78_beam2_302829->Fill(*fLBNumber, pv, per_each_LB);
		h_ECCHit78_beam2_302829->Fill(*fLBNumber, nv, per_each_LB);
	}
    }


   if(*fRunNumber == 300687) {
	if(*fpassesACTrigger == true) {
		h_ACtriggered_events_300687->Fill(*fLBNumber, per_each_LB);
		h_ECCHit78_beam1_300687->Fill(*fLBNumber, nv, per_each_LB);
	}
	if(*fpassesCATrigger == true) {
		h_CAtriggered_events_300687->Fill(*fLBNumber, per_each_LB);
		h_ECAHit78_beam2_300687->Fill(*fLBNumber, pv, per_each_LB);
	}
    }

     if(*fpassesACTrigger == true) {
	// hit of each modules vs runs
		outer_module_ECCdisk6_hit_vs_run_beam1->Fill(*fRunNumber, fHitsOnModulesOfDisk6->at(0) , prescaled/0.3803041); // ECC disk 6, event weight = (weight)/(area of the ring of the module)
		outer_module_ECAdisk6_hit_vs_run_beam1->Fill(*fRunNumber, fHitsOnModulesOfDisk6->at(3)  , prescaled/0.3803041); // ECA disk 6

		middle_module_ECCdisk6_hit_vs_run_beam1->Fill(*fRunNumber, fHitsOnModulesOfDisk6->at(1) , prescaled/0.2468402); // ECC disk 6
		middle_module_ECAdisk6_hit_vs_run_beam1->Fill(*fRunNumber, fHitsOnModulesOfDisk6->at(4) , prescaled/0.2468402); // ECA disk 6

		inner_module_ECCdisk6_hit_vs_run_beam1->Fill(*fRunNumber, fHitsOnModulesOfDisk6->at(2)  , prescaled/0.1204762); // ECC disk 6
		inner_module_ECAdisk6_hit_vs_run_beam1->Fill(*fRunNumber, fHitsOnModulesOfDisk6->at(5)  , prescaled/0.1204762); // ECA disk 6

      }
  
      if(*fpassesCATrigger == true) {
	// hit of each modules vs runs
		outer_module_ECCdisk6_hit_vs_run_beam2->Fill(*fRunNumber, fHitsOnModulesOfDisk6->at(0) , prescaled/0.3803041); // ECC disk 6 weight/area of the ring of the module
		outer_module_ECAdisk6_hit_vs_run_beam2->Fill(*fRunNumber, fHitsOnModulesOfDisk6->at(3) , prescaled/0.3803041); // ECC disk 6

		middle_module_ECCdisk6_hit_vs_run_beam2->Fill(*fRunNumber, fHitsOnModulesOfDisk6->at(1) , prescaled/0.2468402); // ECC disk 6
		middle_module_ECAdisk6_hit_vs_run_beam2->Fill(*fRunNumber, fHitsOnModulesOfDisk6->at(4) , prescaled/0.2468402); // ECA disk 6

		inner_module_ECCdisk6_hit_vs_run_beam2->Fill(*fRunNumber, fHitsOnModulesOfDisk6->at(2) , prescaled/0.1204762); // ECC disk 6
		inner_module_ECAdisk6_hit_vs_run_beam2->Fill(*fRunNumber, fHitsOnModulesOfDisk6->at(5)  , prescaled/0.1204762); // ECA disk 6

     }


    // BCM UI trigger and hit occupancy with respect to run numbers
    if(*fpassesACTrigger == true) { 
	h_ACtrigger->Fill(*fbcid, *fLBNumber);
        h_triggered_events->Fill(*fRunNumber, prescaled);
    	h_ACtriggered_events->Fill(*fRunNumber, prescaled);
        h_AC_seconds->Fill(*ftimeStamp); 

	// Hit multiplicity
	h_ECCHit78_beam1->Fill(*fRunNumber, nv, prescaled);
	h_ECAHit78_beam1->Fill(*fRunNumber, pv, prescaled);
	h_z_asym_beam1->Fill(*fRunNumber, z_asym);

    }
	
    if(*fpassesCATrigger == true) {
	h_CAtrigger->Fill(*fbcid, *fLBNumber);
 	h_triggered_events->Fill(*fRunNumber, prescaled);
 	h_CAtriggered_events->Fill(*fRunNumber, prescaled);
        h_CA_seconds->Fill(*ftimeStamp);

	// Hit multiplicity
 	h_ECAHit78_beam2->Fill(*fRunNumber, pv, prescaled);
    	h_ECCHit78_beam2->Fill(*fRunNumber, nv, prescaled);
	h_z_asym_beam2->Fill(*fRunNumber, z_asym);

    
    }

   
    // BIB event selection: BIB event rate  with respect to run numbers
    if(*fpassesACTrigger == true && nv >= 25 && z_asym <= -0.5) {
	if(z_asym == 1000)
		std::cout << "AC:z_asym == 1000" << std::endl;
	else
		h_ACselected_events->Fill(*fRunNumber, prescaled);
    }

    if(*fpassesCATrigger == true && pv >= 25 && z_asym >= 0.5) {
	if(z_asym == 1000)
		std::cout << "CA:z_asym == 1000" << std::endl;
	else 
		h_CAselected_events->Fill(*fRunNumber, prescaled);
    }

    if( pv >= 25 && z_asym >= 0.5) {
	if(z_asym == 1000)
		std::cout << "BIB selection pv: z_asym == 1000" << std::endl;
	else
		h_PVselected_events->Fill(*fRunNumber, prescaled);
    }
   if( nv >= 25 && z_asym <= -0.5) {
	if(z_asym == 1000)
		std::cout << "BIB selection nv: z_asym == 1000" << std::endl;
	else
		h_NVselected_events->Fill(*fRunNumber, prescaled);
    }
  

   // Event selection by disk 1, 2
   if(*fpassesACTrigger == true && nv_12 >= 25 && z_asym_12 <= -0.5) {
	if(z_asym_12 == 1000)	
		std::cout << "AC:z_asym_12 == 1000" << std::endl;
	else 
		h_ACselected_events_12->Fill(*fRunNumber, prescaled);
   }
  if(*fpassesCATrigger == true && pv_12 >= 25 && z_asym_12 <= -0.5) {
	if(z_asym_12 == 1000)	
		std::cout << "CA:z_asym_12 == 1000" << std::endl;
	else 
		h_CAselected_events_12->Fill(*fRunNumber, prescaled);
   }
     
 }


   // HLT: prescale needs to be taken into account.
   if(*fpassesHLT) {
 	double HLTprescale = *fHLTprescale;
        double prescaled_HLT = HLTprescale*weight;
	// perLB = 1/min
	double per_each_LB_HLT = HLTprescale*perLB;

	//myfile << *fRunNumber << ": "<< *fHLTprescale << "\n";
	//myfile2 << *fRunNumber << ": " << *ftimeStamp << "\n";
	
	h_HLT_events->Fill(*fRunNumber, prescaled_HLT);
	h_HLT_z_asym->Fill(*fRunNumber, z_asym);

	if(*fRunNumber == 298771) {
		h_HLT_z_asym_298771->Fill(*fLBNumber, z_asym);
		h_HLT_hit_298771->Fill(*fLBNumber, nv+pv);
		h_bcid_vs_lb_HLT_298771->Fill(*fbcid, *fLBNumber);
		//std::cout << "298771 disk 9: " << fHitsOnDisks->at(16) << " " << fHitsOnDisks->at(17) << std::endl;
	}

        if(*fRunNumber == 307195) {
		h_bcid_vs_pv_HLT_307195->Fill(*fbcid, pv);
		h_bcid_vs_nv_HLT_307195->Fill(*fbcid, nv);
		h_lb_vs_HitECA78_beam2Like_307195->Fill(*fLBNumber, pv);
		h_lb_vs_HitECC78_beam1Like_307195->Fill(*fLBNumber, nv);
	}

	if(*fRunNumber == 309314) {
		h_bcid_vs_pv_HLT_309314->Fill(*fbcid, pv);
		h_bcid_vs_nv_HLT_309314->Fill(*fbcid, nv);
		h_lb_vs_HitECA78_beam2Like_309314->Fill(*fLBNumber, pv);
		h_lb_vs_HitECC78_beam1Like_309314->Fill(*fLBNumber, nv);
	}


	// Study of the anomaly run 302737
    	// the event weight is not "per_each_LB_HLT" since the HLTprescale is very high for 302737
	//if((*fRunNumber == 302737) && (*fbcid < 50)) {
	//if((*fRunNumber == 302737) && (z_asym_1 > 0.5 || z_asym_1 < -0.5)) {
	if(*fRunNumber == 302737) {
		
		// disk 7,8
		if(z_asym > 0.5) {
			h_bcid_vs_nv_HLT_302737_zlarger05->Fill(*fbcid, nv);
			h_bcid_vs_pv_HLT_302737_zlarger05->Fill(*fbcid, pv);
		}
		if(z_asym < -0.5) {
			h_bcid_vs_nv_HLT_302737_zsmaller05->Fill(*fbcid, nv);
			h_bcid_vs_pv_HLT_302737_zsmaller05->Fill(*fbcid, pv);
		}

		// disk 1
		if(z_asym_1 > 0.5 || z_asym_1 < -0.5) {
			h_bcid_pv_HLT_302737_disk1_largez->Fill(*fbcid, fHitsOnDisks->at(8));
			h_bcid_nv_HLT_302737_disk1_largez->Fill(*fbcid, fHitsOnDisks->at(0));
		}
		// disk 2
		if(z_asym_2 > 0.5 || z_asym_2 < -0.5) {
			h_bcid_pv_HLT_302737_disk2_largez->Fill(*fbcid, fHitsOnDisks->at(9));
			h_bcid_nv_HLT_302737_disk2_largez->Fill(*fbcid, fHitsOnDisks->at(1));
		}
		// disk 3
		if(z_asym_3 > 0.5 || z_asym_3 < -0.5) {
			h_bcid_pv_HLT_302737_disk3_largez->Fill(*fbcid, fHitsOnDisks->at(10));
			h_bcid_nv_HLT_302737_disk3_largez->Fill(*fbcid, fHitsOnDisks->at(2));
		}
		// disk 4
		if(z_asym_4 > 0.5 || z_asym_4 < -0.5) {
			h_bcid_pv_HLT_302737_disk4_largez->Fill(*fbcid, fHitsOnDisks->at(11));
			h_bcid_nv_HLT_302737_disk4_largez->Fill(*fbcid, fHitsOnDisks->at(3));
		}
		// disk 5
		if(z_asym_5 > 0.5 || z_asym_5 < -0.5) {
			h_bcid_pv_HLT_302737_disk5_largez->Fill(*fbcid, fHitsOnDisks->at(12));
			h_bcid_nv_HLT_302737_disk5_largez->Fill(*fbcid, fHitsOnDisks->at(4));
		}
		// disk 6
		if(z_asym_6 > 0.5 || z_asym_6 < -0.5) {
			h_bcid_pv_HLT_302737_disk6_largez->Fill(*fbcid, fHitsOnDisks->at(13));
			h_bcid_nv_HLT_302737_disk6_largez->Fill(*fbcid, fHitsOnDisks->at(5));
		}
		// disk 9
		if(z_asym_9 > 0.5 || z_asym_9 < -0.5) {
			h_bcid_pv_HLT_302737_disk9_largez->Fill(*fbcid, fHitsOnDisks->at(16));
			h_bcid_nv_HLT_302737_disk9_largez->Fill(*fbcid, fHitsOnDisks->at(17));
		}
			


		h_HLT_z_asym_302737->Fill(*fLBNumber, z_asym);
  		h_HLT_hit_302737->Fill(*fLBNumber, nv+pv);
		h_bcid_vs_lb_HLT_302737->Fill(*fbcid, *fLBNumber);
		h_bcid_vs_pv_HLT_302737->Fill(*fbcid, pv);
		h_bcid_vs_nv_HLT_302737->Fill(*fbcid, nv);

		h_bcid_vs_pv_HLT_302737_disk1->Fill(*fbcid, fHitsOnDisks->at(8));
		h_bcid_vs_pv_HLT_302737_disk2->Fill(*fbcid, fHitsOnDisks->at(9));
		h_bcid_vs_pv_HLT_302737_disk3->Fill(*fbcid, fHitsOnDisks->at(10));
		h_bcid_vs_pv_HLT_302737_disk4->Fill(*fbcid, fHitsOnDisks->at(11));
		h_bcid_vs_pv_HLT_302737_disk5->Fill(*fbcid, fHitsOnDisks->at(12));
		h_bcid_vs_pv_HLT_302737_disk6->Fill(*fbcid, fHitsOnDisks->at(13));
		h_bcid_vs_pv_HLT_302737_disk9->Fill(*fbcid, fHitsOnDisks->at(16));
		
		h_bcid_vs_nv_HLT_302737_disk1->Fill(*fbcid, fHitsOnDisks->at(0));
		h_bcid_vs_nv_HLT_302737_disk2->Fill(*fbcid, fHitsOnDisks->at(1));
		h_bcid_vs_nv_HLT_302737_disk3->Fill(*fbcid, fHitsOnDisks->at(2));
		h_bcid_vs_nv_HLT_302737_disk4->Fill(*fbcid, fHitsOnDisks->at(3));
		h_bcid_vs_nv_HLT_302737_disk5->Fill(*fbcid, fHitsOnDisks->at(4));
		h_bcid_vs_nv_HLT_302737_disk6->Fill(*fbcid, fHitsOnDisks->at(5));
		h_bcid_vs_nv_HLT_302737_disk9->Fill(*fbcid, fHitsOnDisks->at(17));
	
		h_bcid_vs_hit_HLT_302737->Fill(*fbcid, pv+nv);

	   	if(z_asym >= -0.5 && z_asym <= 0.5) {

			h_hit_vs_disks->Fill(-8, fHitsOnDisks->at(7), 1/0.46224); // ECC disk 8
			h_hit_vs_disks->Fill(-7, fHitsOnDisks->at(6), 1/0.62714);
			h_hit_vs_disks->Fill(-6, fHitsOnDisks->at(5), 1/0.74762);
			h_hit_vs_disks->Fill(-5, fHitsOnDisks->at(4), 1/0.74762);
			h_hit_vs_disks->Fill(-4, fHitsOnDisks->at(3), 1/0.74762);
			h_hit_vs_disks->Fill(-3, fHitsOnDisks->at(2), 1/0.74762);
			h_hit_vs_disks->Fill(-2, fHitsOnDisks->at(1), 1/0.74762);
			h_hit_vs_disks->Fill(-1, fHitsOnDisks->at(0), 1/0.62714); // ECC disk 1
			h_hit_vs_disks->Fill(1, fHitsOnDisks->at(8), 1/0.62714); // ECA disk 1
			h_hit_vs_disks->Fill(2, fHitsOnDisks->at(9), 1/0.74762);
			h_hit_vs_disks->Fill(3, fHitsOnDisks->at(10), 1/0.74762);
			h_hit_vs_disks->Fill(4, fHitsOnDisks->at(11), 1/0.74762);
			h_hit_vs_disks->Fill(5, fHitsOnDisks->at(12), 1/0.74762);
			h_hit_vs_disks->Fill(6, fHitsOnDisks->at(13), 1/0.74762);
			h_hit_vs_disks->Fill(7, fHitsOnDisks->at(14), 1/0.62714);
			h_hit_vs_disks->Fill(8, fHitsOnDisks->at(15), 1/0.46224); // ECA disk 8
		}

		if(nv >= 25 && z_asym <= -0.5) {
			h_bcid_vs_lb_HLTbeam1Like_302737->Fill(*fbcid, *fLBNumber);
			h_HLTbeam1Like_triggered_events_302737->Fill(*fLBNumber);
			h_HLTbeam1Like_z_asym_302737->Fill(*fLBNumber, z_asym);
			h_HLTbeam1Like_hit_302737->Fill(*fLBNumber, nv);
		}

		if(pv >= 25 && z_asym >= 0.5) {
			h_bcid_vs_lb_HLTbeam2Like_302737->Fill(*fbcid, *fLBNumber);
			h_HLTbeam2Like_triggered_events_302737->Fill(*fLBNumber);
			h_HLTbeam2Like_z_asym_302737->Fill(*fLBNumber, z_asym);
			h_HLTbeam2Like_hit_302737->Fill(*fLBNumber, pv);
		}
	} // end of run = 302737

	if(*fRunNumber == 304337) {
		h_HLT_z_asym_304337->Fill(*fLBNumber, z_asym);
	        h_HLT_hit_304337->Fill(*fLBNumber, pv+nv);	
	}
	
	// all runs, HLT
	h_ECCHit78_HLT->Fill(*fRunNumber, nv, prescaled_HLT);
	h_ECAHit78_HLT->Fill(*fRunNumber, pv, prescaled_HLT);

	// outer module
	outer_module_ECCdisk6_hit_vs_run->Fill(*fRunNumber, fHitsOnModulesOfDisk6->at(0) , prescaled_HLT/0.3803041); // ECC disk 6 weight/area of the ring of the module
	outer_module_ECAdisk6_hit_vs_run->Fill(*fRunNumber, fHitsOnModulesOfDisk6->at(3) , prescaled_HLT/0.3803041); // ECA disk 6

	// middle module
	middle_module_ECCdisk6_hit_vs_run->Fill(*fRunNumber, fHitsOnModulesOfDisk6->at(1) , prescaled_HLT/0.2468402); // ECC disk 6
	middle_module_ECAdisk6_hit_vs_run->Fill(*fRunNumber, fHitsOnModulesOfDisk6->at(4) , prescaled_HLT/0.2468402); // ECA disk 6

	// inner module
	inner_module_ECCdisk6_hit_vs_run->Fill(*fRunNumber, fHitsOnModulesOfDisk6->at(2) , prescaled_HLT/0.1204762); // ECC disk 6
	inner_module_ECAdisk6_hit_vs_run->Fill(*fRunNumber, fHitsOnModulesOfDisk6->at(5) , prescaled_HLT/0.1204762); // ECA disk 6



	// SCT BIB event selection to specify beam direction
	if(nv >= 25 && z_asym <= -0.5) {
		
		h_HLT_beam1Like_events->Fill(*fRunNumber, prescaled_HLT);
		h_ECCHit78_HLT_beam1Like->Fill(*fRunNumber, nv, prescaled_HLT);
		h_ECAHit78_HLT_upstream->Fill(*fRunNumber, pv, prescaled_HLT);

		// outer module
		outer_module_ECCdisk6_hit_vs_run_beam1Like->Fill(*fRunNumber, fHitsOnModulesOfDisk6->at(0) , prescaled_HLT/0.3803041); // ECC disk 6 weight/area of the ring of the module
		outer_module_ECAdisk6_hit_vs_run_beam1Like->Fill(*fRunNumber, fHitsOnModulesOfDisk6->at(3) , prescaled_HLT/0.3803041); // ECA disk 6

		// middle module
		middle_module_ECCdisk6_hit_vs_run_beam1Like->Fill(*fRunNumber, fHitsOnModulesOfDisk6->at(1) , prescaled_HLT/0.2468402); // ECC disk 6
		middle_module_ECAdisk6_hit_vs_run_beam1Like->Fill(*fRunNumber, fHitsOnModulesOfDisk6->at(4) , prescaled_HLT/0.2468402); // ECA disk 6

		// innder module
		inner_module_ECCdisk6_hit_vs_run_beam1Like->Fill(*fRunNumber, fHitsOnModulesOfDisk6->at(2) , prescaled_HLT/0.1204762); // ECC disk 6
		inner_module_ECAdisk6_hit_vs_run_beam1Like->Fill(*fRunNumber, fHitsOnModulesOfDisk6->at(5) , prescaled_HLT/0.1204762); // ECA disk 6


		if(*ftimeStamp >= HLTstartTime && *ftimeStamp <= HLT15min)
			h_HLT_beam1Like_events_15min->Fill(HLTstartTime, norm_15min * HLTprescale);

		if(*fpassesACTrigger) {
			h_HLT_and_AC->Fill(*fRunNumber, prescaled_HLT);
		}
	}

	if(pv >= 25 && z_asym >= 0.5) {

		h_HLT_beam2Like_events->Fill(*fRunNumber, prescaled_HLT);
		h_ECAHit78_HLT_beam2Like->Fill(*fRunNumber, pv, prescaled_HLT);
		h_ECCHit78_HLT_upstream->Fill(*fRunNumber, nv, prescaled_HLT);
	
		// outer module
		outer_module_ECCdisk6_hit_vs_run_beam2Like->Fill(*fRunNumber, fHitsOnModulesOfDisk6->at(0) , prescaled_HLT/0.3803041); // ECC disk 6 weight/area of the ring of the module
		outer_module_ECAdisk6_hit_vs_run_beam2Like->Fill(*fRunNumber, fHitsOnModulesOfDisk6->at(3) , prescaled_HLT/0.3803041); // ECA disk 6

		// middle module
		middle_module_ECCdisk6_hit_vs_run_beam2Like->Fill(*fRunNumber, fHitsOnModulesOfDisk6->at(1)  , prescaled_HLT/0.2468402); // ECC disk 6
		middle_module_ECAdisk6_hit_vs_run_beam2Like->Fill(*fRunNumber, fHitsOnModulesOfDisk6->at(4)  , prescaled_HLT/0.2468402); // ECA disk 6

		// inner module
		inner_module_ECCdisk6_hit_vs_run_beam2Like->Fill(*fRunNumber, fHitsOnModulesOfDisk6->at(2) , prescaled_HLT/0.1204762); // ECC disk 6
		inner_module_ECAdisk6_hit_vs_run_beam2Like->Fill(*fRunNumber, fHitsOnModulesOfDisk6->at(5) , prescaled_HLT/0.1204762); // ECA disk 6


		if(*ftimeStamp >= HLTstartTime && *ftimeStamp <= HLT15min)
			h_HLT_beam2Like_events_15min->Fill(HLTstartTime, norm_15min * HLTprescale);
		if(*fpassesCATrigger) {
			h_HLT_and_CA->Fill(*fRunNumber, prescaled_HLT);
		}
		
	}

   }

   // int N = fHitsOnDisks->size();
   // std::cout << "size of HitsOnDisks: " << N << std::endl;

   // print the number of hits on ECA disk 7, ie at(14)
   // if(fHitsOnDisks->at(14))
   //	std::cout << fHitsOnDisks->at(14) << std::endl;
   //
   //	ECC disk 1 = at(0)
   //	ECC disk 2 = at(1)
   //	...
   //	ECC disk 8 = at(7)
   //	---
   //	ECA disk 1 = at(8)
   //	ECA disk 2 = at(9)
   //	...
   //	ECA disk 8 = at(15)

   return kTRUE;
}

void MySelector::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void MySelector::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.

   // print the result
   //  std::cout << "Total number of events " << fNumberOfEvents << std::endl;
   outputFile->cd();

   // To write the histograms individually,
   // h_ACtrigger->Write();
   // myhisto->Write(); and so on.

   // Or to write the histograms in the for loop
   for( TH2F* th2f : ListTH2F)
	th2f->Write();

   for( TH1F* th1f : ListTH1F)
 	th1f->Write();


   // Any reprocessing of the histograms needs to be done in the MySelector::Terminate() function after writing them down.
   // TGraph
   gROOT->SetStyle("Plain");
   gStyle->SetPalette(51, 0);

   // For the canvas
   gStyle->SetCanvasColor(0);
   gStyle->SetCanvasBorderMode(0);
   
   // For the pad
   gStyle->SetPadColor(0);
   gStyle->SetPadTickX(1);
   gStyle->SetPadTickY(1);
   gStyle->SetPadBorderSize(2);
   gStyle->SetPadBorderMode(0);

   // For the frame
   gStyle->SetFrameBorderMode(0);

   // For the histo
   gStyle->SetMarkerSize(0.7);
   gStyle->SetMarkerStyle(20);
   gStyle->SetMarkerColor(1);

   // For the statistics box
   gStyle->SetOptStat(0);
   gStyle->SetOptFit(1011);  

   // For the Global title
   gStyle->SetOptTitle(0);
   gStyle->SetTitleColor(1);
   gStyle->SetTitleFillColor(10);
   gStyle->SetTitleTextColor(1);
   gStyle->SetTitleFont(42);
   gStyle->SetTitleFontSize(0.05);
   gStyle->SetTitleBorderSize(0);

   gROOT->ForceStyle();


  
   TGraph *g_BCM1 = new TGraph();
   TGraph *g_BCM2 = new TGraph();

   int Nbins = h_AC_seconds->GetNbinsX();
   //std::cout << Nbins << std::endl;

   int day_tmp = 0;
   int begin_day = h_AC_seconds->GetBinCenter(0);
   int g_bin = 0;

    for( int i = 0; i < Nbins; i++) { // starts from i = 1 because h_AC_seconds->GetBinContent(0) gives random large value 
 
  	//std::cout << "BinCenter: " << h_AC_seconds->GetBinCenter(i)  << " Content: " << h_AC_seconds->GetBinContent(i) << std::endl;
	if ( h_AC_seconds->GetBinCenter(i) < (begin_day + 86400) ) {
		 day_tmp += h_AC_seconds->GetBinContent(i);
	}
	else {
	 	//std::cout << begin_day << "	" << day_tmp << std::endl;
                if(day_tmp != 0) { 
			g_BCM1->SetPoint(g_bin, (double)begin_day, (double) day_tmp/84600); // day_tmp/84600 = average over day
			g_bin++;
		}

		begin_day = h_AC_seconds->GetBinCenter(i);
		day_tmp = h_AC_seconds->GetBinContent(i);
	}

   }

  std::cout << std::endl;
  g_bin = 0;
  day_tmp = 0;
  begin_day = h_CA_seconds->GetBinCenter(0);


 for( int i = 0; i < Nbins; i++) { // starts from i = 1 because h_AC_seconds->GetBinContent(0) gives random large value 
 
  	//std::cout << "BinCenter: " << h_AC_seconds->GetBinCenter(i)  << " Content: " << h_AC_seconds->GetBinContent(i) << std::endl;
	if ( h_CA_seconds->GetBinCenter(i) < (begin_day + 86400) ) {
		 day_tmp += h_CA_seconds->GetBinContent(i);
	}
	else {
	 	//std::cout << begin_day << "	" << day_tmp << std::endl;
                if(day_tmp != 0) { 
			g_BCM2->SetPoint(g_bin, (double)begin_day, (double) day_tmp/84600); // day_tmp/84600 = average over day
			g_bin++;
		}
		begin_day = h_CA_seconds->GetBinCenter(i);
		day_tmp = h_CA_seconds->GetBinContent(i);
		
	}

   }

   // not log scaled
   TCanvas *can = new TCanvas("can");
   TMultiGraph *mgBoth = new TMultiGraph();
   mgBoth->Add(g_BCM1, "P");
   mgBoth->Add(g_BCM2, "P");
   mgBoth->Draw("a fb");

   g_BCM1->SetMarkerStyle(21);
   g_BCM1->SetMarkerColor(kBlue);
   g_BCM2->SetMarkerStyle(20);
   g_BCM2->SetMarkerColor(kRed);

   mgBoth->GetYaxis()->SetTitle("Average rate [Hz]");
   mgBoth->GetXaxis()->SetTitle("Day in 2016");
   mgBoth->GetXaxis()->SetLimits(1461500000, 1478500000);
   //gPad->Modified();

   mgBoth->GetXaxis()->SetTimeDisplay(1);
   mgBoth->GetXaxis()->SetTimeFormat("%m/%d");
   gPad->Modified();

   mgBoth->GetYaxis()->SetTitleOffset(0.8);
   gPad->Modified();
 
   TLatex *ebeam = new TLatex();
   ebeam->SetNDC();
   ebeam->SetTextFont(42);
   ebeam->SetTextColor(kBlack);
   ebeam->SetTextSize(0.04);
   ebeam->DrawLatex(0.6, 0.84, "E_{beam}=6.5TeV");
   ebeam->DrawLatex(0.6, 0.78, "BCM trigger");
   //TLegend *tl = new TLegend(0.13, 0.77, 0.28, 0.87); // Top Left
   //TLegend *tl = new TLegend(0.70, 0.15, 0.85, 0.25); // Bottom right
   //TLegend *tl = new TLegend(0.6, 0.67, 0.75, 0.77); // Top right
   TLegend *tl = new TLegend(0.13, 0.15, 0.28, 0.25); // Top right
   tl->AddEntry(g_BCM1, "Beam1", "p");
   tl->AddEntry(g_BCM2, "Beam2", "p");
   tl->Draw();
   gPad->Modified();

   can->Update();
   can->Print("BCM_both.eps");

   can->Clear();

   //log scaled
   can->SetLogy(1);
   mgBoth->Draw("a fb");

   mgBoth->SetMaximum(50);
   mgBoth->SetMinimum(0.001);
  
   ebeam->DrawLatex(0.6, 0.84, "E_{beam}=6.5TeV");
   ebeam->DrawLatex(0.6, 0.78, "BCM trigger");
  
   tl->Draw();
   gPad->Modified();

   can->Update();
   can->Print("BCM_both_logy.eps");


  

   TCanvas *arr_c_BCM[2];
   arr_c_BCM[0] = new TCanvas("arr_c_BCM0");
   arr_c_BCM[1] = new TCanvas("arr_c_BCM1");

   TGraph *arr_tgraph[2];
   arr_tgraph[0] = g_BCM1;
   arr_tgraph[1] = g_BCM2;
  

   for( int i = 0; i < 2; i++) {
   	arr_c_BCM[i]->cd();
   	arr_tgraph[i]->SetMarkerStyle(20);
   	arr_tgraph[i]->SetMarkerColor(kRed);
   	arr_tgraph[i]->GetXaxis()->SetLimits(1461500000, 1478500000);
   	arr_tgraph[i]->GetXaxis()->SetTimeDisplay(1);
   	arr_tgraph[i]->GetXaxis()->SetTimeFormat("%m/%d");
   	arr_tgraph[i]->GetXaxis()->SetTitle("Day in 2016");
   	arr_tgraph[i]->GetYaxis()->SetTitle("Average rate [Hz]");
   	arr_tgraph[i]->Draw("AP"); // Draw Option singly "P" does not work. ->Empty Canvas

	std::string name = "BCM";
	name+= std::to_string(i+1);
        name+= ".eps";

   	arr_c_BCM[i]->Update();
   	arr_c_BCM[i]->Print(name.c_str());
   }

   for(auto can : arr_c_BCM)
	delete can;
   for(auto tg : arr_tgraph)
	delete tg;
   // end of plotting. Plots drawn in the end of this file is no longer in use. All the useful plots are drawn using python script in py/ directory.

   // Closing the outputFile, the root file.
   outputFile->Close();

   // Closing text files
   //myfile.close();
   //myfile2.close();
   //fileACPrescale.close();
   //fileCAPrescale.close();
}

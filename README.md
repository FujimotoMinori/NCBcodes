**********************************************************************
Processing the private ntuple with a macro
**********************************************************************

When the private ntuple is made and merged into a single root file, c++ 
macros, containing the variables of this root file, can be automatically
generated using TSelector with the following commands.

Setting up the root first 
$root -l
root [0] TFile *f = TFile::Open("MyNtuple.root")
root [1] TTree *t = (TTree*) f->Get("tree")
root [2] t->MakeSelector("MySelector")
root [3] .!ls MySelector*
MySelector.C MySelector.h

more details can be found here.
https://root.cern.ch/developing-tselector

You can find in the variables set in the header file.
An example is as below.
TTreeReaderValue<type> fSetNameOfVariable = {fReader, "VariableNameInNtuple"}
see MySelector.h for more example.
Then set up the outputfile name and define histograms in the header file that is generated.

MySelector.C macros that you just generated and amended can be run 
with the following commands. It will make a root file as an output file 
containing the histograms. 

lsetup root
root [0] TFile *f = TFile::Open("MyNtuple.root")
root [1] TTree *t = (TTree*) f->Get("tree")
root [2] t->Process("MySelector.C")

then the output root file of histograms is generated.

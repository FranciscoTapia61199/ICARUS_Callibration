void test10(const char* ext = ".root")	

	// ##Loop over all root files of an specific event and make a list that will be added to TChain##
{
	//const char* inDir = "/pnfs/icarus/persistent/calibration/calib_ntuples/data/v09_56_00_01/offbeambnbminbias/run/85/92";

	const char* inDir = "/pnfs/icarus/persistent/calibration/calib_ntuples/data/v09_56_00_01/offbeambnbminbias/run/86/55";

	char* dir = gSystem->ExpandPathName(inDir);
	void* dirp = gSystem->OpenDirectory(dir);

	const char* entry;
	//const char* filename[700];	
	const char* filename[6660];

	Int_t n = 0;
	TString str;

	while((entry = (char*)gSystem->GetDirEntry(dirp))) {
	str = entry;

	if(str.EndsWith(ext)){
		filename[n++] = gSystem->ConcatFileName(dir, entry);}	
	}

	//## Input TTree name here, and if is inside a TDirectory, we include first the TDirectory and then the TTree 

	TChain *chain = new TChain("simpleLightAna/opflashCryoW_ophittree");
	
	// ##for loop to add each TFile to the TChain
	
	for (Int_t i=0; i<n; i++){
		chain->Add(filename[i]);		
		}
	
	//chain->Add(filename[0]);
	
	// ##Input the TLeaf we are interested to make an histogram

	TString lf = "amplitude";

	Float_t min = chain->GetMinimum(lf);
	Float_t max = chain->GetMaximum(lf);


	TTreeReader myReader(chain);
	TTreeReaderValue<Float_t> x(myReader, lf);

	TH1F *hist = new TH1F("hist", "Histogram " + lf ,100 ,min ,max);
	
	// ##While loop to fill the histogram with all data
	
	while (myReader.Next()) {
		hist->Fill(*x);
		}
	
	hist->GetXaxis()->SetTitle(lf);
	hist->GetYaxis()->SetTitle("Entries");
	
	TCanvas *c1 = new TCanvas();
	c1->SetGrid();
	c1->SetTickx();
	c1->SetTicky();
	hist->Draw();
	
	// ##Save the histogram as png following the structure "eventnumber/_TDirectory/_TTree/_TLeaf/_chain.png"
	c1->SaveAs("8655_simpleLightAna_opflashCryoW_ophittree_amplitude_chain.png");

}

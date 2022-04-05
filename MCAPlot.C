void MCAPlot()
{
  gROOT->SetStyle("ATLAS");

  TString file = "../GAGG_0_collimated_retake_00006.mca";
  //TString file = "../GAGG_0_00001.mca";
  //TString file = "../Co60.mca";
  //TString file = "../Cs137.mca";

  int binnum, keVbinnum, keVmin, keVmax;
  binnum = 1024;
  keVbinnum = 1024;
  keVmin = 0;
  keVmax = 10;

  TH1D* hist = new TH1D("hist","hist", binnum, 0, binnum);
  TH1D* histkeV = new TH1D("histkeV","histkeV", keVbinnum, keVmin, keVmax);

  ifstream ifs(file);

  bool flag = false;
  int index = 0;
  while(1) {
    std::string hoge;
    getline(ifs, hoge);

    if(flag == false) {
      if(hoge.find("<<DATA>>") != std::string::npos) flag = true;
      continue;
    }
    if(hoge.find("<<END>>") != std::string::npos) break;

    //hist->SetBinContent(index, atoi(hoge.c_str()));
    histkeV->SetBinContent((int)((index*8.11818e-03+2.26694e-02)/keVmax*keVbinnum), atoi(hoge.c_str()));
    //histkeV->SetBinContent((int)(index*8.11818e-03-2.26694e-02), atoi(hoge.c_str()));
    index++;
  }
  
  //hist->Rebin(1);
  hist->SetTitle(";MCA Channel;Events");
  hist->SetMarkerStyle(8);
  hist->SetMarkerColor(1);
  hist->SetLineWidth(1);
  hist->SetEntries(hist->Integral());

  histkeV->SetTitle(";Energy[MeV];Events");
  histkeV->SetMarkerStyle(8);
  histkeV->SetMarkerColor(1);
  histkeV->SetLineWidth(1);
  histkeV->SetEntries(histkeV->Integral());

  //hist->Draw("");
  //histkeV->Rebin(5);
  histkeV->Draw("");

// Prepare fitting
    const double FitMin = 0.4;
    const double FitMax = 0.6;

	const double FitMin2 = 155.;
	const double FitMax2 = 200.;

        TF1* func = new TF1("func", "gaus", FitMin, FitMax);
        TF1* func2 = new TF1("func2", "gaus", FitMin2, FitMax2);

	// [0]*exp(-0.5*((x-[1])/[2])**2) is gaussian distribution.
        func->SetParName(0, "Const");
        func->SetParName(1, "Mean" );
        func->SetParName(2, "Sigma");
	
	func2->SetParName(0, "Const");
	func2->SetParName(1, "Mean" );
	func2->SetParName(2, "Sigma");

        // Set initial parameters
        func->SetParameter(0, 0.);
        func->SetParameter(1, 0.5);
        func->SetParameter(2, 0.1);

        func2->SetParameter(0, 30.);
        func2->SetParameter(1, 500.);
        func2->SetParameter(2, 80.);

        // Fitting
        //hist->Fit("func", "R", "same", FitMin, FitMax);
	//hist->Fit("func2", "R+", "sames", FitMin2, FitMax2);
	
	//c1->Update();
	//TPaveStats *st = (TPaveStats*)hist->FindObject("stats");
	//st->SetX1NDC(0.78);
        //st->SetX1NDC(0.98);
        //st->SetX1NDC(0.775);
        //st->SetX1NDC(0.935);
	//c1->Modified();	
	
	//hist->SetStats();
	//gStyle->SetOptFit();
	//hist->SetStats();
	gStyle->SetOptFit();
	

        histkeV->Fit("func", "", "", FitMin, FitMax);

        func->SetLineColor(kRed);
        func->Draw("same");

	func2->SetLineColor(kBlue);
        //func2->Draw("same");


        // Output parameters to command line
        cout << "Mean: " <<
        func->GetParameter(1) <<
        " +/- " <<
        func->GetParError(1) <<
        endl;

	cout << "Sigma: " <<
        func->GetParameter(2) <<
        " +/- " <<
        func->GetParError(2) <<
        endl;
        cout << "Chi2/NDF: " <<
        func->GetChisquare()/func->GetNDF() <<
        endl;



	cout << "Mean: " <<
        func2->GetParameter(1) <<
        " +/- " <<
        func2->GetParError(1) <<
        endl;

        cout << "Sigma: " <<
        func2->GetParameter(2) <<
        " +/- " <<
        func2->GetParError(2) <<
        endl;

        cout << "Chi2/NDF: " <<
        func2->GetChisquare()/func2->GetNDF() <<
        endl;


        //This function type is int.
	
  return 0;
}



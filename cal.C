int cal(){
	
	vector<double> channel = {78.7198, 139.234, 162.129};
	vector<double> energy = {0.6617, 1.17, 1.33};
	vector<double> errors = {0.0269015, 0.307499, 0.254551};

	TGraphErrors* tg = new TGraphErrors(3, channel.data(), energy.data(), errors.data(), 0);
	tg->SetTitle(";MCA channel; Energy (Mev)");
	//tg->SetMarkerSize(5);
	tg->SetMarkerStyle(8);
	tg->SetMinimum(0);
	tg->GetXaxis()->SetLimits(0,200);
	tg->Draw("AP");
	tg->Fit("pol1","rob");

	return 0;
}

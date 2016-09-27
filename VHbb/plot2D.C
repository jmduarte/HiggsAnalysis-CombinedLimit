#include <iostream>

#include "TFile.h"
#include "TH2D.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TPad.h"
#include "TLatex.h"
#include "TMarker.h"

void make_plot2D(bool observed = 0, TString filename = "higgsCombine2D.MultiDimFit.mH125.6.root", TString outname = "", int nbins=21){
  gStyle->SetOptStat(0);
  //gStyle->SetPalette(57);

  TString titlestring = "Expected";
  if(observed==1){
    titlestring = "Observed";
  }

  cout << "file: " << filename << endl;
  TFile fin(filename, "READ");

  TH2D* h_population = new TH2D("h_population", "population", nbins,0,1.000001,nbins,0,2.000001);
  TH2D* h_nll = new TH2D("h_nll", titlestring + " WH+ZH -2#DeltalnL , #mu vs f_{a3}^{ZH}", nbins,0,1.000001,nbins,0,2.000001);
  TH2D* h_nll_contour = new TH2D("h_nll_contour", "", nbins,0,1.000001,nbins,0,2.000001);

  TTree* limit = (TTree*)fin.Get("limit");

  TCanvas* c_population = new TCanvas("c_population", "c_population", 640, 640);
  c_population->cd();
  //limit->Draw("r:CMS_zz4l_fg4>>h_population","(r!=2)", "COLZ");
  limit->Draw("r:CMS_zz4l_fg4>>h_population","(deltaNLL!=0 && r!=2)", "COLZ");
  c_population->SaveAs("c_population"+outname+".png");

  TCanvas* c_deltanll = new TCanvas("c_deltanll", "c_deltanll", 640, 640);
  c_deltanll->cd();
  TString ystring1 = "2*deltaNLL - 2*";
  ystring1 += limit->GetMinimum("deltaNLL");//offset due to rough initial scan
  ystring1 += "+ 0.001";//shortcut to prevent a white box.
  cout << "OFFSET: " << limit->GetMinimum("deltaNLL") << endl;
  //limit->Draw("r:CMS_zz4l_fg4>>h_nll","2*deltaNLL*(deltaNLL!=0 a&& r!=2)", "COLZ");
  //limit->Draw("r:CMS_zz4l_fg4>>h_nll","("+ystring1+")*(deltaNLL!=0 && r!=2)", "COLZ");
  limit->Draw("r:CMS_zz4l_fg4>>h_nll","("+ystring1+")*(r!=2)", "COLZ");
  limit->Draw("r:CMS_zz4l_fg4>>h_nll_contour","("+ystring1+")*(r!=2)", "goff");

  //Processing
  //h_nll->Smooth();
  /*
  for(int x = 1; x<=nbins; x++){
    for(int y = 1; y<=nbins; y++){
      if(h_nll->GetBinContent(x,y) <1E-12){
	h_nll->SetBinContent(x, y, 0.25*(h_nll->GetBinContent(x-1,y) + h_nll->GetBinContent(x+1,y) + h_nll->GetBinContent(x,y-1) + h_nll->GetBinContent(x,y+1)));
	h_nll_contour->SetBinContent(x, y, 0.25*(h_nll->GetBinContent(x-1,y) + h_nll->GetBinContent(x+1,y) + h_nll->GetBinContent(x,y-1) + h_nll->GetBinContent(x,y+1)));
      }
    }
  }
  */
  
  for(int x = 1; x<=nbins; x++){
    for(int y = 1; y<=nbins; y++){
      //cout << "bin content (" << x << "," << y << ") = " << h_nll->GetBinContent(x,y) << endl;
      if(h_population->GetBinContent(x,y)<1E-12){
	
	if(x!=1 && x!=nbins && y!=1 && y!=nbins){
	  cout << "Fixing missing bin: x = " << x << " y = " << y << endl;
	  h_nll->SetBinContent(x, y, 0.25*(h_nll->GetBinContent(x-1,y) + h_nll->GetBinContent(x+1,y) + h_nll->GetBinContent(x,y-1) + h_nll->GetBinContent(x,y+1)));
	  h_nll_contour->SetBinContent(x, y, 0.25*(h_nll->GetBinContent(x-1,y) + h_nll->GetBinContent(x+1,y) + h_nll->GetBinContent(x,y-1) + h_nll->GetBinContent(x,y+1)));
	}
	else if(x==nbins && y!=nbins){
	  cout << "Fixing missing bin: x = " << x << " y = " << y << endl;
	  h_nll->SetBinContent(x, y, 0.5*(h_nll->GetBinContent(x,y-1) + h_nll->GetBinContent(x,y+1)));
	  h_nll_contour->SetBinContent(x, y, 0.5*(h_nll->GetBinContent(x,y-1) + h_nll->GetBinContent(x,y+1)));
	}

      }
    }
  }

  //Markers
  float r, CMS_zz4l_fg4;
  limit->SetBranchAddress("r", &r);
  limit->SetBranchAddress("CMS_zz4l_fg4", &CMS_zz4l_fg4);
  limit->GetEntry(0);
  TMarker marker_sm(0,1,24);
  TMarker marker_fit(CMS_zz4l_fg4,r,20);
  marker_fit.SetMarkerSize(1.3);

  TString channel = "ZH";
  if(outname.Contains("Wh") || outname.Contains("WH")) channel = "WH";

  //Style
  h_nll->SetTitle("");
  h_nll->GetXaxis()->SetTitle("f_{a3}^{"+channel+"}");
  h_nll->GetYaxis()->SetTitle("#mu^{"+channel+"}");
  h_nll->GetZaxis()->SetTitle("-2#DeltalnL");
  h_nll->GetYaxis()->SetRangeUser(0,1.9);
  h_nll->GetXaxis()->SetTitleSize(0.05);
  h_nll->GetYaxis()->SetTitleSize(0.05);
  h_nll->GetZaxis()->SetTitleSize(0.05);
  h_nll->GetYaxis()->SetTitleOffset(1.1);
  h_nll->GetXaxis()->SetTitleOffset(1.1);
  h_nll->GetZaxis()->SetTitleOffset(.85);
  h_nll->GetZaxis()->SetRangeUser(0,1.05*h_nll->GetMaximum());

  h_nll_contour->SetLineColor(kBlack);
  double level[2]={1,3.84};
  h_nll_contour->SetContour(2,level);
  h_nll_contour->SetLineWidth(2);
  h_nll_contour->Draw("cont3SAME");

  //marker_sm.Draw();
  marker_fit.Draw();

  TLatex* prelimTex = new TLatex();
  prelimTex->SetNDC();
  prelimTex->SetTextSize(0.03);
  prelimTex->SetTextAlign(31);//right
  prelimTex->SetTextFont(42);
  prelimTex->DrawLatex(0.88,0.91, "CMS Preliminary, 18.94 fb^{-1} at #sqrt{s} = 8 TeV");

  gPad->SetBottomMargin(0.14);
  gPad->SetLeftMargin(0.15);
  gPad->SetRightMargin(0.15);
  gPad->Modified();

  c_deltanll->SaveAs("c_deltanll"+outname+".png");
  c_deltanll->SaveAs("c_deltanll"+outname+".pdf");
  c_deltanll->SaveAs("c_deltanll"+outname+".eps");
  c_deltanll->SaveAs("c_deltanll"+outname+".root");

  gPad->SetLogz();
  h_nll->GetZaxis()->SetRangeUser(0.001,1.05*h_nll->GetMaximum());
  c_deltanll->SaveAs("c_deltanll"+outname+"_logz.png");
  c_deltanll->SaveAs("c_deltanll"+outname+"_logz.pdf");
  c_deltanll->SaveAs("c_deltanll"+outname+"_logz.eps");
  c_deltanll->SaveAs("c_deltanll"+outname+"_logz.root");
  
  return;
}


void plot2D(){

  //make_plot2D(1,"/eos/uscms/store/user/lpcmbja/noreplica/2D_zhDR_p0plusp1_050915_correlatedBkg_sigThrsld2.5_deCorrdMedHighNuis_trendGuessObserved_rfix/Vh_CMS_common_observed_minuit_0p1_tries5_strategy1_npoints1600.combine.root", "", 41);
  //make_plot2D(1,"/eos/uscms/store/user/lpcmbja/noreplica/2D_zhDR_p0plusp1_050915_correlatedBkg_sigThrsld2.5_deCorrdMedHighNuis_trendGuessObserved_rfix/Vh_CMS_common_expected_minuit_0p1_tries5_strategy1_npoints1600.combine.root", "_expected", 41);

  make_plot2D(1,"/eos/uscms/store/user/lpcmbja/noreplica/2D_zhDR_p0plusp1_050915_correlatedBkg_sigThrsld2.5_deCorrdMedHighNuis_trendGuessObserved_rfix_WHZH/Zh_CMS_common_observed_minuit_0p1_tries5_strategy1_npoints1600.combine.root", "_Zh", 41);
  make_plot2D(1,"/eos/uscms/store/user/lpcmbja/noreplica/2D_zhDR_p0plusp1_050915_correlatedBkg_sigThrsld2.5_deCorrdMedHighNuis_trendGuessObserved_rfix_WHZH/Zh_CMS_common_expected_minuit_0p1_tries5_strategy1_npoints1600.combine.root", "_Zh_expected", 41);

  //WH in fa3wh
  //make_plot2D(1,"/eos/uscms/store/user/lpcmbja/noreplica/2D_zhDR_p0plusp1_050915_correlatedBkg_sigThrsld2.5_deCorrdMedHighNuis_trendGuessObserved_rfix_WHZH/Wh_CMS_common_observed_minuit_0p1_tries5_strategy1_npoints1600.combine.root", "_Wh", 41);
  make_plot2D(1,"/eos/uscms/store/user/lpcmbja/noreplica/2D_zhDR_p0plusp1_050915_correlatedBkg_sigThrsld2.5_deCorrdMedHighNuis_trendGuessObserved_rfix_WHZH/Wh_CMS_common_observed_minuit2_0p1_tries5_strategy0_npoints1600.combine.root", "_Wh", 41);
  make_plot2D(1,"/eos/uscms/store/user/lpcmbja/noreplica/2D_zhDR_p0plusp1_050915_correlatedBkg_sigThrsld2.5_deCorrdMedHighNuis_trendGuessObserved_rfix_WHZH/Wh_CMS_common_expected_minuit_0p1_tries5_strategy1_npoints1600.combine.root", "_Wh_expected", 41);

}

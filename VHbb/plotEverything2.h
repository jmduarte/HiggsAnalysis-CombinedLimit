#include <iostream>
#include <cassert>
#include <algorithm>
#include <stdlib.h>

#include "TString.h"
#include "TFile.h"
#include "TH1F.h"
#include "TTree.h"
#include "TChain.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TAxis.h"
#include "TMultiGraph.h"
#include "TLegend.h"
#include "TLatex.h"

using namespace std;


//double global_x_max = .1; //1, .1 
//int ndiv = 505; //512, 505
//TString prepend = "zoom_";

double global_x_max = 1;
int ndiv = 512; 
TString prepend = "full_";

TString fa3zzTozz = "CMS_zz4l_fg4";
TString fa3zzToww = "CMS_zz4l_fg4*6.36/( (1-CMS_zz4l_fg4)*3.01   + CMS_zz4l_fg4*6.36)";
TString fa3zzTowh = "CMS_zz4l_fg4*6.36/( (1-CMS_zz4l_fg4)*0.017382 + CMS_zz4l_fg4*6.36)";
TString fa3zzTozh = "CMS_zz4l_fg4*6.36/( (1-CMS_zz4l_fg4)*0.023868 + CMS_zz4l_fg4*6.36)";


class graph{
 public:
  graph();
  void get_raw_vectors();
  void sort_vectors();
  void remove_initial_fit();
  void remove_outliers();
  void kill_points();
  void redo_offset();
  void create_graph();

  void min_prep();
  void do_all_prep();
  void do_all_prep_keep_offset();

  void transform_x(TString transform);

  TString file_name;
  std::vector<TString> file_name_vector;

  std::vector<double> x;
  std::vector<double> y;

  std::vector<double> kill;

  TGraph* gr;

  TString scale = "1";
  TString x_variable = fa3zzTozz;

  //Style
  TString legend_name = "";
  int color = 1;
  int linestyle = 1;

  bool verbose = false;
};

//constructor
graph::graph(){

}

void graph::get_raw_vectors(){

  if(file_name_vector.size() == 0){//for backwards compatability (consider removing)
    TFile* fin = TFile::Open(file_name, "READ");
    if(fin->IsZombie()) {cout << "Problem with file " << file_name << endl; return;}
    
    TTree* limit = (TTree*)fin->Get("limit");
    limit->Draw(scale+"*2*deltaNLL:"+x_variable);
    
    std::vector<double> v1(limit->GetV1(), limit->GetV1() + limit->GetSelectedRows());
    std::vector<double> v2(limit->GetV2(), limit->GetV2() + limit->GetSelectedRows());
    
    y=v1;
    x=v2;
  }
  else{
    TChain limit("limit");
    for(int i=0; i<file_name_vector.size(); i++){
      cout << "Adding " << file_name_vector[i] << endl;
      limit.Add( file_name_vector[i] );
    }

    limit.Draw(scale+"*2*deltaNLL:"+x_variable);

    std::vector<double> v1(limit.GetV1(), limit.GetV1() + limit.GetSelectedRows());
    std::vector<double> v2(limit.GetV2(), limit.GetV2() + limit.GetSelectedRows());
    
    y=v1;
    x=v2;
  }

  return;
}


void graph::sort_vectors(){
  
  //fill pair vector
  std::vector< std::pair<double,double> > pair_vector;
  for(unsigned int i=0; i<x.size(); i++){
    std::pair<double,double> my_pair(x[i], y[i]);
    pair_vector.push_back(my_pair);
  }

  //sort pair vector
  std::sort(pair_vector.begin(), pair_vector.end()); //default is to sort based on .first
  
  //dump pair vector back to separated vectors
  for(unsigned int i=0; i<pair_vector.size(); i++){
    x[i] = pair_vector[i].first;
    y[i] = pair_vector[i].second;
  }

  return;
}


void graph::remove_initial_fit(){

  std::vector<double> y_out; 
  std::vector<double> x_out;
  
  for(unsigned int i=0; i<y.size(); i++){
    if( y[i]!=0 ) //ugly integer/double thing
      {
        y_out.push_back(y[i]);
        x_out.push_back(x[i]);
      }
    else{
      cout << "remove " << x[i] << " " << y[i] << endl; 
    }
  }
  
  y.clear();
  x.clear();
  y=y_out;
  x=x_out;

  return;
}


void graph::remove_outliers(){
  if(verbose) cout << "Removing outliers for " << file_name << endl;
  bool noClean = 0;

  std::vector<double> y_out; 
  std::vector<double> x_out;
  
  for(unsigned int i=0; i<y.size(); i++){

    //This can call the true minimum :(
    //if( ((y[i+1]-y[i])*(y[i]-y[i-1])>0 
    //	 || fabs((y[i]-y[i-1])/(y[i]+y[i-1]))<0.2 
    //	 || fabs((y[i]-y[i+1])/(y[i]+y[i+1]))<0.2) 
    //	|| noClean ){

    bool keep = 0;
    if(i==0) keep = 1;
    else if(i==1) keep = 1;
    else if(i==y.size()-1) keep = 1;
    else if(i==y.size()-2) keep = 1;
    if(keep==0){
      if( (y[i+1]-y[i])*(y[i]-y[i-1])>0 ) keep = 1;
      else if( fabs((y[i]-y[i-1])/(y[i]+y[i-1]))<0.04 ) keep = 1;
      else if( fabs((y[i]-y[i+1])/(y[i]+y[i+1]))<0.04 ) keep = 1;
      if(keep==0){
	if( fabs((y[i-1]-y[i-2])/(y[i-1]+y[i-2]))>0.1 ) keep = 1;
	else if( fabs((y[i+1]-y[i+2])/(y[i+1]+y[i+2]))>0.1 ) keep = 1;
      }
    }

    if(keep){
      if(verbose) cout << x[i] << " " <<  y[i] << endl;
      y_out.push_back(y[i]);
      x_out.push_back(x[i]);
    }
    else{
      cout << "Removing: " << x[i] << " " <<  y[i] << endl;
    }
    
  }
  
  y.clear();
  x.clear();
  y=y_out;
  x=x_out;

  return;
}


void graph::kill_points(){
  if(kill.size()==0) return;
  if(verbose) cout << "Killing points for " << file_name << endl;
  bool noClean = 0;

  std::vector<double> y_out; 
  std::vector<double> x_out;
  
  for(unsigned int i=0; i<y.size(); i++){

    bool keep = 1;
    for(unsigned int j=0; j<kill.size(); j+=2){
      double small = kill[j];
      double big = kill[j+1];
      
      if( x[i]>small && x[i]<big ) {
	keep=0;
	break;//only needs to fail once
      }
    }
    if(keep){
      if(verbose) cout << x[i] << " " <<  y[i] << endl;
      y_out.push_back(y[i]);
      x_out.push_back(x[i]);
    }
    else{
      cout << "Removing: " << x[i] << " " <<  y[i] << endl;
    }
    
  }
  
  y.clear();
  x.clear();
  y=y_out;
  x=x_out;

  return;
}



void graph::redo_offset(){

 //find min
 double min = 999999999;
 for(unsigned int i=0; i<y.size(); i++){
   if(y[i] < min) min=y[i];
 }
 
 //warning if abs(offset) is large
 if(fabs(min) > 0.1) cout << "WARNING!!! offset is " << min << endl;

 //apply offset if min<0
 // if(min<0){
 if(1){
   cout << "offset: " << min << endl;
   for(unsigned int i=0; i<y.size(); i++){
     y[i] = y[i] - min;
   }
 }
 else{
   cout << "offset: 0 " << endl;
 }


}


void graph::create_graph(){

  gr = new TGraph(x.size(), &x[0], &y[0]);

  //Style
  gr->SetMarkerSize(1);
  gr->SetMarkerStyle(20);
  gr->SetMarkerColor(color);
  gr->SetLineColor(color);
  gr->SetLineWidth(2);
  gr->SetLineStyle(linestyle);

  if(scale!="1"){
    legend_name += " (#times ";
    legend_name += scale;
    legend_name += ")";
  }

  return;
}


void graph::do_all_prep(){
  
  cout << endl;
  cout << file_name << endl;
  
  get_raw_vectors();
  //remove_initial_fit(); //not needed if sorting!
  sort_vectors();
  kill_points();
  remove_outliers();
  redo_offset();
  create_graph();

  return;
}

void graph::do_all_prep_keep_offset(){
  
  cout << endl;
  cout << file_name << endl;
  
  get_raw_vectors();
  sort_vectors();
  kill_points();
  remove_outliers();
  create_graph();

  return;
}


void graph::min_prep(){
  
  cout << endl;
  cout << file_name << endl;
  
  get_raw_vectors();
  sort_vectors();
  create_graph();

  return;
}


void graph::transform_x(TString transformation){
  
  for(unsigned int i=0; i<x.size(); i++){
    
    if(transformation == "fa3zzToww"){
      return;
    }
    else if(transformation == "fa3zzToww"){
      x[i] = x[i]*6.36/( (1-x[i])*3.01   + x[i]*6.36);
    }
    else if(transformation == "fa3zzTowh"){
      x[i] = x[i]*6.36/( (1-x[i])*0.017382 + x[i]*6.36);
    }
    else if(transformation == "fa3zzTozh"){
      x[i] = x[i]*6.36/( (1-x[i])*0.023868 + x[i]*6.36);
    }
    else assert(0);
  }
  
  return;
}

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////


   
class figure{
 public:
  figure();
  void draw();

  std::vector<graph> graphs;

  double y_min=0;
  double y_max=6;
  double x_min=0;
  double x_max=1;
  //int ndiv = 512;
  //int ndiv = 505;
  double leg_y_min = 0.7;
  double leg_y_max = 0.87;

  TString figure_name;
  TString x_title = "x";

};

//constructor
figure::figure(){

}

void figure::draw(){

  TCanvas* cs = new TCanvas("c "+figure_name, "c "+figure_name, 640, 640);
  cs->cd();
  TH1F* hs = cs->DrawFrame(x_min, y_min, x_max, y_max);
  hs->GetXaxis()->SetNdivisions(ndiv);
  hs->GetXaxis()->SetLabelSize(0.05);
  hs->GetYaxis()->SetLabelSize(0.05);
  hs->GetXaxis()->SetTitleSize(0.05);
  hs->GetYaxis()->SetTitleSize(0.05);
  hs->GetYaxis()->SetTitleOffset(1.2);
  hs->GetXaxis()->SetTitleOffset(1.2);
  hs->GetXaxis()->SetTitle(x_title);
  hs->GetYaxis()->SetTitle("-2 #Delta ln L");
  gPad->SetBottomMargin(0.14);
  gPad->SetLeftMargin(0.15);
  gPad->Modified();
  TString style = "LP";

  //double legy=0.7;
  TLegend* leg = new TLegend(0.2, leg_y_min, .57, leg_y_max);
  leg->SetLineColor(0);
  leg->SetFillColor(0);

  for(unsigned int i=0; i<graphs.size(); i++){
    graphs[i].gr->Draw(style);
    leg->AddEntry(graphs[i].gr, graphs[i].legend_name, "l");
  }
  leg->Draw();

  TLatex* prelimTex = new TLatex();
  prelimTex->SetNDC();
  prelimTex->SetTextSize(0.03);
  prelimTex->SetTextAlign(31);//right
  prelimTex->SetTextFont(42);
  prelimTex->DrawLatex(0.88,0.91, "CMS Preliminary, 18.94 fb^{-1} at #sqrt{s} = 8 TeV");
  gPad->Update();
  cs->SaveAs(figure_name + "_graph.pdf");
  cs->SaveAs(figure_name + "_graph.png");

}

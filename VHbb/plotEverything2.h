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
#include "TLine.h"
#include "TMath.h"

using namespace std;


//double global_x_max = .1; //1, .1 
//int ndiv = 505; //512, 505
//TString prepend = "zoom_";

double global_x_max = 1;
TString prepend = "full_";

TString fa3zzTozz = "CMS_zz4l_fg4";
TString fa3zzToww = "CMS_zz4l_fg4*6.36/( (1-CMS_zz4l_fg4)*3.01   + CMS_zz4l_fg4*6.36)";
TString fa3zzTowh = "CMS_zz4l_fg4*6.36/( (1-CMS_zz4l_fg4)*0.017382 + CMS_zz4l_fg4*6.36)";
TString fa3zzTozh = "CMS_zz4l_fg4*6.36/( (1-CMS_zz4l_fg4)*0.023868 + CMS_zz4l_fg4*6.36)";


class graph{
 public:
  graph();
  void get_raw_vectors();
  void add_point();
  void sort_vectors();
  void remove_initial_fit();
  void remove_outliers();
  void kill_points();
  void redo_offset();
  void create_graph();

  double match(std::vector<double> v1_first, std::vector<double> v2_first, std::vector<double> v1_second, std::vector<double> v2_second, double start);

  void min_prep();
  void do_all_prep(TString transformation = "fa3zzTozz");
  void do_all_prep_keep_offset(TString transformation = "fa3zzTozz");
  void do_all_prep_keep_outliers(TString transformation = "fa3zzTozz");

  void transform_x(TString transform = "fa3zzTozz");

  void findCrossing(double y_value);
  float findMin(bool print = true);

  TString file_name;
  std::vector<TString> file_name_vector;
  std::vector<double> stitch_point_vector;
  std::vector<double> match_point_vector;

  std::vector<double> add_point_x;
  std::vector<double> add_point_y;

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


double graph::match(std::vector<double> v1_first, std::vector<double> v2_first, std::vector<double> v1_second, std::vector<double> v2_second, double start){

  for(unsigned int i=0; i<v2_second.size(); i++){
    for(unsigned int j=0; j<v2_first.size(); j++){//do this post sort if too slow
      cout << "v2_first " << v2_first[j] << " v2_second " << v2_second[i] << endl;
      double diff = fabs( (v2_second[i]-v2_first[j])/(0.5*(v2_second[i]+v2_first[j])));
      cout << "v2_first[j] " << v2_first[j] << " start " << start << " diff " << diff << endl;
      if( v2_first[j]>start && diff<1e-15 ){//match!
        double offset = v1_first[j] - v1_second[i];
        cout << "Match offset = " << v1_first[j] << " - " << v1_second[i] << " = " << offset << " at " << v2_second[i] << " (diff = " << diff << ")"<< endl;
	return offset;
      }
    }//j
  }//i
  cout << "NO MATCH!" << endl;
  
  assert(0);
  return -9999999999999;
}


void graph::get_raw_vectors(){

  if(file_name_vector.size() == 0){//for backwards compatability (consider removing)
    TFile* fin = TFile::Open(file_name, "READ");
    if(fin->IsZombie()) {cout << "Problem with file " << file_name << endl; return;}
    
    TTree* limit = (TTree*)fin->Get("limit");
    limit->Draw(scale+"*2*deltaNLL:"+x_variable);
    if(scale != "1") cout << "SCALED BY " << scale << endl;
    
    std::vector<double> v1(limit->GetV1(), limit->GetV1() + limit->GetSelectedRows());
    std::vector<double> v2(limit->GetV2(), limit->GetV2() + limit->GetSelectedRows());
    
    y=v1;
    x=v2;
  }
  else{
    /*
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
    */

    //stitch
    bool stitch_offset = false;
    bool stitch_offset_match = true;
    bool stitch_verbose = true;
    for(int i=0; i<file_name_vector.size(); i++){
      cout << "Vector " << file_name_vector[i] << endl;
      cout << "Stitch " <<  stitch_point_vector[i] << endl;
      TFile* fin = TFile::Open(file_name_vector[i], "READ");
      if(fin->IsZombie()) {cout << "Problem with file " << file_name_vector[i] << endl; return;}
      TTree* limit = (TTree*)fin->Get("limit");
      limit->Draw(scale+"*2*deltaNLL:"+x_variable);
      std::vector<double> v1(limit->GetV1(), limit->GetV1() + limit->GetSelectedRows());//y
      std::vector<double> v2(limit->GetV2(), limit->GetV2() + limit->GetSelectedRows());//x
      
      if(stitch_offset_match && i>0){
	//Look for match with full range
	double offset = match(y, x, v1, v2, match_point_vector[i-1]);//never tried stitching more than 2

	//Correct small scan 
	for(unsigned int j=0; j<v2.size(); j++){
	  v1[j] = v1[j]+offset;
	}
      }
      else if(stitch_offset){//this doesn't work when there are failures
	cout << "Appllying offset before stitching" << endl;

	//find min
	double min = 999999999;
	for(unsigned int i=0; i<v1.size(); i++){
	  if(v1[i] < min) min=v1[i];
	}
	//if(fabs(min) > 0.1) cout << "WARNING!!! offset is " << min << endl;
	if(1){
	  cout << "offset: " << min << endl;
	  for(unsigned int i=0; i<v1.size(); i++){
	    v1[i] = v1[i] - min;
	  }
	}
	else{
	  cout << "offset: 0 " << endl;
	}
      }

      for(unsigned int j=0; j<v2.size(); j++){
	if(i==0){
	  if(stitch_verbose) cout << v2[j] << " " << v1[j] << " " << stitch_point_vector[i] << endl;
	  if(v2[j] < stitch_point_vector[i]){
	    if(stitch_verbose) cout << "Add" << endl;
	    x.push_back(v2[j]);
	    y.push_back(v1[j]);
	  }
	}
	else{
	  if(stitch_verbose) cout << v2[j] << " " << v1[j] << endl;
	  if(v2[j] < stitch_point_vector[i] && v2[j] >= stitch_point_vector[i-1]){
	    if(stitch_verbose) cout << "Add" << endl;
	    x.push_back(v2[j]);
	    y.push_back(v1[j]);
	  }
	}
      }
    }
  }
  return;
}


void graph::add_point(){
  
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
      cout << "Killing: " << x[i] << " " <<  y[i] << endl;
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


void graph::do_all_prep(TString transformation){
  
  cout << endl;
  cout << file_name << endl;
  
  get_raw_vectors();
  //remove_initial_fit(); //not needed if sorting!
  sort_vectors();
  kill_points();
  remove_outliers();
  redo_offset();
  transform_x(transformation);
  findMin();
  findCrossing(1);
  findCrossing(3.84);
  create_graph();

  return;
}

void graph::do_all_prep_keep_offset(TString transformation){
  
  cout << endl;
  cout << file_name << endl;
  
  get_raw_vectors();
  sort_vectors();
  kill_points();
  remove_outliers();
  transform_x(transformation);
  findMin();
  findCrossing(1);
  findCrossing(3.84);
  create_graph();

  return;
}


void graph::do_all_prep_keep_outliers(TString transformation){
  
  cout << endl;
  cout << file_name << endl;
  
  get_raw_vectors();
  //remove_initial_fit(); //not needed if sorting!
  sort_vectors();
  kill_points();
  //remove_outliers();
  redo_offset();
  transform_x(transformation);
  findMin();
  findCrossing(1);
  findCrossing(3.84);
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
  // f_old R_old / [(1-f_old)R_new + f_old R_old], where R = sigma1/sigma3
  // 7 TeV: Rzz=6.36, Rww=3.01, Rzh=0.0249, Rwh=0.0181
  // 8 TeV: Rzz=6.36, Rww=3.01, Rzh=0.023868, Rwh=0.017382

  for(unsigned int i=0; i<x.size(); i++){
    
    if(transformation == "fa3zzTozz"){
      if(i==0) cout << "x axis is in scan variable" << endl;
      return;
    }
    else if(transformation == "fa3zzToww"){
      if(i==0) cout << "x axis is fa3ww" << endl;
      x[i] = x[i]*6.36/( (1-x[i])*3.01   + x[i]*6.36);
    }
    else if(transformation == "fa3zzTowh"){
      if(i==0) cout << "x axis is fa3wh" << endl;
      x[i] = x[i]*6.36/( (1-x[i])*0.017382 + x[i]*6.36);
    }
    else if(transformation == "fa3zzTozh"){
      if(i==0) cout << "x axis is fa3zh" << endl;
      x[i] = x[i]*6.36/( (1-x[i])*0.023868 + x[i]*6.36);
    }
    else if(transformation == "fa3zhTozz"){
      if(i==0) cout << "x axis is fa3zz" << endl;
      x[i] = x[i]*0.023868/( (1-x[i])*6.36 + x[i]*0.023868);
    }
    else if(transformation == "fa3zhToww"){
      if(i==0) cout << "x axis is fa3ww" << endl;
      x[i] = x[i]*0.023868/( (1-x[i])*3.01 + x[i]*0.023868);
    }
    else if(transformation == "fa3wwTowh"){
      if(i==0) cout << "x axis is fa3ww" << endl;
      x[i] = x[i]*3.01/( (1-x[i])*0.017382 + x[i]*3.01);
    }
    else assert(0);
    cout << "x " << x[i] << endl;
  }
  
  return;
}


//LINEAR INTERPOLATION
void graph::findCrossing(double y_value){

  std::vector<double> x_values;
  
  double last_x = x[0];//to check sorting 
  double last_y = y[0];
  for(unsigned int i=1; i<x.size()-1; i++){//DOES NOT HANDLE FIRST AND LAST POINTS...
    //cout << "i " << i << ", x " << x[i] << ", y " << y[i] << endl;
    
    assert(x[i] >= last_x);//to check sorting

    //right on it
    if(y_value == y[i]){    
      x_values.push_back(x[i]);
    }
    //crossing from below
    else if(y_value > last_y && y_value < y[i]){
      double slope = (y[i] - last_y)/(x[i] - last_x);
      double x_value = last_x + (y_value - last_y)/slope;
      x_values.push_back(x_value);
    }
    //crossing from above
    else if(y_value > y[i] && y_value < last_y){
      double slope = (y[i] - last_y)/(x[i] - last_x);//SAME CODE... i forgot geometry
      double x_value = last_x + (y_value - last_y)/slope;
      x_values.push_back(x_value);
    }

    //for the next iteration
    last_x = x[i];
    last_y = y[i];
  }

  float min = findMin(false);
  float left = 0, right = 1;
  if(x_values.size() == 0) cout << "No crossings at  y = " << y_value << " found." << endl;
  else{
    for(unsigned int i=0; i<x_values.size(); i++){
      cout << "crossing y = " << y_value << " at x = " << x_values[i] << endl;

      if( (x_values[i]<min) && (min-x_values[i])<(min-left) ) left = x_values[i];
      if( (x_values[i]>min) && (x_values[i]-min)<(right-min) ) right = x_values[i];
    }
  }
  cout << "   => fa3 = " << min << "^{+" << right-min << "}_{-" << min-left << "}" << endl; 

}


float graph::findMin(bool print){
  //assumes only one min

  double y_min = 99999;
  unsigned int min_index = -99999;
  for(unsigned int i = 0; i<x.size(); i++){
    if(y[i] < y_min){
      y_min = y[i];
      min_index = i;
    }
  }
  if(print) cout << "min y = " << y[min_index] << " at x = " << x[min_index] << endl;
  return x[min_index];
}

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////


   
class figure{
 public:
  figure();
  void draw(TString style = "LP");

  std::vector<graph> graphs;

  double y_min=0;
  double y_max=6;
  double x_min=0;
  double x_max=1;
  //int ndiv = 512;
  //int ndiv = 505;
  int ndiv = 512; 
  double leg_y_min = 0.65;
  double leg_y_max = 0.87;
  double leg_x_min = 0.2;
  double leg_x_max = 0.65;

  TString figure_name;
  TString x_title = "x";

  //inset
  bool doInset = false;

};

//constructor
figure::figure(){

}

void figure::draw( TString style ){

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


  //double legy=0.7;
  TLegend* leg = new TLegend(leg_x_min, leg_y_min, leg_x_max, leg_y_max);
  leg->SetLineColor(0);
  leg->SetFillColor(0);

  double max = 0;
  for(unsigned int i=0; i<graphs.size(); i++){
    graphs[i].gr->Draw(style);
    leg->AddEntry(graphs[i].gr, graphs[i].legend_name, "l");

    //get max
    double this_max = TMath::MaxElement(graphs[i].gr->GetN(), graphs[i].gr->GetY());
    if(this_max > max) max = this_max;
  }
  cout << "Final max: " << max << endl;
  leg->Draw();

  //old
  TLatex* prelimTex = new TLatex();
  prelimTex->SetNDC();
  prelimTex->SetTextSize(0.03);
  prelimTex->SetTextAlign(31);//right
  prelimTex->SetTextFont(42);
  prelimTex->DrawLatex(0.88,0.91, "CMS Preliminary, 18.94 fb^{-1} at #sqrt{s} = 8 TeV");
  /////////////////////////////////////////////
  // the above should be replaced by https://ghm.web.cern.ch/ghm/plots/
  //////////////////////////////////////////////

  int horizontal_style = 9;
  double one_sigma = 1, CL95 = 3.84, CL99 = 6.63;
  TLine* line_one_sigma  = new TLine(x_min, one_sigma, x_max, one_sigma);
  TLine* line_95CL_sigma = new TLine(x_min, CL95, x_max, CL95);
  TLine* line_99CL_sigma = new TLine(x_min, CL99, x_max, CL99);
  line_one_sigma->SetLineStyle(horizontal_style);
  line_95CL_sigma->SetLineStyle(horizontal_style);
  line_99CL_sigma->SetLineStyle(horizontal_style);

  if(max>one_sigma) line_one_sigma->Draw();
  if(max>CL95) line_95CL_sigma->Draw();
  if(max>CL99) line_99CL_sigma->Draw();

  //inset
  if(doInset){
    gPad->Update();
    TPad *subpad = new TPad("subpad","",0.53,0.45,0.88,0.8);
    subpad->Draw();
    subpad->cd();
    TH1F* hs2 = cs->DrawFrame(0, 0, 0.01, 1);
    hs2->GetXaxis()->SetNdivisions(505);
    hs2->GetXaxis()->SetLabelSize(0.05);
    hs2->GetYaxis()->SetLabelSize(0.05);
    //hs2->GetXaxis()->SetTitleSize(0.05);
    //hs2->GetYaxis()->SetTitleSize(0.05);
    //hs2->GetYaxis()->SetTitleOffset(1.2);
    //hs2->GetXaxis()->SetTitleOffset(1.2);
    //hs2->GetXaxis()->SetTitle(x_title);
    //hs2->GetYaxis()->SetTitle("-2 #Delta ln L");
    //gPad->SetBottomMargin(0.14);
    //gPad->SetLeftMargin(0.15);
    //gPad->Modified();
    for(unsigned int i=0; i<graphs.size(); i++){
      graphs[i].gr->Draw(style);
    }
  }//doInset

  gPad->Update();
  cs->SaveAs(figure_name + ".pdf");
  cs->SaveAs(figure_name + ".png");
  cs->SaveAs(figure_name + ".eps");
  cs->SaveAs(figure_name + ".root");

}

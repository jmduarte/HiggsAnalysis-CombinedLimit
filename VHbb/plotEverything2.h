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

#include "TPad.h"
#include "TBox.h"
#include "TASImage.h"

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
  void add_last_point(bool doit = false);
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

  std::vector<double> x;
  std::vector<double> y;

  bool add_last_point_switch = false;

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
	for(unsigned int k=0; k<v1.size(); k++){
	  if(v1[k] < min) min=v1[k];
	}
	//if(fabs(min) > 0.1) cout << "WARNING!!! offset is " << min << endl;
	if(1){
	  cout << "offset: " << min << endl;
	  for(unsigned int k=0; k<v1.size(); k++){
	    v1[k] = v1[k] - min;
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


void graph::add_last_point(bool doit){

  if(doit){
    x.push_back(1);
    y.push_back(y[y.size()-1]);
    //y.push_back( *y.back() );
  }
  
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
  add_last_point(add_last_point_switch);
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
  add_last_point(add_last_point_switch);
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
  add_last_point(add_last_point_switch);
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
    else if(transformation == "fa3zhTowh"){
      if(i==0) cout << "x axis is fa3wh" << endl;
      x[i] = x[i]*0.023868/( (1-x[i])*0.017382 + x[i]*0.023868);
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
    else{
      cout << "transformation " << transformation << " not found" << endl;
      assert(0);
    }
    //cout << "x " << x[i] << endl;
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

  void CMS_lumi( TPad* pad, int iPeriod=2, int iPosX=11 );

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

  double more_y_offset = 0;

  TString figure_name;
  TString x_title = "x";

  bool draw_lines = true;

  //inset
  bool doInset = false;
  bool draw_inset_lines = true;
  double inset_y_min=0;
  double inset_y_max=1;
  double inset_x_min=0;
  double inset_x_max=0.01;
  double inset_pos_y_min=0.45;
  double inset_pos_y_max=0.8;
  double inset_pos_x_min=0.53;
  double inset_pos_x_max=0.88;

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
  hs->GetYaxis()->SetTitleOffset(1.2+more_y_offset);
  hs->GetXaxis()->SetTitleOffset(1.2);
  hs->GetXaxis()->SetTitle(x_title);
  hs->GetYaxis()->SetTitle("-2 #Delta ln L");
  gPad->SetBottomMargin(0.14);
  gPad->SetLeftMargin(0.15);
  gPad->Modified();


  //double legy=0.7;
  TLegend* leg = new TLegend(leg_x_min, leg_y_min, leg_x_max, leg_y_max);
  leg->SetLineColor(0);
  leg->SetBorderSize(0);
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

  bool oldStyle = false;
  if(oldStyle){
    TLatex* prelimTex = new TLatex();
    prelimTex->SetNDC();
    prelimTex->SetTextSize(0.03);
    prelimTex->SetTextAlign(31);//right
    prelimTex->SetTextFont(42);
    prelimTex->DrawLatex(0.88,0.91, "CMS Preliminary, 18.94 fb^{-1} at #sqrt{s} = 8 TeV");
  }
  else{
    /////////////////////////////////////////////
    // the above should be replaced by https://ghm.web.cern.ch/ghm/plots/
    //////////////////////////////////////////////
    // second parameter in example_plot is iPos, which drives the position of the CMS logo in the plot
    // iPos=11 : top-left, left-aligned
    // iPos=33 : top-right, right-aligned
    // iPos=22 : center, centered
    // mode generally : 
    //   iPos = 10*(alignement 1/2/3) + position (1/2/3 = left/center/right)
    CMS_lumi( cs );
  }

  int horizontal_style = 9;
  double one_sigma = 1, CL95 = 3.84, CL99 = 6.63;
  TLine* line_one_sigma  = new TLine(x_min, one_sigma, x_max, one_sigma);
  TLine* line_95CL_sigma = new TLine(x_min, CL95,      x_max, CL95);
  TLine* line_99CL_sigma = new TLine(x_min, CL99,      x_max, CL99);
  line_one_sigma->SetLineStyle(horizontal_style);
  line_95CL_sigma->SetLineStyle(horizontal_style);
  line_99CL_sigma->SetLineStyle(horizontal_style);

  if(draw_lines){
    if(max>one_sigma && one_sigma<y_max) line_one_sigma->Draw();
    if(max>CL95 && CL95<y_max) line_95CL_sigma->Draw();
    if(max>CL99 && CL99<y_max) line_99CL_sigma->Draw();
  }

  //inset
  if(doInset){
    gPad->Update();
    TPad *subpad = new TPad("subpad","",inset_pos_x_min,inset_pos_y_min,inset_pos_x_max,inset_pos_y_max);
    subpad->Draw();
    subpad->cd();
    TH1F* hs2 = cs->DrawFrame(inset_x_min, inset_y_min, inset_x_max, inset_y_max);
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

    if(draw_inset_lines){
      TLine* inset_line_one_sigma  = new TLine(inset_x_min, one_sigma, inset_x_max, one_sigma);
      TLine* inset_line_95CL_sigma = new TLine(inset_x_min, CL95,      inset_x_max, CL95);
      TLine* inset_line_99CL_sigma = new TLine(inset_x_min, CL99,      inset_x_max, CL99);
      inset_line_one_sigma->SetLineStyle(horizontal_style);
      inset_line_95CL_sigma->SetLineStyle(horizontal_style);
      inset_line_99CL_sigma->SetLineStyle(horizontal_style);
      if(max>one_sigma && one_sigma<inset_y_max) inset_line_one_sigma->Draw();
      if(max>CL95 && CL95<inset_y_max) inset_line_95CL_sigma->Draw();
      if(max>CL99 && CL99<inset_y_max) inset_line_99CL_sigma->Draw();
    }
  }//doInset


  gPad->Update();

  cs->SaveAs(figure_name + ".pdf");
  cs->SaveAs(figure_name + ".png");
  cs->SaveAs(figure_name + ".eps");
  cs->SaveAs(figure_name + ".root");
  cs->SaveAs(figure_name + ".C");

}


////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

//                                       Style



void figure::CMS_lumi( TPad* pad, int iPeriod, int iPosX ){            

  //h file

  // Global
  TString cmsText     = "CMS";
  float cmsTextFont   = 61;  // default is helvetic-bold
  
  bool writeExtraText = true;
  TString extraText   = "Preliminary";
  float extraTextFont = 52;  // default is helvetica-italics
  
  // text sizes and text offsets with respect to the top frame
  // in unit of the top margin size
  /*
  float lumiTextSize     = 0.6;
  float lumiTextOffset   = 0.2;
  float cmsTextSize      = 0.75;
  float cmsTextOffset    = 0.1;  // only used in outOfFrame version
  */
  float lumiTextSize     = 0.4;
  float lumiTextOffset   = 0.1;
  float cmsTextSize      = 0.75*.4/.6;
  float cmsTextOffset    = 0.05;  // only used in outOfFrame version
  
  float relPosX    = 0.045;
  float relPosY    = 0.035;
  float relExtraDY = 1.2;
  //float relExtraDY = 0;
  
  // ratio of "CMS" and extra text size
  float extraOverCmsTextSize  = 0.76;
  
  TString lumi_13TeV = "20.1 fb^{-1}";
  TString lumi_8TeV  = "18.9 fb^{-1}";
  TString lumi_7TeV  = "5.1 fb^{-1}";

  bool drawLogo      = false;


  //C file

  bool outOfFrame    = true;
  if( iPosX/10==0 ) 
    {
      outOfFrame = true;
    }
  int alignY_=3;
  int alignX_=2;
  if( iPosX/10==0 ) alignX_=1;
  if( iPosX==0    ) alignX_=1;
  if( iPosX==0    ) alignY_=1;
  if( iPosX/10==1 ) alignX_=1;
  if( iPosX/10==2 ) alignX_=2;
  if( iPosX/10==3 ) alignX_=3;
  if( iPosX == 0  ) relPosX = 0.12;
  int align_ = 10*alignX_ + alignY_;

  float H = pad->GetWh();
  float W = pad->GetWw();
  float l = pad->GetLeftMargin();
  float t = pad->GetTopMargin();
  float r = pad->GetRightMargin();
  float b = pad->GetBottomMargin();
  //  float e = 0.025;

  pad->cd();

  TString lumiText;
  if( iPeriod==1 )
    {
      lumiText += lumi_7TeV;
      lumiText += " (7 TeV)";
    }
  else if ( iPeriod==2 )
    {
      lumiText += lumi_8TeV;
      lumiText += " (8 TeV)";
    }
  else if( iPeriod==3 ) 
    {
      lumiText = lumi_8TeV; 
      lumiText += " (8 TeV)";
      lumiText += " + ";
      lumiText += lumi_7TeV;
      lumiText += " (7 TeV)";
    }
  else if ( iPeriod==4 )
    {
      lumiText += lumi_13TeV;
      lumiText += " (13 TeV)";
    }
  else if ( iPeriod==7 )
    { 
      if( outOfFrame ) lumiText += "#scale[0.85]{";
      lumiText += lumi_13TeV; 
      lumiText += " (13 TeV)";
      lumiText += " + ";
      lumiText += lumi_8TeV; 
      lumiText += " (8 TeV)";
      lumiText += " + ";
      lumiText += lumi_7TeV;
      lumiText += " (7 TeV)";
      if( outOfFrame) lumiText += "}";
    }
  else if ( iPeriod==12 )
    {
      lumiText += "8 TeV";
    }
   
  cout << lumiText << endl;

  TLatex latex;
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);    

  float extraTextSize = extraOverCmsTextSize*cmsTextSize;

  latex.SetTextFont(42);
  latex.SetTextAlign(31); 
  latex.SetTextSize(lumiTextSize*t);    
  latex.DrawLatex(1-r,1-t+lumiTextOffset*t,lumiText);

  if( outOfFrame )
    {
      latex.SetTextFont(cmsTextFont);
      latex.SetTextAlign(11); 
      latex.SetTextSize(cmsTextSize*t);    
      latex.DrawLatex(l,1-t+lumiTextOffset*t,cmsText);
    }
  
  pad->cd();

  float posX_=0;
  if( iPosX%10<=1 )
    {
      posX_ =   l + relPosX*(1-l-r);
    }
  else if( iPosX%10==2 )
    {
      posX_ =  l + 0.5*(1-l-r);
    }
  else if( iPosX%10==3 )
    {
      posX_ =  1-r - relPosX*(1-l-r);
    }
  float posY_ = 1-t - relPosY*(1-t-b);
  if( !outOfFrame )
    {
      if( drawLogo )
	{
	  posX_ =   l + 0.045*(1-l-r)*W/H;
	  posY_ = 1-t - 0.045*(1-t-b);
	  float xl_0 = posX_;
	  float yl_0 = posY_ - 0.15;
	  float xl_1 = posX_ + 0.15*H/W;
	  float yl_1 = posY_;
	  TASImage* CMS_logo = new TASImage("CMS-BW-label.png");
	  TPad* pad_logo = new TPad("logo","logo", xl_0, yl_0, xl_1, yl_1 );
	  pad_logo->Draw();
	  pad_logo->cd();
	  CMS_logo->Draw("X");
	  pad_logo->Modified();
	  pad->cd();
	}
      else
	{
	  latex.SetTextFont(cmsTextFont);
	  latex.SetTextSize(cmsTextSize*t);
	  latex.SetTextAlign(align_);
	  latex.DrawLatex(posX_, posY_, cmsText);
	  if( writeExtraText ) 
	    {
	      latex.SetTextFont(extraTextFont);
	      latex.SetTextAlign(align_);
	      latex.SetTextSize(extraTextSize*t);
	      latex.DrawLatex(posX_, posY_- relExtraDY*cmsTextSize*t, extraText);
	    }
	}
    }
  else if( writeExtraText )
    {
      if( iPosX==0) 
	{
	  posX_ =   l +  relPosX*(1-l-r);
	  posY_ =   1-t+lumiTextOffset*t;
	}
      latex.SetTextFont(extraTextFont);
      latex.SetTextSize(extraTextSize*t);
      latex.SetTextAlign(align_);
      cout << "posY_ " << posY_ << endl;
      //latex.DrawLatex(posX_, posY_, extraText);      
      latex.DrawLatex(posX_+.08, posY_+.063, extraText);      
    }
  return;
}
   














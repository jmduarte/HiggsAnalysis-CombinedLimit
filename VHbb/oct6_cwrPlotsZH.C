#include "plotEverything2.h"
#include "TSpline.h"
#include "TGraphSmooth.h"

void redo_colors(std::vector<graph> & graphs){

  for(unsigned int i =0; i<graphs.size(); i++){
    int color = 0;
    if(i<=1) graphs[i].color = kBlack;
    else if(i<=3) graphs[i].color = kBlue-6;
    else graphs[i].color = kRed-9;
    //cout << "COLOR: " << graphs_VH[i].color << endl;
  }

}

void oct6_cwrPlotsZH(){
  cout << "Plot everything 2" << endl;

  /////////////////////////////
  // Create graphs
  /////////////////////////////

  TString global_transformation = "fa3zzTozz";
  TString results_variable = "results_fa3zz"; // "results_fa3

  //Wh
  graph g_Wh_CMS_common_expected;
  g_Wh_CMS_common_expected.file_name = "/uscms_data/d2/kreis/junFreeze/Wh_CMS_common_expected_minuit2_0p1_tries5_strategy1.combine.root";
  g_Wh_CMS_common_expected.legend_name = "WH expected";
  g_Wh_CMS_common_expected.color = kGreen+2; 
  g_Wh_CMS_common_expected.linestyle = 9; 
  g_Wh_CMS_common_expected.do_all_prep();

  graph g_Wh_CMS_common_expected_WW;
  g_Wh_CMS_common_expected_WW.file_name = "/uscms_data/d2/kreis/junFreeze/Wh_CMS_common_expected_minuit2_0p1_tries5_strategy1.combine.root";
  g_Wh_CMS_common_expected_WW.legend_name = "WH expected";
  g_Wh_CMS_common_expected_WW.color = kGreen+2; 
  g_Wh_CMS_common_expected_WW.linestyle = 9; 
  g_Wh_CMS_common_expected_WW.add_last_point_switch = true;
  g_Wh_CMS_common_expected_WW.do_all_prep("fa3zhToww");

  graph g_Wh_CMS_common_observed;
  g_Wh_CMS_common_observed.file_name = "/uscms_data/d2/kreis/junFreeze/Wh_CMS_common_observed_minuit2_0p1_tries5_strategy1.combine.root";
  g_Wh_CMS_common_observed.legend_name = "WH observed";
  g_Wh_CMS_common_observed.color = kGreen+2; 
  g_Wh_CMS_common_observed.linestyle = 1; 
  g_Wh_CMS_common_observed.do_all_prep();

  graph g_Wh_CMS_common_observed_WW;
  g_Wh_CMS_common_observed_WW.file_name = "/uscms_data/d2/kreis/junFreeze/Wh_CMS_common_observed_minuit2_0p1_tries5_strategy1.combine.root";
  g_Wh_CMS_common_observed_WW.legend_name = "WH observed";
  g_Wh_CMS_common_observed_WW.color = kGreen+2; 
  g_Wh_CMS_common_observed_WW.linestyle = 1; 
  g_Wh_CMS_common_observed_WW.add_last_point_switch = true; 
  g_Wh_CMS_common_observed_WW.do_all_prep("fa3zhToww");

  graph g_Wh_TEV_common_expected;
  g_Wh_TEV_common_expected.file_name = "/uscms_data/d2/kreis/junFreeze/lambdaNominal_Wh_TEV_common_expected_minuit2_0p1_tries5_strategy1.combine.root";
  g_Wh_TEV_common_expected.legend_name = "WH expected";
  g_Wh_TEV_common_expected.color = kGreen+2; 
  g_Wh_TEV_common_expected.linestyle = 9; 
  g_Wh_TEV_common_expected.do_all_prep();

  graph g_Wh_TEV_common_observed;
  g_Wh_TEV_common_observed.file_name = "/uscms_data/d2/kreis/junFreeze/lambdaNominal_Wh_TEV_common_observed_minuit2_0p1_tries5_strategy1.combine.root";
  g_Wh_TEV_common_observed.legend_name = "WH observed";
  g_Wh_TEV_common_observed.color = kGreen+2; 
  g_Wh_TEV_common_observed.linestyle = 1; 
  g_Wh_TEV_common_observed.do_all_prep();

  //Zh
  graph g_Zh_CMS_common_expected;
  g_Zh_CMS_common_expected.file_name = "/uscms_data/d2/kreis/junFreeze/Zh_CMS_common_expected_minuit2_0p1_tries5_strategy1.combine.root";
  g_Zh_CMS_common_expected.legend_name = "ZH expected";
  g_Zh_CMS_common_expected.color = kAzure-2; 
  g_Zh_CMS_common_expected.linestyle = 9; 
  g_Zh_CMS_common_expected.do_all_prep();

  graph g_Zh_CMS_common_expected_ZZ;
  g_Zh_CMS_common_expected_ZZ.file_name = "/uscms_data/d2/kreis/junFreeze/Zh_CMS_common_expected_minuit2_0p1_tries5_strategy1.combine.root";
  g_Zh_CMS_common_expected_ZZ.legend_name = "ZH expected";
  g_Zh_CMS_common_expected_ZZ.color = kAzure-2; 
  g_Zh_CMS_common_expected_ZZ.linestyle = 9; 
  g_Zh_CMS_common_expected_ZZ.add_last_point_switch = true; 
  g_Zh_CMS_common_expected_ZZ.do_all_prep();

  graph g_Zh_CMS_common_observed;
  g_Zh_CMS_common_observed.file_name = "/uscms_data/d2/kreis/junFreeze/Zh_CMS_common_observed_minuit2_0p1_tries5_strategy1.combine.root";
  g_Zh_CMS_common_observed.legend_name = "ZH observed";
  g_Zh_CMS_common_observed.color = kAzure-2; 
  g_Zh_CMS_common_observed.linestyle = 1; 
  g_Zh_CMS_common_observed.do_all_prep();

  graph g_Zh_CMS_common_observed_ZZ;
  g_Zh_CMS_common_observed_ZZ.file_name = "/uscms_data/d2/kreis/junFreeze/Zh_CMS_common_observed_minuit2_0p1_tries5_strategy1.combine.root";
  g_Zh_CMS_common_observed_ZZ.legend_name = "ZH observed";
  g_Zh_CMS_common_observed_ZZ.kill.push_back(0.038);
  g_Zh_CMS_common_observed_ZZ.kill.push_back(0.041);
  g_Zh_CMS_common_observed_ZZ.color = kAzure-2; 
  g_Zh_CMS_common_observed_ZZ.linestyle = 1; 
  g_Zh_CMS_common_observed_ZZ.add_last_point_switch = true; 
  g_Zh_CMS_common_observed_ZZ.do_all_prep();

  graph g_Zh_TEV_common_expected;
  g_Zh_TEV_common_expected.file_name = "/uscms_data/d2/kreis/junFreeze/lambdaNominal_Zh_TEV_common_expected_minuit2_0p1_tries5_strategy1.combine.root";
  g_Zh_TEV_common_expected.legend_name = "ZH expected";
  g_Zh_TEV_common_expected.color = kAzure-2; 
  g_Zh_TEV_common_expected.linestyle = 9; 
  g_Zh_TEV_common_expected.do_all_prep();

  graph g_Zh_TEV_common_observed;
  g_Zh_TEV_common_observed.file_name = "/uscms_data/d2/kreis/junFreeze/lambdaNominal_Zh_TEV_common_observed_minuit2_0p1_tries5_strategy1.combine.root";
  g_Zh_TEV_common_observed.legend_name = "ZH observed";
  g_Zh_TEV_common_observed.color = kAzure-2; 
  g_Zh_TEV_common_observed.linestyle = 1; 
  g_Zh_TEV_common_observed.do_all_prep();


  //Vh
  graph g_Vh_CMS_common_expected;
  g_Vh_CMS_common_expected.file_name = "/uscms_data/d2/kreis/junFreeze/Vh_CMS_common_expected_minuit2_0p1_tries5_strategy1.combine.root";
  g_Vh_CMS_common_expected.legend_name = "VH expected";
  g_Vh_CMS_common_expected.color = kRed; 
  g_Vh_CMS_common_expected.linestyle = 9; 
  g_Vh_CMS_common_expected.do_all_prep();

  graph g_Vh_CMS_common_expected_ZZ;
  g_Vh_CMS_common_expected_ZZ.file_name = "/uscms_data/d2/kreis/junFreeze/Vh_CMS_common_expected_minuit2_0p1_tries5_strategy1.combine.root";
  g_Vh_CMS_common_expected_ZZ.legend_name = "VH expected";
  g_Vh_CMS_common_expected_ZZ.color = kRed; 
  g_Vh_CMS_common_expected_ZZ.linestyle = 9; 
  g_Vh_CMS_common_expected_ZZ.add_last_point_switch = true;
  g_Vh_CMS_common_expected_ZZ.do_all_prep("fa3zhTozz");

  graph g_Vh_CMS_common_observed;
  g_Vh_CMS_common_observed.file_name = "/uscms_data/d2/kreis/junFreeze/Vh_CMS_common_observed_minuit_0p1_tries5_strategy1.combine.root";
  g_Vh_CMS_common_observed.legend_name = "VH observed";
  g_Vh_CMS_common_observed.color = kRed; 
  g_Vh_CMS_common_observed.linestyle = 1; 
  g_Vh_CMS_common_observed.do_all_prep();

  graph g_Vh_CMS_common_observed_ZZ;
  g_Vh_CMS_common_observed_ZZ.file_name = "/uscms_data/d2/kreis/junFreeze/Vh_CMS_common_observed_minuit_0p1_tries5_strategy1.combine.root";
  g_Vh_CMS_common_observed_ZZ.legend_name = "VH observed";
  g_Vh_CMS_common_observed_ZZ.color = kRed; 
  g_Vh_CMS_common_observed_ZZ.linestyle = 1; 
  g_Vh_CMS_common_observed_ZZ.add_last_point_switch = true;
  g_Vh_CMS_common_observed_ZZ.do_all_prep("fa3zhTozz");

  graph g_Vh_TEV_common_expected;
  g_Vh_TEV_common_expected.file_name = "/uscms_data/d2/kreis/junFreeze/lambdaNominal_Vh_TEV_common_expected_minuit2_0p1_tries5_strategy1.combine.root";
  g_Vh_TEV_common_expected.legend_name = "VH expected";
  g_Vh_TEV_common_expected.color = kRed; 
  g_Vh_TEV_common_expected.linestyle = 9; 
  g_Vh_TEV_common_expected.do_all_prep();

  graph g_Vh_TEV_common_observed;
  g_Vh_TEV_common_observed.file_name = "/uscms_data/d2/kreis/junFreeze/lambdaNominal_Vh_TEV_common_observed_minuit2_0p1_tries5_strategy1.combine.root";
  g_Vh_TEV_common_observed.legend_name = "VH observed";
  g_Vh_TEV_common_observed.color = kRed; 
  g_Vh_TEV_common_observed.linestyle = 1; 
  g_Vh_TEV_common_observed.do_all_prep();


  //WW
  graph g_WW_CMS_expected_WW;
 g_WW_CMS_expected_WW.file_name = "/eos/uscms/store/user/lpcmbja/noreplica/jstupak/fa3Scans/hVV_newGrid/WW_CMS_common_expected_minuit2_0p1_tries5_strategy1.combine.root";
  g_WW_CMS_expected_WW.legend_name = "WW expected";
  g_WW_CMS_expected_WW.color = kCyan+1; 
  g_WW_CMS_expected_WW.linestyle = 9; 
  g_WW_CMS_expected_WW.do_all_prep("fa3zzToww");

  graph g_WW_CMS_observed_WW;
  g_WW_CMS_observed_WW.file_name = "/eos/uscms/store/user/lpcmbja/noreplica/jstupak/fa3Scans/hVV_newGrid/WW_CMS_common_observed_minuit2_0p01_tries5_strategy1.combine.root";
  g_WW_CMS_observed_WW.legend_name = "WW observed";
  g_WW_CMS_observed_WW.color = kCyan+1; 
  g_WW_CMS_observed_WW.linestyle = 1; 
  g_WW_CMS_observed_WW.do_all_prep("fa3zzToww");

  //ZZ
  graph g_ZZ_CMS_expected;
 g_ZZ_CMS_expected.file_name = "/eos/uscms/store/user/lpcmbja/noreplica/jstupak/fa3Scans/hVV_newGrid/ZZ_CMS_common_expected_minuit2_0p1_tries5_strategy1.combine.root";
  g_ZZ_CMS_expected.legend_name = "ZZ expected";
  g_ZZ_CMS_expected.color = kTeal+2; 
  g_ZZ_CMS_expected.linestyle = 9; 
  g_ZZ_CMS_expected.do_all_prep("fa3zzTozh");

  graph g_ZZ_CMS_observed;
  g_ZZ_CMS_observed.file_name = "/eos/uscms/store/user/lpcmbja/noreplica/jstupak/fa3Scans/hVV_newGrid/ZZ_CMS_common_observed_minuit2_0p1_tries5_strategy1.combine.root";
  g_ZZ_CMS_observed.legend_name = "ZZ observed";
  g_ZZ_CMS_observed.color = kTeal+2; 
  g_ZZ_CMS_observed.linestyle = 1; 
  g_ZZ_CMS_observed.do_all_prep("fa3zzTozh");


  //VV
  graph g_VV_CMS_expected;
  g_VV_CMS_expected.file_name = "/eos/uscms/store/user/lpcmbja/noreplica/jstupak/fa3Scans/072015/correctHVVCards/VV_CMS_common_expected_minuit2_0p1_tries5_strategy1.combine.root";//new jul25
  g_VV_CMS_expected.legend_name = "VV expected";
  g_VV_CMS_expected.color = kOrange+7; 
  g_VV_CMS_expected.linestyle = 9; 
  g_VV_CMS_expected.do_all_prep();

  graph g_VV_CMS_observed;
  g_VV_CMS_observed.file_name = "/eos/uscms/store/user/lpcmbja/noreplica/jstupak/fa3Scans/072015/correctHVVCards/VV_CMS_common_observed_minuit2_0p1_tries5_strategy1.combine.root";//new jul25
  g_VV_CMS_observed.legend_name = "VV observed";
  g_VV_CMS_observed.color = kOrange+7; 
  g_VV_CMS_observed.linestyle = 1; 
  g_VV_CMS_observed.do_all_prep();

  //WWWh
  graph g_WWWh_CMS_common_expected_WW;
  g_WWWh_CMS_common_expected_WW.file_name = "/uscms_data/d2/kreis/junFreeze/WWWh_CMS_common_expected_minuit_0p1_tries5_strategy1.combine.root";
  g_WWWh_CMS_common_expected_WW.legend_name = "WH+WW expected (correlated #mu)";
  g_WWWh_CMS_common_expected_WW.scale = "0.1"; 
  g_WWWh_CMS_common_expected_WW.color = kViolet; 
  g_WWWh_CMS_common_expected_WW.linestyle = 9; 
  g_WWWh_CMS_common_expected_WW.do_all_prep("fa3zzToww");

  graph g_WWWh_CMS_common_expected_WW_noScale;
  g_WWWh_CMS_common_expected_WW_noScale.file_name = "/uscms_data/d2/kreis/junFreeze/WWWh_CMS_common_expected_minuit_0p1_tries5_strategy1.combine.root";
  g_WWWh_CMS_common_expected_WW_noScale.legend_name = "WH+WW expected (correlated #mu)";
  g_WWWh_CMS_common_expected_WW_noScale.color = kViolet; 
  g_WWWh_CMS_common_expected_WW_noScale.linestyle = 9; 
  g_WWWh_CMS_common_expected_WW_noScale.do_all_prep("fa3zzToww");

  graph g_WWWh_CMS_common_expected_noScale;
  g_WWWh_CMS_common_expected_noScale.file_name = "/uscms_data/d2/kreis/junFreeze/WWWh_CMS_common_expected_minuit_0p1_tries5_strategy1.combine.root";
  g_WWWh_CMS_common_expected_noScale.legend_name = "WH+WW expected (correlated #mu)";
  g_WWWh_CMS_common_expected_noScale.color = kViolet; 
  g_WWWh_CMS_common_expected_noScale.linestyle = 9; 
  g_WWWh_CMS_common_expected_noScale.do_all_prep();

  graph g_WWWh_CMS_float_expected_WW;
  g_WWWh_CMS_float_expected_WW.file_name = "/uscms_data/d2/kreis/junFreeze/WWWh_CMS_float_expected_minuit_0p001_tries5_strategy1.combine.root";
  g_WWWh_CMS_float_expected_WW.kill.push_back(0.984);
  g_WWWh_CMS_float_expected_WW.kill.push_back(0.998);
  g_WWWh_CMS_float_expected_WW.kill.push_back(0.999);
  g_WWWh_CMS_float_expected_WW.kill.push_back(0.9991);
  g_WWWh_CMS_float_expected_WW.legend_name = "WH+WW expected";
  g_WWWh_CMS_float_expected_WW.color = kOrange; 
  g_WWWh_CMS_float_expected_WW.linestyle = 9; 
  g_WWWh_CMS_float_expected_WW.do_all_prep("fa3zzToww");
  


  graph g_WWWh_CMS_common_observed_WW;
  g_WWWh_CMS_common_observed_WW.file_name = "/uscms_data/d2/kreis/junFreeze/WWWh_CMS_common_observed_minuit_0p005_tries5_strategy1.combine.root";
  g_WWWh_CMS_common_observed_WW.kill.push_back(0.33);
  g_WWWh_CMS_common_observed_WW.kill.push_back(0.35);
  g_WWWh_CMS_common_observed_WW.kill.push_back(0.59);
  g_WWWh_CMS_common_observed_WW.kill.push_back(0.62);
  g_WWWh_CMS_common_observed_WW.kill.push_back(0.61);
  g_WWWh_CMS_common_observed_WW.kill.push_back(0.63);
  g_WWWh_CMS_common_observed_WW.kill.push_back(0.65);
  g_WWWh_CMS_common_observed_WW.kill.push_back(0.67);
  g_WWWh_CMS_common_observed_WW.legend_name = "WH+WW observed (correlated #mu)";
  g_WWWh_CMS_common_observed_WW.scale = "0.1"; 
  g_WWWh_CMS_common_observed_WW.color = kViolet; 
  g_WWWh_CMS_common_observed_WW.linestyle = 1; 
  g_WWWh_CMS_common_observed_WW.do_all_prep("fa3zzToww");

  graph g_WWWh_CMS_common_observed_WW_noScale;
  g_WWWh_CMS_common_observed_WW_noScale.file_name = "/uscms_data/d2/kreis/junFreeze/WWWh_CMS_common_observed_minuit_0p005_tries5_strategy1.combine.root";
  g_WWWh_CMS_common_observed_WW_noScale.kill.push_back(0.33);
  g_WWWh_CMS_common_observed_WW_noScale.kill.push_back(0.35);
  g_WWWh_CMS_common_observed_WW_noScale.kill.push_back(0.59);
  g_WWWh_CMS_common_observed_WW_noScale.kill.push_back(0.62);
  g_WWWh_CMS_common_observed_WW_noScale.kill.push_back(0.61);
  g_WWWh_CMS_common_observed_WW_noScale.kill.push_back(0.63);
  g_WWWh_CMS_common_observed_WW_noScale.kill.push_back(0.65);
  g_WWWh_CMS_common_observed_WW_noScale.kill.push_back(0.67);
  g_WWWh_CMS_common_observed_WW_noScale.legend_name = "WH+WW observed (correlated #mu)";
  g_WWWh_CMS_common_observed_WW_noScale.color = kViolet; 
  g_WWWh_CMS_common_observed_WW_noScale.linestyle = 1; 
  g_WWWh_CMS_common_observed_WW_noScale.do_all_prep("fa3zzToww");

  graph g_WWWh_CMS_common_observed_noScale;
  g_WWWh_CMS_common_observed_noScale.file_name = "/uscms_data/d2/kreis/junFreeze/WWWh_CMS_common_observed_minuit_0p005_tries5_strategy1.combine.root";
  g_WWWh_CMS_common_observed_noScale.kill.push_back(0.33);
  g_WWWh_CMS_common_observed_noScale.kill.push_back(0.35);
  g_WWWh_CMS_common_observed_noScale.kill.push_back(0.59);
  g_WWWh_CMS_common_observed_noScale.kill.push_back(0.62);
  g_WWWh_CMS_common_observed_noScale.kill.push_back(0.61);
  g_WWWh_CMS_common_observed_noScale.kill.push_back(0.63);
  g_WWWh_CMS_common_observed_noScale.kill.push_back(0.65);
  g_WWWh_CMS_common_observed_noScale.kill.push_back(0.67);
  g_WWWh_CMS_common_observed_noScale.legend_name = "WH+WW observed (correlated #mu)";
  g_WWWh_CMS_common_observed_noScale.color = kViolet; 
  g_WWWh_CMS_common_observed_noScale.linestyle = 1; 
  g_WWWh_CMS_common_observed_noScale.do_all_prep();//fa3zz

  graph g_WWWh_CMS_float_observed_WW;
  //g_WWWh_CMS_float_observed_WW.file_name_vector.push_back("/uscms_data/d2/kreis/junFreeze/WWWh_CMS_float_observed_minuit_0p0001_tries5_strategy0.combine.root");
  //g_WWWh_CMS_float_observed_WW.file_name_vector.push_back("/uscms_data/d2/kreis/junFreeze/WWWh_CMS_float_observed_minuit2_0p001_tries5_strategy0.combine.root");
  g_WWWh_CMS_float_observed_WW.file_name = "/eos/uscms/store/user/lpcmbja/noreplica/zzDR_p0plusp1_050915_correlatedBkg_sigThrsld2.5_deCorrdMedHighNuis_trendGuessObserved_snapshot_fixp75/WWWh_CMS_float_observed_minuit_0p001_tries5_strategy1.combine.root";
  /*  
  g_WWWh_CMS_float_observed_WW.stitch_point_vector.push_back(0.3);
  g_WWWh_CMS_float_observed_WW.stitch_point_vector.push_back(1);
  g_WWWh_CMS_float_observed_WW.match_point_vector.push_back(.2);
  g_WWWh_CMS_float_observed_WW.kill.push_back(0.09);
  g_WWWh_CMS_float_observed_WW.kill.push_back(0.13);
  g_WWWh_CMS_float_observed_WW.kill.push_back(0.145);
  g_WWWh_CMS_float_observed_WW.kill.push_back(0.156);
  g_WWWh_CMS_float_observed_WW.kill.push_back(0.175);
  g_WWWh_CMS_float_observed_WW.kill.push_back(0.185);
*/
  g_WWWh_CMS_float_observed_WW.kill.push_back(0.745);
  g_WWWh_CMS_float_observed_WW.kill.push_back(0.755);
  g_WWWh_CMS_float_observed_WW.legend_name = "WH+WW observed";
  g_WWWh_CMS_float_observed_WW.color = kOrange; 
  g_WWWh_CMS_float_observed_WW.linestyle = 1; 
  g_WWWh_CMS_float_observed_WW.do_all_prep("fa3zzToww");
  
  
  

  //ZZZh
  graph g_ZZZh_CMS_common_expected;
  g_ZZZh_CMS_common_expected.file_name = "/uscms_data/d2/kreis/junFreeze/ZZZh_CMS_common_expected_minuit_0p1_tries5_strategy1.combine.root";
  g_ZZZh_CMS_common_expected.legend_name = "ZH+ZZ expected (correlated #mu)";
  g_ZZZh_CMS_common_expected.scale = "0.3"; 
  g_ZZZh_CMS_common_expected.color = kRed+2; 
  g_ZZZh_CMS_common_expected.linestyle = 9; 
  g_ZZZh_CMS_common_expected.do_all_prep();

  graph g_ZZZh_CMS_common_expected_noScale;
  g_ZZZh_CMS_common_expected_noScale.file_name = "/uscms_data/d2/kreis/junFreeze/ZZZh_CMS_common_expected_minuit_0p1_tries5_strategy1.combine.root";
  g_ZZZh_CMS_common_expected_noScale.legend_name = "ZH+ZZ expected (correlated #mu)";
  g_ZZZh_CMS_common_expected_noScale.color = kRed+2; 
  g_ZZZh_CMS_common_expected_noScale.linestyle = 9; 
  g_ZZZh_CMS_common_expected_noScale.do_all_prep();

  graph g_ZZZh_CMS_float_expected;
  g_ZZZh_CMS_float_expected.file_name = "/uscms_data/d2/kreis/junFreeze/ZZZh_CMS_float_expected_minuit_0p1_tries5_strategy1.combine.root";
  g_ZZZh_CMS_float_expected.legend_name = "ZH+ZZ expected";
  g_ZZZh_CMS_float_expected.color = kViolet-6; 
  g_ZZZh_CMS_float_expected.linestyle = 9; 
  g_ZZZh_CMS_float_expected.do_all_prep("fa3zzTozh");

  graph g_ZZZh_CMS_common_observed;
  g_ZZZh_CMS_common_observed.file_name = "/uscms_data/d2/kreis/junFreeze/ZZZh_CMS_common_observed_minuit_0p1_tries5_strategy1.combine.root";
  g_ZZZh_CMS_common_observed.legend_name = "ZH+ZZ observed (correlated #mu)";
  g_ZZZh_CMS_common_observed.scale = "0.3"; 
  g_ZZZh_CMS_common_observed.color = kRed+2; 
  g_ZZZh_CMS_common_observed.linestyle = 1; 
  g_ZZZh_CMS_common_observed.do_all_prep();

  graph g_ZZZh_CMS_common_observed_noScale;
  g_ZZZh_CMS_common_observed_noScale.file_name = "/uscms_data/d2/kreis/junFreeze/ZZZh_CMS_common_observed_minuit_0p1_tries5_strategy1.combine.root";
  g_ZZZh_CMS_common_observed_noScale.legend_name = "ZH+ZZ observed (correlated #mu)";
  g_ZZZh_CMS_common_observed_noScale.color = kRed+2; 
  g_ZZZh_CMS_common_observed_noScale.linestyle = 1; 
  g_ZZZh_CMS_common_observed_noScale.do_all_prep();

  graph g_ZZZh_CMS_float_observed;
  g_ZZZh_CMS_float_observed.file_name = "/uscms_data/d2/kreis/junFreeze/ZZZh_CMS_float_observed_minuit_0p1_tries5_strategy1.combine.root";
  g_ZZZh_CMS_float_observed.legend_name = "ZH+ZZ observed";
  g_ZZZh_CMS_float_observed.color = kViolet-6; 
  g_ZZZh_CMS_float_observed.linestyle = 1; 
  g_ZZZh_CMS_float_observed.do_all_prep("fa3zzTozh");


  //VVVh
  graph g_VVVh_CMS_common_expected;
  //g_VVVh_CMS_common_expected.file_name = "/eos/uscms/store/user/lpcmbja/noreplica/zzDR_p0plusp1_050915_correlatedBkg_sigThrsld2.5_deCorrdMedHighNuis_correctHVVCards/VVVh_CMS_common_expected_minuit_0p1_tries5_strategy0.combine.root";//new jul25  
  g_VVVh_CMS_common_expected.file_name = "/eos/uscms/store/user/lpcmbja/noreplica/zzDR_p0plusp1_050915_correlatedBkg_sigThrsld2.5_deCorrdMedHighNuis_correctHVVCards/VVVh_CMS_common_expected_minuit2_0p01_tries5_strategy0.combine.root";
  g_VVVh_CMS_common_expected.legend_name = "VH+VV expected (correlated #mu)";
  g_VVVh_CMS_common_expected.scale = "0.2"; 
  g_VVVh_CMS_common_expected.color = kBlue; 
  g_VVVh_CMS_common_expected.linestyle = 9; 
  g_VVVh_CMS_common_expected.do_all_prep();
  
  graph g_VVVh_CMS_common_expected_noScale;
  g_VVVh_CMS_common_expected_noScale.file_name = "/eos/uscms/store/user/lpcmbja/noreplica/zzDR_p0plusp1_050915_correlatedBkg_sigThrsld2.5_deCorrdMedHighNuis_correctHVVCards/VVVh_CMS_common_expected_minuit2_0p01_tries5_strategy0.combine.root";//new jul 25
  g_VVVh_CMS_common_expected_noScale.legend_name = "VH+VV expected (correlated #mu)";
  g_VVVh_CMS_common_expected_noScale.color = kBlue; 
  g_VVVh_CMS_common_expected_noScale.linestyle = 9; 
  g_VVVh_CMS_common_expected_noScale.do_all_prep();

  graph g_VVVh_CMS_float_expected;
  g_VVVh_CMS_float_expected.file_name = "/eos/uscms/store/user/lpcmbja/noreplica/zzDR_p0plusp1_050915_correlatedBkg_sigThrsld2.5_deCorrdMedHighNuis_correctHVVCards/VVVh_CMS_float_expected_minuit_0p005_tries5_strategy1.combine.root";//new jul 25
  g_VVVh_CMS_float_expected.legend_name = "VH+VV expected";
  g_VVVh_CMS_float_expected.color = kBlue-9; 
  g_VVVh_CMS_float_expected.linestyle = 9; 
  g_VVVh_CMS_float_expected.do_all_prep();

  graph g_VVVh_CMS_common_observed;
  g_VVVh_CMS_common_observed.file_name = "/eos/uscms/store/user/lpcmbja/noreplica/zzDR_p0plusp1_050915_correlatedBkg_sigThrsld2.5_deCorrdMedHighNuis_correctHVVCards_snapshot/VVVh_CMS_common_observed_minuit_0p1_tries5_strategy1.combine.root";//jul25
  g_VVVh_CMS_common_observed.legend_name = "VH+VV observed (correlated #mu)";
  g_VVVh_CMS_common_observed.scale = "0.2"; 
  g_VVVh_CMS_common_observed.color = kBlue; 
  g_VVVh_CMS_common_observed.linestyle = 1; 
  g_VVVh_CMS_common_observed.do_all_prep();


  graph g_VVVh_CMS_common_observed_noScale;
  g_VVVh_CMS_common_observed_noScale.file_name = "/eos/uscms/store/user/lpcmbja/noreplica/zzDR_p0plusp1_050915_correlatedBkg_sigThrsld2.5_deCorrdMedHighNuis_correctHVVCards_snapshot/VVVh_CMS_common_observed_minuit2_0p1_tries5_strategy1.combine.root";//jul25
  g_VVVh_CMS_common_observed_noScale.legend_name = "VH+VV observed (correlated #mu)";
  g_VVVh_CMS_common_observed_noScale.color = kBlue; 
  g_VVVh_CMS_common_observed_noScale.linestyle = 1; 
  g_VVVh_CMS_common_observed_noScale.do_all_prep();


  graph g_VVVh_CMS_float_observed;
  g_VVVh_CMS_float_observed.file_name_vector.push_back("/eos/uscms/store/user/lpcmbja/noreplica/zzDR_p0plusp1_050915_correlatedBkg_sigThrsld2.5_deCorrdMedHighNuis_correctHVVCards/VVVh_CMS_float_observed_minuit_0p0005_tries5_strategy1.combine.root");//jul25
  g_VVVh_CMS_float_observed.file_name_vector.push_back("/eos/uscms/store/user/lpcmbja/noreplica/zzDR_p0plusp1_050915_correlatedBkg_sigThrsld2.5_deCorrdMedHighNuis_correctHVVCards_snapshot/VVVh_CMS_float_observed_minuit_0p001_tries5_strategy1.combine.root");//jul25
  g_VVVh_CMS_float_observed.stitch_point_vector.push_back(0.12);
  g_VVVh_CMS_float_observed.stitch_point_vector.push_back(1);
  g_VVVh_CMS_float_observed.match_point_vector.push_back(0.1);
  g_VVVh_CMS_float_observed.legend_name = "VH+VV observed";
  g_VVVh_CMS_float_observed.color = kBlue-9; 
  g_VVVh_CMS_float_observed.linestyle = 1; 
  g_VVVh_CMS_float_observed.do_all_prep();
  
  /*
  //SMOOTHING TEST
  //////////////////
  TCanvas* c1 = new TCanvas();
  TH1F* hs1 = c1->DrawFrame(0, 0, 1, 70);
  g_WWWh_CMS_float_observed_WW.gr->Draw("LP");
  //g_WWWh_CMS_float_observed_WW.gr->Fit("pol9");

  TGraphSmooth *gs = new TGraphSmooth("normal");
  //TGraph* grout = gs->SmoothKern(g_WWWh_CMS_float_observed_WW.gr,"normal",.1);//kernel // doesn't work well for me
  //TGraph* grout = gs->SmoothSuper(g_WWWh_CMS_float_observed_WW.gr,"",0,0);//super
  TGraph* grout = gs->SmoothSuper(g_WWWh_CMS_float_observed_WW.gr,"",.01);//super
  //TGraph* grout = gs->SmoothLowess(g_WWWh_CMS_float_observed_WW.gr,"",0.2);
  grout->Draw("LPX");

  //other attempt I have not got working yet
  //TSpline *s = new TSpline3("grs",g_WWWh_CMS_float_observed_WW.gr);
  //s->SetLineColor(kGreen);
  //s->Draw("c same");
  //s->Draw("c");
  */


  /////////////////////////////
  // Create figures
  /////////////////////////////


  //std::vector<graph> graphs_VVVh;
  /*
  //graphs_VVVh.push_back(g_WWWh_CMS_common_expected);
  ////graphs_VVVh.push_back(g_WWWh_CMS_common_observed);
  //graphs_VVVh.push_back(g_WWWh_CMS_float_expected);
  //graphs_VVVh.push_back(g_WWWh_CMS_float_observed);
  //graphs_VVVh.push_back(g_ZZZh_CMS_common_expected);
  //graphs_VVVh.push_back(g_ZZZh_CMS_common_observed);
  //graphs_VVVh.push_back(g_ZZZh_CMS_float_expected);
  //graphs_VVVh.push_back(g_ZZZh_CMS_float_observed);
  //graphs_VVVh.push_back(g_VVVh_CMS_common_expected);
  //graphs_VVVh.push_back(g_VVVh_CMS_common_observed);
  //graphs_VVVh.push_back(g_VVVh_CMS_float_expected);
  ////graphs_VVVh.push_back(g_VVVh_CMS_float_observed);
  
  figure f_VVVh;
  f_VVVh.figure_name = prepend +"VVVh";
  f_VVVh.x_title = "f_{a3}^{ZZ}";
  //f_VVVh.x_title = "f_{a3}^{ZH}";
  f_VVVh.y_min = 0;
  f_VVVh.y_max = 70;
  f_VVVh.x_min = 0;
  f_VVVh.x_max = global_x_max;
  
  f_VVVh.graphs = graphs_VVVh;
  f_VVVh.draw("L");
  */


  ////////////////
  // TeV
  ///////////////

  std::vector<graph> graphs_TEV;
  graphs_TEV.push_back(g_Wh_TEV_common_observed);
  graphs_TEV.push_back(g_Wh_TEV_common_expected);
  graphs_TEV.push_back(g_Zh_TEV_common_observed);
  graphs_TEV.push_back(g_Zh_TEV_common_expected);
  graphs_TEV.push_back(g_Vh_TEV_common_observed);
  graphs_TEV.push_back(g_Vh_TEV_common_expected);
  redo_colors(graphs_TEV);

  figure f_TEV;
  f_TEV.figure_name = prepend +"TEV";
  //f_TEV.x_title = "f_{a3}^{ZZ}";
  f_TEV.x_title = "f_{0^{-}}";
  f_TEV.y_min = 0;
  f_TEV.y_max = 20;
  f_TEV.x_min = 0;
  /*
  f_TEV.leg_y_min = 0.65;
  f_TEV.leg_y_max = 0.87;
  f_TEV.leg_x_min = 0.2;
  f_TEV.leg_x_max = 0.65;
  */
  f_TEV.x_max = global_x_max;
  
  f_TEV.graphs = graphs_TEV;
  //f_TEV.draw("L");


  ////////////////
  // VH
  ///////////////

  std::vector<graph> graphs_VH;
  graphs_VH.push_back(g_Vh_CMS_common_observed);
  graphs_VH.push_back(g_Vh_CMS_common_expected);
  graphs_VH.push_back(g_Zh_CMS_common_observed);
  graphs_VH.push_back(g_Zh_CMS_common_expected);
  graphs_VH.push_back(g_Wh_CMS_common_observed);
  graphs_VH.push_back(g_Wh_CMS_common_expected);
  redo_colors(graphs_VH);

  figure f_VH;
  f_VH.figure_name = prepend +"VH";
  f_VH.x_title = "f_{a_{#scale[1.3]{3}}}^{ZH}";
  f_VH.y_min = 0;
  f_VH.y_max = 2;
  f_VH.x_min = 0;
  /*
  f_VH.leg_y_min = 0.65;
  f_VH.leg_y_max = 0.87;
  f_VH.leg_x_min = 0.2;
  f_VH.leg_x_max = 0.65;
  */
  f_VH.x_max = global_x_max;

  f_VH.labelCL = true;
  f_VH.cl68_x = 0.2987421;
  f_VH.cl68_y = 0.526971;
  
  f_VH.graphs = graphs_VH;
  //f_VH.draw("L");


  ////////////////
  // Z
  ///////////////

  std::vector<graph> graphs_Z;
  //graphs_Z.push_back(g_ZZZh_CMS_common_observed_noScale);
  //graphs_Z.push_back(g_ZZZh_CMS_common_expected_noScale);
  graphs_Z.push_back(g_ZZZh_CMS_float_observed);
  graphs_Z.push_back(g_ZZZh_CMS_float_expected);
  graphs_Z.push_back(g_ZZ_CMS_observed);
  graphs_Z.push_back(g_ZZ_CMS_expected);
  graphs_Z.push_back(g_Zh_CMS_common_observed_ZZ);  //actually zh
  graphs_Z.push_back(g_Zh_CMS_common_expected_ZZ);
  redo_colors(graphs_Z);

  figure f_Z;
  f_Z.figure_name = prepend +"Z_fa3vh";
  f_Z.x_title = "f_{a_{#scale[1.3]{3}}}^{ZH}";
  f_Z.y_min = 0;
  f_Z.y_max = 15;
  f_Z.x_min = 0;
  /*
  f_Z.leg_y_min = 0.6;
  f_Z.leg_y_max = 0.87;
  f_Z.leg_x_min = 0.26;
  f_Z.leg_x_max = 0.65;
  */
  f_Z.x_max = global_x_max;

  f_Z.doInset = false;
  f_Z.inset_x_min = 0;
  f_Z.inset_x_max = 1;
  f_Z.inset_y_min = 0;
  f_Z.inset_y_max = 1;

  f_Z.labelCL = true;
  f_Z.cl68_x = 0.2672956;
  f_Z.cl95_x = 0.2672956;
  f_Z.cl99_x = 0.2672956;

  f_Z.cl68_y = 0.1964039;
  f_Z.cl95_y = 0.3388658;
  f_Z.cl99_y = 0.4813278;

  f_Z.graphs = graphs_Z;
  f_Z.draw("L");


  ////////////////
  // Z ZOOM
  ///////////////

  std::vector<graph> graphs_zoom_Z;
  //graphs_zoom_Z.push_back(g_ZZZh_CMS_common_observed_noScale);
  //graphs_zoom_Z.push_back(g_ZZZh_CMS_common_expected_noScale);
  graphs_zoom_Z.push_back(g_ZZZh_CMS_float_observed);
  graphs_zoom_Z.push_back(g_ZZZh_CMS_float_expected);
  graphs_zoom_Z.push_back(g_ZZ_CMS_observed);
  graphs_zoom_Z.push_back(g_ZZ_CMS_expected);
  graphs_zoom_Z.push_back(g_Zh_CMS_common_observed_ZZ);  
  graphs_zoom_Z.push_back(g_Zh_CMS_common_expected_ZZ);
  redo_colors(graphs_zoom_Z);

  figure f_zoom_Z;
  f_zoom_Z.figure_name = prepend +"Z_fa3vh_zoom";
  f_zoom_Z.x_title = "f_{a_{#scale[1.3]{3}}}^{ZH}";
  f_zoom_Z.y_min = 0;
  f_zoom_Z.x_min = 0;
  f_zoom_Z.x_max = 1;
  f_zoom_Z.y_max = 1.2;

  f_zoom_Z.leg_x_min = 0.28;
  f_zoom_Z.leg_x_max = 0.78;
  f_zoom_Z.leg_y_min = 0.47;
  f_zoom_Z.leg_y_max = 0.75;
  
  f_zoom_Z.rightMargin = 0.1;

  f_zoom_Z.doInset = false;

  f_zoom_Z.draw_lines = true;

  f_zoom_Z.labelCL = true;
  f_zoom_Z.cl68_x = 0.8647799;
  f_zoom_Z.cl68_y = 0.7786999;

  f_zoom_Z.graphs = graphs_zoom_Z;
  //f_zoom_Z.draw("L");


  ////////////////
  // W
  ///////////////

  std::vector<graph> graphs_W;
  //graphs_W.push_back(g_WWWh_CMS_common_observed_WW_noScale);
  //graphs_W.push_back(g_WWWh_CMS_common_expected_WW_noScale);
  graphs_W.push_back(g_WWWh_CMS_float_observed_WW);
  graphs_W.push_back(g_WWWh_CMS_float_expected_WW);
  graphs_W.push_back(g_WW_CMS_observed_WW);
  graphs_W.push_back(g_WW_CMS_expected_WW);
  graphs_W.push_back(g_Wh_CMS_common_observed_WW);  
  graphs_W.push_back(g_Wh_CMS_common_expected_WW);
  redo_colors(graphs_W);

  figure f_W;
  f_W.figure_name = prepend +"W";
  f_W.x_title = "f_{a_{#scale[1.3]{3}}}^{WW}";
  f_W.y_min = 0;
  f_W.y_max = 3;
  f_W.x_min = 0;
  /*
  f_W.leg_y_min = 0.6;
  f_W.leg_y_max = 0.87;
  f_W.leg_x_min = 0.2;
  f_W.leg_x_max = 0.7;
  */
  f_W.x_max = global_x_max;

  f_W.doInset = true;
  f_W.inset_y_max = .65;
  f_W.inset_x_max = .025;

  f_W.labelCL = true;
  f_W.cl68_x = 0.9371069;
  f_W.cl68_y = 0.4024896;


  f_W.graphs = graphs_W;
  //f_W.draw("L");


  ////////////////
  // W ZOOM
  ///////////////

  std::vector<graph> graphs_zoom_W;
  //graphs_zoom_W.push_back(g_WWWh_CMS_common_observed_WW_noScale);
  //graphs_zoom_W.push_back(g_WWWh_CMS_common_expected_WW_noScale);
  graphs_zoom_W.push_back(g_WWWh_CMS_float_observed_WW);
  graphs_zoom_W.push_back(g_WWWh_CMS_float_expected_WW);
  graphs_zoom_W.push_back(g_WW_CMS_observed_WW);
  graphs_zoom_W.push_back(g_WW_CMS_expected_WW);
  graphs_zoom_W.push_back(g_Wh_CMS_common_observed_WW);  
  graphs_zoom_W.push_back(g_Wh_CMS_common_expected_WW);
  redo_colors(graphs_zoom_W);

  figure f_zoom_W;
  f_zoom_W.figure_name = prepend +"W_zoom";
  f_zoom_W.x_title = "f_{a_{#scale[1.3]{3}}}^{WW}";
  f_zoom_W.y_min = 0;
  f_zoom_W.y_max = 1.2;
  f_zoom_W.x_min = 0;
  f_zoom_W.x_max = 0.025;
  f_zoom_W.rightMargin = 0.1;


  f_zoom_W.doInset = false;
  f_zoom_W.draw_lines = false;
  
  f_zoom_W.graphs = graphs_zoom_W;
  //f_zoom_W.draw("L");


  ////////////////
  // V
  ///////////////

  std::vector<graph> graphs_V;
  //graphs_V.push_back(g_VVVh_CMS_common_observed_noScale);
  //graphs_V.push_back(g_VVVh_CMS_common_expected_noScale);
  graphs_V.push_back(g_VVVh_CMS_float_observed);
  graphs_V.push_back(g_VVVh_CMS_float_expected);
  graphs_V.push_back(g_VV_CMS_observed);
  graphs_V.push_back(g_VV_CMS_expected);
  graphs_V.push_back(g_Vh_CMS_common_observed_ZZ);  
  graphs_V.push_back(g_Vh_CMS_common_expected_ZZ);
  redo_colors(graphs_V);

  figure f_V;
  f_V.figure_name = prepend +"V";
  f_V.x_title = "f_{a_{#scale[1.3]{3}}}^{ZZ}";
  f_V.y_min = 0;
  f_V.y_max = 28;
  f_V.x_min = 0;
  /*
  f_V.leg_y_min = 0.6;
  f_V.leg_y_max = 0.87;
  f_V.leg_x_min = 0.2;
  f_V.leg_x_max = 0.7;
  */
  f_V.x_max = global_x_max;

  f_V.doInset = true;
  //f_V.inset_x_max = .025;

  f_V.labelCL = true;
  f_V.cl68_x = 0.92;
  f_V.cl95_x = 0.92;
  f_V.cl99_x = 0.92;
  f_V.cl68_y = 0.1743;
  f_V.cl95_y = 0.2517;
  f_V.cl99_y = 0.3264;

  f_V.graphs = graphs_V;
  //f_V.draw("L");

  

  ////////////////
  // V ZOOM
  ///////////////

  std::vector<graph> graphs_zoom_V;
  //graphs_zoom_V.push_back(g_VVVh_CMS_common_observed_noScale);
  //graphs_zoom_V.push_back(g_VVVh_CMS_common_expected_noScale);
  graphs_zoom_V.push_back(g_VVVh_CMS_float_observed);
  graphs_zoom_V.push_back(g_VVVh_CMS_float_expected);
  graphs_zoom_V.push_back(g_VV_CMS_observed);
  graphs_zoom_V.push_back(g_VV_CMS_expected);
  graphs_zoom_V.push_back(g_Vh_CMS_common_observed_ZZ);  
  graphs_zoom_V.push_back(g_Vh_CMS_common_expected_ZZ);
  redo_colors(graphs_zoom_V);

  figure f_zoom_V;
  f_zoom_V.figure_name = prepend +"V_zoom";
  f_zoom_V.x_title = "f_{a_{#scale[1.3]{3}}}^{ZZ}";
  f_zoom_V.y_min = 0;
  f_zoom_V.y_max = 2;
  f_zoom_V.x_min = 0;
  /*
  f_zoom_V.leg_y_min = 0.5;
  f_zoom_V.leg_y_max = 0.72;
  f_zoom_V.leg_x_min = 0.43;
  f_zoom_V.leg_x_max = 0.88;
  */
  f_zoom_V.x_max = 0.01;
  f_zoom_V.rightMargin = 0.1;


  f_zoom_V.doInset = false;
  f_zoom_V.labelCL = true;
  f_zoom_V.cl68_x = 0.28;
  f_zoom_V.cl68_y = 0.525;

  
  f_zoom_V.graphs = graphs_zoom_V;
  //f_zoom_V.draw("L");


  ////////////////
  // all common
  ///////////////
  //HACK to remove "correlated mu" from legend
  g_ZZZh_CMS_common_expected_noScale.legend_name.ReplaceAll(" (correlated #mu)","");
  g_ZZZh_CMS_common_observed_noScale.legend_name.ReplaceAll(" (correlated #mu)","");
  g_WWWh_CMS_common_observed_noScale.legend_name.ReplaceAll(" (correlated #mu)","");
  g_WWWh_CMS_common_expected_noScale.legend_name.ReplaceAll(" (correlated #mu)","");
  g_VVVh_CMS_common_observed_noScale.legend_name.ReplaceAll(" (correlated #mu)","");
  g_VVVh_CMS_common_expected_noScale.legend_name.ReplaceAll(" (correlated #mu)","");

  std::vector<graph> graphs_all_common;
  graphs_all_common.push_back(g_VVVh_CMS_common_observed_noScale);
  graphs_all_common.push_back(g_VVVh_CMS_common_expected_noScale);
  graphs_all_common.push_back(g_ZZZh_CMS_common_observed_noScale);
  graphs_all_common.push_back(g_ZZZh_CMS_common_expected_noScale);
  graphs_all_common.push_back(g_WWWh_CMS_common_observed_noScale);
  graphs_all_common.push_back(g_WWWh_CMS_common_expected_noScale);
  redo_colors(graphs_all_common);

  figure f_all_common;
  f_all_common.figure_name = prepend +"all_common";
  f_all_common.x_title = "f_{a_{#scale[1.3]{3}}}^{ZZ}";
  f_all_common.y_min = 0;
  f_all_common.y_max = 120;
  f_all_common.x_min = 0;

  f_all_common.leg_y_min = 0.54;
  f_all_common.leg_y_max = 0.79;
  /*
  f_all_common.leg_x_min = 0.2;
  f_all_common.leg_x_max = 0.53;
  */
  f_all_common.x_max = 1;
  f_all_common.ndiv = 505;

  f_all_common.extraTextHack = true;

  f_all_common.draw_lines = false;
  f_all_common.draw_lines_99_only = true;
  f_all_common.labelCL = true;
  f_all_common.cl99_x = .92;
  f_all_common.cl99_y = 0.1881051;

  f_all_common.more_y_offset = 0.15;

  f_all_common.doInset = true;

  f_all_common.inset_y_min = 0;
  f_all_common.inset_y_max = 4.3;
  f_all_common.inset_x_min = 0;
  f_all_common.inset_x_max = .01;

  f_all_common.inset_pos_x_min = 0.51;
  /*
  f_all_common.inset_pos_y_min = 0.53;
  f_all_common.inset_pos_y_max = 0.88;
  f_all_common.inset_pos_x_min = 0.54;
  f_all_common.inset_pos_x_max = 0.89;
  */

  f_all_common.labelCL_inset = true;
  f_all_common.cl68_x_inset = 0.89;
  f_all_common.cl95_x_inset = 0.89;
  f_all_common.cl68_y_inset = 0.315;
  f_all_common.cl95_y_inset = 0.8815;

  f_all_common.graphs = graphs_all_common;
  //f_all_common.draw("L");

  ////////////////
  // all common zoom
  ///////////////
  
  std::vector<graph> graphs_zoom_all_common;
  graphs_zoom_all_common.push_back(g_VVVh_CMS_common_observed_noScale);
  graphs_zoom_all_common.push_back(g_VVVh_CMS_common_expected_noScale);
  graphs_zoom_all_common.push_back(g_ZZZh_CMS_common_observed_noScale);
  graphs_zoom_all_common.push_back(g_ZZZh_CMS_common_expected_noScale);
  graphs_zoom_all_common.push_back(g_WWWh_CMS_common_observed_noScale);
  graphs_zoom_all_common.push_back(g_WWWh_CMS_common_expected_noScale);
  redo_colors(graphs_zoom_all_common);

  figure f_zoom_all_common;
  f_zoom_all_common.figure_name = prepend +"all_common_zoom";
  f_zoom_all_common.x_title = "f_{a_{#scale[1.3]{3}}}^{ZZ}";
  f_zoom_all_common.y_min = 0;
  f_zoom_all_common.y_max = 48;
  f_zoom_all_common.x_min = 0;

  f_zoom_all_common.leg_y_min = 0.5421853;
  f_zoom_all_common.leg_y_max = 0.791148;
  f_zoom_all_common.leg_x_min = 0.1823899;
  f_zoom_all_common.leg_x_max = 0.5125786;
  
  f_zoom_all_common.x_max = 0.0115;
  f_zoom_all_common.ndiv = 505;
  f_zoom_all_common.rightMargin = 0.1;

  f_zoom_all_common.extraTextHack = true;

  f_zoom_all_common.draw_lines = true;
  f_zoom_all_common.more_y_offset = 0.15;

  f_zoom_all_common.labelCL = true;
  //f_zoom_all_common.cl_text_size = 0.025;
  f_zoom_all_common.cl68_x = 0.7562893;
  f_zoom_all_common.cl95_x = 0.8254717;
  f_zoom_all_common.cl99_x = 0.8977;
  f_zoom_all_common.cl68_y = 0.1590595;
  f_zoom_all_common.cl95_y = 0.2047026;
  f_zoom_all_common.cl99_y = 0.2489627;

  f_zoom_all_common.graphs = graphs_zoom_all_common;
  //f_zoom_all_common.draw("L");

  
  

  return;
}

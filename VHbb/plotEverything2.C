#include "plotEverything2.h"

void plotEverything2(){
  cout << "Plot everything 2" << endl;

  /////////////////////////////
  // Create graphs
  /////////////////////////////

  //Wh
  graph g_Wh_CMS_common_expected;
  g_Wh_CMS_common_expected.file_name = "/uscms_data/d2/kreis/Hbb/fa3/CMSSW_6_1_1/src/20150505_defaultMinuit/Wh_CMS_common_expected/higgsCombine1D_exp.MultiDimFit.mH125.6.root";
  g_Wh_CMS_common_expected.legend_name = "WH expected";
  g_Wh_CMS_common_expected.color = kBlack; 
  g_Wh_CMS_common_expected.linestyle = 2; 
  g_Wh_CMS_common_expected.do_all_prep();

  graph g_Wh_CMS_common_observed;
  g_Wh_CMS_common_observed.file_name = "/uscms_data/d2/kreis/Hbb/fa3/CMSSW_6_1_1/src/20150505_defaultMinuit/Wh_CMS_common_observed/higgsCombine1D_obs.MultiDimFit.mH125.6.root";
  g_Wh_CMS_common_observed.legend_name = "WH observed";
  g_Wh_CMS_common_observed.color = kBlack; 
  g_Wh_CMS_common_observed.linestyle = 1; 
  g_Wh_CMS_common_observed.do_all_prep();

  graph g_Wh_CMS_common_expected_fa3WW;
  g_Wh_CMS_common_expected_fa3WW.file_name = "/uscms_data/d2/kreis/Hbb/fa3/CMSSW_6_1_1/src/20150505_defaultMinuit/Wh_CMS_common_expected/higgsCombine1D_exp.MultiDimFit.mH125.6.root";
  g_Wh_CMS_common_expected_fa3WW.legend_name = "WH expected";
  g_Wh_CMS_common_expected_fa3WW.x_variable = fa3zzToww;
  g_Wh_CMS_common_expected_fa3WW.color = kBlack; 
  g_Wh_CMS_common_expected_fa3WW.linestyle = 2; 
  g_Wh_CMS_common_expected_fa3WW.do_all_prep();

  graph g_Wh_CMS_common_observed_fa3WW;
  g_Wh_CMS_common_observed_fa3WW.file_name = "/uscms_data/d2/kreis/Hbb/fa3/CMSSW_6_1_1/src/20150505_defaultMinuit/Wh_CMS_common_observed/higgsCombine1D_obs.MultiDimFit.mH125.6.root";
  g_Wh_CMS_common_observed_fa3WW.legend_name = "WH observed";
  g_Wh_CMS_common_observed_fa3WW.x_variable = fa3zzToww;
  g_Wh_CMS_common_observed_fa3WW.color = kBlack; 
  g_Wh_CMS_common_observed_fa3WW.linestyle = 1; 
  g_Wh_CMS_common_observed_fa3WW.do_all_prep();

  graph g_Wh_CMS_common_expected_fa3ZH;
  g_Wh_CMS_common_expected_fa3ZH.file_name = "/uscms_data/d2/kreis/Hbb/fa3/CMSSW_6_1_1/src/20150505_defaultMinuit/Wh_CMS_common_expected/higgsCombine1D_exp.MultiDimFit.mH125.6.root";
  g_Wh_CMS_common_expected_fa3ZH.legend_name = "WH expected";
  g_Wh_CMS_common_expected_fa3ZH.x_variable = fa3zzTozh;
  g_Wh_CMS_common_expected_fa3ZH.color = kBlack; 
  g_Wh_CMS_common_expected_fa3ZH.linestyle = 2; 
  g_Wh_CMS_common_expected_fa3ZH.do_all_prep();

  graph g_Wh_CMS_common_observed_fa3ZH;
  g_Wh_CMS_common_observed_fa3ZH.file_name = "/uscms_data/d2/kreis/Hbb/fa3/CMSSW_6_1_1/src/20150505_defaultMinuit/Wh_CMS_common_observed/higgsCombine1D_obs.MultiDimFit.mH125.6.root";
  g_Wh_CMS_common_observed_fa3ZH.legend_name = "WH observed";
  g_Wh_CMS_common_observed_fa3ZH.x_variable = fa3zzTozh;
  g_Wh_CMS_common_observed_fa3ZH.color = kBlack; 
  g_Wh_CMS_common_observed_fa3ZH.linestyle = 1; 
  g_Wh_CMS_common_observed_fa3ZH.do_all_prep();

  graph g_Wh_CMS_common_expected_fa3WH;
  g_Wh_CMS_common_expected_fa3WH.file_name = "/uscms_data/d2/kreis/Hbb/fa3/CMSSW_6_1_1/src/20150505_defaultMinuit/Wh_CMS_common_expected/higgsCombine1D_exp.MultiDimFit.mH125.6.root";
  g_Wh_CMS_common_expected_fa3WH.legend_name = "WH expected";
  g_Wh_CMS_common_expected_fa3WH.x_variable = fa3zzTowh;
  g_Wh_CMS_common_expected_fa3WH.color = kBlack; 
  g_Wh_CMS_common_expected_fa3WH.linestyle = 2; 
  g_Wh_CMS_common_expected_fa3WH.do_all_prep();
  
  graph g_Wh_CMS_common_observed_fa3WH;
  g_Wh_CMS_common_observed_fa3WH.file_name = "/uscms_data/d2/kreis/Hbb/fa3/CMSSW_6_1_1/src/20150505_defaultMinuit/Wh_CMS_common_observed/higgsCombine1D_obs.MultiDimFit.mH125.6.root";
  g_Wh_CMS_common_observed_fa3WH.legend_name = "WH observed";
  g_Wh_CMS_common_observed_fa3WH.x_variable = fa3zzTowh;
  g_Wh_CMS_common_observed_fa3WH.color = kBlack; 
  g_Wh_CMS_common_observed_fa3WH.linestyle = 1; 
  g_Wh_CMS_common_observed_fa3WH.do_all_prep();



  //Zh
  graph g_Zh_CMS_common_expected;
  g_Zh_CMS_common_expected.file_name = "/uscms_data/d2/kreis/Hbb/fa3/CMSSW_6_1_1/src/20150505_defaultMinuit/Zh_CMS_common_expected/higgsCombine1D_exp.MultiDimFit.mH125.6.root";
  g_Zh_CMS_common_expected.legend_name = "ZH expected";
  g_Zh_CMS_common_expected.color = kBlue; 
  g_Zh_CMS_common_expected.linestyle = 2; 
  g_Zh_CMS_common_expected.do_all_prep();

  graph g_Zh_CMS_common_observed;
  g_Zh_CMS_common_observed.file_name = "/uscms_data/d2/kreis/Hbb/fa3/CMSSW_6_1_1/src/20150505_defaultMinuit/Zh_CMS_common_observed/higgsCombine1D_obs.MultiDimFit.mH125.6.root";
  g_Zh_CMS_common_observed.legend_name = "ZH observed";
  g_Zh_CMS_common_observed.color = kBlue; 
  g_Zh_CMS_common_observed.linestyle = 1; 
  g_Zh_CMS_common_observed.do_all_prep();

  graph g_Zh_CMS_common_expected_fa3ZH;
  g_Zh_CMS_common_expected_fa3ZH.file_name = "/uscms_data/d2/kreis/Hbb/fa3/CMSSW_6_1_1/src/20150505_defaultMinuit/Zh_CMS_common_expected/higgsCombine1D_exp.MultiDimFit.mH125.6.root";
  g_Zh_CMS_common_expected_fa3ZH.legend_name = "ZH expected";
  g_Zh_CMS_common_expected_fa3ZH.x_variable = fa3zzTozh;
  g_Zh_CMS_common_expected_fa3ZH.color = kBlue; 
  g_Zh_CMS_common_expected_fa3ZH.linestyle = 2; 
  g_Zh_CMS_common_expected_fa3ZH.do_all_prep();

  graph g_Zh_CMS_common_observed_fa3ZH;
  g_Zh_CMS_common_observed_fa3ZH.file_name = "/uscms_data/d2/kreis/Hbb/fa3/CMSSW_6_1_1/src/20150505_defaultMinuit/Zh_CMS_common_observed/higgsCombine1D_obs.MultiDimFit.mH125.6.root";
  g_Zh_CMS_common_observed_fa3ZH.legend_name = "ZH observed";
  g_Zh_CMS_common_observed_fa3ZH.x_variable = fa3zzTozh;
  g_Zh_CMS_common_observed_fa3ZH.color = kBlue; 
  g_Zh_CMS_common_observed_fa3ZH.linestyle = 1; 
  g_Zh_CMS_common_observed_fa3ZH.do_all_prep();

  //Vh
  graph g_Vh_CMS_common_expected;
  g_Vh_CMS_common_expected.file_name = "/uscms_data/d2/kreis/Hbb/fa3/CMSSW_6_1_1/src/20150505_defaultMinuit/Vh_CMS_common_expected/higgsCombine1D_exp.MultiDimFit.mH125.6.root";
  g_Vh_CMS_common_expected.legend_name = "VH expected";
  g_Vh_CMS_common_expected.color = kRed; 
  g_Vh_CMS_common_expected.linestyle = 2; 
  g_Vh_CMS_common_expected.do_all_prep();

  graph g_Vh_CMS_common_observed;
  g_Vh_CMS_common_observed.file_name = "/uscms_data/d2/kreis/Hbb/fa3/CMSSW_6_1_1/src/20150505_defaultMinuit/Vh_CMS_common_observed/higgsCombine1D_obs.MultiDimFit.mH125.6.root";
  g_Vh_CMS_common_observed.legend_name = "VH observed";
  g_Vh_CMS_common_observed.color = kRed; 
  g_Vh_CMS_common_observed.linestyle = 1; 
  g_Vh_CMS_common_observed.do_all_prep();

  graph g_Vh_CMS_common_expected_fa3ZH;
  g_Vh_CMS_common_expected_fa3ZH.file_name = "/uscms_data/d2/kreis/Hbb/fa3/CMSSW_6_1_1/src/20150505_defaultMinuit/Vh_CMS_common_expected/higgsCombine1D_exp.MultiDimFit.mH125.6.root";
  g_Vh_CMS_common_expected_fa3ZH.legend_name = "VH expected";
  g_Vh_CMS_common_expected_fa3ZH.x_variable = fa3zzTozh;
  g_Vh_CMS_common_expected_fa3ZH.color = kRed; 
  g_Vh_CMS_common_expected_fa3ZH.linestyle = 2; 
  g_Vh_CMS_common_expected_fa3ZH.do_all_prep();

  graph g_Vh_CMS_common_observed_fa3ZH;
  g_Vh_CMS_common_observed_fa3ZH.file_name = "/uscms_data/d2/kreis/Hbb/fa3/CMSSW_6_1_1/src/20150505_defaultMinuit/Vh_CMS_common_observed/higgsCombine1D_obs.MultiDimFit.mH125.6.root";
  g_Vh_CMS_common_observed_fa3ZH.legend_name = "VH observed";
  g_Vh_CMS_common_observed_fa3ZH.x_variable = fa3zzTozh; 
  g_Vh_CMS_common_observed_fa3ZH.color = kRed; 
  g_Vh_CMS_common_observed_fa3ZH.linestyle = 1; 
  g_Vh_CMS_common_observed_fa3ZH.do_all_prep();

  //WW
  graph g_WW_CMS_common_expected_fa3WW;
  g_WW_CMS_common_expected_fa3WW.file_name = "/uscms_data/d1/jstupak/fa3Combo/CMSSW_6_1_1/src/vhvv_combination/hVVCards/WW_CMS_common_expected/higgsCombine1D_exp.MultiDimFit.mH125.6.root";
  g_WW_CMS_common_expected_fa3WW.legend_name = "WW expected";
  g_WW_CMS_common_expected_fa3WW.x_variable = fa3zzToww;
  g_WW_CMS_common_expected_fa3WW.color = kViolet; 
  g_WW_CMS_common_expected_fa3WW.linestyle = 2; 
  g_WW_CMS_common_expected_fa3WW.do_all_prep();

  graph g_WW_CMS_common_observed_fa3WW;
  g_WW_CMS_common_observed_fa3WW.file_name = "/uscms_data/d1/jstupak/fa3Combo/CMSSW_6_1_1/src/vhvv_combination/hVVCards/WW_CMS_common_observed/higgsCombine1D_obs.MultiDimFit.mH125.6.root";
  g_WW_CMS_common_observed_fa3WW.legend_name = "WW observed";
  g_WW_CMS_common_observed_fa3WW.x_variable = fa3zzToww;
  g_WW_CMS_common_observed_fa3WW.color = kViolet; 
  g_WW_CMS_common_observed_fa3WW.linestyle = 1; 
  g_WW_CMS_common_observed_fa3WW.do_all_prep();

  graph g_WW_CMS_common_expected_fa3WH;
  g_WW_CMS_common_expected_fa3WH.file_name = "/uscms_data/d1/jstupak/fa3Combo/CMSSW_6_1_1/src/vhvv_combination/hVVCards/WW_CMS_common_expected/higgsCombine1D_exp.MultiDimFit.mH125.6.root";
  g_WW_CMS_common_expected_fa3WH.legend_name = "WW expected";
  g_WW_CMS_common_expected_fa3WH.x_variable = fa3zzTowh;
  g_WW_CMS_common_expected_fa3WH.color = kViolet; 
  g_WW_CMS_common_expected_fa3WH.linestyle = 2; 
  g_WW_CMS_common_expected_fa3WH.do_all_prep();

  graph g_WW_CMS_common_observed_fa3WH;
  g_WW_CMS_common_observed_fa3WH.file_name = "/uscms_data/d1/jstupak/fa3Combo/CMSSW_6_1_1/src/vhvv_combination/hVVCards/WW_CMS_common_observed/higgsCombine1D_obs.MultiDimFit.mH125.6.root";
  g_WW_CMS_common_observed_fa3WH.legend_name = "WW observed";
  g_WW_CMS_common_observed_fa3WH.x_variable = fa3zzTowh;
  g_WW_CMS_common_observed_fa3WH.color = kViolet; 
  g_WW_CMS_common_observed_fa3WH.linestyle = 1; 
  g_WW_CMS_common_observed_fa3WH.do_all_prep();

  //ZZ
  graph g_ZZ_CMS_common_expected;
  g_ZZ_CMS_common_expected.file_name = "/uscms_data/d1/jstupak/fa3Combo/CMSSW_6_1_1/src/vhvv_combination/hVVCards/ZZ_CMS_common_expected/higgsCombine1D_exp.MultiDimFit.mH125.6.root";
  g_ZZ_CMS_common_expected.legend_name = "ZZ expected";
  g_ZZ_CMS_common_expected.color = kGreen+2; 
  g_ZZ_CMS_common_expected.linestyle = 2; 
  g_ZZ_CMS_common_expected.do_all_prep();

  graph g_ZZ_CMS_common_observed;
  g_ZZ_CMS_common_observed.file_name = "/uscms_data/d1/jstupak/fa3Combo/CMSSW_6_1_1/src/vhvv_combination/hVVCards/ZZ_CMS_common_observed/higgsCombine1D_obs.MultiDimFit.mH125.6.root";
  g_ZZ_CMS_common_observed.legend_name = "ZZ observed";
  g_ZZ_CMS_common_observed.color = kGreen+2; 
  g_ZZ_CMS_common_observed.linestyle = 1; 
  g_ZZ_CMS_common_observed.do_all_prep();

  graph g_ZZ_CMS_common_expected_fa3ZH;
  g_ZZ_CMS_common_expected_fa3ZH.file_name = "/uscms_data/d1/jstupak/fa3Combo/CMSSW_6_1_1/src/vhvv_combination/hVVCards/ZZ_CMS_common_expected/higgsCombine1D_exp.MultiDimFit.mH125.6.root";
  g_ZZ_CMS_common_expected_fa3ZH.legend_name = "ZZ expected";
  g_ZZ_CMS_common_expected_fa3ZH.color = kGreen+2; 
  g_ZZ_CMS_common_expected_fa3ZH.x_variable = fa3zzTozh;
  g_ZZ_CMS_common_expected_fa3ZH.linestyle = 2; 
  g_ZZ_CMS_common_expected_fa3ZH.do_all_prep();

  graph g_ZZ_CMS_common_observed_fa3ZH;
  g_ZZ_CMS_common_observed_fa3ZH.file_name = "/uscms_data/d1/jstupak/fa3Combo/CMSSW_6_1_1/src/vhvv_combination/hVVCards/ZZ_CMS_common_observed/higgsCombine1D_obs.MultiDimFit.mH125.6.root";
  g_ZZ_CMS_common_observed_fa3ZH.legend_name = "ZZ observed";
  g_ZZ_CMS_common_observed_fa3ZH.color = kGreen+2; 
  g_ZZ_CMS_common_observed_fa3ZH.x_variable = fa3zzTozh;
  g_ZZ_CMS_common_observed_fa3ZH.linestyle = 1; 
  g_ZZ_CMS_common_observed_fa3ZH.do_all_prep();

  //VV
  graph g_VV_CMS_common_expected;
  g_VV_CMS_common_expected.file_name = "/uscms_data/d1/jstupak/fa3Combo/CMSSW_6_1_1/src/vhvv_combination/hVVCards/VV_CMS_common_expected/higgsCombine1D_exp.MultiDimFit.mH125.6.root";
  g_VV_CMS_common_expected.legend_name = "VV expected";
  g_VV_CMS_common_expected.color = kMagenta; 
  g_VV_CMS_common_expected.linestyle = 2; 
  g_VV_CMS_common_expected.do_all_prep();

  graph g_VV_CMS_common_observed;
  g_VV_CMS_common_observed.file_name = "/uscms_data/d1/jstupak/fa3Combo/CMSSW_6_1_1/src/vhvv_combination/hVVCards/VV_CMS_common_observed/higgsCombine1D_obs.MultiDimFit.mH125.6.root";
  g_VV_CMS_common_observed.legend_name = "VV observed";
  g_VV_CMS_common_observed.color = kMagenta; 
  g_VV_CMS_common_observed.linestyle = 1; 
  g_VV_CMS_common_observed.do_all_prep();

  graph g_VV_CMS_common_expected_fa3ZH;
  g_VV_CMS_common_expected_fa3ZH.file_name = "/uscms_data/d1/jstupak/fa3Combo/CMSSW_6_1_1/src/vhvv_combination/hVVCards/VV_CMS_common_expected/higgsCombine1D_exp.MultiDimFit.mH125.6.root";
  g_VV_CMS_common_expected_fa3ZH.legend_name = "VV expected";
  g_VV_CMS_common_expected_fa3ZH.x_variable = fa3zzTozh;
  g_VV_CMS_common_expected_fa3ZH.color = kMagenta; 
  g_VV_CMS_common_expected_fa3ZH.linestyle = 2; 
  g_VV_CMS_common_expected_fa3ZH.do_all_prep();

  graph g_VV_CMS_common_observed_fa3ZH;
  g_VV_CMS_common_observed_fa3ZH.file_name = "/uscms_data/d1/jstupak/fa3Combo/CMSSW_6_1_1/src/vhvv_combination/hVVCards/VV_CMS_common_observed/higgsCombine1D_obs.MultiDimFit.mH125.6.root";
  g_VV_CMS_common_observed_fa3ZH.legend_name = "VV observed";
  g_VV_CMS_common_observed_fa3ZH.x_variable = fa3zzTozh;
  g_VV_CMS_common_observed_fa3ZH.color = kMagenta; 
  g_VV_CMS_common_observed_fa3ZH.linestyle = 1; 
  g_VV_CMS_common_observed_fa3ZH.do_all_prep();

  //WWW
  graph g_WWWh_CMS_common_expected_fa3WW;
  g_WWWh_CMS_common_expected_fa3WW.file_name = "/uscms_data/d2/kreis/Hbb/fa3/CMSSW_6_1_1/src/20150515_fa3_tol0p03Minuit/WWWh_CMS_common_expected/higgsCombine1D_exp.MultiDimFit.mH125.6.root";
  g_WWWh_CMS_common_expected_fa3WW.legend_name = "WH+WW expected, #mu^{WW}=#mu^{WH}";
  g_WWWh_CMS_common_expected_fa3WW.x_variable = fa3zzToww;
  g_WWWh_CMS_common_expected_fa3WW.scale = "0.2"; 
  g_WWWh_CMS_common_expected_fa3WW.color = kCyan+1; 
  g_WWWh_CMS_common_expected_fa3WW.linestyle = 2; 
  g_WWWh_CMS_common_expected_fa3WW.do_all_prep();

  graph g_WWWh_CMS_common_observed_fa3WW;
  g_WWWh_CMS_common_observed_fa3WW.file_name = "/uscms_data/d2/kreis/Hbb/fa3/CMSSW_6_1_1/src/20150515_fa3_tol0p03Minuit/WWWh_CMS_common_observed/higgsCombine1D_obs.MultiDimFit.mH125.6.root";
  g_WWWh_CMS_common_observed_fa3WW.legend_name = "WH+WW observed, #mu^{WW}=#mu^{WH}";
  g_WWWh_CMS_common_observed_fa3WW.x_variable = fa3zzToww;
  g_WWWh_CMS_common_observed_fa3WW.scale = "0.2"; 
  g_WWWh_CMS_common_observed_fa3WW.color = kCyan+1; 
  g_WWWh_CMS_common_observed_fa3WW.linestyle = 1; 
  g_WWWh_CMS_common_observed_fa3WW.do_all_prep();

  graph g_WWWh_CMS_float_expected_fa3WW;
  g_WWWh_CMS_float_expected_fa3WW.file_name = "/uscms_data/d2/kreis/Hbb/fa3/CMSSW_6_1_1/src/20150515_fa3_tol0p03Minuit/WWWh_CMS_float_expected/higgsCombine1D_exp.MultiDimFit.mH125.6.root";
  g_WWWh_CMS_float_expected_fa3WW.legend_name = "WH+WW expected";
  g_WWWh_CMS_float_expected_fa3WW.x_variable = fa3zzToww;
  g_WWWh_CMS_float_expected_fa3WW.color = kOrange+1; 
  g_WWWh_CMS_float_expected_fa3WW.linestyle = 2; 
  g_WWWh_CMS_float_expected_fa3WW.do_all_prep();

  graph g_WWWh_CMS_float_observed_fa3WW;
  g_WWWh_CMS_float_observed_fa3WW.file_name = "/uscms_data/d2/kreis/Hbb/fa3/CMSSW_6_1_1/src/20150515_fa3_tol0p03Minuit/WWWh_CMS_float_observed/higgsCombine1D_obs.MultiDimFit.mH125.6.root";
  g_WWWh_CMS_float_observed_fa3WW.legend_name = "WH+WW observed";
  g_WWWh_CMS_float_observed_fa3WW.x_variable = fa3zzToww;
  g_WWWh_CMS_float_observed_fa3WW.color = kOrange+1; 
  g_WWWh_CMS_float_observed_fa3WW.linestyle = 1; 
  g_WWWh_CMS_float_observed_fa3WW.do_all_prep();

  graph g_WWWh_CMS_common_expected_fa3WH;
  g_WWWh_CMS_common_expected_fa3WH.file_name = "/uscms_data/d2/kreis/Hbb/fa3/CMSSW_6_1_1/src/20150515_fa3_tol0p03Minuit/WWWh_CMS_common_expected/higgsCombine1D_exp.MultiDimFit.mH125.6.root";
  g_WWWh_CMS_common_expected_fa3WH.legend_name = "WH+WW expected, #mu^{WW}=#mu^{WH}";
  g_WWWh_CMS_common_expected_fa3WH.x_variable = fa3zzTowh;
  g_WWWh_CMS_common_expected_fa3WH.scale = "0.2"; 
  g_WWWh_CMS_common_expected_fa3WH.color = kCyan+1; 
  g_WWWh_CMS_common_expected_fa3WH.linestyle = 2; 
  g_WWWh_CMS_common_expected_fa3WH.do_all_prep();

  graph g_WWWh_CMS_common_observed_fa3WH;
  g_WWWh_CMS_common_observed_fa3WH.file_name = "/uscms_data/d2/kreis/Hbb/fa3/CMSSW_6_1_1/src/20150515_fa3_tol0p03Minuit/WWWh_CMS_common_observed/higgsCombine1D_obs.MultiDimFit.mH125.6.root";
  g_WWWh_CMS_common_observed_fa3WH.legend_name = "WH+WW observed, #mu^{WW}=#mu^{WH}";
  g_WWWh_CMS_common_observed_fa3WH.x_variable = fa3zzTowh;
  g_WWWh_CMS_common_observed_fa3WH.scale = "0.2"; 
  g_WWWh_CMS_common_observed_fa3WH.color = kCyan+1; 
  g_WWWh_CMS_common_observed_fa3WH.linestyle = 1; 
  g_WWWh_CMS_common_observed_fa3WH.do_all_prep();

  graph g_WWWh_CMS_float_expected_fa3WH;
  g_WWWh_CMS_float_expected_fa3WH.file_name = "/uscms_data/d2/kreis/Hbb/fa3/CMSSW_6_1_1/src/20150515_fa3_tol0p03Minuit/WWWh_CMS_float_expected/higgsCombine1D_exp.MultiDimFit.mH125.6.root";
  g_WWWh_CMS_float_expected_fa3WH.legend_name = "WH+WW expected";
  g_WWWh_CMS_float_expected_fa3WH.x_variable = fa3zzTowh;
  g_WWWh_CMS_float_expected_fa3WH.color = kOrange+1; 
  g_WWWh_CMS_float_expected_fa3WH.linestyle = 2; 
  g_WWWh_CMS_float_expected_fa3WH.do_all_prep();

  graph g_WWWh_CMS_float_observed_fa3WH;
  g_WWWh_CMS_float_observed_fa3WH.file_name = "/uscms_data/d2/kreis/Hbb/fa3/CMSSW_6_1_1/src/20150515_fa3_tol0p03Minuit/WWWh_CMS_float_observed/higgsCombine1D_obs.MultiDimFit.mH125.6.root";
  g_WWWh_CMS_float_observed_fa3WH.legend_name = "WH+WW observed";
  g_WWWh_CMS_float_observed_fa3WH.x_variable = fa3zzTowh;
  g_WWWh_CMS_float_observed_fa3WH.color = kOrange+1; 
  g_WWWh_CMS_float_observed_fa3WH.linestyle = 1; 
  g_WWWh_CMS_float_observed_fa3WH.do_all_prep();

  
  //ZZZ
  graph g_ZZZh_CMS_common_expected;
  g_ZZZh_CMS_common_expected.file_name = "/uscms_data/d2/kreis/Hbb/fa3/CMSSW_6_1_1/src/20150505_defaultMinuit/ZZZh_CMS_common_expected/higgsCombine1D_exp.MultiDimFit.mH125.6.root";
  g_ZZZh_CMS_common_expected.legend_name = "ZH+ZZ expected, #mu^{ZZ}=#mu^{ZH}";
  g_ZZZh_CMS_common_expected.scale = "0.3"; 
  g_ZZZh_CMS_common_expected.color = kCyan+1; 
  g_ZZZh_CMS_common_expected.linestyle = 2; 
  g_ZZZh_CMS_common_expected.do_all_prep();

  graph g_ZZZh_CMS_common_observed;
  g_ZZZh_CMS_common_observed.file_name = "/uscms_data/d2/kreis/Hbb/fa3/CMSSW_6_1_1/src/20150505_defaultMinuit/ZZZh_CMS_common_observed/higgsCombine1D_obs.MultiDimFit.mH125.6.root";
  g_ZZZh_CMS_common_observed.legend_name = "ZH+ZZ observed, #mu^{ZZ}=#mu^{ZH}";
  g_ZZZh_CMS_common_observed.scale = "0.3"; 
  g_ZZZh_CMS_common_observed.color = kCyan+1; 
  g_ZZZh_CMS_common_observed.linestyle = 1; 
  g_ZZZh_CMS_common_observed.do_all_prep();

  graph g_ZZZh_CMS_float_expected;
  g_ZZZh_CMS_float_expected.file_name = "/uscms_data/d2/kreis/Hbb/fa3/CMSSW_6_1_1/src/20150505_defaultMinuit/ZZZh_CMS_float_expected/higgsCombine1D_exp.MultiDimFit.mH125.6.root";
  g_ZZZh_CMS_float_expected.legend_name = "ZH+ZZ expected";
  g_ZZZh_CMS_float_expected.color = kOrange+1; 
  g_ZZZh_CMS_float_expected.linestyle = 2; 
  g_ZZZh_CMS_float_expected.do_all_prep();

  graph g_ZZZh_CMS_float_observed;
  g_ZZZh_CMS_float_observed.file_name = "/uscms_data/d2/kreis/Hbb/fa3/CMSSW_6_1_1/src/20150505_defaultMinuit/ZZZh_CMS_float_observed/higgsCombine1D_obs.MultiDimFit.mH125.6.root";
  g_ZZZh_CMS_float_observed.legend_name = "ZH+ZZ observed";
  g_ZZZh_CMS_float_observed.color = kOrange+1; 
  g_ZZZh_CMS_float_observed.linestyle = 1; 
  g_ZZZh_CMS_float_observed.do_all_prep();

  graph g_ZZZh_CMS_common_expected_fa3ZH;
  g_ZZZh_CMS_common_expected_fa3ZH.file_name = "/uscms_data/d2/kreis/Hbb/fa3/CMSSW_6_1_1/src/20150505_defaultMinuit/ZZZh_CMS_common_expected/higgsCombine1D_exp.MultiDimFit.mH125.6.root";
  g_ZZZh_CMS_common_expected_fa3ZH.legend_name = "ZH+ZZ expected, #mu^{ZZ}=#mu^{ZH}";
  g_ZZZh_CMS_common_expected_fa3ZH.scale = "0.3"; 
  g_ZZZh_CMS_common_expected_fa3ZH.x_variable = fa3zzTozh; 
  g_ZZZh_CMS_common_expected_fa3ZH.color = kCyan+1; 
  g_ZZZh_CMS_common_expected_fa3ZH.linestyle = 2; 
  g_ZZZh_CMS_common_expected_fa3ZH.do_all_prep();

  graph g_ZZZh_CMS_common_observed_fa3ZH;
  g_ZZZh_CMS_common_observed_fa3ZH.file_name = "/uscms_data/d2/kreis/Hbb/fa3/CMSSW_6_1_1/src/20150505_defaultMinuit/ZZZh_CMS_common_observed/higgsCombine1D_obs.MultiDimFit.mH125.6.root";
  g_ZZZh_CMS_common_observed_fa3ZH.legend_name = "ZH+ZZ observed, #mu^{ZZ}=#mu^{ZH}";
  g_ZZZh_CMS_common_observed_fa3ZH.scale = "0.3"; 
  g_ZZZh_CMS_common_observed_fa3ZH.x_variable = fa3zzTozh; 
  g_ZZZh_CMS_common_observed_fa3ZH.color = kCyan+1; 
  g_ZZZh_CMS_common_observed_fa3ZH.linestyle = 1; 
  g_ZZZh_CMS_common_observed_fa3ZH.do_all_prep();

  graph g_ZZZh_CMS_float_expected_fa3ZH;
  g_ZZZh_CMS_float_expected_fa3ZH.file_name = "/uscms_data/d2/kreis/Hbb/fa3/CMSSW_6_1_1/src/20150505_defaultMinuit/ZZZh_CMS_float_expected/higgsCombine1D_exp.MultiDimFit.mH125.6.root";
  g_ZZZh_CMS_float_expected_fa3ZH.legend_name = "ZH+ZZ expected";
  g_ZZZh_CMS_float_expected_fa3ZH.x_variable = fa3zzTozh; 
  g_ZZZh_CMS_float_expected_fa3ZH.color = kOrange+1; 
  g_ZZZh_CMS_float_expected_fa3ZH.linestyle = 2; 
  g_ZZZh_CMS_float_expected_fa3ZH.do_all_prep();

  graph g_ZZZh_CMS_float_observed_fa3ZH;
  g_ZZZh_CMS_float_observed_fa3ZH.file_name = "/uscms_data/d2/kreis/Hbb/fa3/CMSSW_6_1_1/src/20150505_defaultMinuit/ZZZh_CMS_float_observed/higgsCombine1D_obs.MultiDimFit.mH125.6.root";
  g_ZZZh_CMS_float_observed_fa3ZH.legend_name = "ZH+ZZ observed";
  g_ZZZh_CMS_float_observed_fa3ZH.x_variable = fa3zzTozh; 
  g_ZZZh_CMS_float_observed_fa3ZH.color = kOrange+1; 
  g_ZZZh_CMS_float_observed_fa3ZH.linestyle = 1; 
  g_ZZZh_CMS_float_observed_fa3ZH.do_all_prep();

  //VVV
  graph g_VVVh_CMS_common_expected;
  g_VVVh_CMS_common_expected.file_name = "/uscms_data/d2/kreis/Hbb/fa3/CMSSW_6_1_1/src/20150505_defaultMinuit/VVVh_CMS_common_expected/higgsCombine1D_exp.MultiDimFit.mH125.6.root";
  g_VVVh_CMS_common_expected.legend_name = "VH+VV expected, #mu^{VV}=#mu^{VH}";
  g_VVVh_CMS_common_expected.scale = "0.2";
  g_VVVh_CMS_common_expected.color = kCyan+1; 
  g_VVVh_CMS_common_expected.linestyle = 2; 
  g_VVVh_CMS_common_expected.do_all_prep();

  graph g_VVVh_CMS_common_observed;
  g_VVVh_CMS_common_observed.file_name = "/uscms_data/d2/kreis/Hbb/fa3/CMSSW_6_1_1/src/20150505_manual/VVVh_CMS_common_observed/higgsCombine1D_obs.MultiDimFit.mH125.6.root";
  g_VVVh_CMS_common_observed.legend_name = "VH+VV observed, #mu^{VV}=#mu^{VH}";
  g_VVVh_CMS_common_observed.scale = "0.2"; 
  g_VVVh_CMS_common_observed.color = kCyan+1; 
  g_VVVh_CMS_common_observed.linestyle = 1; 
  g_VVVh_CMS_common_observed.do_all_prep();

  graph g_VVVh_CMS_float_expected;
  g_VVVh_CMS_float_expected.file_name = "/uscms_data/d2/kreis/Hbb/fa3/CMSSW_6_1_1/src/20150505_defaultMinuit/VVVh_CMS_float_expected/higgsCombine1D_exp.MultiDimFit.mH125.6.root";
  g_VVVh_CMS_float_expected.legend_name = "VH+VV expected";
  g_VVVh_CMS_float_expected.color = kOrange+1; 
  g_VVVh_CMS_float_expected.linestyle = 2; 
  g_VVVh_CMS_float_expected.do_all_prep();

  graph g_VVVh_CMS_float_observed;
  g_VVVh_CMS_float_observed.file_name = "/uscms_data/d2/kreis/Hbb/fa3/CMSSW_6_1_1/src/20150505_manual/VVVh_CMS_float_observed/higgsCombine1D_obs.MultiDimFit.mH125.6.root";
  g_VVVh_CMS_float_observed.legend_name = "VH+VV observed";
  g_VVVh_CMS_float_observed.color = kOrange+1; 
  g_VVVh_CMS_float_observed.linestyle = 1; 
  g_VVVh_CMS_float_observed.do_all_prep();

  graph g_VVVh_CMS_common_expected_fa3ZH;
  g_VVVh_CMS_common_expected_fa3ZH.file_name = "/uscms_data/d2/kreis/Hbb/fa3/CMSSW_6_1_1/src/20150505_defaultMinuit/VVVh_CMS_common_expected/higgsCombine1D_exp.MultiDimFit.mH125.6.root";
  g_VVVh_CMS_common_expected_fa3ZH.legend_name = "VH+VV expected, #mu^{VV}=#mu^{VH}";
  g_VVVh_CMS_common_expected_fa3ZH.scale = "0.2";
  g_VVVh_CMS_common_expected_fa3ZH.x_variable = fa3zzTozh;
  g_VVVh_CMS_common_expected_fa3ZH.color = kCyan+1; 
  g_VVVh_CMS_common_expected_fa3ZH.linestyle = 2; 
  g_VVVh_CMS_common_expected_fa3ZH.do_all_prep();

  graph g_VVVh_CMS_common_observed_fa3ZH;
  g_VVVh_CMS_common_observed_fa3ZH.file_name = "/uscms_data/d2/kreis/Hbb/fa3/CMSSW_6_1_1/src/20150505_manual/VVVh_CMS_common_observed/higgsCombine1D_obs.MultiDimFit.mH125.6.root";
  g_VVVh_CMS_common_observed_fa3ZH.legend_name = "VH+VV observed, #mu^{VV}=#mu^{VH}";
  g_VVVh_CMS_common_observed_fa3ZH.scale = "0.2"; 
  g_VVVh_CMS_common_observed_fa3ZH.x_variable = fa3zzTozh;
  g_VVVh_CMS_common_observed_fa3ZH.color = kCyan+1; 
  g_VVVh_CMS_common_observed_fa3ZH.linestyle = 1; 
  g_VVVh_CMS_common_observed_fa3ZH.do_all_prep();

  graph g_VVVh_CMS_float_expected_fa3ZH;
  g_VVVh_CMS_float_expected_fa3ZH.file_name = "/uscms_data/d2/kreis/Hbb/fa3/CMSSW_6_1_1/src/20150505_defaultMinuit/VVVh_CMS_float_expected/higgsCombine1D_exp.MultiDimFit.mH125.6.root";
  g_VVVh_CMS_float_expected_fa3ZH.legend_name = "VH+VV expected";
  g_VVVh_CMS_float_expected_fa3ZH.x_variable = fa3zzTozh;
  g_VVVh_CMS_float_expected_fa3ZH.color = kOrange+1; 
  g_VVVh_CMS_float_expected_fa3ZH.linestyle = 2; 
  g_VVVh_CMS_float_expected_fa3ZH.do_all_prep();

  graph g_VVVh_CMS_float_observed_fa3ZH;
  g_VVVh_CMS_float_observed_fa3ZH.file_name = "/uscms_data/d2/kreis/Hbb/fa3/CMSSW_6_1_1/src/20150505_manual/VVVh_CMS_float_observed/higgsCombine1D_obs.MultiDimFit.mH125.6.root";
  g_VVVh_CMS_float_observed_fa3ZH.legend_name = "VH+VV observed";
  g_VVVh_CMS_float_observed_fa3ZH.x_variable = fa3zzTozh;
  g_VVVh_CMS_float_observed_fa3ZH.color = kOrange+1; 
  g_VVVh_CMS_float_observed_fa3ZH.linestyle = 1; 
  g_VVVh_CMS_float_observed_fa3ZH.do_all_prep();
  
  

  /////////////////////////////
  // Create figures
  /////////////////////////////


 
  std::vector<graph> graphs_Vh;
  graphs_Vh.push_back(g_Wh_CMS_common_expected);
  graphs_Vh.push_back(g_Wh_CMS_common_observed);
  graphs_Vh.push_back(g_Zh_CMS_common_expected);
  graphs_Vh.push_back(g_Zh_CMS_common_observed);
  graphs_Vh.push_back(g_Vh_CMS_common_expected);
  graphs_Vh.push_back(g_Vh_CMS_common_observed);
  
  figure f_Vh;
  f_Vh.figure_name = prepend + "Vh";
  f_Vh.x_title = "f_{a3}^{ZZ}";
  f_Vh.y_min = 0;
  f_Vh.y_max = 6;
  f_Vh.x_min = 0;
  f_Vh.x_max = global_x_max;
  
  f_Vh.graphs = graphs_Vh;
  f_Vh.draw();
 

  std::vector<graph> graphs_Vh_fa3ZH;
  graphs_Vh_fa3ZH.push_back(g_Wh_CMS_common_expected_fa3ZH);
  graphs_Vh_fa3ZH.push_back(g_Wh_CMS_common_observed_fa3ZH);
  graphs_Vh_fa3ZH.push_back(g_Zh_CMS_common_expected_fa3ZH);
  graphs_Vh_fa3ZH.push_back(g_Zh_CMS_common_observed_fa3ZH);
  graphs_Vh_fa3ZH.push_back(g_Vh_CMS_common_expected_fa3ZH);
  graphs_Vh_fa3ZH.push_back(g_Vh_CMS_common_observed_fa3ZH);
  
  figure f_Vh_fa3ZH;
  f_Vh_fa3ZH.figure_name = prepend +"Vh_fa3ZH";
  f_Vh_fa3ZH.x_title = "f_{a3}^{ZH}";
  f_Vh_fa3ZH.y_min = 0;
  f_Vh_fa3ZH.y_max = 6;
  f_Vh_fa3ZH.x_min = 0;
  f_Vh_fa3ZH.x_max = global_x_max;
  
  f_Vh_fa3ZH.graphs = graphs_Vh_fa3ZH;
  f_Vh_fa3ZH.draw();
 


  std::vector<graph> graphs_VVVh;
  graphs_VVVh.push_back(g_Vh_CMS_common_expected);
  graphs_VVVh.push_back(g_Vh_CMS_common_observed);
  graphs_VVVh.push_back(g_VV_CMS_common_expected);
  graphs_VVVh.push_back(g_VV_CMS_common_observed);
  graphs_VVVh.push_back(g_VVVh_CMS_float_expected);
  graphs_VVVh.push_back(g_VVVh_CMS_float_observed);
  graphs_VVVh.push_back(g_VVVh_CMS_common_expected);
  graphs_VVVh.push_back(g_VVVh_CMS_common_observed);
  
  figure f_VVVh;
  f_VVVh.figure_name = prepend +"VVVh";
  f_VVVh.x_title = "f_{a3}^{ZZ}";
  f_VVVh.y_min = 0;
  f_VVVh.y_max = 18;
  f_VVVh.x_min = 0;
  f_VVVh.x_max = global_x_max;

  f_VVVh.graphs = graphs_VVVh;
  f_VVVh.draw();



  std::vector<graph> graphs_VVVh_fa3ZH;
  graphs_VVVh_fa3ZH.push_back(g_Vh_CMS_common_expected_fa3ZH);
  graphs_VVVh_fa3ZH.push_back(g_Vh_CMS_common_observed_fa3ZH);
  graphs_VVVh_fa3ZH.push_back(g_VV_CMS_common_expected_fa3ZH);
  graphs_VVVh_fa3ZH.push_back(g_VV_CMS_common_observed_fa3ZH);
  graphs_VVVh_fa3ZH.push_back(g_VVVh_CMS_float_expected_fa3ZH);
  graphs_VVVh_fa3ZH.push_back(g_VVVh_CMS_float_observed_fa3ZH);
  graphs_VVVh_fa3ZH.push_back(g_VVVh_CMS_common_expected_fa3ZH);
  graphs_VVVh_fa3ZH.push_back(g_VVVh_CMS_common_observed_fa3ZH);
  
  figure f_VVVh_fa3ZH;
  f_VVVh_fa3ZH.figure_name = prepend +"VVVh_fa3ZH";
  f_VVVh_fa3ZH.x_title = "f_{a3}^{ZH}";
  f_VVVh_fa3ZH.y_min = 0;
  f_VVVh_fa3ZH.y_max = 18;
  f_VVVh_fa3ZH.x_min = 0;
  f_VVVh_fa3ZH.x_max = global_x_max;

  f_VVVh_fa3ZH.graphs = graphs_VVVh_fa3ZH;
  f_VVVh_fa3ZH.draw();



  std::vector<graph> graphs_ZZZh;
  graphs_ZZZh.push_back(g_Zh_CMS_common_expected);
  graphs_ZZZh.push_back(g_Zh_CMS_common_observed);
  graphs_ZZZh.push_back(g_ZZ_CMS_common_expected);
  graphs_ZZZh.push_back(g_ZZ_CMS_common_observed);
  graphs_ZZZh.push_back(g_ZZZh_CMS_float_expected);
  graphs_ZZZh.push_back(g_ZZZh_CMS_float_observed);
  graphs_ZZZh.push_back(g_ZZZh_CMS_common_expected);
  graphs_ZZZh.push_back(g_ZZZh_CMS_common_observed);
  
  figure f_ZZZh;
  f_ZZZh.figure_name = prepend +"ZZZh";
  f_ZZZh.x_title = "f_{a3}^{ZZ}";
  f_ZZZh.y_min = 0;
  f_ZZZh.y_max = 15;
  f_ZZZh.x_min = 0;
  f_ZZZh.x_max = global_x_max;

  f_ZZZh.graphs = graphs_ZZZh;
  f_ZZZh.draw();



  std::vector<graph> graphs_ZZZh_fa3ZH;
  graphs_ZZZh_fa3ZH.push_back(g_Zh_CMS_common_expected_fa3ZH);
  graphs_ZZZh_fa3ZH.push_back(g_Zh_CMS_common_observed_fa3ZH);
  graphs_ZZZh_fa3ZH.push_back(g_ZZ_CMS_common_expected_fa3ZH);
  graphs_ZZZh_fa3ZH.push_back(g_ZZ_CMS_common_observed_fa3ZH);
  graphs_ZZZh_fa3ZH.push_back(g_ZZZh_CMS_float_expected_fa3ZH);
  graphs_ZZZh_fa3ZH.push_back(g_ZZZh_CMS_float_observed_fa3ZH);
  graphs_ZZZh_fa3ZH.push_back(g_ZZZh_CMS_common_expected_fa3ZH);
  graphs_ZZZh_fa3ZH.push_back(g_ZZZh_CMS_common_observed_fa3ZH);
  
  figure f_ZZZh_fa3ZH;
  f_ZZZh_fa3ZH.figure_name = prepend +"ZZZh_fa3ZH";
  f_ZZZh_fa3ZH.x_title = "f_{a3}^{ZH}";
  f_ZZZh_fa3ZH.y_min = 0;
  f_ZZZh_fa3ZH.y_max = 15;
  f_ZZZh_fa3ZH.x_min = 0;
  f_ZZZh_fa3ZH.x_max = global_x_max;

  f_ZZZh_fa3ZH.graphs = graphs_ZZZh_fa3ZH;
  f_ZZZh_fa3ZH.draw();



  std::vector<graph> graphs_WWWh;
  graphs_WWWh.push_back(g_Wh_CMS_common_expected_fa3WW);
  graphs_WWWh.push_back(g_Wh_CMS_common_observed_fa3WW);
  graphs_WWWh.push_back(g_WW_CMS_common_expected_fa3WW);
  graphs_WWWh.push_back(g_WW_CMS_common_observed_fa3WW);
  graphs_WWWh.push_back(g_WWWh_CMS_float_expected_fa3WW);
  graphs_WWWh.push_back(g_WWWh_CMS_float_observed_fa3WW);
  graphs_WWWh.push_back(g_WWWh_CMS_common_expected_fa3WW);
  graphs_WWWh.push_back(g_WWWh_CMS_common_observed_fa3WW);
  
  figure f_WWWh;
  f_WWWh.figure_name = prepend +"WWWh";
  f_WWWh.x_title = "f_{a3}^{WW}";
  f_WWWh.y_min = 0;
  f_WWWh.y_max = 8;
  f_WWWh.x_min = 0;
  f_WWWh.x_max = global_x_max;

  f_WWWh.graphs = graphs_WWWh;
  f_WWWh.draw();


  std::vector<graph> graphs_WWWh_fa3WH;
  graphs_WWWh_fa3WH.push_back(g_Wh_CMS_common_expected_fa3WH);
  graphs_WWWh_fa3WH.push_back(g_Wh_CMS_common_observed_fa3WH);
  graphs_WWWh_fa3WH.push_back(g_WW_CMS_common_expected_fa3WH);
  graphs_WWWh_fa3WH.push_back(g_WW_CMS_common_observed_fa3WH);
  graphs_WWWh_fa3WH.push_back(g_WWWh_CMS_float_expected_fa3WH);
  graphs_WWWh_fa3WH.push_back(g_WWWh_CMS_float_observed_fa3WH);
  graphs_WWWh_fa3WH.push_back(g_WWWh_CMS_common_expected_fa3WH);
  graphs_WWWh_fa3WH.push_back(g_WWWh_CMS_common_observed_fa3WH);
  
  figure f_WWWh_fa3WH;
  f_WWWh_fa3WH.figure_name = prepend +"WWWh_fa3WH";
  f_WWWh_fa3WH.x_title = "f_{a3}^{WH}";
  f_WWWh_fa3WH.y_min = 0;
  f_WWWh_fa3WH.y_max = 8;
  f_WWWh_fa3WH.x_min = 0;
  f_WWWh_fa3WH.x_max = global_x_max;

  f_WWWh_fa3WH.graphs = graphs_WWWh_fa3WH;
  f_WWWh_fa3WH.draw();

  

  return;
}

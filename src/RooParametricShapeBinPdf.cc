//---------------------------------------------------------------------------
#include "RooFit.h"

#include "Riostream.h"
#include <TMath.h>
#include <cassert>
#include <cmath>
#include <math.h>

#include "HiggsAnalysis/CombinedLimit/interface/RooParametricShapeBinPdf.h"
#include "RooRealVar.h"
#include "RooArgList.h"
#include "RooRealProxy.h"
#include "RooListProxy.h"

using namespace std;
using namespace RooFit;

ClassImp(RooParametricShapeBinPdf)
//---------------------------------------------------------------------------

RooParametricShapeBinPdf::RooParametricShapeBinPdf(const char *name, const char *title, RooAbsReal& _pdf, 
			       RooAbsReal& _x, RooArgList& _pars, const TH1 &_shape ) : RooAbsPdf(name, title), 
  x("x", "x Observable", this, _x),
  pars("pars","pars",this),
  mypdf("mypdf","mypdf", this, _pdf),
  xBins(0),
  xMax(0),
  xMin(0)
{
  memset(&xArray, 0, sizeof(xArray));
  TIterator *varIter=_pars.createIterator(); 
  RooAbsReal *fVar;
  while ( (fVar = (RooAbsReal*)varIter->Next()) ){
    pars.add(*fVar);
  }
  setTH1Binning(_shape);
}
//---------------------------------------------------------------------------
RooParametricShapeBinPdf::RooParametricShapeBinPdf(const RooParametricShapeBinPdf& other, const char* name) : RooAbsPdf(other, name), 
   x("x", this, other.x),
   pars("pars",this,RooListProxy()),
   mypdf("mypdf",this,other.mypdf),
   xBins(other.xBins),
   xMax(other.xMax),
   xMin(other.xMin)
{
  //memset(&xArray, 0, sizeof(xArray));
  for (Int_t i=0; i<xBins+1; i++){
    xArray[i] = other.xArray[i];
  }
  
  TIterator *varIter=other.pars.createIterator(); 
  RooAbsReal *fVar;
  while ( (fVar = (RooAbsReal*) varIter->Next()) ){
    pars.add(*fVar);
  }
  
}
//---------------------------------------------------------------------------
void RooParametricShapeBinPdf::setTH1Binning(const TH1 &_Hnominal){
  xBins = _Hnominal.GetXaxis()->GetNbins();
  xMin = _Hnominal.GetXaxis()->GetBinLowEdge(1);
  xMax = _Hnominal.GetXaxis()->GetBinUpEdge(xBins);
  memset(&xArray, 0, sizeof(xArray));
  for (Int_t i=0; i<xBins+1; i++){
    xArray[i] =  _Hnominal.GetXaxis()->GetBinLowEdge(i+1);
  }
}
//---------------------------------------------------------------------------
/// Return the parameteric p.d.f
RooAbsPdf* RooParametricShapeBinPdf::getPdf() const {
  return mypdf ? ((RooAbsPdf*)mypdf.absArg()) : 0 ;
}
//---------------------------------------------------------------------------
Double_t RooParametricShapeBinPdf::evaluate() const
{
  Double_t integral = 0.0;
  Int_t iBin;
  for(iBin=0; iBin<xBins; iBin++) {  
    if (x>=xArray[iBin] && x < xArray[iBin+1] ) break;
  }
  
  if(iBin < 0 || iBin >= xBins) {
    //cout << "in bin " << iBin << " which is outside of range" << endl;
    return 0.0;
  }

  Double_t xLow = xArray[iBin];
  Double_t xHigh = xArray[iBin+1];

  std::string rangeName  = Form("%s_%s_range_bin%d", GetName(), x.GetName(), iBin);
  if (!x.arg().hasRange(rangeName.c_str())) {
    RooRealVar x_rrv = dynamic_cast<const RooRealVar &>(x.arg());
    x_rrv.setRange(rangeName.c_str(),xLow,xHigh);
  }
  
  RooListProxy obs;
  obs.add(x.arg());
  RooAbsReal* myintegral = getPdf()->createIntegral(obs,Range(rangeName.c_str()));
    
  integral = myintegral->getVal() / (xHigh-xLow);
  
  if (integral>0.0) {
    return integral;
  } else return 0;

}

// //---------------------------------------------------------------------------
Int_t RooParametricShapeBinPdf::getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* rangeName) const{
  if (matchArgs(allVars, analVars, x)) return 1;
  return 0;
}

// //---------------------------------------------------------------------------
Double_t RooParametricShapeBinPdf::analyticalIntegral(Int_t code, const char* rangeName) const{

  Double_t xRangeMin = x.min(rangeName); Double_t xRangeMax = x.max(rangeName);
  
  Double_t integral = 0.0;
  
  RooListProxy obs;
  obs.add(x.arg());
  
  if (code==1 && xRangeMin<=xMin && xRangeMax>=xMax){
    RooAbsReal* myintegral = getPdf()->createIntegral(obs);
    integral = myintegral->getVal();
    return integral;
  }
  else if(code==1) {     
    RooAbsReal* myintegral = getPdf()->createIntegral(obs,Range(rangeName));
    integral = myintegral->getVal();
    return integral;
   } else {
    cout << "WARNING IN RooParametricShapeBinPdf: integration code is not correct" << endl;
    cout << "                           what are you integrating on?" << endl;
    return 1.0;
  }
}
// //---------------------------------------------------------------------------


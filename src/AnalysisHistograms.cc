//
// Original Author:  Artur Kalinowski
//         Created:  Tue Oct 24 15:08:51 CEST 2006
// $Id: AnalysisHistograms.cc,v 1.8 2010/09/14 11:37:23 cbern Exp $
//
//
// system include files
#include <memory>
#include <bitset>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <vector>

#include "AnalysisHistograms.h"

//
// constructors and destructor
//
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
AnalysisHistograms::~AnalysisHistograms(){
 
  using namespace std;

  finalizeHistograms();

}
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
void AnalysisHistograms::addProfile(const std::string& name, 
				    const std::string& title, 
				    int nBinsX, float xlow, float xhigh, 
				    const TFileDirectory* myDir) {
  
  using namespace std;
  
  TProfile *hTmp = myDir->make<TProfile>(name.c_str(),title.c_str(),
					 nBinsX,xlow,xhigh);  
  if(myProfiles_.find(name)==myProfiles_.end()) myProfiles_[name] = hTmp;
  else cout<<"ERROR Substituting existing profile!"<<endl;
  
  
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void  AnalysisHistograms::add1DHistogram(const std::string& name, const std::string& title,
			                             int nBinsX, float xlow, float xhigh,
					                     const TFileDirectory* myDir){

  using namespace std;

  TH1F *hTmp = myDir->make<TH1F>(name.c_str(),title.c_str(),nBinsX,xlow,xhigh);
  hTmp->Sumw2();

  if(my1Dhistograms_.find(name)==my1Dhistograms_.end()) my1Dhistograms_[name] = hTmp;
  else cout<<"ERROR Substituting existing histogram!"<<endl;

}
//////////////////////////////////////////////////////////////////////////////
void  AnalysisHistograms::add1DHistogram(const std::string& name, const std::string& title, int nBinsX, float* bins,
					 const TFileDirectory* myDir){

  using namespace std;
  
  TH1F *hTmp = myDir->make<TH1F>(name.c_str(),title.c_str(),nBinsX,bins);
  hTmp->Sumw2();

  if(my1Dhistograms_.find(name)==my1Dhistograms_.end()) my1Dhistograms_[name] = hTmp;
  else cout<<"ERROR Substituting existing histogram!"<<endl;
}
//////////////////////////////////////////////////////////////////////////////
void  AnalysisHistograms::add2DHistogram(const std::string& name, const std::string& title,
					int nBinsX, float xlow, float xhigh,
					 int nBinsY, float ylow, float yhigh,
					 const TFileDirectory* myDir){

  using namespace std;

  TH2F *hTmp =  myDir->make<TH2F>(name.c_str(),title.c_str(),nBinsX,xlow,xhigh, nBinsY, ylow,yhigh);  
  hTmp->Sumw2();

  if(my2Dhistograms_.find(name)==my2Dhistograms_.end()) my2Dhistograms_[name] = hTmp;
  else cout<<"ERROR Substituting existing histogram!"<<endl;

}
//////////////////////////////////////////////////////////////////////////////
void  AnalysisHistograms::add2DHistogram(const std::string& name, const std::string& title,
					 int nBinsX, float* binsX,
					 int nBinsY, float* binsY, 					 
					 const TFileDirectory* myDir){

  using namespace std;
  
  TH2F *hTmp =  myDir->make<TH2F>(name.c_str(),title.c_str(),nBinsX,binsX,nBinsY,binsY);
  hTmp->Sumw2();

  if(my2Dhistograms_.find(name)==my2Dhistograms_.end()) my2Dhistograms_[name] = hTmp;
  else cout<<"ERROR Substituting existing histogram!"<<endl;
}
//////////////////////////////////////////////////////////////////////////////
void  AnalysisHistograms::add2DHistogram(const std::string& name, const std::string& title,
					 int nBinsX, float xlow, float xhigh,
					 int nBinsY, double* binsY, 					 
					 const TFileDirectory* myDir){

  using namespace std;
  
  TH2F *hTmp =  myDir->make<TH2F>(name.c_str(),title.c_str(),nBinsX,xlow,xhigh,nBinsY,binsY);
  hTmp->Sumw2();

  if(my2Dhistograms_.find(name)==my2Dhistograms_.end()) my2Dhistograms_[name] = hTmp;
  else cout<<"ERROR Substituting existing histogram!"<<endl;
}
//////////////////////////////////////////////////////////////////////////////
void  AnalysisHistograms::add3DHistogram(const std::string& name, const std::string& title,
					 int nBinsX, float xlow, float xhigh,
					 int nBinsY, float ylow, float yhigh,
					 int nBinsZ, float zlow, float zhigh,
					 const TFileDirectory* myDir){
  using namespace std;
  
  TH3F *hTmp =  myDir->make<TH3F>(name.c_str(),title.c_str(),nBinsX,xlow,xhigh,
				  nBinsY,ylow,yhigh, nBinsZ,zlow,zhigh);
  hTmp->Sumw2();

  if(my3Dhistograms_.find(name)==my3Dhistograms_.end()) my3Dhistograms_[name] = hTmp;
  else cout<<"ERROR Substituting existing histogram!"<<endl;
}
//////////////////////////////////////////////////////////////////////////////
void  AnalysisHistograms::add3DHistogram(const std::string& name, const std::string& title,
					 int nBinsX, double* binsX,
					 int nBinsY, double* binsY,
					 int nBinsZ, double* binsZ,
					 const TFileDirectory* myDir){

  using namespace std;
  
  TH3F *hTmp = myDir->make<TH3F>(name.c_str(),title.c_str(),nBinsX,binsX,nBinsY,binsY,
			nBinsZ,binsZ);
  hTmp->Sumw2();

  if(my3Dhistograms_.find(name)==my3Dhistograms_.end()) my3Dhistograms_[name] = hTmp;
  else cout<<"ERROR Substituting existing histogram!"<<endl;
}
//////////////////////////////////////////////////////////////////////////////
void AnalysisHistograms::fillProfile(const std::string& name, float x, float val, float weight) {
  using namespace std;

  if(myProfiles_.find(name)!=myProfiles_.end()) 
    myProfiles_[name]->Fill(x, val,weight);
  else cout<<"ERROR: profile : "<<name<<" not found!"<<endl;

}
//////////////////////////////////////////////////////////////////////////////
bool  AnalysisHistograms::fill1DHistogram(const std::string& name, float val, float weight){

 using namespace std;

  if(my1Dhistograms_.find(name)!=my1Dhistograms_.end()) my1Dhistograms_[name]->Fill(val,weight);
  else{
    //cout<<"ERROR: Histogram: "<<name<<" not found!"<<endl;
	  return false;
  }
  return true;
}
//////////////////////////////////////////////////////////////////////////////
bool AnalysisHistograms::fill2DHistogram(const std::string& name, float val1, float val2, float weight){

 using namespace std;

  if(my2Dhistograms_.find(name)!=my2Dhistograms_.end()) my2Dhistograms_[name]->Fill(val1,val2,weight);
  else{
    //cout<<"ERROR: Histogram: "<<name<<" not found!"<<endl;
	  return false;
  }
  return true;
}
//////////////////////////////////////////////////////////////////////////////
bool  AnalysisHistograms::fill3DHistogram(const std::string& name, float val1, float val2, float val3,
					  float weight){

 using namespace std;

 if(my3Dhistograms_.find(name)!=my3Dhistograms_.end()) my3Dhistograms_[name]->Fill(val1,val2,val3,weight);
  else{
    //cout<<"ERROR: Histogram: "<<name<<" not found!"<<endl;
	  return false;
  }
 return true;
}
//////////////////////////////////////////////////////////////////////////////
TProfile* AnalysisHistograms::getProfile(const std::string& name, bool noClone){

 using namespace std;

 if(noClone && myProfiles_.find(name)!=myProfiles_.end()) return myProfiles_[name];
 else if(myProfiles_.find(name)!=myProfiles_.end()){
   TProfile *aClone = (TProfile*)(myProfiles_[name]->Clone());
   aClone->SetDirectory(0);///the cloned object will not be saved to ROOT file.
   return aClone;
 }
 else cout<<"ERROR: Profile : "<<name<<" not found!"<<endl;
 return 0;

}
//////////////////////////////////////////////////////////////////////////////
TH1F* AnalysisHistograms::get1DHistogram(const std::string& name, bool noClone){

 using namespace std;

 std::unordered_map<std::string,TH1F*>::const_iterator it = my1Dhistograms_.find(name);

 if(noClone && it!=my1Dhistograms_.end()) return it->second;
 else if(it!=my1Dhistograms_.end()){
   TH1F *aClone = (TH1F*)(it->second->Clone());
   aClone->SetDirectory(0);///the cloned object will not be saved to ROOT file.
   return aClone;
 }
 else cout<<"ERROR: Histogram: "<<name<<" not found!"<<endl;
 return 0;

}
//////////////////////////////////////////////////////////////////////////////
TH2F* AnalysisHistograms::get2DHistogram(const std::string& name, bool noClone){

 using namespace std;

 std::unordered_map<std::string,TH2F*>::const_iterator it = my2Dhistograms_.find(name);

 if(noClone && it!=my2Dhistograms_.end()) return it->second;
 else if(it!=my2Dhistograms_.end()){
   TH2F *aClone = (TH2F*)(it->second->Clone());
   aClone->SetDirectory(0);///the cloned object will not be saved to ROOT file.
   return aClone;
 }
 else cout<<"ERROR: Histogram: "<<name<<" not found!"<<endl;
 return 0;

}
//////////////////////////////////////////////////////////////////////////////
TH3F* AnalysisHistograms::get3DHistogram(const std::string& name, bool noClone){

 using namespace std;

 std::unordered_map<std::string,TH3F*>::const_iterator it = my3Dhistograms_.find(name);

 if(noClone && it!=my3Dhistograms_.end()) return it->second;
 else if(it!=my3Dhistograms_.end()){
   TH3F *aClone = (TH3F*)(it->second->Clone());
   aClone->SetDirectory(0);///the cloned object will not be saved to ROOT file.
   return aClone;
 }
 else cout<<"ERROR: Histogram: "<<name<<" not found!"<<endl;
 return 0;

}
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void AnalysisHistograms::resetHistos(std::pair<const std::string, TH1*> aPair){
  aPair.second->Reset();
}
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void AnalysisHistograms::init(TFileDirectory *myDir,
			      const std::string & name){ 

  name_ = name;

  if(!histosInitialized_){
    if(name_.size()){
      mySecondaryDirs_.push_back(myDir->mkdir(name_));
      file_ = &mySecondaryDirs_[mySecondaryDirs_.size()-1];
    }
    else file_ = myDir;
    defineHistograms();
  }
}
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void AnalysisHistograms::finalizeHistograms(){ }
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void AnalysisHistograms::clear(){

  for_each(myProfiles_.begin(), myProfiles_.end(), &AnalysisHistograms::resetHistos);
  for_each(my1Dhistograms_.begin(), my1Dhistograms_.end(), &AnalysisHistograms::resetHistos);
  for_each(my2Dhistograms_.begin(), my2Dhistograms_.end(), &AnalysisHistograms::resetHistos);
  for_each(my3Dhistograms_.begin(), my3Dhistograms_.end(), &AnalysisHistograms::resetHistos);

}
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void AnalysisHistograms::write(){

  finalizeHistograms();

}
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
double* AnalysisHistograms::equalRanges(int nSteps, double min, double max, double *ranges){

  for(int i=0;i<=nSteps;++i){
    double val = min + i*(max-min)/nSteps;
    ranges[i] = val;
  }

  return ranges;
}
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

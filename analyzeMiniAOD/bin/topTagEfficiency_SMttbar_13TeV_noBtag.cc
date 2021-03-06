#if !defined(__CINT__) && !defined(__MAKECINT__)
#include<TROOT.h>
#include<TFile.h>
#include<vector>
#include<TChain.h>
#include<TCanvas.h>
#include<TH1.h>
#include<TF1.h>
#include<TH2.h>
#include<TProfile.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<iostream>
#include<fstream>
#include<TLegend.h>
#include<TMath.h>
#include<TStyle.h>
#include<TSystem.h>
#include<TApplication.h>
//#include "boost/shared_ptr.hpp"
#include "/uscms_data/d3/camclean/CSA14/topTaggingEfficiency/CMSSW_7_0_6_patch1/src/Analysis/FWCore/FWLite/interface/AutoLibraryLoader.h"
#include "/uscms_data/d3/camclean/CSA14/topTaggingEfficiency/CMSSW_7_0_6_patch1/src/Analysis/DataFormats/FWLite/interface/Handle.h"
#include "/uscms_data/d3/camclean/CSA14/topTaggingEfficiency/CMSSW_7_0_6_patch1/src/Analysis/DataFormats/FWLite/interface/ChainEvent.h"
#include "/uscms_data/d3/camclean/CSA14/topTaggingEfficiency/CMSSW_7_0_6_patch1/src/Analysis/FWCore/ParameterSet/interface/ParameterSet.h"
#include "/uscms_data/d3/camclean/CSA14/topTaggingEfficiency/CMSSW_7_0_6_patch1/src/Analysis/DataFormats/PatCandidates/interface/Jet.h"
#include "/uscms_data/d3/camclean/CSA14/topTaggingEfficiency/CMSSW_7_0_6_patch1/src/Analysis/DataFormats/PatCandidates/interface/PackedGenParticle.h"
#include "/uscms_data/d3/camclean/CSA14/topTaggingEfficiency/CMSSW_7_0_6_patch1/src/Analysis/DataFormats/Candidate/interface/Candidate.h"
#include "/uscms_data/d3/camclean/CSA14/topTaggingEfficiency/CMSSW_7_0_6_patch1/src/Analysis/DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "/uscms_data/d3/camclean/CSA14/topTaggingEfficiency/CMSSW_7_0_6_patch1/src/Analysis/DataFormats/JetReco/interface/CATopJetTagInfo.h"
#endif

using namespace std;

int main(){
  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(0000000000);
  gStyle->SetTitleBorderSize(0);
  //gStyle->SetTitleAlign(0); 

  gSystem->Load("libFWCoreFWLite.so"); 
  gSystem->Load("libDataFormatsFWLite.so");
  AutoLibraryLoader::enable();
  
  int nbins_pt = 37;
  float bins_pt[38] = {0,20,40,60,80,100,120,140,160,180,200,220,240,260,280,300,320,340,360,380,400,420,440,460,480,500,520,540,560,580,600,700,800,900,1000,1500,2000,2500};                                    
  
  int nbins_npv = 19;                                                                                                                                                                                   
  float bins_npv[20] = {0,10,15,17,19,21,23,25,27,29,31,33,35,37,39,41,43,45,50,60};
 
  /////////////////////////////////                                                                                                                                                         
  //// No Mass Grooming Techniques                                                                                                                                                               
  /////////////////////////////////  

  /////jet mass histogram                                                                                                                                                                                 
  TH1F *hist_SMttbar_noBtag_AK8jetMass = new TH1F("hist_SMttbar_noBtag_AK8jetMass","Jet Mass - 13 TeV (SM t#bar{t});Jet Mass (GeV); Events",80,0,800);

  /////pt histograms                                                                                                                                                                                 
  TH1F *hist_SMttbar_noBtag_topTagEffPt = new TH1F("hist_SMttbar_noBtag_topTagEffPt","Top Tagging Efficiency (Pt) - 13 TeV (Standard Model t#bar{t}); pt; Efficiency",nbins_pt,bins_pt);
  TH1F *hist_SMttbar_noBtag_tagJet1pt = new TH1F("hist_SMttbar_noBtag_tagJet1pt","Top Tagging Efficiency - 13 TeV; pt; Efficiency",nbins_pt,bins_pt);
  TH1F *hist_SMttbar_noBtag_tagJet2pt = new TH1F("hist_SMttbar_noBtag_tagJet2pt","Jet 2 Pt - 13 TeV; pt; Events",nbins_pt,bins_pt);
  //TH1F *hist_SMttbar_noBtag_jetPt = new TH1F("hist_SMttbar_noBtag_jetPt","Jet Pt - 13 TeV; pt; Events",nbins_pt,bins_pt);                                                                                                                  
  TH1F *hist_SMttbar_noBtag_jet1pt = new TH1F("hist_SMttbar_noBtag_jet1pt","Generated Top 1 Pt - 13 TeV; pt; Events",nbins_pt,bins_pt);
  TH1F *hist_SMttbar_noBtag_jet2pt = new TH1F("hist_SMttbar_noBtag_jet2pt","Generated Top 2 Pt - 13 TeV; pt; Events",nbins_pt,bins_pt);
  //TH1F *hist_SMttbar_noBtag_genTopPt = new TH1F("hist_SMttbar_noBtag_genTopPt","Generated Top Pt - 13 TeV; pt; Events",nbins_pt,bins_pt);                                                                                                  
  hist_SMttbar_noBtag_tagJet1pt->Sumw2();
  hist_SMttbar_noBtag_tagJet2pt->Sumw2();
  hist_SMttbar_noBtag_jet1pt->Sumw2();
  hist_SMttbar_noBtag_jet2pt->Sumw2();

  /////pileup histograms - no pt cut                                                                                                                                                                     
  TH1F *hist_SMttbar_noBtag_topTagEffNpv = new TH1F("hist_SMttbar_noBtag_topTagEffNpv","Top Tagging Efficiency (Npv)- 13 TeV (Standard Model t#bar{t}); Number of Primary Vertices; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_tagNpv1 = new TH1F("hist_SMttbar_noBtag_tagNpv1","Top Tagging Efficiency - 13 TeV; Npv; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_tagNpv2 = new TH1F("hist_SMttbar_noBtag_tagNpv2","Jet 2 Pt - 13 TeV; Npt; Events",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_npv1 = new TH1F("hist_SMttbar_noBtag_npv1","Generated Top 1 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_npv2 = new TH1F("hist_SMttbar_noBtag_npv2","Generated Top 2 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);

  hist_SMttbar_noBtag_tagNpv1->Sumw2();
  hist_SMttbar_noBtag_tagNpv2->Sumw2();
  hist_SMttbar_noBtag_npv1->Sumw2();
  hist_SMttbar_noBtag_npv2->Sumw2();

  /////pileup histograms - pt > 400 GeV                                                                                                                                                                  
  TH1F *hist_SMttbar_noBtag_topTagEffNpv_400 = new TH1F("hist_SMttbar_noBtag_topTagEffNpv_400","Top Tagging Efficiency (Npv)- 13 TeV; Number of Primary Vertices; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_tagNpv1_400 = new TH1F("hist_SMttbar_noBtag_tagNpv1_400","Top Tagging Efficiency - 13 TeV; Npv; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_tagNpv2_400 = new TH1F("hist_SMttbar_noBtag_tagNpv2_400","Jet 2 Pt - 13 TeV; Npt; Events",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_npv1_400 = new TH1F("hist_SMttbar_noBtag_npv1_400","Generated Top 1 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_npv2_400 = new TH1F("hist_SMttbar_noBtag_npv2_400","Generated Top 2 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);

  hist_SMttbar_noBtag_tagNpv1_400->Sumw2();
  hist_SMttbar_noBtag_tagNpv2_400->Sumw2();
  hist_SMttbar_noBtag_npv1_400->Sumw2();
  hist_SMttbar_noBtag_npv2_400->Sumw2();

  /////pileup histograms - pt > 500 GeV                                                                                                                                                                  
  TH1F *hist_SMttbar_noBtag_topTagEffNpv_500 = new TH1F("hist_SMttbar_noBtag_topTagEffNpv_500","Top Tagging Efficiency (Npv)- 13 TeV; Number of Primary Vertices; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_tagNpv1_500 = new TH1F("hist_SMttbar_noBtag_tagNpv1_500","Top Tagging Efficiency - 13 TeV; Npv; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_tagNpv2_500 = new TH1F("hist_SMttbar_noBtag_tagNpv2_500","Jet 2 Pt - 13 TeV; Npt; Events",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_npv1_500 = new TH1F("hist_SMttbar_noBtag_npv1_500","Generated Top 1 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_npv2_500 = new TH1F("hist_SMttbar_noBtag_npv2_500","Generated Top 2 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);

  hist_SMttbar_noBtag_tagNpv1_500->Sumw2();
  hist_SMttbar_noBtag_tagNpv2_500->Sumw2();
  hist_SMttbar_noBtag_npv1_500->Sumw2();
  hist_SMttbar_noBtag_npv2_500->Sumw2();

  /////pileup histograms - pt > 600 GeV                                                                                                                                                                  
  TH1F *hist_SMttbar_noBtag_topTagEffNpv_600 = new TH1F("hist_SMttbar_noBtag_topTagEffNpv_600","Top Tagging Efficiency (Npv)- 13 TeV; Number of Primary Vertices; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_tagNpv1_600 = new TH1F("hist_SMttbar_noBtag_tagNpv1_600","Top Tagging Efficiency - 13 TeV; Npv; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_tagNpv2_600 = new TH1F("hist_SMttbar_noBtag_tagNpv2_600","Jet 2 Pt - 13 TeV; Npt; Events",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_npv1_600 = new TH1F("hist_SMttbar_noBtag_npv1_600","Generated Top 1 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_npv2_600 = new TH1F("hist_SMttbar_noBtag_npv2_600","Generated Top 2 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);

  hist_SMttbar_noBtag_tagNpv1_600->Sumw2();
  hist_SMttbar_noBtag_tagNpv2_600->Sumw2();
  hist_SMttbar_noBtag_npv1_600->Sumw2();
  hist_SMttbar_noBtag_npv2_600->Sumw2();

  /////pileup histograms - pt > 700 GeV                                                                                                                                                                  
  TH1F *hist_SMttbar_noBtag_topTagEffNpv_700 = new TH1F("hist_SMttbar_noBtag_topTagEffNpv_700","Top Tagging Efficiency (Npv)- 13 TeV; Number of Primary Vertices; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_tagNpv1_700 = new TH1F("hist_SMttbar_noBtag_tagNpv1_700","Top Tagging Efficiency - 13 TeV; Npv; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_tagNpv2_700 = new TH1F("hist_SMttbar_noBtag_tagNpv2_700","Jet 2 Pt - 13 TeV; Npt; Events",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_npv1_700 = new TH1F("hist_SMttbar_noBtag_npv1_700","Generated Top 1 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_npv2_700 = new TH1F("hist_SMttbar_noBtag_npv2_700","Generated Top 2 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);

  hist_SMttbar_noBtag_tagNpv1_700->Sumw2();
  hist_SMttbar_noBtag_tagNpv2_700->Sumw2();
  hist_SMttbar_noBtag_npv1_700->Sumw2();
  hist_SMttbar_noBtag_npv2_700->Sumw2();

  /////////////////////////////////                                                                                                                                                                   
  //// AK8 Filtered Jets                                                                                                                                                                           
  /////////////////////////////////  

  /////jet mass histogram
  TH1F *hist_SMttbar_noBtag_filtered_AK8jetMass = new TH1F("hist_SMttbar_noBtag_filtered_AK8jetMass","Jet Mass - 13 TeV (SM t#bar{t});Jet Mass (GeV); Events",80,0,800);

  /////pt histograms                                                                                                                                                                          
  TH1F *hist_SMttbar_noBtag_filtered_topTagEffPt = new TH1F("hist_SMttbar_noBtag_filtered_topTagEffPt","Top Tagging Efficiency (Pt) - 13 TeV (Standard Model t#bar{t}); pt; Efficiency",nbins_pt,bins_pt);
  TH1F *hist_SMttbar_noBtag_filtered_tagJet1pt = new TH1F("hist_SMttbar_noBtag_filtered_tagJet1pt","Top Tagging Efficiency - 13 TeV; pt; Efficiency",nbins_pt,bins_pt);
  TH1F *hist_SMttbar_noBtag_filtered_tagJet2pt = new TH1F("hist_SMttbar_noBtag_filtered_tagJet2pt","Jet 2 Pt - 13 TeV; pt; Events",nbins_pt,bins_pt);
  //TH1F *hist_SMttbar_noBtag_filtered_jetPt = new TH1F("hist_SMttbar_noBtag_filtered_jetPt","Jet Pt - 13 TeV; pt; Events",nbins_pt,bins_pt);                                                                                                                  
  TH1F *hist_SMttbar_noBtag_filtered_jet1pt = new TH1F("hist_SMttbar_noBtag_filtered_jet1pt","Generated Top 1 Pt - 13 TeV; pt; Events",nbins_pt,bins_pt);
  TH1F *hist_SMttbar_noBtag_filtered_jet2pt = new TH1F("hist_SMttbar_noBtag_filtered_jet2pt","Generated Top 2 Pt - 13 TeV; pt; Events",nbins_pt,bins_pt);
  //TH1F *hist_SMttbar_noBtag_filtered_genTopPt = new TH1F("hist_SMttbar_noBtag_filtered_genTopPt","Generated Top Pt - 13 TeV; pt; Events",nbins_pt,bins_pt);                                                                                                  
  hist_SMttbar_noBtag_filtered_tagJet1pt->Sumw2();
  hist_SMttbar_noBtag_filtered_tagJet2pt->Sumw2();
  hist_SMttbar_noBtag_filtered_jet1pt->Sumw2();
  hist_SMttbar_noBtag_filtered_jet2pt->Sumw2();

  /////pileup histograms - no pt cut                                                                                                                                                                 
  TH1F *hist_SMttbar_noBtag_filtered_topTagEffNpv = new TH1F("hist_SMttbar_noBtag_filtered_topTagEffNpv","Top Tagging Efficiency (Npv)- 13 TeV (Standard Model t#bar{t}); Number of Primary Vertices; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_filtered_tagNpv1 = new TH1F("hist_SMttbar_noBtag_filtered_tagNpv1","Top Tagging Efficiency - 13 TeV; Npv; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_filtered_tagNpv2 = new TH1F("hist_SMttbar_noBtag_filtered_tagNpv2","Jet 2 Pt - 13 TeV; Npt; Events",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_filtered_npv1 = new TH1F("hist_SMttbar_noBtag_filtered_npv1","Generated Top 1 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_filtered_npv2 = new TH1F("hist_SMttbar_noBtag_filtered_npv2","Generated Top 2 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);

  hist_SMttbar_noBtag_filtered_tagNpv1->Sumw2();
  hist_SMttbar_noBtag_filtered_tagNpv2->Sumw2();
  hist_SMttbar_noBtag_filtered_npv1->Sumw2();
  hist_SMttbar_noBtag_filtered_npv2->Sumw2();

  /////pileup histograms - pt > 400 GeV                                                                                                                                                                  
  TH1F *hist_SMttbar_noBtag_filtered_topTagEffNpv_400 = new TH1F("hist_SMttbar_noBtag_filtered_topTagEffNpv_400","Top Tagging Efficiency (Npv)- 13 TeV; Number of Primary Vertices; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_filtered_tagNpv1_400 = new TH1F("hist_SMttbar_noBtag_filtered_tagNpv1_400","Top Tagging Efficiency - 13 TeV; Npv; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_filtered_tagNpv2_400 = new TH1F("hist_SMttbar_noBtag_filtered_tagNpv2_400","Jet 2 Pt - 13 TeV; Npt; Events",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_filtered_npv1_400 = new TH1F("hist_SMttbar_noBtag_filtered_npv1_400","Generated Top 1 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_filtered_npv2_400 = new TH1F("hist_SMttbar_noBtag_filtered_npv2_400","Generated Top 2 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);

  hist_SMttbar_noBtag_filtered_tagNpv1_400->Sumw2();
  hist_SMttbar_noBtag_filtered_tagNpv2_400->Sumw2();
  hist_SMttbar_noBtag_filtered_npv1_400->Sumw2();
  hist_SMttbar_noBtag_filtered_npv2_400->Sumw2();

  /////pileup histograms - pt > 500 GeV                                                                                                                                                                  
  TH1F *hist_SMttbar_noBtag_filtered_topTagEffNpv_500 = new TH1F("hist_SMttbar_noBtag_filtered_topTagEffNpv_500","Top Tagging Efficiency (Npv)- 13 TeV; Number of Primary Vertices; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_filtered_tagNpv1_500 = new TH1F("hist_SMttbar_noBtag_filtered_tagNpv1_500","Top Tagging Efficiency - 13 TeV; Npv; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_filtered_tagNpv2_500 = new TH1F("hist_SMttbar_noBtag_filtered_tagNpv2_500","Jet 2 Pt - 13 TeV; Npt; Events",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_filtered_npv1_500 = new TH1F("hist_SMttbar_noBtag_filtered_npv1_500","Generated Top 1 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_filtered_npv2_500 = new TH1F("hist_SMttbar_noBtag_filtered_npv2_500","Generated Top 2 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);

  hist_SMttbar_noBtag_filtered_tagNpv1_500->Sumw2();
  hist_SMttbar_noBtag_filtered_tagNpv2_500->Sumw2();
  hist_SMttbar_noBtag_filtered_npv1_500->Sumw2();
  hist_SMttbar_noBtag_filtered_npv2_500->Sumw2();

  /////pileup histograms - pt > 600 GeV                                                                                                                                                                  
  TH1F *hist_SMttbar_noBtag_filtered_topTagEffNpv_600 = new TH1F("hist_SMttbar_noBtag_filtered_topTagEffNpv_600","Top Tagging Efficiency (Npv)- 13 TeV; Number of Primary Vertices; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_filtered_tagNpv1_600 = new TH1F("hist_SMttbar_noBtag_filtered_tagNpv1_600","Top Tagging Efficiency - 13 TeV; Npv; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_filtered_tagNpv2_600 = new TH1F("hist_SMttbar_noBtag_filtered_tagNpv2_600","Jet 2 Pt - 13 TeV; Npt; Events",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_filtered_npv1_600 = new TH1F("hist_SMttbar_noBtag_filtered_npv1_600","Generated Top 1 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_filtered_npv2_600 = new TH1F("hist_SMttbar_noBtag_filtered_npv2_600","Generated Top 2 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);

  hist_SMttbar_noBtag_filtered_tagNpv1_600->Sumw2();
  hist_SMttbar_noBtag_filtered_tagNpv2_600->Sumw2();
  hist_SMttbar_noBtag_filtered_npv1_600->Sumw2();
  hist_SMttbar_noBtag_filtered_npv2_600->Sumw2();

  /////pileup histograms - pt > 700 GeV                                                                                                                                                                  
  TH1F *hist_SMttbar_noBtag_filtered_topTagEffNpv_700 = new TH1F("hist_SMttbar_noBtag_filtered_topTagEffNpv_700","Top Tagging Efficiency (Npv)- 13 TeV; Number of Primary Vertices; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_filtered_tagNpv1_700 = new TH1F("hist_SMttbar_noBtag_filtered_tagNpv1_700","Top Tagging Efficiency - 13 TeV; Npv; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_filtered_tagNpv2_700 = new TH1F("hist_SMttbar_noBtag_filtered_tagNpv2_700","Jet 2 Pt - 13 TeV; Npt; Events",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_filtered_npv1_700 = new TH1F("hist_SMttbar_noBtag_filtered_npv1_700","Generated Top 1 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_filtered_npv2_700 = new TH1F("hist_SMttbar_noBtag_filtered_npv2_700","Generated Top 2 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);

  hist_SMttbar_noBtag_filtered_tagNpv1_700->Sumw2();
  hist_SMttbar_noBtag_filtered_tagNpv2_700->Sumw2();
  hist_SMttbar_noBtag_filtered_npv1_700->Sumw2();
  hist_SMttbar_noBtag_filtered_npv2_700->Sumw2();

  /////////////////////////////////                                                                                                                                                                   
  //// AK8 Pruned Jets                                                                                                                                                                           
  /////////////////////////////////  

  /////jet mass histogram
  TH1F *hist_SMttbar_noBtag_pruned_AK8jetMass = new TH1F("hist_SMttbar_noBtag_prunedd_AK8jetMass","Jet Mass - 13 TeV (SM t#bar{t});Jet Mass (GeV); Events",80,0,800);

  /////pt histograms                                                                                                                                                                          
  TH1F *hist_SMttbar_noBtag_pruned_topTagEffPt = new TH1F("hist_SMttbar_noBtag_pruned_topTagEffPt","Top Tagging Efficiency (Pt) - 13 TeV (Standard Model t#bar{t}); pt; Efficiency",nbins_pt,bins_pt);
  TH1F *hist_SMttbar_noBtag_pruned_tagJet1pt = new TH1F("hist_SMttbar_noBtag_pruned_tagJet1pt","Top Tagging Efficiency - 13 TeV; pt; Efficiency",nbins_pt,bins_pt);
  TH1F *hist_SMttbar_noBtag_pruned_tagJet2pt = new TH1F("hist_SMttbar_noBtag_pruned_tagJet2pt","Jet 2 Pt - 13 TeV; pt; Events",nbins_pt,bins_pt);
  //TH1F *hist_SMttbar_noBtag_pruned_jetPt = new TH1F("hist_SMttbar_noBtag_pruned_jetPt","Jet Pt - 13 TeV; pt; Events",nbins_pt,bins_pt);                                                                                                                  
  TH1F *hist_SMttbar_noBtag_pruned_jet1pt = new TH1F("hist_SMttbar_noBtag_pruned_jet1pt","Generated Top 1 Pt - 13 TeV; pt; Events",nbins_pt,bins_pt);
  TH1F *hist_SMttbar_noBtag_pruned_jet2pt = new TH1F("hist_SMttbar_noBtag_pruned_jet2pt","Generated Top 2 Pt - 13 TeV; pt; Events",nbins_pt,bins_pt);
  //TH1F *hist_SMttbar_noBtag_pruned_genTopPt = new TH1F("hist_SMttbar_noBtag_pruned_genTopPt","Generated Top Pt - 13 TeV; pt; Events",nbins_pt,bins_pt);                                                                                                  
  hist_SMttbar_noBtag_pruned_tagJet1pt->Sumw2();
  hist_SMttbar_noBtag_pruned_tagJet2pt->Sumw2();
  hist_SMttbar_noBtag_pruned_jet1pt->Sumw2();
  hist_SMttbar_noBtag_pruned_jet2pt->Sumw2();

  /////pileup histograms - no pt cut                                                                                                                                                                 
  TH1F *hist_SMttbar_noBtag_pruned_topTagEffNpv = new TH1F("hist_SMttbar_noBtag_pruned_topTagEffNpv","Top Tagging Efficiency (Npv)- 13 TeV (Standard Model t#bar{t}); Number of Primary Vertices; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_pruned_tagNpv1 = new TH1F("hist_SMttbar_noBtag_pruned_tagNpv1","Top Tagging Efficiency - 13 TeV; Npv; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_pruned_tagNpv2 = new TH1F("hist_SMttbar_noBtag_pruned_tagNpv2","Jet 2 Pt - 13 TeV; Npt; Events",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_pruned_npv1 = new TH1F("hist_SMttbar_noBtag_pruned_npv1","Generated Top 1 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_pruned_npv2 = new TH1F("hist_SMttbar_noBtag_pruned_npv2","Generated Top 2 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);

  hist_SMttbar_noBtag_pruned_tagNpv1->Sumw2();
  hist_SMttbar_noBtag_pruned_tagNpv2->Sumw2();
  hist_SMttbar_noBtag_pruned_npv1->Sumw2();
  hist_SMttbar_noBtag_pruned_npv2->Sumw2();

  /////pileup histograms - pt > 400 GeV                                                                                                                                                                  
  TH1F *hist_SMttbar_noBtag_pruned_topTagEffNpv_400 = new TH1F("hist_SMttbar_noBtag_pruned_topTagEffNpv_400","Top Tagging Efficiency (Npv)- 13 TeV; Number of Primary Vertices; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_pruned_tagNpv1_400 = new TH1F("hist_SMttbar_noBtag_pruned_tagNpv1_400","Top Tagging Efficiency - 13 TeV; Npv; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_pruned_tagNpv2_400 = new TH1F("hist_SMttbar_noBtag_pruned_tagNpv2_400","Jet 2 Pt - 13 TeV; Npt; Events",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_pruned_npv1_400 = new TH1F("hist_SMttbar_noBtag_pruned_npv1_400","Generated Top 1 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_pruned_npv2_400 = new TH1F("hist_SMttbar_noBtag_pruned_npv2_400","Generated Top 2 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);

  hist_SMttbar_noBtag_pruned_tagNpv1_400->Sumw2();
  hist_SMttbar_noBtag_pruned_tagNpv2_400->Sumw2();
  hist_SMttbar_noBtag_pruned_npv1_400->Sumw2();
  hist_SMttbar_noBtag_pruned_npv2_400->Sumw2();

  /////pileup histograms - pt > 500 GeV                                                                                                                                                                  
  TH1F *hist_SMttbar_noBtag_pruned_topTagEffNpv_500 = new TH1F("hist_SMttbar_noBtag_pruned_topTagEffNpv_500","Top Tagging Efficiency (Npv)- 13 TeV; Number of Primary Vertices; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_pruned_tagNpv1_500 = new TH1F("hist_SMttbar_noBtag_pruned_tagNpv1_500","Top Tagging Efficiency - 13 TeV; Npv; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_pruned_tagNpv2_500 = new TH1F("hist_SMttbar_noBtag_pruned_tagNpv2_500","Jet 2 Pt - 13 TeV; Npt; Events",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_pruned_npv1_500 = new TH1F("hist_SMttbar_noBtag_pruned_npv1_500","Generated Top 1 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_pruned_npv2_500 = new TH1F("hist_SMttbar_noBtag_pruned_npv2_500","Generated Top 2 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);

  hist_SMttbar_noBtag_pruned_tagNpv1_500->Sumw2();
  hist_SMttbar_noBtag_pruned_tagNpv2_500->Sumw2();
  hist_SMttbar_noBtag_pruned_npv1_500->Sumw2();
  hist_SMttbar_noBtag_pruned_npv2_500->Sumw2();

  /////pileup histograms - pt > 600 GeV                                                                                                                                                                  
  TH1F *hist_SMttbar_noBtag_pruned_topTagEffNpv_600 = new TH1F("hist_SMttbar_noBtag_pruned_topTagEffNpv_600","Top Tagging Efficiency (Npv)- 13 TeV; Number of Primary Vertices; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_pruned_tagNpv1_600 = new TH1F("hist_SMttbar_noBtag_pruned_tagNpv1_600","Top Tagging Efficiency - 13 TeV; Npv; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_pruned_tagNpv2_600 = new TH1F("hist_SMttbar_noBtag_pruned_tagNpv2_600","Jet 2 Pt - 13 TeV; Npt; Events",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_pruned_npv1_600 = new TH1F("hist_SMttbar_noBtag_pruned_npv1_600","Generated Top 1 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_pruned_npv2_600 = new TH1F("hist_SMttbar_noBtag_pruned_npv2_600","Generated Top 2 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);

  hist_SMttbar_noBtag_pruned_tagNpv1_600->Sumw2();
  hist_SMttbar_noBtag_pruned_tagNpv2_600->Sumw2();
  hist_SMttbar_noBtag_pruned_npv1_600->Sumw2();
  hist_SMttbar_noBtag_pruned_npv2_600->Sumw2();

  /////pileup histograms - pt > 700 GeV                                                                                                                                                                  
  TH1F *hist_SMttbar_noBtag_pruned_topTagEffNpv_700 = new TH1F("hist_SMttbar_noBtag_pruned_topTagEffNpv_700","Top Tagging Efficiency (Npv)- 13 TeV; Number of Primary Vertices; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_pruned_tagNpv1_700 = new TH1F("hist_SMttbar_noBtag_pruned_tagNpv1_700","Top Tagging Efficiency - 13 TeV; Npv; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_pruned_tagNpv2_700 = new TH1F("hist_SMttbar_noBtag_pruned_tagNpv2_700","Jet 2 Pt - 13 TeV; Npt; Events",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_pruned_npv1_700 = new TH1F("hist_SMttbar_noBtag_pruned_npv1_700","Generated Top 1 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_pruned_npv2_700 = new TH1F("hist_SMttbar_noBtag_pruned_npv2_700","Generated Top 2 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);

  hist_SMttbar_noBtag_pruned_tagNpv1_700->Sumw2();
  hist_SMttbar_noBtag_pruned_tagNpv2_700->Sumw2();
  hist_SMttbar_noBtag_pruned_npv1_700->Sumw2();
  hist_SMttbar_noBtag_pruned_npv2_700->Sumw2();

  /////////////////////////////////                                                                                                                                                                   
  //// AK8 Trimmed Jets                                                                                                                                                                           
  /////////////////////////////////  

  /////jet mass histogram
  TH1F *hist_SMttbar_noBtag_trimmed_AK8jetMass = new TH1F("hist_SMttbar_noBtag_trimmed_AK8jetMass","Jet Mass - 13 TeV (SM t#bar{t});Jet Mass (GeV); Events",80,0,800);

  /////pt histograms                                                                                                                                                                          
  TH1F *hist_SMttbar_noBtag_trimmed_topTagEffPt = new TH1F("hist_SMttbar_noBtag_trimmed_topTagEffPt","Top Tagging Efficiency (Pt) - 13 TeV (Standard Model t#bar{t}); pt; Efficiency",nbins_pt,bins_pt);
  TH1F *hist_SMttbar_noBtag_trimmed_tagJet1pt = new TH1F("hist_SMttbar_noBtag_trimmed_tagJet1pt","Top Tagging Efficiency - 13 TeV; pt; Efficiency",nbins_pt,bins_pt);
  TH1F *hist_SMttbar_noBtag_trimmed_tagJet2pt = new TH1F("hist_SMttbar_noBtag_trimmed_tagJet2pt","Jet 2 Pt - 13 TeV; pt; Events",nbins_pt,bins_pt);
  //TH1F *hist_SMttbar_noBtag_trimmed_jetPt = new TH1F("hist_SMttbar_noBtag_trimmed_jetPt","Jet Pt - 13 TeV; pt; Events",nbins_pt,bins_pt);                                                                                                                  
  TH1F *hist_SMttbar_noBtag_trimmed_jet1pt = new TH1F("hist_SMttbar_noBtag_trimmed_jet1pt","Generated Top 1 Pt - 13 TeV; pt; Events",nbins_pt,bins_pt);
  TH1F *hist_SMttbar_noBtag_trimmed_jet2pt = new TH1F("hist_SMttbar_noBtag_trimmed_jet2pt","Generated Top 2 Pt - 13 TeV; pt; Events",nbins_pt,bins_pt);
  //TH1F *hist_SMttbar_noBtag_trimmed_genTopPt = new TH1F("hist_SMttbar_noBtag_trimmed_genTopPt","Generated Top Pt - 13 TeV; pt; Events",nbins_pt,bins_pt);                                                                                                  
  hist_SMttbar_noBtag_trimmed_tagJet1pt->Sumw2();
  hist_SMttbar_noBtag_trimmed_tagJet2pt->Sumw2();
  hist_SMttbar_noBtag_trimmed_jet1pt->Sumw2();
  hist_SMttbar_noBtag_trimmed_jet2pt->Sumw2();

  /////pileup histograms - no pt cut                                                                                                                                                                 
  TH1F *hist_SMttbar_noBtag_trimmed_topTagEffNpv = new TH1F("hist_SMttbar_noBtag_trimmed_topTagEffNpv","Top Tagging Efficiency (Npv)- 13 TeV (Standard Model t#bar{t}); Number of Primary Vertices; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_trimmed_tagNpv1 = new TH1F("hist_SMttbar_noBtag_trimmed_tagNpv1","Top Tagging Efficiency - 13 TeV; Npv; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_trimmed_tagNpv2 = new TH1F("hist_SMttbar_noBtag_trimmed_tagNpv2","Jet 2 Pt - 13 TeV; Npt; Events",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_trimmed_npv1 = new TH1F("hist_SMttbar_noBtag_trimmed_npv1","Generated Top 1 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_trimmed_npv2 = new TH1F("hist_SMttbar_noBtag_trimmed_npv2","Generated Top 2 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);

  hist_SMttbar_noBtag_trimmed_tagNpv1->Sumw2();
  hist_SMttbar_noBtag_trimmed_tagNpv2->Sumw2();
  hist_SMttbar_noBtag_trimmed_npv1->Sumw2();
  hist_SMttbar_noBtag_trimmed_npv2->Sumw2();

  /////pileup histograms - pt > 400 GeV                                                                                                                                                                  
  TH1F *hist_SMttbar_noBtag_trimmed_topTagEffNpv_400 = new TH1F("hist_SMttbar_noBtag_trimmed_topTagEffNpv_400","Top Tagging Efficiency (Npv)- 13 TeV; Number of Primary Vertices; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_trimmed_tagNpv1_400 = new TH1F("hist_SMttbar_noBtag_trimmed_tagNpv1_400","Top Tagging Efficiency - 13 TeV; Npv; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_trimmed_tagNpv2_400 = new TH1F("hist_SMttbar_noBtag_trimmed_tagNpv2_400","Jet 2 Pt - 13 TeV; Npt; Events",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_trimmed_npv1_400 = new TH1F("hist_SMttbar_noBtag_trimmed_npv1_400","Generated Top 1 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_trimmed_npv2_400 = new TH1F("hist_SMttbar_noBtag_trimmed_npv2_400","Generated Top 2 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);

  hist_SMttbar_noBtag_trimmed_tagNpv1_400->Sumw2();
  hist_SMttbar_noBtag_trimmed_tagNpv2_400->Sumw2();
  hist_SMttbar_noBtag_trimmed_npv1_400->Sumw2();
  hist_SMttbar_noBtag_trimmed_npv2_400->Sumw2();

  /////pileup histograms - pt > 500 GeV                                                                                                                                                                  
  TH1F *hist_SMttbar_noBtag_trimmed_topTagEffNpv_500 = new TH1F("hist_SMttbar_noBtag_trimmed_topTagEffNpv_500","Top Tagging Efficiency (Npv)- 13 TeV; Number of Primary Vertices; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_trimmed_tagNpv1_500 = new TH1F("hist_SMttbar_noBtag_trimmed_tagNpv1_500","Top Tagging Efficiency - 13 TeV; Npv; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_trimmed_tagNpv2_500 = new TH1F("hist_SMttbar_noBtag_trimmed_tagNpv2_500","Jet 2 Pt - 13 TeV; Npt; Events",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_trimmed_npv1_500 = new TH1F("hist_SMttbar_noBtag_trimmed_npv1_500","Generated Top 1 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_trimmed_npv2_500 = new TH1F("hist_SMttbar_noBtag_trimmed_npv2_500","Generated Top 2 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);

  hist_SMttbar_noBtag_trimmed_tagNpv1_500->Sumw2();
  hist_SMttbar_noBtag_trimmed_tagNpv2_500->Sumw2();
  hist_SMttbar_noBtag_trimmed_npv1_500->Sumw2();
  hist_SMttbar_noBtag_trimmed_npv2_500->Sumw2();

  /////pileup histograms - pt > 600 GeV                                                                                                                                                                  
  TH1F *hist_SMttbar_noBtag_trimmed_topTagEffNpv_600 = new TH1F("hist_SMttbar_noBtag_trimmed_topTagEffNpv_600","Top Tagging Efficiency (Npv)- 13 TeV; Number of Primary Vertices; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_trimmed_tagNpv1_600 = new TH1F("hist_SMttbar_noBtag_trimmed_tagNpv1_600","Top Tagging Efficiency - 13 TeV; Npv; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_trimmed_tagNpv2_600 = new TH1F("hist_SMttbar_noBtag_trimmed_tagNpv2_600","Jet 2 Pt - 13 TeV; Npt; Events",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_trimmed_npv1_600 = new TH1F("hist_SMttbar_noBtag_trimmed_npv1_600","Generated Top 1 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_trimmed_npv2_600 = new TH1F("hist_SMttbar_noBtag_trimmed_npv2_600","Generated Top 2 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);

  hist_SMttbar_noBtag_trimmed_tagNpv1_600->Sumw2();
  hist_SMttbar_noBtag_trimmed_tagNpv2_600->Sumw2();
  hist_SMttbar_noBtag_trimmed_npv1_600->Sumw2();
  hist_SMttbar_noBtag_trimmed_npv2_600->Sumw2();

  /////pileup histograms - pt > 700 GeV                                                                                                                                                                  
  TH1F *hist_SMttbar_noBtag_trimmed_topTagEffNpv_700 = new TH1F("hist_SMttbar_noBtag_trimmed_topTagEffNpv_700","Top Tagging Efficiency (Npv)- 13 TeV; Number of Primary Vertices; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_trimmed_tagNpv1_700 = new TH1F("hist_SMttbar_noBtag_trimmed_tagNpv1_700","Top Tagging Efficiency - 13 TeV; Npv; Efficiency",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_trimmed_tagNpv2_700 = new TH1F("hist_SMttbar_noBtag_trimmed_tagNpv2_700","Jet 2 Pt - 13 TeV; Npt; Events",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_trimmed_npv1_700 = new TH1F("hist_SMttbar_noBtag_trimmed_npv1_700","Generated Top 1 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);
  TH1F *hist_SMttbar_noBtag_trimmed_npv2_700 = new TH1F("hist_SMttbar_noBtag_trimmed_npv2_700","Generated Top 2 Npv - 13 TeV; Npv; Events",nbins_npv,bins_npv);

  hist_SMttbar_noBtag_trimmed_tagNpv1_700->Sumw2();
  hist_SMttbar_noBtag_trimmed_tagNpv2_700->Sumw2();
  hist_SMttbar_noBtag_trimmed_npv1_700->Sumw2();
  hist_SMttbar_noBtag_trimmed_npv2_700->Sumw2();
    
  vector<string> fileNames;

  string line;
  ifstream myfile ("rootFiles_SMttbar13TeV.txt");
  if (myfile.is_open()){
      while ( getline (myfile,line) )
	{
	  fileNames.push_back(line);
	}
      myfile.close();
    }
  
  //fileNames.push_back("/uscms_data/d3/camclean/CSA14/topTaggingEfficiency/CMSSW_7_0_6_patch1/src/Analysis/analyzeMiniAOD/RSGluonToTT_M_4000_08_19_2014/res/miniAOD*.root");

  fwlite::ChainEvent ev(fileNames);

  for( ev.toBegin(); ! ev.atEnd(); ++ev) {
    fwlite::Handle<int> h_jet1tagEff;
    fwlite::Handle<int> h_jet2tagEff;
    fwlite::Handle<int> h_AK8jet1tagEff;
    fwlite::Handle<int> h_AK8jet2tagEff;
    fwlite::Handle<unsigned int> h_npv;
    fwlite::Handle<double> h_jet1ptEff;
    fwlite::Handle<double> h_jet2ptEff;
    fwlite::Handle<vector<double>> h_AK8jetMass_filtered;
    fwlite::Handle<vector<double>> h_AK8jetMass_pruned;
    fwlite::Handle<vector<double>> h_AK8jetMass_trimmed;
    fwlite::Handle<vector<reco::Candidate::PolarLorentzVector>> h_AK8jetP4;

    h_jet1tagEff.getByLabel(ev,"miniAOD","jet1tagEff","MiniAOD");
    h_jet2tagEff.getByLabel(ev,"miniAOD","jet2tagEff","MiniAOD");
    h_AK8jet1tagEff.getByLabel(ev,"miniAOD","AK8jet1tagEff","MiniAOD");
    h_AK8jet2tagEff.getByLabel(ev,"miniAOD","AK8jet2tagEff","MiniAOD");
    h_jet1ptEff.getByLabel(ev,"miniAOD","jet1ptEff","MiniAOD");
    h_jet2ptEff.getByLabel(ev,"miniAOD","jet2ptEff","MiniAOD");
    h_npv.getByLabel(ev,"miniAOD","npv","MiniAOD");

    h_AK8jetMass_filtered.getByLabel(ev,"miniAOD","ak8PFJetsCHSFilteredLinks","MiniAOD");
    h_AK8jetMass_pruned.getByLabel(ev,"miniAOD","ak8PFJetsCHSPrunedLinks","MiniAOD");
    h_AK8jetMass_trimmed.getByLabel(ev,"miniAOD","ak8PFJetsCHSTrimmedLinks","MiniAOD");
    h_AK8jetP4.getByLabel(ev,"miniAOD","AK8jetP4","MiniAOD");

    const std::vector<double>* AK8jetMass_filtered = h_AK8jetMass_filtered.product();
    const std::vector<double>* AK8jetMass_pruned = h_AK8jetMass_pruned.product();
    const std::vector<double>* AK8jetMass_trimmed = h_AK8jetMass_trimmed.product();
    const std::vector<reco::Candidate::PolarLorentzVector>* AK8jetP4 = h_AK8jetP4.product();

    int AK8jetSize =  AK8jetP4->size();

    //jet mass histograms                                                                                                                                                                                 
    for(int i=0; i<AK8jetSize; i++){
      if((AK8jetP4->at(i)).pt() > 400){
	hist_SMttbar_noBtag_AK8jetMass->Fill((AK8jetP4->at(i)).M());
	hist_SMttbar_noBtag_filtered_AK8jetMass->Fill(AK8jetMass_filtered->at(i));
	hist_SMttbar_noBtag_pruned_AK8jetMass->Fill(AK8jetMass_pruned->at(i));
	hist_SMttbar_noBtag_trimmed_AK8jetMass->Fill(AK8jetMass_trimmed->at(i));
      }
    }

    /////////////////////////////////
    //// No Mass Grooming Techniques
    /////////////////////////////////

    //denominator histograms (no mass grooming) - 0 = top-matched, not top-tagged; 1 = top-matched and top-tagged                                                                 
    if(*h_jet1tagEff == 0 || *h_jet1tagEff == 1){

      hist_SMttbar_noBtag_npv1->Fill(*h_npv);
      hist_SMttbar_noBtag_jet1pt->Fill(*h_jet1ptEff);
      
      if(*h_jet1ptEff > 400.){
	hist_SMttbar_noBtag_npv1_400->Fill(*h_npv);
      }
      if(*h_jet1ptEff > 500.){
	hist_SMttbar_noBtag_npv1_500->Fill(*h_npv);
      }
      if(*h_jet1ptEff > 600.){
	hist_SMttbar_noBtag_npv1_600->Fill(*h_npv);
      }
      if(*h_jet1ptEff > 700.){
	hist_SMttbar_noBtag_npv1_700->Fill(*h_npv);
      }
    }
 
    if(*h_jet2tagEff == 0 || *h_jet2tagEff == 1){
      hist_SMttbar_noBtag_npv2->Fill(*h_npv);
      hist_SMttbar_noBtag_jet2pt->Fill(*h_jet2ptEff);
      
      if(*h_jet2ptEff > 400.){
	hist_SMttbar_noBtag_npv2_400->Fill(*h_npv);
      }
      if(*h_jet2ptEff > 500.){
	hist_SMttbar_noBtag_npv2_500->Fill(*h_npv);
      }
      if(*h_jet2ptEff > 600.){
	hist_SMttbar_noBtag_npv2_600->Fill(*h_npv);
      }
      if(*h_jet2ptEff > 700.){
	hist_SMttbar_noBtag_npv2_700->Fill(*h_npv);
      }
    }

    //numerator histograms                                                                                                                                                                               
    if(*h_jet1tagEff == 1){
      hist_SMttbar_noBtag_tagJet1pt->Fill(*h_jet1ptEff);
      hist_SMttbar_noBtag_tagNpv1->Fill(*h_npv);
      
      if(*h_jet1ptEff > 400.){
        hist_SMttbar_noBtag_tagNpv1_400->Fill(*h_npv);
      }
      if(*h_jet1ptEff > 500.){
        hist_SMttbar_noBtag_tagNpv1_500->Fill(*h_npv);
      }
      if(*h_jet1ptEff > 600.){
        hist_SMttbar_noBtag_tagNpv1_600->Fill(*h_npv);
      }
      if(*h_jet1ptEff > 700.){
        hist_SMttbar_noBtag_tagNpv1_700->Fill(*h_npv);
      }
    }

    if(*h_jet2tagEff == 1){
      hist_SMttbar_noBtag_tagJet2pt->Fill(*h_jet2ptEff);
      hist_SMttbar_noBtag_tagNpv2->Fill(*h_npv);
      
      if(*h_jet2ptEff > 400.){
        hist_SMttbar_noBtag_tagNpv2_400->Fill(*h_npv);
      }
      if(*h_jet2ptEff > 500.){
        hist_SMttbar_noBtag_tagNpv2_500->Fill(*h_npv);
      }
      if(*h_jet2ptEff > 600.){
        hist_SMttbar_noBtag_tagNpv2_600->Fill(*h_npv);
      }
      if(*h_jet2ptEff > 700.){
        hist_SMttbar_noBtag_tagNpv2_700->Fill(*h_npv);
	//jet2pt_tag = jet1ptEff;                                                                                                                                                                          
      }
    }

    /////////////////////////////////
    //// AK8 Filtered Jets
    /////////////////////////////////

    int filteredJet1tag_1 = *h_AK8jet1tagEff;
    int filteredJet1tag_2 = *h_AK8jet1tagEff;
    int filteredJet1tag_3 = *h_AK8jet1tagEff;
    int filteredJet2tag_1 = *h_AK8jet2tagEff;
    int filteredJet2tag_2 = *h_AK8jet2tagEff;
    int filteredJet2tag_3 = *h_AK8jet2tagEff;

    //denominator histograms (filtered mass) -  1 = top-matched, not top-tagged; 2 = top-matched and top-tagged                                                                 

    if((filteredJet1tag_1 &= 1) == 1 || (filteredJet1tag_2 &= 2) == 2){
      hist_SMttbar_noBtag_filtered_npv1->Fill(*h_npv);
      hist_SMttbar_noBtag_filtered_jet1pt->Fill(*h_jet1ptEff);
      
      if(*h_jet1ptEff > 400.){
	hist_SMttbar_noBtag_filtered_npv1_400->Fill(*h_npv);
      }
      if(*h_jet1ptEff > 500.){
	hist_SMttbar_noBtag_filtered_npv1_500->Fill(*h_npv);
      }
      if(*h_jet1ptEff > 600.){
	hist_SMttbar_noBtag_filtered_npv1_600->Fill(*h_npv);
      }
      if(*h_jet1ptEff > 700.){
	hist_SMttbar_noBtag_filtered_npv1_700->Fill(*h_npv);
      }
    }
 
    if((filteredJet2tag_1 &= 1) == 1 || (filteredJet2tag_2 &= 2) == 2){
      hist_SMttbar_noBtag_filtered_npv2->Fill(*h_npv);
      hist_SMttbar_noBtag_filtered_jet2pt->Fill(*h_jet2ptEff);
      
      if(*h_jet2ptEff > 400.){
	hist_SMttbar_noBtag_filtered_npv2_400->Fill(*h_npv);
      }
      if(*h_jet2ptEff > 500.){
	hist_SMttbar_noBtag_filtered_npv2_500->Fill(*h_npv);
      }
      if(*h_jet2ptEff > 600.){
	hist_SMttbar_noBtag_filtered_npv2_600->Fill(*h_npv);
      }
      if(*h_jet2ptEff > 700.){
	hist_SMttbar_noBtag_filtered_npv2_700->Fill(*h_npv);
      }
    }

    //numerator histograms                                                                                                                                                                           
    if((filteredJet1tag_3 &= 2) == 2){
      hist_SMttbar_noBtag_filtered_tagJet1pt->Fill(*h_jet1ptEff);
      hist_SMttbar_noBtag_filtered_tagNpv1->Fill(*h_npv);

      if(*h_jet1ptEff > 400.){
        hist_SMttbar_noBtag_filtered_tagNpv1_400->Fill(*h_npv);
      }
      if(*h_jet1ptEff > 500.){
        hist_SMttbar_noBtag_filtered_tagNpv1_500->Fill(*h_npv);
      }
      if(*h_jet1ptEff > 600.){
        hist_SMttbar_noBtag_filtered_tagNpv1_600->Fill(*h_npv);
      }
      if(*h_jet1ptEff > 700.){
        hist_SMttbar_noBtag_filtered_tagNpv1_700->Fill(*h_npv);
      }
    }

    if((filteredJet2tag_3 &= 2) == 2){
      hist_SMttbar_noBtag_filtered_tagJet2pt->Fill(*h_jet2ptEff);
      hist_SMttbar_noBtag_filtered_tagNpv2->Fill(*h_npv);
      
      if(*h_jet2ptEff > 400.){
        hist_SMttbar_noBtag_filtered_tagNpv2_400->Fill(*h_npv);
      }
      if(*h_jet2ptEff > 500.){
        hist_SMttbar_noBtag_filtered_tagNpv2_500->Fill(*h_npv);
      }
      if(*h_jet2ptEff > 600.){
        hist_SMttbar_noBtag_filtered_tagNpv2_600->Fill(*h_npv);
      }
      if(*h_jet2ptEff > 700.){
        hist_SMttbar_noBtag_filtered_tagNpv2_700->Fill(*h_npv);
	//jet2pt_tag = jet1ptEff;                                                                                                                                                                     
      }
    }

    /////////////////////////////////
    //// AK8 Pruned Jets
    /////////////////////////////////

    int prunedJet1tag_1 = *h_AK8jet1tagEff;
    int prunedJet1tag_2 = *h_AK8jet1tagEff;
    int prunedJet1tag_3 = *h_AK8jet1tagEff;
    int prunedJet2tag_1 = *h_AK8jet2tagEff;
    int prunedJet2tag_2 = *h_AK8jet2tagEff;
    int prunedJet2tag_3 = *h_AK8jet2tagEff;

    //denominator histograms (pruned mass) -  1 = top-matched, not top-tagged; 4 = top-matched and top-tagged                                                                 

    if((prunedJet1tag_1 &= 1) == 1 || (prunedJet1tag_2 &= 4) == 4){
      hist_SMttbar_noBtag_pruned_npv1->Fill(*h_npv);
      hist_SMttbar_noBtag_pruned_jet1pt->Fill(*h_jet1ptEff);
      
      if(*h_jet1ptEff > 400.){
	hist_SMttbar_noBtag_pruned_npv1_400->Fill(*h_npv);
      }
      if(*h_jet1ptEff > 500.){
	hist_SMttbar_noBtag_pruned_npv1_500->Fill(*h_npv);
      }
      if(*h_jet1ptEff > 600.){
	hist_SMttbar_noBtag_pruned_npv1_600->Fill(*h_npv);
      }
      if(*h_jet1ptEff > 700.){
	hist_SMttbar_noBtag_pruned_npv1_700->Fill(*h_npv);
      }
    }
 
    if((prunedJet2tag_1 &= 1) == 1 || (prunedJet2tag_2 &= 4) == 4){
      hist_SMttbar_noBtag_pruned_npv2->Fill(*h_npv);
      hist_SMttbar_noBtag_pruned_jet2pt->Fill(*h_jet2ptEff);
      
      if(*h_jet2ptEff > 400.){
	hist_SMttbar_noBtag_pruned_npv2_400->Fill(*h_npv);
      }
      if(*h_jet2ptEff > 500.){
	hist_SMttbar_noBtag_pruned_npv2_500->Fill(*h_npv);
      }
      if(*h_jet2ptEff > 600.){
	hist_SMttbar_noBtag_pruned_npv2_600->Fill(*h_npv);
      }
      if(*h_jet2ptEff > 700.){
	hist_SMttbar_noBtag_pruned_npv2_700->Fill(*h_npv);
      }
    }

    //numerator histograms                                                                                                                                                                           
    if((prunedJet1tag_3 &= 4) == 4){
      hist_SMttbar_noBtag_pruned_tagJet1pt->Fill(*h_jet1ptEff);
      hist_SMttbar_noBtag_pruned_tagNpv1->Fill(*h_npv);

      if(*h_jet1ptEff > 400.){
        hist_SMttbar_noBtag_pruned_tagNpv1_400->Fill(*h_npv);
      }
      if(*h_jet1ptEff > 500.){
        hist_SMttbar_noBtag_pruned_tagNpv1_500->Fill(*h_npv);
      }
      if(*h_jet1ptEff > 600.){
        hist_SMttbar_noBtag_pruned_tagNpv1_600->Fill(*h_npv);
      }
      if(*h_jet1ptEff > 700.){
        hist_SMttbar_noBtag_pruned_tagNpv1_700->Fill(*h_npv);
      }
    }

    if((prunedJet2tag_3 &= 4) == 4){
      hist_SMttbar_noBtag_pruned_tagJet2pt->Fill(*h_jet2ptEff);
      hist_SMttbar_noBtag_pruned_tagNpv2->Fill(*h_npv);
      
      if(*h_jet2ptEff > 400.){
        hist_SMttbar_noBtag_pruned_tagNpv2_400->Fill(*h_npv);
      }
      if(*h_jet2ptEff > 500.){
        hist_SMttbar_noBtag_pruned_tagNpv2_500->Fill(*h_npv);
      }
      if(*h_jet2ptEff > 600.){
        hist_SMttbar_noBtag_pruned_tagNpv2_600->Fill(*h_npv);
      }
      if(*h_jet2ptEff > 700.){
        hist_SMttbar_noBtag_pruned_tagNpv2_700->Fill(*h_npv);
	//jet2pt_tag = jet1ptEff;                                                                                                                                                                     
      }
    }

    /////////////////////////////////
    //// AK8 Trimmed Jets
    /////////////////////////////////

    int trimmedJet1tag_1 = *h_AK8jet1tagEff;
    int trimmedJet1tag_2 = *h_AK8jet1tagEff;
    int trimmedJet1tag_3 = *h_AK8jet1tagEff;
    int trimmedJet2tag_1 = *h_AK8jet2tagEff;
    int trimmedJet2tag_2 = *h_AK8jet2tagEff;
    int trimmedJet2tag_3 = *h_AK8jet2tagEff;

    //denominator histograms (trimmed mass) -  1 = top-matched, not top-tagged; 8 = top-matched and top-tagged                                                                 

    if((trimmedJet1tag_1 &= 1) == 1 || (trimmedJet1tag_2 &= 8) == 8){
      hist_SMttbar_noBtag_trimmed_npv1->Fill(*h_npv);
      hist_SMttbar_noBtag_trimmed_jet1pt->Fill(*h_jet1ptEff);
      
      if(*h_jet1ptEff > 400.){
	hist_SMttbar_noBtag_trimmed_npv1_400->Fill(*h_npv);
      }
      if(*h_jet1ptEff > 500.){
	hist_SMttbar_noBtag_trimmed_npv1_500->Fill(*h_npv);
      }
      if(*h_jet1ptEff > 600.){
	hist_SMttbar_noBtag_trimmed_npv1_600->Fill(*h_npv);
      }
      if(*h_jet1ptEff > 700.){
	hist_SMttbar_noBtag_trimmed_npv1_700->Fill(*h_npv);
      }
    }
 
    if((trimmedJet2tag_1 &= 1) == 1 || (trimmedJet2tag_2 &= 8) == 8){
      hist_SMttbar_noBtag_trimmed_npv2->Fill(*h_npv);
      hist_SMttbar_noBtag_trimmed_jet2pt->Fill(*h_jet2ptEff);
      
      if(*h_jet2ptEff > 400.){
	hist_SMttbar_noBtag_trimmed_npv2_400->Fill(*h_npv);
      }
      if(*h_jet2ptEff > 500.){
	hist_SMttbar_noBtag_trimmed_npv2_500->Fill(*h_npv);
      }
      if(*h_jet2ptEff > 600.){
	hist_SMttbar_noBtag_trimmed_npv2_600->Fill(*h_npv);
      }
      if(*h_jet2ptEff > 700.){
	hist_SMttbar_noBtag_trimmed_npv2_700->Fill(*h_npv);
      }
    }

    //numerator histograms                                                                                                                                                                           
    if((trimmedJet1tag_3 &= 8) == 8){
      hist_SMttbar_noBtag_trimmed_tagJet1pt->Fill(*h_jet1ptEff);
      hist_SMttbar_noBtag_trimmed_tagNpv1->Fill(*h_npv);

      if(*h_jet1ptEff > 400.){
        hist_SMttbar_noBtag_trimmed_tagNpv1_400->Fill(*h_npv);
      }
      if(*h_jet1ptEff > 500.){
        hist_SMttbar_noBtag_trimmed_tagNpv1_500->Fill(*h_npv);
      }
      if(*h_jet1ptEff > 600.){
        hist_SMttbar_noBtag_trimmed_tagNpv1_600->Fill(*h_npv);
      }
      if(*h_jet1ptEff > 700.){
        hist_SMttbar_noBtag_trimmed_tagNpv1_700->Fill(*h_npv);
      }
    }

    if((trimmedJet2tag_3 &= 8) == 8){
      hist_SMttbar_noBtag_trimmed_tagJet2pt->Fill(*h_jet2ptEff);
      hist_SMttbar_noBtag_trimmed_tagNpv2->Fill(*h_npv);
      
      if(*h_jet2ptEff > 400.){
        hist_SMttbar_noBtag_trimmed_tagNpv2_400->Fill(*h_npv);
      }
      if(*h_jet2ptEff > 500.){
        hist_SMttbar_noBtag_trimmed_tagNpv2_500->Fill(*h_npv);
      }
      if(*h_jet2ptEff > 600.){
        hist_SMttbar_noBtag_trimmed_tagNpv2_600->Fill(*h_npv);
      }
      if(*h_jet2ptEff > 700.){
        hist_SMttbar_noBtag_trimmed_tagNpv2_700->Fill(*h_npv);
	//jet2pt_tag = jet1ptEff;                                                                                                                                                                     
      }
    }
  }

  /////////////////////////////////
  //// No Mass Grooming Techniques
  /////////////////////////////////

  //efficiency histograms                                                                                                                                                                            
  hist_SMttbar_noBtag_jet1pt->Add(hist_SMttbar_noBtag_jet2pt);                                                                                                                                                                     
  hist_SMttbar_noBtag_tagJet1pt->Add(hist_SMttbar_noBtag_tagJet2pt);                                                                                                                                                              
  //hist_SMttbar_noBtag_tagJet1pt->Divide(hist_SMttbar_noBtag_jet1pt);                                                                                                                                                             
  hist_SMttbar_noBtag_topTagEffPt->Divide(hist_SMttbar_noBtag_tagJet1pt,hist_SMttbar_noBtag_jet1pt,1,1,"B");                                                                                                                                                                                                                                                                                                                                            
  hist_SMttbar_noBtag_npv1->Add(hist_SMttbar_noBtag_npv2);                                                                                                                                                                       
  hist_SMttbar_noBtag_tagNpv1->Add(hist_SMttbar_noBtag_tagNpv2);                                                                                                                                                   
  hist_SMttbar_noBtag_topTagEffNpv->Divide(hist_SMttbar_noBtag_tagNpv1,hist_SMttbar_noBtag_npv1,1,1,"B");                                                                                                                                                      
  hist_SMttbar_noBtag_npv1_400->Add(hist_SMttbar_noBtag_npv2_400); 
  hist_SMttbar_noBtag_tagNpv1_400->Add(hist_SMttbar_noBtag_tagNpv2_400);
  hist_SMttbar_noBtag_topTagEffNpv_400->Divide(hist_SMttbar_noBtag_tagNpv1_400,hist_SMttbar_noBtag_npv1_400,1,1,"B");                                                                                                                                 
  hist_SMttbar_noBtag_npv1_500->Add(hist_SMttbar_noBtag_npv2_500);      
  hist_SMttbar_noBtag_tagNpv1_500->Add(hist_SMttbar_noBtag_tagNpv2_500);
  hist_SMttbar_noBtag_topTagEffNpv_500->Divide(hist_SMttbar_noBtag_tagNpv1_500,hist_SMttbar_noBtag_npv1_500,1,1,"B");                                                                                                                                 
  hist_SMttbar_noBtag_npv1_600->Add(hist_SMttbar_noBtag_npv2_600);      
  hist_SMttbar_noBtag_tagNpv1_600->Add(hist_SMttbar_noBtag_tagNpv2_600);
  hist_SMttbar_noBtag_topTagEffNpv_600->Divide(hist_SMttbar_noBtag_tagNpv1_600,hist_SMttbar_noBtag_npv1_600,1,1,"B");                                                                                                                                 
  hist_SMttbar_noBtag_npv1_700->Add(hist_SMttbar_noBtag_npv2_700);      
  hist_SMttbar_noBtag_tagNpv1_700->Add(hist_SMttbar_noBtag_tagNpv2_700);
  hist_SMttbar_noBtag_topTagEffNpv_700->Divide(hist_SMttbar_noBtag_tagNpv1_700,hist_SMttbar_noBtag_npv1_700,1,1,"B");                                                                                                                                
 
  //fit functions
  TF1 *fit_topTagEffNpv = new TF1("fit_topTagEffNpv","[0]*x + [1]",0.,60.);
  fit_topTagEffNpv->SetParameters(-0.0011,0.388);
  fit_topTagEffNpv->SetParNames("No pt cut: slope","No pt cut: y intercept");
  hist_SMttbar_noBtag_topTagEffNpv->Fit("fit_topTagEffNpv","N");                             
                                                                                                                        
  TF1 *fit_topTagEffNpv_400 = new TF1("fit_topTagEffNpv_400","[0]*x + [1]",0.,60.);
  fit_topTagEffNpv_400->SetParameters(-0.0015,0.43);
  fit_topTagEffNpv_400->SetParNames("pt > 400: slope","pt > 400: y intercept");    
  hist_SMttbar_noBtag_topTagEffNpv_400->Fit("fit_topTagEffNpv_400","N");                                                                                                                                                
  TF1 *fit_topTagEffNpv_500 = new TF1("fit_topTagEffNpv_500","[0]*x + [1]",0.,60.);
  fit_topTagEffNpv_500->SetParameters(-0.002,0.445);
  fit_topTagEffNpv_500->SetParNames("pt > 500: slope","pt > 500: y intercept");    
  hist_SMttbar_noBtag_topTagEffNpv_500->Fit("fit_topTagEffNpv_500","N");                          
                                                                                                                                                                                                 
  TF1 *fit_topTagEffNpv_600 = new TF1("fit_topTagEffNpv_600","[0]*x + [1]",0.,60.);
  fit_topTagEffNpv_600->SetParameters(-0.0025,0.446);
  fit_topTagEffNpv_600->SetParNames("pt > 600: slope","pt > 600: y intercept");    
  hist_SMttbar_noBtag_topTagEffNpv_600->Fit("fit_topTagEffNpv_600","N");                          

  TF1 *fit_topTagEffNpv_700 = new TF1("fit_topTagEffNpv_700","[0]*x + [1]",0.,60.);
  fit_topTagEffNpv_700->SetParameters(-0.0029,0.438);
  fit_topTagEffNpv_700->SetParNames("pt > 700: slope","pt > 700: y intercept");
  hist_SMttbar_noBtag_topTagEffNpv_700->Fit("fit_topTagEffNpv_700","N");

  TCanvas* c1 = new TCanvas("canvas1");
  //c1->Draw();
  //c1->Update();
  hist_SMttbar_noBtag_topTagEffPt->Draw("E");      
  hist_SMttbar_noBtag_topTagEffPt->SetMaximum(1.1);                                                                                                                                                                   

  //legend                                                                                                                                                                                                 
  TLegend *legend_topTagEffPt = new TLegend(0.75,0.8,0.9,0.9);
  legend_topTagEffPt->AddEntry((TObject*)0 ,"No Grooming Techniques","");
  legend_topTagEffPt->AddEntry((TObject*)0 ,"No B-tagging","");
  legend_topTagEffPt->SetFillColor(kWhite);
  legend_topTagEffPt->Draw("Same");
                                                                                                                                           
  TCanvas* c2 = new TCanvas("canvas2");                  
  hist_SMttbar_noBtag_topTagEffNpv->Draw("E");
  hist_SMttbar_noBtag_topTagEffNpv->SetMaximum(0.75);
  hist_SMttbar_noBtag_topTagEffNpv->SetMinimum(0.0); 

  fit_topTagEffNpv->Draw("Same");    
  fit_topTagEffNpv->SetLineColor(1);
  fit_topTagEffNpv->SetLineWidth(2);

  hist_SMttbar_noBtag_topTagEffNpv_400->Draw("ESAME");                                                                                                                                                       
  hist_SMttbar_noBtag_topTagEffNpv_400->SetMaximum(0.75);                                                                                                                                                     
  hist_SMttbar_noBtag_topTagEffNpv_400->SetLineColor(kMagenta+1);                                                                                                                                          
  
  fit_topTagEffNpv_400->Draw("Same");
  fit_topTagEffNpv_400->SetLineColor(kMagenta+1);
  fit_topTagEffNpv_400->SetLineWidth(2);
  
  hist_SMttbar_noBtag_topTagEffNpv_500->Draw("ESAME");
  hist_SMttbar_noBtag_topTagEffNpv_500->SetMaximum(0.75);
  hist_SMttbar_noBtag_topTagEffNpv_500->SetLineColor(kBlue);
  
  fit_topTagEffNpv_500->Draw("Same");
  fit_topTagEffNpv_500->SetLineColor(kBlue);
  fit_topTagEffNpv_500->SetLineWidth(2);
  
  hist_SMttbar_noBtag_topTagEffNpv_600->Draw("ESAME");                                                                                                                                                        
  hist_SMttbar_noBtag_topTagEffNpv_600->SetMaximum(0.75);                                                                                                                                                    
  hist_SMttbar_noBtag_topTagEffNpv_600->SetLineColor(kCyan+1);                                                                                                                                                          
  fit_topTagEffNpv_600->Draw("Same");
  fit_topTagEffNpv_600->SetLineColor(kCyan+1);
  fit_topTagEffNpv_600->SetLineWidth(2);

  hist_SMttbar_noBtag_topTagEffNpv_700->Draw("ESAME");                                                                                                                                                        
  hist_SMttbar_noBtag_topTagEffNpv_700->SetMaximum(0.75);                                                                                                                                                     
  hist_SMttbar_noBtag_topTagEffNpv_700->SetLineColor(kGreen+2);                                                                                                                                                         
  fit_topTagEffNpv_700->Draw("Same");
  fit_topTagEffNpv_700->SetLineColor(kGreen+2);
  fit_topTagEffNpv_700->SetLineWidth(2);

  //legend                                                                                                                                                                                             
  TLegend *legend_topTagEffNpv = new TLegend(0.7,0.7,0.9,0.9);
  legend_topTagEffNpv->AddEntry((TObject*)0 ,"No Grooming Techniques","");
  legend_topTagEffNpv->AddEntry((TObject*)0 ,"No B-tagging","");
  legend_topTagEffNpv->AddEntry(hist_SMttbar_noBtag_topTagEffNpv,"No Pt Cut","LPE");
  legend_topTagEffNpv->AddEntry(hist_SMttbar_noBtag_topTagEffNpv_400,"Pt > 400 GeV","LPE");
  legend_topTagEffNpv->AddEntry(hist_SMttbar_noBtag_topTagEffNpv_500,"Pt > 500 GeV","LPE");
  legend_topTagEffNpv->AddEntry(hist_SMttbar_noBtag_topTagEffNpv_600,"Pt > 600 GeV","LPE");
  legend_topTagEffNpv->AddEntry(hist_SMttbar_noBtag_topTagEffNpv_700,"Pt > 700 GeV","LPE");
  legend_topTagEffNpv->SetFillColor(kWhite); 
  legend_topTagEffNpv->Draw("Same"); 

  TCanvas* c_massCompare = new TCanvas("Mass Compare");
  hist_SMttbar_noBtag_pruned_AK8jetMass->Draw();
  hist_SMttbar_noBtag_filtered_AK8jetMass->Draw("SAME");
  hist_SMttbar_noBtag_trimmed_AK8jetMass->Draw("SAME");
  hist_SMttbar_noBtag_AK8jetMass->Draw("SAME");
  hist_SMttbar_noBtag_trimmed_AK8jetMass->SetLineColor(4);
  hist_SMttbar_noBtag_pruned_AK8jetMass->SetLineColor(3);
  hist_SMttbar_noBtag_filtered_AK8jetMass->SetLineColor(2);
  hist_SMttbar_noBtag_filtered_AK8jetMass->GetYaxis()->SetTitleOffset(1.5);

  //legend                                                                                                                                                                                               
  TLegend *legend_massCompare = new TLegend(0.65,0.7,0.9,0.9);
  legend_massCompare->AddEntry((TObject*)0 ,"AK8 Jet pt > 400 GeV","");
  legend_massCompare->AddEntry(hist_SMttbar_noBtag_AK8jetMass,"No Grooming Techniques","L");
  legend_massCompare->AddEntry(hist_SMttbar_noBtag_filtered_AK8jetMass,"Filtered Mass","L");
  legend_massCompare->AddEntry(hist_SMttbar_noBtag_pruned_AK8jetMass,"Pruned Mass","L");
  legend_massCompare->AddEntry(hist_SMttbar_noBtag_trimmed_AK8jetMass,"Trimmed Mass","L");
  legend_massCompare->SetFillColor(kWhite);
  legend_massCompare->Draw("Same");

  c1->SaveAs("topTagEfficiencyPt_SMttbar_13TeV_noBtag.pdf");
  c2->SaveAs("topTagEfficiencyNpv_SMttbar_13TeV_noBtag.pdf");
  c_massCompare->SaveAs("AK8jetMassCompare_SMttbar_13TeV_noBtag.pdf");

  /////////////////////////////////
  //// AK8 Filtered Jets
  /////////////////////////////////

  //efficiency histograms                                                                                                                                                                            
  hist_SMttbar_noBtag_filtered_jet1pt->Add(hist_SMttbar_noBtag_filtered_jet2pt);                                                                                                                                                   
  hist_SMttbar_noBtag_filtered_tagJet1pt->Add(hist_SMttbar_noBtag_filtered_tagJet2pt);                                                                                                                                             
  //hist_SMttbar_noBtag_filtered_tagJet1pt->Divide(hist_SMttbar_noBtag_filtered_jet1pt);                                                                                                                                           
  hist_SMttbar_noBtag_filtered_topTagEffPt->Divide(hist_SMttbar_noBtag_filtered_tagJet1pt,hist_SMttbar_noBtag_filtered_jet1pt,1,1,"B");                                                                                                                                                                                                                                                                                                              
  hist_SMttbar_noBtag_filtered_npv1->Add(hist_SMttbar_noBtag_filtered_npv2);                                                                                                                                                        
  hist_SMttbar_noBtag_filtered_tagNpv1->Add(hist_SMttbar_noBtag_filtered_tagNpv2);                                                                                                                                                  
  hist_SMttbar_noBtag_filtered_topTagEffNpv->Divide(hist_SMttbar_noBtag_filtered_tagNpv1,hist_SMttbar_noBtag_filtered_npv1,1,1,"B");                                                                                                                                                      
  hist_SMttbar_noBtag_filtered_npv1_400->Add(hist_SMttbar_noBtag_filtered_npv2_400); 
  hist_SMttbar_noBtag_filtered_tagNpv1_400->Add(hist_SMttbar_noBtag_filtered_tagNpv2_400);
  hist_SMttbar_noBtag_filtered_topTagEffNpv_400->Divide(hist_SMttbar_noBtag_filtered_tagNpv1_400,hist_SMttbar_noBtag_filtered_npv1_400,1,1,"B");                                                                                                                                 
  hist_SMttbar_noBtag_filtered_npv1_500->Add(hist_SMttbar_noBtag_filtered_npv2_500);      
  hist_SMttbar_noBtag_filtered_tagNpv1_500->Add(hist_SMttbar_noBtag_filtered_tagNpv2_500);
  hist_SMttbar_noBtag_filtered_topTagEffNpv_500->Divide(hist_SMttbar_noBtag_filtered_tagNpv1_500,hist_SMttbar_noBtag_filtered_npv1_500,1,1,"B");                                                                                                                                 
  hist_SMttbar_noBtag_filtered_npv1_600->Add(hist_SMttbar_noBtag_filtered_npv2_600);      
  hist_SMttbar_noBtag_filtered_tagNpv1_600->Add(hist_SMttbar_noBtag_filtered_tagNpv2_600);
  hist_SMttbar_noBtag_filtered_topTagEffNpv_600->Divide(hist_SMttbar_noBtag_filtered_tagNpv1_600,hist_SMttbar_noBtag_filtered_npv1_600,1,1,"B");                                                                                                                                 
  hist_SMttbar_noBtag_filtered_npv1_700->Add(hist_SMttbar_noBtag_filtered_npv2_700);      
  hist_SMttbar_noBtag_filtered_tagNpv1_700->Add(hist_SMttbar_noBtag_filtered_tagNpv2_700);
  hist_SMttbar_noBtag_filtered_topTagEffNpv_700->Divide(hist_SMttbar_noBtag_filtered_tagNpv1_700,hist_SMttbar_noBtag_filtered_npv1_700,1,1,"B");                                                                                                                                
  //fit functions
  TF1 *fit_filtered_topTagEffNpv = new TF1("fit_filtered_topTagEffNpv","[0]*x + [1]",0.,60.);
  fit_filtered_topTagEffNpv->SetParameters(-0.0011,0.388);
  fit_filtered_topTagEffNpv->SetParNames("No pt cut: slope","No pt cut: y intercept");
  hist_SMttbar_noBtag_filtered_topTagEffNpv->Fit("fit_filtered_topTagEffNpv","N");                             
                                                                                                                        
  TF1 *fit_filtered_topTagEffNpv_400 = new TF1("fit_filtered_topTagEffNpv_400","[0]*x + [1]",0.,60.);
  fit_filtered_topTagEffNpv_400->SetParameters(-0.0015,0.43);
  fit_filtered_topTagEffNpv_400->SetParNames("pt > 400: slope","pt > 400: y intercept");    
  hist_SMttbar_noBtag_filtered_topTagEffNpv_400->Fit("fit_filtered_topTagEffNpv_400","N");                                                                                                                                                
  TF1 *fit_filtered_topTagEffNpv_500 = new TF1("fit_filtered_topTagEffNpv_500","[0]*x + [1]",0.,60.);
  fit_filtered_topTagEffNpv_500->SetParameters(-0.002,0.445);
  fit_filtered_topTagEffNpv_500->SetParNames("pt > 500: slope","pt > 500: y intercept");    
  hist_SMttbar_noBtag_filtered_topTagEffNpv_500->Fit("fit_filtered_topTagEffNpv_500","N");                          
                                                                                                                                                                                                 
  TF1 *fit_filtered_topTagEffNpv_600 = new TF1("fit_filtered_topTagEffNpv_600","[0]*x + [1]",0.,60.);
  fit_filtered_topTagEffNpv_600->SetParameters(-0.0025,0.446);
  fit_filtered_topTagEffNpv_600->SetParNames("pt > 600: slope","pt > 600: y intercept");    
  hist_SMttbar_noBtag_filtered_topTagEffNpv_600->Fit("fit_filtered_topTagEffNpv_600","N");                          

  TF1 *fit_filtered_topTagEffNpv_700 = new TF1("fit_filtered_topTagEffNpv_700","[0]*x + [1]",0.,60.);
  fit_filtered_topTagEffNpv_700->SetParameters(-0.0029,0.438);
  fit_filtered_topTagEffNpv_700->SetParNames("pt > 700: slope","pt > 700: y intercept");
  hist_SMttbar_noBtag_filtered_topTagEffNpv_700->Fit("fit_filtered_topTagEffNpv_700","N");

  TCanvas* c1_filtered = new TCanvas("canvas1");
  //c1_filtered->Draw();
  //c1_filtered->Update();
  hist_SMttbar_noBtag_filtered_topTagEffPt->Draw("E");      
  hist_SMttbar_noBtag_filtered_topTagEffPt->SetMaximum(1.1);                                                                                                                                                                   
  //legend                                                                                                                                                                                                 
  TLegend *legend_filtered_topTagEffPt = new TLegend(0.75,0.8,0.9,0.9);
  legend_filtered_topTagEffPt->AddEntry((TObject*)0 ,"Filtered Mass Jets","");
  legend_filtered_topTagEffPt->AddEntry((TObject*)0 ,"No B-tagging","");
  legend_filtered_topTagEffPt->SetFillColor(kWhite);
  legend_filtered_topTagEffPt->Draw("Same");
                                                     
  TCanvas* c2_filtered = new TCanvas("canvas2");
  hist_SMttbar_noBtag_filtered_topTagEffNpv->Draw("E");
  hist_SMttbar_noBtag_filtered_topTagEffNpv->SetMaximum(0.75);
  hist_SMttbar_noBtag_filtered_topTagEffNpv->SetMinimum(0.0); 

  fit_filtered_topTagEffNpv->Draw("Same");    
  fit_filtered_topTagEffNpv->SetLineColor(1);
  fit_filtered_topTagEffNpv->SetLineWidth(2);

  hist_SMttbar_noBtag_filtered_topTagEffNpv_400->Draw("ESAME");                                                                                                                                                    
  hist_SMttbar_noBtag_filtered_topTagEffNpv_400->SetMaximum(0.75);                                                                                                                                                  
  hist_SMttbar_noBtag_filtered_topTagEffNpv_400->SetLineColor(kMagenta+1);                                                                                                                                          
  
  fit_filtered_topTagEffNpv_400->Draw("Same");
  fit_filtered_topTagEffNpv_400->SetLineColor(kMagenta+1);
  fit_filtered_topTagEffNpv_400->SetLineWidth(2);
  
  hist_SMttbar_noBtag_filtered_topTagEffNpv_500->Draw("ESAME");
  hist_SMttbar_noBtag_filtered_topTagEffNpv_500->SetMaximum(0.75);
  hist_SMttbar_noBtag_filtered_topTagEffNpv_500->SetLineColor(kBlue);
  
  fit_filtered_topTagEffNpv_500->Draw("Same");
  fit_filtered_topTagEffNpv_500->SetLineColor(kBlue);
  fit_filtered_topTagEffNpv_500->SetLineWidth(2);
  
  hist_SMttbar_noBtag_filtered_topTagEffNpv_600->Draw("ESAME");                                                                                                                                                      
  hist_SMttbar_noBtag_filtered_topTagEffNpv_600->SetMaximum(0.75);                                                                                                                                                  
  hist_SMttbar_noBtag_filtered_topTagEffNpv_600->SetLineColor(kCyan+1);                                                                                                                                                          
  fit_filtered_topTagEffNpv_600->Draw("Same");
  fit_filtered_topTagEffNpv_600->SetLineColor(kCyan+1);
  fit_filtered_topTagEffNpv_600->SetLineWidth(2);

  hist_SMttbar_noBtag_filtered_topTagEffNpv_700->Draw("ESAME");                                                                                                                                                     
  hist_SMttbar_noBtag_filtered_topTagEffNpv_700->SetMaximum(0.75);                                                                                                                                                   
  hist_SMttbar_noBtag_filtered_topTagEffNpv_700->SetLineColor(kGreen+2);                                                                                                                                                         
  fit_filtered_topTagEffNpv_700->Draw("Same");
  fit_filtered_topTagEffNpv_700->SetLineColor(kGreen+2);
  fit_filtered_topTagEffNpv_700->SetLineWidth(2);

  //legend                                                                                                                                                                                           
  TLegend *legend_filtered_topTagEffNpv = new TLegend(0.7,0.7,0.9,0.9);
  legend_filtered_topTagEffNpv->AddEntry((TObject*)0 ,"Filtered Mass Jets","");
  legend_filtered_topTagEffNpv->AddEntry((TObject*)0 ,"No B-tagging","");
  legend_filtered_topTagEffNpv->AddEntry(hist_SMttbar_noBtag_filtered_topTagEffNpv,"No Pt Cut","LPE");
  legend_filtered_topTagEffNpv->AddEntry(hist_SMttbar_noBtag_filtered_topTagEffNpv_400,"Pt > 400 GeV","LPE");
  legend_filtered_topTagEffNpv->AddEntry(hist_SMttbar_noBtag_filtered_topTagEffNpv_500,"Pt > 500 GeV","LPE");
  legend_filtered_topTagEffNpv->AddEntry(hist_SMttbar_noBtag_filtered_topTagEffNpv_600,"Pt > 600 GeV","LPE");
  legend_filtered_topTagEffNpv->AddEntry(hist_SMttbar_noBtag_filtered_topTagEffNpv_700,"Pt > 700 GeV","LPE");
  legend_filtered_topTagEffNpv->SetFillColor(kWhite); 
  legend_filtered_topTagEffNpv->Draw("Same"); 

  c1_filtered->SaveAs("topTagEfficiencyPt_filtered_SMttbar_13TeV_noBtag.pdf");
  c2_filtered->SaveAs("topTagEfficiencyNpv_filtered_SMttbar_13TeV_noBtag.pdf");

  /////////////////////////////////
  //// AK8 Pruned Jets
  /////////////////////////////////

  //efficiency histograms                                                                                                                                                                            
  hist_SMttbar_noBtag_pruned_jet1pt->Add(hist_SMttbar_noBtag_pruned_jet2pt);                                                                                                                                                   
  hist_SMttbar_noBtag_pruned_tagJet1pt->Add(hist_SMttbar_noBtag_pruned_tagJet2pt);                                                                                                                                             
  //hist_SMttbar_noBtag_pruned_tagJet1pt->Divide(hist_SMttbar_noBtag_pruned_jet1pt);                                                                                                                                           
  hist_SMttbar_noBtag_pruned_topTagEffPt->Divide(hist_SMttbar_noBtag_pruned_tagJet1pt,hist_SMttbar_noBtag_pruned_jet1pt,1,1,"B");                                                                                                                                                                                                                                                                                                              
  hist_SMttbar_noBtag_pruned_npv1->Add(hist_SMttbar_noBtag_pruned_npv2);                                                                                                                                                        
  hist_SMttbar_noBtag_pruned_tagNpv1->Add(hist_SMttbar_noBtag_pruned_tagNpv2);                                                                                                                                                  
  hist_SMttbar_noBtag_pruned_topTagEffNpv->Divide(hist_SMttbar_noBtag_pruned_tagNpv1,hist_SMttbar_noBtag_pruned_npv1,1,1,"B");                                                                                                                                                      
  hist_SMttbar_noBtag_pruned_npv1_400->Add(hist_SMttbar_noBtag_pruned_npv2_400); 
  hist_SMttbar_noBtag_pruned_tagNpv1_400->Add(hist_SMttbar_noBtag_pruned_tagNpv2_400);
  hist_SMttbar_noBtag_pruned_topTagEffNpv_400->Divide(hist_SMttbar_noBtag_pruned_tagNpv1_400,hist_SMttbar_noBtag_pruned_npv1_400,1,1,"B");                                                                                                                                 
  hist_SMttbar_noBtag_pruned_npv1_500->Add(hist_SMttbar_noBtag_pruned_npv2_500);      
  hist_SMttbar_noBtag_pruned_tagNpv1_500->Add(hist_SMttbar_noBtag_pruned_tagNpv2_500);
  hist_SMttbar_noBtag_pruned_topTagEffNpv_500->Divide(hist_SMttbar_noBtag_pruned_tagNpv1_500,hist_SMttbar_noBtag_pruned_npv1_500,1,1,"B");                                                                                                                                 
  hist_SMttbar_noBtag_pruned_npv1_600->Add(hist_SMttbar_noBtag_pruned_npv2_600);      
  hist_SMttbar_noBtag_pruned_tagNpv1_600->Add(hist_SMttbar_noBtag_pruned_tagNpv2_600);
  hist_SMttbar_noBtag_pruned_topTagEffNpv_600->Divide(hist_SMttbar_noBtag_pruned_tagNpv1_600,hist_SMttbar_noBtag_pruned_npv1_600,1,1,"B");                                                                                                                                 
  hist_SMttbar_noBtag_pruned_npv1_700->Add(hist_SMttbar_noBtag_pruned_npv2_700);      
  hist_SMttbar_noBtag_pruned_tagNpv1_700->Add(hist_SMttbar_noBtag_pruned_tagNpv2_700);
  hist_SMttbar_noBtag_pruned_topTagEffNpv_700->Divide(hist_SMttbar_noBtag_pruned_tagNpv1_700,hist_SMttbar_noBtag_pruned_npv1_700,1,1,"B");                                                                                                                                
  //fit functions
  TF1 *fit_pruned_topTagEffNpv = new TF1("fit_pruned_topTagEffNpv","[0]*x + [1]",0.,60.);
  fit_pruned_topTagEffNpv->SetParameters(-0.0011,0.388);
  fit_pruned_topTagEffNpv->SetParNames("No pt cut: slope","No pt cut: y intercept");
  hist_SMttbar_noBtag_pruned_topTagEffNpv->Fit("fit_pruned_topTagEffNpv","N");                             
                                                                                                                        
  TF1 *fit_pruned_topTagEffNpv_400 = new TF1("fit_pruned_topTagEffNpv_400","[0]*x + [1]",0.,60.);
  fit_pruned_topTagEffNpv_400->SetParameters(-0.0015,0.43);
  fit_pruned_topTagEffNpv_400->SetParNames("pt > 400: slope","pt > 400: y intercept");    
  hist_SMttbar_noBtag_pruned_topTagEffNpv_400->Fit("fit_pruned_topTagEffNpv_400","N");                                                                                                                                                
  TF1 *fit_pruned_topTagEffNpv_500 = new TF1("fit_pruned_topTagEffNpv_500","[0]*x + [1]",0.,60.);
  fit_pruned_topTagEffNpv_500->SetParameters(-0.002,0.445);
  fit_pruned_topTagEffNpv_500->SetParNames("pt > 500: slope","pt > 500: y intercept");    
  hist_SMttbar_noBtag_pruned_topTagEffNpv_500->Fit("fit_pruned_topTagEffNpv_500","N");                          
                                                                                                                                                                                                 
  TF1 *fit_pruned_topTagEffNpv_600 = new TF1("fit_pruned_topTagEffNpv_600","[0]*x + [1]",0.,60.);
  fit_pruned_topTagEffNpv_600->SetParameters(-0.0025,0.446);
  fit_pruned_topTagEffNpv_600->SetParNames("pt > 600: slope","pt > 600: y intercept");    
  hist_SMttbar_noBtag_pruned_topTagEffNpv_600->Fit("fit_pruned_topTagEffNpv_600","N");                          

  TF1 *fit_pruned_topTagEffNpv_700 = new TF1("fit_pruned_topTagEffNpv_700","[0]*x + [1]",0.,60.);
  fit_pruned_topTagEffNpv_700->SetParameters(-0.0029,0.438);
  fit_pruned_topTagEffNpv_700->SetParNames("pt > 700: slope","pt > 700: y intercept");
  hist_SMttbar_noBtag_pruned_topTagEffNpv_700->Fit("fit_pruned_topTagEffNpv_700","N");

  TCanvas* c1_pruned = new TCanvas("canvas1");
  //c1_pruned->Draw();
  //c1_pruned->Update();
  hist_SMttbar_noBtag_pruned_topTagEffPt->Draw("E");      
  hist_SMttbar_noBtag_pruned_topTagEffPt->SetMaximum(1.1);                                                                                                                                                                   
  //legend
  TLegend *legend_pruned_topTagEffPt = new TLegend(0.75,0.8,0.9,0.9);
  legend_pruned_topTagEffPt->AddEntry((TObject*)0 ,"Pruned Mass Jets","");
  legend_pruned_topTagEffPt->AddEntry((TObject*)0 ,"No B-tagging","");
  legend_pruned_topTagEffPt->SetFillColor(kWhite);
  legend_pruned_topTagEffPt->Draw("Same");
                                                                                                                                                                                         
  TCanvas* c2_pruned = new TCanvas("canvas2");
  hist_SMttbar_noBtag_pruned_topTagEffNpv->Draw("E");
  hist_SMttbar_noBtag_pruned_topTagEffNpv->SetMaximum(0.75);
  hist_SMttbar_noBtag_pruned_topTagEffNpv->SetMinimum(0.0); 

  fit_pruned_topTagEffNpv->Draw("Same");    
  fit_pruned_topTagEffNpv->SetLineColor(1);
  fit_pruned_topTagEffNpv->SetLineWidth(2);

  hist_SMttbar_noBtag_pruned_topTagEffNpv_400->Draw("ESAME");                                                                                                                                                    
  hist_SMttbar_noBtag_pruned_topTagEffNpv_400->SetMaximum(0.75);                                                                                                                                                  
  hist_SMttbar_noBtag_pruned_topTagEffNpv_400->SetLineColor(kMagenta+1);                                                                                                                                          
  
  fit_pruned_topTagEffNpv_400->Draw("Same");
  fit_pruned_topTagEffNpv_400->SetLineColor(kMagenta+1);
  fit_pruned_topTagEffNpv_400->SetLineWidth(2);
  
  hist_SMttbar_noBtag_pruned_topTagEffNpv_500->Draw("ESAME");
  hist_SMttbar_noBtag_pruned_topTagEffNpv_500->SetMaximum(0.75);
  hist_SMttbar_noBtag_pruned_topTagEffNpv_500->SetLineColor(kBlue);
  
  fit_pruned_topTagEffNpv_500->Draw("Same");
  fit_pruned_topTagEffNpv_500->SetLineColor(kBlue);
  fit_pruned_topTagEffNpv_500->SetLineWidth(2);
  
  hist_SMttbar_noBtag_pruned_topTagEffNpv_600->Draw("ESAME");                                                                                                                                                      
  hist_SMttbar_noBtag_pruned_topTagEffNpv_600->SetMaximum(0.75);                                                                                                                                                  
  hist_SMttbar_noBtag_pruned_topTagEffNpv_600->SetLineColor(kCyan+1);                                                                                                                                                          
  fit_pruned_topTagEffNpv_600->Draw("Same");
  fit_pruned_topTagEffNpv_600->SetLineColor(kCyan+1);
  fit_pruned_topTagEffNpv_600->SetLineWidth(2);

  hist_SMttbar_noBtag_pruned_topTagEffNpv_700->Draw("ESAME");                                                                                                                                                     
  hist_SMttbar_noBtag_pruned_topTagEffNpv_700->SetMaximum(0.75);                                                                                                                                                   
  hist_SMttbar_noBtag_pruned_topTagEffNpv_700->SetLineColor(kGreen+2);                                                                                                                                                         
  fit_pruned_topTagEffNpv_700->Draw("Same");
  fit_pruned_topTagEffNpv_700->SetLineColor(kGreen+2);
  fit_pruned_topTagEffNpv_700->SetLineWidth(2);

  //legend                                                                                                                                                                                           
  TLegend *legend_pruned_topTagEffNpv = new TLegend(0.7,0.7,0.9,0.9);
  legend_pruned_topTagEffNpv->AddEntry((TObject*)0 ,"Pruned Mass Jets","");
  legend_pruned_topTagEffNpv->AddEntry((TObject*)0 ,"No B-tagging","");
  legend_pruned_topTagEffNpv->AddEntry(hist_SMttbar_noBtag_pruned_topTagEffNpv,"No Pt Cut","LPE");
  legend_pruned_topTagEffNpv->AddEntry(hist_SMttbar_noBtag_pruned_topTagEffNpv_400,"Pt > 400 GeV","LPE");
  legend_pruned_topTagEffNpv->AddEntry(hist_SMttbar_noBtag_pruned_topTagEffNpv_500,"Pt > 500 GeV","LPE");
  legend_pruned_topTagEffNpv->AddEntry(hist_SMttbar_noBtag_pruned_topTagEffNpv_600,"Pt > 600 GeV","LPE"); 
  legend_pruned_topTagEffNpv->AddEntry(hist_SMttbar_noBtag_pruned_topTagEffNpv_700,"Pt > 700 GeV","LPE");
  legend_pruned_topTagEffNpv->SetFillColor(kWhite); 
  legend_pruned_topTagEffNpv->Draw("Same"); 

  c1_pruned->SaveAs("topTagEfficiencyPt_pruned_SMttbar_13TeV_noBtag.pdf");
  c2_pruned->SaveAs("topTagEfficiencyNpv_pruned_SMttbar_13TeV_noBtag.pdf");

  /////////////////////////////////
  //// AK8 Trimmed Jets
  /////////////////////////////////

  //efficiency histograms                                                                                                                                                                            
  hist_SMttbar_noBtag_trimmed_jet1pt->Add(hist_SMttbar_noBtag_trimmed_jet2pt);                                                                                                                                                   
  hist_SMttbar_noBtag_trimmed_tagJet1pt->Add(hist_SMttbar_noBtag_trimmed_tagJet2pt);                                                                                                                                             
  //hist_SMttbar_noBtag_trimmed_tagJet1pt->Divide(hist_SMttbar_noBtag_trimmed_jet1pt);                                                                                                                                           
  hist_SMttbar_noBtag_trimmed_topTagEffPt->Divide(hist_SMttbar_noBtag_trimmed_tagJet1pt,hist_SMttbar_noBtag_trimmed_jet1pt,1,1,"B");                                                                                                                                                                                                                                                                                                              
  hist_SMttbar_noBtag_trimmed_npv1->Add(hist_SMttbar_noBtag_trimmed_npv2);                                                                                                                                                        
  hist_SMttbar_noBtag_trimmed_tagNpv1->Add(hist_SMttbar_noBtag_trimmed_tagNpv2);                                                                                                                                                  
  hist_SMttbar_noBtag_trimmed_topTagEffNpv->Divide(hist_SMttbar_noBtag_trimmed_tagNpv1,hist_SMttbar_noBtag_trimmed_npv1,1,1,"B");                                                                                                                                                      
  hist_SMttbar_noBtag_trimmed_npv1_400->Add(hist_SMttbar_noBtag_trimmed_npv2_400); 
  hist_SMttbar_noBtag_trimmed_tagNpv1_400->Add(hist_SMttbar_noBtag_trimmed_tagNpv2_400);
  hist_SMttbar_noBtag_trimmed_topTagEffNpv_400->Divide(hist_SMttbar_noBtag_trimmed_tagNpv1_400,hist_SMttbar_noBtag_trimmed_npv1_400,1,1,"B");                                                                                                                                 
  hist_SMttbar_noBtag_trimmed_npv1_500->Add(hist_SMttbar_noBtag_trimmed_npv2_500);      
  hist_SMttbar_noBtag_trimmed_tagNpv1_500->Add(hist_SMttbar_noBtag_trimmed_tagNpv2_500);
  hist_SMttbar_noBtag_trimmed_topTagEffNpv_500->Divide(hist_SMttbar_noBtag_trimmed_tagNpv1_500,hist_SMttbar_noBtag_trimmed_npv1_500,1,1,"B");                                                                                                                                 
  hist_SMttbar_noBtag_trimmed_npv1_600->Add(hist_SMttbar_noBtag_trimmed_npv2_600);      
  hist_SMttbar_noBtag_trimmed_tagNpv1_600->Add(hist_SMttbar_noBtag_trimmed_tagNpv2_600);
  hist_SMttbar_noBtag_trimmed_topTagEffNpv_600->Divide(hist_SMttbar_noBtag_trimmed_tagNpv1_600,hist_SMttbar_noBtag_trimmed_npv1_600,1,1,"B");                                                                                                                                 
  hist_SMttbar_noBtag_trimmed_npv1_700->Add(hist_SMttbar_noBtag_trimmed_npv2_700);      
  hist_SMttbar_noBtag_trimmed_tagNpv1_700->Add(hist_SMttbar_noBtag_trimmed_tagNpv2_700);
  hist_SMttbar_noBtag_trimmed_topTagEffNpv_700->Divide(hist_SMttbar_noBtag_trimmed_tagNpv1_700,hist_SMttbar_noBtag_trimmed_npv1_700,1,1,"B");                                                                                                                                
  //fit functions
  TF1 *fit_trimmed_topTagEffNpv = new TF1("fit_trimmed_topTagEffNpv","[0]*x + [1]",0.,60.);
  fit_trimmed_topTagEffNpv->SetParameters(-0.0011,0.388);
  fit_trimmed_topTagEffNpv->SetParNames("No pt cut: slope","No pt cut: y intercept");
  hist_SMttbar_noBtag_trimmed_topTagEffNpv->Fit("fit_trimmed_topTagEffNpv","N");                             
                                                                                                                        
  TF1 *fit_trimmed_topTagEffNpv_400 = new TF1("fit_trimmed_topTagEffNpv_400","[0]*x + [1]",0.,60.);
  fit_trimmed_topTagEffNpv_400->SetParameters(-0.0015,0.43);
  fit_trimmed_topTagEffNpv_400->SetParNames("pt > 400: slope","pt > 400: y intercept");    
  hist_SMttbar_noBtag_trimmed_topTagEffNpv_400->Fit("fit_trimmed_topTagEffNpv_400","N");                                                                                                                                                
  TF1 *fit_trimmed_topTagEffNpv_500 = new TF1("fit_trimmed_topTagEffNpv_500","[0]*x + [1]",0.,60.);
  fit_trimmed_topTagEffNpv_500->SetParameters(-0.002,0.445);
  fit_trimmed_topTagEffNpv_500->SetParNames("pt > 500: slope","pt > 500: y intercept");    
  hist_SMttbar_noBtag_trimmed_topTagEffNpv_500->Fit("fit_trimmed_topTagEffNpv_500","N");                          
                                                                                                                                                       
  TF1 *fit_trimmed_topTagEffNpv_600 = new TF1("fit_trimmed_topTagEffNpv_600","[0]*x + [1]",0.,60.);
  fit_trimmed_topTagEffNpv_600->SetParameters(-0.0025,0.446);
  fit_trimmed_topTagEffNpv_600->SetParNames("pt > 600: slope","pt > 600: y intercept");    
  hist_SMttbar_noBtag_trimmed_topTagEffNpv_600->Fit("fit_trimmed_topTagEffNpv_600","N");                          

  TF1 *fit_trimmed_topTagEffNpv_700 = new TF1("fit_trimmed_topTagEffNpv_700","[0]*x + [1]",0.,60.);
  fit_trimmed_topTagEffNpv_700->SetParameters(-0.0029,0.438);
  fit_trimmed_topTagEffNpv_700->SetParNames("pt > 700: slope","pt > 700: y intercept");
  hist_SMttbar_noBtag_trimmed_topTagEffNpv_700->Fit("fit_trimmed_topTagEffNpv_700","N");

  TCanvas* c1_trimmed = new TCanvas("canvas1");
  //c1_trimmed->Draw();
  //c1_trimmed->Update();
  hist_SMttbar_noBtag_trimmed_topTagEffPt->Draw("E");      
  hist_SMttbar_noBtag_trimmed_topTagEffPt->SetMaximum(1.1);                                                                                                                                                                   
  //legend
  TLegend *legend_trimmed_topTagEffPt = new TLegend(0.75,0.8,0.9,0.9);
  legend_trimmed_topTagEffPt->AddEntry((TObject*)0 ,"Trimmed Mass Jets","");
  legend_trimmed_topTagEffPt->AddEntry((TObject*)0 ,"No B-tagging","");
  legend_trimmed_topTagEffPt->SetFillColor(kWhite);
  legend_trimmed_topTagEffPt->Draw("Same");
                                                                                                                                                                                         
  TCanvas* c2_trimmed = new TCanvas("canvas2");
  hist_SMttbar_noBtag_trimmed_topTagEffNpv->Draw("E");
  hist_SMttbar_noBtag_trimmed_topTagEffNpv->SetMaximum(0.75);
  hist_SMttbar_noBtag_trimmed_topTagEffNpv->SetMinimum(0.0); 

  fit_trimmed_topTagEffNpv->Draw("Same");    
  fit_trimmed_topTagEffNpv->SetLineColor(1);
  fit_trimmed_topTagEffNpv->SetLineWidth(2);

  hist_SMttbar_noBtag_trimmed_topTagEffNpv_400->Draw("ESAME");                                                                                                                                                    
  hist_SMttbar_noBtag_trimmed_topTagEffNpv_400->SetMaximum(0.75);                                                                                                                                                  
  hist_SMttbar_noBtag_trimmed_topTagEffNpv_400->SetLineColor(kMagenta+1);                                                                                                                                          
  
  fit_trimmed_topTagEffNpv_400->Draw("Same");
  fit_trimmed_topTagEffNpv_400->SetLineColor(kMagenta+1);
  fit_trimmed_topTagEffNpv_400->SetLineWidth(2);
  
  hist_SMttbar_noBtag_trimmed_topTagEffNpv_500->Draw("ESAME");
  hist_SMttbar_noBtag_trimmed_topTagEffNpv_500->SetMaximum(0.75);
  hist_SMttbar_noBtag_trimmed_topTagEffNpv_500->SetLineColor(kBlue);
  
  fit_trimmed_topTagEffNpv_500->Draw("Same");
  fit_trimmed_topTagEffNpv_500->SetLineColor(kBlue);
  fit_trimmed_topTagEffNpv_500->SetLineWidth(2);
  
  hist_SMttbar_noBtag_trimmed_topTagEffNpv_600->Draw("ESAME");                                                                                                                                                      
  hist_SMttbar_noBtag_trimmed_topTagEffNpv_600->SetMaximum(0.75);                                                                                                                                                  
  hist_SMttbar_noBtag_trimmed_topTagEffNpv_600->SetLineColor(kCyan+1);                                                                                                                                                          
  fit_trimmed_topTagEffNpv_600->Draw("Same");
  fit_trimmed_topTagEffNpv_600->SetLineColor(kCyan+1);
  fit_trimmed_topTagEffNpv_600->SetLineWidth(2);

  hist_SMttbar_noBtag_trimmed_topTagEffNpv_700->Draw("ESAME");                                                                                                                                                     
  hist_SMttbar_noBtag_trimmed_topTagEffNpv_700->SetMaximum(0.75);                                                                                                                                                   
  hist_SMttbar_noBtag_trimmed_topTagEffNpv_700->SetLineColor(kGreen+2);                                                                                                                                                         
  fit_trimmed_topTagEffNpv_700->Draw("Same");
  fit_trimmed_topTagEffNpv_700->SetLineColor(kGreen+2);
  fit_trimmed_topTagEffNpv_700->SetLineWidth(2);

  //legend                                                                                                                                                                                           
  TLegend *legend_trimmed_topTagEffNpv = new TLegend(0.7,0.7,0.9,0.9);
  legend_trimmed_topTagEffNpv->AddEntry((TObject*)0 ,"Trimmed Mass Jets","");
  legend_trimmed_topTagEffNpv->AddEntry((TObject*)0 ,"No B-tagging","");
  legend_trimmed_topTagEffNpv->AddEntry(hist_SMttbar_noBtag_trimmed_topTagEffNpv,"No Pt Cut","LPE");
  legend_trimmed_topTagEffNpv->AddEntry(hist_SMttbar_noBtag_trimmed_topTagEffNpv_400,"Pt > 400 GeV","LPE");
  legend_trimmed_topTagEffNpv->AddEntry(hist_SMttbar_noBtag_trimmed_topTagEffNpv_500,"Pt > 500 GeV","LPE");
  legend_trimmed_topTagEffNpv->AddEntry(hist_SMttbar_noBtag_trimmed_topTagEffNpv_600,"Pt > 600 GeV","LPE");                                                                                                        
  legend_trimmed_topTagEffNpv->AddEntry(hist_SMttbar_noBtag_trimmed_topTagEffNpv_700,"Pt > 700 GeV","LPE");
  legend_trimmed_topTagEffNpv->SetFillColor(kWhite); 
  legend_trimmed_topTagEffNpv->Draw("Same"); 

  c1_trimmed->SaveAs("topTagEfficiencyPt_trimmed_SMttbar_13TeV_noBtag.pdf");
  c2_trimmed->SaveAs("topTagEfficiencyNpv_trimmed_SMttbar_13TeV_noBtag.pdf");

  TFile f("topTagEfficiency_SMttbar_13TeV_noBtag.root","recreate");
  hist_SMttbar_noBtag_topTagEffPt->Write();
  hist_SMttbar_noBtag_topTagEffNpv->Write();
  hist_SMttbar_noBtag_topTagEffNpv_400->Write();
  hist_SMttbar_noBtag_topTagEffNpv_500->Write();
  hist_SMttbar_noBtag_topTagEffNpv_600->Write();
  hist_SMttbar_noBtag_topTagEffNpv_700->Write();

  hist_SMttbar_noBtag_filtered_topTagEffPt->Write();
  hist_SMttbar_noBtag_filtered_topTagEffNpv->Write();
  hist_SMttbar_noBtag_filtered_topTagEffNpv_400->Write();
  hist_SMttbar_noBtag_filtered_topTagEffNpv_500->Write();
  hist_SMttbar_noBtag_filtered_topTagEffNpv_600->Write();
  hist_SMttbar_noBtag_filtered_topTagEffNpv_700->Write();

  hist_SMttbar_noBtag_pruned_topTagEffPt->Write();
  hist_SMttbar_noBtag_pruned_topTagEffNpv->Write();
  hist_SMttbar_noBtag_pruned_topTagEffNpv_400->Write();
  hist_SMttbar_noBtag_pruned_topTagEffNpv_500->Write();
  hist_SMttbar_noBtag_pruned_topTagEffNpv_600->Write();
  hist_SMttbar_noBtag_pruned_topTagEffNpv_700->Write();

  hist_SMttbar_noBtag_trimmed_topTagEffPt->Write();
  hist_SMttbar_noBtag_trimmed_topTagEffNpv->Write();
  hist_SMttbar_noBtag_trimmed_topTagEffNpv_400->Write();
  hist_SMttbar_noBtag_trimmed_topTagEffNpv_500->Write();
  hist_SMttbar_noBtag_trimmed_topTagEffNpv_600->Write();
  hist_SMttbar_noBtag_trimmed_topTagEffNpv_700->Write();

  hist_SMttbar_noBtag_jet1pt->Write();
  hist_SMttbar_noBtag_npv1->Write();
  f.Close();

  return 0;
}

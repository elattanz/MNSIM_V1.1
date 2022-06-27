#include "SetDemux.h"


SetDemux::SetDemux(int demux_num){
  Demux_InputNum = demux_num;
}

SetDemux::~SetDemux(){}

double SetDemux::Demux_Area(){
  switch(Demux_InputNum) {
    case 4 :
      return 15.4869;
    case 8 :
      return 34.2589;
    case 16 : 
      return 76.9652;
    case 32 :
      return 140.790;
    case 64 :
      return 263.2773;
    default 
      return 0; }
  }
 
double SetDemux::Demux_Latency(){
  switch(Demux_InputNum) {
    case 4 :
      return .08;
    case 8 :
      return .13;
    case 16 : 
      return .11;
    case 32 :
      return .18;
    case 64 :
      return .19;
    default 
      return 0; }
  }
  
double SetDemux::Demux_Power_Leakage(){
  switch(Demux_InputNum) {
    case 4 :
      return 27.6717e-9;
    case 8 :
      return 84.8136e-9;
    case 16 : 
      return 232.8362e-9;
    case 32 :
      return 422.1485e-9;
    case 64 :
      return 740.6179e-9;
    default 
      return 0; }
  }
  
double SetDemux::Demux_Power_Dynamic(){
  switch(Demux_InputNum) {
    case 4 :
      return 3.1805e-6;
    case 8 :
      return 6.202e-6;
    case 16 : 
      return 10.4622e-6;
    case 32 :
      return 16.6957e-6;
    case 64 :
      return 27.7357e-6;
    default 
      return 0; }
  }  
  

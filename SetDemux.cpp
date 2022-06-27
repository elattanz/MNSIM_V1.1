#include "SetDemux.h"


SetDemux::SetDemux(Technology tech, int demux_num){
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
      return 0;
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
      return 0;
  }
  

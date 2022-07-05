#include "SetMux.h"


SetMux::SetMux(){
  //Mux_InputNum = mux_num;
}

//SetMux::~SetMux(){}

double SetMux::Mux_Area(){
  switch(Mux_InputNum) 
  {
    case 4 :
      return 11.2632;
    case 8 :
      return 27.6887;
    case 16 : 
      return 132.3426;
    case 32 :
      return 276.417;
    case 64 :
      return 561.2829;
    default 
      return 0;
  }
}

double SetMux::Mux_Latency(){
  switch(Mux_InputNum)
  {
    case 4 :
      return .07;
    case 8 :
      return .14;
    case 16 : 
      return .49;
    case 32 :
      return .81;
    case 64 :
      return 1.188;
    default 
      return 0;
  }
}
  
double SetMux::Mux_Power_Leakage(){
  switch(Mux_InputNum) 
  {
    case 4 :
      return 55.6509e-9;
    case 8 :
      return 131.5937e-9;
    case 16 : 
      return 640.5314e-9;
    case 32 :
      return 1.3155e-6;
    case 64 :
      return 2.6812e-6;
    default 
      return 0;
  }
}
  
double SetMux::Mux_Power_Dynamic(){
  switch(Mux_InputNum) 
  {
    case 4 :
      return 3.3018e-6;
    case 8 :
      return 8.9763e-6;
    case 16 : 
      return 34.585e-6;
    case 32 :
      return 68.506e-6;
    case 64 :
      return 105.2228e-6;
    default 
      return 0;
  }
}

#include "SetShifter.h"

SetShifter::SetShifter(int shifter_num) {
  Shifter_InputNum = shifter_num;
}

SetShifter::~SetShifter(){}

double SetShifter::Shifter_Area() {
  switch(Shifter_InputNum) {
    case 8 :
      return 161.4392;
    case 16 : 
      return 304.1064;
    case 32 : 
      return 589.4408;
  default 
      return 0; }
}
  
 
double SetShifter::Shifter_Latency() {
  switch(Shifter_InputNum) {
    case 8 :
      return .11;
    case 16 : 
      return .11;
    case 32 : 
      return .11;
  default 
      return 0; }
}


double SetShifter::Shifter_Power_Leakage() {
  switch(Shifter_InputNum) {
    case 8 :
      return 780.9201e-9;
    case 16 : 
      return 1.4882e-6;
    case 32 : 
      return 2.9029e-6;
  default 
      return 0; }
}


double SetShifter::Shifter_Power_Dynamic() {
  switch(Shifter_InputNum) {
    case 8 : 
      return 14.5705e-6;
    case 16 : 
      return 23.6001e-6;
    case 32 : 
      return 41.6210e-6;
  default 
      return 0; }
}
  
  
  

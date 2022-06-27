#include "SetMultiplier.cpp"


SetMultiplier::SetMultiplier(int mult_num) {
  Mult_InputNum = mult_num;
}


SetMultiplier::~SetMultiplier() {}

double SetMultiplier::Mult_Area () {
  switch (Mult_InputNum) {
   case 8 :
      return 384.826;
   case 16 : 
      return 1400.8605;
   case 32 :
      return 5328.013;
   default
     return 0; }
}


double SetMultiplier::Mult_Latency () {
  switch (Mult_InputNum) {
   case 8 :
      return .91;
   case 16 : 
      return 1.67;
   case 32 :
      return 2.61;
   default
     return 0; }
}


double SetMultiplier::Mult_Power_Leakage () {
  switch (Mult_InputNum) {
   case 8 :
      return 2.2366e-6;
   case 16 : 
      return 8.1425e-6;
   case 32 :
      return 31.0545e-6;
   default
     return 0; }
}

double SetMultiplier::Mult_Power_Dynamic () {
  switch (Mult_InputNum) {
   case 8 :
      return 96.8856e-6;
   case 16 : 
      return 536.0497e-6;
   case 32 :
      return 3.057e-3;
   default
     return 0; }
}



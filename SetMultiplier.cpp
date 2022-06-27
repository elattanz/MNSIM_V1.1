#include "SetMultiplier.cpp"


SetMultiplier::SetMultiplier(int mult_num) {
  Mult_InputNum = mult_num;
}


SetMultiplier::SetMultiplier() {}

double Mult_Area () {
  switch (Mult_InputNum)
   case 8 :
      return 384.826;
   case 16 : 
      return 1400.8605;
   case 32 :
      return 5328.013;
   default
     return 0;
}

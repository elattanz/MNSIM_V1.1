#indef SETSHIFTER_H_
#define SETSHIFTER_H_

#include "Technology.h"
#include <stdlib.h>
#include "constant.h"

class SetShifter{
  public:
          int Shifter_InputNum; 
          
          SetShifter(int shifter_num);
          double ~SetShifter();
          double Shifter_Area();
          double Shifter_Latency();
          double Shifter_Power_Leakage();
          double Shifter_Power_Dynamic();
};

#endif
            

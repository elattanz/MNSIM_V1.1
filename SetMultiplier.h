
#indef SETMULTIPLIER_H_
#define SETMULTIPLIER_H_

#include "Technology.h"
#include <stdlib.h>
#include "constant.h"

class SetMultiplier{
  public:
          int Mult_InputNum; 
          
          SetMultiplier(Technology tech, int mult_num);
          double ~SetMultiplier();
          double Mult_Area();
          double Mult_Latency();
          double Mult_Power_Leakage();
          double Mult_Power_Dynamic();
};

#endif

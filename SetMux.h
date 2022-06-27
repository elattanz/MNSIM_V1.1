#indef SETMUX_H_
#define SETMUX_H_

//#include "CalculateGate.h"
#include "Technology.h"
#include <stdlib.h>
#include "constant.h"

class SetDemux {
  public:
          int Mux_InputNum; //size of gate, ex a 4 means a 4:1 MUX
  
          SetMux(Technology tech, int mux_num);
          double ~SetMux();
          double Mux_Area();
          double Mux_Latency();
          double Mux_Power_Leakage();
          double Mux_Power_Dynamic();
};

#endif

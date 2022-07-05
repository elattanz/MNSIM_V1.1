#ifndef SETDEMUX_H_
#define SETDEMUX_H_

//#include "CalculateGate.h"
#include "Technology.h"
#include <stdlib.h>
#include "constant.h"

class SetDemux {
  public:
          int Demux_InputNum; //size of gate, ex a 4 means a 1:4 DEMUX
  
          SetDemux(int demux_num);
          //double ~SetDemux();
          double Demux_Area();
          double Demux_Latency();
          double Demux_Power_Leakage();
          double Demux_Power_Dynamic();
};

#endif

                                

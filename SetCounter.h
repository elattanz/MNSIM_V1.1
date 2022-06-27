#indef SETCOUNTER_H_
#define SETCOUNTER_H_

#include "Technology.h"
#include <stdlib.h>
#include "constant.h"

class SetCounter{
  public: 
          
          SetCounter();
          double ~SetCounter();
          double Counter_Area();
          double Counter_Latency();
          double Counter_Power_Leakage();
          double Counter_Power_Dynamic();
};

#endif
        

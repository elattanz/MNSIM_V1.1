#ifndef INPUTPARAMETER_H_
#define INPUTPARAMETER_H_
#include <iostream>
#include <string>
#include <stdint.h>
using namespace std;

class InputParameter{
public:
	InputParameter();
	virtual ~InputParameter();

	/* Functions */
	void ReadInputParameterFromFile(string filename);

	/* Properties */
	int AppScale;
	//double rs;   
	//int cell_bit;
	int sig_bit;
	double rramtech;
	int minXbarSize;
	int maxXbarSize;
	//int minCell;
	//int maxCell;
	int minAdPos;
	int maxAdPos;
	int minBtLv;
	int maxBtLv;
	int minRRang;
	int maxRRang;
	int minAdder;
	int maxAdder;
	int minLine;
	int maxLine;
	int *NetScale;
	int *ComputationTime;
	int *OutputChannel;
	int *InputLength;
	string SimLv;
    	//string Target_Output;
	//string Application;
	//string Action_type;
	int WeightPolar;
	//string Cell;
	//string RRAMModel;
	int TranTech;
	string WriteMth;
	string *cfgtxt;
	int Pipeline;
	int MUX4;
	int MUX8;
	int MU16;
	int MUX32;
	int MUX64;
	int DEMUX4;
	int DEMUX8;
	int DEMUX16;
	int DEMUX32;
	int DEMUX64;
	int RPC8;
	int RPC16;
	int RPC32;
	int shifter8;
	int shifter16; 
	int shifter32;
	int mult8;
	int mult16;
	int mult32;
	int counter16;

};

#endif

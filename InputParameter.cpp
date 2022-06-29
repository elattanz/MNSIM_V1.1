#include "InputParameter.h"
#include<fstream>
#include<string>
#include <sstream>
#include<unistd.h>

InputParameter::InputParameter() {
	// TODO Auto-generated constructor stub
	AppScale = 0;
	rs = 3000;   
	//cell_bit = 8;
	sig_bit = 8;
	//rramtech = 32e-9;
	minXbarSize = 4;
	maxXbarSize = 1024;
	//minCell = 1;
	//maxCell = 1;
	minAdPos = 1;
	maxAdPos = 1;
	minBtLv = 0;
	maxBtLv = 16;
	minRRang = 1000;
	maxRRang = 1000000;
	minAdder = 1;
	maxAdder = 1;
	minLine = 22;
	maxLine = 90;
	MUX4 = 0;
	MUX8 = 0;
	MUX16 = 0;
	MUX32 = 0;
	MUX64 = 0;
	DEMUX4 = 0;
	DEMUX8 = 0;
	DEMUX16 = 0;
	DEMUX32 = 0;
	DEMUX64 = 0;
	RPC8 = 0;
	RPC16 = 0;
	RPC32 = 0;
	shifter8 = 0;
	shifter16 = 0;
	shifter32 = 0;
	mult8 = 0;
	mult16 = 0;
	mult32 = 0;
	counter16 = 0;
	subCompNum = 0;
	
}
InputParameter::~InputParameter() {
	// TODO Auto-generated destructor stub
}
void InputParameter::ReadInputParameterFromFile(string filename){
    ifstream fin;
    int i = 0;
    int filelength = 0;						
	int j = 0;
	string temp;
    fin.open(filename,ios::in);
	if(!fin.is_open())
		cout<<"SimConfig.txt cannot be found!"<<endl;
    while(fin.good() && !fin.eof()){
        getline(fin,temp);
        filelength++;
    }
    cfgtxt = new string[filelength];
    fin.clear();
    fin.seekg(0,ios::beg);
    for (i=0;i<filelength;i++)
    {
    	getline(fin,temp);
    	cfgtxt[i] = temp;
    }
    int config_begin = 0;
    int config_end = 0;
    bool flag = true;
	
    i = 0;
    while(flag)
    {
    	if(cfgtxt[i].find("config")!=string::npos)
	{
    		config_begin = i;
		j = i;
    		while(1)
		{
                	if (cfgtxt[j].find("}")!=string::npos)
			{
    				config_end = j;
				break;
                	}
                	else j++;
    		}
           	flag = false;
    	}
        i++;
    }


	// reading in configration from file
	for (i=(config_begin+1);i<=config_end;i++)
	{
		if(cfgtxt[i].find("Photonic")!=string::npos)
		{
			sim_mode = 1;
		} 
		else if(cfgtxt[i].find("Electronic")!=string::npos)
		{
			sim_mode = 0;
		} 
       		else if(cfgtxt[i].find("Application_Scale")!=string::npos)
		{
            		temp.assign(cfgtxt[i],sizeof("Application_Scale"),temp.length()-sizeof("Application_Scale")); 
			AppScale = std::stoi (temp,nullptr,0);
		}
		else if(cfgtxt[i].find("Weight_Polarity")!=string::npos)
		{
            		temp.assign(cfgtxt[i],sizeof("Weight_Polarity"),temp.length()-sizeof("Weight_Polarity")); 
			WeightPolar = std::stoi (temp,nullptr,0);
		}
		// max cell and min cell no longer defined here
   		else if(cfgtxt[i].find("Bit_Levels")!=string::npos)
		{
           		temp.assign(cfgtxt[i],sizeof("Bit_Levels"),temp.length()-sizeof("Bit_Levels")); 
			minBtLv = std::stoi (temp,nullptr,0);
			maxBtLv=minBtLv;
		}
		else if(cfgtxt[i].find("Min_Crossbar_Size")!=string::npos)
		{
            		temp.assign(cfgtxt[i],sizeof("Min_Crossbar_Size"),temp.length()-sizeof("Min_Crossbar_Size")); 
			minXbarSize = std::stoi(temp,nullptr,0);
		}
		else if(cfgtxt[i].find("Max_Crossbar_Size")!=string::npos)
		{
          		temp.assign(cfgtxt[i],sizeof("Max_Crossbar_Size"),temp.length()-sizeof("Max_Crossbar_Size")); 
			maxXbarSize = std::stoi(temp,nullptr,0);
		}
		else if(cfgtxt[i].find("Pipeline")!=string::npos)
		{
          		temp.assign(cfgtxt[i],sizeof("Pipeline"),temp.length()-sizeof("Pipeline"));
          		Pipeline = std::stoi(temp,nullptr,0);
        	}
		else if(cfgtxt[i].find("MUX_4:1")!=string::npos)
		{
          		temp.assign(cfgtxt[i],sizeof("MUX_4:1"),temp.length()-sizeof("MUX_4:1"));
          		MUX4 = std::stoi(temp,nullptr,0);
        	}
		else if(cfgtxt[i].find("MUX_8:1")!=string::npos)
		{
          		temp.assign(cfgtxt[i],sizeof("MUX_8:1"),temp.length()-sizeof("MUX_8:1"));
          		MUX8 = std::stoi(temp,nullptr,0);
        	}
		else if(cfgtxt[i].find("MUX_16:1")!=string::npos)
		{
          		temp.assign(cfgtxt[i],sizeof("MUX_16:1"),temp.length()-sizeof("MUX_16:1"));
          		MUX16 = std::stoi(temp,nullptr,0);
        	}
		else if(cfgtxt[i].find("MUX_32:1")!=string::npos)
		{
          		temp.assign(cfgtxt[i],sizeof("MUX_32:1"),temp.length()-sizeof("MUX_32:1"));
          		MUX32 = std::stoi(temp,nullptr,0);
        	}
		else if(cfgtxt[i].find("MUX_64:1")!=string::npos)
		{
          		temp.assign(cfgtxt[i],sizeof("MUX_64:1"),temp.length()-sizeof("MUX_64:1"));
          		MUX64 = std::stoi(temp,nullptr,0);
        	}
		else if(cfgtxt[i].find("DEMUX_1:4")!=string::npos)
		{
          		temp.assign(cfgtxt[i],sizeof("DEMUX_1:4"),temp.length()-sizeof("DEMUX_1:4"));
          		DEMUX4 = std::stoi(temp,nullptr,0);
        	}
		else if(cfgtxt[i].find("DEMUX_1:8")!=string::npos)
		{
          		temp.assign(cfgtxt[i],sizeof("DEMUX_1:8"),temp.length()-sizeof("DEMUX_1:8"));
          		DEMUX8 = std::stoi(temp,nullptr,0);
        	}
		else if(cfgtxt[i].find("DEMUX_1:16")!=string::npos)
		{
          		temp.assign(cfgtxt[i],sizeof("DEMUX_1:16"),temp.length()-sizeof("DEMUX_1:16"));
          		DEMUX16 = std::stoi(temp,nullptr,0);
        	}
		else if(cfgtxt[i].find("DEMUX_1:32")!=string::npos)
		{
          		temp.assign(cfgtxt[i],sizeof("DEMUX_1:32"),temp.length()-sizeof("DEMUX_1:32"));
          		DEMUX32 = std::stoi(temp,nullptr,0);
        	}
		else if(cfgtxt[i].find("DEMUX_1:64")!=string::npos)
		{
          		temp.assign(cfgtxt[i],sizeof("DEMUX_1:64"),temp.length()-sizeof("DEMUX_1:64"));
          		DEMUX64 = std::stoi(temp,nullptr,0);
        	}
		else if(cfgtxt[i].find("Ripple_Carry_Adder_8_bit")!=string::npos)
		{
          		temp.assign(cfgtxt[i],sizeof("Ripple_Carry_Adder_8_bit"),temp.length()-sizeof("Ripple_Carry_Adder_8_bit"));
          		RPC8 = std::stoi(temp,nullptr,0);
        	}
		else if(cfgtxt[i].find("Ripple_Carry_Adder_16_bit")!=string::npos)
		{
          		temp.assign(cfgtxt[i],sizeof("Ripple_Carry_Adder_16_bit"),temp.length()-sizeof("Ripple_Carry_Adder_16_bit"));
          		RPC16 = std::stoi(temp,nullptr,0);
        	}
		else if(cfgtxt[i].find("Ripple_Carry_Adder_32_bit")!=string::npos)
		{
          		temp.assign(cfgtxt[i],sizeof("Ripple_Carry_Adder_32_bit"),temp.length()-sizeof("Ripple_Carry_Adder_32_bit"));
          		RPC32 = std::stoi(temp,nullptr,0);
        	}
		else if(cfgtxt[i].find("Shifter_8_bit")!=string::npos)
		{
          		temp.assign(cfgtxt[i],sizeof("Shifter_8_bit"),temp.length()-sizeof("Shifter_8_bit"));
          		shifter8 = std::stoi(temp,nullptr,0);
        	}
		else if(cfgtxt[i].find("Shifter_16_bit")!=string::npos)
		{
          		temp.assign(cfgtxt[i],sizeof("Shifter_16_bit"),temp.length()-sizeof("Shifter_16_bit"));
          		shifter16 = std::stoi(temp,nullptr,0);
        	}
		else if(cfgtxt[i].find("Shifter_32_bit")!=string::npos)
		{
          		temp.assign(cfgtxt[i],sizeof("Shifter_32_bit"),temp.length()-sizeof("Shifter_32_bit"));
          		shifter32 = std::stoi(temp,nullptr,0);
        	}
		else if(cfgtxt[i].find("Multiplier_8_bit")!=string::npos)
		{
          		temp.assign(cfgtxt[i],sizeof("Multiplier_8_bit"),temp.length()-sizeof("Multiplier_8_bit"));
          		mult8 = std::stoi(temp,nullptr,0);
        	}
		else if(cfgtxt[i].find("Multiplier_16_bit")!=string::npos)
		{
          		temp.assign(cfgtxt[i],sizeof("Multiplier_16_bit"),temp.length()-sizeof("Multiplier_16_bit"));
          		mult16 = std::stoi(temp,nullptr,0);
        	}
		else if(cfgtxt[i].find("Multiplier_32_bit")!=string::npos)
		{
          		temp.assign(cfgtxt[i],sizeof("Multiplier_32_bit"),temp.length()-sizeof("Multiplier_32_bit"));
          		mult32 = std::stoi(temp,nullptr,0);
        	}
		else if(cfgtxt[i].find("Counter_16_bit")!=string::npos)
		{
          		temp.assign(cfgtxt[i],sizeof("Counter_16_bit"),temp.length()-sizeof("Counter_16_bit"));
          		counter16 = std::stoi(temp,nullptr,0);
        	}
		else if(cfgtxt[i].find("Subaddon_Components")!=string::npos)
		{
          		temp.assign(cfgtxt[i],sizeof("Subaddon_Components"),temp.length()-sizeof("Subaddon_Components"));
          		subCompNum = std::stoi(temp,nullptr,0);
			int n=0; 
			for(int k=0; k<subCompNum; k++)
			{
				// next immediate line is the number component, we don't need to save that to a var so we skip that line
				temp.assign(cfgtxt[i+n+2],sizeof("Area"),temp.length()-sizeof("Area"));
				subArea[k] = std::stoi(temp,nullptr,0);
				temp.assign(cfgtxt[i+n+3],sizeof("Latency"),temp.length()-sizeof("Latency"));
				subLatency[k] = std::stoi(temp,nullptr,0);
				temp.assign(cfgtxt[i+n+4],sizeof("Leakage_Power"),temp.length()-sizeof("Leakage_Power"));
				subLeakPw[k] = std::stoi(temp,nullptr,0);
				temp.assign(cfgtxt[i+n+5],sizeof("Dynamic_Power"),temp.length()-sizeof("Dynamic_Power"));
				subDymPw[k] = std::stoi(temp,nullptr,0);
				n = n+5;
			}//for
        	}//else if 
	}//for 
	

	ComputationTime = new int[AppScale];
	OutputChannel = new int [AppScale];
	InputLength = new int [AppScale];
	int temp_inputsize = 0;
	int temp_outputsize = 0;
	int temp_kernelsize = 0;
	int temp_inputchannel = 0;
	int temp_outputchannel = 0;
	int temp_inputlength = 0;
	int temp_outputlength = 0;
	int layer_type = 0;
	int layer_begin = config_end;//begin to search from the end of the config
	int layer_end = config_end;
	for (i=0;i<AppScale;i++)
	{
		flag = true;
		j = layer_end;
		while(flag)
		{
			if(cfgtxt[j].find("Layer"+to_string(i+1))!=string::npos)
			{
				layer_begin = j;
				while(1)
				{
                			if (cfgtxt[j].find("}")!=string::npos)
					{
    						layer_end = j;
                    				break;
                			}//if
					else j++;
				}//while
    				flag = false;
			}//if
			else
				j++;
		}//while
		layer_type = 0;
		for(j=layer_begin;j<layer_end;j++)
		{
           	 //cout<<"layer"<<i<<"FC"<<cfgtxt[j].find("FC")<<endl;
           	 //cout<<"layer"<<i<<"Conv"<<cfgtxt[j].find("Conv")<<endl;
          	  //cout<<endl;
			if(cfgtxt[j].find("Conv")!=string::npos)
			{//this layer is a conv layer
				layer_type = 1;
				break;
			}
			else if(cfgtxt[j].find("FC")!=string::npos)
			{
				layer_type = 2;
				break;
			}
		}//for
		if(layer_type == 1)
		{
			for(j=layer_begin;j<=layer_end;j++)
			{
				if(cfgtxt[j].find("Outputsize")!=string::npos)
				{
					temp.assign(cfgtxt[j],sizeof("Outputsize"),temp.length()-sizeof("Outputsize")); 
					temp_outputsize = std::stoi(temp,nullptr,0);
				}
				else if(cfgtxt[j].find("Kernelsize")!=string::npos)
				{
					temp.assign(cfgtxt[j],sizeof("Kernelsize"),temp.length()-sizeof("Kernelsize")); 
					temp_kernelsize = std::stoi(temp,nullptr,0);
				}
				else if(cfgtxt[j].find("Inputchannel")!=string::npos)
				{
					temp.assign(cfgtxt[j],sizeof("Inputchannel"),temp.length()-sizeof("Inputchannel")); 
					temp_inputchannel = std::stoi(temp,nullptr,0);
				}
				else if(cfgtxt[j].find("Outputchannel")!=string::npos)
				{
					temp.assign(cfgtxt[j],sizeof("Outputchannel"),temp.length()-sizeof("Outputchannel")); 
					temp_outputchannel = std::stoi(temp,nullptr,0);
				} //else if
			} //for
			ComputationTime[i] = temp_outputsize*temp_outputsize;
			OutputChannel[i] = temp_outputchannel;
			InputLength[i] = temp_kernelsize*temp_kernelsize*temp_inputchannel;
		} //if
		else if(layer_type == 2)
		{
			for(j=layer_begin;j<=layer_end;j++)
			{
				if(cfgtxt[j].find("Inputlength")!=string::npos)
				{
					temp.assign(cfgtxt[j],sizeof("Inputlength"),temp.length()-sizeof("Inputlength")); 
					temp_inputlength = std::stoi(temp,nullptr,0);
				}
				else if(cfgtxt[j].find("Outputlength")!=string::npos)
				{
					temp.assign(cfgtxt[j],sizeof("Outputlength"),temp.length()-sizeof("Outputlength")); 
					temp_outputlength = std::stoi(temp,nullptr,0);
				}
			} //for
			ComputationTime[i] = 1;
			OutputChannel[i] = temp_outputlength;
			InputLength[i] = temp_inputlength;
		} //else if
		else
			;
	}
}
    

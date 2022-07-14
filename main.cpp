#include<iostream>
#include<fstream>
#include<iomanip>
#include<math.h>
#include<time.h>
#include<string>
#include"InputParameter.h"
#include"module.h"
#include"formula.h"
#include"global.h"
#include"function.h"
#include"Technology.h"
//#include "SetMux.h"
//#include "SetDemux.h"

using namespace std;


void equal_P(double netlevel,double area,double energy,double latency,double power,double read_sep,double bit_level,double linetech,double xbarsize, double dym_power, double lkg_power);
double Demux_Area(int Demux_InputNum);
double Demux_Latency(int Demux_InputNum);
double Demux_Power_Leakage(int Demux_InputNum);
double Demux_Power_Dynamic(int Demux_InputNum);
double Mux_Area(int Mux_InputNum);
double Mux_Latency(int Mux_InputNum);
double Mux_Power_Leakage(int Mux_InputNum);
double Mux_Power_Dynamic(int Mux_InputNum);

InputParameter *inputParameter;
int count_my = 1;
double area,area_flags,latency,latency_multi,power_multi,power_flags,area_multi,power,energy,application,action_type,celltype, linetech;
double xbar_power_p, xbar_lat_p, xbar_area_p, periph_area_p, periph_lat_p, periph_power_p, x_dym_power, x_lkg_power, p_dym_power, p_lkg_power, dym_power, lkg_power;
int target;
double pulseposition = 0;
double cell_bit = 8;

double ** AAestrslt;
double ** AAAestrslt;
int row, row2;
//[17000][19];AAAestrslt[1100][19];
int mincount = 0;
double tech;
int err_count;
Technology *technology;
//SetMux Mux4;
/*
Mux4.Mux_InputNum = 4;
SetDemux Demux4;
Demux4.Demux_InputNum = 4;
SetDemux Demux16;
Demux16.Demux_InputNum = 16;
*/

int main(int argc, char *argv[]) 
{
	clock_t tic,toc;
	tic=clock();
	inputParameter = new InputParameter();

	string inputFileName;
	string outputFileName;

	if (argc == 1) {   //read configuration file
		inputFileName = "SimConfig.txt";
		outputFileName = "result.txt";
		cout << "Default sim-config file (SimConfig.txt) is loaded" << endl;
		cout << "Use default output results file (result.txt)" << endl;
	} 
	else if (argc == 2) {
		inputFileName = argv[1];
		cout << "User-defined sim-config file (" << inputFileName << ") is loaded" << endl;
		cout << "Use default output results file (result.txt)" << endl;
	} 
	else if (argc == 3) {
		inputFileName = argv[1];
		outputFileName = argv[2];
		cout << "User-defined sim-config file (" << inputFileName << ") is loaded" << endl;
		cout << "Print output to result file (" << outputFileName << ")" << endl;
	} 
	else {
		cout << "Error: Please use the correct format as follows" << endl;
		cout << "  Use the default configuration: " << argv[0] << endl;
		cout << "  Use the customized configuration: " << argv[0] << " <.txt file>"  << endl;
		exit(-1);
	}
	
	cout << endl;

	  
	//read configs  &  init configs
	inputParameter->ReadInputParameterFromFile(inputFileName);
	/*
	if (inputParameter->Application[0] == 'c' ||inputParameter->Application[0] == 'C') //Convolution
        application = 0;
    else
        application = 1;
	if (inputParameter->Action_type[0] == 'c' || inputParameter->Action_type[0] == 'C') //calculate phase
    	action_type = 2;
    else
    	action_type = 0;
	*/
	
	   
	switch (inputParameter->Target_Output[1]) {
		case 'a':
				target = 1;break;
		case 'A':
				target = 1;break;
		case 'e':
				target = 2;break;
		case 'E':
				target = 2;break;
		case 'l':
				target = 3;break;
		case 'L':
				target = 3;break;
		case 'p':
				target = 4;break;
		case 'P':
				target = 4;break;
	}

	if (inputParameter->sim_mode == 0)
	{	
		cout << "Checkpoint 5" << endl;
		technology = new Technology();
		technology->Initialize(HP/*inputParameter->deviceRoadmap*/);
		Technology techHigh;
		double alpha = 0;
		techHigh.Initialize(HP/*inputParameter->deviceRoadmap*/);
		alpha = (inputParameter->TranTech - 32.0) / 13;
		technology->InterpolateWith(techHigh, alpha);  
		//  load tech
		int tech = inputParameter->TranTech;
   		double minarea = 8e10;
   		double minenergy = 8e10;
    		double minpower = 8e10;
    		double minlatency = 8e10;
    		double minerr = 8e10;
		//double mintarget[8]={0,0,minarea,minenergy,minlatency,minerr,minpower};
    		double mintarget[4]={minarea,minenergy,minlatency,minpower};
		double input_err[200]={0};
    		row = (min(1,inputParameter->maxAdPos)-max(0,inputParameter->minAdPos)+1)*(min(16,inputParameter->maxBtLv)-max(0,inputParameter->minBtLv)+1)*(min(1,inputParameter->maxAdder)-max(0,inputParameter->minAdder)+1)*(log(inputParameter->maxXbarSize)/log(2)-log(inputParameter->minXbarSize)/log(2)+1)*128*inputParameter->AppScale+1;//*6 Decide by the size of crossbar
		AAestrslt = new double* [row];
		for(int i =0; i < row; i++)
			AAestrslt[i] = new double [19];
    		
		for (double adposition=max(0,inputParameter->minAdPos);adposition<=min(1,inputParameter->maxAdPos);adposition++) 
    		{
			
        		for (double bit_level = max(0,inputParameter->minBtLv);(bit_level<=min(16,inputParameter->maxBtLv));bit_level++) 
			{
				
            			for (double adderposition = max(0,inputParameter->minAdder);adderposition<=min(1,inputParameter->maxAdder);adderposition++) 
	    			{
                			//for (double linetech = 90;linetech<=90;linetech++) 
					//{    //[18,22,28,36,45,65,90];
                        			for (double xbarsize = inputParameter->minXbarSize;xbarsize<=inputParameter->maxXbarSize;xbarsize*=2) 
						{   //[4,8,16,32,64,128,256]%,512,1024]
							
                            				for (double read_sep = 1;read_sep<=128;read_sep++)
			    				{   //xbarsize/128 : xbarsize/128 : xbarsize%8:8:xbarsize
								
                                				if (xbarsize<inputParameter->minXbarSize || xbarsize > inputParameter->maxXbarSize)
								{
                                    					cout<<"error:xbarsize over the limit"<<endl;
								}
                                				else
								{
									for (int netlevel = 1;netlevel<=inputParameter->AppScale;netlevel++) 
									{ //-1
									
									for (int netlevel = 1;netlevel<=inputParameter->AppScale;netlevel++) { //-1
										if (bit_level != 0)
											cell_bit = bit_level; }
									linetech = 90;
									celltype = 1;
									determin_sig(xbarsize,adderposition,inputParameter->sig_bit,cell_bit,adposition);
									determin_net(xbarsize,inputParameter->InputLength[netlevel-1],inputParameter->OutputChannel[netlevel-1],signalsize);		
									unit_area_c(*technology,celltype,xbarsize,adposition,adderposition,pulseposition,inputParameter->sig_bit,application,inputParameter->rramtech,read_sep);	
									unit_latency_c(*technology,celltype,xbarsize,adposition,adderposition,pulseposition,action_type,inputParameter->sig_bit,read_sep);
									unit_power_c(*technology,celltype,xbarsize,adposition,adderposition,pulseposition,action_type,inputParameter->sig_bit,application,inputParameter->maxRRang,netrow,xbar_latency,adda_latency,adder_latency,decoder_latency,write_latency,read_latency,read_sep);
									periphery_area(*technology,xbarsize, netrow, netcolumn, adderposition,pulseposition,inputParameter->sig_bit,application);
									periphery_latency_c(*technology,netrow, adderposition,pulseposition,inputParameter->sig_bit,application); 
									periphery_power_c(*technology,xbarsize, netrow, netcolumn, adderposition,pulseposition,inputParameter->sig_bit,application,inputParameter->InputLength[netlevel-1],inputParameter->OutputChannel[netlevel-1]);
									accuracy_c(xbarsize,linetech,inputParameter->sig_bit,cell_bit,inputParameter->maxRRang,input_err[(int)netlevel-1]);	
									input_err[(int)netlevel] = accuracy;
									area = area_u * netrow * netcolumn + area_l + area_p ;//+ area_r + area_w;
									energy = utilization * power_u * latency_u * netrow * netcolumn + power_l * latency_l + power_p * latency_p;
									latency = latency = latency_u + latency_l + latency_p;
									latency_multi = latency_u;
									power_multi = utilization * power_u * netrow * netcolumn;
									power_flags = power_flags * netrow * netcolumn;
									area_multi = area_u * netrow * netcolumn;
									power = utilization * power_u  * netrow * netcolumn + power_l  + power_p ;
									equal(netlevel,area,energy,latency,power,accuracy,area_multi,power_multi,latency_multi,read_sep,adposition,bit_level,adderposition,pulseposition,linetech,celltype,xbarsize);
									if (accuracy < minerr) 
									{
										minerr = accuracy;
										err_count = count_my;
									}
									count_my = count_my + 1;
									}//for				
								}//else
            		    				}//for
        					}//for
    		    			//}//for
    				}//for
	   	 
			}//for
   		 }//for 
	double design_space = count_my/inputParameter->AppScale;
	
   	 //row2 = design_space*inputParameter->AppScale+1;
    	AAAestrslt = new double* [int(design_space)+1];
		for(int i =0; i <= design_space; i++)
			AAAestrslt[i] = new double [19];
		for (int temp_count = 1;temp_count<=design_space;temp_count++) 
		{
			for(int netlevel_temp=1;netlevel_temp<=inputParameter->AppScale;netlevel_temp++) 
			{
				AAAestrslt[temp_count][0] += AAestrslt[((temp_count-1) * inputParameter->AppScale +netlevel_temp)][0];
				AAAestrslt[temp_count][1] = AAestrslt[((temp_count-1) * inputParameter->AppScale +netlevel_temp)][1];
				AAAestrslt[temp_count][2] += AAestrslt[((temp_count-1) * inputParameter->AppScale +netlevel_temp)][2];
				AAAestrslt[temp_count][3] += AAestrslt[((temp_count-1) * inputParameter->AppScale +netlevel_temp)][3]*(inputParameter->ComputationTime[netlevel_temp-1]);
				if(inputParameter->Pipeline == 0) //not pipelined
					AAAestrslt[temp_count][4] += AAestrslt[((temp_count-1) * inputParameter->AppScale +netlevel_temp)][4]*(inputParameter->ComputationTime[netlevel_temp-1]);
				else if (netlevel_temp == 1)
					AAAestrslt[temp_count][4] = AAestrslt[((temp_count-1) * inputParameter->AppScale + 1)][4]*(inputParameter->ComputationTime[0]);
				else
					AAAestrslt[temp_count][4] = (AAAestrslt[temp_count][4] > AAestrslt[((temp_count-1) * inputParameter->AppScale + netlevel_temp)][4]*(inputParameter->ComputationTime[netlevel_temp-1]))? AAAestrslt[temp_count][4] : AAestrslt[((temp_count-1) * inputParameter->AppScale + netlevel_temp)][4]*(inputParameter->ComputationTime[netlevel_temp-1]);
				AAAestrslt[temp_count][5] += AAestrslt[((temp_count-1) * inputParameter->AppScale +netlevel_temp)][5];
				AAAestrslt[temp_count][6] = 0; //will update later
				AAAestrslt[temp_count][7] = AAestrslt[((temp_count-1) * inputParameter->AppScale +netlevel_temp)][7];
				AAAestrslt[temp_count][8] += AAestrslt[((temp_count-1) * inputParameter->AppScale +netlevel_temp)][8];
				AAAestrslt[temp_count][9] += AAestrslt[((temp_count-1) * inputParameter->AppScale +netlevel_temp)][9];
				AAAestrslt[temp_count][10] += AAestrslt[((temp_count-1) * inputParameter->AppScale +netlevel_temp)][10]*(inputParameter->ComputationTime[netlevel_temp-1]);
				for(int i = 11;i<19;i++)
					AAAestrslt[temp_count][i] = AAestrslt[((temp_count-1) * inputParameter->AppScale +netlevel_temp)][i];
			}  
			if (AAAestrslt[temp_count][target+1] < mintarget[target-1])
			{
				mintarget[target-1] = AAAestrslt[temp_count][target+1];
				mincount = temp_count;
			}
		}//for
		
		
		double optresult[17];
		optresult[0] = AAAestrslt[mincount][0];
		for (int i=1;i<6;i++)
			optresult[i] = AAAestrslt[mincount][i+1];
		for (int i=6;i<17;i++)
			optresult[i] = AAAestrslt[mincount][i+2];
	
		ofstream fout;
		fout.open(outputFileName,ios::out);
		if(!fout.is_open())
			cout<<"result.txt cannot be found!"<<endl;
		else {
			fout<<"xbarnumber:"<<optresult[0]<<endl;
			fout<<"area:"<<optresult[1]<<endl;
			fout<<"energy:"<<optresult[2]<<endl;
			fout<<"latency:"<<optresult[3]<<endl;
			fout<<"power:"<<optresult[4]<<endl;
			//fout<<"accuracy:"<<optresult[5]<<endl;
			fout<<"area_multi:"<<optresult[6]<<endl;
			fout<<"power_multi:"<<optresult[7]<<endl;
			fout<<"latency_multi:"<<optresult[8]<<endl;
			fout<<"read_sep:"<<optresult[9]<<endl;
			fout<<"adposition:"<<optresult[10]<<endl;
			fout<<"bit_level:"<<optresult[11]<<endl;
			fout<<"adderposition:"<<optresult[12]<<endl;
			fout<<"pulseposition:"<<optresult[13]<<endl;
			fout<<"linetech:"<<optresult[14]<<endl;
			fout<<"celltype:"<<optresult[15]<<endl;
			fout<<"xbarsize:"<<optresult[16]<<endl;
		}
   	}// if 

   	else if (inputParameter->sim_mode == 1)
   	{
		row = (min(16,inputParameter->maxBtLv)-max(0,inputParameter->minBtLv)+1)*(log(inputParameter->maxXbarSize)/log(2)-log(inputParameter->minXbarSize)/log(2)+1)*128*inputParameter->AppScale+1;//*6 Decide by the size of crossbar
		AAestrslt = new double* [row];
		for(int i =0; i < row; i++)
			AAestrslt[i] = new double [12];	
		double minarea = 8e10;
   		double minenergy = 8e10;
    		double minpower = 8e10;
    		double minlatency = 8e10;
    		double minerr = 8e10;
		//double mintarget[8]={0,0,minarea,minenergy,minlatency,minerr,minpower};
    		double mintarget[4]={minarea,minenergy,minlatency,minpower};
		
        	for (double bit_level = max(0,inputParameter->minBtLv);(bit_level<=min(16,inputParameter->maxBtLv));bit_level++) 
		{
              	  	for (double linetech = 90;linetech<=90;linetech++) 
			{    //[18,22,28,36,45,65,90];
                        	for (double xbarsize = inputParameter->minXbarSize;xbarsize<=inputParameter->maxXbarSize;xbarsize*=2) 
				{   //[4,8,16,32,64,128,256]%,512,1024]
                            		for (double read_sep = 1;read_sep<=128;read_sep++)
			    		{   //xbarsize/128 : xbarsize/128 : xbarsize%8:8:xbarsize
                                		if (xbarsize<inputParameter->minXbarSize || xbarsize > inputParameter->maxXbarSize)
						{
                                    			cout<<"error:xbarsize over the limit"<<endl;
						}
                                		else
						{
							for (int netlevel = 1;netlevel<=inputParameter->AppScale;netlevel++) 
							{ 
								// this func calculates netrow and netcolumn 
								determin_net_P(xbarsize,inputParameter->InputLength[netlevel-1],inputParameter->OutputChannel[netlevel-1]);	
								// crossbar power = PCM_leakage_power*xbarsize*xbarsize*netrow*netcolumn + PCM_dynamic_power*xbarsize*xbarsize*netrow*netcolumn
								x_dym_power = 1e-6*xbarsize*xbarsize*netrow*netcolumn;
								x_lkg_power = 1e-6*xbarsize*xbarsize*netrow*netcolumn;
								xbar_power_p = x_dym_power + x_lkg_power;
								// crossbar latency = PCM_latency*xbarsize*xbarsize*netrow*netcolumn 
								xbar_lat_p = 2e-11*netrow*netcolumn;
								// crossbar area = PCM_area*xbarsize*xbarsize*netrow*netcolumn 
								xbar_area_p = 9.07e-6*xbarsize*xbarsize*netrow*netcolumn;
								// periphery area = #MUX*areaMUX*netrow*netcolumn + #DEMUX*areaDEMUX*netrow*netcolumn + subcomponents...
								periph_area_p = 4*Mux_Area(4)*netrow*netcolumn + 1*Demux_Area(16)*netrow*netcolumn + 4*Demux_Area(4)*netrow*netcolumn;
								// periphery latency = #MUX*latencyMUX*netrow*netcolumn + #DEMUX*DEMUXlatency*netrow*netcolumn + subcomponents...
								periph_lat_p = 4*Mux_Latency(4)*netrow*netcolumn + 1*Demux_Latency(16)*netrow*netcolumn + 4*Demux_Area(4)*netrow*netcolumn;
								// periphery power = #MUX*MUXleakagePower*netrow*netcolumn + #MUX*MUXdynamicPower*netrow*netcolumn + #DEMUX*DEMUXleakagePower*netrow*netcolumn + #DEMUX*DEMUXdynamicPower*netrow*netcolumn+ subcomponents...
								p_dym_power = 4*Mux_Power_Dynamic(4)*netrow*netcolumn + 1*Demux_Power_Dynamic(16)*netrow*netcolumn + 4*Demux_Power_Dynamic(4)*netrow*netcolumn;
								p_lkg_power = 4*Mux_Power_Leakage(4)*netrow*netcolumn + 1*Demux_Power_Leakage(16)*netrow*netcolumn + 4*Demux_Power_Leakage(4)*netrow*netcolumn;
								for (int j=0; j < inputParameter->subCompNum; j++)
								{
									periph_area_p = periph_area_p + inputParameter->subArea[j]*netrow*netcolumn;
									periph_lat_p = periph_lat_p + inputParameter->subLatency[j]*netrow*netcolumn;
									p_lkg_power =  p_dym_power+ inputParameter->subLeakPw[j]*netrow*netcolumn;
									p_dym_power = p_lkg_power + inputParameter->subDymPw[j]*netrow*netcolumn;
								}
								periph_power_p = p_dym_power + p_lkg_power;
								dym_power = x_dym_power + p_dym_power;
								lkg_power = x_lkg_power + p_lkg_power;
								// area = crossbar area + periphery area
								area = xbar_area_p + periph_area_p; 
								// latency = crossbar latency + periphery latency
								latency = xbar_lat_p + periph_lat_p;
								// power = crossbar power + crossbar latency
								power = xbar_power_p + periph_power_p;
								// ***** There is a good change this energy calculation won't be accurate because we did not add the read and write power of PCM
								energy = (utilization*xbar_power_p * xbar_lat_p) + (periph_power_p * periph_lat_p);
								//energy = 10;
								equal_P(netlevel,area,energy,latency,power,read_sep,bit_level,linetech,xbarsize,dym_power,lkg_power);
								count_my = count_my + 1;
							}//for				
						}//else
            		    		}//for
    		    		}//for
	   	 	}//for
   	 	}//for 
   		 double design_space = count_my/inputParameter->AppScale;
   		 AAAestrslt = new double* [int(design_space)+1];
		for(int i =0; i <= design_space; i++)
			AAAestrslt[i] = new double [12];
		for (int temp_count = 1;temp_count<=design_space;temp_count++) 
		{
			for(int netlevel_temp=1;netlevel_temp<=inputParameter->AppScale;netlevel_temp++) 
			{
				AAAestrslt[temp_count][0] += AAestrslt[((temp_count-1) * inputParameter->AppScale +netlevel_temp)][0];   //netrow*netcolumn
				AAAestrslt[temp_count][1] = AAestrslt[((temp_count-1) * inputParameter->AppScale +netlevel_temp)][1];    //net level
				AAAestrslt[temp_count][2] += AAestrslt[((temp_count-1) * inputParameter->AppScale +netlevel_temp)][2];    // area
				AAAestrslt[temp_count][3] += AAestrslt[((temp_count-1) * inputParameter->AppScale +netlevel_temp)][3]*(inputParameter->ComputationTime[netlevel_temp-1]);   //energy
				if(inputParameter->Pipeline == 0) //not pipelined
					AAAestrslt[temp_count][4] += AAestrslt[((temp_count-1) * inputParameter->AppScale +netlevel_temp)][4]*(inputParameter->ComputationTime[netlevel_temp-1]);   //latency
				else if (netlevel_temp == 1)
					AAAestrslt[temp_count][4] = AAestrslt[((temp_count-1) * inputParameter->AppScale + 1)][4]*(inputParameter->ComputationTime[0]);
				else
					AAAestrslt[temp_count][4] = (AAAestrslt[temp_count][4] > AAestrslt[((temp_count-1) * inputParameter->AppScale + netlevel_temp)][4]*(inputParameter->ComputationTime[netlevel_temp-1]))? AAAestrslt[temp_count][4] : AAestrslt[((temp_count-1) * inputParameter->AppScale + netlevel_temp)][4]*(inputParameter->ComputationTime[netlevel_temp-1]);
				AAAestrslt[temp_count][5] += AAestrslt[((temp_count-1) * inputParameter->AppScale +netlevel_temp)][5];   //power
				for(int i = 6;i<12;i++)   //read_sep, bit_level, linetech, xbarsize
					AAAestrslt[temp_count][i] = AAestrslt[((temp_count-1) * inputParameter->AppScale +netlevel_temp)][i];
			} //for
			if (AAAestrslt[temp_count][target+1] < mintarget[target-1])
			{
				mintarget[target-1] = AAAestrslt[temp_count][target+1];
				mincount = temp_count;
			} //if 
		}//for
		double optresult[11];
		optresult[0] = AAAestrslt[mincount][0];
		optresult[1] = AAAestrslt[mincount][2];
		optresult[2] = AAAestrslt[mincount][3];
		optresult[3] = AAAestrslt[mincount][4];
		optresult[4] = AAAestrslt[mincount][5];
		optresult[5] = AAAestrslt[mincount][6];
		optresult[6] = AAAestrslt[mincount][7];
		optresult[7] = AAAestrslt[mincount][8];
		optresult[8] = AAAestrslt[mincount][9];
		optresult[9] = AAAestrslt[mincount][10];
		optresult[10] = AAAestrslt[mincount][11];
		//for (int i=1;i<6;i++)
		//	optresult[i] = AAAestrslt[mincount][i+1];
		//for (int i=6;i<11;i++)
		//	optresult[i] = AAAestrslt[mincount][i+2];
	
		ofstream fout;
		fout.open(outputFileName,ios::out);
		if(!fout.is_open())
			cout<<"result.txt cannot be found!"<<endl;
		else {
			fout<<"xbarnumber:"<<optresult[0]<<endl;
			fout<<"area:"<<optresult[1]<<endl;
			fout<<"energy:"<<optresult[2]<<endl;
			fout<<"latency:"<<optresult[3]<<endl;
			fout<<"total power:"<<optresult[4]<<endl;
			fout<<"dynamic power:"<<optresult[9]<<endl;
			fout<<"leakage power:"<<optresult[10]<<endl;
			fout<<"read_sep:"<<optresult[5]<<endl;
			fout<<"bit_level:"<<optresult[6]<<endl;
			fout<<"linetech:"<<optresult[7]<<endl;
			fout<<"xbarsize:"<<optresult[8]<<endl;
			}
  	} // elseif 

	toc=clock();
   	cout<<"Run time: "<<(double)(toc-tic)/CLOCKS_PER_SEC<<"S"<<endl;
	delete inputParameter;
	delete AAestrslt;
	delete AAAestrslt;
	delete technology;
	return 0;
} //main

void equal(double netlevel,double area,double energy,double latency,double power,double accuracy,double area_multi,double power_multi,double latency_multi,double read_sep,double adposition,double bit_level,double adderposition,double pulseposition,double linetech,double celltype,double xbarsize) {
	AAestrslt[count_my][0] = netrow * netcolumn;
	AAestrslt[count_my][1] = netlevel;
	AAestrslt[count_my][2] = area;
	AAestrslt[count_my][3] = energy;
	AAestrslt[count_my][4] = latency;
	AAestrslt[count_my][5] = power;
	AAestrslt[count_my][6] = accuracy;
	AAestrslt[count_my][7] = d1;
	AAestrslt[count_my][8] = area_multi;
	AAestrslt[count_my][9] = power_multi;
	AAestrslt[count_my][10] = latency_multi;
	AAestrslt[count_my][11] = read_sep;
	AAestrslt[count_my][12] = adposition;
	AAestrslt[count_my][13] = bit_level;
	AAestrslt[count_my][14] = adderposition;
	AAestrslt[count_my][15] = pulseposition;
	AAestrslt[count_my][16] = linetech;
	AAestrslt[count_my][17] = celltype;
	AAestrslt[count_my][18] = xbarsize;
}

void equal_P(double netlevel,double area,double energy,double latency,double power,double read_sep,double bit_level,double linetech,double xbarsize, double dym_power, double lkg_power) {
	AAestrslt[count_my][0] = netrow * netcolumn;
	AAestrslt[count_my][1] = netlevel;
	AAestrslt[count_my][2] = area;
	AAestrslt[count_my][3] = energy;
	AAestrslt[count_my][4] = latency;
	AAestrslt[count_my][5] = power;
	AAestrslt[count_my][6] = read_sep;  //originally [11]
	AAestrslt[count_my][7] = bit_level;  //originally [13]
	AAestrslt[count_my][8] = linetech;  //originally [16]
	AAestrslt[count_my][9] = xbarsize;  //originally [18]
	AAestrslt[count_my][10] = dym_power;
	AAestrslt[count_my][11] = lkg_power;
}

double max1(int a,int b,int c) {
	double i;
	int j;
	i=AAestrslt[b][4];
	for(j=b;j<a;j++)
		if(AAestrslt[j][4]>i)
			i=AAestrslt[j][4];
	return i;
}


double Demux_Area(int Demux_InputNum){
  switch(Demux_InputNum) {
    case 4 :
      return 15.4869;
    case 8 :
      return 34.2589;
    case 16 : 
      return 76.9652;
    case 32 :
      return 140.790;
    case 64 :
      return 263.2773;
    default :
      return 0; }
  }
 
double Demux_Latency(int Demux_InputNum){
  switch(Demux_InputNum) {
    case 4 :
      return .08;
    case 8 :
      return .13;
    case 16 : 
      return .11;
    case 32 :
      return .18;
    case 64 :
      return .19;
    default :
      return 0; }
  }
  
double Demux_Power_Leakage(int Demux_InputNum){
  switch(Demux_InputNum) {
    case 4 :
      return 27.6717e-9;
    case 8 :
      return 84.8136e-9;
    case 16 : 
      return 232.8362e-9;
    case 32 :
      return 422.1485e-9;
    case 64 :
      return 740.6179e-9;
    default :
      return 0; }
  }
  
double Demux_Power_Dynamic(int Demux_InputNum){
  switch(Demux_InputNum) {
    case 4 :
      return 3.1805e-6;
    case 8 :
      return 6.202e-6;
    case 16 : 
      return 10.4622e-6;
    case 32 :
      return 16.6957e-6;
    case 64 :
      return 27.7357e-6;
    default :
      return 0; }
  }

double Mux_Area(int Mux_InputNum){
  switch(Mux_InputNum) {
    case 4 :
      return 11.2632;
    case 8 :
      return 27.6887;
    case 16 : 
      return 132.3426;
    case 32 :
      return 276.417;
    case 64 :
      return 561.2829;
    default :
      return 0; }
  }
 
double Mux_Latency(int Mux_InputNum){
  switch(Mux_InputNum) {
    case 4 :
      return .07;
    case 8 :
      return .14;
    case 16 : 
      return .49;
    case 32 :
      return .81;
    case 64 :
      return 1.188;
    default :
      return 0; }
  }
  
double Mux_Power_Leakage(int Mux_InputNum){
  switch(Mux_InputNum) {
    case 4 :
      return 55.6509e-9;
    case 8 :
      return 131.5937e-9;
    case 16 : 
      return 640.5314e-9;
    case 32 :
      return 1.3155e-6;
    case 64 :
      return 2.6812e-6;
    default :
      return 0; }
  }
  
double Mux_Power_Dynamic(int Mux_InputNum){
  switch(Mux_InputNum) {
    case 4 :
      return 3.3018e-6;
    case 8 :
      return 8.9763e-6;
    case 16 : 
      return 34.585e-6;
    case 32 :
      return 68.506e-6;
    case 64 :
      return 105.2228e-6;
    default :
      return 0; }
  }
  

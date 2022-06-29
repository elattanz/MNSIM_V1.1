/*******************************************************************************
* Copyright (c) 2012-2013, The Microsystems Design Labratory (MDL)
* Department of Computer Science and Engineering, The Pennsylvania State University
* Exascale Computing Lab, Hewlett-Packard Company
* All rights reserved.
* 
* This source code is part of NVSim - An area, timing and power model for both 
* volatile (e.g., SRAM, DRAM) and non-volatile memory (e.g., PCRAM, STT-RAM, ReRAM, 
* SLC NAND Flash). The source code is free and you can redistribute and/or modify it
* by providing that the following conditions are met:
* 
*  1) Redistributions of source code must retain the above copyright notice,
*     this list of conditions and the following disclaimer.
* 
*  2) Redistributions in binary form must reproduce the above copyright notice,
*     this list of conditions and the following disclaimer in the documentation
*     and/or other materials provided with the distribution.
* 
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
* 
* Author list: 
*   Cong Xu	    ( Email: czx102 at psu dot edu 
*                     Website: http://www.cse.psu.edu/~czx102/ )
*   Xiangyu Dong    ( Email: xydong at cse dot psu dot edu
*                     Website: http://www.cse.psu.edu/~xydong/ )
*******************************************************************************/


#include "Technology.h"
#include <math.h>

Technology::Technology() {
	// TODO Auto-generated constructor stub
	initialized = false;
}

Technology::~Technology() {
	// TODO Auto-generated destructor stub
}

void Technology::Initialize(DeviceRoadmap _deviceRoadmap) 
{
	if (initialized)
		cout << "Warning: Already initialized!" << endl;
	int featureSize = 45 * 1e-9;
	deviceRoadmap = _deviceRoadmap;
	// emily deleted the feature sizes beyond 45nm 	
	//else if (_featureSizeInNano >= 45) {
		if (_deviceRoadmap == HP) 
		{
			/* MASTAR 5 - hp-bulk-2010.pro */
			vdd = 1.0;
			vth = 126.79e-3;
			phyGateLength = 0.018e-6;
			capIdealGate = 6.78e-10;
			capFringe = 1.7e-10;
			capJunction = 1.00e-3;
			capOx = 3.77e-2;
			effectiveElectronMobility = 297.70e-4;
			effectiveHoleMobility = 95.27e-4;
			pnSizeRatio = 2.41;						/* from CACTI */
			effectiveResistanceMultiplier = 1.51;	/* from CACTI */
			currentOnNmos[0] = 1823.8;
			currentOnNmos[10] = 1808.2;
			currentOnNmos[20] = 1792.6;
			currentOnNmos[30] = 1777.0;
			currentOnNmos[40] = 1761.4;
			currentOnNmos[50] = 1745.8;
			currentOnNmos[60] = 1730.3;
			currentOnNmos[70] = 1714.7;
			currentOnNmos[80] = 1699.1;
			currentOnNmos[90] = 1683.2;
			currentOnNmos[100] = 1666.6;
			currentOnPmos[0] = 1632.2;
			currentOnPmos[10] = 1612.8;
			currentOnPmos[20] = 1593.6;
			currentOnPmos[30] = 1574.1;
			currentOnPmos[40] = 1554.7;
			currentOnPmos[50] = 1535.5;
			currentOnPmos[60] = 1516.4;
			currentOnPmos[70] = 1497.6;
			currentOnPmos[80] = 1478.8;
			currentOnPmos[90] = 1460.3;
			currentOnPmos[100] = 1441.8;
			/* NMOS off current, Unit: A/m, these values are calculated by Sheng Li offline */
			currentOffNmos[0] = 2.80e-1;
			currentOffNmos[10] = 3.28e-1;
			currentOffNmos[20] = 3.81e-1;
			currentOffNmos[30] = 4.39e-1;
			currentOffNmos[40] = 5.02e-1;
			currentOffNmos[50] = 5.69e-1;
			currentOffNmos[60] = 6.42e-1;
			currentOffNmos[70] = 7.20e-1;
			currentOffNmos[80] = 8.03e-1;
			currentOffNmos[90] = 8.91e-1;
			currentOffNmos[100] = 9.84e-1;
			/* PMOS off current, Unit: A/m. TO-DO: set PMOS = NMOS because MASTAR value is obviously wrong */
			currentOffPmos[0] = currentOffNmos[0];
			currentOffPmos[10] = currentOffNmos[10];
			currentOffPmos[20] = currentOffNmos[20];
			currentOffPmos[30] = currentOffNmos[30];
			currentOffPmos[40] = currentOffNmos[40];
			currentOffPmos[50] = currentOffNmos[50];
			currentOffPmos[60] = currentOffNmos[60];
			currentOffPmos[70] = currentOffNmos[70];
			currentOffPmos[80] = currentOffNmos[80];
			currentOffPmos[90] = currentOffNmos[90];
			currentOffPmos[100] = currentOffNmos[100];
		}
		else if (_deviceRoadmap == LSTP) 
		{
			/* MASTAR 5 - lstp-bulk-2010.pro */
			vdd = 1.0;
			vth = 564.52e-3;
			phyGateLength = 0.028e-6;
			capIdealGate = 5.58e-10;
			capFringe = 2.1e-10;
			capJunction = 1.00e-3;
			capOx = 1.99e-2;
			effectiveElectronMobility = 456.14e-4;
			effectiveHoleMobility = 96.98e-4;
			pnSizeRatio = 2.23;						/* from CACTI */
			effectiveResistanceMultiplier = 1.99;	/* from CACTI */
			currentOnNmos[0] = 527.5;
			currentOnNmos[10] = 520.2;
			currentOnNmos[20] = 512.9;
			currentOnNmos[30] = 505.8;
			currentOnNmos[40] = 498.6;
			currentOnNmos[50] = 491.4;
			currentOnNmos[60] = 483.7;
			currentOnNmos[70] = 474.4;
			currentOnNmos[80] = 461.2;
			currentOnNmos[90] = 442.6;
			currentOnNmos[100] = 421.3;
			currentOnPmos[0] = 497.9;
			currentOnPmos[10] = 489.5;
			currentOnPmos[20] = 481.3;
			currentOnPmos[30] = 473.2;
			currentOnPmos[40] = 465.3;
			currentOnPmos[50] = 457.6;
			currentOnPmos[60] = 450.0;
			currentOnPmos[70] = 442.5;
			currentOnPmos[80] = 435.1;
			currentOnPmos[90] = 427.5;
			currentOnPmos[100] = 419.7;
			/* NMOS off current, Unit: A/m, these values are calculated by Sheng Li offline */
			currentOffNmos[0] = 1.01e-5;
			currentOffNmos[10] = 1.65e-5;
			currentOffNmos[20] = 2.62e-5;
			currentOffNmos[30] = 4.06e-5;
			currentOffNmos[40] = 6.12e-5;
			currentOffNmos[50] = 9.02e-5;
			currentOffNmos[60] = 1.30e-4;
			currentOffNmos[70] = 1.83e-4;
			currentOffNmos[80] = 2.51e-4;
			currentOffNmos[90] = 3.29e-4;
			currentOffNmos[100] = 4.10e-4;
			/* PMOS off current, Unit: A/m. TO-DO: set PMOS = NMOS because MASTAR value is obviously wrong */
			currentOffPmos[0] = currentOffNmos[0];
			currentOffPmos[10] = currentOffNmos[10];
			currentOffPmos[20] = currentOffNmos[20];
			currentOffPmos[30] = currentOffNmos[30];
			currentOffPmos[40] = currentOffNmos[40];
			currentOffPmos[50] = currentOffNmos[50];
			currentOffPmos[60] = currentOffNmos[60];
			currentOffPmos[70] = currentOffNmos[70];
			currentOffPmos[80] = currentOffNmos[80];
			currentOffPmos[90] = currentOffNmos[90];
			currentOffPmos[100] = currentOffNmos[100];
		} 
		else 
		{
			/* MASTAR 5 - lop-bulk-2010.pro */
			vdd = 0.7;
			vth = 288.94e-3;
			phyGateLength = 0.022e-6;
			capIdealGate = 6.13e-10;
			capFringe = 2.0e-10;
			capJunction = 1.00e-3;
			capOx = 2.79e-2;
			effectiveElectronMobility = 606.95e-4;
			effectiveHoleMobility = 124.60e-4;
			pnSizeRatio = 2.28;						/* from CACTI */
			effectiveResistanceMultiplier = 1.76;	/* from CACTI */
			currentOnNmos[0] = 682.1;
			currentOnNmos[10] = 672.3;
			currentOnNmos[20] = 662.5;
			currentOnNmos[30] = 652.8;
			currentOnNmos[40] = 643.0;
			currentOnNmos[50] = 632.8;
			currentOnNmos[60] = 620.9;
			currentOnNmos[70] = 605.0;
			currentOnNmos[80] = 583.6;
			currentOnNmos[90] = 561.0;
			currentOnNmos[100] = 542.7;
			currentOnPmos[0] = 772.4;
			currentOnPmos[10] = 759.6;
			currentOnPmos[20] = 746.9;
			currentOnPmos[30] = 734.4;
			currentOnPmos[40] = 722.1;
			currentOnPmos[50] = 710.0;
			currentOnPmos[60] = 698.1;
			currentOnPmos[70] = 686.3;
			currentOnPmos[80] = 674.4;
			currentOnPmos[90] = 662.3;
			currentOnPmos[100] = 650.2;
			/* NMOS off current, Unit: A/m, these values are calculated by Sheng Li offline */
			currentOffNmos[0] = 4.03e-3;
			currentOffNmos[10] = 5.02e-3;
			currentOffNmos[20] = 6.18e-3;
			currentOffNmos[30] = 7.51e-3;
			currentOffNmos[40] = 9.04e-3;
			currentOffNmos[50] = 1.08e-2;
			currentOffNmos[60] = 1.27e-2;
			currentOffNmos[70] = 1.47e-2;
			currentOffNmos[80] = 1.66e-2;
			currentOffNmos[90] = 1.84e-2;
			currentOffNmos[100] = 2.03e-2;
			/* PMOS off current, Unit: A/m. TO-DO: set PMOS = NMOS because MASTAR value is obviously wrong */
			currentOffPmos[0] = currentOffNmos[0];
			currentOffPmos[10] = currentOffNmos[10];
			currentOffPmos[20] = currentOffNmos[20];
			currentOffPmos[30] = currentOffNmos[30];
			currentOffPmos[40] = currentOffNmos[40];
			currentOffPmos[50] = currentOffNmos[50];
			currentOffPmos[60] = currentOffNmos[60];
			currentOffPmos[70] = currentOffNmos[70];
			currentOffPmos[80] = currentOffNmos[80];
			currentOffPmos[90] = currentOffNmos[90];
			currentOffPmos[100] = currentOffNmos[100];
		}
	}

	// THE REST OF THIS CODE STILL NEEDS TO BE LOOKED AT AND CHANGED

	capOverlap = capIdealGate * 0.2;
	//capSidewall = 2.5e-10;	/* Unit: F/m, this value is from CACTI, PTM model shows the value is 5e-10 */
	double cjd = 1e-3;             /* Bottom junction capacitance, Unit: F/m^2*/
	double cjswd = 2.5e-10;           /* Isolation-edge sidewall junction capacitance, Unit: F/m */
	double cjswgd = 0.5e-10;          /* Gate-edge sidewall junction capacitance, Unit: F/m */
	double mjd = 0.5;             /* Bottom junction capacitance grating coefficient */
	double mjswd = 0.33;           /* Isolation-edge sidewall junction capacitance grading coefficient */
	double mjswgd = 0.33;          /* Gate-edge sidewall junction capacitance grading coefficient */
	buildInPotential = 0.9;			/* This value is from BSIM4 */
	capJunction = cjd / pow(1 + vdd / buildInPotential, mjd);
	capSidewall = cjswd / pow(1 + vdd / buildInPotential, mjswd);
	capDrainToChannel = cjswgd / pow(1 + vdd / buildInPotential, mjswgd);

	vdsatNmos = phyGateLength * 1e5 /* Silicon saturatio velocity, Unit: m/s */ / effectiveElectronMobility;
	vdsatPmos = phyGateLength * 1e5 /* Silicon saturatio velocity, Unit: m/s */ / effectiveHoleMobility;

	/* Properties not used so far */
	capPolywire = 0.0;	/* TO-DO: we need to find the values */

	/* Interpolate */
	for (int i = 1; i < 100; i++) {
		if (i % 10) {
			double a = currentOnNmos[i / 10 * 10];
			double b = currentOnNmos[i / 10 * 10 + 10];
			currentOnNmos[i] = a + (b-a) * (i % 10) / 10;
		}
	}

	for (int i = 1; i < 100; i++) {
		if (i % 10) {
			double a = currentOnPmos[i / 10 * 10];
			double b = currentOnPmos[i / 10 * 10 + 10];
			currentOnPmos[i] = a + (b-a) * (i % 10) / 10;
		}
	}

	for (int i = 1; i < 100; i++) {
		if (i % 10) {
			double a = currentOffNmos[i / 10 * 10];
			double b = currentOffNmos[i / 10 * 10 + 10];
			currentOffNmos[i] = a + (b-a) * (i % 10) / 10;
		}
	}

	for (int i = 1; i < 100; i++) {
		if (i % 10) {
			double a = currentOffPmos[i / 10 * 10];
			double b = currentOffPmos[i / 10 * 10 + 10];
			currentOffPmos[i] = a + (b-a) * (i % 10) / 10;
		}
	}

	initialized = true;
}
void Technology::PrintProperty() {
	cout << "Fabrication Process Technology Node:" << endl;
	cout << "TO-DO" << endl;
}

void Technology::InterpolateWith(Technology rhs, double _alpha) {
	if (featureSizeInNano != rhs.featureSizeInNano) {
		vdd = (1 - _alpha) * vdd + _alpha * rhs.vdd;
		vth = (1 - _alpha) * vth + _alpha * rhs.vth;
		phyGateLength = (1 - _alpha) * phyGateLength + _alpha * rhs.phyGateLength;
		capIdealGate = (1 - _alpha) * capIdealGate + _alpha * rhs.capIdealGate;
		capFringe = (1 - _alpha) * capFringe + _alpha * rhs.capFringe;
		capJunction = (1 - _alpha) * capJunction + _alpha * rhs.capJunction;
		capOx = (1 - _alpha) * capOx + _alpha * rhs.capOx;
		effectiveElectronMobility = (1 - _alpha) * effectiveElectronMobility + _alpha * rhs.effectiveElectronMobility;
		effectiveHoleMobility = (1 - _alpha) * effectiveHoleMobility + _alpha * rhs.effectiveHoleMobility;
		pnSizeRatio = (1 - _alpha) * pnSizeRatio + _alpha * rhs.pnSizeRatio;
		effectiveResistanceMultiplier = (1 - _alpha) * effectiveResistanceMultiplier + _alpha * rhs.effectiveResistanceMultiplier;
		for (int i = 0; i <= 100; i++){
			currentOnNmos[i] = (1 - _alpha) * currentOnNmos[i] + _alpha * rhs.currentOnNmos[i];
			currentOnPmos[i] = (1 - _alpha) * currentOnPmos[i] + _alpha * rhs.currentOnPmos[i];
			currentOffNmos[i] = pow(currentOffNmos[i], 1 - _alpha) * pow(rhs.currentOffNmos[i], _alpha);
			currentOffPmos[i] = pow(currentOffPmos[i], 1 - _alpha) * pow(rhs.currentOffPmos[i], _alpha);
		}
		//capSidewall = 2.5e-10;	/* Unit: F/m, this value is from CACTI, PTM model shows the value is 5e-10 */
		double cjd = 1e-3;             /* Bottom junction capacitance, Unit: F/m^2*/
		double cjswd = 2.5e-10;           /* Isolation-edge sidewall junction capacitance, Unit: F/m */
		double cjswgd = 0.5e-10;          /* Gate-edge sidewall junction capacitance, Unit: F/m */
		double mjd = 0.5;             /* Bottom junction capacitance grating coefficient */
		double mjswd = 0.33;           /* Isolation-edge sidewall junction capacitance grading coefficient */
		double mjswgd = 0.33;          /* Gate-edge sidewall junction capacitance grading coefficient */
		buildInPotential = 0.9;			/* This value is from BSIM4 */
		capJunction = cjd / pow(1 + vdd / buildInPotential, mjd);
		capSidewall = cjswd / pow(1 + vdd / buildInPotential, mjswd);
		capDrainToChannel = cjswgd / pow(1 + vdd / buildInPotential, mjswgd);

		vdsatNmos = phyGateLength * 1e5 /* Silicon saturatio velocity, Unit: m/s */ / effectiveElectronMobility;
		vdsatPmos = phyGateLength * 1e5 /* Silicon saturatio velocity, Unit: m/s */ / effectiveHoleMobility;
	}
}

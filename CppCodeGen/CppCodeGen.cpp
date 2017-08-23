// CppCodeGen.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;


void genCode(vector<string> robotType, string toDefine) {
	if (robotType.empty()) return;

	cout << "#if ";

		for (vector<string>::iterator it = robotType.begin(); it != robotType.end(); it++) { 
			string robotNumber = *it; 
			cout << "defined(ROBOT_NUMBER_" << robotNumber << ")";
			if (it+1 != robotType.end()) cout << " || ";
			//if (robotNumber != robotType.back()) cout << " || ";

		}
		cout << endl << "	#define " << toDefine << endl;
		cout << "#endif" << endl;

}

void main()
{
	vector<string> BASIC_DRIVETRAIN = {};
	vector<string> DUAL_MOTORS = {};
	vector<string> LR_TACKLE_PERIPHERALS = {};
	vector<string> CENTER_PERIPHERALS = {};
	vector<string> QB_PERIPHERALS = {};
	vector<string> IR_MAST = {};
	vector<string> QB_TRACKING = {};
	vector<string> KICKER_PERIPHERALS = {};
	vector<string> RECEIVER_PERIPHERALS = {};
	vector<string> LED_STRIP = {};
	vector<string> TACKLE = {};

	genCode(BASIC_DRIVETRAIN, "BASIC_DRIVETRAIN");
	genCode(DUAL_MOTORS, "DUAL_MOTORS");
	genCode(LR_TACKLE_PERIPHERALS, "LR_TACKLE_PERIPHERALS");
	genCode(CENTER_PERIPHERALS, "CENTER_PERIPHERALS");
	genCode(QB_PERIPHERALS, "QB_PERIPHERALS");
	genCode(IR_MAST, "IR_MAST");
	genCode(QB_TRACKING, "QB_TRACKING");
	genCode(KICKER_PERIPHERALS, "KICKER_PERIPHERALS");
	genCode(RECEIVER_PERIPHERALS, "RECEIVER_PERIPHERALS");
	genCode(LED_STRIP, "LED_STRIP");
	genCode(TACKLE, "TACKLE");


	while (true);
    return;
}


#include <string>
#include <vector>
#include <iostream>

using namespace std;


void genCode(vector<string> robotType, string toDefine) {
	/*
	prints out
	#if defined(ROBOT_NUMBER_FirstNumber) || ... || defined(ROBOT_NUMBER_LastNumber)
		#define toDefine
	#endif
	*/
	
	if (robotType.empty()) return; // if no robots need this property defined do nothing and return

	cout << "#if ";

		for (vector<string>::iterator it = robotType.begin(); it != robotType.end(); it++) { // starting at the begining of each vector itterate through the whole vector 
			string robotNumber = *it;	//put the number of the robot into a local vatiable
			cout << "defined(ROBOT_NUMBER_" << robotNumber << ")";  
			if (it+1 != robotType.end()) cout << " || "; // if the loop is not on its last iteration print out a || (or)
			//if (robotNumber != robotType.back()) cout << " || ";

		}
		cout << endl << "	#define " << toDefine << endl;
		cout << "#endif" << endl;
		return;

}

void main()
{
	// DO NOT RELY ON THESE they are based on a potentally faulty memory VERIFY and remove this comment
	vector<string> BASIC_DRIVETRAIN = { "9", "16", "35", "40", "42", "44", "56", "68", "74", "75", "81", "85", "88", "K9" };
	vector<string> DUAL_MOTORS = { "35" };
	vector<string> LR_TACKLE_PERIPHERALS = {};
	vector<string> OMNIWHEEL_DRIVETRAIN = { "7", "12", "82" };
	vector<string> CENTER_PERIPHERALS = { "42", "68" };
	vector<string> QB_PERIPHERALS = { "7", "82" };
	vector<string> IR_MAST = { "12" };
	vector<string> QB_TRACKING = { "7", "82" };
	vector<string> KICKER_PERIPHERALS = {};
	vector<string> RECEIVER_PERIPHERALS = {};
	vector<string> LED_STRIP = { "9", "12", "16", "35", "40", "42", "44", "74", "75", "81", "82", "85", "88", "K9" };
	vector<string> TACKLE = { "12", "16", "35", "40", "85", "88", "K9" };

	genCode(BASIC_DRIVETRAIN, "BASIC_DRIVETRAIN");
	genCode(DUAL_MOTORS, "DUAL_MOTORS");
	genCode(LR_TACKLE_PERIPHERALS, "LR_TACKLE_PERIPHERALS");
	genCode(OMNIWHEEL_DRIVETRAIN, "OMNIWHEEL_DRIVETRAIN  ");
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


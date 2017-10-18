#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>


using namespace std;

bool compare(string a, string b) {
	return (a.compare(b) < 0);
}

void genCheckIfRobotNameIsListed(vector<string>* robotList) {
	std::sort(robotList->begin(), robotList->end(), compare);

	cout << "#if ";

	for (vector<string>::iterator it = robotList->begin(); it != robotList->end(); it++) {
		cout << "!defined(ROBOT_NUMBER_" << *it << ")";
		if (it + 1 != robotList->end()) cout << " && "; // if the loop is not on its last iteration print out a && (and)
	}
	cout << endl << "	#warning Robot Number Does not Match any known Robot Configuration" << endl;
	cout << "#endif" << endl;
}

void genMultipleRobotErrorCheck(vector<string> *robotList) {
	/*
	takes a pointer to a list of strings

	prints out C/C++ Preprocessor statments that throw and error when more than
	one string in that list is defined
	*/

	std::sort(robotList->begin(), robotList->end(), compare);
	string errorMessage = "#error more than one robot number is defined";
	for (auto it = robotList->begin(); it != robotList->end(); it++) {
		cout << "#if defined(ROBOT_NUMBER_" << *it << ") && (";
		for (auto it2 = robotList->begin(); it2 != robotList->end(); it2++) {
			if (it != it2) cout << " defined(ROBOT_NUMBER_" << *it2 << ")";
			if (it2 + 1 != robotList->end() && ((it != it2 +1 ) )) {
				cout << " || ";
			}
		}
		cout << ")" << endl << "	" << errorMessage << endl;
		cout << "#endif " << endl;
	}
}


void genCode(vector<string> robotNumbers, string YourDefineHere, vector<string> *robotList) {
	/*
	prints out
	#if defined(ROBOT_NUMBER_FirstNumber) || ... || defined(ROBOT_NUMBER_LastNumber)
		#define YourDefineHere
	#endif
	*/
	
	if (robotNumbers.empty()) return; // if no robots need this property defined do nothing and return

	cout << "#if ";

	for (vector<string>::iterator it = robotNumbers.begin(); it != robotNumbers.end(); it++) { // starting at the begining of each vector itterate through the whole vector 
		string robotNumber = *it;	//put the number of the robot into a local vatiable
		cout << "defined(ROBOT_NUMBER_" << robotNumber << ")";  
		if (it+1 != robotNumbers.end()) cout << " || "; // if the loop is not on its last iteration print out a || (or)
		if (find(robotList->begin(), robotList->end(), *it) == robotList->end()) {
			robotList->push_back(*it);
		}
	}
	cout << endl << "	#define " << YourDefineHere << endl;
	cout << "#endif" << endl;	
	return;

}

void main()
{
	// DO NOT RELY ON THESE they are based on a potentally faulty human memory VERIFY and remove this comment
	vector<string> BASIC_DRIVETRAIN = {"3", "9",  "35", "40", "42", "44", "56", "74", "75", "81", "85", "88", "K9" };
	vector<string> DUAL_MOTORS = {};
	vector<string> LR_TACKLE_PERIPHERALS = {};
	vector<string> OMNIWHEEL_DRIVETRAIN = { "7", "12", "16", "82" };
	vector<string> CENTER_PERIPHERALS = { "42" };
	vector<string> QB_PERIPHERALS = { "7", "82" };
	vector<string> IR_MAST = { "86" };
	vector<string> QB_TRACKING = { "7", "82" };
	vector<string> KICKER_PERIPHERALS = {"3"};
	vector<string> RECEIVER_PERIPHERALS = {"86"};
	vector<string> LED_STRIP = { "7", "9", "12", "16", "35", "40", "42", "44", "56", "74", "75", "81", "82", "85", "88", "K9" };
	vector<string> TACKLE = { "7", "12", "16", "35", "40", "56", "82", "85", "88", "K9" };
	vector<string> NEW_CENTER_PERIPHERALS = { "68" };
	vector<string> NEW_KICKER_PERIPHERALS = { "6" };

	vector<string> robotList;


	genCode(BASIC_DRIVETRAIN, "BASIC_DRIVETRAIN", &robotList);
	genCode(DUAL_MOTORS, "DUAL_MOTORS", &robotList);
	genCode(LR_TACKLE_PERIPHERALS, "LR_TACKLE_PERIPHERALS", &robotList);
	genCode(OMNIWHEEL_DRIVETRAIN, "OMNIWHEEL_DRIVETRAIN", &robotList);
	genCode(CENTER_PERIPHERALS, "CENTER_PERIPHERALS", &robotList);
	genCode(QB_PERIPHERALS, "QB_PERIPHERALS", &robotList);
	genCode(IR_MAST, "IR_MAST", &robotList);
	genCode(QB_TRACKING, "QB_TRACKING", &robotList);
	genCode(KICKER_PERIPHERALS, "KICKER_PERIPHERALS", &robotList);
	genCode(RECEIVER_PERIPHERALS, "RECEIVER_PERIPHERALS", &robotList);
	genCode(LED_STRIP, "LED_STRIP", &robotList);
	genCode(TACKLE, "TACKLE", &robotList);
	genCode(NEW_CENTER_PERIPHERALS, "NEW_CENTER_PERIPHERALS", &robotList);
	genCode(NEW_KICKER_PERIPHERALS, "NEW_KICKER_PERIPHERALS", &robotList);

	genCheckIfRobotNameIsListed(&robotList);

	cout << endl << endl << endl;

	genMultipleRobotErrorCheck(&robotList);


	while (true);
    return;
}


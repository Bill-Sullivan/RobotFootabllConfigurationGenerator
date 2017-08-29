#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;

bool compare(string a, string b) {
	return (a.compare(b) < 0);
}

void multipleRobotErrorCheck(vector<string> *robotList) {
	std::sort(robotList->begin(), robotList->end(), compare);
	string errorMessage = "#error more than one robot number is defined";
	for (auto it = robotList->begin(); it != robotList->end()-1; it++) {
		string indentation = "";
		cout << indentation << "#if defined(ROBOT_NUMBER_" << *it << ")" << endl;
		indentation += "	";
		cout << indentation << "#if defined(ROBOT_NUMBER_" << *(it + 1) << ")" << endl;
		indentation += "	";
		cout << indentation << errorMessage << endl;
		indentation.erase(indentation.begin());
	
		for (auto it2 = it+2; it2 != robotList->end(); it2++)	{
			cout << indentation << "#elif defined(ROBOT_NUMBER_" << *it2 << ")" << endl;
			indentation += "	";
			cout << indentation << errorMessage << endl;
			indentation.erase(indentation.begin());
		}
		cout << "	" << "#endif" << endl;
		indentation.erase(indentation.begin());
		cout << "#endif" << endl;
	}

}

void genCode(vector<string> robotNumbers, string toDefine, vector<string> *robotList) {
	/*
	prints out
	#if defined(ROBOT_NUMBER_FirstNumber) || ... || defined(ROBOT_NUMBER_LastNumber)
		#define toDefine
	#endif
	*/
	
	if (robotNumbers.empty()) return; // if no robots need this property defined do nothing and return

	cout << "#if ";

	for (vector<string>::iterator it = robotNumbers.begin(); it != robotNumbers.end(); it++) { // starting at the begining of each vector itterate through the whole vector 
		string robotNumber = *it;	//put the number of the robot into a local vatiable
		cout << "defined(ROBOT_NUMBER_" << robotNumber << ")";  
		if (it+1 != robotNumbers.end()) cout << " || "; // if the loop is not on its last iteration print out a || (or)
		//if (robotNumber != robotNumbers.back()) cout << " || ";
		if (find(robotList->begin(), robotList->end(), *it) == robotList->end()) {
			robotList->push_back(*it);
		}
	}
	cout << endl << "	#define " << toDefine << endl;
	cout << "#endif" << endl;	
	return;

}

void main()
{
	// DO NOT RELY ON THESE they are based on a potentally faulty memory VERIFY and remove this comment
	vector<string> BASIC_DRIVETRAIN = { "9",  "35", "40", "42", "44", "56", "68", "74", "75", "81", "85", "88", "K9" };
	vector<string> DUAL_MOTORS = { "35" };
	vector<string> LR_TACKLE_PERIPHERALS = {};
	vector<string> OMNIWHEEL_DRIVETRAIN = { "7", "12", "16", "82" };
	vector<string> CENTER_PERIPHERALS = { "42", "68" };
	vector<string> QB_PERIPHERALS = { "7", "82" };
	vector<string> IR_MAST = { "12" };
	vector<string> QB_TRACKING = { "7", "82" };
	vector<string> KICKER_PERIPHERALS = {};
	vector<string> RECEIVER_PERIPHERALS = {};
	vector<string> LED_STRIP = { "7", "9", "12", "16", "35", "40", "42", "44", "56", "74", "75", "81", "82", "85", "88", "K9" };
	vector<string> TACKLE = { "7", "12", "16", "35", "40", "56", "82", "85", "88", "K9" };

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

	cout << "#if " ;

	for (vector<string>::iterator it = robotList.begin(); it != robotList.end(); it++) {
		cout << "!defined(ROBOT_NUMBER_" << *it << ")";  
		if (it + 1 != robotList.end()) cout << " && "; // if the loop is not on its last iteration print out a || (or)
	}
	cout << endl << "	#warning Robot Number Does not Match any known Robot Configuration" << endl;
	cout << "#endif" << endl;

	multipleRobotErrorCheck(&robotList);

	while (true);
    return;
}


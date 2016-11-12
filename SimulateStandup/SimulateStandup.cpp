#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<float> objtempV;
vector<float> ambTempV;

void populateData(vector<float>& vec, string sourceFile) {
	string line;
	ifstream myfile(sourceFile);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			//line to char array
			char charArray[10];
			char * part;
			strcpy(charArray, line.c_str());

			//Split char array w. delimiter ","
			part = strtok(charArray, ",");

			//Convert to float and push in vector
			float tmp = stof(part);
			vec.push_back(tmp);
		}
	}
	else {
		cout << "Unable to open file: " << sourceFile;
	}
}

int main() {
	//Read data from files
	populateData(objtempV, "OBJTEMP2.txt");
	populateData(ambTempV, "AMBTEMP2.txt");

	int smallestVector = (objtempV.size() > ambTempV.size()) ? ambTempV.size() : objtempV.size();
	ofstream resultFile;
	resultFile.open("result.txt");

	//Declare "global" variables for your algoritm
	float filteredObjTemp = 0;
	float filteredAmbTemp = 0;

	for (int i = 0; i < smallestVector; i++) {
		//Read "current samples"
		float objTemp = objtempV[i];
		float ambTemp = ambTempV[i];

		//Apply algoritms
		filteredObjTemp = filteredObjTemp * 0.99 + objTemp * 0.01;
		filteredAmbTemp = filteredAmbTemp * 0.99 + ambTemp * 0.01;
		float diff = abs(objTemp - ambTemp);
		bool isPresent = 0;
		if (diff > 0) {
			isPresent = 1;
		}

		//Save to result to file
		resultFile << diff << endl;
	}
	resultFile.close();

	return 0;
}
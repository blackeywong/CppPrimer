// CP8.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

void readFtoS_ss(string file) {
	ifstream input(file);
	vector<string> v;
	string str;
	while (getline(input, str)) {
		v.push_back(str);
	}

	istringstream ss;
	for (string str : v) {
		//stringstream ss(str);
		ss.str(str);
		string word;
		while (ss >> word)
			cout << word << endl;
		ss.clear();
	}

}

void readFtoS_line(string file) {
	ifstream input(file);
	vector<string> v;
	string s;
	while (getline(input,s)) {
		v.push_back(s);
	}

	for (string str : v) {
		cout << str << endl;
	}

}

void readFtoS(string file) {
	ifstream input(file);
	vector<string> v;
	string s;
	while (input) {
		input >> s;
		v.push_back(s);
	}
	
	for (string str : v) {
		cout << str << endl;
	}

}

int main()
{
	//readFtoS_ss("G:\\boot.ini");
	//readFtoS_line("G:\\boot.ini");
	//readFtoS("G:\\boot.ini");
	const vector<int> v1(5,10);
	//v1.push_back(10);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

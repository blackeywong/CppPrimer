// CP13.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include "String.h"
#include "HasPtr.h"
#include "StrVec.h"
using namespace std;

class Employee {
	friend ostream& operator<<(ostream& out, Employee& e);
public:
	Employee(string name = "") { ID = ++IDproducer; this->name = name; }
	Employee(const Employee& e) :Employee() { name = e.name; }
	Employee& operator=(const Employee& e) { ID = ++IDproducer; name = e.name; return *this; }
private:
	int ID;
	string name;
	static int IDproducer;
};

int Employee::IDproducer = 0;

ostream& operator<<(ostream& out, Employee& e) {
	out << "Employee ID and name: " << e.ID << " " << e.name;
	return out;
}
//13.58
class Foo {
	friend istream& operator>>(istream& in, Foo& f);
	friend ostream& operator<<(ostream& out, const Foo& f);
public:
	Foo sorted() &&;
	Foo sorted() const &;
private:
	vector<int> data;
};

Foo Foo::sorted() && {
	cout << "right value" << endl;
	sort(data.begin(), data.end());
	return *this;
}

Foo Foo::sorted() const & {
	cout << "left value" << endl;
	Foo ret(*this);
	//sort(ret.data.begin(), ret.data.end());
	//return ret;
	//return ret.sorted();//13.56
	return Foo(*this).sorted();//13.57
}

istream& operator>>(istream& in, Foo& f) {
	istream_iterator<int> ii(in), eof;
	copy(ii, eof, back_inserter(f.data));
	return in;
}

ostream& operator<<(ostream& out, const Foo& f) {
	copy(f.data.begin(), f.data.end(), ostream_iterator<int>(out, " "));
	return out;
}


int main()
{
	Employee a(string("hello"));
	cout << a << endl;
	Employee b(a);
	cout << b << endl;
	Employee c = b;
	cout << c << endl;

	//13.44
	cout << "Exercise 13.44" << endl;
	String s1;
	cout << s1 << endl;
	String s2("test");
	cout << s2 << endl;
	//13.48
	cout << "Exercise 13.48" << endl;
	vector<String> v48;
	v48.push_back("1");
	v48.push_back("2");
	v48.push_back("3");
	v48.push_back("4");
	//13.49
	cout << "Exercise 13.49" << endl;
	String s3(std::move(s2));
	cout << s2 << endl;
	cout << s3 << endl;
	String s4 = s3;
	cout << s3 << endl;
	cout << s4 << endl;
	s4 = std::move(s3);
	cout << s3 << endl;
	cout << s4 << endl;
	cout << "Exercise 13.54" << endl;
	HasPtr hp1(string("hp1"));
	cout << hp1 << endl;
	HasPtr hp2;
	//hp2 = hp1;
	cout << hp1 << endl;
	cout << hp2 << endl;
	HasPtr hp3;
	hp3 = std::move(hp1);
	cout << hp1 << endl;
	cout << hp3 << endl;

	cout << "Exercise 13.58" << endl;
	string s58("3 7 9 2 1 5 8");
	istringstream iss58(s58);
	Foo f58;
	iss58 >> f58;
	cout << f58 << endl;
	Foo f59 = f58.sorted();
	Foo f60 = std::move(f59).sorted();
	cout << f60 << endl;

	cout << "Exercise 16.58" << endl;
	StrVec sv;
	sv.emplace_back(10, 'c');
	sv.emplace_back(std::string("hi"));
	for_each(sv.begin(), sv.end(), [](std::string& s) {std::cout << s << ", "; });
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

// CP14.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <functional>
#include <map>
#include <functional>
//#include <regex>
//14.34
class func1 {
public:
	int operator()(bool cond, int a, int b) { return cond ? a : b; }

};

//14.35
class ReadString {
public:
	ReadString(std::istream& in = std::cin) : in(in) {}
	std::string operator()() { std::string s;  std::getline(in, s); return s; }
private:
	std::istream& in;
};

//14.37
class IfEqual {
public:
	IfEqual(char c) :c(c){}
	bool operator()(char a) { return a == c; }
private:
	char c;
};

//14.38
class StrLen {
public:
	StrLen(std::size_t sz) :sz(sz) {}
	bool operator()(std::string s) { return s.size() == sz; }
private:
	std::size_t sz;
};

//14.44
class Calculator {
public:
	Calculator() {
		bi_op.insert({ std::string("+"), std::plus<int>()});
		bi_op.insert({ std::string("-"), std::minus<int>() });
		bi_op.insert({ std::string("*"), std::multiplies<int>() });
		bi_op.insert({ std::string("/"), std::divides<int>() });
		bi_op.insert({ std::string("%"), std::modulus<int>() });
	}
	void run() {
		std::string s;
		while (true) {
			std::cout << "Input an expression like: 2 * 3<Enter>." << std::endl;
			std::getline(std::cin, s);
			if (s == "q" || s == "Q") {
				std::cout << "quit." << std::endl;
				break;
			}
			std::istringstream iss(s);
			int num1, num2;
			std::string op;
			iss >> num1 >> op >> num2;
			std::cout << bi_op[op](num1, num2) << std::endl;

		}
	}
private:
	std::map<std::string, std::function<int(int,int)>> bi_op;
};

int main()
{
	//14.36
	std::vector<std::string> v1;

	std::string s1("1 2 3\n4 5 6\n7 8 9\n");
	std::cout << s1 << std::endl;
	std::stringstream ss1(s1);
	ReadString rs(ss1);

	while (ss1) {
		std::string s = rs();
		v1.push_back(s);
	}

	copy(v1.begin(), v1.end(), std::ostream_iterator<std::string>(std::cout, " "));
	std::cout << std::endl;

	std::cout << "Exercise 14.37" << std::endl;
	std::string s37("show me the meaning");
	std::replace_copy_if(s37.begin(), s37.end(), s37.begin(), IfEqual('e'), 'E');
	std::cout << s37 << std::endl;

	std::cout << "Exercise 14.38" << std::endl;
	std::fstream file("adminguide.txt");
	std::vector<int> vNum(12, 0);

	//std::string s;
	//while (file >> s) {
	//	int l = s.size();
	//	if (l <= 10) {
	//		++vNum[s.size()];
	//	}
	//	else {
	//		++vNum[11];
	//	}
	//}
	//for (int i = 1; i <= 10; i++) {
	//	std::cout << "Count of words with length " << i << " is: " << vNum[i] << "." << std::endl;
	//}
	//std::cout << "Count of words longer than 11 is: " << vNum[11] << "." << std::endl;


	std::istream_iterator<std::string> fit(file), eof;
	std::vector<std::string> vfile;
	copy(fit, eof, std::back_inserter(vfile));
	for (int i = 1; i <= 10; i++) {
		//std::cout << "Count of words with length " << i << " is: " << std::count_if(vfile.begin(),vfile.end(), StrLen(i)) << "." << std::endl;
	}
	
	//14.42
	std::vector<int> v42 = {5, 123, 1024, 3048, 1, 3456};
	std::cout << std::count_if(v42.begin(), v42.end(), bind(std::greater<int>(), std::placeholders::_1, 1024)) << std::endl;

	std::cout << *(std::find_if(v1.begin(), v1.end(), bind(std::not_equal_to<std::string>(), std::placeholders::_1, "pooh"))) << std::endl;

	std::transform(v42.begin(), v42.end(), v42.begin(), bind(std::multiplies<int>(), std::placeholders::_1, 2));

	std::for_each(v42.begin(), v42.end(), [](int i) {std::cout << i << " "; });
	std::cout << std::endl;

	//14.43
	if (std::find_if(v42.begin(), v42.end(), std::bind(std::modulus<int>(), std::placeholders::_1, 2)) == v42.end()) {
		std::cout << "all divisable" << std::endl;
	}
	else {
		std::cout << "find not divisable" << std::endl;
	}

	//14.42
	Calculator cal;
	cal.run();
}


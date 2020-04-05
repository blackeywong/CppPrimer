// CP11.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

#include "sales_data.h"
using namespace std;

//Exercise 11.3
set<string> excludes = { "A", "a", "An", "an", "The", "the", "But", "but", "And", "and" };
void countWord(vector<string>& v) {
	map<string, int> cntMap;
	for (string s : v) {
		if (excludes.find(s) == excludes.end())
		{
			cntMap[s]++;
		}
	}

	for (auto p : cntMap) {
		cout << "Word: " + p.first << " occurs " << p.second << " time(s)." << endl;
	}
}

//Exercise 11.4
set<string> exclude2 = { "a", "an", "the", "but", "and" };
void countWord2(vector<string>& v) {
	map<string, int> cntMap;
	for (string s : v) {
		auto it = stable_partition(s.begin(),s.end(),isalnum);//remove punctuations
		s.erase(it, s.end());
		transform(s.begin(), s.end(), s.begin(), tolower);//transition to lower case
		if (excludes.find(s) == excludes.end())
		{
			cntMap[s]++;
		}
	}

	for (auto p : cntMap) {
		cout << "Word: " + p.first << " occurs " << p.second << " time(s)." << endl;
	}
}

//Exercise 11.20
void countWord3(vector<string>& v) {
	map<string, int> cntMap;
	for (string s : v) {
		auto it = stable_partition(s.begin(), s.end(), isalnum);//remove punctuations
		s.erase(it, s.end());
		transform(s.begin(), s.end(), s.begin(), tolower);//transition to lower case
		if (excludes.find(s) == excludes.end())
		{
			auto p = cntMap.insert(make_pair(s, 1));
			if (p.second == false) {
				++cntMap[s];
				//++p.first->second;
			}
		}

	}
	for (auto p : cntMap) {
		cout << "Word: " + p.first << " occurs " << p.second << " time(s)." << endl;
	}

}

//Exercise 11.33
void transformWords(ifstream& source, ifstream& rule) {
	string line;
	map<string, string> rulemap;
	while (getline(rule, line)) {
		string key, value;
		key = line.substr(0, line.find(" "));
		value = line.substr(line.find(" ") + 1);
		rulemap[key] = value;
	}

	vector<string> v33;
	while (getline(source, line)) {
		string resultline = "";
		string::size_type b = 0, e = line.find(" ");
		while (true) {
			string word = line.substr(b, e - b);
			if (rulemap.find(word) != rulemap.end()) {
				resultline += rulemap[word];
			}
			else {
				resultline += word;
			}
			resultline += " ";
			b = line.find(" ", b);
			if (b == string::npos) break;
			b++;
			e = line.find(" ", b);
			if (e == string::npos) {
				e = line.size();
			}
		}

		v33.push_back(resultline.substr(0, resultline.size() - 1));
	}
	for (string line : v33) {
		cout << line << endl;
	}
}

//Exercise 11.38
unordered_set<string> exclude4 = { "a", "an", "the", "but", "and" };
void countWord4(vector<string>& v) {
	unordered_map<string, int> cntMap;

	for (string word : v) {
		auto it = stable_partition(word.begin(), word.end(), isalnum);
		word.erase(it, word.end());
		word[0] = tolower(word[0]);
		if (exclude4.find(word) == exclude4.end()) {
			cntMap[word]++;
		}
	}

	for_each(cntMap.begin(), cntMap.end(), [](pair<string, int> p) {cout << "Word: " + p.first << " occurs " << p.second << " time(s)." << endl; });
}

//Exercise 11.38
void transformWords2(ifstream& source, ifstream& rule) {
	unordered_map<string, string> ruleset;
	string line;
	while (getline(rule, line)) {
		istringstream iss(line);
		string key, value;
		iss >> key;
		getline(iss, value);
		value = value.substr(1);
		ruleset[key] = value;
	}

	vector<string> result;
	while (getline(source, line)) {
		string transformed = "";
		istringstream iss(line);
		string word;
		while (iss >> word) {
			auto res = ruleset.find(word);
			if (res != ruleset.end()) {
				transformed += ruleset[word];
			}
			else {
				transformed += word;
			}
			transformed += " ";
		}
		transformed.erase(transformed.end() - 1);
		result.push_back(transformed);
	}

	for_each(result.begin(), result.end(), [](string s) {cout << s << endl; });

}

int main()
{
	ifstream in("a.txt");
	vector<string> v;
	auto bi = back_inserter(v);
	istream_iterator<string> it(in), eof;
	copy(it, eof, bi);
	in.close();

	//Exercise 11.3
	//countWord(v);
	//Exercise 11.4
	//countWord2(v);
	
	//Exercise 11.11
	multiset<Sales_data, decltype(compareIsbn)*> bookstore(compareIsbn);
	multiset<Sales_data, bool (*)(const Sales_data&, const Sales_data&)> bookstore2(compareIsbn);

	//Exercise 11.12
	vector<pair<string, int> > v12;

	//Exercise 11.13
	string s13("a");
	int n13 = 1;
	auto p = make_pair(s13, n13);
	pair<string, int> p13(s13, n13);

	//Exercise 11.14
	map<string, vector<pair<string, string> > > family; //map<lastName, vector<pair<firstName, birthday>>>

	//Exercise 11.16
	map<string, int> m;
	m["a"] = 1;
	map<string, int>::iterator it16 = m.begin();
	m[*it] = 2;

	//Exercise 11.17
	cout << "Exercise 11.17" << endl;
	multiset<string> c17{"a", "a","b"};
	vector<string> v17{"c", "c", "d"};
	//copy(v17.begin(), v17.end(), inserter(c17, c17.end()));
	//copy(v17.begin(), v17.end(), back_inserter(c17));//wrong!!
	//copy(c17.begin(), c17.end(), inserter(v17, v17.end()));
	copy(c17.begin(), c17.end(), back_inserter(v17));
	copy(c17.begin(), c17.end(), ostream_iterator<string>(cout, " "));
	cout << endl;
	copy(v17.begin(), v17.end(), ostream_iterator<string>(cout, " "));
	cout << endl;

	//Exercise 11.18
	map<string, int> word_count;
	map<string, int>::iterator it18 = word_count.begin();

	//Exercise 11.19
	set<Sales_data, bool(*)(const Sales_data&, const Sales_data&)>::iterator it19 = bookstore.begin();

	//Exercise 11.20
	countWord3(v);

	//Exercise 11.21
	map<string, vector<int>> m21;
	pair<map<string,vector<int>>::iterator, bool> p21 = m21.insert({ "a", {1,2} });
	//para: pair<string, vector<int>>
	//return: ppair<map<string,vector<int>>::iterator, bool>

	//Exercise 11.28
	map<string, vector<int>> m28;
	map<string, vector<int>>::iterator p28 = m28.find("a");

	//Exercise 11.31
	multimap<string, string> m31;
	m31.insert(make_pair("a", "B"));
	m31.insert(make_pair("a", "A"));
	m31.insert(make_pair("b", "B"));
	auto m31_bak(m31);
	for_each(m31.begin(), m31.end(), [](pair<string,string> p) {cout << p.first << ": " << p.second << endl; });
	auto p31 = m31.equal_range("c");
	m31.erase(p31.first, p31.second);
	for_each(m31.begin(), m31.end(), [](pair<string, string> p) {cout << p.first << ": " << p.second << endl; }); 
	p31 = m31.equal_range("a");
	m31.erase(p31.first, p31.second);
	for_each(m31.begin(), m31.end(), [](pair<string, string> p) {cout << p.first << ": " << p.second << endl; });

	//Exercise 11.32
	cout << "Exercise 11.32" << endl;
	auto m32(m31_bak);
	string s32 = "";
	vector<string> v32;
	auto cur = m32.begin();
	for (; cur != m32.end(); cur++) {
		if (s32 == "") {
			s32 = cur->first;
			v32.push_back(cur->second);
		}
		else if (s32 == cur->first) {
			v32.push_back(cur->second);
		}
		else {
			cout << s32 << ": ";
			sort(v32.begin(), v32.end());
			copy(v32.begin(), v32.end(), ostream_iterator<string>(cout, " "));
			cout << endl;
			s32 = cur->first;
			v32.clear();
			v32.push_back(cur->second);
		}
	}
	cout << s32 << ": ";
	sort(v32.begin(), v32.end());
	copy(v32.begin(), v32.end(), ostream_iterator<string>(cout, " "));
	cout << endl;

	//Exercise 11.33
	cout << "Exercise 11.33" << endl;
	ifstream source("source.txt");
	ifstream rule("rule.txt");
	transformWords(source, rule);
	source.close();
	rule.close();

	//Exercise 11.38
	cout << "Exercise 11.38" << endl;
	countWord4(v);
	ifstream source2("source.txt");
	ifstream rule2("rule.txt");
	transformWords2(source2, rule2);

	source2.close();
	rule2.close();

}

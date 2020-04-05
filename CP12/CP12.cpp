// CP12.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <memory>
#include <set>
#include <algorithm>
#include <map>

#include "StrBlob.h"
using namespace std;

//Exercise 12.6
vector<int>* f1() {
	return new vector<int>();
}

vector<int>& f2(vector<int>& v) {
	int n;
	while (cin >> n) {
		v.push_back(n);
	}
	return v;
}

void f3(vector<int>& v) {
	for_each(v.begin(), v.end(), [](int n) {cout << n << " "; });
		cout << endl;
	delete& v;
}

//Exercise 12.7
shared_ptr<vector<int>> f11(){
	return make_shared<vector<int>>();
}

shared_ptr<vector<int>> f22(shared_ptr<vector<int>> pv) {
	int n;
	while (cin >> n) {
		pv->push_back(n);
	}
	return pv;
}

void f33(shared_ptr<vector<int>> pv) {
	copy(pv->begin(), pv->end(), ostream_iterator<int>(cout, " "));
	cout << endl;
}

//Exercise 12.14
struct destination {};
struct connection {};
connection* connect(destination* d) { connection* c = new connection(); return c; }
void disconnect(connection& c) { delete &c; }
void delete_connection(connection* c) {
	disconnect(*c);
}
void f(destination& d) {
	connection* c = connect(&d);
	shared_ptr<connection> p(c, delete_connection);
	//...
}
//Exercise 12.15
void f2(destination& d) {
	shared_ptr<connection> p(connect(&d), [](connection* c) {disconnect(*c); });
	//...
}

//Exercise 12.23
char* concat1(char* s1, char* s2) {
	size_t len1 = strlen(s1);
	size_t len2 = strlen(s2);
	char* res = new char[len1 + len2 +1];
	copy(s1, s1 + len1, res);
	copy(s2, s2 + len2, res + len1);
	res[len1 + len2] = '\0';
	return res;
}

string* concat2(string& s1, string& s2) {
	string* s3 = new string(s1 + s2);
	return s3;
}

////Exercise 12.27
//class QueryResult;
//class TextQuery {
//	friend class QueryResult;
//public:
//	TextQuery(string& filename);
//	void query(string& searchfor);
//protected:
//	vector<string> text;
//	map<string, int> countmap;
//	map<string, set<int>> linemap;
//};
//
//TextQuery::TextQuery(string& filename) {
//	ifstream in(filename);
//	string s;
//	while (getline(in, s)) {
//		text.push_back(s);
//	}
//	in.close();
//}
//
//void TextQuery::query(string& searchfor) {
//	if (linemap.find(searchfor) != linemap.end()) return;
//
//	set<int> lines;
//	int cnt = 0;
//	for (int i = 0; i < text.size(); i++) {
//		int number = 0;
//		auto b = text[i].begin();
//		while (b != text[i].end()) {
//			auto it = search(b, text[i].end(), searchfor.begin(), searchfor.end());
//			if (it != text[i].end()) {
//				number++;
//				b = it + 1;
//			}
//			else
//				break;
//		}
//		if (number != 0) {
//			lines.insert(i + 1);
//			cnt += number;
//		}
//	}
//	linemap[searchfor] = lines;
//	countmap[searchfor] = cnt;
//}
//
//
//class QueryResult {
//public:
//	void printResult(TextQuery& tq, string& searchfor);
//};
//
//void QueryResult::printResult(TextQuery& tq, string& searchfor) {
//	cout << searchfor << " appears " << tq.countmap[searchfor] << " times." << endl;
//	for (auto p = tq.linemap[searchfor].begin(); p != tq.linemap[searchfor].end(); p++) {
//		cout << "(line " << *p << ") " << tq.text[*p-1] << endl;
//	}
//}

////Exercise 12.30
//class QueryResult;
//class TextQuery {
//	friend class QueryResult;
//public:
//	TextQuery(string& filename);
//	TextQuery(istream& infile);
//	QueryResult query(string& searchfor);
//protected:
//	shared_ptr<vector<string>> text;
//	map<string, shared_ptr<pair<int, set<int>>>> resultmap;
//};
//
//class QueryResult {
//public:
//	QueryResult(string& sf, TextQuery& tq) :searchfor(sf), text(tq.text), result(tq.resultmap[searchfor]) {}
//	ostream& printResult(ostream& out);
//protected:
//	string searchfor;
//	shared_ptr<vector<string>> text;
//	shared_ptr<pair<int, set<int>>> result;
//};
//
//TextQuery::TextQuery(string& filename) {
//	text = make_shared<vector<string>>();
//	ifstream in(filename);
//	string s;
//	while (getline(in, s)) {
//		text->push_back(s);
//	}
//	in.close();
//}
//
//TextQuery::TextQuery(istream& infile) {
//	text = make_shared<vector<string>>();
//	string s;
//	while (getline(infile, s)) {
//		text->push_back(s);
//	}
//}
//
//QueryResult TextQuery::query(string& searchfor) {
//	if (resultmap.find(searchfor) != resultmap.end()) return QueryResult(searchfor, *this);
//
//	set<int> lines;
//	int cnt = 0;
//	for (int i = 0; i < text->size(); i++) {
//		int number = 0;
//		auto b = (*text)[i].begin();
//		while (b != (*text)[i].end()) {
//			auto it = search(b, (*text)[i].end(), searchfor.begin(), searchfor.end());
//			if (it != (*text)[i].end()) {
//				number++;
//				b = it + 1;
//			}
//			else
//				break;
//		}
//		if (number != 0) {
//			lines.insert(i + 1);
//			cnt += number;
//		}
//	}
//	resultmap[searchfor] = make_shared<pair<int, set<int>>>(cnt, lines);
//	return QueryResult(searchfor, *this);
//}
//
//
//ostream& QueryResult::printResult(ostream& out) {
//	out << searchfor << " appears " << result->first << " times." << endl;
//	for (auto p = result->second.begin(); p != result->second.end(); p++) {
//		cout << "(line " << *p << ") " << (*text)[*p - 1] << endl;
//	}
//	return out;
//}
//
//ostream& print(ostream& out, QueryResult& qr) {
//	qr.printResult(out);
//	return out;
//}

////Exercise 12.32
//class QueryResult;
//class TextQuery {
//	friend class QueryResult;
//public:
//	TextQuery(string& filename);
//	TextQuery(istream& infile);
//	QueryResult query(string& searchfor);
//protected:
//	shared_ptr<StrBlob> text;
//	map<string, shared_ptr<pair<int, set<int>>>> resultmap;
//};
//
//class QueryResult {
//public:
//	QueryResult(string& sf, TextQuery& tq) :searchfor(sf), text(tq.text), result(tq.resultmap[searchfor]) {}
//	ostream& printResult(ostream& out);
//protected:
//	string searchfor;
//	shared_ptr<StrBlob> text;
//	shared_ptr<pair<int, set<int>>> result;
//};
//
//TextQuery::TextQuery(string& filename) {
//	text = make_shared<StrBlob>();
//	ifstream in(filename);
//	string s;
//	while (getline(in, s)) {
//		text->push_back(s);
//	}
//	in.close();
//}
//
//TextQuery::TextQuery(istream& infile) {
//	text = make_shared<StrBlob>();
//	string s;
//	while (getline(infile, s)) {
//		text->push_back(s);
//	}
//}
//
//QueryResult TextQuery::query(string& searchfor) {
//	if (resultmap.find(searchfor) != resultmap.end()) return QueryResult(searchfor, *this);
//
//	set<int> lines;
//	int cnt = 0;
//	for (int i = 0; i < text->size(); i++) {
//		int number = 0;
//		string line = (*text).at(i);
//		auto b = line.begin();
//		while (b != line.end()) {
//			auto it = search(b, line.end(), searchfor.begin(), searchfor.end());
//			if (it != line.end()) {
//				number++;
//				b = it + 1;
//			}
//			else
//				break;
//		}
//		if (number != 0) {
//			lines.insert(i + 1);
//			cnt += number;
//		}
//	}
//	resultmap[searchfor] = make_shared<pair<int, set<int>>>(cnt, lines);
//	return QueryResult(searchfor, *this);
//}
//
//
//ostream& QueryResult::printResult(ostream & out) {
//	out << searchfor << " appears " << result->first << " times." << endl;
//	for (auto p = result->second.begin(); p != result->second.end(); p++) {
//		cout << "(line " << *p << ") " << (*text).at(*p - 1) << endl;
//	}
//	return out;
//}
//
//ostream& print(ostream & out, QueryResult & qr) {
//	qr.printResult(out);
//	return out;
//}

#include "TextQuery.h"

void runQueries(ifstream& infile) {
	TextQuery tq(infile);
	while (true) {
		cout << "enter word to look for, or q to quit.";
		string s;
		if (!(cin >> s) || s == "q") break;
		print(cout, tq.query(s)) << endl;
	}
}


int main()
{
	cout << endl;
	//Exercise 12.6
	//cout << "Exercise 12.6" << endl;
	//vector<int>* pv = f1();
	//vector<int>& rv = f2(*pv);
	//f3(rv);

	//Exercise 12.7
	//cout << "Exercise 12.7" << endl;
	//auto pv = f11();
	//pv = f22(pv);
	//f33(pv);

	//Exercise 12.16
	//unique_ptr<int> p1(new int(1));
	//unique_ptr<int> p2(p1);
	//unique_ptr<int> p3 = p1;

	cout << "Exercise 12.20" << endl;
	ifstream in("..\\CP11\\rule.txt");
	string line;
	StrBlob sb;
	while (getline(in, line)) {
		sb.push_back(line);
	}
	in.close();

	StrBlobPtr sbp(sb);
	for (int i = 0; i < sb.size();i++) {
		cout << sbp.deref() << endl;
		sbp.incr();
	}

	cout << "Exercise 12.22" << endl;
	const StrBlob& sbr = sb;
	StrBlobPtr sbp2(sbr);

	ConstStrBlobPtr csbp(sbr);
	for (int i = 0; i < sbr.size(); i++) {
		cout << csbp.deref() << endl;
		csbp.incr();
	}

	//cout << "Exercise 12.23" << endl;
	//char* s1 = "test", * s2 = "lala";
	//char* s3 = concat1(s1, s2);
	//cout << s3 << endl;
	//delete[] s3;
	//string str1(s1), str2(s2);
	//string* str3 = concat2(str1, str2);
	//cout << *str3 << endl;
	//delete str3;

	//cout << "Exercise 12.24" << endl;
	//char buf[20];
	//int sz = 0;
	//char* str1 = nullptr, * str2 = nullptr;
	//while (cin) {
	//	cin.read(buf, 20);
	//	str2 = new char[sz + cin.gcount() + 1];
	//	if (str1) {
	//		copy(str1, str1 + sz, str2);
	//		delete[]str1;
	//	}
	//	copy(buf, buf + cin.gcount(), str2 + sz);
	//	sz += cin.gcount();
	//	str2[sz] = '\0';
	//	str1 = str2;

	//}
	//cout << str2 << endl;
	//delete [] str2;

	//cout << "Exercise 12.26" << endl;
	//const int n = 50;
	//allocator<string> alloc;
	//string* p = alloc.allocate(n);
	//string s;
	//int i;
	//for (i = 0; cin >> s && i < n;i++) {
	//	alloc.construct(p + i, s);
	//}
	//for (i-=1; i >= 0; i--) {
	//	alloc.destroy(p + i);
	//}
	//alloc.deallocate(p, n);

	//cout << "Exercise 12.27" << endl;
	//TextQuery tq(string("..\\CP11\\rule.txt"));
	//string searchfor;
	//cin >> searchfor;
	//do {
	//	tq.query(searchfor);
	//	QueryResult qr;
	//	qr.printResult(tq, searchfor);
	//} while (cin >> searchfor);//Exercise 12.29

	//cout << "Exercise 12.28" << endl;
	//ifstream in28("CP12.cpp");
	////ifstream in28("..\\CP11\\rule.txt");
	//vector<string> text;
	//string s28;
	//while (getline(in28, s28)) {
	//	text.push_back(s28);
	//}
	//in28.close();

	//string searchfor;
	//while (cin >> searchfor) {
	//	set<int> lines;
	//	int cnt = 0;
	//	for (int i = 0; i < text.size(); i++) {
	//		int number = 0;
	//		auto b = text[i].begin();
	//		while (b != text[i].end()) {
	//			auto it = search(b, text[i].end(), searchfor.begin(), searchfor.end());
	//			if (it != text[i].end()) {
	//				number++;
	//				b = it + 1;
	//			}
	//			else
	//				break;			
	//		}
	//		if (number != 0) {
	//			lines.insert(i+1);
	//			cnt += number;
	//		}
	//	}
	//	cout << searchfor << " appears " << cnt << " times." << endl;
	//	for (auto p = lines.begin(); p != lines.end(); p++) {
	//		cout << "(line " << *p << ") " << text[*p-1] << endl;
	//	}
	//}

	cout << "Exercise 12.30, 12.32, 12.33, 13.42" << endl;
	ifstream in30("..\\CP11\\rule.txt");
	runQueries(in30);
	in30.close();
}
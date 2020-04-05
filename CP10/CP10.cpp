// CP10.cpp : Defines the entry point for the console application.
//
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <numeric>
#include <iostream>
#include <sstream>
#include <fstream>
#include <functional>
#include <iterator>
using namespace std;
using namespace std::placeholders;


void elimDups(vector<string>& words){
	sort(words.begin(),words.end());
	auto it = unique(words.begin(),words.end());
	words.erase(it,words.end());
}

void elimDups(list<string>& words) {
	words.sort();
	words.unique();
}

bool isShorter(const string& s1, const string& s2){
	return s1.size() < s2.size();
}

bool shorterThanFive(const string& s){
	return s.size() < 5;
}

bool shorterThan(const string& s, const unsigned int num){
	return s.size() < num;
}

string make_plural(int count, string s, string p){
	return count > 1 ? s+p : s;
}

void biggies(vector<string>& words, vector<string>::size_type sz){
	elimDups(words);
	auto f = [sz](string& s) -> bool {return s.size() >= sz;};
	//auto it = partition(words.begin(), words.end(), [sz](string& s){return s.size() < sz;});//10.18
	auto f2 = bind(shorterThan, _1, 5);
	auto it = partition(words.begin(), words.end(), f2);//10.25
	//auto it = stable_partition(words.begin(), words.end(), [sz](string& s){return s.size() < sz;});//10.19
	//stable_sort(words.begin(), words.end(), isShorter);//10.16
	//auto it = find_if(words.begin(), words.end(),f);
	//auto n = words.end()- it;
	int n = count_if(words.begin(), words.end(),[sz](string& s){return s.size() >= sz;});//10.20
	cout << n << " " << make_plural(n, "word","s") << " of length " << sz << " or longer" << endl;
	//copy(it,words.end(),ostream_iterator<string>(cout, " "));
	for_each(it, words.end(), [](string& s){cout << s << " ";});
	cout << endl;
}

int main()
{
	cout << "Exercise 10.1" << endl;
	vector<int> v1;
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(2);
	cout << count(v1.cbegin(), v1.cend(),2) << endl;

	cout << "Exercise 10.2" << endl;
	vector<string> v2;
	v2.push_back("aa");
	v2.push_back("bb");
	v2.push_back("bb");
	cout << count(v2.cbegin(), v2.cend(),"bb") << endl;

	cout << "Exercise 10.3" << endl;
	cout << accumulate(v1.cbegin(), v1.cend(),0) << endl;
	cout << accumulate(v2.cbegin(), v2.cend(),string("lala")) << endl;

	cout << "Exercise 10.4" << endl;
	vector<double> v4;
	v4.push_back(1.1);
	v4.push_back(2.2);
	v4.push_back(2.2);
	cout << count(v4.cbegin(), v4.cend(),2.2) << endl;
	cout << accumulate(v4.cbegin(), v4.cend(),0.0) << endl;

	cout << "Exercise 10.5" << endl;
	//vector<string> v5(v2);
	vector<const char*> v3;
	v3.push_back("aa");
	v3.push_back("bb");
	v3.push_back("bb");
	vector<const char*> v5;
	v5.push_back("aa");
	v5.push_back("bb");
	v5.push_back("aa");
	cout << equal(v5.cbegin(), v5.cend(),v2.cbegin()) << endl;
	
	cout << "Exercise 10.6" << endl;
	
	vector<int> v6;
	auto it = back_inserter(v6);
	fill_n(it, 5, 0);
	copy(v6.cbegin(),v6.cend(),ostream_iterator<int>(cout, " "));
	cout << endl;

	cout << "Exercise 10.9" << endl;
	
	string s = "the quick red fox jumps over the slow red turtle";
	istringstream ss(s);
	istream_iterator<string> ss_in(ss), eof;
	//vector<string> v9;
	//string word;
	//while(ss >> word){
	//	v9.push_back(word);
	//}
	vector<string> v9(ss_in, eof);
	vector<string> v9_bak(v9);
	elimDups(v9);
	copy(v9.cbegin(),v9.cend(),ostream_iterator<string>(cout, " "));
	cout << endl;

	cout << "Exercise 10.11" << endl;
	stable_sort(v9.begin(),v9.end(),isShorter);
	copy(v9.cbegin(),v9.cend(),ostream_iterator<string>(cout," "));
	cout << endl;

	cout << "Exercise 10.13" << endl;

	sort(v9.begin(),v9.end());
	copy(v9.begin(), v9.end(), ostream_iterator<string>(cout, " "));
	cout << endl;
	auto it_par = partition(v9.begin(),v9.end(), shorterThanFive);
	copy(v9.cbegin(),v9.cend(),ostream_iterator<string>(cout," "));
	cout << endl;
	copy(it_par,v9.end(),ostream_iterator<string>(cout," "));
	cout << endl;

	cout << "Exercise 10.16, 10.18, 10.19, 10.20, 10.25" << endl;
	vector<string> v14(v9_bak);
	biggies(v14, 5);

	cout << "Exercise 10.21" << endl;
	vector<string> v20(v9_bak);
	int n = 5;

	auto f2 = [n]()mutable -> bool {if(n == 0) return true; --n; return false;};
	for(int i=5;i>=-2;i--){
		cout << f2() << " " << n << endl;
	}

	cout << "Exercise 10.22" << endl;
	vector<string> v22(v9_bak);
	auto f22 = bind(shorterThan, _1, 5);
	cout << count_if(v22.begin(),v22.end(),f22) << endl;

	cout << "Exercise 10.24" << endl;
	string s24("size");
	vector<int> v24;
	auto bi24 = back_inserter(v24);
	fill_n(bi24,10,0);
	iota(v24.begin(),v24.end(),0);
	auto f24 = bind(shorterThan, s24, _1);
	auto it24 = find_if(v24.begin(),v24.end(),f24);
	if(it24 != v24.end())
		cout << *it24 << endl;

	cout << "Exercise 10.27" << endl;
	vector<string> v27(v9_bak);
	vector<string> v27_2;
	sort(v27.begin(),v27.end());
	auto bi27 = back_inserter(v27_2);
	unique_copy(v27.begin(),v27.end(),bi27);
	for_each(v27_2.begin(),v27_2.end(),[](string& s){cout << s << " ";});
	cout << endl;

	cout << "Exercise 10.28" << endl;
	vector<int> v28;
	auto bi28 = back_inserter(v28);
	fill_n(bi28,9,0);
	iota(v28.begin(),v28.end(),1);
	list<int> l28_1, l28_2, l28_3;
	auto bi28_1 = inserter(l28_1, l28_1.end());
	auto bi28_2 = back_inserter(l28_2);
	auto bi28_3 = front_inserter(l28_3);

	copy(v28.begin(),v28.end(),bi28_1);
	copy(v28.begin(),v28.end(),bi28_2);
	copy(v28.begin(),v28.end(),bi28_3);

	for_each(l28_1.begin(),l28_1.end(),[](int& i){cout << i << " ";});
	cout << endl;
	copy(l28_2.begin(),l28_2.end(),ostream_iterator<int>(cout, " "));
	cout << endl;
	string s28;
	auto bi28_4 = back_inserter(s28);
	for_each(l28_3.begin(),l28_3.end(),[](int& i){cout << i << " ";});
	cout << endl;
	copy(l28_3.begin(),l28_3.end(),bi28_4);
	transform(s28.begin(),s28.end(),s28.begin(),[](char c){return c+48;});
	cout << s28 << endl;
	//string s28_4;
	//ostringstream oss(s28);
	//ostream_iterator<char> osi(oss, " ");
	//copy(s28.begin(),s28.end(), osi);
	//cout << s28_4 << endl;

	cout << "Exercise 10.29" << endl;
	ifstream in("a.txt");
	istream_iterator<string> it_in(in), eof29;
	vector<string> v29(it_in, eof29);
	//vector<string> v29;
	//auto bi29 = back_inserter(v29);
	//copy(it_in, eof29, bi29);
	//while(it_in !=eof29){
	//	v29.push_back(*it_in++);
	//}
	copy(v29.begin(),v29.end(),ostream_iterator<string>(cout, " "));
	cout << endl;
	in.close();

	cout << "Exercise 10.30" << endl;
	ifstream in30("b.txt");
	istream_iterator<int> it_in30(in30), eof30;
	vector<int> v30(it_in30, eof30);
	sort(v30.begin(), v30.end());
	copy(v30.begin(),v30.end(),ostream_iterator<int>(cout, " "));
	cout << endl;
	in30.close();

	cout << "Exercise 10.31" << endl;
	ifstream in31("b.txt");
	istream_iterator<int> it_in31(in31), eof31;
	vector<int> v31(it_in31, eof31);
	sort(v31.begin(), v31.end());
	unique_copy(v31.begin(),v31.end(),ostream_iterator<int>(cout, " "));
	cout << endl;
	in31.close();

	cout << "Exercise 10.33" << endl;
	ifstream in33("b.txt");
	ofstream out33_1("c.txt"), out33_2("d.txt");
	istream_iterator<int> it_in33(in33), eof33;
	vector<int> v33(it_in33, eof33);
	vector<int> v33_bak(v33);
	auto it33 = stable_partition(v33.begin(),v33.end(),[](int i){return i % 2 == 1;});
	copy(v33.begin(),it33,ostream_iterator<int>(out33_1," "));
	copy(it33,v33.end(),ostream_iterator<int>(out33_2, "\r\n"));
	in33.close();
	out33_1.close();
	out33_2.close();

	cout << "Exercise 10.34" << endl;
	vector<int> v34(v33_bak);
	sort(v34.begin(), v34.end());
	copy(v34.rbegin(), v34.rend(), ostream_iterator<int>(cout, " "));
	cout << endl;

	cout << "Exercise 10.35" << endl;
	vector<int> v35(v33_bak);
	auto it35 = v35.end();
	while (--it35 != v35.begin()) {
		cout << *it35 << " ";
	}
	cout << *it35 << endl;

	cout << "Exercise 10.36" << endl;
	list<int> l36(v33_bak.begin(), v33_bak.end());
	auto it36 = find(l36.rbegin(), l36.rend(), 0);
	it36++;
	copy(it36.base(), l36.end(), ostream_iterator<int>(cout, " "));
	cout << endl;

	cout << "Exercise 10.37" << endl;
	vector<int> v37(v33_bak);
	list<int> l37(v37.rbegin() + 5, v37.rbegin() + 10);
	copy(l37.begin(), l37.end(), ostream_iterator<int>(cout, " "));
	cout << endl;

	cout << "Exercise 10.42" << endl;
	list<string> l42(v9_bak.begin(), v9_bak.end());
	copy(l42.begin(), l42.end(), ostream_iterator<string>(cout, " "));
	cout << endl;
	elimDups(l42);
	copy(l42.begin(), l42.end(), ostream_iterator<string>(cout, " "));
	cout << endl;
}


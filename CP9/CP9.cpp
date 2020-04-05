#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <deque>
#include <forward_list>
#include <stack>
using namespace std;
//9.18
void printDeque(){
	deque<string> ds;
	string s;
	while(cin >> s){
		ds.push_back(s);
	}

	deque<string>::iterator b=ds.begin(), e=ds.end();
	while(b!=e){
		cout << *b++ << " ";
	}
	cout << endl;
}
//9.19
void printList(){
	list<string> ds;
	string s;
	while(cin >> s){
		ds.push_back(s);
	}

	list<string>::iterator b=ds.begin(), e=ds.end();
	while(b!=e){
		cout << *b++ << " ";
	}
	cout << endl;
}
//9.20
void removeOdd(){
	forward_list<int> l;
	l.push_front(5);l.push_front(4);l.push_front(3);l.push_front(2);l.push_front(1);
	auto prev = l.before_begin(), cur = l.begin();
	while(cur!=l.end()){
		if(*cur %2 != 0)
			cur=l.erase_after(prev);
		else{
			prev = cur;
			cur++;
		}
	}

	auto b = l.begin();
	while(b!=l.end())
		cout << *b++ << " ";
	cout << endl;
}

//9.38
void vectorIncrease(){
	vector<int> v;
	for(int i=1;i<1026;i++){
		cout << "v.size(): " << v.size() << " ;v.capacity(): " << v.capacity() << endl;
		v.push_back(i);
	}

}

//9.43, 9.44
void replaceAll(string& s, const string& oldVal, const string& newVal){
	string::size_type pos = 0;
	pos = s.find(oldVal);
	while(pos!=string::npos){
		//s.erase(pos,oldVal.size());
		//s.insert(pos,newVal);
		s.replace(pos,oldVal.size(),newVal);
		pos += newVal.size();
		pos = s.find(oldVal, pos);
	}
}

//9.49
string longestNoCender(string filename){
	ifstream file(filename);
	string word;
	const string cender = "bdfghijklpqtyBDFGHIJKLPQTY";
	const string noCender = "acemnorsuvwxzACEMNORSUVWXZ";
	string::size_type longest = 0;
	string longestWord = "";
	while(file >> word){
		if(word.find_first_of(cender) == string::npos && word.size() > longest){
			longestWord = word;
			longest = word.size();
		}
	}
	file.close();
	return longestWord;
}

void split(const string& s,vector<string>& result, const string& sep=" "){
	result.clear();
	string::size_type pos1 = string::npos, pos2 = 0;
	do{
		pos1 = pos2;
		pos2 = s.find(sep, pos1);
		if(pos2!=string::npos){
			result.push_back(s.substr(pos1,pos2-pos1));
			pos2 += sep.size();
		}
		else
			result.push_back(s.substr(pos1));		
	}while(pos2 != string::npos);
}

void tolower(string& s){
	for(unsigned int i=0;i<s.size();i++){
		s[i] = tolower(s[i]);
	}
}

//9.51
class Day{
public:
	Day(string aDay){
		//const string alphas="abcdefghijklmnopqrstuvwxyz";
		const string numbers="0123456789";
		vector<string> v;
		if(aDay.find_first_of("/")!=string::npos)
			split(aDay, v, "/");
		else
			split(aDay, v);

		if(v[0].find_first_not_of(numbers)!=string::npos){
			tolower(v[0]);
			v[0].erase(3, v[0].size());
		}
		day = stoul(v[1]);
		year = stoul(v[2]);

		switch (v[0][0]) {
		case 'j': {
			switch (v[0][1]) {
				case 'a':
						month = 1;	break;
				case 'u':{
					switch (v[0][2]) {
						case 'n':
							month = 6; break;
						case 'l':
							month = 7; break;
						}
					}
					break;
				}
			}
			break;
		case 'f':
			month = 2; break;
		case 'm': {
			switch (v[0][2]) {
				case 'r':
					month = 3; break;
				case 'y':
					month = 5; break;
				}
			}
			break;
		case 'a': {
			switch (v[0][1]) {
				case 'p':
					month = 4; break;
				case 'u':
					month = 8; break;
				}
			}
			break;
		case 's':
			month = 9; break;
		case 'o':
			month = 10; break;
		case 'n':
			month = 11; break;
		case 'd':
			month = 12; break;

		}
	};

	void output(ostream&out){
		out << year << '-' << month << '-' << day;
	}

private:
	unsigned int year;
	unsigned int month;
	unsigned int day;
};

ostream& operator<<(ostream& out, Day& aDay){
	aDay.output(out);
	return out;
}

//9.52
void trim(string& s) {
	auto b = s.begin();
	while(b!=s.end()) {
		if (*b == ' ')
			s.erase(b);
		else
			b++;
	}
}

int computeAtomic(string s) {//"only 3 parts: a x b, x = +, - * / %
	int result = 0;
	const string symbols = "+-*/%";
	string::size_type pos = s.find_first_of(symbols);
	int a = stoi(s.substr(0,pos));
	int b = stoi(s.substr(pos+1));
	char c = s[pos];
	switch (c) {
	case '+':
		result = a + b;
		break;
	case '-':
		result = a - b;
		break;
	case '*':
		result = a * b;
		break;
	case '/':
		result = a / b;
		break;
	case '%':
		result = a % b;
		break;
	}

	return result;
}

int computeAtomicDeque(deque<string>& deq) {
	int result = 0;
	string s = deq.back();
	deq.pop_back();
	s.insert(0, deq.back());
	deq.pop_back();
	s.insert(0, deq.back());
	deq.pop_back();
	result = computeAtomic(s);
	//stk.push(to_string(result));

	return result;
}

int computeDeque(deque<string>& deq) {
	int result = 0;
	while(deq.size() > 1){
		string s = deq.front();
		deq.pop_front();
		s.append(deq.front());
		deq.pop_front();
		s.append(deq.front());
		deq.pop_front();
		result = computeAtomic(s);
		deq.push_front(to_string(result));
	}
	return result;
}

int computeNoParen(string expr) {//no ( ) in expr, * / % take precedence over + -
	const string symbols = "+-*/%";
	const string hsyms = "*/%";
	deque<string> deq;
	int result = 0;
	string s,s2;
	string::size_type prev = 0;
	string::size_type pos = expr.find_first_of(symbols);
	string lastsym, sym;
	while (pos != string::npos) {
		s = expr.substr(prev, pos - prev);
		deq.push_back(s);
		
		lastsym = sym;
		sym = expr[pos];
		if(lastsym.find_first_of(hsyms)!=string::npos){//if last symbol is */%, compute it first
			result = computeAtomicDeque(deq);
			if(deq.size() > 1)
				lastsym = deq.back();
			else
				lastsym = "";
			deq.push_back(to_string(result));
		}else{
			if(lastsym != "" && sym.find_first_of(hsyms) == string::npos){//if last sysbol is not empty(is +-), and current sysbol is not */%, compute
				result = computeDeque(deq);
				if(deq.size() > 1)
					lastsym = deq.back();
				else
					lastsym = "";
				//deq.push_back(to_string(result));
			}
		}
		deq.push_back(sym);
		pos++;
		prev = pos;
		pos = expr.find_first_of(symbols, pos);	
	}
	s = expr.substr(prev);
	deq.push_back(s);
	while (deq.size() > 1) {
		result = computeDeque(deq);
		//deq.push_back(to_string(result));
	}

	return result;
}

//first step, consider the string is fully parenthesis'd, like: (1 + (2 * ((8 -3) % (6 / 3))))
int compute(string expr) {
	const string symbols = "()+-*/%";
	stack<string> stk;
	int result = 0;
	string s;
	string::size_type prev = string::npos;
	string::size_type pos = 0;
	while (pos != string::npos) {
		prev = pos;
		pos = expr.find_first_of(symbols, pos);
		if (pos != string::npos) {
			switch (expr[pos]) {
			case ')':
				s = expr.substr(prev, pos - prev);
				trim(s);
				while(stk.size() > 0 && stk.top() != "("){
					s.insert(0, stk.top());
					stk.pop();
				}
				if (stk.top() == "(")
					stk.pop();

				result = computeNoParen(s);
				stk.push(to_string(result));
				break;
			default:
				s = expr.substr(prev, pos - prev);
				trim(s);
				if(!s.empty())
					stk.push(s);
				s = expr.substr(pos, 1);
				stk.push(s);
				break;
			}
			pos += 1;
		}
	}
	if (stk.size() > 1) {
		s = expr.substr(prev);
//		stk.push(s);
		while (stk.size() > 0) {
			s.insert(0, stk.top());
			stk.pop();
		}
		result = computeNoParen(s);
		stk.push(to_string(result));
		
	}

	return result;
}

int main()
{
	//int result = compute("(1 + (2 * ((8 - 3) % (6 / 3))))"); //3
	//int result = compute("((((84 - 35) % (65 / 2))*23)+12)"); //403
	//int result = compute("(1 + 1)");
	int result = compute("1 + 4*5/2 - 8%5*2 +5 - 3"); //7
	//int result = compute("1 + 4*5/2 - 3"); //8
	//int result = compute("1 + 1 + 1");
	cout << result << endl;

	//string s = "January/1/1900";
	//string s = "June 28 2000";
	//Day d(s);
	//cout << d << endl;

	//printDeque();
	//printList();
	//removeOdd();
	//vectorIncrease();
	//string s = longestNoCender("C:\\Temp\\test.txt");
	//cout << s << endl;

	//string s="This type trait may be specialized for user-provided types that may be used as iterators. The standard library provides two partial specializations for pointer types T*, which makes it possible to use all iterator-based algorithms with raw pointers.";
	//replaceAll(s,"may","MMAAYY");
	//cout << s<< endl;

	//const vector<int> v1(5,10);
	////v1.push_back(10);

	//list<int> l(3,5);
	//vector<double> vd(v1.begin(),v1.end());

	//list<char*> l1(3, "hello");
	//vector<string> v2;
	//v2.assign(l1.begin(),l1.end());
	//auto b = v2.begin(), e = v2.end();
	//cout << sizeof(b) << endl;
	//while(b != e)
	//	cout << *b++ << " ";
	//cout << endl;

	//cout << v1.max_size() << endl;
	//cout << v2.max_size() << endl;
	//cout << vd.max_size() << endl;
	//cout << l.max_size() << endl;
	//cout << l1.max_size() << endl;
}
#pragma once
#ifndef _TEXTQUERY_H
#define _TEXTQUERY_H
#include <vector>
#include <string>
#include <fstream>
#include <memory>
#include <map>
#include <set>
#include "../CP13/StrVec.h"
#include "../CP16/DebugDelete.h"
using namespace std;
class QueryResult;
class TextQuery {
public:
	using line_no = vector<string>::size_type;
	//15.42a
	//TextQuery() :file(new vector<string>) {}
	//16.22
	TextQuery() :file(new vector<string>, DebugDelete()) {}
	TextQuery(ifstream& infile);
	virtual QueryResult query(const string& searchfor) const;
	virtual ~TextQuery() = default;
//15.42a
protected:
//private:
	shared_ptr<vector<string>> file;
	//shared_ptr<StrVec> file;//13.42
	map<string, shared_ptr<set<line_no>>> wm;
};

class LineLimitedTextQuery: public TextQuery {
public:
	LineLimitedTextQuery(ifstream& infile, size_t line_start, size_t line_end);

};

class QueryResult {
	friend ostream& print(ostream& out, const QueryResult& qr);
public:
	QueryResult(string s, shared_ptr<set<TextQuery::line_no>> p, shared_ptr<vector<string>> f) : sought(s), lines(p), file(f){}
	//QueryResult(string s, shared_ptr<set<TextQuery::line_no>> p, shared_ptr<StrVec> f) : sought(s), lines(p), file(f) {}//13.42

	//Exercise 12.33
	set<TextQuery::line_no>::iterator begin() { return lines->begin(); }
	set<TextQuery::line_no>::iterator end() { return lines->end(); }
	shared_ptr<vector<string>> get_file() { return file; }
	//shared_ptr<StrVec> get_file() { return file; }//13.42
private:
	string sought;
	shared_ptr<set<TextQuery::line_no>> lines;
	shared_ptr<vector<string>> file;
	//shared_ptr<StrVec> file;//13.42
};

ostream& print(ostream& out, const QueryResult& qr);


//15.42a
class TextQuerySentence : public TextQuery {
public:
	TextQuerySentence(ifstream& infile);
private:
	void analyzeSentence(string& sentence);
};

#endif

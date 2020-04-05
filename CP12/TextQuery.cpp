#include "TextQuery.h"
#include <sstream>
#include <iterator>
#include <iostream>
#include <algorithm>
using namespace std;
//TextQuery::TextQuery(ifstream& is) :file(new vector<string>) {
//16.22
TextQuery::TextQuery(ifstream& is):file(new vector<string>, DebugDelete()) {
//TextQuery::TextQuery(ifstream& is) :file(new StrVec) {
	string text;
	while (getline(is, text)) {
		file->push_back(text);
		int n = file->size() - 1;
		istringstream line(text);
		string word;
		while (line >> word) {
			auto& lines = wm[word];
			if (!lines) {
				//lines.reset(new set<line_no>);
				//16.22
				lines.reset(new set<line_no>, DebugDelete());
			}
			lines->insert(n);
			
		}
	}
}
//15.42c
LineLimitedTextQuery::LineLimitedTextQuery(ifstream& is, size_t line_start, size_t line_end) {
	file = shared_ptr<vector<string>>(new vector<string>());
	string text;
	size_t ln = 0;
	while (getline(is, text)) {
		ln++;
		file->push_back(text);
		if (ln < line_start || ln > line_end)
			continue;
		//int n = file->size() - 1;
		istringstream line(text);
		string word;
		while (line >> word) {
			auto& lines = wm[word];
			if (!lines) {
				//lines.reset(new set<line_no>);
				//16.22
				lines.reset(new set<line_no>, DebugDelete());
			}
			lines->insert(ln-1);

		}
	}
}

QueryResult TextQuery::query(const string& sought) const {
	static shared_ptr<set<line_no>> nodata(new set<line_no >);

	auto loc = wm.find(sought);
	if (loc == wm.end())
		return QueryResult(sought, nodata, file);
	else
		return QueryResult(sought, loc->second, file);
}

ostream& print(ostream& out, const QueryResult& qr) {
	out << qr.sought << " occurs " << qr.lines->size() << " " << "times(s)" << endl;
	for (auto num : *qr.lines) {
		out << "\t(line " << num + 1 << ") " << *(qr.file->begin() + num) << endl;
	}
	return out;
}
//
//bool func1(char c) {
//	return c == '.' || c == '?' || c == '!';
//}
//
//class func2 {
//public:
//	bool operator()(char c) {
//		return c == '.' || c == '?' || c == '!';
//	}
//
//};

//15.42a
TextQuerySentence::TextQuerySentence(ifstream& is) {
	string text;
	auto func = [](char c) ->bool {return c == '.' || c == '?' || c == '!';  };
	/*func2 f2;*/
	string sentence = "";
	while (getline(is, text)) {
		for (auto b = text.begin(), e= text.end(); b != e;++b) {
			//auto i = find(b, text.end(), '.');
			auto i = find_if(b, text.end(), func);
			if (i != text.end()) {
				sentence += string(b, i+1);
				b = i;
				file->push_back(sentence);
				analyzeSentence(sentence);
				sentence = "";
			}
			else {
				sentence += string(b, e);
				sentence += " ";
				break;
			}
		}
	}
	if (sentence != "") {
		file->push_back(sentence);
		analyzeSentence(sentence);
	}

	copy(file->begin(), file->end(), ostream_iterator<string>(cout, "\n"));
}

void TextQuerySentence::analyzeSentence(string& sentence) {
	int n = file->size() - 1;
	istringstream line(sentence);
	string word;
	while (line >> word) {
		auto& lines = wm[word];
		if (!lines) {
			lines.reset(new set<line_no>);
		}
		lines->insert(n);

	}
}
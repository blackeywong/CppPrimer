#include "Query.h"
#include <algorithm>
#include <iterator>
#include <numeric>

std::ostream& operator<<(std::ostream& out, const Query& query) {
	out << query.rep();
	return out;
}

bool isNumber(const string& s) {
	if (s.size() == 0) return false;
	for (char c : s) {
		if (!isdigit(c))
			return false;
	}
	return true;
}

bool isToken(const string& s) {
	if (s.size() == 0) return false;
	for (char c : s) {
		if (!isalnum(c))
			return false;
	}
	return true;
}

void tokenize(const string& expr, vector<string>& v, const string& syms) {
	string word;
	string wp(" \t\r\n");
	v.clear();
	for (char c : expr) {
		if (find(wp.begin(), wp.end(), c) != wp.end()) {
			if (word != "") {
				v.push_back(word);
				word.clear();
			}
		}else if (find(syms.begin(), syms.end(), c) != syms.end()) {
			if (word != "") {
				v.push_back(word);
				word.clear();
			}
			v.push_back(string(1, c));
		}
		else {
			word += c;
		}

	}
}

bool priorityOver(const char sym1, const char sym2, const string& prio_str) {
	auto it1 = find(prio_str.begin(), prio_str.end(), sym1);
	auto it2 = find(prio_str.begin(), prio_str.end(), sym2);
	return it1 <= it2;
}

string infixToSuffix(const string& expr) {
	//priority: (~&|)
	vector<string> symstack, numstack;
	string symtop;
	vector<string> v;
	tokenize(expr, v, "(~&|)");
	for (string s : v) {
		if (isToken(s)) {
			numstack.push_back(s);
		}
		else {
			if (symtop != "" && priorityOver(symtop[0], s[0], "(~&|)")) {
				numstack.push_back(symtop);
				symstack.pop_back();
				if (s == ")") {
					symstack.pop_back();//must be "("
				}
			}
			symstack.push_back(s);
			symtop = s;
		}
	}

	while (symstack.size() > 0) {
		numstack.push_back(symstack.back());
		symstack.pop_back();
	}

	string res;
	res = accumulate(numstack.begin(), numstack.end(), string(""));
	/*for (string s : numstack) {
		res += s;
	}*/

	return res;
}

string interceptFirstTokenOrSym(string& expr) {

	return "";
}

void trim(string& s) {
	auto f = [](char c) {return c == ' ' || c == '\t' || c == '\r' || c == '\n';  };
	auto it1 = find_if_not(s.begin(), s.end(), f);
	auto it2 = find_if_not(s.rbegin(), s.rend(), f);
	s = s.substr(it1 - s.begin(), it2.base() - it1);
}

Query::Query(const std::string& text) {
if (isToken(text) && !isNumber(text)) {
		q = std::shared_ptr<Query_base>(new WordQuery(text));
	}
	else if(isNumber(text)){
		//15.42b needs a tree, uncomplete
		string suffix = infixToSuffix(text);
		//TODO: produce a tree. Preorder traversal to 
		//tree = produceTree(suffix);
		/*
		if(root is "&") q = make_shared<Query_base>(new AndQuery(ltree, rtree));
		else if(root is "|") q = make_shared<Query_base>(new OrQuery(ltree, rtree));
		else if(root is "~") q = make_shared<Query_base>(new NotQuery(ltree));
		else q = std::shared_ptr<Query_base>(new WordQuery(text));
		*/
	}
}

QueryResult WordQuery::eval(const TextQuery& tq) const {
	return tq.query(word);
}

QueryResult NotQuery::eval(const TextQuery& tq) const {
	QueryResult qr = q.eval(tq);

	std::shared_ptr<std::set<line_no>> res = make_shared<std::set<line_no>>();

	auto sz = qr.get_file()->size();
	auto qb = qr.begin(), qe = qr.end();
	for (size_t i = 0; i < sz;i++) {
		if (qb == qe || i != *qb) {
			res->insert(i);
		}
		else if (qb != qe) {
			qb++;
		}
	}

	return QueryResult(rep(), res, qr.get_file());
}

QueryResult AndQuery::eval(const TextQuery& tq) const {
	QueryResult qr1 = lhs.eval(tq);
	QueryResult qr2 = rhs.eval(tq);

	std::shared_ptr<std::set<line_no>> res = make_shared<std::set<line_no>>();
	set_intersection(qr1.begin(), qr1.end(), qr2.begin(), qr2.end(), inserter(*res, res->begin()));

	return QueryResult(rep(), res, qr1.get_file());
}

QueryResult OrQuery::eval(const TextQuery& tq) const {
	QueryResult qr1 = lhs.eval(tq);
	QueryResult qr2 = rhs.eval(tq);

	std::shared_ptr<std::set<line_no>> res = make_shared<std::set<line_no>>(qr1.begin(), qr1.end());
	res->insert(qr2.begin(), qr2.end());

	return QueryResult(rep(), res, qr1.get_file());
}
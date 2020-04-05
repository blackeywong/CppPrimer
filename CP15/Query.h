#pragma once
#ifndef _QUERY_H
#define _QUERY_H
#include <string>
#include <memory>
#include <iostream>
#include "../CP12/TextQuery.h"

class Query;
class Query_base {
	friend class Query;
public:
	using line_no = TextQuery::line_no;
	virtual ~Query_base() = default;
private:
	virtual QueryResult eval(const TextQuery& tq) const = 0;
	virtual std::string rep() const = 0;
};

class Query {
	friend Query operator~(const Query& rhs);
	friend Query operator&(const Query & lhs, const Query& rhs);
	friend Query operator|(const Query& lhs, const Query& rhs);
public:
	Query(const std::string& text);
	QueryResult eval(const TextQuery& t) const{ return q->eval(t); }
	std::string rep() const{ return q->rep(); }
private:
	Query(const std::shared_ptr<Query_base>& qb) :q(qb) {}
	std::shared_ptr<Query_base> q;
};

std::ostream& operator<<(std::ostream& out, const Query& query);


class WordQuery : public Query_base {
	friend class Query;
public:
	WordQuery(const std::string& text) :word(text) {}
private:
	QueryResult eval(const TextQuery& tq) const override;
	std::string rep() const override { return word; }
	std::string word;
};

class NotQuery : public Query_base {
	friend Query operator~(const Query& rhs);
public:
	NotQuery(const Query& query) :q(query) {}
private:
	QueryResult eval(const TextQuery& tq) const override;
	std::string rep() const override { return "~(" + q.rep()+")"; }
	Query q;
};

class BinaryQuery : public Query_base {
protected:
	BinaryQuery(const Query& q1, const Query& q2, std::string s) :lhs(q1), rhs(q2), sym(s) {}
	std::string rep() const override { return "(" + lhs.rep()+sym+rhs.rep()+")"; }
	Query lhs;
	Query rhs;
	std::string sym;

};

class AndQuery :public BinaryQuery {
	friend Query operator&(const Query& lhs, const Query& rhs);
public:
	AndQuery(const Query& q1, const Query& q2) :BinaryQuery(q1, q2, "&") { }
private:
	QueryResult eval(const TextQuery& tq) const override;

};

class OrQuery :public BinaryQuery {
	friend Query operator|(const Query& lhs, const Query& rhs);
public:
	OrQuery(const Query& q1, const Query& q2) :BinaryQuery(q1, q2, "|") { }
private:
	QueryResult eval(const TextQuery& tq) const override;

};



inline Query operator~(const Query& rhs) {
	//return Query(make_shared<Query_base>(new NotQuery(rhs)));
	return std::shared_ptr<Query_base>(new NotQuery(rhs));
}

inline Query operator&(const Query& lhs, const Query& rhs) {
	//return Query(make_shared<Query_base>(new AndQuery(lhs, rhs)));
	return std::shared_ptr<Query_base>(new AndQuery(lhs, rhs));
}

inline Query operator|(const Query& lhs, const Query& rhs) {
	//return Query(make_shared<Query_base>(new OrQuery(lhs, rhs)));
	return std::shared_ptr<Query_base>(new OrQuery(lhs, rhs));
}

/*********************************************************************/
//15.42b
class HistoryQuery {
public:
	size_t size() { return history.size(); }
	void add(Query& q) { history.push_back(q); }
	Query& get(size_t n) { if (n < size()) return history[n]; }
private:
	vector<Query> history;
};

bool isNumber(const string& s);
bool isToken(const string& s);
void tokenize(const string& s, vector<string>& v, const string& syms);
bool priorityOver(const char sym1, const char sym2, const string& prio_str);
string infixToSuffix(const string& s);
string interceptFirstTokenOrSym(string& expr);

void trim(string& s);

#endif
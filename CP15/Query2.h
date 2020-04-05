#pragma once
#ifndef _QUERY2_H
#define _QUERY2_H
#include <string>
#include <memory>
#include <iostream>
#include "../CP12/TextQuery.h"
//15.41
class Query;
class Query_base {
	friend class Query;
protected:
	using line_no = TextQuery::line_no;
	virtual ~Query_base() = default;
private:
	virtual QueryResult eval(TextQuery& tq) = 0;
	virtual std::string rep() = 0;
};

class Query {
	friend Query operator~(Query& rhs);
	
	friend Query operator&(Query& lhs, Query& rhs);
	friend Query operator|(Query& lhs, Query& rhs);
public:
	
	//copy a pointer may lead to delete an object twice. So has to set the original one to nullptr
	Query(Query& query) : q(query.q) { query.q = nullptr; }

	inline Query(std::string& text);
	QueryResult eval(TextQuery& t) { return q->eval(t); }
	std::string rep() { return q->rep(); }
	
	~Query() {
		delete q;
	}
private:
	//Query(std::shared_ptr<Query_base>& qb) :q(qb) {}
	//std::shared_ptr<Query_base> q;
	
	Query(Query_base* qb) :q(qb) {
	}
	Query_base* q;
};

std::ostream& operator<<(std::ostream& out, Query& query);


class WordQuery : public Query_base {
	friend class Query;
	WordQuery(std::string& text) :word(text) {}
	QueryResult eval(TextQuery& tq) override;
	std::string rep() override { return word; }
	std::string word;
};

class NotQuery : public Query_base {
	friend Query operator~(Query& rhs);
	//NotQuery(Query& query) :q(query) {}
	
	NotQuery(Query& query) :q(query) {}
	QueryResult eval(TextQuery& tq) override;
	std::string rep() override { return "~(" + q.rep() + ")"; }
	Query q;
};

class BinaryQuery : public Query_base {
protected:
	//~BinaryQuery() = default;
	BinaryQuery(Query& q1, Query& q2, std::string s) :lhs(q1), rhs(q2), sym(s) {}
	std::string rep() override { return "(" + lhs.rep() + sym + rhs.rep() + ")"; }
	Query lhs;
	Query rhs;
	std::string sym;

};

class AndQuery :public BinaryQuery {
	friend Query operator&(Query& lhs, Query& rhs);
	AndQuery(Query& q1, Query& q2) :BinaryQuery(q1, q2, "&") { }
	QueryResult eval(TextQuery& tq) override;
};

class OrQuery :public BinaryQuery {
	friend Query operator|(Query& lhs, Query& rhs);
	OrQuery(Query& q1, Query& q2) :BinaryQuery(q1, q2, "|") { }
	QueryResult eval(TextQuery& tq) override;
};



inline Query operator~(Query& rhs) {
	//return Query(make_shared<Query_base>(new NotQuery(rhs)));
	//return std::shared_ptr<Query_base>(new NotQuery(rhs));
	
	return new NotQuery(rhs);
}


inline Query operator&(Query& lhs, Query& rhs) {
	//inline Query operator&(Query& lhs, Query& rhs) {
		//return Query(make_shared<Query_base>(new AndQuery(lhs, rhs)));
		//return std::shared_ptr<Query_base>(new AndQuery(lhs, rhs));
		
	Query_base* p = new AndQuery(lhs, rhs);
	lhs.q = nullptr;
	rhs.q = nullptr;
	return p;
}


inline Query operator|(Query& lhs, Query& rhs) {
	//inline Query operator|(Query& lhs, Query& rhs) {
		//return Query(make_shared<Query_base>(new OrQuery(lhs, rhs)));
		//return std::shared_ptr<Query_base>(new OrQuery(lhs, rhs));
		
	Query_base* p = new OrQuery(lhs, rhs);
	lhs.q = nullptr;
	rhs.q = nullptr;
	return p;
}

inline Query::Query(std::string& text) :q(new WordQuery(text)) {
	//q = std::shared_ptr<Query_base>(new WordQuery(text));
}

#endif
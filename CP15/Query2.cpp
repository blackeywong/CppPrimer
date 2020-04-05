#include "Query2.h"
#include <algorithm>
#include <iterator>
//15.41
std::ostream& operator<<(std::ostream& out, Query& query) {
	out << query.rep();
	return out;
}

QueryResult WordQuery::eval(TextQuery& tq) {
	return tq.query(word);
}

QueryResult NotQuery::eval(TextQuery& tq) {
	QueryResult qr = q.eval(tq);

	std::shared_ptr<std::set<line_no>> res = make_shared<std::set<line_no>>();

	auto sz = qr.get_file()->size();
	auto qb = qr.begin(), qe = qr.end();
	for (size_t i = 0; i < sz; i++) {
		if (qb == qe || i != *qb) {
			res->insert(i);
		}
		else if (qb != qe) {
			qb++;
		}
	}

	return QueryResult(rep(), res, qr.get_file());
}

QueryResult AndQuery::eval(TextQuery& tq) {
	QueryResult qr1 = lhs.eval(tq);
	QueryResult qr2 = rhs.eval(tq);

	std::shared_ptr<std::set<line_no>> res = make_shared<std::set<line_no>>();
	set_intersection(qr1.begin(), qr1.end(), qr2.begin(), qr2.end(), inserter(*res, res->begin()));

	return QueryResult(rep(), res, qr1.get_file());
}

QueryResult OrQuery::eval(TextQuery& tq) {
	QueryResult qr1 = lhs.eval(tq);
	QueryResult qr2 = rhs.eval(tq);

	std::shared_ptr<std::set<line_no>> res = make_shared<std::set<line_no>>(qr1.begin(), qr1.end());
	res->insert(qr2.begin(), qr2.end());

	return QueryResult(rep(), res, qr1.get_file());
}
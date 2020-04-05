#pragma once
#ifndef _BASKET_H
#define _BASKET_H
#include <set>
#include <memory>
#include <algorithm>
#include "Quote.h"
//15.30
class Basket {
public:
	//Basket() { items = std::multiset<std::shared_ptr<Quote>, compare_func*>(&compare); }
	void add_item(const Quote& q) { items.insert(std::shared_ptr<Quote>(q.clone())); }
	void add_item(Quote&& q) { items.insert(std::shared_ptr<Quote>((std::move(q)).clone())); }
	double total_receipt() {
		double result = 0.0;
		std::for_each(items.begin(), items.end(), [&result](std::shared_ptr<Quote> pq) {result += pq->net_price(5); });
		return result;
	}
private:
	static bool compare(const std::shared_ptr<Quote>& lhs, const std::shared_ptr<Quote>& rhs) { return lhs->isbn() < rhs->isbn(); }
	//using compare_func =  decltype(compare)*;

	std::multiset<std::shared_ptr<Quote>, decltype(compare)*> items{ compare };
};

#endif

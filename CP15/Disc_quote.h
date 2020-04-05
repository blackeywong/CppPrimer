#pragma once
#ifndef _DISC_QUOTE_H
#define _DISC_QUOTE_H
#include "Quote.h"

class Disc_quote : public Quote {
public:
	Disc_quote() = default;
	Disc_quote(const std::string& bookNo, double sales_price, std::size_t qty, double discount) :
		Quote(bookNo, sales_price), quantity(qty), discount(discount) {}
	virtual double net_price(std::size_t n) const = 0;
	//15.11
	virtual void debug() { this->Quote::debug(); std::cout << "quantity discount" << std::endl; }
	//15.26
	~Disc_quote() { 
		//std::cout << "in ~Disc_quote()" << std::endl;
	}
	Disc_quote(const Disc_quote& q) : Quote::Quote(q), quantity(q.quantity), discount(q.discount) { std::cout << "in Disc_quote(const Disc_quote& q)" << std::endl; }
	Disc_quote& operator=(const Disc_quote& q) { Quote::operator=(q); this->quantity = q.quantity; this->discount = q.discount;  std::cout << "in Disc_quote& operator=(const Disc_quote& q)" << std::endl; return *this; }
	Disc_quote(Disc_quote&& q) : Quote::Quote(std::move(q)), quantity(q.quantity), discount(q.discount) { std::cout << "in Disc_quote(Disc_quote&& q)" << std::endl; }
	Disc_quote& operator=(Disc_quote&& q) { Quote::operator=(std::move(q)); this->quantity = q.quantity; this->discount = q.discount;  std::cout << "in Disc_quote& operator=(Disc_quote&& q)" << std::endl; return *this; }
protected:
	std::size_t quantity = 0;
	double discount = 0.0;
};

#endif
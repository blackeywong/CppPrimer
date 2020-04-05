#pragma once
#ifndef _BULK_QUOTE_H
#define _BULK_QUOTE_H
#include "Disc_quote.h"

class Bulk_quote : public Disc_quote {
public:
	Bulk_quote() = default;
	//Bulk_quote(const std::string& bookNo, double sales_price, std::size_t qty, double discount) :
	//	Disc_quote(bookNo, sales_price, qty, discount){}
	//13.27
	using Disc_quote::Disc_quote;
	double net_price(std::size_t n) const override {
		if (n >= quantity)
			return n * (1 - discount) * price;
		else
			return n * price;
	}
	//15.11
	virtual void debug() { this->Disc_quote::debug(); }
	//15.26
	~Bulk_quote() { 
		//std::cout << "in ~Bulk_quote()" << std::endl;
	}
	Bulk_quote(const Bulk_quote& q) : Disc_quote::Disc_quote(q) { std::cout << "in Bulk_quote(const Bulk_quote& q)" << std::endl; }
	Bulk_quote& operator=(const Bulk_quote& q) { Disc_quote::operator=(q); std::cout << "in Bulk_quote& operator=(const Bulk_quote& q)" << std::endl; return *this; }
	Bulk_quote(Bulk_quote&& q) : Disc_quote::Disc_quote(std::move(q)) { std::cout << "in Bulk_quote(Bulk_quote&& q)" << std::endl; }
	Bulk_quote& operator=(Bulk_quote&& q) { Disc_quote::operator=(std::move(q)); std::cout << "in Bulk_quote& operator=(Bulk_quote&& q)" << std::endl; return *this; }

	//15.30
	virtual Bulk_quote* clone() const & { return new Bulk_quote(*this); }
	virtual Bulk_quote* clone() && { return new Bulk_quote(std::move(*this)); }
};

#endif
#pragma once
#ifndef _LIMIT_QUOTE_H
#define _LIMIT_QUOTE_H
#include "Disc_quote.h"

class Limit_quote : public Disc_quote {
public:
	Limit_quote() = default;
	Limit_quote(const std::string& bookNo, double sales_price, std::size_t qty, double discount) :
		Disc_quote(bookNo, sales_price, qty, discount) {}

	double net_price(std::size_t n) const override {
		if (n <= quantity)
			return n * (1 - discount) * price;
		else
			return quantity * (1 - discount) * price + (n - quantity) * price;
	}
	//15.11
	virtual void debug() { this->Disc_quote::debug();}
	//15.26
	~Limit_quote() { 
		//std::cout << "in ~Limit_quote()" << std::endl; 
	}
	Limit_quote(const Limit_quote& q) : Disc_quote::Disc_quote(q) { std::cout << "in Limit_quote(const Limit_quote& q)" << std::endl; }
	Limit_quote& operator=(const Limit_quote& q) { Disc_quote::operator=(q); std::cout << "in Limit_quote& operator=(const Limit_quote& q)" << std::endl; return *this; }
	Limit_quote(Limit_quote&& q) : Disc_quote::Disc_quote(std::move(q)) { std::cout << "in Limit_quote(Limit_quote&& q)" << std::endl; }
	Limit_quote& operator=(Limit_quote&& q) { Disc_quote::operator=(std::move(q)); std::cout << "in Limit_quote& operator=(Limit_quote&& q)" << std::endl; return *this; }
};

#endif
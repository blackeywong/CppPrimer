#pragma once
#ifndef _QUOTE_H
#define _QUOTE_H
#include <string>
#include <iostream>

class Quote {
public:
	Quote() = default;
	Quote(const std::string& book, double sales_price) :bookNo(book), price(sales_price) {}
	std::string isbn() const { return bookNo; }
	virtual double net_price(std::size_t n) const { return n * price; }
	virtual ~Quote() { 
		//std::cout << "in ~Quote()" << std::endl;
	}
	//15.3
	void print_total(std::size_t n) { std::cout << "book " << bookNo << " saled " << net_price(n) << std::endl; }
	//15.11
	virtual void debug() { std::cout << "bookNo price" << std::endl; }
	//15.26
	Quote(const Quote& q) : bookNo(q.bookNo), price(q.price) { std::cout << "in Quote(const Quote& q)" << std::endl; }
	Quote& operator=(const Quote& q) { this->bookNo = q.bookNo; this->price = q.price;  std::cout << "in Quote& operator=(const Quote& q)" << std::endl; return *this; }
	Quote(Quote&& q) : bookNo(q.bookNo), price(q.price) { std::cout << "in Quote(Quote&& q)" << std::endl; }
	Quote& operator=(Quote&& q) { this->bookNo = q.bookNo; this->price = q.price;  std::cout << "in Quote& operator=(Quote&& q)" << std::endl; return *this; }

	//15.30
	virtual Quote* clone() const & { return new Quote(*this); }
	virtual Quote* clone() && { return new Quote(std::move(*this)); }
private:
	std::string bookNo;
protected:
	double price = 0.0;
};

#endif
#pragma once
#ifndef _SALES_DATA_H
#define _SALES_DATA_H
#include <string>
#include <iostream>
using namespace std;

class Sales_data{
	friend Sales_data add(const Sales_data&, const Sales_data&);
	friend ostream& print(ostream& os, const Sales_data& item);
	friend istream& read(istream& is, Sales_data& item);
	friend struct hash<Sales_data>;
	//14.21
	friend Sales_data operator+(const Sales_data& a, const Sales_data& b);
public:
	Sales_data() {units_sold = 0; revenue = 0.0;};
	Sales_data(const string& s): bookNo(s){units_sold = 0; revenue = 0.0;}
	Sales_data(const string& s, unsigned n, double p) :bookNo(s), units_sold(n), revenue(p*n) {}
	Sales_data(istream&);

	string isbn() const { return bookNo; }
	Sales_data& combine(const Sales_data&);
	double avg_price() const;

	//14.20
	//Sales_data& operator+=(const Sales_data& rhs) { combine(rhs); }
	//14.21
	Sales_data& operator+=(const Sales_data& rhs) { Sales_data c = *this + rhs; *this = c; return *this; }
	//14.22
	Sales_data& operator=(const string& bn) { this->bookNo = bn; return *this; }
	//16.62
	bool operator==(const Sales_data& rhs) const { return bookNo == rhs.bookNo && units_sold == rhs.units_sold && revenue == rhs.revenue; }
protected:
	string bookNo;
	unsigned units_sold;
	double revenue;
};

Sales_data add(const Sales_data&, const Sales_data&);
ostream& print(ostream& os, const Sales_data& item);
istream& read(istream& is, Sales_data& item);
bool compareIsbn(const Sales_data& lhs, const Sales_data& rhs);
//14.2
inline ostream& operator<<(ostream& out, const Sales_data& sd) { print(out, sd); return out; }
inline istream& operator>>(istream& in, Sales_data& sd) { read(in, sd); return in; }
Sales_data operator+(const Sales_data&, const Sales_data&);

//16.62
namespace std {
	template<> struct hash<Sales_data> {
		typedef std::size_t result_type;
		typedef Sales_data argument_type;
		std::size_t operator()(const Sales_data& sd) const {
			return hash<std::string>()(sd.bookNo) ^ hash<unsigned>()(sd.units_sold) ^ hash<double>()(sd.revenue);
		}
	};
}


#endif
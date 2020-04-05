#include "sales_data.h"

Sales_data::Sales_data(istream& is) {
	read(is, *this);
}

double Sales_data::avg_price() const {
	if (units_sold) return revenue / units_sold;
	else return 0;
}

Sales_data& Sales_data::combine(const Sales_data& rhs) {
	units_sold += rhs.units_sold;
	revenue += rhs.revenue;
	return *this;
}

istream& read(istream& is, Sales_data& item) {
	double price = 0;
	is >> item.bookNo >> item.units_sold >> price;
	item.revenue = price * item.units_sold;
	return is;
}

ostream& print(ostream& os, const Sales_data& item) {
	os << item.isbn() << " " << item.units_sold << " " << item.revenue << " " << item.avg_price();
	return os;
}

Sales_data add(const Sales_data& lhs, const Sales_data& rhs) {
	Sales_data sum = lhs;
	sum.combine(rhs);
	return sum;
}

bool compareIsbn(const Sales_data& lhs, const Sales_data& rhs) {
	return lhs.isbn() < rhs.isbn();
}


//inline Sales_data operator+(const Sales_data& a, const Sales_data& b) { return add(a, b); }
Sales_data operator+(const Sales_data& a, const Sales_data& b) {
	Sales_data c(a);
	c.units_sold += b.units_sold;
	c.revenue += b.revenue;
	return c;
}
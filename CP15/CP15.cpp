// CP15.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include "Quote.h"
#include "Bulk_quote.h"
#include "Limit_quote.h"
#include "Basket.h"
#include "Query.h"
//#include "Query2.h"

//15.20
class Base {
public:
	void pub_mem();
protected:
	int prot_mem;
private:
	char priv_mem;
};

struct Pub_Derv : public Base {
	void memfcn(Base& b) { b = *this; }//15.19
};

struct Prot_Derv : protected Base {
	void memfcn(Base& b) { b = *this; }//15.19
};

struct Priv_Derv : private Base {
	void memfcn(Base& b) { b = *this; }//15.19
};

struct Derived_from_Public : public Pub_Derv {
	void memfcn(Base& b) { b = *this; }//15.19
};

struct Derived_from_Protected : public Prot_Derv {
	void memfcn(Base& b) { b = *this; }//15.19
};

struct Derived_from_Private : public Priv_Derv {
	//void memfcn(Base& b) { b = *this; }//15.19
};


//15.39
void runQueries(std::ifstream& infile) {
	TextQuery tq(infile);
	HistoryQuery hq;

	while (true) {
		cout << "enter query to look for, or q to quit.";
		string s;
		getline(cin, s);
		if (! cin || s == "q") break;
		if (isNumber(s)){
			size_t n = stoi(s);
			if (hq.size() >= n) {
				Query& q = hq.get(n);
				string qs = q.rep();
				cout << "Querying: " << qs << endl;
				print(std::cout, q.eval(tq)) << std::endl;
			}
		}
		else if (isToken(s) && !isNumber(s)) {
			Query q = Query(s);
			std::cout << q << std::endl;
			print(std::cout, q.eval(tq)) << std::endl;
			hq.add(q);
		}
		else {
			//15.42c
			auto it1 = find(s.begin(), s.end(), ',');
			string ls = s.substr(0, it1 - s.begin());
			size_t line_start = stoi(ls);
			string left = s.substr(it1 - s.begin() + 1, string::npos);
			trim(left);

			auto it2 = find(left.begin(), left.end(), ' ');
			string le = left.substr(0, it2 - left.begin());
			size_t line_end = stoi(le);
			left = left.substr(it2 - left.begin() + 1);
			trim(left);

			Query q = Query(left);
			std::cout << q << std::endl;
			infile.clear();
			infile.seekg(0);
			LineLimitedTextQuery tq(infile, line_start, line_end);
			print(std::cout, q.eval(tq)) << std::endl;
			hq.add(q);
		}
	}
}

int main()
{
    std::cout << "Exercise 15.6" << std::endl; 
	Bulk_quote bq1(std::string("0001"), 2.0, 5, 0.25);
	bq1.print_total(5);
	bq1.print_total(4);

	std::cout << "Exercise 15.7" << std::endl;
	Limit_quote lq1(std::string("0001"), 2.0, 5, 0.25);
	lq1.print_total(5);
	lq1.print_total(6);

	//15.20
	Pub_Derv d1;
	Prot_Derv d2;
	Priv_Derv d3;
	Derived_from_Public dd1;
	Derived_from_Protected dd2;
	Derived_from_Private dd3;
	//15.18
	Base* p = &d1;
	//p = &d2;
	//p = &d3;
	//p = &dd1;
	//p = &dd2;
	//p = &dd3;


	std::cout << "Exercise 15.26" << std::endl;
	std::cout << "default constructor" << std::endl;
	Quote q1;
	//Disc_quote dq1;
	Bulk_quote bq11;
	std::cout << "create reference" << std::endl;
	//Disc_quote& rdq1 = q1;
	Disc_quote& rdq2 = bq11;
	Quote& rq1 = q1;
	Quote& rq2 = rdq2;
	Quote& rq3 = bq11;

	Bulk_quote& rbq1 = bq11;

	std::cout << "copy constructor" << std::endl;
	Quote q2(q1);
	Quote q3(bq11);
	Quote q4(rdq2);

	//Bulk_quote bq2(q1);
	//Bulk_quote bq3(rdq2);
	Bulk_quote bq3(bq11);

	std::cout << "copy operator=" << std::endl;
	Quote q5;
	q5 = q1;
	Quote q6;
	q6 = bq11;
	Quote q7;
	q7 = rdq2;
	Bulk_quote bq4;
	bq4 = bq11;
	//Bulk_quote bq5;
	//bq4 = rqd2;

	std::cout << "move constructor" << std::endl;
	Quote q8(std::move(q1));
	Quote q9(std::move(bq11));
	Quote q10(std::move(rdq2));

	Bulk_quote bq6(std::move(bq11));

	std::cout << "move operator=" << std::endl;
	Quote q11;
	q11 = std::move(q5);
	Quote q12;
	q12 = std::move(bq4);
	Quote q13;
	q13 = std::move(rdq2);
	Bulk_quote bq66;
	bq66 = std::move(bq11);
	//Bulk_quote bq7;
	//bq7 = rqd2;

	std::cout << "Exercise 15.28" << std::endl;
	std::vector<Quote> v1;
	Quote q28("q28", 5);
	Bulk_quote bq28("bq28", 5, 3, 0.2);
	v1.push_back(q28);
	v1.push_back(bq28);

	double result = 0.0;
	std::for_each(v1.begin(), v1.end(), [&result](Quote & q) {result += q.net_price(5); });

	std::cout << "Total price in v1: "<< result << std::endl;
	
	std::cout << "Exercise 15.29" << std::endl;
	std::vector<std::shared_ptr<Quote>> v2;
	v2.push_back(std::make_shared<Quote>(q28));
	v2.push_back(std::make_shared<Bulk_quote>(bq28));
	result = 0.0;
	std::for_each(v2.begin(), v2.end(), [&result](std::shared_ptr<Quote> q) {result += q->net_price(5); });

	std::cout << "Total price in v2: " << result << std::endl;

	std::cout << "Exercise 15.30" << std::endl;
	Basket bk;
	bk.add_item(q28);
	bk.add_item(bq28);
	std::cout << "Total price in basket: " << bk.total_receipt() << std::endl;

	std::cout << "Exercise 15.39, 15.41, 15.42a" << std::endl;
	std::ifstream in39("cp15.txt");
	//runQueries(in39);
	Query q = Query("fiery") & Query("bird") | Query("wind");
	//Query q = Query("fiery") & Query("bird");
	//Query q = Query("fiery");
	//Query q = Query("bird");

	//15.41
	//Query q = Query(std::string("fiery")) & Query(std::string("bird")) | Query(std::string("wind"));
	////Query q = Query(std::string("fiery")) & Query(std::string("bird"));
	////Query q = Query(std::string("fiery"));
	////Query q = Query(std::string("bird"));
	std::cout << q << std::endl;
	//print(std::cout, q.eval(TextQuery(in39))) << std::endl;
	//15.42a
	//print(std::cout, q.eval(TextQuerySentence(in39))) << std::endl;

	//15.42c
	runQueries(in39);
	in39.close();


}

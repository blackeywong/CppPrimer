// CP16.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <sstream>
#include <iterator>
#include <vector>
#include <list>
#include <string>
#include <utility>
#include "Blob.h"
#include "Screen.h"
#include "Vec.h"
#include <algorithm>
#include "../CP11/sales_data.h"
#include <unordered_set>
#include "SharedPtr.h"
//16.4
template<typename It, typename V>
It myFind(It start, It end, const V& val) {
	while (start != end) {
		if (*start == val)
			return start;
		++start;
	}
	return end;
}

//16.5
template<typename T, unsigned N>
void myPrint(const T (&arr)[N]){
	for (T t : arr)
		std::cout << t << " ";
}

//16.6
template<typename T, unsigned N>
T* begin(const T (&arr)[N]) {
	return arr;
}

template<typename T, unsigned N>
T* end(const T(&arr)[N]) {
	return arr+N;
}

//16.7
template<typename T, unsigned N>
constexpr unsigned arrSize(const T (&arr)[N]) {
	return N;
}

//16.19
template<typename T>
void printContainer(T& container) {
	for (typename T::size_type i = 0; i < container.size(); ++i) {
		std::cout << container[i] << " ";
	}
}

//16.20
template<typename T>
void printContainer2(T& container) {
	for (auto i = container.begin(); i != container.end(); ++i) {
		std::cout << *i << " ";
	}
}
template<typename T> void f1(T, T) {}

//16.47
template<typename F, typename T1, typename T2>void flip(F f, T1&& t1, T2&& t2) {
	f(std::forward<T2>(t2), std::forward<T1>(t1));
}

void f(int t1, int t2) {
	std::cout << t1 - t2 << std::endl;
}

//16.48
template<typename T>std::string debug_rep(const T& t) {
	std::ostringstream os;
	os << t;
	return os.str();
}

template<typename T>std::string debug_rep(T* t) {
	std::ostringstream os;
	os << "pointer: " << t;
	if (t) os << debug_rep(*t);
	else os << "null pointer.";
	return os.str();
}

std::string debug_rep(const std::string& s) {
	return '"' + s + '"';
}

//16.65
template<> std::string debug_rep(char* s) {
//std::string debug_rep(char * s) {
	return debug_rep(std::string(s));
}

template<> std::string debug_rep(const char* s) {
//std::string debug_rep(const char* s) {
	return debug_rep(std::string(s));
}

//16.50
template <typename T> void f50(T) { std::cout << "f50(T)" << std::endl; }
template <typename T> void f50(const T*) { std::cout << "f50(const T*)" << std::endl; }
template <typename T> void g50(T) { std::cout << "g50(T)" << std::endl; }
template <typename T> void g50(T*) { std::cout << "g50(T*)" << std::endl; }

//16.52
template<typename T, typename... Args>void f52(const T& t, const Args&... args) {
	std::cout << sizeof...(Args) << std::endl;
	std::cout << sizeof...(args) << std::endl;
}

//16.53
template<typename T>
std::ostream& print53(std::ostream& out, const T& t) {
	out << t;
	return out;
}

template<typename T, typename... Args>
std::ostream& print53(std::ostream& out, const T& t, const Args&... args) {
	out << t <<", ";
	return print53(out, args...);
}

//16.56
template<typename... Args>
std::ostream& errorMsg(std::ostream& out, const Args&... args) {
	return print53(out, debug_rep(args)...);
}

//16.63
//template<typename T>unsigned count_in_vector(const std::vector<T>& v, const T& val) {
template<typename T>unsigned count_in_vector(const std::vector<T>& v, const T val) {
	unsigned res = 0;
	//std::for_each(v.begin(), v.end(), [&res, &val](const T& t) {if (t == val) ++res; });
	for (const T& t : v) {
		if (t == val) ++res;
	}
	return res;
}

//template<> unsigned count_in_vector(const std::vector<char*>& v, char* const& val) {
template<> unsigned count_in_vector(const std::vector<char*>& v, char* const val) {
	//unsigned count_in_vector(const std::vector<char*>& v, char* val) {
	unsigned res = 0;
	for (char* t : v) {
		if (strcmp(t, val) == 0) ++res;
	}
	return res;
}

//template<> unsigned count_in_vector(const std::vector<const char*>& v, const char* const& val) {
template<> unsigned count_in_vector(const std::vector<const char*> & v, const char* const val) {
//unsigned count_in_vector(const std::vector<const char*>& v, const char* const& val) {
	unsigned res = 0;
	for (const char* t : v) {
		if (strcmp(t, val) == 0) ++res;
	}
	return res;
}

int main()
{
	std::cout << "Exercise 16.4" << std::endl;
	std::vector<int> v4 = {1, 3, 5, 7};
	//std::cout << *myFind<decltype(v4.begin()), int>(v4.begin(), v4.end(), 3) << std::endl;
	std::cout << *myFind(v4.begin(), v4.end(), 3) << std::endl;

	std::list<std::string> l4 = {"hello", "world", "haha", "hehe"};
	//std::cout << *myFind<decltype(l4.begin()), std::string>(l4.begin(), l4.end(), "haha") << std::endl;
	std::cout << *myFind(l4.begin(), l4.end(), "haha") << std::endl;

	std::cout << "Exercise 16.5" << std::endl;
	int a5[5] = {1,3,5,7,9};
	//myPrint<int, 5>(a5);
	myPrint(a5);
	std::cout << std::endl;
	std::string s5[4] = { "hello", "world", "haha", "hehe" };
	//myPrint<std::string, 4>(s5);
	myPrint(s5);
	std::cout << std::endl;

	std::cout << "Exercise 16.7" << std::endl;
	int a7[arrSize(a5)] = { 3,8 };
	//myPrint<int, arrSize(a5)>(a7);
	myPrint(a7);
	std::cout << std::endl;

	std::cout << "Exercise 16.12" << std::endl;
	Blob<std::string> blob12;
	blob12.push_back("hello");
	std::cout << blob12[0] << std::endl;
	
	//BlobPtr<std::string> bp12(blob12);
	//std::cout << *bp12 << std::endl;
	
	//Blob<std::string> blob13({ "hello" });

	//std::cout << (blob12 == blob13) << std::endl;

	//ConstBlobPtr<std::string> cbp12(blob12);
	//std::cout << *cbp12 << std::endl;

	std::cout << "Exercise 16.14, 16.15" << std::endl;
	Screen<int> scr;
	//std::cin >> scr;
	//std::cout << scr << std::endl;

	std::cout << "Exercise 16.16" << std::endl;
	Vec <std::string> vec16;
	vec16.push_back(std::string("hello"));
	Vec<std::string> vec17(vec16);
	std::cout << (vec16 == vec17) << std::endl;
	std::string s16("world");
	vec16.push_back(s16);
	Vec<std::string> vec18;
	vec18 = vec16;
	std::cout << (vec17 < vec18) << std::endl;

	std::cout << "Exercise 16.19" << std::endl;
	printContainer(blob12);

	std::cout << "Exercise 16.20" << std::endl;
	printContainer2(v4);

	std::cout << "Exercise 16.24" << std::endl;
	//Blob<int> blob24(v4.begin(), v4.end());
	//std::cout << blob24[1] << std::endl;

	std::cout << "Exercise 16.31" << std::endl;
	int* p = new int(5);
	UniquePtr<int> up31(p);
	std::cout << *up31 << std::endl;
	up31.release();
	//16.34
	char a[4] = "bye";
	//const char a[4] = "bye";
	std::cout << a << std::endl;

	//auto & b = a;
	char(&b)[4] = a;
	//const char(const& c)[4] = a;
	const char* const& d = a;
	std::cout << b << std::endl;

	//16.36
	std::cout << "Exercise 16.36" << std::endl;
	int i = 0, j = 42, * pi = &i;
	const int* cpi = &i;
	int* const pci = &i;
	//f1(pi, cpi);
	f1(pi, pci);

	//16.47
	std::cout << "Exercise 16.47" << std::endl;
	int i47 = 1;
	f(i47, 42);
	flip(f, i47, 42);

	//16.50
	std::cout << "Exercise 16.50" << std::endl;
	int i50 = 42, * p50 = &i50;
	const int ci = 0, * p2 = &ci;
	g50(42); g50(p50); g50(ci); g50(p2);
	f50(42); f50(p50); f50(ci); f50(p2);

	//16.52
	std::cout << "Exercise 16.52" << std::endl;
	int i52 = 0; double d52 = 3.14; std::string s52 = "hello world";

	f52(i52, s52, 42, d52);
	f52(s52, 42, "hi");
	f52(d52, s52);
	f52("hi");

	//16.53
	std::cout << "Exercise 16.53" << std::endl;

	print53(std::cout, 5);
	std::cout << std::endl;
	print53(std::cout, 5, "hi", i52, d52, s52);
	std::cout << std::endl;

	//16.56
	std::cout << "Exercise 16.56" << std::endl;
	errorMsg(std::cout, i52, s52, 42, d52);
	std::cout << std::endl;
	errorMsg(std::cout, 5, "hi", i52, d52, s52);
	std::cout << std::endl;

	//16.58
	std::cout << "Exercise 16.58" << std::endl;
	Vec<std::string> sv;
	sv.emplace_back(10, 'c');
	sv.emplace_back(std::string("hi"));
	std::for_each(sv.begin(), sv.end(), [](std::string& s) {std::cout << s << ", "; });
	std::cout << std::endl;

	//16.61
	std::cout << "Exercise 16.61" << std::endl;
	SharedPtr<std::string> sp61 = makeShared<std::string>(10, 'd');
	std::cout << *sp61 << std::endl;

	//16.62
	std::cout << "Exercise 16.62" << std::endl;
	std::unordered_multiset<Sales_data> rec62;
	rec62.insert(Sales_data("11",4,7.0));
	rec62.insert(Sales_data("22", 5, 8.0));
	rec62.insert(Sales_data("33", 6, 9.0));
	std::for_each(rec62.begin(), rec62.end(), [](const Sales_data& sd) {std::cout << sd << std::endl; });

	std::cout << "Exercise 16.63" << std::endl;
	std::vector<std::string> vs63 = { "hi", "ha", "he", "he" };
	std::vector<int> vi63 = { 1,3,5,7,9,5,1,5 };
	std::vector<double> vd63 = { 1.0,3.0,5.0 };

	std::cout << count_in_vector(vs63, std::string("he")) << std::endl;
	std::cout << count_in_vector(vi63, 5) << std::endl;
	std::cout << count_in_vector(vd63, 1.5) << std::endl;

	std::cout << "Exercise 16.64" << std::endl;
	//std::vector<char*> cp64 = { "a", "bb", "ccc", "dddd" };
	std::vector<const char*> vcp64 = { "a", "bb", "ccc", "dddd" };
	std::cout << count_in_vector(vcp64, "a") << std::endl;

}




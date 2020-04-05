#pragma once
#ifndef _STRBLOB_H
#define _STRBLOB_H
#include <memory>
#include <vector>
#include <string>
#include <initializer_list>

using namespace std;

class StrBlobPtr;
class ConstStrBlobPtr;
class StrBlob {
	friend class StrBlobPtr;
	friend class ConstStrBlobPtr;
public:
	StrBlob();
	StrBlob(initializer_list<string> li);
	StrBlob(const vector<string>& v);

	int size() const;
	bool empty() const;
	//StrBlob operator=(const StrBlob& right);
	StrBlob& push_back(const string& s);
	StrBlob& push_back(string&& s);
	void pop_back();
	void erase(int index);
	string front() const;
	string back() const;
	int find(const string s) const;
	string at(const int index) const;

	StrBlobPtr begin();
	StrBlobPtr end();
	//14.16
	bool operator==(const StrBlob& b) const;
	bool operator!=(const StrBlob& b) const { return !(*this == b); }
	//14.18
	bool operator<(const StrBlob& b) const;
	//14.26
	string& operator[](std::size_t n) { check(n); return (*data)[n]; }
	const string& operator[](std::size_t n) const { check(n); return (*data)[n]; }
protected:
	shared_ptr<vector<string>> data;
	void check(unsigned int index) const;
};

class StrBlobPtr {
	//14.28
	friend StrBlobPtr operator+(StrBlobPtr& sbp, int n);
	friend StrBlobPtr operator+(int n, StrBlobPtr& sbp);
	friend StrBlobPtr operator-(StrBlobPtr& sbp, int n);
	friend int operator-(StrBlobPtr& sbp1, StrBlobPtr& sbp2);

public:
	StrBlobPtr() : curr(0) {}
	StrBlobPtr(const StrBlob& sb, size_t sz = 0) : wptr(sb.data), curr(sz) { }

	string& deref() const;
	StrBlobPtr& incr();
	//14.16
	bool operator==(const StrBlobPtr& b) const;
	bool operator!=(const StrBlobPtr& b) const { return !(*this == b); }
	//14.18
	bool operator<(const StrBlobPtr& b) const;
	//14.26
	string& operator[](std::size_t n) { check(n+curr, string("index overflow")); return (*wptr.lock())[n + curr]; }
	const string& operator[](std::size_t n) const { check(n+curr, string("index overflow")); return (*wptr.lock())[n + curr]; }
	//14.27
	StrBlobPtr& operator++() { check(curr + 1, string("index overflow")); ++curr;  return *this;}
	StrBlobPtr operator++(int) { StrBlobPtr sbp = *this;  check(curr + 1, string("index overflow")); ++curr;  return sbp; }
	StrBlobPtr& operator--() { check(curr - 1, string("index overflow")); --curr;  return *this; }
	StrBlobPtr operator--(int) { StrBlobPtr sbp = *this;  check(curr - 1, string("index overflow")); --curr;  return sbp; }

	string& operator*() const { auto p = check(curr, string("dereference past end")); return(*p)[curr]; }
	string* operator->() const { return &operator*(); }
protected:
	shared_ptr<vector<string>> check(size_t, string&) const;

	weak_ptr<vector<string>> wptr;
	size_t curr;
};

class ConstStrBlobPtr {
public:
	ConstStrBlobPtr() : curr(0) {}
	ConstStrBlobPtr(const StrBlob& sb, size_t sz = 0) : wptr(sb.data), curr(sz) { }

	string& deref() const;
	ConstStrBlobPtr& incr();
	//14.30
	const string& operator*() const { auto p = check(curr, string("dereference past end")); return(*p)[curr]; }
	const string* operator->() const { return &operator*(); }

protected:
	shared_ptr<vector<string>> check(size_t, string&) const;

	const weak_ptr<vector<string>> wptr;
	size_t curr;
};

//14.32
class StrBlobPtrPtr {
public:
	StrBlobPtr* operator->() const { shared_ptr<StrBlobPtr> p = wptr.lock(); return &(*p); }

protected:
	weak_ptr<StrBlobPtr> wptr;

};

#endif

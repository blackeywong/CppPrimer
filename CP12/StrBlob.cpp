#include <stdexcept>
#include <algorithm>
#include <vector>
#include "StrBlob.h"
using namespace std;

StrBlob::StrBlob() {
	data = make_shared<vector<string>>();
}

StrBlob::StrBlob(initializer_list<string> li) {
	data = make_shared<vector<string>>(li);
}

StrBlob::StrBlob(const vector<string>& v) {
	data = make_shared<vector<string>>(v);
}

int StrBlob::size() const {
	return data->size();
}

bool StrBlob::empty() const {
	return data->empty();
}

//StrBlob StrBlob::operator=(const StrBlob& right) {
//	data = right.data;
//	return *this;
//}

StrBlob& StrBlob::push_back(const string& s) {
	data->push_back(s);
	return *this;
}

StrBlob& StrBlob::push_back(string&& s) {
	data->push_back(std::move(s));
	return *this;
}

void StrBlob::pop_back() {
	check(size()-1);
	data->pop_back();
}

void StrBlob::erase(int index) {
	check(index);
	data->erase(data->begin() + index);
}

string StrBlob::front() const {
	check(0);
	return data->front();
}
string StrBlob::back() const {
	check(size() - 1);
	return data->back();
}

int StrBlob::find(const string s) const {
	auto it = ::find(data->begin(), data->end(), s);
	if (it == data->end()) return -1;
	else return it - data->begin();
}

string StrBlob::at(const int index) const {
	check(index);

	return data->at(index);
}

void StrBlob::check(unsigned int index) const {
	if (index < 0 || index >= data->size())
		throw out_of_range("invalid index");
}

bool StrBlob::operator==(const StrBlob& b) const {
	return (*data).size() == (*b.data).size() && equal((*data).begin(), (*data).end(), (*b.data).begin());
}

bool StrBlob::operator<(const StrBlob& b) const {
	auto pa = (*data).begin(), pb = (*b.data).begin();

	while (pa < (*data).end() && pb < (*b.data).begin()) {
		if (*pa < *pb) return true;
		if (*pa > * pb) return false;
	}

	if (pa == (*data).end() && pb == (*b.data).begin()) return false;
	if (pa < (*data).end()) return false;
	return true;
}

//Exercise 12.19
StrBlobPtr StrBlob::begin() {
	return StrBlobPtr(*this); 
}

StrBlobPtr StrBlob::end() {
	return StrBlobPtr(*this, data->size()); 
}

bool StrBlobPtr::operator==(const StrBlobPtr& b) const {
	auto sa = wptr.lock();
	auto sb = b.wptr.lock();
	return (*sa).size() == (*sb).size() && equal((*sa).begin(), (*sa).end(), (*sb).begin()) && curr == b.curr;
}

bool StrBlobPtr::operator<(const StrBlobPtr& b) const {
	auto sa = wptr.lock();
	auto sb = b.wptr.lock();
	auto pa = (*sa).begin(), pb = (*sb).begin();

	while (pa < (*sa).end() && pb < (*sb).begin()) {
		if (*pa < *pb) return true;
		if (*pa > * pb) return false;
	}

	if (pa == (*sa).end() && pb == (*sb).begin()) return false;
	if (pa < (*sa).end()) return false;
	return true;
}

string& StrBlobPtr::deref() const {
	string s("exception in incr()");
	shared_ptr<vector<string>> sp = check(curr, s);

	//return sp->data[curr];
	return (*sp)[curr];
}

StrBlobPtr& StrBlobPtr::incr() {
	string s("exception in incr()");
	shared_ptr<vector<string>> sp = check(curr++, s);
	return *this;
}

shared_ptr<vector<string>> StrBlobPtr::check(size_t sz, string& s) const {
	shared_ptr<vector<string>> sp = wptr.lock();
	if (!sp) {
		throw invalid_argument(s);
	}
	if (sz >= (*sp).size()) {
		throw out_of_range(s);
	}
	return sp;
}

string& ConstStrBlobPtr::deref() const {
	string s("exception in incr()");
	shared_ptr<vector<string>> sp = check(curr, s);

	//return sp->data[curr];
	return (*sp)[curr];
}

ConstStrBlobPtr& ConstStrBlobPtr::incr() {
	string s("exception in incr()");
	shared_ptr<vector<string>> sp = check(curr++, s);
	return *this;
}

shared_ptr<vector<string>> ConstStrBlobPtr::check(size_t sz, string& s) const {
	shared_ptr<vector<string>> sp = wptr.lock();
	if (!sp) {
		throw invalid_argument(s);
	}
	if (sz >= (*sp).size()) {
		throw out_of_range(s);
	}
	return sp;
}

StrBlobPtr operator+(StrBlobPtr& sbp, int n) {
	sbp.check(sbp.curr + n, string("index overflow"));
	StrBlobPtr sbp2(sbp);
	sbp2.curr += n;
	return sbp2;
}

StrBlobPtr operator+(int n, StrBlobPtr& sbp) {
	return sbp + n;
}

StrBlobPtr operator-(StrBlobPtr& sbp, int n) {
	sbp.check(sbp.curr - n, string("index overflow"));
	StrBlobPtr sbp2(sbp);
	sbp2.curr -= n;
	return sbp2;
}

int operator-(StrBlobPtr& sbp1, StrBlobPtr& sbp2) {
	return sbp1.curr - sbp2.curr;
}


#pragma once
#ifndef _BLOB_H
#define _BLOB_H
#include <memory>
#include <vector>
#include <string>
#include <initializer_list>
#include "SharedPtr.h"
//16.12
template<typename> class BlobPtr;
template<typename> class ConstBlobPtr;
template<typename> class Blob;
template<typename T> bool operator==(const Blob<T>&, const Blob<T>&);
template<typename T>
class Blob {
public:
	friend class BlobPtr<T>;
	friend class ConstBlobPtr<T>;
	friend bool operator==<T>(const Blob<T>& b1, const Blob<T>& b2);
	typedef T value_type;
	typedef typename std::vector<T>::size_type size_type;

	size_type size() const { return data->size(); }
	bool empty() const { return data->empty(); }

	//Blob() :data(std::make_shared<std::vector<T>>()) {}
	Blob() :data(make_shared<std::vector<T>>()) {}
	
	//16.29
	//Blob(std::initializer_list<T> il):data(std::make_shared<std::vector<T>>(il)) {}
	//16.24
	template<typename It> Blob(It start, It end);

	void push_back(const T& val) { data->push_back(val); }
	void push_back(T&& val) { data->push_back(std::move(val)); }
	void pop_back();

	T& back();
	T& front();
	T& operator[](size_type n);
private:
	//16.29
	//std::shared_ptr<std::vector<T>> data;
	SharedPtr<std::vector<T>> data;
	void check(size_type n, const std::string& msg) const;
};

//template<typename T>
//template<typename It> Blob<T>::Blob(It start, It end):data(std::make_shared<std::vector<T>>(start, end)) {}

template<typename T> bool operator==<T>(const Blob<T>& b1, const Blob<T>& b2) {
	return equal(b1.data->begin(), b1.data->end(), b2.data->begin(), b2.data->end());
}

template<typename T>
void Blob<T>::check(size_type n, const std::string& msg) const {
	if (n >= size()) throw std::out_of_range(msg);
}

template<typename T>
T& Blob<T>::back() {
	//if (size() == 0) throw out_of_range("empty vector.");
	check(0, "back on empty Blob");
	return data->back();
}

template<typename T>
T& Blob<T>::front() {
	//if (size() == 0) throw out_of_range("empty vector.");
	check(0, "back on empty Blob");
	return data->front();
}


template<typename T>
T& Blob<T>:: operator[](size_type n) {
	check(n, "operator[] out of range");
	return (*data)[n];
}

template<typename T>
void Blob<T>::pop_back() {
	check(0, "pop_back on empty Blob"); 
	data->pop_back();
}

template<typename T>
class BlobPtr {
public:
	BlobPtr() :cur(0) {}
	BlobPtr(Blob<T>& b, typename Blob<T>::size_type sz = 0) :wptr(b.data), cur(sz) {}

	BlobPtr& operator++();
	BlobPtr& operator--();
	BlobPtr operator++(int);
	BlobPtr operator--(int);

	T& operator*() const { return (*(check(cur, "* for BlobPtr")))[cur]; }
private:
	//16.29
	//std::shared_ptr<std::vector<T>> check(typename Blob<T>::size_type n, const std::string& msg) const;
	SharedPtr<std::vector<T>> check(typename Blob<T>::size_type n, const std::string& msg) const;
	std::weak_ptr<std::vector<T>> wptr;
	typename Blob<T>::size_type cur;
};

template<typename T>
//std::shared_ptr<std::vector<T>> BlobPtr<T>::check(typename Blob<T>::size_type n, const std::string& msg) const {
SharedPtr<std::vector<T>> BlobPtr<T>::check(typename Blob<T>::size_type n, const std::string& msg) const {
	auto sp = wptr.lock();
	if (n >= sp->size()) throw std::out_of_range(msg);
	return sp;
}

template<typename T>
BlobPtr<T>& BlobPtr<T>::operator++() {
	check(cur + 1, "++ operator");
	++cur;
	return *this;
}

template<typename T>
BlobPtr<T>& BlobPtr<T>::operator--() {
	check(cur - 1, "-- operator");
	--cur;
	return *this;
}

template<typename T>
BlobPtr<T> BlobPtr<T>::operator++(int) {
	BlobPtr<T> bp = *this;
	++*this;
	return bp;
}

template<typename T>
BlobPtr<T> BlobPtr<T>::operator--(int) {
	BlobPtr bp = *this;
	--* this;
	return bp;
}


template<typename T>
class ConstBlobPtr {
public:
	ConstBlobPtr() :cur(0) {}
	ConstBlobPtr(const Blob<T>& b, typename Blob<T>::size_type sz = 0) :wptr(b.data), cur(sz) {}

	const ConstBlobPtr& operator++();
	const ConstBlobPtr& operator--();
	const ConstBlobPtr operator++(int);
	const ConstBlobPtr operator--(int);

	const T& operator*() const { return (*(check(cur, "* for ConstBlobPtr")))[cur]; }
private:
	std::shared_ptr<std::vector<T>> check(typename Blob<T>::size_type n, const std::string& msg) const;
	std::weak_ptr<std::vector<T>> wptr;
	typename Blob<T>::size_type cur;
};

template<typename T>
std::shared_ptr<std::vector<T>> ConstBlobPtr<T>::check(typename Blob<T>::size_type n, const std::string& msg) const {
	auto sp = wptr.lock();
	if (n >= sp->size()) throw std::out_of_range(msg);
	return sp;
}

template<typename T>
const ConstBlobPtr<T>& ConstBlobPtr<T>::operator++() {
	check(cur + 1, "++ operator");
	++cur;
	return *this;
}

template<typename T>
const ConstBlobPtr<T>& ConstBlobPtr<T>::operator--() {
	check(cur - 1, "-- operator");
	--cur;
	return *this;
}

template<typename T>
const ConstBlobPtr<T> ConstBlobPtr<T>::operator++(int) {
	ConstBlobPtr<T> bp = *this;
	++* this;
	return bp;
}

template<typename T>
const ConstBlobPtr<T> ConstBlobPtr<T>::operator--(int) {
	ConstBlobPtr bp = *this;
	--* this;
	return bp;
}
#endif
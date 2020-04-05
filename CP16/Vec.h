#pragma once
#ifndef _VEC_H
#define _VEC_H
#include <utility>
#include <memory>
#include <initializer_list>
//16.16
template<typename T>
class Vec {
public:
	Vec() :elements(nullptr), first_free(nullptr), cap(nullptr) {}
	Vec(const Vec& sv);
	Vec& operator=(const Vec& sv);
	~Vec();
	Vec(Vec&& sv) noexcept;
	Vec& operator=(Vec&& sv) noexcept;

	void push_back(const T& s);
	void push_back(T&& s);
	size_t size() const { return first_free - elements; }
	size_t capacity() const { return cap - elements; }
	T* begin() const { return elements; }
	T* end() const { return first_free; }

	void reserve(size_t sz);
	void resize(size_t sz);
	
	bool operator==(const Vec& b) const;
	bool operator!=(const Vec& b) const { return !(*this == b); }
	
	bool operator<(const Vec& b) const;
	
	Vec& operator=(std::initializer_list<T> list);
	
	T& operator[](std::size_t n) { return *(elements + n); }
	const T& operator[](std::size_t n) const { return *(elements + n); }
	//16.58
	template<typename... Args>
	void emplace_back(Args&&... args) { chk_n_alloc(); alloc.construct(first_free++, std::forward<Args>(args)...); }
private:
	std::allocator<T> alloc;
	void chk_n_alloc() { if (size() == capacity()) reallocate(); }
	std::pair<T*, T*> alloc_n_copy(const T* start, const T* end);
	void free();
	void reallocate(size_t sz = 0);

	T* elements;
	T* first_free;
	T* cap;

};

template<typename T>
std::pair<T*, T*> Vec<T>::alloc_n_copy(const T* start, const T* end) {
	T* data = alloc.allocate(end - start);
	return { data, std::uninitialized_copy(start, end, data) };
}

template<typename T>
void Vec<T>::free() {
	if (elements) {
		while (elements != first_free) {
			alloc.destroy(--first_free);
		}
		alloc.deallocate(elements, capacity());
		elements = first_free = cap = nullptr;
	}
}

template<typename T>
void Vec<T>::reallocate(size_t sz) {
	size_t newcap = sz > capacity() * 2 + 1 ? sz : capacity() * 2 + 1;

	T* newele = alloc.allocate(newcap);
	T* dest = newele;
	for (T* src = elements; src != first_free; ++src, ++dest) {
		alloc.construct(dest, std::move(*src));
	}
	//alloc.deallocate(elements, capacity());
	free();

	elements = newele;
	first_free = dest;
	cap = elements + newcap;
	
}

template<typename T>
Vec<T>::Vec(const Vec& sv) {
	std::pair<T*, T*> p = alloc_n_copy(sv.elements, sv.first_free);
	elements = p.first;
	cap = first_free = p.second;
}

template<typename T>
Vec<T>& Vec<T>::operator=(const Vec& sv) {
	if (this != &sv) {
		free();

		std::pair<T*, T*> p = alloc_n_copy(sv.elements, sv.first_free);
		elements = p.first;
		cap = first_free = p.second;
	}
	return *this;
}

template<typename T>
Vec<T>::~Vec() {
	free();
}

template<typename T>
Vec<T>::Vec(Vec&& sv) noexcept {
	elements = sv.elements;
	first_free = sv.first_free;
	cap = sv.cap;
	sv.elements = sv.first_free = sv.cap = nullptr;
}

template<typename T>
Vec<T>& Vec<T>::operator=(Vec&& sv) noexcept {
	if (this != &sv) {
		free();

		elements = sv.elements;
		first_free = sv.first_free;
		cap = sv.cap;
		sv.elements = sv.first_free = sv.cap = nullptr;
	}
	return *this;
}

template<typename T>
void Vec<T>::push_back(const T& s) {
	chk_n_alloc();
	alloc.construct(first_free++, s);
}

template<typename T>
void Vec<T>::push_back(T&& s) {
	chk_n_alloc();
	alloc.construct(first_free++, std::move(s));
}

template<typename T>
void Vec<T>::reserve(size_t sz) {
	if (sz > capacity())
		reallocate(sz);
}

template<typename T>
void Vec<T>::resize(size_t sz) {
	if (sz > capacity()) {
		reallocate();
	}else if (sz > size()) {
		for (T* p = first_free; p < elements + sz; ++p) {
			alloc.construct(p, T());
		}
		first_free = elements + sz;
	}
	else if (sz < size()) {
		for (T* p = elements + sz; p < first_free; ++p) {
			alloc.destroy(p);
		}
		first_free = elements + sz;
	}
}

template<typename T>
bool Vec<T>::operator==(const Vec& b) const {
	return size() == b.size() && std::equal(elements, first_free, b.elements);
}

template<typename T>
bool Vec<T>::operator<(const Vec& b) const {
	for (T* p1 = elements, *p2 = b.elements; p1 != first_free && p2 != b.first_free; ++p1, ++p2) {
		if (*p1 < *p2) return true;
		if (*p2 < *p1) return false;
	}
	if (size() < b.size()) return true;
	else return false;
}

template<typename T>
Vec<T>& Vec<T>::operator=(std::initializer_list<T> list) {
	free();

	std::pair<T*, T*> p = alloc_n_copy(list.begin(), list.end());
	elements = p.first;
	cap = first_free = p.second;
	return *this;
}


#endif
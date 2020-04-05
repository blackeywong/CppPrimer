#pragma once
#ifndef _STRVEC_H
#define _STRVEC_H
#include <string>
#include <memory>

using namespace std;
//13.39
class StrVec {
public:
	StrVec() :elements(nullptr), first_free(nullptr), cap(nullptr) {}
	StrVec(const StrVec& sv);
	StrVec(initializer_list<string> list);//13.40
	StrVec& operator=(const StrVec& sv);
	~StrVec();
	StrVec(StrVec&& sv) noexcept;
	StrVec& operator=(StrVec&& sv) noexcept;

	void push_back(const string& s);
	void push_back(string&& s);
	size_t size() const { return first_free - elements; }
	size_t capacity() const { return cap - elements; }
	string* begin() const { return elements; }
	string* end() const { return first_free; }
	
	void reserve(size_t sz);
	void resize(size_t sz);
	//14.16
	bool operator==(const StrVec& b) const;
	bool operator!=(const StrVec& b) const { return !(*this == b); }
	//14.18
	bool operator<(const StrVec& b) const;
	//14.23
	StrVec& operator=(initializer_list<string> list);
	//14.26
	string& operator[](std::size_t n) { return *(elements + n); }
	const string& operator[](std::size_t n) const { return *(elements + n); }

	//16.58
	template<typename... Args>
	inline void emplace_back(Args&&... args) {
		chk_n_alloc();
		alloc.construct(first_free++, std::forward<Args>(args)...);
	}
private:
	allocator<string> alloc;
	void chk_n_alloc() { if (size() == capacity()) reallocate(); }
	pair<string*, string*> alloc_n_copy(const string* start, const string* end);
	void free();
	void reallocate(size_t sz = 0);
	string* elements;
	string* first_free;
	string* cap;

};

#endif
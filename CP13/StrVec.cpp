#include "StrVec.h"
#include <algorithm>

StrVec::StrVec(const StrVec& sv) {
	auto p = alloc_n_copy(sv.begin(), sv.end());
	elements = p.first;
	first_free = cap = p.second;
}

StrVec::StrVec(initializer_list<string> list) {
	alloc_n_copy(list.begin(), list.end());
}

StrVec& StrVec::operator=(const StrVec& sv) {
	if (sv.begin() != elements) {
		free();
		auto p = alloc_n_copy(sv.begin(), sv.end());
		elements = p.first;
		first_free = cap = p.second;
	}

	return *this;
}

StrVec::StrVec(StrVec&& sv) noexcept {
	elements = sv.elements;
	first_free = sv.first_free;
	cap = sv.cap;
	sv.elements = sv.first_free = sv.cap = nullptr;
}


StrVec& StrVec::operator=(StrVec&& sv) noexcept {
	if (this != &sv) {
		free();
		elements = sv.elements;
		first_free = sv.first_free;
		cap = sv.cap;
		sv.elements = sv.first_free = sv.cap = nullptr;
	}

	return *this;
}

StrVec::~StrVec() {
	free();
}

bool StrVec::operator==(const StrVec& b) const {
	if (first_free - elements != b.first_free - b.elements)
		return false;
	
	for (int i = 0; i < first_free - elements; i++) {
		if (*(elements + i) != *(b.elements + i))
			return false;
	}

	return true;
}

bool StrVec::operator<(const StrVec& b) const {
	string* pa = elements, * pb = b.elements;

	while (pa < first_free && pb < b.first_free) {
		if (*pa < *pb) return true;
		if (*pa > * pb) return false;
	}

	if (pa == first_free && pb == b.first_free) return false;
	if (pa < first_free) return false;
	return true;
}

StrVec& StrVec::operator=(initializer_list<string> list) {
	free();
	alloc_n_copy(list.begin(), list.end());
	return *this;
}

void StrVec::push_back(const string& s) {
	chk_n_alloc();

	alloc.construct(first_free++, s);
}

void StrVec::push_back(string&& s) {
	chk_n_alloc();

	alloc.construct(first_free++, std::move(s));
}

void StrVec::reserve(size_t sz) {
	reallocate(sz);
}

void StrVec::resize(size_t sz) {
	if (sz > capacity()) {
		reallocate(sz);
	}

	for (int i = 0; i < sz - size(); i++) {
		alloc.construct(first_free++, "");
	}
}

pair<string*, string*> StrVec::alloc_n_copy(const string* start, const string* end) {
	string * data = alloc.allocate(end - start);
	return { data, uninitialized_copy(start, end, data) };
}

void StrVec::free() {
	//while (first_free != elements) {
	//	alloc.destroy(--first_free);
	//}
	//13.43
	allocator<string>& allo = this->alloc;
	for_each(elements, first_free, [&allo](string& s) {allo.destroy(&s); });

	alloc.deallocate(elements, size());
	elements = first_free = cap = nullptr;
}

void StrVec::reallocate(size_t sz) {
	size_t newcap = sz > capacity() * 2 + 1 ? sz : capacity() * 2 + 1;

	string* newele = alloc.allocate(newcap);
	string* dest = newele;
	string* elem = elements;
	for (size_t i = 0; i != size(); i++) {
		alloc.construct(dest++, std::move(*elem++));
	}
	free();

	elements = newele;
	first_free = dest;
	cap = elements + newcap;

}


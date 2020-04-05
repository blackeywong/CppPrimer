#include "String.h"
#include <iostream>
#include <iterator>
#include <algorithm>
using namespace std;
//13.44
String::String():element(nullptr), end(nullptr) {
}

String::String(const char* s) {
	alloc_n_copy(s, strlen(s));
}

String::String(const String& s) {
	cout << "In String copy constructor." << endl;
	alloc_n_copy(s.element, s.end - s.element);
}

String& String::operator=(const String& s) {
	cout << "In String copy-assign operator." << endl;
	free();
	alloc_n_copy(s.element, s.end - s.element);
	return *this;
}

String::String(String&& s)  noexcept {
	cout << "In String move constructor." << endl;
	element = s.element;
	end = s.end;
	s.element = nullptr;
	s.end = nullptr;
}

String& String::operator=(String && s) noexcept {
	cout << "In String move-assign operator." << endl;
	if (this != &s) {
		free();
		element = s.element;
		end = s.end;
		s.element = nullptr;
		s.end = nullptr;
	}
	return *this;
}

String::~String() {
	free();
}

bool String::operator==(const String& b) const {
	return (end - element == b.end - b.element) && equal(element, end, b.element);
}

bool String::operator<(const String& b) const {
	char* pa = element, * pb = b.element;

	while (pa < end && pb < b.end) {
		if (*pa < *pb) return true;
		if (*pa > * pb) return false;
		++pa;
		++pb;
	}

	if (pa == end && pb == b.end)
		return false;
	if (pa < end)
		return false;
	return true;
}

void String::alloc_n_copy(const char* s, int size) {
	if (s != nullptr) {
		element = alloc.allocate(size);
		end = element + size;
		//alloc.construct(end++, *s++);
		uninitialized_copy(s, s + size, element);
	}
}

void String::free() {
	if (element != nullptr) {
		int len = end - element;
		while (end != element) {
			alloc.destroy(--end);
		}
		alloc.deallocate(element, len);
		element = end = nullptr;
	}
}


ostream& operator<<(ostream& out, const String& s) {
	if (s.element != nullptr) {
		copy(s.element, s.end, ostream_iterator<char>(out));
	}
	return out;
}

#pragma once
#ifndef _STRING_H
#define _STRING_H
#include <memory>
using namespace std;
//13.44
class String {
	friend ostream& operator<<(ostream& out, const String& s);
public:
	String();
	String(const char* s);
	String(const String& s);
	String(String&& s) noexcept;
	String& operator=(const String& s);
	String& operator=(String&& s) noexcept;
	~String();
	//14.16
	bool operator==(const String& b) const;
	bool operator!=(const String& b) const { return !(*this == b); }
	//14.18
	bool operator<(const String& b) const;
	bool operator<=(const String& b) const { return *this < b || *this == b; }
	bool operator>(const String& b) const { return b > *this; }
	bool operator>=(const String& b) const { return b > *this || *this == b; }
	//14.26
	char& operator[](std::size_t n) { return *(element + n); }
	const char& operator[](std::size_t n) const { return *(element + n); }
private:
	void alloc_n_copy(const char* s, int size);
	void free();

	allocator<char> alloc;
	char* element;
	char* end;
};

#endif
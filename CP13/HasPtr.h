#pragma once
#ifndef _HASPTR_H
#define _HASPTR_H
#include <string>

class HasPtr {
	friend void swap(HasPtr& a, HasPtr& b);
	friend std::ostream& operator<<(std::ostream& out, HasPtr& hp);
public:
	HasPtr(const std::string& s = std::string()) : ps(new std::string(s)), i(0), use(new std::size_t(1)) {}
	HasPtr(const HasPtr& p) :ps(new std::string(*p.ps)), i(p.i), use(p.use) { ++* use; }
	HasPtr(HasPtr&& p) :ps(p.ps), i(p.i), use(p.use) {
		p.ps = new std::string();
		p.i = 0; *p.use = 1;
	}
	//HasPtr& operator=(const HasPtr& p);
	//HasPtr& operator=(HasPtr p);
	HasPtr& operator=(HasPtr&& p);
	~HasPtr();
private:
	std::string* ps;
	int i;
	std::size_t* use;
};
#endif
#include <iostream>
#include "HasPtr.h"


//HasPtr& HasPtr::operator=(const HasPtr& rhs) {
//	++* rhs.use;
//	--* use;
//	if (*use == 0) {
//		delete ps;
//		delete use;
//	}
//	ps = rhs.ps;
//	i = rhs.i;
//	use = rhs.use;
//	return *this;
//}

//HasPtr& HasPtr::operator=(HasPtr rhs) {
//	std::cout << "In HasPtr swap&copy operator" << std::endl;
//	swap(*this, rhs);
//	return *this;
//}

HasPtr& HasPtr::operator=(HasPtr&& p) {
	std::cout << "In HasPtr move operator" << std::endl;
	if (this != &p) {
		--* use;
		if (*use == 0) {
			delete ps;
			delete use;
		}
		ps = p.ps;
		i = p.i;
		use = p.use;
		if ((*p.use == 1)) {
			p.ps = new std::string();
			p.i = 0;
		}
	}
	return *this;
}

HasPtr::~HasPtr() {
	--* use;
	if (*use == 0) {
		delete ps;
		delete use;
	}
}

inline void swap(HasPtr& a, HasPtr& b) {
	using std::swap;
	swap(a.ps, b.ps);
	swap(a.i, b.i);
	//swap(a.use, b.use);
}

std::ostream& operator<<(std::ostream& out, HasPtr& hp) {
	out << *hp.ps << " " << hp.i << " " << *hp.use;
	return out;
}
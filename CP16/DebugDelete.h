#pragma once
#ifndef _DEBUGDELETE_H
#define _DEBUGDELETE_H
#include<iostream>
class DebugDelete {
public:
	DebugDelete(std::ostream& os = std::cerr) :out(os) {}
	template<typename T> void operator()(T* p) const { out << "deleting pointer" << std::endl; delete p; }
private:
	std::ostream& out;
	
};

#endif

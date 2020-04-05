#pragma once
#ifndef _SCREEN_H
#define _SCREEN_H
#include <iostream>
//16.14, 16.15
template<typename> class Screen;
template<typename T>
std::istream& operator>>(std::istream& in, Screen<T> & scr);
template<typename T>
std::ostream& operator<<(std::ostream& out, const Screen<T>& scr);

template<typename T>
class Screen {
	friend std::istream& operator>> <T>(std::istream& in, Screen<T>& scr);
	friend std::ostream& operator<< <T>(std::ostream& out, const Screen<T>& scr);
public:
	Screen() = default;
	Screen(const T& h, const T& w) :height(h), width(w) {}

private:
	T height;
	T width;

};

template<typename T>
std::istream& operator>>(std::istream& in, Screen<T>& scr) {
	in >> scr.height >> scr.width;
	return in;
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const Screen<T>& scr) {
	out << scr.height << " " << scr.width;
	return out;
}

#endif
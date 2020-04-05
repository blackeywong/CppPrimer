#pragma once
#ifndef _SHAREDPTR_H
#define _SHAREDPTR_H
#include <iostream>
#include "DebugDelete.h"
//https://github.com/huangmingchuan/Cpp_Primer_Answers/tree/master/ch16
//16.28

template <typename T> class SharedPtr;

template <typename T, typename D = DebugDelete>
class UniquePtr {
	friend class SharedPtr<T>;
public:
	UniquePtr() = default;
	UniquePtr(T* pointer) :ptr(pointer){}
	UniquePtr(const UniquePtr<T,D>&) = delete;
	UniquePtr& operator=(const UniquePtr<T, D>&) = delete;
	UniquePtr& operator=(const std::nullptr_t null) { if(null == nullptr) free(); return *this; }
	UniquePtr& operator=(UniquePtr<T, D>&& up) { if (this != *up) { free(); swap(up); } return *this; }

	UniquePtr(UniquePtr<T>&& up) noexcept :ptr(nullptr) { swap(up); }
	~UniquePtr() { free(); }

	operator bool() const { return ptr == nullptr; }
	T& operator*() const { return *ptr; }
	T* operator->() const { return &operator*(); }
	T* get() const { return ptr; }

	void swap(UniquePtr<T>& q) { 
		using std::swap;  
		swap(ptr, q.ptr); 
		swap(delfunc, q.delfunc);
	}

	T* release() { T* ret = ptr; free(); return ret; }
	void reset(T* q = nullptr) { free();  }
private:
	void free() {
		delfunc(ptr);
		ptr = nullptr;
	}
	T* ptr;
	D delfunc = D();

};

template<typename T, typename D>
void swap(UniquePtr<T, D>& p, UniquePtr<T, D>& q) {
	p.swap(q);
}

template <typename T>
class SharedPtr {
	typedef void (*_del_func)(T*);
public:
	SharedPtr() :ptr(nullptr), count(new unsigned(1)), delfunc(nullptr) {}
	SharedPtr(T * pointer, _del_func del = nullptr) :ptr(pointer), count(new unsigned(1)), delfunc(del) {}
	SharedPtr(const SharedPtr<T>& sp) :ptr(sp.ptr), count(sp.count),delfunc(sp.delfunc) { ++*sp.count; }
	SharedPtr(const SharedPtr<T>& sp, _del_func del) :ptr(sp.ptr), count(sp.count),delfunc(del) { ++*sp.count; }
	SharedPtr(UniquePtr<T>& up) :ptr(up.ptr), count(1), delfunc(nullptr) { up.ptr = nullptr; }
	~SharedPtr() { check_and_free(); }
	SharedPtr<T>& operator=(const SharedPtr<T>& q) { if (this != *q) { ptr = q.ptr; count = q.count; delfunc = q.delfunc; ++* count; } return *this; }

	SharedPtr<T>& operator=(SharedPtr<T>&& q) { if (this != *q) { swap(q); q.ptr = nullptr; } return *this; }
	SharedPtr(SharedPtr<T>&& sp) :ptr(sp.ptr), count(sp.count), delfunc(std::move(sp.delfunc)) { sp.ptr = nullptr; sp.count = nullptr; }

	bool empty() const { return ptr == nullptr; }
	operator bool() const { return ptr == nullptr; }
	T& operator*() const { return *ptr; }
	T* operator->() const { return &operator*(); }
	
	T* get() const { return ptr; }

	void swap(SharedPtr<T>& q) { using std::swap; swap(ptr, q.ptr); swap(count, q.count); swap(delfunc, q.delfunc); }
	bool unique() const { if (*count == 1) return true; return false; }
	
	void reset(T* q = nullptr, _del_func d = nullptr) {
		check_and_free(); 
		ptr = q; *count = 1; delfunc = d; 
		if (!ptr) delete count; 
		count = nullptr;
	}
private:
	void check_and_free() { 
		if (*count == 1)
		{
			if (delfunc) delfunc(ptr);
			else delete ptr;
			delete count;
			count = nullptr;
			ptr = nullptr;
		}
		else
		{
			--*count;
		}
		
	}
	T* ptr;
	unsigned* count;
	_del_func delfunc;
};

template<typename T>
void swap(SharedPtr<T>& p, SharedPtr<T>& q) { p.swap(q); }

template<typename T, typename... Args>
SharedPtr<T> makeShared(Args&&... args) {
	return new T(std::forward<Args>(args)...);
}

#endif

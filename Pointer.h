// Pointer.h
// Colossus Runtime
// ref-counted smart pointer


#pragma once

#include "defs.h"
#include "gc.h"


class PointerBase
{
protected:
	static RefTable reftable;
};

template<class T>
class Pointer : public PointerBase
{
public:
	Pointer() : ptr(NULL) {}
	Pointer(T* p) : ptr(p)
	{
		if(ptr)
			inc();
	}
	Pointer(const Pointer<T>& p) : ptr(p.ptr)
	{
		if(ptr)
			inc();
	}
	~Pointer()
	{
		if(ptr)
		{
			dec();
			ptr = NULL;
		}
	}
	
	Pointer<T>& operator=(T* p)
	{
		if (ptr)
			dec();
		ptr = p;
		if(ptr)
			inc();
		return *this;
	}
	Pointer<T>& operator=(Pointer<T>& p)
	{
		if(ptr)
			dec();
		ptr = (T*)p.ptr;
		if(ptr)
			inc();
		return *this;
	}
	
	T& operator*() { return *(T*)ptr; }
	T* operator->() const{return (T*)ptr; }
	
protected:
	void inc() { PointerBase::reftable.inc(ptr); }
	void dec() { PointerBase::reftable.dec(ptr); }
	
	T* ptr;
};

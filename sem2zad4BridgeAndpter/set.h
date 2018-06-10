#pragma once
#include <vector>
#include <list>

template <class T> 
class setAbstraction
{
public:
	virtual void insert(T) = 0;
	virtual void erase(T) = 0;
	virtual bool belongs(T) = 0;
	virtual void print() = 0;
	virtual int size() = 0;
};

template <class T>
class setOfVector : public setAbstraction<T>
{
	std::vector<T> vec;
public:
	void insert(T);
	void erase(T);
	bool belongs(T);
	void print();
	int size();
};


template <class T>
class setOfList : public setAbstraction<T>
{
	std::list<T> li;
public:
	void insert(T);
	void erase(T);
	bool belongs(T);
	void print();
	int size();
};

template <class T>
class set
{
	setAbstraction<T>* setabs;
public:
	set(setAbstraction<T>* abs) : setabs(abs) {};
	void insert(T);
	void erase(T);
	bool belongs(T);
	void print();
	int size();
};
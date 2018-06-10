#pragma once 
#include "List.h"
class CyclicList: virtual public List
{
public:
	CyclicList(char elem);
	virtual void cons(char elem);
//	virtual char head();
	virtual void pop();
	//void show();
};

class DoubleSidedList: virtual public List
{
protected:
	Node * prev;
public:
	DoubleSidedList(char elem) :List(elem) { prev = node;};
	virtual void cons(char elem);
//	virtual char head();
	virtual void pop();
};

class CyclicDoubleSidedList: public DoubleSidedList, public CyclicList
{
public:
	CyclicDoubleSidedList(char elem) :CyclicList(elem), DoubleSidedList(elem), List(elem)
	{
		prev->_next = prev;
	};
	virtual void cons(char elem);
	//virtual char head();
	virtual void pop();

};

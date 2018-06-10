#pragma once 
#include <iostream>
class ListIterator;
class List
{
	friend class ListIterator;
public:
	struct Node
	{
		char _elem;
		Node * _next;
	};
	class BadList
	{
	public:
		void msg()
		{
			std::cout << "Bad list exeption";
		}
	};
	List(char elem);
	virtual void cons(char elem);
	virtual char head();
	virtual void pop();
	virtual ListIterator iterate();
	virtual void show();
protected:
	Node * node;
};


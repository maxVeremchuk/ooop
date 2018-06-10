#pragma once 
#include "List.h"
class List;

class ListIterator
{
	bool start;
	List::Node * _first;
	List::Node * _current;
public:
	void begin(List*);
	char get();
	List::Node *getCur();
	List::Node *getFirst();
	void next();
	bool end();
};


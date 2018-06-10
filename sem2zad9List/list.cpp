#include "List.h"
#include "ListIterator.h"
#include "Lists.h"
#include <iostream>

List::List(char elem)
{
	node = new Node;
	node->_elem = elem;
	node->_next = NULL;
}

char List::head()
{
	if (!node)
	{
		throw BadList();
	}
	return node->_elem;
}

void List::cons(char elem)
{
	Node *temp = node;
	while (temp->_next)
	{
		temp = temp->_next;
	}
	temp->_next = new Node;
	temp->_next->_elem = elem;
	temp->_next->_next = NULL;
}

void List::pop()
{
	if (!node)
	{
		throw BadList();
	}
	Node *toDel = node;
	node = node->_next;
	delete toDel;
}

ListIterator List::iterate()
{
	ListIterator *iter = new ListIterator();
	iter->begin(this);

	return *iter;
}

void List::show()
{
	if (!node)
	{
		throw BadList();
	}
	//Node *temp = node;
	//while (temp)
	//{
	//	std::cout << temp->_elem << " ";
	//	temp = temp->_next;
	//}
	//std::cout << std::endl;
	for (auto it = this->iterate(); !it.end(); it.next())
	{
		std::cout << it.get() << " ";
		if (it.getCur()->_next == it.getFirst())
		{
			break;
		}
		
	}
}

List::Node *ListIterator::getCur()
{
	return _current;
}

List::Node *ListIterator::getFirst()
{
	return _first;
}

void ListIterator::begin(List *list)
{
	_first = list->node;
	_current = list->node;
	start = true;
}

char ListIterator::get()
{
	return _current->_elem;
}

void ListIterator::next()
{
	if (!end())
	{
		_current = _current->_next;
		start = false;
	}
}

bool ListIterator::end()
{
	return !(_current);
}

CyclicList::CyclicList(char elem):List(elem)
{
	node->_next = node;
}
void CyclicList::cons(char elem)
{
	Node *add = new Node;
	add->_elem = elem;
	add->_next = node;
	Node *tail = node->_next;
	while (tail->_next != node)
	{
		tail = tail->_next;
	}
	tail->_next = add;
}

void CyclicList::pop()
{
	Node *toDel = node;
	Node *tail = node;
	while (tail->_next != node)
	{
		tail = tail->_next;
	}

	tail->_next = node->_next;
	node = node->_next;
	if (toDel == node)
	{
		node = NULL;
	}
	delete toDel;
}

//void CyclicList::show()
//{
//	for (auto i = List::iterate(); i.end(); i.next())
//	{
//		std::cout << i.get() << " ";
//	}
//}

void DoubleSidedList::cons(char elem)
{
	List::cons(elem);
	prev = prev->_next;
}

void DoubleSidedList::pop()
{
	if (node == prev)
	{
		node = NULL;
	}
	else
	{
		List::pop();
	}
}


void CyclicDoubleSidedList::cons(char elem)
{
	CyclicList::cons(elem);
	prev = prev->_next;
}

void CyclicDoubleSidedList::pop()
{
	Node *nextTail = node;
	while (nextTail->_next != prev)
	{
		nextTail = nextTail->_next;
	}
	prev = nextTail;
	CyclicList::pop();
}
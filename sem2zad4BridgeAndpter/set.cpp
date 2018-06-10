#include "set.h"
#include <iostream>
using namespace std;

template <class T>
void setOfVector<T>::insert(T element)
{
	vec.push_back(element);

}
template <class T>
void setOfVector<T>::erase(T element)
{
	vec.erase(find(vec.begin(), vec.end(), element));
}
template <class T>
bool setOfVector<T>::belongs(T element)
{
	return (find(vec.begin(), vec.end(), element) != vec.end());
}
template <class T>
void setOfVector<T>::print()
{
	for (int i = 0; i < vec.size(); i++)
	{
		cout << vec[i] << " ";
	}
	cout << endl;
}
template <class T>
int setOfVector<T>::size()
{
	return vec.size();
}


template <class T>
void setOfList<T>::insert(T element)
{
	li.push_back(element);

}
template <class T>
void setOfList<T>::erase(T element)
{
	li.erase(find(li.begin(), li.end(), element));
}
template <class T>
bool setOfList<T>::belongs(T element)
{
	return (find(li.begin(), li.end(), element) != li.end());
}
template <class T>
void setOfList<T>::print()
{
	std::list<T>::iterator i;
	for (i = li.begin(); i != li.end(); ++i)
	{
		cout << *i << " ";
	}
	cout << endl;
}
template <class T>
int setOfList<T>::size()
{
	return li.size();
}


template <class T>
void set<T>::insert(T element)
{
	setabs->insert(element);
}
template <class T>
void set<T>::erase(T element)
{
	if (setabs->belongs(element))
	{
		setabs->erase(element);
	}
	else
	{
		cout << "Not in set" << endl;
	}
}
template <class T>
bool set<T>::belongs(T element)
{
	return setabs->belongs(element);
}
template <class T>
void set<T>::print()
{
	setabs->print();
}

template <class T>
int set<T>::size()
{
	setabs->size();
}
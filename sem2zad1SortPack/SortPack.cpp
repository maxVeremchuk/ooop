#include <iostream>
#include <ctime>
#include <stack>
#include "SortPack.h"
using namespace std;
void IntToSort::showItem()
{
	cout << value << endl;
}

int IntToSort::getValue()
{
	return value;
}

bool IntToSort::operator<(const SortedItems &item)const
{
	int tmp = (*(IntToSort*)&item).getValue();
	return (value < tmp);
}


ArrayOfInt::ArrayOfInt(int length)
{
	this->length = length;
}
void ArrayOfInt::fill()
{
	srand(time(0));
	arrayToSort = new IntToSort[length];
	int val;
	for (int i = 0; i < length; i++)
	{
		val = rand() % 100;
		arrayToSort[i] = IntToSort(val);
	}
}

void ArrayOfInt::show()
{
	for (int i = 0; i < length; i++)
	{
		cout << arrayToSort[i].getValue() << " ";
	}
	cout << endl;
}

SortedItems& ArrayOfInt::operator[](int index)
{
	return arrayToSort[index];
}

void ArrayOfInt::swap(int i, int j)
{
	IntToSort temp = arrayToSort[i];
	arrayToSort[i] = arrayToSort[j];
	arrayToSort[j] = temp;
}

ArrayOfInt::~ArrayOfInt()
{
	delete[] arrayToSort;
	length = 0;
}


void SortPack::attach(ArrayOfItems& arr, int qua)
{
	items = &arr;
	quantity = qua;
}

void SortPack::bubble()
{
	for (int i = 0; i < quantity; i++)
	{
		for (int j = i + 1; j < quantity; j++)
		{
			if ((*items)[j] < (*items)[i])
			{
				items->swap(i, j);
				increaseConter();
			}
		}
	}
}

void SortPack::shell()
{
	for (int k = quantity / 2; k >= 1; k /= 2)
	{
		for (int i = k; i < quantity; i++)
		{
			for (int j = i; j >= k && (*items)[j] < (*items)[j - k]; j -= k)
			{
				items->swap(j, j - k);
				increaseConter();
			}
		}
	}
}

void SortPack::insert()
{
	for (int j = 1; j < quantity; j++)
	{
		for (int i = j - 1; i >= 0 && (*items)[i + 1] < (*items)[i]; i--)
		{
			items->swap(i, i + 1);
			increaseConter();
		}
	}
}


void SortPack::select()
{
	int min;
	for (int i = 0; i < quantity; i++)
	{
		min = i;
		for(int j = i + 1; j < quantity; j++)
		{ 
			if ((*items)[j] < (*items)[min])
			{
				min = j;
			}
		}
		if (min != i)
		{
			items->swap(i, min);
		}
	}
}


void SortPack::quick()
{
	int low = 0;
	int hight = quantity - 1;
	stack<int> st;
	st.push(low);
	st.push(hight);
	int iter;
	while (!st.empty())
	{
		hight = st.top();
		st.pop();
		low = st.top();
		st.pop();

		iter = low - 1;
		for (int j = low; j < hight; j++)
		{
			if ((*items)[j] < (*items)[hight])
			{
				iter++;
				if (iter != j)
				{
					items->swap(iter, j);
				}
			}
		}
		items->swap(iter + 1, hight);
		if (iter + 2 < hight)
		{
			st.push(iter + 2);
			st.push(hight);
		}

		if (iter > low)
		{
			st.push(low);
			st.push(iter);
		}
	}
}



void SortPack::increaseConter()
{
	counter++;
}

void SortPack::discardCounter()
{
	counter = 0;
}

void SortPack::show()
{
	(*items).show();
}
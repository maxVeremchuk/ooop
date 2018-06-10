#include "set.cpp"
#include <iostream>

using namespace std;
int main()
{
	set<int> setInt(new setOfList<int>);
	for (int i = 0; i < 10; i++)
	{
		setInt.insert(i);
	}
	setInt.erase(9);
	setInt.print();
	return 0;
}
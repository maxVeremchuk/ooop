#include <iostream>
#include <windows.h>
#include <ctime>
#include <thread>
#include "skipList.h"
using namespace std;
int main()
{
	srand(time(0));
	SkipList list(0.5, 10);
	vector<int> v = { 1, 2, 3, 6, 1, 4, 6, 9, 1, 1, 6, 9, 2, 9, 8 };
#pragma omp parallel for num_threads(4)
	for (int i = 0; i < 15; i++)
	{
		/*int a = rand() % 10;
		cout << a << " ";*/
		list.insert(v[i]);
	}
	list.print();
	list.remove(2);
	list.remove(9);
	cout << endl;
	list.print();
	return 0;
}
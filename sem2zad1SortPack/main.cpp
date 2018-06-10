#include <iostream>
#include "SortPack.h"
using namespace std;
int main()
{
	ArrayOfInt arr(20);
	arr.fill();
	arr.show();
	SortPack sort;
	sort.attach(arr, 20);
	//sort.bubble();
	//sort.shell();
	//sort.insert();
	//sort.select();
	sort.quick();
	sort.show();
	return 0;
}
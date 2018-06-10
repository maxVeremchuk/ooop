#include <iostream>
#include "Lists.h"
using namespace std;
int main()
{
	/*CyclicList cyList('a');
	cyList.cons('b');

	cyList.pop();
	cyList.show();

	DoubleSidedList dsl('l');
	dsl.cons('d');
	dsl.pop();
	dsl.show();
*/
	CyclicDoubleSidedList cdsl('z');
	cdsl.cons('x');
	//cdsl.pop();
	cdsl.show();

	//for (auto i = first.iterate(); i.end(); i.next())
	//{
	//	std::cout << i.get() << " ";
	//}
	return 0;
}
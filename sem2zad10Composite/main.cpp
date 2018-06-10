#include <iostream>
#include <string>
#include "calculator.h"
using namespace std;
int main()
{
	string str = "((2+2)*2+(3*(1+1)+1))/5";
	Calculator *calc = new Calculator;
	calc->addOperation(parser(str));
	cout << calc->getAnswer() << endl;
	return 0;
}
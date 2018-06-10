#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <stack>
using std::string;
using std::cout;
using std::endl;

class Operation
{
public:
	virtual int getAnswer() = 0;
};

//primitives
class Sum : public  Operation
{
	Operation *first;
	Operation *second;
public:
	Sum(Operation *_first, Operation *_second)
	{
		first = _first;
		second = _second;
	}
	int getAnswer()
	{
		return  first->getAnswer() + second->getAnswer();
	}
};

class Sub : public  Operation
{
	Operation *first;
	Operation *second;
public:
	Sub(Operation *_first, Operation *_second)
	{
		first = _first;
		second = _second;
	}
	int getAnswer()
	{
		return  second->getAnswer() - first->getAnswer();
	}
};

class Mult : public  Operation
{
	Operation *first;
	Operation *second;
public:
	Mult(Operation *_first, Operation *_second)
	{
		first = _first;
		second = _second;
	}
	int getAnswer()
	{
		return  first->getAnswer() * second->getAnswer();
	}
};

class Div : public  Operation
{
	Operation *first;
	Operation *second;
public:
	Div(Operation *_first, Operation *_second)
	{
		first = _first;
		second = _second;
	}
	int getAnswer()
	{
		if (first->getAnswer())
		{
			return   second->getAnswer() / first->getAnswer();
		}
		else
		{
			cout << "Dividion by zero" << endl;
			exit(1);
		}
	}
};

class Number : public Operation
{
	int num;
public:
	void setNumber(int _num)
	{
		num = _num;
	}
	int getAnswer()
	{
		return num;
	}
};

//composite

class Calculator : public Operation
{
	std::vector<Operation*> operations;
public:
	void addOperation(Operation *op)
	{
		operations.push_back(op);
	}
	void removeOperatoin()
	{
		operations.pop_back();
	}
	Operation *getLast()
	{
		return operations.back();
	}

	int getAnswer()
	{
		return operations[0]->getAnswer();
	}
	
};


Calculator* parser(string str)
{
	Calculator* calc = new Calculator;
	Number *num;
	//polish notation
	std::stack<char> st;
	string digit = "";
	bool flagSpace = false;
	for (int i = 0; i < str.size(); i++)
	{
		digit = "";
		while (str[i] >= '0' && str[i] <= '9')
		{
			digit += str[i];
			i++;
			flagSpace = true;
		}
		if (flagSpace)
		{
			i--;


			num = new Number;
			num->setNumber(stoi(digit));
			calc->addOperation(num);
			num = NULL;


			flagSpace = false;
			continue;
		}


		if (str[i] == ')')
		{
			if (st.empty())
			{
				cout << "Error" << endl;
				exit(1);
			}
			while (st.top() != '(')
			{
				switch(st.top())
				{
				case '+':
				{
					Operation * first = calc->getLast();
					calc->removeOperatoin();
					Operation * second = calc->getLast();
					calc->removeOperatoin();
					Sum *sum = new Sum(first, second);
					calc->addOperation(sum);
					st.pop();
					break;
				}
				case '-':
				{
					Operation * first = calc->getLast();
					calc->removeOperatoin();
					Operation * second = calc->getLast();
					calc->removeOperatoin();
					Sub *sub = new Sub(first, second);
					calc->addOperation(sub);
					st.pop();
					break;
				}
				case '*':
				{
					Operation * first = calc->getLast();
					calc->removeOperatoin();
					Operation * second = calc->getLast();
					calc->removeOperatoin();
					Mult *mult = new Mult(first, second);
					calc->addOperation(mult);
					st.pop();
					break;
				}
				case '/':
				{
					Operation * first = calc->getLast();
					calc->removeOperatoin();
					Operation * second = calc->getLast();
					calc->removeOperatoin();
					Div *div = new Div(first, second);
					calc->addOperation(div);
					st.pop();
					break;
				}
				}
		
				if (st.empty())
				{
					cout << "Error" << endl;
					exit(1);
				}
			}
			if (st.top() == '(')
			{
				st.pop();
			}
			continue;

		}
		else if (str[i] == '+' || str[i] == '-')
		{
			while (!st.empty() && (st.top() == '*' || st.top() == '/'))
			{
				if (st.top() == '*')
				{
					Operation * first = calc->getLast();
					calc->removeOperatoin();
					Operation * second = calc->getLast();
					calc->removeOperatoin();
					Mult *mult = new Mult (first, second);
					calc->addOperation(mult);
					st.pop();
				}
				else
				{
					Operation * first = calc->getLast();
					calc->removeOperatoin();
					Operation * second = calc->getLast();
					calc->removeOperatoin();
					Div *div = new Div(first, second);
					calc->addOperation(div);
					st.pop();
				}
			}
		}
	/*	else if (str[i] == '*' || str[i] == '/')
		{
			while (!st.empty() && st.top() == '^')
			{
				digit += st.top();
				digit += " ";
				st.pop();
			}
		}*/

		st.push(str[i]);

	}

	while (!st.empty())
	{
		switch (st.top())
		{
		case '+':
		{
			Operation * first = calc->getLast();
			calc->removeOperatoin();
			Operation * second = calc->getLast();
			calc->removeOperatoin();
			Sum *sum = new Sum(first, second);
			calc->addOperation(sum);
			st.pop();
			break;
		}
		case '-':
		{
			Operation * first = calc->getLast();
			calc->removeOperatoin();
			Operation * second = calc->getLast();
			calc->removeOperatoin();
			Sub *sub = new Sub(first, second);
			calc->addOperation(sub);
			st.pop();
			break;
		}
		case '*':
		{
			Operation * first = calc->getLast();
			calc->removeOperatoin();
			Operation * second = calc->getLast();
			calc->removeOperatoin();
			Mult *mult = new Mult(first, second);
			calc->addOperation(mult);
			st.pop();
			break;
		}
		case '/':
		{
			Operation * first = calc->getLast();
			calc->removeOperatoin();
			Operation * second = calc->getLast();
			calc->removeOperatoin();
			Div *div = new Div(first, second);
			calc->addOperation(div);
			st.pop();
			break;
		}
		default:
		{
			cout << "Error" << endl;
			exit(1);
			break;
		}
		}
	}
	return calc;
}

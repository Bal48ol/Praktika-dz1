#include <vector>
#include <string>
#include <iostream>
#include "C:\Users\Yakov\source\repos\Praktika dz1\Praktika dz1\Header.h"

int pos = 0;
std::string expr;
std::vector <char> OPZ;
std::vector <int> stack;

bool E()
{
	if (T() && E_())
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool E_()
{
	if (pos == expr.length())
	{
		return true;
	}

	if ((expr[pos] == '+') || (expr[pos] == '-'))
	{
		char symb = expr[pos];
		pos++;

		if (!T())
		{
			return false;
		}

		OPZ.push_back(symb);

		if (!E_())
		{
			return false;
		}
		return true;
	}
	return true;
}

bool T()
{
	if (F() && T_())
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool T_()
{
	if (pos == expr.length())
	{
		return true;
	}

	if ((expr[pos] == '*') || (expr[pos] == '/'))
	{
		char symb = expr[pos];
		pos++;

		if (!F())
		{
			return false;
		}

		OPZ.push_back(symb);

		if (!T_())
		{
			return false;
		}
		return true;
	}
	return true;
}

bool F()
{
	if (pos == expr.length())
	{
		return false;
	}

	if (isdigit(expr[pos]))
	{
		OPZ.push_back(expr[pos]);
		pos++;
		return true;
	}

	if (expr[pos] == '(')
	{
		pos++;
		if (!E())
		{
			return false;
		}
		if (expr[pos] != ')')
		{
			return false;
		}
		pos++;
		return true;
	}
	return false;
}

int calc_OPZ()
{
	int a, b;
	for (int i = 0; i < OPZ.size(); i++)
	{
		if ('0' <= OPZ[i] && OPZ[i] <= '9')
		{
			stack.push_back(OPZ[i] - '0');
		}
		if (OPZ[i] == '+')
		{
			a = stack.back();
			stack.pop_back();
			b = stack.back();
			stack.pop_back();
			stack.push_back(a + b);
		}

		if (OPZ[i] == '-')
		{
			a = stack.back();
			stack.pop_back();
			b = stack.back();
			stack.pop_back();
			stack.push_back(a - b);
		}

		if (OPZ[i] == '*')
		{
			a = stack.back();
			stack.pop_back();
			b = stack.back();
			stack.pop_back();
			stack.push_back(a * b);
		}

		if (OPZ[i] == '/')
		{
			a = stack.back();
			stack.pop_back();
			b = stack.back();
			stack.pop_back();
			stack.push_back(a / b);
		}
	}
	if (stack.size() != 1)
	{
		throw "Error.";
	}
	return stack[0];
}

int main()
{
	expr = "(2+4)*6";
	if (!E())
	{
		throw "Error.";
	}
	if (pos != expr.length())
	{
		throw "Error.";
	}
	std::cout << calc_OPZ();
}

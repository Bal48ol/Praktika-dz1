#include <vector>
#include <string>
#include <iostream>
#include "C:\Users\Yakov\source\repos\Praktika dz1\Praktika dz1\Header.h"

int pos = 0;
std::string exemp;
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
	if (pos == exemp.length())
	{
		return true;
	}

	if ((exemp[pos] == '+') || (exemp[pos] == '-'))
	{
		char symb = exemp[pos];
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
	if (pos == exemp.length())
	{
		return true;
	}

	if ((exemp[pos] == '*') || (exemp[pos] == '/'))
	{
		char symb = exemp[pos];
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
	if (pos == exemp.length())
	{
		return false;
	}

	if (isdigit(exemp[pos]))
	{
		OPZ.push_back(exemp[pos]);
		pos++;
		return true;
	}

	if (exemp[pos] == '(')
	{
		pos++;
		if (!E())
		{
			return false;
		}
		if (exemp[pos] != ')')
		{
			return false;
		}
		pos++;
		return true;
	}
	return false;
}

int main()
{
	exemp = "2-3-4"; //(2-3)*4
	if (!E())
	{
		throw "Error.";
	}
	if (pos != exemp.length())
	{
		throw "Error.";
	}
	std::cout << calc_OPZ();
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
			b = stack.back();
			stack.pop_back();
			a = stack.back();
			stack.pop_back();
			stack.push_back(a + b);
		}

		if (OPZ[i] == '-')
		{
			b = stack.back();
			stack.pop_back();
			a = stack.back();
			stack.pop_back();
			stack.push_back(a - b);
		}

		if (OPZ[i] == '*')
		{
			b = stack.back();
			stack.pop_back();
			a = stack.back();
			stack.pop_back();
			stack.push_back(a * b);
		}

		if (OPZ[i] == '/')
		{
			b = stack.back();
			stack.pop_back();
			a = stack.back();
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
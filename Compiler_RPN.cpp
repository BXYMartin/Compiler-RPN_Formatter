// Compiler_RPN.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
#include <string>
#include <stack> 
#include <map> 

using namespace std;

class RPN {
public:
	map<char, int> priList;
	stack<char> opStack;
	string reg, mod;
public:
	RPN(string target)
	{
		reg = target;
		priList.insert(pair<char, int>('#', -2));
		priList.insert(pair<char, int>('=', -1));

		priList.insert(pair<char, int>('(', 0));
		priList.insert(pair<char, int>('[', 0));
		priList.insert(pair<char, int>('{', 0));
		priList.insert(pair<char, int>(')', 0));
		priList.insert(pair<char, int>(']', 0));
		priList.insert(pair<char, int>('}', 0));

		priList.insert(pair<char, int>('+', 1));
		priList.insert(pair<char, int>('-', 1));

		priList.insert(pair<char, int>('*', 2));
		priList.insert(pair<char, int>('/', 2));

		
		
	}

	bool isOp(char c)
	{
		return (priList.count(c)) ? true : false;
	}

	bool isEnd(char b, char c)
	{
		if ((b == '(' && c == ')') || (b == '[' && c == ']') || (b == '{' && c == '}') || (b == '#' && c == '#'))
			return true;
		return false;
	}

	char checkStack(char c)
	{
		char t = '\0';
		if(!opStack.empty()){
			int pri = (priList.find(opStack.top()))->second;
			int now = priList.find(c)->second;
			if ((c == '(') || (c == '[') || (c == '{'))
			{
				opStack.push(c);
				return t;
			}
			if (pri >= now)
			{
				t = opStack.top();
				opStack.pop();
				if (c == '#' && t != '#')
				{
					mod = mod + t;
					while ((t = opStack.top()) != '#')
					{
						mod = mod + t;
						opStack.pop();
					}
					t = '\0';
				}
				else if (c == '#' && t == '#')
				{
					t = '\0';
					return t;
				}
				if (!opStack.empty() && isEnd(t, c))
					t = '\0';
				else
				{
					if ((c == ')') || (c == ']') || (c == '}'))
						while (!opStack.empty() && !isEnd(opStack.top(), c))
						{
						
							mod = mod + t;
							t = opStack.top();
							opStack.pop();
						
						}
					if (!opStack.empty() && isEnd(opStack.top(), c))
					{
						opStack.pop();
						
					}
					else
						opStack.push(c);
				}
			}
			else
				opStack.push(c);
			
		}
		else
			opStack.push(c);

		return t;
	}

	void REG2RPN()
	{
		char t;
		for (string::iterator c = reg.begin(); c != reg.end(); c++)
		{
			if (*c == ' ')
				continue;
			if (isOp(*c))
			{
				if ((t = checkStack(*c)) != '\0')
					mod = mod + t;
			}
			else
				mod = mod + *c;
		}
		if (opStack.empty())
			return;
		else
		{
			cout << "Parse Error!" << endl;
			exit(1);
		}
	}
	void output()
	{
		cout << "Original Input Sequence:\t" << reg << endl;
		cout << "Result RPN Sequence:\t" << mod << endl;
	}
};



int main()
{
	int temp;
	RPN t("# a = (a + b) / [c + {d * e}] - (t - a) #");
	t.REG2RPN();
	t.output();
    return 0;
}


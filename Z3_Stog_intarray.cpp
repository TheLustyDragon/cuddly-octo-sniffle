#include <iostream>

template <class T>
class Stog
{
	static const int stackLimit = 100;

	T polje[stackLimit];

	int sp = 0;

public:
	bool push(T data)
	{
		if (sp >= stackLimit)
			return false;
		else
		{
			polje[sp] = data;
			sp++;
		}
		return true;
	}

	bool pop(T& retval)
	{
		if (sp < 0)
			return false;
		else
		{
			retval = polje[sp];
			sp--;
		}
		return true;
	}
};

int main()
{
	Stog<int>* stog = new Stog<int>;

	srand(time(NULL));

	for (int i = 0; i < 101; i++)
		stog->push((int)rand());

	int pval;
	while (stog->pop(pval))
		std::cout << pval << " ";
	std::cout << std::endl;

	delete stog;

	return 0;
}
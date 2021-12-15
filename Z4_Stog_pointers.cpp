#include <iostream>

template <class T>
class Stog
{
	template <class X>
	struct StogAtom
	{
		X data;
		StogAtom<X>* next;
	};

public:
	StogAtom<T>* sp = nullptr;

	bool push(T data)
	{
		StogAtom<T>* newAtom = new (std::nothrow) StogAtom<T>;
		if (!newAtom)
			return false;

		newAtom->data = data;
		newAtom->next = sp;

		sp = newAtom;
		return true;
	}

	bool pop(T& retval)
	{
		if (sp == nullptr)
			return false;
		else
		{
			retval = sp->data;
			sp = sp->next;
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

	return 0;
}
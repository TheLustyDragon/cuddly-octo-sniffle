#include <iostream>
#include <string.h>

template <class T>
class List
{
	template <class X>
	struct ListAtom
	{
		ListAtom<X>* prev;
		X data;
		ListAtom<X>* next;
	};

public:
	ListAtom<T>* head = nullptr;
	ListAtom<T>* tail = nullptr;

	bool upis(T newData)
	{
		ListAtom<T>* newEl = new (std::nothrow) ListAtom<T>;
		if (!newEl)
			return false;
		
		newEl->data = newData;
		newEl->prev = nullptr;

		if (!tail)
			head = newEl;
		else
		{
			newEl->next = tail;
			tail->prev = newEl;
		}

		tail = newEl;

		return true;
	}

	void ispis()
	{
		ListAtom<T>* tmp = head;

		while (tmp)
		{
			std::cout << tmp->data << " | ";
			tmp = tmp->prev;
		}			
	}
};

int main()
{
	List<int>* list = new List<int>;
	int var;
	for (int i = 0; i < 10; i++)
	{
		std::cout << "\nUpis: ";
		std::cin >> var;
		list->upis(var);
	}

	std::cout << std::endl;
	list->ispis();
	std::cout << std::endl;

	return 0;
}
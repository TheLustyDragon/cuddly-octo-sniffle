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
	// prev goes to tail, next goes to head
	ListAtom<T>* head = nullptr;
	ListAtom<T>* tail = nullptr;

	bool insertHead(T newData)
	{
		ListAtom<T>* newEl = new (std::nothrow) ListAtom<T>;
		if (!newEl)
			return false;
		newEl->data = newData;
		newEl->next = nullptr;
		newEl->prev = nullptr;

		if (tail == nullptr)
		{
			head = tail = newEl;
		}
		else
		{
			newEl->prev = head;
			head->next = newEl;
			head = newEl;
		}

		return true;
	}

	bool insertBefore(ListAtom<T>* atom, ListAtom<T>* newAtom)
	{
		atom->next = newAtom;
		newAtom->prev = atom;
		newAtom->next = atom->next;
		atom->next->prev = newAtom;
		return true;
	}

	void printFromHead()
	{
		ListAtom<T>* tmp = head;

		while (tmp)
		{
			std::cout << tmp->data << " | ";
			tmp = tmp->prev;
		}
	}

	void printFromTail()
	{
		ListAtom<T>* tmp = tail;

		while (tmp)
		{
			std::cout << tmp->data << " | ";
			tmp = tmp->next;
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
		list->insertHead(var);
	}

	std::cout << std::endl;
	list->printFromHead();
	std::cout << std::endl;
	list->printFromTail();
	std::cout << std::endl;

	return 0;
}
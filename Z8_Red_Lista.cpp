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

	bool popHead(T& retval)
	{
		retval = head->data;

		head->prev->next = nullptr;

		head = head->prev;

		return true;
	}

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
	bool insertTail(T newData)
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
			newEl->next = tail;
			tail->prev = newEl;
			tail = newEl;
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

template <class T>
class Red
{
	List<int>* red = new (std::nothrow) List<int>;

public:

	bool dodaj(int broj)
	{
		return red->insertTail(broj);
	}

	bool poljeURed(int polje[], int n)
	{
		std::cout << "\n - dodaje se: " << polje[n - 1];
		if (dodaj(polje[n - 1]))
			if (n - 1 <= 0)
				return true;
			else
				return poljeURed(polje, n - 1);
		else
			return false;
	}
	
	void ispis()
	{
		red->printFromHead();
	}		
};

int main()
{
	Red<int>* red = new (std::nothrow) Red<int>;

	srand(time(NULL));

	int polje[10];
	for (int i = 0; i < 10; i++)
	{
		polje[i] = rand() % 10 + 1;
	}

	red->poljeURed(polje, 10);

	red->ispis();

	return 0;
}
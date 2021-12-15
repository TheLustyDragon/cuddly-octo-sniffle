#include <iostream>

template <class T>
class List
{
	template <class X>
	struct ListAtom
	{
		X data;
		ListAtom<X>* next;
	};

public:
	ListAtom<T>* head = nullptr;

	bool upis(T newData)
	{
		ListAtom<T>* newElement = new (std::nothrow) ListAtom<T>;
		if (!newElement)
			return false;
		newElement->data = newData;
		newElement->next = nullptr;

		ListAtom<T>** tmp = &head;
		while (*tmp && (**tmp).data < newData)
		{
			tmp = &((*tmp)->next);
		}

		newElement->next = *tmp;
		*tmp = newElement;
		return true;
	}

	void ispis()
	{
		ListAtom<T>* tmp = head;

		while (tmp)
		{
			std::cout << tmp->data << " ";
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
		list->upis(var);
	}

	std::cout << std::endl;
	list->ispis();
	std::cout << std::endl;

	return 0;
}
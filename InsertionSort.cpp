#include <iostream>
#include <string.h>

struct Zapis
{
	int pbr;
	std::string naziv;
};

bool operator<(const Zapis& a, const Zapis& b)
{
	return a.pbr < b.pbr;
}

// smjer 0 ASC, smjer 1 DESC
void insertionSort(Zapis A[], int n, char smjer)
{
	if (smjer == '0')
		for (int i = 1; i < n; i++)
		{
			Zapis temp = A[i];
			int j;
			for (j = i; j >= 1 && temp < A[j - 1]; j--)
				A[j] = A[j - 1];
			A[j] = temp;
		}
	else if (smjer == '1')
		for (int i = 1; i < n; i++)
		{
			Zapis temp = A[i];
			int j;
			for (j = i; j >= 1 && !(temp < A[j - 1]); j--)
				A[j] = A[j - 1];
			A[j] = temp;
		}
}

int main()
{
	Zapis* polje = new Zapis[10];

	for (int i = 0; i < 10; i++)
		std::cin >> polje[i].pbr;

	std::cout << "\n[ Unsorted: ]" << std::endl;

	for (int i = 0; i < 10; i++)
		std::cout << polje[i].pbr << " | ";

	insertionSort(polje, 10, '0');

	std::cout << "\n[ Sorting ASC... ]" << std::endl;

	for (int i = 0; i < 10; i++)
		std::cout << polje[i].pbr << " | ";

	insertionSort(polje, 10, '1');

	std::cout << "\n[ Sorting DESC... ]" << std::endl;

	for (int i = 0; i < 10; i++)
		std::cout << polje[i].pbr << " | ";

	return 0;
}
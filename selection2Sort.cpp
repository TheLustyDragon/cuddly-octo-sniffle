#include <iostream>
#include <string>

#define LOGGER false

void swap(int& a, int& b);

// smjer '0' ASC, smjer '1' DESC
void selection2Sort(int A[], int n, char smjer)
{
	int min, max;
	if (smjer == '0') // sortiranje uzlazno
	{
		// iterate with sliding array borders, [ sorted sub-array left | min | unsorted sub-array | max | sorted sub-array right ]
		for (int i = 0; i < n / 2; i++)
		{
			min = i; // i | mjesto lokalnog minimuma A[i] (globalni minimum ce biti na mjestu A[0])
			max = (n - 1) - i; // (n - 1) - i | mjesto lokalnog maksimuma A[(n - 1) - i]
			if (A[min] > A[max]) // U slucaju gdje je pretpostavljeni A[max] lokalni minimum ne-sortiranog podniza, taj lokalni minimum se nece ispravno sortirati bez ove provjere
			{
				swap(A[min], A[max]);
				if (LOGGER) std::cout << "\n { LOG: PRE-swapped index " << min << "i and " << max << "i | elements: " << A[min] << " and " << A[max] << "; }";
			}
			/* example; i == 0
			* [ min | unsorted first | (...) | unsorted last | max ]
			* i == N, N e [1, n - 1 - 1]
			* [ sorted sub-array min-side | (...) | min | unsorted first | (...) | unsorted last | max | (...) | sorted sub-array max-side]
			*
			* N == 10, i < N/2 => i == 4 (last iteration)
			* [ 0 | 1 | 2 | 3 | local min | local max | 6 | 7 | 8 | 9 ] => (!): Potrebno je usporediti A[min] i A[max] prije ulazenja u ne-sortirani podniz!
			*/
			// (!): pocetni uvjet i zavrsni uvjet u ovoj for petlji ne smiju biti varijable min i max jer ih mijenjamo!
			for (int j = i + 1; j < (n - 1) - i; j++) // find min & max in unsorted sub-array
			{
				if (A[j] < A[min])
				{
					min = j;
					if (LOGGER) std::cout << "\n { LOG: min = " << min << "i; A[min] == " << A[min] << " }";
				}
				if (A[j] > A[max])
				{
					max = j;
					if (LOGGER) std::cout << "\n { LOG: max = " << max << "i; A[max] == " << A[max] << " }";
				}
			}
			if (min != i) // Provjera za pronadeni minimum. Ako je pretpostavljeni element na mjestu i ostao minimum, nije potrebno raditi premjestanje elementa u nizu sa samim sobom
			{
				swap(A[i], A[min]);
				if (LOGGER) std::cout << "\n { LOG: swapped index " << i << "i and " << min << "i | elements: " << A[i] << " and " << A[min] << "; }";
			}
			if (max != (n - 1) - i) // provjera promjene maksimuma(...)
			{
				swap(A[(n - 1) - i], A[max]);
				if (LOGGER) std::cout << "\n { LOG: swapped index " << ((n - 1) - i) << "i and " << max << "i | elements: " << A[(n - 1) - i] << " and " << A[max] << "; }";
			}
			if (LOGGER)
			{
				std::cout << "\n { LOG: i == " << i << " : [ ";
				for (int ti = 0; ti < n - 1; ti++)
				{
					std::cout << A[ti] << " | ";
				}
				std::cout << A[n - 1] << " ] ";
			}			
		}
	}
	else if (smjer == '1') // sortiranje silazno
	{
		for (int i = 0; i < n / 2; i++)
		{
			min = (n - 1) - i; // minimum na desnoj strani
			max = i; // maximum na lijevoj strani
			if (A[min] > A[max])
			{
				swap(A[min], A[max]);
				if (LOGGER) std::cout << "\n { LOG: PRE-swapped index " << min << "i and " << max << "i | elements: " << A[min] << " and " << A[max] << "; }";
			}
			for (int j = i + 1; j < (n - 1) - i; j++)
			{
				if (A[j] < A[min])
				{
					min = j;
					if (LOGGER) std::cout << "\n { LOG: min = " << min << "i; A[min] == " << A[min] << " }";
				}
				if (A[j] > A[max])
				{
					max = j;
					if (LOGGER) std::cout << "\n { LOG: max = " << max << "i; A[max] == " << A[max] << " }";
				}
			}
			if (min != i)
			{
				swap(A[i], A[min]);
				if (LOGGER) std::cout << "\n { LOG: swapped index " << i << "i and " << min << "i | elements: " << A[i] << " and " << A[min] << "; }";
			}
			if (max != (n - 1) - i)
			{
				swap(A[(n - 1) - i], A[max]);
				if (LOGGER) std::cout << "\n { LOG: swapped index " << ((n - 1) - i) << "i and " << max << "i | elements: " << A[(n - 1) - i] << " and " << A[max] << "; }";
			}
			if (LOGGER)
			{
				std::cout << "\n { LOG: i == " << i << " : [ ";
				for (int ti = 0; ti < n - 1; ti++)
				{
					std::cout << A[ti] << " | ";
				}
				std::cout << A[n - 1] << " ] ";
			}
		}
	}
}

int main(int argc, char* argv[])
{
	int n;
	int* polje;
	if (argc > 1) // cmd line args entered
	{
		n = argc;
		polje = new int[n];
		for (int i = 1; i < argc; i++)
		{
			polje[i - 1] = (int)argv[i]; // argv[0] je ime programa, argv[argc] je nullptr
		}
	}
	else // input manually 1 by 1, n == 1
	{
		std::cout << "\n Koliko clanova u nizu?: ";
		std::cin >> n;
		polje = new int[n];
		for (int i = 0; i < n; i++)
		{
			std::cout << "\n - upisi " << (i + 1) << ". clan niza: ";
			std::cin >> polje[i];
		}
	}

	// Ispis unesenog niza
	{
		std::cout << "\n[ Upis ne-sortirani niz ] : [ ";
		for (int i = 0; i < n - 1; i++)
		{
			std::cout << polje[i] << " | ";
		}
		std::cout << polje[n - 1] << " ] ";
	}

	// Sortiranje uzlazno i ispis
	{
		selection2Sort(polje, n, '0');
		std::cout << "\n[ Uzlazno sortirani niz ] : [ ";
		for (int i = 0; i < n - 1; i++)
		{
			std::cout << polje[i] << " | ";
		}
		std::cout << polje[n - 1] << " ] ";
	}

	// Sortiranje silazno i ispis
	{
		selection2Sort(polje, n, '1');
		std::cout << "\n[ Silazno sortirani niz ] : [ ";
		for (int i = 0; i < n - 1; i++)
		{
			std::cout << polje[i] << " | ";
		}
		std::cout << polje[n - 1] << " ] ";
	}

	std::cout << std::endl;

	return 0;
}

void swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
	return;
}
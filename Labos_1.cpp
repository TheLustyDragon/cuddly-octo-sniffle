// cd "/root/Labos_1/Labos_1/" && g++ -std=c++0x Labos_1.cpp -o Labos_1 && "/root/Labos_1/Labos_1/"Labos_1
#include <iostream>
#include <math.h>
#include <fstream>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string>
/* funkcije za obradu signala, navedene ispod main-a */
void obradi_sigusr1(int sig);
void obradi_sigterm(int sig);
void obradi_sigint(int sig);
std::string getLastLine(std::ifstream& in);
int nije_kraj = 1;
int broj;
int main()
{
	std::ofstream fwrite;
	std::ifstream fread;
	struct sigaction act;
	/* 1. maskiranje signala SIGUSR1 */
	act.sa_handler = obradi_sigusr1; /* kojom se funkcijom signal obrađuje */
	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask, SIGTERM); /* blokirati i SIGTERM za vrijeme obrade */
	act.sa_flags = 0; /* naprednije mogućnosti preskočene */
	sigaction(SIGUSR1, &act, NULL); /* maskiranje signala preko sučelja OS-a */
	/* 2. maskiranje signala SIGTERM */
	act.sa_handler = obradi_sigterm;
	sigemptyset(&act.sa_mask);
	sigaction(SIGTERM, &act, NULL);
	/* 3. maskiranje signala SIGINT */
	act.sa_handler = obradi_sigint;
	sigaction(SIGINT, &act, NULL);

	std::cout << "Program s PID=" << (long)getpid() << " krenuo s radom\n";
	/* neki posao koji program radi; ovdje samo simulacija */
	// Read status.txt
	fread.open("status.txt");
	std::string status;
	if (fread.is_open())
	{
		getline(fread, status);
		broj = std::stoi(status);
	}
	else
		std::cout << "Error 1 opening file: status.txt";
	fread.close();

	if (broj == 0)
	{
		// Read last obrada.txt
		fread.open("obrada.txt");
		std::string obrada;
		if (fread.is_open())
		{
			obrada = getLastLine(fread);
			broj = std::sqrt(std::stoi(obrada));
		}
		else
			std::cout << "Error 2 opening file: obrada.txt";
		fread.close();
	}

	// overwrite 0 to status.txt
	fwrite.open("status.txt", std::ios_base::trunc);
	if (fwrite.is_open())
	{
		fwrite << "0\n";
	}
	else
		std::cout << "Error 3 opening file: status.txt";
	fwrite.close();

	int i = 1;
	while (nije_kraj == 1) {
		// broj++ write to status, write sqr to obrada, sleep(5)
		broj++;

		fwrite.open("obrada.txt", std::ios_base::app);
		if (fwrite.is_open())
		{
			fwrite << (broj * broj) << std::endl;
		}
		else
			std::cout << "Error 4 opening file: obrada.txt";
		fwrite.close();

		std::cout << "Program: iteracija " << i++ << std::endl;
		int j = 5;
		while (j > 0)
		{
			sleep(1);
			j--;
		}
	}
	std::cout << "Program s PID=" << (long)getpid() << " zavrsio s radom\n";

	return 0;
}
void obradi_sigusr1(int sig)
{
	int i;
	std::cout << "Pocetak obrade signala " << sig << std::endl;
	std::cout << "Broj u obradi:" << broj << "." << std::endl;
	std::cout << "Kraj obrade signala " << sig << std::endl;
}
void obradi_sigterm(int sig)
{
	std::ofstream fwrite;
	std::cout << "Primio signal SIGTERM, pospremam prije izlaska iz programa\n";

	fwrite.open("status.txt", std::ios_base::trunc);
	if (fwrite.is_open())
	{
		fwrite << broj << std::endl;
	}
	else
	{
		std::cout << "Error sigterm opening file: status.txt";
	}
	fwrite.close();

	nije_kraj = 0;
}
void obradi_sigint(int sig)
{
	std::cout << "Primio signal SIGINT, prekidam rad\n";
	exit(1);
}
std::string getLastLine(std::ifstream& in)
{
    std::string line;
    while (in >> std::ws && std::getline(in, line)) // skip empty lines
        ;

    return line;
}
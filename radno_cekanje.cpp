/* 
 * Luka Starčević 0036528002, student Fakulteta elektrotehnike i računarstva
 * UNIX C Program za predmet Operacijski sustavi 2022.
 * Drugi labos | Zadatak: Sinkronizacija ulazne, radne i izlazne dretve radnim čekanjem
 * http://www.zemris.fer.hr/predmeti/os/
 * Za prevođenje: cd "/root/Labos_2/" && g++ -pthread radno_cekanje.cpp -o radno_cekanje && "/root/Labos_2/"radno_cekanje 5
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <math.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <values.h>
#include <pthread.h>
#include <atomic>

std::atomic<int> shmVarUR; // shared variable between Ulazna and Radna dretva within same process

int shmId; // shared memory segment ID shmVar
int* shmVar; // shared memory variable Radna-Izlazna

// Free up shared memory
void freeShm(int sig)
{
    (void) shmdt(shmVar);
    (void) shmctl(shmId, IPC_RMID, NULL);
    exit(0);
}

// @param shmVarUR Shared memory variable with ulaznaDretva
// @param shmVar Shared memory variable with izlaznaDretva
void radnaDretva()
{
    printf("Pokrenuta RADNA DRETVA\n");
    while (shmVarUR != -1)
    {
        while (shmVarUR == 0)
            sleep(1);        // radno čekanje
        int read = shmVarUR; // shmVarUR == 0 => read from shared memory variable
        shmVarUR = 0;        // shared memory ready to receive next number
        if (read != -1)
        {
            printf("RADNA DRETVA: pročitan broj %d i povećan na %d\n", read, read+1);
            read++;
            while (*shmVar != 0)
                sleep(1); // radno čekanje
            *shmVar = read;
        }
        else
        {
            while (*shmVar != 0)
                sleep(1); // radno čekanje
            *shmVar = -1;
            break;
        }
    }
    
    printf("Završila RADNA DRETVA\n");
}

// @param shmVar Shared memory variable with radnaDretva
void izlaznaDretva()
{
    printf("Pokrenut IZLAZNI PROCES\n");
    std::ofstream fstream("/root/Labos_2/izlaz.txt");
    
    while (*shmVar != -1)
    {
        while (*shmVar == 0) sleep(1);
        int izlaz = *shmVar;
        *shmVar = 0; // shared memory variable ready to process next number
        if (izlaz == -1)
            break;
        
        fstream << izlaz << "\n";
        printf("IZLAZNI PROCES: broj upisan u datoteku %d\n \n", izlaz);
    }    
    fstream.close();

    printf("Završio IZLAZNI PROCES\n");
}

// @param arg Number of random numbers to generate
// @param shmVarUR Shared memory variable with radnaDretva
void* ulaznaDretva(void* arg)
{
    printf("Pokrenuta ULAZNA DRETVA\n");
    int N = *(int *) arg;
    for (int i = 0; i < N; i++)
    {
        sleep(rand() % 5 + 1); // sleep 1 to 5 seconds
        int generate = rand() % 100 + 1; // generate random number between 1 and 100
        printf("ULAZNA DRETVA: broj %d\n", generate);
        while (shmVarUR != 0) sleep(1); // radno čekanje
        shmVarUR = generate; // shmVarUR != 0 => write generated number to shared memory variable
    }
    while (shmVarUR != 0) sleep(1); // radno čekanje
    shmVarUR = -1; // signal -1 kraj rada
    printf("Završila ULAZNA DRETVA\n");
    return (void*)shmVar; // nista
}

/* Stvori 3 dretve u 2 procesa.
 * 1. proces: ulazna i radna dretva
 * 2. proces: izlazna dretva
 * Ulazna dretva: rand(1-5 sek) generate rand(1 - 100 int) and write to var. shr. w/ radna dretva
 * Radna dretva: read shr.var., increment 1, write to var. shr. w/ izlazna dretva
 * Izlazna dretva: read shr.var. and write to file.
 * 
 * Radna dretva radno čeka 0 u shr.var. ulaz+rad,
 * Ulazna dretva radno čeka != 0 shr.var. ulaz+rad,
 * RadnaIzlazna ista sinkronizacija preko shr.var.
 */
/* @param N Broj nasumičnih brojeva koje generira ulazna dretva
 */
int main(int argc, char* argv[])
{
    int N = atoi(argv[1]);

    // Reserve shared memory UR
    shmId = shmget(IPC_PRIVATE, sizeof(int), 0600);
    if (shmId == -1)
    {
        printf("Error: No shared memory.");
        exit(1);
    }
    shmVar = (int*) shmat(shmId, NULL, 0);
    *shmVar = 0;

    // Start parallel processing
    int childNum = 0;

    switch (fork())
    {
    case 0: // child process
        // main thread is izlaznaDretva
        izlaznaDretva();
        exit(0);
    case -1: // Error
        printf("Error: Cannot create child process.\n");
    default: // parent process
        pthread_t thrIdU; // thread ID ulaznaDretva
        if (pthread_create(&thrIdU, NULL, ulaznaDretva, &N) != 0)
        {
            printf("Error: Failed to create thread %d.\n", (int)thrIdU);
            exit(1);
        }
        radnaDretva();
        pthread_join(thrIdU, NULL);
        break;
    }

    // Parent waits and collects all created children
    while (childNum >= 0)
    {
        (void) wait(NULL);
        childNum--;
    }

    freeShm(0);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "mymutex.h"

#define NO_MUTEX 0
#define POSIX_MUTEX 1
#define MY_MUTEX 2

#define USE_MUTEX NO_MUTEX
//#define USE_MUTEX POSIX_MUTEX
//#define USE_MUTEX MY_MUTEX

void *functionC();

// Further is
// Trash,
#if USE_MUTEX == NO_MUTEX
int foo(void* bar) { return -1; }
#define LOCK_MUTEX foo
#define UNLOCK_MUTEX foo
void* mutex1;
#endif

// waste
#if USE_MUTEX == POSIX_MUTEX
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
#define LOCK_MUTEX pthread_mutex_lock
#define UNLOCK_MUTEX pthread_mutex_unlock
#endif

// and sodomy!
#if USE_MUTEX == MY_MUTEX
struct MyMutex mutex1;
#define LOCK_MUTEX lockMyMutex
#define UNLOCK_MUTEX unlockMyMutex
#endif

// Globals! Achtung! Keep your children away!
int counter = 0;
int result = 0;
const int ITERATIONS_NUMBER = 1E6;

main()
{
    int rc1, rc2;
    int i;
    pthread_t thread1, thread2;
    unsigned int threadsNumber;
    printf("Enter the number of threads (please, don't be cruel, "
            "enter the number between 1 and 1000) ");
    scanf("%u", &threadsNumber);
    if (threadsNumber < 1 || threadsNumber > 1000) {
        printf("You shouldn't have done it!\n");
        return(EXIT_FAILURE);
    }
    // A little bit of pain
    pthread_t* threads = (pthread_t*)malloc(sizeof(pthread_t)*threadsNumber);
    i = -1;
    while (++i < threadsNumber) {
        if (pthread_create( &threads[i], NULL, &functionC, NULL)) {
            printf("Thread %d creation failed :(", i);
        }
    }

    i = -1;
    while (++i < threadsNumber) {
        pthread_join( threads[i], NULL);
    }
    printf("Mean: %u (should be %u with muteces, error is %2.2f%%), "
            "%u threads processed\n",
            result/threadsNumber, ITERATIONS_NUMBER,
            (100 - (float)100*ITERATIONS_NUMBER/(result/threadsNumber)),
            threadsNumber);

    // This is Sparta!
    exit(EXIT_SUCCESS);
}

// Funny Mutex :)
// int my_mute = 0;

void *functionC()
{
    /*
    // Funny Mutex locking
    while (my_mute == 1);
    my_mute = 1;
    */
    LOCK_MUTEX(&mutex1);

    int i = 0;
    while (i < ITERATIONS_NUMBER) {
        counter++;
        i++;
    }
    printf("Counter value: %d\n",counter);
    result += counter;
    // Funny Mutex unlocking
    //my_mute = 0;
    UNLOCK_MUTEX(&mutex1);
}

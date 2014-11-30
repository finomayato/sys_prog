#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *functionC();

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutexattr_t   mta;

// Globals! Achtung! Keep your children away!
int counter = 0;
int result = 0;
const int ITERATIONS_NUMBER = 1E6;

void showPshared(pthread_mutexattr_t *mta) {
    int           rc;
    int           pshared;
 
    printf("Check pshared attribute\n");
    rc = pthread_mutexattr_getpshared(mta, &pshared);
    //checkResults("pthread_mutexattr_getpshared()\n", rc);
 
    printf("The pshared attributed is: ");
    switch (pshared) {
        case PTHREAD_PROCESS_PRIVATE:
            printf("PTHREAD_PROCESS_PRIVATE\n");
            break;
        case PTHREAD_PROCESS_SHARED:
            printf("PTHREAD_PROCESS_SHARED\n");
            break;
          default : 
            printf("! pshared Error !\n");
            exit(1);
    }
    return;
}

main()
{
    //printf("%ld\n", _POSIX_THREAD_PROCESS_SHARED);
    pthread_mutex_init(&mutex1, &mta);
    int ps = pthread_mutexattr_setpshared(&mta, PTHREAD_PROCESS_SHARED);
    printf("%d\n", ps);
    int rc1, rc2;
    int i;
    pthread_t thread1, thread2;
    unsigned int threadsNumber;
    printf("Enter the number of threads (please, don't be cruel to yourself, "
            "enter the number between 1 and 10) ");
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

    showPshared(&mta);
    // This is Sparta!
    exit(EXIT_SUCCESS);
}


void *functionC()
{
    int v;
    pthread_mutex_lock(&mutex1);
    printf("Enter some integer value ");
    scanf("%d", &v);

    pthread_mutex_unlock(&mutex1);
}

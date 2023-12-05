#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define NUM_THREAD 99

typedef struct {
    int index;
    pthread_t fatherId;
} Thread;

void *generateSon(void *arg){
    int res; /* controllo risultato create e join */
    pthread_t threadId; /* Salvo id del nuovo processo */
    Thread *pFather /* Puntatore di appoggio per il padre arg*/;

    /* arg passato è un type Thread -> *((Thread*)arg) */
    Thread *newThread = malloc(sizeof(Thread));
    if (newThread == NULL){
        printf("Errore nell'allocazione della memoria\n");
    }

    /* Alloco puntatore di appoggio e assegno */
    pFather = (void*)malloc(sizeof(Thread));
    if(pFather == NULL){
        printf("Errore nell'allocazione della memoria\n");
    }

    /* Assegno puntatori di appoggio al thread figlio e al thread padre */
   
    *pFather = *((Thread*)arg);
    
    newThread->index = pFather->index + 1;
    newThread->fatherId = pthread_self();
    usleep(1000);
    if (pFather->index < NUM_THREAD){
        /* Inizializzo nuovo thread */
        res = pthread_create(&threadId, NULL, generateSon, newThread);
        if (res){ 
            printf("pthread_create() failed: error %i\n", res); exit(1);
        }
    }
    res = pthread_join( pFather->fatherId , NULL );
    if (res){ 
        printf("pthread_create() failed: error %i\n", res); exit(1);
    }
    printf("Thread %d eliminato\n",pFather->index);
    printf("Thread %d creato\n",newThread->index);
    free(pFather);
    pthread_exit (NULL);
}

int main (void){
    pthread_t threadId; /* Salvo id del nuovo processo */
    Thread *p; /* puntatore di appoggio per passare l'argomento */

    /* Alloco in memoria nuovo thread */
    Thread *newThread = malloc(sizeof(Thread));
    if (newThread == NULL){
        printf("Errore nell'allocazione della memoria\n");
    }

    /* Assegno valori alla struttura */
    newThread->index = 0;
    newThread->fatherId = pthread_self();

    p = newThread;
    
    usleep(1000);
    pthread_create(&threadId, NULL, generateSon, p);
    
    pthread_exit(NULL);
    
}

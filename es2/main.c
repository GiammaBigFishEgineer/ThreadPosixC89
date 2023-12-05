#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define NUM_THREAD 4

typedef struct {
    int N; /* thread rimanenti da creare */
    char str[101];
    int Indice; /* un valore compreso tra 0 ed N-1 diverso per ciascun thread creato */
} Struttura;

void *threadAction(void *arg){
    pthread_t threadId[NUM_THREAD]; /* array id threads */
    Struttura* pArg; /* puntatore struttura arg */
    Struttura* pNew; /* puntatore struttura nuovo */
    int i; /* indice ciclo */
    int M; /* arg->N */
    int rc; /* controllo */

    sleep(1);
    pArg = (Struttura*) arg;
    M = pArg->N;
    if (M > 1) {
        for (i = 0; i < M - 1; i++) {
            pNew = malloc(sizeof(Struttura));
            if(pNew == NULL){
                printf("Errore nell'allocazione della memoria\n");
            }
            pNew->N = M - 1;
            pNew->Indice = i;
            rc = pthread_create(&threadId[i],NULL,threadAction,pNew);
            if(rc){
                printf("Errore nella creazione di un nuovo thread\n");
                exit(1);
            }
        }
        for(i = 0; i < M - 1; i++){
            rc = pthread_join(threadId[i],(void**)&pNew);
            if(rc){
                printf("Errore nella join di un thread\n");
                exit(1);
            }
            printf("received %s\n",pNew->str);
            free(pNew);
        }

    }
    sprintf( pArg->str, "%i %i", pArg->N, pArg->Indice);
    pthread_exit(pArg);
}

int main (void){
    pthread_t threadId[NUM_THREAD]; /* array id threads */
    int i; /* indice ciclo */
    int rc; /* controllo */
    void *p; /* puntatore di appoggio alla struttura */
    Struttura *struttura; /* nuova struttura */

    for(i = 0; i < NUM_THREAD; i++){
        struttura = malloc(sizeof(Struttura));
        if(struttura == NULL){
            printf("Errore nell'allocazione della memoria\n");
        }
        struttura->N = NUM_THREAD - 1;
        struttura->Indice = i;
        p = struttura;
        rc = pthread_create(&threadId[i],NULL, threadAction, p);
        if(rc){
            printf("Errore nella creazione di un nuovo thread\n");
            exit(1);
        }
    }
    for(i = 0; i < NUM_THREAD; i++){
        rc = pthread_join(threadId[i],(void**)&struttura);
        if(rc){
            printf("Errore nella join di un thread\n");
            exit(1);
        }
        printf("main received %s\n",struttura->str);
        free(struttura);
    }
   
    pthread_exit(NULL);
}

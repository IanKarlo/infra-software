#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include <pthread.h>
#include <string.h>

//Paramentros
int quant_threads, ocupadas = 0;
pthread_t despacharThread;
pthread_t *threads;

pthread_mutex_t despachar_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t pronto_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t *threads_mutex;

pthread_cond_t acabou = PTHREAD_COND_INITIALIZER;
pthread_cond_t preencheu = PTHREAD_COND_INITIALIZER;
short int loop = 1;

//Gerenciamento de queues


Queue *bufferQueue ;
Queue *prontos;

int main(){
    printf("Quantos nucleos? ");
    scanf(" %d", &quant_threads);
    threads = (pthread_t *) malloc(sizeof(pthread_t)*quant_threads);
    threads_mutex = (pthread_mutex_t*) malloc(sizeof(pthread_mutex_t)*quant_threads);
    for(int i=0;i<quant_threads;i++) pthread_mutex_init(&threads_mutex[i],NULL);

    //Queues
    bufferQueue = newQueue(-1);
    prontos = newQueue(-1);

    //Colocar em funcoes
    pthread_create(&despacharThread,NULL,despachar,NULL);
    
    //liberar memoria alocada
    for(int i=0;i<quant_threads;i++) {
        pthread_join(threads[i],NULL);
        pthread_mutex_destroy(&threads_mutex[i]);
    }
    pthread_join(despacharThread,NULL);

    free(threads);
    free(threads_mutex);
    freeQueue(bufferQueue);
    freeQueue(prontos);
}

void *despachar(void *arg){
    ocupadas = 0;
    int array[quant_threads];
    for(int i=0;i<quant_threads;i++) array[i]=0;
    while(loop){
        while (bufferQueue->size==0) pthread_cond_wait(&preencheu,&despachar_mutex);
        Elem* e = takeQueue_first(bufferQueue);
        do{ //COmo sinalizar isso????
            for(int i=0;i<quant_threads;i++) if(!array[i]){break;} else{ocupadas++;}
            if (ocupadas == quant_threads) pthread_cond_wait(&acabou,&despachar_mutex);
        }while (ocupadas == quant_threads);
        pthread_create(&threads[ocupadas],NULL,executar,e);
        pthread_cond_signal(&acabou);
    }
    pthread_exit(NULL);
}

void agendar(Elem *e){
    pthread_mutex_lock(&pronto_mutex);
    putQueue_node(prontos,e);
    pthread_mutex_unlock(&pronto_mutex);
    pthread_cond_signal(&preencheu);
}

int pegar(int id){
    pthread_mutex_lock(&pronto_mutex);
    while (!isthere(prontos,id)){pthread_cond_wait(&acabou,&pronto_mutex);}
    int e = takeQueue_key(prontos,id);
    pthread_mutex_unlock(&pronto_mutex);
    return e;
}

void *executar(void *e) {
    Elem *node = (Elem*)e;
    pthread_mutex_lock(&pronto_mutex);
    putQueue_node(prontos,e);
    pthread_mutex_unlock(&pronto_mutex);
    pthread_cond_signal(&acabou);
    pthread_exit(NULL);
}
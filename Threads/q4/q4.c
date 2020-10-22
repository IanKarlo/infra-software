#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "funcoes.h"
#include <pthread.h>
#include <string.h>
#include <time.h>
#include "ansi-functions.h"

#define QUANT_FUNCOES 6

//Paramentros
int quant_threads, ocupadas = 0;
pthread_t despacharThread;
pthread_t *threads;
short int *vetor;

//Funcoes lista
char lista[][QUANT_FUNCOES] = {"add","sub","mul","div","elv","sum"};
int (*lista_funcoes[QUANT_FUNCOES])(int,int) = {add,sub,mul,dvs,elv,sum}; 

pthread_mutex_t despachar_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t pronto_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t *threads_mutex;

pthread_cond_t acabou = PTHREAD_COND_INITIALIZER;
pthread_cond_t preencheu = PTHREAD_COND_INITIALIZER;
short int loop = 1;

//Gerenciamento de queues
Queue *bufferQueue ;
Queue *prontos;

//funcoes
void *executar(void *e);
void *despachar(void *arg);
void agendar(Elem *e);
int pegar(int id);
void *executar(void *e);

int main(){
    clear();
    srand(time(NULL));
    printf("Quantos nucleos? ");
    scanf(" %d", &quant_threads);
    clear();

    threads = (pthread_t *) malloc(sizeof(pthread_t)*quant_threads);
    vetor = (short int*) malloc(sizeof(short int) * quant_threads);
    threads_mutex = (pthread_mutex_t*) malloc(sizeof(pthread_mutex_t)*quant_threads);
    for(int i=0;i<quant_threads;i++) {
      pthread_mutex_init(&threads_mutex[i],NULL);
      vetor[i]=0;
    }

    //Queues
    bufferQueue = newQueue(-1);
    prontos = newQueue(-1);

    //Colocar em funcoes
    pthread_create(&despacharThread,NULL,despachar,NULL);

    //funcao principal
    char funcao[50],resto[30];
    int x,y,id;
    Elem* e;
    char quit[] = "quit",pegar_str[]="pegar",clear_str[]="clear";

    while(loop){
      fflush(stdout);
      printf(">>> "); fflush(stdout);
      scanf(" %[^(]",funcao);
      //organizar casos
      if (!strcmp(funcao, quit)) loop=0;
      else if(!strcmp(funcao,pegar_str)) {
        scanf("(%d)",&id); 
        if (isthere(bufferQueue, id)||isthere(prontos,id)){
          int resposta = pegar(id);
          printf("Resultado = %d\n",resposta);
        }
        else printf("Nao existe resposta com esse id\n");
      }
      else if(!strcmp(funcao,clear_str)){clear(); scanf(" %[^\n]",resto);}
      else{ 
        scanf("(%d,%d)",&x,&y);
        e = (Elem*) malloc(sizeof(Elem));
        e->x=x; e->y=y; 
        do{e->id=rand()%100;}while(isthere(bufferQueue,e->id)||isthere(prontos, e->id));
        int i;
        for(i=0;i<QUANT_FUNCOES;i++){
          if (!strcmp(lista[i],funcao)) 
          {e->funcao = lista_funcoes[i]; break;}
        }
        if (i==QUANT_FUNCOES) {printf("Operacao invalida\n"); free(e); e=NULL;}
        if(e!=NULL){
          agendar(e);
          printf("O id dessa resposta e: %d\n",e->id);
        }
      }
    }
    
    //liberar memoria alocada
    for(int i=0;i<quant_threads;i++) {
        pthread_join(threads[i],NULL);
        pthread_mutex_destroy(&threads_mutex[i]);
    }
    pthread_cancel(despacharThread);
    clear();

    free(threads);
    free(vetor);
    free(threads_mutex);
    freeQueue(bufferQueue);
    freeQueue(prontos);
}

void *despachar(void *arg){
    while(1){
        while (bufferQueue->size == 0) pthread_cond_wait(&preencheu, &despachar_mutex);
        Elem* e = takeQueue_first(bufferQueue);
        do{
            for(ocupadas=0;ocupadas<quant_threads;ocupadas++) if (!vetor[ocupadas]) break;
            if (ocupadas == quant_threads) pthread_cond_wait(&acabou,&despachar_mutex);
        }while (ocupadas == quant_threads);
        pthread_join(threads[ocupadas],NULL);
        e->vetor = ocupadas;
        vetor[ocupadas] = 1;
        pthread_create(&threads[ocupadas],NULL,executar,e);
    }
    pthread_exit(NULL);
}

void agendar(Elem *e){
    pthread_mutex_lock(&pronto_mutex);
    putQueue_node(bufferQueue,e);
    pthread_mutex_unlock(&pronto_mutex);
    pthread_cond_signal(&preencheu);
}

int pegar(int id){
    pthread_mutex_lock(&pronto_mutex);
    while (!isthere(prontos,id)) {pthread_cond_wait(&acabou,&pronto_mutex);}
    int e = takeQueue_key(prontos,id);
    pthread_mutex_unlock(&pronto_mutex);
    return e;
}

void *executar(void *e) {
    Elem *node = (Elem*) e;
    pthread_mutex_lock(&pronto_mutex);
    node->resultado = node->funcao(node->x,node->y);
    putQueue_node(prontos,node);
    pthread_mutex_unlock(&pronto_mutex);
    vetor[node->vetor] = 0;
    pthread_cond_signal(&acabou);
    pthread_exit(NULL);
}

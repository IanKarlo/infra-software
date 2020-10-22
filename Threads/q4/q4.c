#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "funcoes.h"
#include <unistd.h>

//funcoes
int (*lista_funcoes[FUNC_QUANT]) (int,int) = {add,sub,mul,dvs,elv,sum};
char nome_funcoes [][5]= {"add","sub","mul","div","pow","sum"};

#define MAXSIZE 1000

typedef struct elemento{
  int x,y;
  int (*func) (int,int);
  bool pronto;
  int id;
  int thread;
}elem;

typedef struct threads{
  pthread_t thread;
  bool livre;
}threads_s;

typedef struct parametros{
  int first,second;
}param;

typedef struct respostas{
  int resultado;
  bool pronto;
  bool reservado;
}respostas;

//Parametros
int buffer_index = 0, criar_index = 0,quant_threads;
int maior_resposta=1;
pthread_mutex_t despachar_mutex = PTHREAD_MUTEX_INITIALIZER, pegar_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t acabou = PTHREAD_COND_INITIALIZER, preencheu = PTHREAD_COND_INITIALIZER;
pthread_t despachar_t;
threads_s *threads;
elem buffer[MAXSIZE];
respostas res[MAXSIZE];

//funcoes
void agendarFuncao(int (*func)(int,int), param str){
  buffer[criar_index].x = str.first;
  buffer[criar_index].y = str.second;
  buffer[criar_index].func = func;

  int id = criar_index;
  buffer[criar_index].id = id;
  res[id].pronto = false;
  res[id].reservado = true;
  criar_index++; if(criar_index == MAXSIZE) criar_index = 0;
  
  printf("O id desse resultado e (%d)\n",id);
  pthread_cond_broadcast(&preencheu);
}

void pegarResultado(int id){
  if (!res[id].reservado) {printf("Nao existe resultado para esse id\n"); return;}
  while (!res[id].pronto) {pthread_cond_wait(&acabou, &pegar_mutex);} //Colocar um mutex
  printf("O resultado e (%d)\n", res[id].resultado);
}

void *funcexec(void *arg){
  sleep(5);
  elem* e = (elem*) arg;
  res[e->id].resultado = e->func(e->x,e->y);
  res[e->id].pronto = true;
  threads[e->thread].livre = true; 
  //Sinalizar condicao
  pthread_cond_broadcast(&acabou);
  pthread_exit(NULL); 
}

void *despachante (void *arg){
  int i;
  while (true){
    while (criar_index == buffer_index) {pthread_cond_wait(&preencheu, &despachar_mutex);} //colocar mutex
    do{
      for (i = 0; i<quant_threads; i++) if (threads[i].livre) break;
      if (i==quant_threads) {pthread_cond_wait(&acabou, &despachar_mutex);} //colocar mutex
    }while(i==quant_threads);
    pthread_join(threads[i].thread, NULL);
    threads[i].livre = false;
    buffer[buffer_index].thread = i;
    pthread_create(&threads[i].thread, NULL, funcexec, &buffer[buffer_index]);
    buffer_index++; if (buffer_index==MAXSIZE) buffer_index = 0;
  }
}

int main(){
  printf("Quantos nucleos? ");
  scanf(" %d", &quant_threads);
  //Reservar memoria
  threads = (threads_s *) malloc(sizeof(threads_s) * quant_threads);
  for (int i=0;i<quant_threads;i++) threads[i].livre=true;
  for (int i=0;i<MAXSIZE;i++) res[i].reservado=false;
  
  //loop
  char funcao[30], quit[]="quit", pegar[] = "pegar", reset[] = "reset";
  int i;
  param str;
  pthread_create(&despachar_t, NULL, despachante, NULL);

  while(1){
    printf(">>> ");
    scanf(" %s", funcao);
    if (!strcmp(funcao,quit)) break;
    else if (!strcmp(funcao,pegar)) {scanf(" %d", &i); pegarResultado(i);}
    else if (!strcmp(funcao,reset)) {
      for (int i=0;i<quant_threads;i++) pthread_cancel(threads[i].thread);
      pthread_cancel(despachar_t);
      for (int i=0;i<MAXSIZE;i++) res[i].reservado=false;
      buffer_index = criar_index = 0;
      pthread_create(&despachar_t, NULL, despachante, NULL);
      printf("Todos os resultados foram resetados\n");
    }
    //Formar funcoes
    else{
      scanf(" %d %d",&str.first,&str.second);
      for (i=0;i<FUNC_QUANT;i++) 
        if (!strcmp(funcao,nome_funcoes[i])) break;
      if (i!=FUNC_QUANT) agendarFuncao(lista_funcoes[i],str);
      else printf("Funcao invalida\n");
    }
  }
  pthread_cancel(despachar_t);

  //liberar tudo
  free(threads);
}
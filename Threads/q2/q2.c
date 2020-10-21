#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include "ansi-functions.h"

//Todos começam na posicao 1 para facilitar o entendimento
pthread_t *threads;
pthread_mutex_t *mutexes;
pthread_t *temporizadores;
int total_linhas, total_arquivos, total_threads;
FILE** files;
int* nums;

void *funcao(void* args);
void *temporizador(void* mutex);

int main(void)
{
    //Pegar valores
    printf("Quantos arquivos?: ");
    scanf(" %d", &total_arquivos);
    printf("Quantas threads?: ");
    scanf(" %d", &total_threads);
    printf("Quantos linhas?: ");
    scanf(" %d", &total_linhas);
    if(total_threads>total_arquivos) total_threads=total_arquivos;

    //Pegar arquivos;
    files = (FILE**) malloc((total_arquivos+1)*sizeof(FILE*));
    for(int i=1;i<=total_arquivos;i++){
        char nomes_arquivo[30];
        sprintf(nomes_arquivo,"example/file%02d.txt",i);
        files[i]=fopen(nomes_arquivo,"r");
    }

    //apagar tudo
    start();
    first_print(total_linhas);

    //Criação dos arrays;
    mutexes = (pthread_mutex_t*) malloc(sizeof(pthread_mutex_t) * (total_linhas+1));
    threads = (pthread_t*) calloc(total_threads+1,sizeof(pthread_t));
    temporizadores = (pthread_t*) calloc(total_linhas+1,sizeof(pthread_t));
    for(int i=0;i<=total_linhas;i++){pthread_mutex_init(&mutexes[i],NULL);}

    //Criaçao de threads
    nums = (int*) calloc(total_threads+1, sizeof(int));
    for(int i=1;i<=total_threads;i++){nums[i] = i; pthread_create(&threads[i],NULL,funcao,&nums[i]);}

    //Unir as threads de threads
    for(int i=0;i<=total_threads;i++) pthread_join(threads[i],NULL);
    for(int i=0;i<=total_linhas;i++){pthread_join(temporizadores[i],NULL);}

    //Libera todas as memorias alocadas
    for(int i=0;i<=7;i++){pthread_mutex_destroy(&mutexes[i]);}
    for(int i=1;i<=total_arquivos;i++){fclose(files[i]);}
    free(files);
    free(threads);
    free(temporizadores);
    free(nums);
    pthread_exit(NULL);
}

void *funcao(void* arg){
    int arq = *((int*) arg);
    int linha;

    imprimir str;
    for(int i=arq;i<=total_arquivos;i+=total_threads){
            while(fscanf(files[i]," %d", &linha)!=EOF){
                fscanf(files[i]," %s %s %s", str.codigo,str.cidade,str.horario);
                pthread_mutex_lock(&mutexes[linha]);
                str.linha=linha;
                func_main(total_linhas,str);
                pthread_create(&temporizadores[linha],NULL,temporizador,&mutexes[linha]);

        }
    }
    pthread_exit(NULL);
}

void *temporizador(void* mutex){
    sleep(2);
    pthread_mutex_unlock((pthread_mutex_t*) mutex);
    pthread_exit(NULL);
}

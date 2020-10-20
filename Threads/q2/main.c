#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include "ansi-functions.h"

pthread_t *threads;
pthread_mutex_t *mutexes;
int total_linhas, total_arquivos, total_threads;
FILE** files;
int* nums;

void *funcao(void* args);

int main(void)
{
    start();

    //Pegar valores
    printf("Quantos arquivos?: ");
    scanf(" %d", &total_arquivos);
    printf("Quantas threads?: ");
    scanf(" %d", &total_threads);
    printf("Quantos linhas?: ");
    scanf(" %d", &total_linhas);

    //Apagar tudo
    ret_pos();
    erase_display();

    //Pegar arquivos;
    char arquivo_nome[30];
    files = (FILE**) malloc((total_arquivos+1)*sizeof(FILE*));
    for(int i=1;i<=total_arquivos;i++){
        printf("Nome do arquivo (%d): ",i);
        scanf(" %s",arquivo_nome);
        files[i]=fopen(arquivo_nome,"r");
    }

    //apagar tudo
    ret_pos();
    erase_display();
    first_print(total_linhas);

    //Criação dos arrays;
    mutexes = (pthread_mutex_t*) malloc(sizeof(pthread_mutex_t) * (total_linhas+1));
    threads = (pthread_t*) calloc(total_threads+1,sizeof(pthread_t));
    for(int i=0;i<=total_linhas;i++){pthread_mutex_init(&mutexes[i],NULL);}

    //Criaçao de threads
    nums = (int*) calloc(total_threads+1, sizeof(int));
    for(int i=1;i<=total_threads;i++){nums[i] = i; pthread_create(&threads[i],NULL,funcao,&nums[i]);}

    //Unir as threads de threads
    for(int i=0;i<=total_threads;i++) pthread_join(threads[i],NULL);

    //Libera todas as memorias alocadas
    for(int i=0;i<=7;i++){pthread_mutex_destroy(&mutexes[i]);}
    for(int i=1;i<=total_arquivos;i++){fclose(files[i]);}
    free(files);
    free(threads);
    free(nums);
    pthread_exit(NULL);
}

void *funcao(void* arg){
    int linha = *((int*) arg);
    imprimir str;
    for(int i=linha;i<=total_arquivos;i+=total_threads){
            while(fscanf(files[i]," %d", &linha)!=EOF){
                fscanf(files[i]," %s %s %s", str.codigo,str.cidade,str.horario);
                pthread_mutex_lock(&mutexes[linha]);
                str.linha=linha;
                func_main(total_linhas,str);
                sleep(2); //Tentar depois implementar um mutex para a linha e não para a thread
                pthread_mutex_unlock(&mutexes[linha]);

        }
    }
    
    pthread_exit(NULL);
}
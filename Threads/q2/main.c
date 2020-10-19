#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include "ansi-functions.h"

pthread_t *threads;
pthread_mutex_t *mutexes;
imprimir* str;
int total;

void *funcao(void* args);

int main(void)
{
    start(); //Funcao para colocar a quantidade de linha
    int quant_arquivos;
    printf("Quantos arquivos, serao? ");
    scanf(" %d", &quant_arquivos);
    
    FILE **file = (FILE**) malloc(sizeof(file)*quant_arquivos);
    for(int i=0;i<quant_arquivos;i++){
        printf("Digite o nome do arquivo (%d): ", i);
        char frase[30];
        scanf(" %s",frase);
        file[i] = fopen(frase,"r");
    }

    int linha;
    printf("Quantas linhas no total?: ");
    scanf(" %d", &total);
    threads = (pthread_t *) malloc( sizeof(pthread_t)*total);
    mutexes = (pthread_mutex_t *) malloc( sizeof(pthread_mutex_t) * total);
    for(int i=0;i<total;i++) pthread_mutex_init(&mutexes[i],NULL);
    str = (imprimir*) malloc(sizeof(imprimir) * total);


    //Une tudo em um arquivo só
    char tudo[40];
    FILE* novo = fopen("tudo.txt","w");
    for(int i=0;i<quant_arquivos;i++){
        while(fscanf(file[i]," %[^\n]\n", tudo) != EOF){
            fprintf(novo,"%s\n",tudo);
        }
    }
    fclose(novo);

    //Apagar tudo antes de começar
    ret_pos();
    erase_display();

    //Começa agora os casos
    novo = fopen("tudo.txt","r");
    while(fscanf(novo," %d", &linha) != EOF){
        fscanf(novo," %s %s %s", str[linha-1].codigo, str[linha-1].cidade, str[linha-1].horario);
        str[linha-1].linha = linha;
        pthread_create(&threads[linha-1],NULL,funcao,&linha);
        pthread_join(threads[linha-1],NULL);
    }
    
    for (int i = 0; i<total;i++) pthread_join(threads[i],NULL);
    //Libera todas as memorias alocadas
    free(file);
    free(mutexes);
    free(threads);
    free(str);
    remove("tudo.txt");
}

void *funcao(void* args){
    int *linha = (int*) args;
    func_main(total,str[(*linha)-1]);
    pthread_exit(NULL);
}
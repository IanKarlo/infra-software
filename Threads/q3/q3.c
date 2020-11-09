#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#define MAX 100

typedef struct thread_data{
    int id;
}thread_data;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_t *threads;
int counter = 0;

char palavra1[MAX];
char palavra2[MAX];
int size1,size2;
int qnt_threads;

void * substrings (void * arg){
    int *id = (int*) arg;
    int i,j;
    
    for(i=*id; i<=(size1-size2); i+=qnt_threads){
        for(j=0; j<size2; j++){
            if(palavra1[i+j] == palavra2[j]){
                if(j == size2 - 1){
                    pthread_mutex_lock(&lock);
                    counter++;
                    pthread_mutex_unlock(&lock); 
                }
            }
            else {
                j = size2;
            }         
        }
    }
    pthread_exit(NULL);
}

int main(){
    
    int i,j;
    
    printf("String 1:");
    scanf(" %[^\n]",palavra1);
    do{
    printf("String 2:");
    scanf(" %[^\n]",palavra2);
    }while(strlen(palavra2) > strlen(palavra1));

    size1 = strlen(palavra1);
    size2 = strlen(palavra2);

    do{printf("quantidade de threads:");
    scanf("%d",&qnt_threads);
    }while(qnt_threads < 1 ||(size1 % qnt_threads) != 0);

    threads = (pthread_t*)malloc(qnt_threads*sizeof(pthread_t));
    int id[qnt_threads];
        for(i = 0;i < qnt_threads;i++) {
            id[i] = i;
            pthread_create(&threads[i],NULL,substrings,&id[i]);
        }
        for(j = 0;j < qnt_threads;j++) pthread_join(threads[j],NULL);
        printf("existem %d substrings\n",counter);   
    free(threads);
}
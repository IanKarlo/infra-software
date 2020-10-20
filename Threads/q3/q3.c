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
char s1[MAX];
char s2[MAX];
int n1,n2;
int qnt_threads;
void * substrings (void * arg){
    int * t = (int*) arg;
    int i,j;
    
    for(i=*t;i<=(n1-n2);i+=qnt_threads){
        for(j=0;j<n2;j++){
            if(s1[i+j] == s2[j]){
                
                if(j == n2-1){
                    pthread_mutex_lock(&lock);
                    counter++;
                    pthread_mutex_unlock(&lock); 
                }
            }
            else {
                j = n2;
            }         
            
            
        }
    }
    
     
    pthread_exit(NULL);
}
int main(){
    
    int i,j;
    
    printf("String 1:");
    scanf("%s",s1);
    do{
    printf("String 2:");
    scanf("%s",s2);
    }while(strlen(s2)>strlen(s1));

    n1 = strlen(s1);
    n2 = strlen(s2);

    do{printf("quantidade de threads:");
    scanf("%d",&qnt_threads);
    }while(qnt_threads < 1 ||(n1 % qnt_threads) != 0);

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
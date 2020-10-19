#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* Variaveis Globais */
int i = 0;                        // Variavel de incremento
pthread_mutex_t lock;             // Mutex
pthread_t *threads;               // Vetor de threads

/* Funções do Programa */

void *ThreadFunc(void *arg) {    //Função da thread 

    while(i < 1000000){

      pthread_mutex_lock(&lock);
      if(i == 1000000){
        printf("A thread com ID: %lu, alcançou o limite!\n",pthread_self());
        i++;
        free(threads);
        exit(0);
      }
      i++;
      pthread_mutex_unlock(&lock);
    }

    return NULL;
} 

/* Main */
   
int main() {

    int n;

    if (pthread_mutex_init(&lock, NULL) != 0) {
      puts("\n Erro na inicialização do mutex!\n");
      return 1;
    }

    printf("Digite a quantidade de threads: ");
    scanf("%d", &n);

    if(n < 0) {
      puts("Valor invalido!");
      exit(-1);
    }

    threads = (pthread_t*) malloc(n * sizeof(pthread_t));
    if(threads == NULL){
      puts("Erro de alocação!\nPrograma encerrado!");
      exit(-1);
    }

    for(int j = 0; j < n; j++) {
      pthread_create(&threads[j], NULL, ThreadFunc, NULL); 
    }
    for(int j = 0; j < n; j++) {
      pthread_join(threads[j], NULL); 
    }
    exit(0); 
}

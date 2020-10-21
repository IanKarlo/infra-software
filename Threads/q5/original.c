#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#define TAM 10 //tamanho das dimensões da matriz e vetores
#define K_ITER 1000 //quantidade de iterações para precisão do valor

typedef struct{
  int index;
  int start;
  int size;
} Data;

/* Variaveis Globais */
pthread_barrier_t barrier;       // barreira
int i = 0;                        // Variavel de incremento           
pthread_t *threads;               // Vetor de threads
double x_vector[10] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };      // Vetor com os valores de Xi -> equivalente a X^k

double b_vector[10] = { 25, 35, 16, 73, 84, 33, 37, 123, 267, 17 };
double matriz[10][10] = { 
    { 10, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, 
    { 1, 10, 1, 1, 1, 1, 1, 1, 1, 1 }, 
    { 1, 1, 10, 1, 1, 1, 1, 1, 1, 1 }, 
    { 1, 1, 1, 10, 1, 1, 1, 1, 1, 1 }, 
    { 1, 1, 1, 1, 10, 1, 1, 1, 1, 1 }, 
    { 1, 1, 1, 1, 1, 10, 1, 1, 1, 1 }, 
    { 1, 1, 1, 1, 1, 1, 10, 1, 1, 1 }, 
    { 1, 1, 1, 1, 1, 1, 1, 10, 1, 1 }, 
    { 1, 1, 1, 1, 1, 1, 1, 1, 10, 1 }, 
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 10 }
  };

void get_matrix(){
    int tamanho;
    FILE* file = fopen("matrix.txt","r");
    fscanf(" %d", &tamanho);
    //Gerar tamanhos
    
}
void free_matrix(){

}

/* Funções do Programa */

void *ThreadFunc(void *arg) {    //Função da thread 

  Data values = *((Data *) arg);

  int size = values.size;
  double *x_next = (double *) malloc(size*sizeof(double));
  double sum;
  int i;

  for(int k = 0; k < K_ITER; k++){
    for(int x_index=0; x_index < size; x_index++){
      
      sum = 0;
      i = x_index + values.start;

      for(int j = 0; j < TAM; j++){
        if(i != j){
          sum += matriz[i][j] * x_vector[j];
        }
      }

      x_next[x_index] = (b_vector[i] - sum)/matriz[i][i];
      
    }
    pthread_barrier_wait (&barrier); // espera todas as threads calcularem todos os novos valores das incógnitas

    for(int x_index=0; x_index < size; x_index++){
      x_vector[x_index + values.start] = x_next[x_index];
    }

    pthread_barrier_wait (&barrier); // espera todas as threads substituirem os valores das incógnitas pelos novos calculados
  }

  free(x_next);
  pthread_exit(NULL);
} 

/* Main */
   
int main() {
    /* Inicialização das variaveis */
    int n;
    Data *args;
    printf("Digite a quantidade de threads: ");
    scanf("%d", &n);
    get_matrix();

    /* Validação da quantidade de threads */

    if(n > 10) n = 10;

    if(n < 1) {
      puts("Quantidade inválida de threads!");
      exit(1);
    }

    /* Alocação de memória*/

    threads = (pthread_t*) malloc(n * sizeof(pthread_t));
    if(threads == NULL){
      printf("Erro de alocação!\nPrograma encerrado!\n");
      exit(-1);
    }

     args = (Data*) malloc(n * sizeof(Data));
    if(args == NULL){
      printf("Erro de alocação!\nPrograma encerrado!\n");
      exit(-1);
    }
    pthread_barrier_init(&barrier, NULL, n); //Inicialização da barreira

    /* Variaveis para divisão de incógnitas por thread*/

    int perThread = 10/n;
    int mod = 10%n;
    int start = 0;  

    for(int j = 0; j < n; j++) {
      args[j].index = j;
      args[j].start = start;
      if(mod > 0){
        args[j].size = perThread + 1;
        mod--;
      } else {
        args[j].size = perThread;
      }
      start += args[j].size;
      pthread_create(&threads[j], NULL, ThreadFunc, &(args[j]));
    }
    for(int j = 0; j < n; j++) {
      pthread_join(threads[j], NULL); 
    }

    for(int j = 0; j < 10; j++){
      printf("X%d : %lf\n",j+1,x_vector[j]);
    }

    free(args);
    free(threads);

    exit(0); 
}

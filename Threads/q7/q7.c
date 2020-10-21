#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//Matriz global
int *red,*green,*blue;
int counter = 0;
int quantidade_threads;
int largura,altura,maximo;
pthread_t* threads; 

void* funcao(void* index);

int main(){
    printf("Quantas de threads? ");
    scanf(" %d", &quantidade_threads);
    char nome[30];
    printf("Qual o nome da imagem ppm? ");
    scanf(" %[^\n]",nome);
    FILE *f = fopen(nome,"r");
    
    //Pega as informações basicas
    fscanf(f,"P3 %d %d %d",&largura,&altura,&maximo);
    red = (int*) malloc(sizeof(int)*largura*altura);
    green = (int*) malloc(sizeof(int)*largura*altura);
    blue = (int*) malloc(sizeof(int)*largura*altura);
    threads = (pthread_t*) malloc(sizeof(pthread_t)*quantidade_threads);
    int *nums = (int*) malloc(sizeof(int)*largura*altura);

    //Pega o geral
    int r,g,b, index=0;
    while(fscanf(f," %d %d %d",&r,&g,&b)!=EOF){
        red[index]=r;
        green[index]=g;
        blue[index]=b;
        nums[index]=index;
        index++;
    }
    for(int i=0;i<quantidade_threads;i++){pthread_create(&threads[i],NULL,funcao,&nums[i]);}
    for(int i=0;i<quantidade_threads;i++){pthread_join(threads[i],NULL);}

    //Imprime de volta
    FILE* novo = fopen("traducao.ppm","w");
    fprintf(novo,"P3 %d %d %d\n\n",largura,altura,maximo);
    for(int i=0;i<altura*largura;i++){fprintf(novo,"%d %d %d\n",red[i],green[i],blue[i]);}

    //Libera todos
    free(red);
    free(green);
    free(blue);
    free(threads);
    free(nums);
    fclose(f);
}

void* funcao(void* index){
    int i = *((int*) index);
    for(;i<largura*altura;i+=quantidade_threads){
        int tom_c = (int) red[i]*0.30 + green[i]*0.59 + blue[i]*0.11;
        red[i]=tom_c;
        green[i]=tom_c;
        blue[i]=tom_c;
    }
    pthread_exit(NULL);
}

#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//Matriz global
int *red,*green,*blue;
int counter = 0;

void* funcao(void* index);

int main(){
    pthread_t* threads; //Aumentaremos cada valor de acordo com a necessidade;

    char nome[30];
    printf("Qual o nome da imagem ppm? ");
    scanf(" %[^\n]",nome);
    FILE *f = fopen(nome,"r");
    
    //Pega as informações basicas
    int largura,altura,maximo;
    fscanf(f,"P3 %d %d %d",&largura,&altura,&maximo);
    red = (int*) malloc(sizeof(int)*largura*altura);
    green = (int*) malloc(sizeof(int)*largura*altura);
    blue = (int*) malloc(sizeof(int)*largura*altura);
    threads = (pthread_t*) malloc(sizeof(pthread_t)*largura*altura);
    int *nums = (int*) malloc(sizeof(int)*largura*altura);

    

    //Pega o geral
    int b,r,g, index=0;
    while(fscanf(f," %d %d %d",&r,&g,&b)!=EOF){
        red[index]=r;
        green[index]=g;
        blue[index]=b;
        nums[index]=index;
        index++;
    }
    for(int i=0;i<largura*altura;i++){pthread_create(&threads[index],NULL,funcao,&nums[i]);}
    for(int i=0;i<largura*altura;i++){pthread_join(threads[i],NULL);}

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
    int tom_c = (int) red[i]*0.30 + green[i]*0.59 + blue[i]*0.11;
    red[i]=tom_c;
    green[i]=tom_c;
    blue[i]=tom_c;
    pthread_exit(NULL);
}

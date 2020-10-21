#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(){
    char cidades[12][15] = {"Luxemburgo","Paris","Tokyo","Recife","NovaYork","Seoul","Berlim","Madri","Estocolmo","Madri","Nice","St.Petsbu."};
    char letras[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    srand(time(NULL));
    int arquivos,linhas,casos;
    printf("Quantos arquivos? ");
    scanf(" %d",&arquivos);
    printf("Quantas linhas? ");
    scanf(" %d",&linhas);
    printf("Quantos casos por arquivo? ");
    scanf(" %d",&casos);
    //Formar os numeros
    for(int i=1;i<=arquivos;i++){
        char nome[30];
        sprintf(nome,"example/file%02d.txt",i);
        FILE* file = fopen(nome,"w");
        for(int j=1;j<=casos;j++){
            int linha = rand()%(linhas+1);
            fprintf(file,"%d\n",linha==0?1:linha);
            fprintf(file,"%d%d%d%c%c%c %s %02d:%02d\n",rand()%10,rand()%10,rand()%10,
                letras[rand()%26],letras[rand()%26],letras[rand()%26],
                cidades[rand()%12],rand()%24,rand()%60);
        }
        fclose(file);
    }
}

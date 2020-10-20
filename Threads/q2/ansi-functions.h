#include <stdio.h>
#include <string.h>
#include <pthread.h>
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Funções para mover o cursor
void left(int n)    {printf("\u001b[%dD", n);}
void right(int n)   {printf("\u001b[%dC", n);}
void up(int n)      {printf("\u001b[%dA", n);}
void down(int n)    {printf("\u001b[%dB", n);}

void next_line(int n){printf("\u001b[%dE",n);}
void prev_line(int n){printf("\u001b[%dF",n);}

void save_pos(){printf("\u001b[s");}
void ret_pos(){printf("\u001b[u");}

void erase_line(){printf("\u001b[2K");}
void erase_display(){printf("\u001b[2J");fflush(stdout);}

// \033[38;2;<r>;<g>;<b>m     #Select RGB foreground color
// \033[48;2;<r>;<g>;<b>m     #Select RGB background color

void print_red()    {printf("\033[38;2;0;0;0m"); printf("\033[48;2;255;0;0m");}
void print_yellow() {printf("\033[38;2;0;0;0m"); printf("\033[48;2;255;255;0m");}
void print_blue()   {printf("\033[38;2;0;0;0m"); printf("\033[48;2;0;0;255m");}
void print_magenta(){printf("\033[38;2;0;0;0m"); printf("\033[48;2;255;0;255m");}
void print_green()  {printf("\033[38;2;0;0;0m"); printf("\033[48;2;0;255;0m");}
void print_black()  {printf("\033[38;2;255;255;255m"); printf("\033[48;2;0;0;0m");}
void print_cyan()   {printf("\033[38;2;0;0;0m"); printf("\033[48;2;0;255;255m");}

void reset(){printf("\e[0m");fflush(stdout);}

// imprimir tudo certinho
typedef struct  imprimir{
    char codigo[10];
    char cidade[15];
    char horario[10];
    int linha;
}imprimir;

void print_line(char* codigo, char* cidade, char* horario){
    printf("%s %s",codigo,cidade);
    int espacos = 13 - strlen(cidade);
    for (int i=0;i<espacos;i++)printf(" ");
    printf("%s",horario);
    fflush(stdout);
}

void func_main(int total, imprimir str){
    pthread_mutex_lock(&mutex);
    ret_pos();
    next_line(str.linha);
    switch(str.linha % 7){
        case 0: {print_red(); break;}
        case 1: {print_yellow(); break;}
        case 2: {print_blue(); break;}
        case 3: {print_magenta(); break;}
        case 4: {print_green(); break;}
        case 5: {print_black(); break;}
        case 6: {print_cyan(); break;}
    }
    print_line(str.codigo,str.cidade,str.horario);
    reset();
    next_line(total-str.linha+1); printf(" "); //Apenas para ir para lá
    pthread_mutex_unlock(&mutex);
}

void first_print(int linhas){
    imprimir str;
    strcpy(str.codigo,"      ");
    strcpy(str.cidade," ");
    strcpy(str.horario,"     ");
    for(int i=1;i<=linhas;i++){str.linha=i; func_main(linhas,str);}
}

void start(){
    up(11); //Só para ficar no topo de algo
    save_pos();
    erase_display(); //Isso só funciona pra ficar tudo em uma mesma linha
}

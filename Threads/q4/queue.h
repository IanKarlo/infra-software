#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#define MAXSIZE 10000

typedef struct Elem
{
    int x,y;
    int (*funcao)();
    int resultado;
    int id;
    struct Elem *next;
}Elem;
typedef struct Queue
{
    int max,size;
    Elem *first;
    Elem *last;
}Queue;

//Todas
void display(Elem* first);

Queue *newQueue(int maxsize)
{
    Queue* q = (Queue*) malloc(sizeof(Queue));
    if (maxsize==-1) q->max = MAXSIZE;
    else q->max = maxsize;
    q->size = 0;
    q->first = NULL;
    q->last = NULL;
    return q;
}

int isempty(Queue *q) {return (q->first == NULL);}

void putQueue_complete(Queue *q, int x, int y, int id, int (*func)(), int resultado)//O resultado e temporario
{
    // pthread_mutex_lock(&mutex);
    Elem *temp;
    temp = (Elem*) malloc(sizeof(Elem));

    //Setting up
    temp->next = NULL;
    temp->x = x;
    temp->y = y;
    temp->id = id;
    temp->funcao = func;
    temp->resultado = resultado; //temporario

    if(!isempty(q)) {q->last->next = temp; q->last = temp;}
    else {q->first = q->last = temp;}
    q->size++;
    // pthread_mutex_unlock(&mutex); 
}

void putQueue_node(Queue *q, Elem* e){
    if(!isempty(q)) {q->last->next = e; q->last = e;}
    else {q->first = q->last = e;}
    q->size++;
}

Elem *takeQueue_first(Queue *q)
{
    Elem *tmp;
    int n = q->first->resultado;
    tmp = q->first;
    q->first = q->first->next;
    q->size--;
    return tmp;   
}

short int isthere(Queue *q,int id){
    Elem* e = q->first;
    while(e!=NULL){
        if (e->id==id) return 1;
        e = e->next;
    }
    return 0;
}

int takeQueue_key(Queue *q, int id){
    Elem *tmp,*anterior;
    if (!isthere(q,id)) {return -1;} //Temporario
    tmp = q->first;
    if (id == tmp->id){
        int n = tmp->resultado;
        q->size--;
        q->first=q->first->next;
        free(tmp);
        return n;
    }else{
        while(id != tmp->id){anterior = tmp; tmp=tmp->next;}
        int n =tmp->resultado;
        anterior->next = tmp->next;
        q->size--;
        free(tmp);
        return(n);   
    }
}

void display(Elem *first) //Serve para visualização
{
    if(first == NULL) printf("NULL\n");
    else
    {
        printf("%d ", first -> resultado);
        display(first->next);
    }
}

void freeQueue(Queue *q){
    Elem* e = q->first;
    while(e!=NULL){q->first=q->first->next; free(e); e=q->first;}
    free(q);
}
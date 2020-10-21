#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//threads
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t empty = PTHREAD_COND_INITIALIZER, full = PTHREAD_COND_INITIALIZER;
pthread_t cons,prod;
int produtos_total,produzidos=0,consumidos=0;


typedef struct Elem
{
    int value;
    struct Elem *prox;
}Elem;

typedef struct BlockingQueue
{
    unsigned int sizeBuffer,statusBuffer;
    Elem *head;
    Elem *last;
}BlockingQueue;

BlockingQueue *newBlockingQueue(unsigned int size)
{
    BlockingQueue* q = (BlockingQueue*) malloc(sizeof(BlockingQueue));
    q->sizeBuffer = size;
    q->statusBuffer = 0;
    q->head = NULL;
    q->last = NULL;
    return q;
}

int isempty(BlockingQueue *q) {return (q->last == NULL);}

void putBlockingQueue(BlockingQueue *q, int value)
{
    if (q->statusBuffer < q->sizeBuffer)
    {
        Elem *temp;
        temp = (Elem*) malloc(sizeof(Elem));
        temp->value = value;
        temp->prox = NULL;
        if(!isempty(q)) {q->last->prox = temp; q->last = temp;}
        else {q->head = q->last = temp;}
        q->statusBuffer++;
    }
    else printf("List is full\n");
}

int takeBlockingQueue(BlockingQueue *q)
{
    if (isempty(q)) {printf("O queue está vazio.\n"); return -1;}
    Elem *tmp;
    int n = q->head->value;
    tmp = q->head;
    q->head = q->head->prox;
    q->statusBuffer--;
    free(tmp);
    return(n);
}

void display(Elem *head)
{
    if(head == NULL) printf("NULL\n");
    else
    {
        printf("%d ", head -> value);
        display(head->prox);
    }
}

int main()
{
    int x=1, y=2,z=3;
    x=y=z;
    printf(" %d %d %d\n",x,y,z);

    BlockingQueue *q = newBlockingQueue(10);
    printf("Queue before queue\n");
    display(q->head);
    takeBlockingQueue(q);
    printf("Queue after queue\n");
    display(q->head);
    return 0;
}
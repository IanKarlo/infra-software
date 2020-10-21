#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

//threads
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t empty = PTHREAD_COND_INITIALIZER, fill = PTHREAD_COND_INITIALIZER;
int producao=0, consumo=0;
short int flag=0;

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

int isempty(BlockingQueue *q) {return (q->head == NULL);}

void putBlockingQueue(BlockingQueue *q, int value)
{
    // pthread_mutex_lock(&mutex);
    while (q->statusBuffer == q->sizeBuffer) {pthread_cond_wait(&empty, &mutex);}
    Elem *temp;
    temp = (Elem*) malloc(sizeof(Elem));
    temp->value = value;
    temp->prox = NULL;
    if(!isempty(q)) {q->last->prox = temp; q->last = temp;}
    else {q->head = q->last = temp;}
    q->statusBuffer++;
    // pthread_mutex_unlock(&mutex); 
    if(q->statusBuffer == 1) {pthread_cond_broadcast(&fill);}
}

int takeBlockingQueue(BlockingQueue *q)
{
    // pthread_mutex_lock(&mutex);
    while(q->statusBuffer == 0) {pthread_cond_wait(&fill, &mutex);}    
    Elem *tmp;
    int n = q->head->value;
    tmp = q->head;
    q->head = q->head->prox;
    q->statusBuffer--;
    free(tmp);
    // pthread_mutex_unlock(&mutex); 
    if(q->statusBuffer == q->sizeBuffer-1){pthread_cond_broadcast(&empty);}
    return(n);
    
}

void display(Elem *head) //Serve para visualização
{
    if(head == NULL) printf("NULL\n");
    else
    {
        printf("%d ", head -> value);
        display(head->prox);
    }
}

//funcoes
void *consumer(void *q){
    int v;
    BlockingQueue* Q = (BlockingQueue*) q;
    while(1){
        pthread_mutex_lock(&mutex);
        consumo++;
        v = takeBlockingQueue(Q);
        printf("Consumiu %d\n",v);
        pthread_mutex_unlock(&mutex);
        if (flag) break;
    }
    printf("Consumidor terminou\n");
    pthread_exit(NULL);
}

void *producer(void *q) {
    BlockingQueue* Q = (BlockingQueue*) q;
    while(1){
        pthread_mutex_lock(&mutex);
        producao++;
        putBlockingQueue(Q,producao);
        printf("Produziu %d\n",producao);
        pthread_mutex_unlock(&mutex);
        if (flag) break;
    }
    printf("Produtor terminou\n");
    pthread_exit(NULL);
}

void freeQueue(BlockingQueue *q){
    Elem* e = q->head;
    while(e!=NULL){q->head=q->head->prox; free(e); e=q->head;}
    free(q);
}

int main()
{
    pthread_t *threads;
    int B,C,P,Segundos;
    printf("Digite o tamanho do buffer: ");
    scanf(" %d",&B);
    BlockingQueue *q = newBlockingQueue(B);
    printf("Digite quantas Consumidores: ");
    scanf(" %d",&C);
    printf("Digite quantas Produtores: ");
    scanf(" %d",&P);
    printf("Digite quantos Segundos deverão se passar até esse programa acabar: ");
    scanf(" %d",&Segundos);

    //Organizar as threads
    int total=C+P;
    threads = (pthread_t *) malloc(sizeof(pthread_t)*C*P);
    for(int i = 0;i<C;i++){pthread_create(&threads[i],NULL,consumer,q);}
    for(int i = C;i<total;i++){pthread_create(&threads[i],NULL,producer,q);}

    sleep(Segundos);
    flag=1;

    //Resultados
    for(int i=0;i<total;i++) pthread_join(threads[i],NULL);
    free(threads);

    printf("\nQueue restante\n");
    display(q->head);
    freeQueue(q);
    
    return 0;
}
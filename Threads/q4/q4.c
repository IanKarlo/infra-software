#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int counter = 0;
pthread_cond_t signal1 = PTHREAD_COND_INITIALIZER,signal2=PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *add(void* arg){
    for(int i=0;;i++){
        pthread_mutex_lock(&mutex);
        pthread_cond_wait(&signal1,&mutex);
        counter++;
        pthread_
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&signal1);
    }
    pthread_exit(NULL);
}


void *sub(void* arg){
    for(int i=0;;i++){
        pthread_mutex_lock(&mutex);
        if (i>0) pthread_cond_wait(&signal1,&mutex);
        counter--;
        getchar();
        printf("Counter %d",counter);
        fflush(stdout);
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&signal1);
    }
    pthread_exit(NULL);
}

void *reach(void *arg){
    printf("chegou\n");
    pthread_barrier_wait((pthread_barrier_t*) arg);
    pthread_exit(NULL);
}

int main(){
    pthread_t t1,t2,t3;
    pthread_barrier_t barrier;
    pthread_barrier_init(&barrier,NULL,3);
    pthread_create(&t1,NULL,reach,&barrier);
    pthread_create(&t2,NULL,reach,&barrier);
    pthread_create(&t3,NULL,reach,&barrier);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_join(t3,NULL);
    printf("%d\n",counter);
    pthread_barrier_destroy(&barrier);
}

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>

int step = 1, n = 4;
void *Thread_fun(void *arg);
void signalHandler(int signal);

int main(int argc, char const *argv[]){
    if(argc!=2){
        fprintf(stderr, "Debe haber exactamente un argumento, el valor de N\n");
        exit(1);
    }
    int count = 0;
    pthread_t threads[n];
    signal(SIGTSTP, signalHandler);
    signal(SIGPWR, signalHandler);
    for (int i = 0; i < n; i++){
        pthread_t tid;
        pthread_create(&tid, NULL, Thread_fun, NULL);
        threads[i] = tid;
    }
    while (1){
        pthread_kill(threads[count], 4);
        pause();
        count = count + step;
        if (count == n)
        {
            count = 0;
        }
        if (count < 0)
        {
            count = n - 1;
        }
    }
    pthread_exit(NULL);
    return 0;
}

void *Thread_fun(void *arg){
    while (1){
        pause();
        printf("%ld \n", pthread_self());
        kill(getpid(), 4);
    }
}

void signalHandler(int signal){
    switch (signal){
    case SIGTSTP:
        step *= -1;
        for (int i = 0; i < 10000000; i++){}
        break;
    case SIGPWR:
    default:
        break;
    }
}
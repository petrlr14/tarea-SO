#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

struct node{
  int data;
  struct node *next;
};

struct node *head=NULL;
struct node *tail=NULL;

int array[31];
char *signame[]={"INVALID", "SIGHUP", "SIGINT", "SIGQUIT", "SIGILL", "SIGTRAP", "SIGABRT", "SIGBUS", "SIGFPE", "SIGKILL", "SIGUSR1", "SIGSEGV", "SIGUSR2", "SIGPIPE", "SIGALRM", "SIGTERM", "SIGSTKFLT", "SIGCHLD", "SIGCONT", "SIGSTOP", "SIGTSTP", "SIGTTIN", "SIGTTOU", "SIGURG", "SIGXCPU", "SIGXFSZ", "SIGVTALRM", "SIGPROF", "SIGWINCH", "SIGPOLL", "SIGPWR", "SIGSYS", NULL};

void signalHandler(int signal);
void enqueue(int signal);

int main(int argc, char*argv[]){
  if(argc!=1){
    fprintf(stderr, "No deben haber argumentos\n");
    exit(1);
  }
  printf("Listening to signals in pid:%d...\n", getpid());
  for(int i= 0; i<31; i++){
    array[i]=0;
    signal(i+1, signalHandler);
  }
  while(1){}
}

void enqueue(int signal){
  struct node *nptr = malloc(sizeof(struct node));
  nptr->data=signal;
  nptr->next=NULL;
  if(tail==NULL){
    head=nptr;
    tail=nptr;    
  }else{
    tail->next=nptr;
    tail=nptr;
  }
}

void signalHandler(int signal){
  struct node *temp;
  switch (signal){
  case SIGINT:
    temp=head;
    while(temp!=NULL){
      printf("\nSe bloque la señal %s", signame[temp->data]);
      temp=temp->next;
    }
    printf("\n");
    exit(0);
    break;
  default:
    enqueue(signal);
    break;
  }
}
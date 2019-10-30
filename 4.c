#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>

/* Lista circular */
struct node
{
    int val;
    int index;
    struct node *next;
    struct node *prev;    
};
typedef struct node n;

n* create_node(int, int);
void add_node();
void display_from_beg();
void display_in_rev();
/* ********************************* */

/* Signal */
void signalHandler(int signal);
int reverse=0;
/* ********************************* */


n *new, *ptr, *prev;
n *first = NULL, *last = NULL;
int number = 0, count=0;

int main(int argc, char*argv[]){
  int N = atoi(argv[1]);
  int fd[2], process[N];
  int hijo, father=getpid();
  pipe(fd);
  for(int i=0; i<N; i++){
    if(!fork()){
      hijo = getpid();
      count++;
      close(fd[0]);
      close(1);
      dup(fd[1]);
      write(1, &hijo, sizeof(hijo));
      write(1, &count, sizeof(count));
    }else{/* daddy */
      close(0);
      close(fd[1]);
      dup(fd[0]);
      read(fd[0], &hijo, sizeof(hijo));
      read(fd[0], &count, sizeof(count));
      add_node(hijo, count);
      wait(NULL);
    }
  }
  if(father==getpid()){
    signal(SIGINT, signalHandler);
    ptr=first;
    while(1){
      display_from_beg();
      display_in_rev();
    }
  }else{
    kill(getpid(), SIGKILL);
    wait(NULL);
  }
}

n* create_node(int info, int count){
  new = (n *)malloc(sizeof(n));
  new->val = info;
  new->index=count;
  new->next = NULL;
  new->prev = NULL;
  return new;
}


void add_node(int info, int count){
  new = create_node(info, count);
  if (first == last && first == NULL){
    first = last = new;
    first->next = last->next = NULL;
    first->prev = last->prev = NULL;
  }else{
    last->next = new;
    new->prev = last;
    last = new;
    last->next = first;
    first->prev = last;
  }
}

void display_from_beg(){
  while(1){
    if(reverse){
      break;
    }
    printf("proceso hijo #%d: %d\n",ptr->index, ptr->val);
    sleep(1);
    ptr = ptr->next;
  }
}

void display_in_rev(){
  while(1){
    if(!reverse){
      break;
    }
    printf("proceso hijo #%d: %d\n",ptr->index, ptr->val);
    sleep(1);
    ptr=ptr->prev;
  }
}

void signalHandler(int signal){
  switch (signal){
  case SIGINT:
    if(reverse)
      reverse=0;
    else
      reverse=1;
    break;
  default:
    break;
  }
}
